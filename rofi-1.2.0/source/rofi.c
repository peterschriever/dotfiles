/**
 * rofi
 *
 * MIT/X11 License
 * Copyright (c) 2012 Sean Pringle <sean.pringle@gmail.com>
 * Modified 2013-2016 Qball Cow <qball@gmpclient.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <time.h>
#include <locale.h>
#include <xcb/xcb.h>
#include <xcb/xcb_aux.h>
#include <xcb/xcb_ewmh.h>
#include <xcb/xinerama.h>
#include <xcb/xkb.h>
#include <xkbcommon/xkbcommon.h>
#include <xkbcommon/xkbcommon-compose.h>
#include <xkbcommon/xkbcommon-x11.h>
#include <sys/types.h>

#include <glib-unix.h>

#include <libgwater-xcb.h>

#include "xcb-internal.h"
#include "xkb-internal.h"

#include "settings.h"
#include "mode.h"
#include "rofi.h"
#include "helper.h"
#include "textbox.h"
#include "x11-helper.h"
#include "xrmoptions.h"
#include "dialogs/dialogs.h"

#include "view.h"
#include "view-internal.h"

#include "gitconfig.h"

// Pidfile.
char             *pidfile   = NULL;
const char       *cache_dir = NULL;
struct xkb_stuff xkb        = {
    .xcb_connection = NULL,
    .context        = NULL,
    .keymap         = NULL,
    .state          = NULL,
    .compose        = {
        .table = NULL,
        .state = NULL
    }
};
char             *config_path = NULL;
// Array of modi.
Mode             **modi   = NULL;
unsigned int     num_modi = 0;
// Current selected switcher.
unsigned int     curr_switcher = 0;

GMainLoop        *main_loop        = NULL;
GWaterXcbSource  *main_loop_source = NULL;

static int       dmenu_mode = FALSE;

int              return_code = EXIT_SUCCESS;

void process_result ( RofiViewState *state );

void rofi_set_return_code ( int code )
{
    return_code = code;
}

unsigned int rofi_get_num_enabled_modi ( void )
{
    return num_modi;
}

const Mode * rofi_get_mode ( unsigned int index )
{
    return modi[index];
}

/**
 * @param name Name of the switcher to lookup.
 *
 * Find the index of the switcher with name.
 *
 * @returns index of the switcher in modi, -1 if not found.
 */
static int switcher_get ( const char *name )
{
    for ( unsigned int i = 0; i < num_modi; i++ ) {
        if ( strcmp ( mode_get_name ( modi[i] ), name ) == 0 ) {
            return i;
        }
    }
    return -1;
}

/**
 * Do needed steps to start showing the gui
 */
static int setup ()
{
    // Create pid file
    int pfd = create_pid_file ( pidfile );
    if ( pfd >= 0 ) {
        // Request truecolor visual.
        x11_create_visual_and_colormap ( );
        textbox_setup ();
    }
    return pfd;
}

/**
 * Teardown the gui.
 */
static void teardown ( int pfd )
{
    // Cleanup font setup.
    textbox_cleanup ( );

    // Release the window.
    release_keyboard ( );
    release_pointer ( );

    // Cleanup view
    rofi_view_cleanup ();
    // Cleanup pid file.
    remove_pid_file ( pfd );
}

static void __run_switcher_internal ( ModeMode mode, char *input )
{
    char          *prompt = g_strdup_printf ( "%s:", mode_get_display_name ( modi[mode] ) );
    curr_switcher = mode;
    RofiViewState * state = rofi_view_create ( modi[mode], input, prompt, NULL, MENU_NORMAL, process_result );
    g_free ( prompt );
    if ( state ) {
        rofi_view_set_active ( state );
    }
    else {
        rofi_view_set_active ( NULL );

        if ( rofi_view_get_active () == NULL ) {
            g_main_loop_quit ( main_loop  );
        }
    }
}
static void run_switcher ( ModeMode mode )
{
    // Otherwise check if requested mode is enabled.
    for ( unsigned int i = 0; i < num_modi; i++ ) {
        if ( !mode_init ( modi[i] ) ) {
            rofi_view_error_dialog ( ERROR_MSG ( "Failed to initialize all the modi." ), ERROR_MSG_MARKUP );
            return;
        }
    }
    char *input = g_strdup ( config.filter );
    __run_switcher_internal ( mode, input );
    g_free ( input );
}
void process_result ( RofiViewState *state )
{
    Mode *sw = state->sw;
    rofi_view_set_active ( NULL );
    if ( sw != NULL ) {
        unsigned int selected_line = rofi_view_get_selected_line ( state );;
        MenuReturn   mretv         = rofi_view_get_return_value ( state );
        char         *input        = g_strdup ( rofi_view_get_user_input ( state ) );
        ModeMode     retv          = mode_result ( sw, mretv, &input, selected_line );

        ModeMode     mode = curr_switcher;
        // Find next enabled
        if ( retv == NEXT_DIALOG ) {
            mode = ( mode + 1 ) % num_modi;
        }
        else if ( retv == PREVIOUS_DIALOG ) {
            if ( mode == 0 ) {
                mode = num_modi - 1;
            }
            else {
                mode = ( mode - 1 ) % num_modi;
            }
        }
        else if ( retv == RELOAD_DIALOG ) {
            // do nothing.
        }
        else if ( retv < MODE_EXIT ) {
            mode = ( retv ) % num_modi;
        }
        else {
            mode = retv;
        }
        if ( mode != MODE_EXIT ) {
            /**
             * Load in the new mode.
             */
            __run_switcher_internal ( mode, input );
        }
        g_free ( input );
    }
    rofi_view_free ( state );
}

/**
 * Help function.
 */
static void print_main_application_options ( void )
{
    int is_term = isatty ( fileno ( stdout ) );
    print_help_msg ( "-no-config", "", "Do not load configuration, use default values.", NULL, is_term );
    print_help_msg ( "-v,-version", "", "Print the version number and exit.", NULL, is_term  );
    print_help_msg ( "-dmenu", "", "Start in dmenu mode.", NULL, is_term );
    print_help_msg ( "-display", "[string]", "X server to contact.", "${DISPLAY}", is_term );
    print_help_msg ( "-h,-help", "", "This help message.", NULL, is_term );
    print_help_msg ( "-dump-xresources", "", "Dump the current configuration in Xresources format and exit.", NULL, is_term );
    print_help_msg ( "-dump-xresources-theme", "", "Dump the current color scheme in Xresources format and exit.", NULL, is_term );
    print_help_msg ( "-e", "[string]", "Show a dialog displaying the passed message and exit.", NULL, is_term );
    print_help_msg ( "-markup", "", "Enable pango markup where possible.", NULL, is_term );
    print_help_msg ( "-normal-window", "", "In dmenu mode, behave as a normal window. (experimental)", NULL, is_term );
    print_help_msg ( "-show", "[mode]", "Show the mode 'mode' and exit. The mode has to be enabled.", NULL, is_term );
}
static void help ( G_GNUC_UNUSED int argc, char **argv )
{
    printf ( "%s usage:\n", argv[0] );
    printf ( "\t%s [-options ...]\n\n", argv[0] );
    printf ( "Command line only options:\n" );
    print_main_application_options ();
    printf ( "DMENU command line options:\n" );
    print_dmenu_options ();
    printf ( "Global options:\n" );
    print_options ();
    printf ( "\n" );
    printf ( "For more information see: man rofi\n" );
#ifdef GIT_VERSION
    printf ( "Version:    "GIT_VERSION "\n" );
#else
    printf ( "Version:    "VERSION "\n" );
#endif
    printf ( "Bugreports: "PACKAGE_BUGREPORT "\n" );
}

/**
 * Function bound by 'atexit'.
 * Cleanup globally allocated memory.
 */
static void cleanup ()
{
    for ( unsigned int i = 0; i < num_modi; i++ ) {
        mode_destroy ( modi[i] );
    }
    rofi_view_workers_finalize ();
    if ( main_loop != NULL  ) {
        if ( main_loop_source ) {
            g_water_xcb_source_free ( main_loop_source );
        }
        g_main_loop_unref ( main_loop );
        main_loop = NULL;
    }
    // Cleanup
    xcb_stuff_wipe ( xcb );
    // Cleaning up memory allocated by the Xresources file.
    config_xresource_free ();
    for ( unsigned int i = 0; i < num_modi; i++ ) {
        mode_free ( &( modi[i] ) );
    }
    g_free ( modi );

    // Cleanup the custom keybinding
    cleanup_abe ();

    g_free ( config_path );

    TIMINGS_STOP ();
}

/**
 * Parse the switcher string, into internal array of type Mode.
 *
 * String is split on separator ','
 * First the three build-in modi are checked: window, run, ssh
 * if that fails, a script-switcher is created.
 */
static int add_mode ( const char * token )
{
    unsigned int index = num_modi;
    // Resize and add entry.
    modi = (Mode * *) g_realloc ( modi, sizeof ( Mode* ) * ( num_modi + 1 ) );

    // Window switcher.
#ifdef WINDOW_MODE
    if ( strcasecmp ( token, "window" ) == 0 ) {
        modi[num_modi] = &window_mode;
        num_modi++;
    }
    else if ( strcasecmp ( token, "windowcd" ) == 0 ) {
        modi[num_modi] = &window_mode_cd;
        num_modi++;
    }
    else
#endif // WINDOW_MODE
       // SSh dialog
    if ( strcasecmp ( token, "ssh" ) == 0 ) {
        modi[num_modi] = &ssh_mode;
        num_modi++;
    }
    else if ( strcasecmp ( token, mode_get_name ( &help_keys_mode ) ) == 0 ) {
        modi[num_modi] = &help_keys_mode;
        num_modi++;
    }
    // Run dialog
    else if ( strcasecmp ( token, "run" ) == 0 ) {
        modi[num_modi] = &run_mode;
        num_modi++;
    }
    else if ( strcasecmp ( token, "drun" ) == 0 ) {
        modi[num_modi] = &drun_mode;
        num_modi++;
    }
    // combi dialog
    else if ( strcasecmp ( token, "combi" ) == 0 ) {
        modi[num_modi] = &combi_mode;
        num_modi++;
    }
    else {
        // If not build in, use custom modi.
        Mode *sw = script_switcher_parse_setup ( token );
        if ( sw != NULL ) {
            modi[num_modi] = sw;
            mode_set_config ( sw );
            num_modi++;
        }
        else{
            // Report error, don't continue.
            fprintf ( stderr, "Invalid script switcher: %s\n", token );
        }
    }
    return ( index == num_modi ) ? -1 : (int) index;
}
static void setup_modi ( void )
{
    const char *const sep     = ",";
    char              *savept = NULL;
    // Make a copy, as strtok will modify it.
    char              *switcher_str = g_strdup ( config.modi );
    // Split token on ','. This modifies switcher_str.
    for ( char *token = strtok_r ( switcher_str, sep, &savept ); token != NULL; token = strtok_r ( NULL, sep, &savept ) ) {
        add_mode ( token );
    }
    // Free string that was modified by strtok_r
    g_free ( switcher_str );
    // We cannot do this in main loop, as we create pointer to string,
    // and re-alloc moves that pointer.
    mode_set_config ( &ssh_mode );
    mode_set_config ( &run_mode );
    mode_set_config ( &drun_mode );

#ifdef WINDOW_MODE
    mode_set_config ( &window_mode );
    mode_set_config ( &window_mode_cd );
#endif // WINDOW_MODE
    mode_set_config ( &combi_mode );
}

/**
 * Load configuration.
 * Following priority: (current), X, commandline arguments
 */
static inline void load_configuration ( )
{
    // Load distro default settings
    gchar *etc = g_build_filename ( SYSCONFDIR, "rofi.conf", NULL );
    if ( g_file_test ( etc, G_FILE_TEST_IS_REGULAR ) ) {
        config_parse_xresource_options_file ( etc );
    }
    g_free ( etc );
    // Load in config from X resources.
    config_parse_xresource_options ( xcb );
    config_parse_xresource_options_file ( config_path );

    // Parse command line for settings.
    config_parse_cmd_options ( );
}
static inline void load_configuration_dynamic ( )
{
    // Load in config from X resources.
    config_parse_xresource_options_dynamic ( xcb );
    config_parse_xresource_options_dynamic_file ( config_path );
    config_parse_cmd_options_dynamic (  );
}

/**
 * Process X11 events in the main-loop (gui-thread) of the application.
 */
static gboolean main_loop_x11_event_handler ( xcb_generic_event_t *ev, G_GNUC_UNUSED gpointer data )
{
    if ( ev == NULL ) {
        int status = xcb_connection_has_error ( xcb->connection );
        fprintf ( stderr, "The XCB connection to X server had a fatal error: %d\n", status );
        g_main_loop_quit ( main_loop );
        return G_SOURCE_REMOVE;
    }
    uint8_t type = ev->response_type & ~0x80;
    if ( type == xkb.first_event ) {
        switch ( ev->pad0 )
        {
        case XCB_XKB_MAP_NOTIFY:
            xkb_state_unref ( xkb.state );
            xkb_keymap_unref ( xkb.keymap );
            xkb.keymap = xkb_x11_keymap_new_from_device ( xkb.context, xcb->connection, xkb.device_id, 0 );
            xkb.state  = xkb_x11_state_new_from_device ( xkb.keymap, xcb->connection, xkb.device_id );
            break;
        case XCB_XKB_STATE_NOTIFY:
        {
            xcb_xkb_state_notify_event_t *ksne = (xcb_xkb_state_notify_event_t *) ev;
            guint                        modmask;
            xkb_state_update_mask ( xkb.state,
                                    ksne->baseMods,
                                    ksne->latchedMods,
                                    ksne->lockedMods,
                                    ksne->baseGroup,
                                    ksne->latchedGroup,
                                    ksne->lockedGroup );
            modmask = x11_get_current_mask ( &xkb );
            if ( modmask == 0 ) {
                abe_trigger_release ( );
            }
            break;
        }
        }
        return G_SOURCE_CONTINUE;
    }
    RofiViewState *state = rofi_view_get_active ();
    if ( xcb->sndisplay != NULL ) {
        sn_xcb_display_process_event ( xcb->sndisplay, ev );
    }
    if ( state != NULL ) {
        rofi_view_itterrate ( state, ev, &xkb );
        if ( rofi_view_get_completed ( state ) ) {
            // This menu is done.
            rofi_view_finalize ( state );
            // cleanup
            if ( rofi_view_get_active () == NULL ) {
                g_main_loop_quit ( main_loop );
            }
        }
    }
    return G_SOURCE_CONTINUE;
}

static gboolean main_loop_signal_handler_int ( G_GNUC_UNUSED gpointer data )
{
    // Break out of loop.
    g_main_loop_quit ( main_loop );
    return G_SOURCE_CONTINUE;
}

static int error_trap_depth = 0;
static void error_trap_push ( G_GNUC_UNUSED SnDisplay *display, G_GNUC_UNUSED xcb_connection_t *xdisplay )
{
    ++error_trap_depth;
}

static void error_trap_pop ( G_GNUC_UNUSED SnDisplay *display, xcb_connection_t *xdisplay )
{
    if ( error_trap_depth == 0 ) {
        fprintf ( stderr, "Error trap underflow!\n" );
        exit ( EXIT_FAILURE );
    }

    xcb_flush ( xdisplay );
    --error_trap_depth;
}

static gboolean startup ( G_GNUC_UNUSED gpointer data )
{
    TICK_N ( "Startup" );
    // flags to run immediately and exit
    char      *sname       = NULL;
    char      *msg         = NULL;
    MenuFlags window_flags = MENU_NORMAL;

    if ( find_arg ( "-normal-window" ) >= 0 ) {
        window_flags |= MENU_NORMAL_WINDOW;
    }

    /**
     * Create window (without showing)
     */
    __create_window ( window_flags );

    //
    // Sanity check
    if ( config_sanity_check ( ) ) {
        return G_SOURCE_REMOVE;
    }
    TICK_N ( "Config sanity check" );
    // Parse the keybindings.
    if ( !parse_keys_abe () ) {
        // Error dialog
        return G_SOURCE_REMOVE;
    }
    TICK_N ( "Parse ABE" );
    // Dmenu mode.
    if ( dmenu_mode == TRUE ) {
        // force off sidebar mode:
        config.sidebar_mode = FALSE;
        int retv = dmenu_switcher_dialog ();
        if ( retv ) {
            rofi_set_return_code ( EXIT_SUCCESS );
            // Directly exit.
            g_main_loop_quit ( main_loop );
        }
    }
    else if ( find_arg_str (  "-e", &( msg ) ) ) {
        int markup = FALSE;
        if ( find_arg ( "-markup" ) >= 0 ) {
            markup = TRUE;
        }
        if (  !rofi_view_error_dialog ( msg, markup ) ) {
            g_main_loop_quit ( main_loop );
        }
    }
    else if ( find_arg_str ( "-show", &sname ) == TRUE ) {
        int index = switcher_get ( sname );
        if ( index < 0 ) {
            // Add it to the list
            index = add_mode ( sname );
            // Complain
            if ( index >= 0 ) {
                fprintf ( stdout, "Mode %s not enabled. Please add it to the list of enabled modi: %s\n",
                          sname, config.modi );
                fprintf ( stdout, "Adding mode: %s\n", sname );
            }
            // Run it anyway if found.
        }
        if ( index >= 0 ) {
            run_switcher ( index );
        }
        else {
            fprintf ( stderr, "The %s switcher has not been enabled\n", sname );
            g_main_loop_quit ( main_loop );
            return G_SOURCE_REMOVE;
        }
    }
    else if ( find_arg ( "-show" ) >= 0 && num_modi > 0 ) {
        run_switcher ( 0 );
    }
    else{
        // Daemon mode
        fprintf ( stderr, "Rofi daemon mode is now removed.\n" );
        fprintf ( stderr, "Please use your window manager binding functionality or xbindkeys to replace it.\n" );
        g_main_loop_quit ( main_loop );
    }

    return G_SOURCE_REMOVE;
}

int main ( int argc, char *argv[] )
{
    TIMINGS_START ();

    cmd_set_arguments ( argc, argv );

    // Version
    if ( find_arg (  "-v" ) >= 0 || find_arg (  "-version" ) >= 0 ) {
#ifdef GIT_VERSION
        fprintf ( stdout, "Version: "GIT_VERSION "\n" );
#else
        fprintf ( stdout, "Version: "VERSION "\n" );
#endif
        exit ( EXIT_SUCCESS );
    }

    // Detect if we are in dmenu mode.
    // This has two possible causes.
    // 1 the user specifies it on the command-line.
    if ( find_arg (  "-dmenu" ) >= 0 ) {
        dmenu_mode = TRUE;
    }
    // 2 the binary that executed is called dmenu (e.g. symlink to rofi)
    else{
        // Get the base name of the executable called.
        char               *base_name = g_path_get_basename ( argv[0] );
        const char * const dmenu_str  = "dmenu";
        dmenu_mode = ( strcmp ( base_name, dmenu_str ) == 0 );
        // Free the basename for dmenu detection.
        g_free ( base_name );
    }
    TICK ();
    // Get the path to the cache dir.
    cache_dir = g_get_user_cache_dir ();

    // Create pid file path.
    const char *path = g_get_user_runtime_dir ();
    if ( path ) {
        pidfile = g_build_filename ( path, "rofi.pid", NULL );
    }
    config_parser_add_option ( xrm_String, "pid", (void * *) &pidfile, "Pidfile location" );

    if ( find_arg ( "-config" ) < 0 ) {
        const char *cpath = g_get_user_config_dir ();
        if ( cpath ) {
            config_path = g_build_filename ( cpath, "rofi", "config", NULL );
        }
    }
    else {
        char *c = NULL;
        find_arg_str ( "-config", &c );
        config_path = rofi_expand_path ( c );
    }

    TICK ();
    // Register cleanup function.
    atexit ( cleanup );

    TICK ();
    // Get DISPLAY, first env, then argument.
    char *display_str = getenv ( "DISPLAY" );
    find_arg_str (  "-display", &display_str );

    if ( setlocale ( LC_ALL, "" ) == NULL ) {
        fprintf ( stderr, "Failed to set locale.\n" );
        return EXIT_FAILURE;
    }

    xcb->connection = xcb_connect ( display_str, &xcb->screen_nbr );
    if ( xcb_connection_has_error ( xcb->connection ) ) {
        fprintf ( stderr, "Failed to open display: %s", display_str );
        return EXIT_FAILURE;
    }
    TICK_N ( "Open Display" );

    xcb->screen = xcb_aux_get_screen ( xcb->connection, xcb->screen_nbr );

    xcb_intern_atom_cookie_t *ac     = xcb_ewmh_init_atoms ( xcb->connection, &xcb->ewmh );
    xcb_generic_error_t      *errors = NULL;
    xcb_ewmh_init_atoms_replies ( &xcb->ewmh, ac, &errors );
    if ( errors ) {
        fprintf ( stderr, "Failed to create EWMH atoms\n" );
        free ( errors );
    }

    if ( xkb_x11_setup_xkb_extension ( xcb->connection, XKB_X11_MIN_MAJOR_XKB_VERSION, XKB_X11_MIN_MINOR_XKB_VERSION,
                                       XKB_X11_SETUP_XKB_EXTENSION_NO_FLAGS, NULL, NULL, &xkb.first_event, NULL ) < 0 ) {
        fprintf ( stderr, "cannot setup XKB extension!\n" );
        return EXIT_FAILURE;
    }

    xkb.context = xkb_context_new ( XKB_CONTEXT_NO_FLAGS );
    if ( xkb.context == NULL ) {
        fprintf ( stderr, "cannot create XKB context!\n" );
        return EXIT_FAILURE;
    }
    xkb.xcb_connection = xcb->connection;

    xkb.device_id = xkb_x11_get_core_keyboard_device_id ( xcb->connection );

    enum
    {
        required_events =
            ( XCB_XKB_EVENT_TYPE_NEW_KEYBOARD_NOTIFY |
              XCB_XKB_EVENT_TYPE_MAP_NOTIFY |
              XCB_XKB_EVENT_TYPE_STATE_NOTIFY ),

        required_nkn_details =
            ( XCB_XKB_NKN_DETAIL_KEYCODES ),

        required_map_parts   =
            ( XCB_XKB_MAP_PART_KEY_TYPES |
              XCB_XKB_MAP_PART_KEY_SYMS |
              XCB_XKB_MAP_PART_MODIFIER_MAP |
              XCB_XKB_MAP_PART_EXPLICIT_COMPONENTS |
              XCB_XKB_MAP_PART_KEY_ACTIONS |
              XCB_XKB_MAP_PART_VIRTUAL_MODS |
              XCB_XKB_MAP_PART_VIRTUAL_MOD_MAP ),

        required_state_details =
            ( XCB_XKB_STATE_PART_MODIFIER_BASE |
              XCB_XKB_STATE_PART_MODIFIER_LATCH |
              XCB_XKB_STATE_PART_MODIFIER_LOCK |
              XCB_XKB_STATE_PART_GROUP_BASE |
              XCB_XKB_STATE_PART_GROUP_LATCH |
              XCB_XKB_STATE_PART_GROUP_LOCK ),
    };

    static const xcb_xkb_select_events_details_t details = {
        .affectNewKeyboard  = required_nkn_details,
        .newKeyboardDetails = required_nkn_details,
        .affectState        = required_state_details,
        .stateDetails       = required_state_details,
    };
    xcb_xkb_select_events ( xcb->connection, xkb.device_id, required_events, /* affectWhich */
                            0,                                               /* clear */
                            required_events,                                 /* selectAll */
                            required_map_parts,                              /* affectMap */
                            required_map_parts,                              /* map */
                            &details );

    xkb.keymap = xkb_x11_keymap_new_from_device ( xkb.context, xcb->connection, xkb.device_id, XKB_KEYMAP_COMPILE_NO_FLAGS );
    if ( xkb.keymap == NULL ) {
        fprintf ( stderr, "Failed to get Keymap for current keyboard device.\n" );
        return EXIT_FAILURE;
    }
    xkb.state = xkb_x11_state_new_from_device ( xkb.keymap, xcb->connection, xkb.device_id );
    if ( xkb.state == NULL ) {
        fprintf ( stderr, "Failed to get state object for current keyboard device.\n" );
        return EXIT_FAILURE;
    }

    xkb.compose.table = xkb_compose_table_new_from_locale ( xkb.context, setlocale ( LC_CTYPE, NULL ), 0 );
    if ( xkb.compose.table != NULL ) {
        xkb.compose.state = xkb_compose_state_new ( xkb.compose.table, 0 );
    }
    else {
        fprintf ( stderr, "Failed to get keyboard compose table. Trying to limp on.\n" );
    }

    if ( xcb_connection_has_error ( xcb->connection ) ) {
        fprintf ( stderr, "Connection has error\n" );
        exit ( EXIT_FAILURE );
    }
    x11_setup ( &xkb );
    if ( xcb_connection_has_error ( xcb->connection ) ) {
        fprintf ( stderr, "Connection has error\n" );
        exit ( EXIT_FAILURE );
    }

    const xcb_query_extension_reply_t *er = xcb_get_extension_data ( xcb->connection, &xcb_xinerama_id );
    if ( er ) {
        if ( er->present ) {
            xcb_xinerama_is_active_cookie_t is_active_req = xcb_xinerama_is_active ( xcb->connection );
            xcb_xinerama_is_active_reply_t  *is_active    = xcb_xinerama_is_active_reply ( xcb->connection, is_active_req, NULL );
            xcb->has_xinerama = is_active->state;
            free ( is_active );
        }
    }
    main_loop = g_main_loop_new ( NULL, FALSE );

    TICK_N ( "Setup mainloop" );
    // startup not.
    xcb->sndisplay = sn_xcb_display_new ( xcb->connection, error_trap_push, error_trap_pop );
    if ( xcb_connection_has_error ( xcb->connection ) ) {
        fprintf ( stderr, "Connection has error\n" );
        exit ( EXIT_FAILURE );
    }

    if ( xcb->sndisplay != NULL ) {
        xcb->sncontext = sn_launchee_context_new_from_environment ( xcb->sndisplay, xcb->screen_nbr );
    }
    if ( xcb_connection_has_error ( xcb->connection ) ) {
        fprintf ( stderr, "Connection has error\n" );
        exit ( EXIT_FAILURE );
    }
    TICK_N ( "Startup Notification" );
    // Setup keybinding
    setup_abe ();
    TICK_N ( "Setup abe" );

    if ( find_arg ( "-no-config" ) < 0 ) {
        load_configuration ( );
    }
    if ( !dmenu_mode ) {
        // setup_modi
        setup_modi ();
    }

    if ( find_arg ( "-no-config" ) < 0 ) {
        // Reload for dynamic part.
        load_configuration_dynamic ( );
    }
    // Dump.
    // catch help request
    if ( find_arg (  "-h" ) >= 0 || find_arg (  "-help" ) >= 0 || find_arg (  "--help" ) >= 0 ) {
        help ( argc, argv );
        exit ( EXIT_SUCCESS );
    }
    if ( find_arg (  "-dump-xresources" ) >= 0 ) {
        config_parse_xresource_dump ();
        exit ( EXIT_SUCCESS );
    }
    if ( find_arg (  "-dump-xresources-theme" ) >= 0 ) {
        config_parse_xresources_theme_dump ();
        exit ( EXIT_SUCCESS );
    }

    main_loop_source = g_water_xcb_source_new_for_connection ( NULL, xcb->connection, main_loop_x11_event_handler, NULL, NULL );

    TICK_N ( "X11 Setup " );

    rofi_view_workers_initialize ();

    // Setup signal handling sources.
    // SIGINT
    g_unix_signal_add ( SIGINT, main_loop_signal_handler_int, NULL );

    g_idle_add ( startup, NULL );

    // Pidfile + visuals
    int pfd = setup ();
    if ( pfd < 0 ) {
        return EXIT_FAILURE;
    }
    // Start mainloop.
    g_main_loop_run ( main_loop );
    teardown ( pfd );
    return return_code;
}
