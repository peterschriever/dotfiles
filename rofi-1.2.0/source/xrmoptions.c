/**
 * rofi
 *
 * MIT/X11 License
 * Copyright 2013-2016 Qball Cow <qball@gmpclient.org>
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
 *
 */
#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <xcb/xcb.h>
#include <xcb/xkb.h>
#include <xcb/xcb_xrm.h>
#include <xkbcommon/xkbcommon.h>
#include <xkbcommon/xkbcommon-compose.h>
#include <xkbcommon/xkbcommon-x11.h>
#include <glib.h>
#include "xcb.h"
#include "xcb-internal.h"
#include "x11-helper.h"
#include "rofi.h"
#include "xrmoptions.h"
#include "settings.h"
#include "helper.h"

const char * const ConfigSourceStr[] = {
    "Default",
    "XResources",
    "File",
    "Commandline",
};
enum ConfigSource
{
    CONFIG_DEFAULT    = 0,
    CONFIG_XRESOURCES = 1,
    CONFIG_FILE       = 2,
    CONFIG_CMDLINE    = 3
};

typedef struct
{
    int        type;
    const char * name;
    union
    {
        unsigned int * num;
        int          * snum;
        char         ** str;
        void         *pointer;
        char         * charc;
    }                 value;
    char              *mem;
    const char        *comment;
    enum ConfigSource source;
} XrmOption;
/**
 * Map X resource and commandline options to internal options
 * Currently supports string, boolean and number (signed and unsigned).
 */
static XrmOption xrmOptions[] = {
    { xrm_String,  "switchers",         { .str  = &config.modi               }, NULL,
      "", CONFIG_DEFAULT },
    { xrm_String,  "modi",              { .str  = &config.modi               }, NULL,
      "Enabled modi", CONFIG_DEFAULT },
    { xrm_Number,  "opacity",           { .num  = &config.window_opacity     }, NULL,
      "Window opacity", CONFIG_DEFAULT },
    { xrm_SNumber, "width",             { .snum = &config.menu_width         }, NULL,
      "Window width", CONFIG_DEFAULT },
    { xrm_Number,  "lines",             { .num  = &config.menu_lines         }, NULL,
      "Number of lines", CONFIG_DEFAULT },
    { xrm_Number,  "columns",           { .num  = &config.menu_columns       }, NULL,
      "Number of columns", CONFIG_DEFAULT },

    { xrm_String,  "font",              { .str  = &config.menu_font          }, NULL,
      "Font to use", CONFIG_DEFAULT },
    { xrm_String,  "color-normal",      { .str  = &config.color_normal       }, NULL,
      "Color scheme for normal row", CONFIG_DEFAULT },
    { xrm_String,  "color-urgent",      { .str  = &config.color_urgent       }, NULL,
      "Color scheme for urgent row", CONFIG_DEFAULT },
    { xrm_String,  "color-active",      { .str  = &config.color_active       }, NULL,
      "Color scheme for active row", CONFIG_DEFAULT },
    { xrm_String,  "color-window",      { .str  = &config.color_window       }, NULL,
      "Color scheme window", CONFIG_DEFAULT },

    { xrm_Number,  "borderwidth",       { .num  = &config.menu_bw            }, NULL,
      "", CONFIG_DEFAULT },
    { xrm_Number,  "bw",                { .num  = &config.menu_bw            }, NULL,
      "Border width", CONFIG_DEFAULT },

    { xrm_Number,  "location",          { .num  = &config.location           }, NULL,
      "Location on screen", CONFIG_DEFAULT },

    { xrm_Number,  "padding",           { .num  = &config.padding            }, NULL,
      "Padding", CONFIG_DEFAULT },
    { xrm_SNumber, "yoffset",           { .snum = &config.y_offset           }, NULL,
      "Y-offset relative to location", CONFIG_DEFAULT },
    { xrm_SNumber, "xoffset",           { .snum = &config.x_offset           }, NULL,
      "X-offset relative to location", CONFIG_DEFAULT },
    { xrm_Boolean, "fixed-num-lines",   { .num  = &config.fixed_num_lines    }, NULL,
      "Always show number of lines", CONFIG_DEFAULT },

    { xrm_String,  "terminal",          { .str  = &config.terminal_emulator  }, NULL,
      "Terminal to use", CONFIG_DEFAULT },
    { xrm_String,  "ssh-client",        { .str  = &config.ssh_client         }, NULL,
      "Ssh client to use", CONFIG_DEFAULT },
    { xrm_String,  "ssh-command",       { .str  = &config.ssh_command        }, NULL,
      "Ssh command to execute", CONFIG_DEFAULT },
    { xrm_String,  "run-command",       { .str  = &config.run_command        }, NULL,
      "Run command to execute", CONFIG_DEFAULT },
    { xrm_String,  "run-list-command",  { .str  = &config.run_list_command   }, NULL,
      "Command to get extra run targets", CONFIG_DEFAULT },
    { xrm_String,  "run-shell-command", { .str  = &config.run_shell_command  }, NULL,
      "Run command to execute that runs in shell", CONFIG_DEFAULT },
    { xrm_String,  "window-command",    { .str  = &config.window_command     }, NULL,
      "Command executed on accep-entry-custom for window modus", CONFIG_DEFAULT },

    { xrm_Boolean, "disable-history",   { .num  = &config.disable_history    }, NULL,
      "Disable history in run/ssh", CONFIG_DEFAULT },
    { xrm_Boolean, "levenshtein-sort",  { .num  = &config.levenshtein_sort   }, NULL,
      "Use levenshtein sorting", CONFIG_DEFAULT },
    { xrm_Boolean, "case-sensitive",    { .num  = &config.case_sensitive     }, NULL,
      "Set case-sensitivity", CONFIG_DEFAULT },
    { xrm_Boolean, "cycle",             { .num  = &config.cycle              }, NULL,
      "Cycle through the results list", CONFIG_DEFAULT },
    { xrm_Boolean, "sidebar-mode",      { .num  = &config.sidebar_mode       }, NULL,
      "Enable sidebar-mode", CONFIG_DEFAULT },
    { xrm_SNumber, "eh",                { .snum = &config.element_height     }, NULL,
      "Row height (in chars)", CONFIG_DEFAULT },
    { xrm_Boolean, "auto-select",       { .num  = &config.auto_select        }, NULL,
      "Enable auto select mode", CONFIG_DEFAULT },
    { xrm_Boolean, "parse-hosts",       { .num  = &config.parse_hosts        }, NULL,
      "Parse hosts file for ssh mode", CONFIG_DEFAULT },
    { xrm_Boolean, "parse-known-hosts", { .num  = &config.parse_known_hosts  }, NULL,
      "Parse known_hosts file for ssh mode", CONFIG_DEFAULT },
    { xrm_String,  "combi-modi",        { .str  = &config.combi_modi         }, NULL,
      "Set the modi to combine in combi mode", CONFIG_DEFAULT },
    { xrm_Boolean, "glob",              { .num  = &config.glob               }, NULL,
      "Use glob matching", CONFIG_DEFAULT },
    { xrm_Boolean, "regex",             { .num  = &config.regex              }, NULL,
      "Use regex matching", CONFIG_DEFAULT },
    { xrm_Boolean, "tokenize",          { .num  = &config.tokenize           }, NULL,
      "Tokenize input string", CONFIG_DEFAULT },
    { xrm_Number,  "monitor",           { .snum = &config.monitor            }, NULL,
      "", CONFIG_DEFAULT },
    /* Alias for dmenu compatibility. */
    { xrm_SNumber, "m",                 { .snum = &config.monitor            }, NULL,
      "Monitor id to show on", CONFIG_DEFAULT },
    { xrm_Number,  "line-margin",       { .num  = &config.line_margin        }, NULL,
      "Margin between rows", CONFIG_DEFAULT },
    { xrm_String,  "filter",            { .str  = &config.filter             }, NULL,
      "Pre-set filter", CONFIG_DEFAULT },
    { xrm_String,  "separator-style",   { .str  = &config.separator_style    }, NULL,
      "Separator style (none, dash, solid)", CONFIG_DEFAULT },
    { xrm_Boolean, "hide-scrollbar",    { .num  = &config.hide_scrollbar     }, NULL,
      "Hide scroll-bar", CONFIG_DEFAULT },
    { xrm_Boolean, "fullscreen",        { .num  = &config.fullscreen         }, NULL,
      "Fullscreen", CONFIG_DEFAULT },
    { xrm_Boolean, "fake-transparency", { .num  = &config.fake_transparency  }, NULL,
      "Fake transparency", CONFIG_DEFAULT },
    { xrm_SNumber, "dpi",               { .snum = &config.dpi                }, NULL,
      "DPI", CONFIG_DEFAULT },
    { xrm_Number,  "threads",           { .num  = &config.threads            }, NULL,
      "Threads to use for string matching", CONFIG_DEFAULT },
    { xrm_Number,  "scrollbar-width",   { .num  = &config.scrollbar_width    }, NULL,
      "Scrollbar width", CONFIG_DEFAULT },
    { xrm_Number,  "scroll-method",     { .num  = &config.scroll_method      }, NULL,
      "Scrolling method. (0: Page, 1: Centered)", CONFIG_DEFAULT },
    { xrm_String,  "fake-background",   { .str  = &config.fake_background    }, NULL,
      "Background to use for fake transparency. (background or screenshot)", CONFIG_DEFAULT },
    { xrm_String,  "window-format",     { .str  = &config.window_format      }, NULL,
      "Window Format. w (desktop name), t (title), n (name), r (role), c (class)", CONFIG_DEFAULT },
};

// Dynamic options.
XrmOption    *extra_options    = NULL;
unsigned int num_extra_options = 0;

void config_parser_add_option ( XrmOptionType type, const char *key, void **value, const char *comment )
{
    extra_options = g_realloc ( extra_options, ( num_extra_options + 1 ) * sizeof ( XrmOption ) );

    extra_options[num_extra_options].type          = type;
    extra_options[num_extra_options].name          = key;
    extra_options[num_extra_options].value.pointer = value;
    extra_options[num_extra_options].comment       = comment;
    extra_options[num_extra_options].source        = CONFIG_DEFAULT;
    if ( type == xrm_String ) {
        extra_options[num_extra_options].mem = ( (char *) ( *value ) );
    }
    else {
        extra_options[num_extra_options].mem = NULL;
    }

    num_extra_options++;
}

static void config_parser_set ( XrmOption *option, char *xrmValue, enum ConfigSource source )
{
    if ( option->type == xrm_String ) {
        if ( ( option )->mem != NULL ) {
            g_free ( option->mem );
            option->mem = NULL;
        }
        *( option->value.str ) = g_strdup ( xrmValue );

        // Memory
        ( option )->mem = *( option->value.str );
    }
    else if ( option->type == xrm_Number ) {
        *( option->value.num ) = (unsigned int) g_ascii_strtoull ( xrmValue, NULL, 10 );
    }
    else if ( option->type == xrm_SNumber ) {
        *( option->value.snum ) = (int) g_ascii_strtoll ( xrmValue, NULL, 10 );
    }
    else if ( option->type == xrm_Boolean ) {
        if ( strlen ( xrmValue ) > 0 &&
             g_ascii_strcasecmp ( xrmValue, "true" ) == 0 ) {
            *( option->value.num ) = TRUE;
        }
        else{
            *( option->value.num ) = FALSE;
        }
    }
    else if ( option->type == xrm_Char ) {
        *( option->value.charc ) = helper_parse_char ( xrmValue );
    }
    option->source = source;
}

static void __config_parse_xresource_options ( xcb_xrm_database_t *xDB, enum ConfigSource source )
{
    const char * namePrefix = "rofi";

    for ( unsigned int i = 0; i < sizeof ( xrmOptions ) / sizeof ( XrmOption ); ++i ) {
        char *name = g_strdup_printf ( "%s.%s", namePrefix, xrmOptions[i].name );

        char *xrmValue = NULL;
        if ( xcb_xrm_resource_get_string ( xDB, name, NULL, &xrmValue ) == 0 ) {
            config_parser_set ( &( xrmOptions[i] ), xrmValue, source );
        }
        if ( xrmValue ) {
            free ( xrmValue );
        }

        g_free ( name );
    }
}
void config_parse_xresource_options ( xcb_stuff *xcb )
{
    xcb_xrm_database_t *xDB = xcb_xrm_database_from_default ( xcb->connection );
    if ( xDB ) {
        __config_parse_xresource_options ( xDB, CONFIG_XRESOURCES );
        xcb_xrm_database_free ( xDB );
    }
}
void config_parse_xresource_options_file ( const char *filename )
{
    if ( !filename ) {
        return;
    }
    // Map Xresource entries to rofi config options.
    xcb_xrm_database_t *xDB = xcb_xrm_database_from_file ( filename );
    if ( xDB == NULL ) {
        return;
    }
    __config_parse_xresource_options ( xDB, CONFIG_FILE );
    xcb_xrm_database_free ( xDB );
}

/**
 * Parse an option from the commandline vector.
 */
static void config_parse_cmd_option ( XrmOption *option )
{
    // Prepend a - to the option name.
    char *key = g_strdup_printf ( "-%s", option->name );
    switch ( option->type )
    {
    case xrm_Number:
        if ( find_arg_uint ( key, option->value.num ) == TRUE ) {
            option->source = CONFIG_CMDLINE;
        }
        break;
    case xrm_SNumber:
        if ( find_arg_int (  key, option->value.snum ) == TRUE ) {
            option->source = CONFIG_CMDLINE;
        }
        break;
    case xrm_String:
        if ( find_arg_str (  key, option->value.str ) == TRUE ) {
            if ( option->mem != NULL ) {
                g_free ( option->mem );
                option->mem = NULL;
            }
            option->source = CONFIG_CMDLINE;
        }
        break;
    case xrm_Boolean:
        if ( find_arg (  key ) >= 0 ) {
            *( option->value.num ) = TRUE;
            option->source         = CONFIG_CMDLINE;
        }
        else {
            g_free ( key );
            key = g_strdup_printf ( "-no-%s", option->name );
            if ( find_arg (  key ) >= 0 ) {
                *( option->value.num ) = FALSE;
                option->source         = CONFIG_CMDLINE;
            }
        }
        break;
    case xrm_Char:
        if ( find_arg_char (  key, option->value.charc ) == TRUE ) {
            option->source = CONFIG_CMDLINE;
        }
        break;
    default:
        break;
    }
    g_free ( key );
}

void config_parse_cmd_options ( void )
{
    for ( unsigned int i = 0; i < sizeof ( xrmOptions ) / sizeof ( XrmOption ); ++i ) {
        XrmOption *op = &( xrmOptions[i] );
        config_parse_cmd_option ( op );
    }
}

void config_parse_cmd_options_dynamic ( void )
{
    for ( unsigned int i = 0; i < num_extra_options; ++i ) {
        XrmOption *op = &( extra_options[i] );
        config_parse_cmd_option ( op  );
    }
}

static void __config_parse_xresource_options_dynamic ( xcb_xrm_database_t *xDB, enum ConfigSource source )
{
    const char * namePrefix = "rofi";

    for ( unsigned int i = 0; i < num_extra_options; ++i ) {
        char *name;

        name = g_strdup_printf ( "%s.%s", namePrefix, extra_options[i].name );
        char *xrmValue = NULL;
        if ( xcb_xrm_resource_get_string ( xDB, name, NULL, &xrmValue ) == 0 ) {
            config_parser_set ( &( extra_options[i] ), xrmValue, source );
        }
        if ( xrmValue ) {
            free ( xrmValue );
        }

        g_free ( name );
    }
}

void config_parse_xresource_options_dynamic ( xcb_stuff *xcb )
{
    char *name = window_get_text_prop ( xcb_stuff_get_root_window ( xcb ), XCB_ATOM_RESOURCE_MANAGER );
    if ( name ) {
        xcb_xrm_database_t *xDB = xcb_xrm_database_from_string ( name );
        __config_parse_xresource_options_dynamic ( xDB, CONFIG_XRESOURCES );
        xcb_xrm_database_free ( xDB );
        g_free ( name );
    }
}
void config_parse_xresource_options_dynamic_file ( const char *filename )
{
    if ( !filename ) {
        return;
    }
    // Map Xresource entries to rofi config options.
    xcb_xrm_database_t *xDB = xcb_xrm_database_from_file ( filename );
    if ( xDB == NULL ) {
        return;
    }
    __config_parse_xresource_options_dynamic ( xDB, CONFIG_FILE );
    xcb_xrm_database_free ( xDB );
}

void config_xresource_free ( void )
{
    for ( unsigned int i = 0; i < ( sizeof ( xrmOptions ) / sizeof ( *xrmOptions ) ); ++i ) {
        if ( xrmOptions[i].mem != NULL ) {
            g_free ( xrmOptions[i].mem );
            xrmOptions[i].mem = NULL;
        }
    }
    for ( unsigned int i = 0; i < num_extra_options; ++i ) {
        if ( extra_options[i].mem != NULL ) {
            g_free ( extra_options[i].mem );
            extra_options[i].mem = NULL;
        }
    }
    if ( extra_options != NULL ) {
        g_free ( extra_options );
    }
}

static void xresource_dump_entry ( const char *namePrefix, XrmOption *option )
{
    printf ( "! \"%s\" ", option->comment );
    printf ( "Set from: %s\n", ConfigSourceStr[option->source] );
    if ( option->source == CONFIG_DEFAULT ) {
        printf ( "! " );
    }
    printf ( "%s.%s: %*s", namePrefix, option->name,
             (int) ( 30 - strlen ( option->name ) ), "" );
    switch ( option->type )
    {
    case xrm_Number:
        printf ( "%u", *( option->value.num ) );
        break;
    case xrm_SNumber:
        printf ( "%i", *( option->value.snum ) );
        break;
    case xrm_String:
        if ( ( *( option->value.str ) ) != NULL ) {
            printf ( "%s", *( option->value.str ) );
        }
        break;
    case xrm_Boolean:
        printf ( "%s", ( *( option->value.num ) == TRUE ) ? "true" : "false" );
        break;
    case xrm_Char:
        if ( *( option->value.charc ) > 32 && *( option->value.charc ) < 127 ) {
            printf ( "%c", *( option->value.charc ) );
        }
        else {
            printf ( "\\x%02X", *( option->value.charc ) );
        }
        break;
    default:
        break;
    }
    printf ( "\n" );
}

void config_parse_xresource_dump ( void )
{
    const char   * namePrefix = "rofi";
    unsigned int entries      = sizeof ( xrmOptions ) / sizeof ( *xrmOptions );
    for ( unsigned int i = 0; i < entries; ++i ) {
        // Skip duplicates.
        if ( ( i + 1 ) < entries ) {
            if ( xrmOptions[i].value.str == xrmOptions[i + 1].value.str ) {
                continue;
            }
        }
        xresource_dump_entry ( namePrefix, &( xrmOptions[i] ) );
    }
    for ( unsigned int i = 0; i < num_extra_options; i++ ) {
        xresource_dump_entry ( namePrefix, &( extra_options[i] ) );
    }
}

static void print_option_string ( XrmOption *xo, int is_term )
{
    int l = strlen ( xo->name );
    if ( is_term ) {
        printf ( "\t"color_bold "-%s"color_reset " [string]%-*c%s\n", xo->name, 30 - l, ' ', xo->comment );
        printf ( "\t"color_italic "%s"color_reset, ( *( xo->value.str ) == NULL ) ? "(unset)" : ( *( xo->value.str ) ) );
        printf ( " "color_green "(%s)"color_reset "\n", ConfigSourceStr[xo->source] );
    }
    else {
        printf ( "\t-%s [string]%-*c%s\n", xo->name, 30 - l, ' ', xo->comment );
        printf ( "\t\t%s", ( *( xo->value.str ) == NULL ) ? "(unset)" : ( *( xo->value.str ) ) );
        printf ( " (%s)\n", ConfigSourceStr[xo->source] );
    }
}
static void print_option_number ( XrmOption *xo, int is_term )
{
    int l = strlen ( xo->name );
    if ( is_term ) {
        printf ( "\t"color_bold "-%s"color_reset " [number]%-*c%s\n", xo->name, 30 - l, ' ', xo->comment );
        printf ( "\t"color_italic "%u"color_reset, *( xo->value.num ) );
        printf ( " "color_green "(%s)"color_reset "\n", ConfigSourceStr[xo->source] );
    }
    else {
        printf ( "\t-%s [number]%-*c%s\n", xo->name, 30 - l, ' ', xo->comment );
        printf ( "\t\t%u", *( xo->value.num ) );
        printf ( " (%s)\n", ConfigSourceStr[xo->source] );
    }
}
static void print_option_snumber ( XrmOption *xo, int is_term )
{
    int l = strlen ( xo->name );
    if ( is_term ) {
        printf ( "\t"color_bold "-%s"color_reset " [number]%-*c%s\n", xo->name, 30 - l, ' ', xo->comment );
        printf ( "\t"color_italic "%d"color_reset, *( xo->value.snum ) );
        printf ( " "color_green "(%s)"color_reset "\n", ConfigSourceStr[xo->source] );
    }
    else {
        printf ( "\t-%s [number]%-*c%s\n", xo->name, 30 - l, ' ', xo->comment );
        printf ( "\t\t%d", *( xo->value.snum ) );
        printf ( " (%s)\n", ConfigSourceStr[xo->source] );
    }
}
static void print_option_char ( XrmOption *xo, int is_term )
{
    int l = strlen ( xo->name );
    if ( is_term ) {
        printf ( "\t"color_bold "-%s"color_reset " [character]%-*c%s\n", xo->name, 30 - l, ' ', xo->comment );
        printf ( "\t"color_italic "%c"color_reset, *( xo->value.charc ) );
        printf ( " "color_green "(%s)"color_reset "\n", ConfigSourceStr[xo->source] );
    }
    else {
        printf ( "\t-%s [character]%-*c%s\n", xo->name, 30 - l, ' ', xo->comment );
        printf ( "\t\t%c", *( xo->value.charc ) );
        printf ( " (%s)\n", ConfigSourceStr[xo->source] );
    }
}
static void print_option_boolean ( XrmOption *xo, int is_term )
{
    int l = strlen ( xo->name );
    if ( is_term ) {
        printf ( "\t"color_bold "-[no-]%s"color_reset " %-*c%s\n", xo->name, 33 - l, ' ', xo->comment );
        printf ( "\t"color_italic "%s"color_reset, ( *( xo->value.snum ) ) ? "True" : "False" );
        printf ( " "color_green "(%s)"color_reset "\n", ConfigSourceStr[xo->source] );
    }
    else {
        printf ( "\t-[no-]%s %-*c%s\n", xo->name, 33 - l, ' ', xo->comment );
        printf ( "\t\t%s", ( *( xo->value.snum ) ) ? "True" : "False" );
        printf ( " (%s)\n", ConfigSourceStr[xo->source] );
    }
}

static void print_option ( XrmOption *xo, int is_term )
{
    switch ( xo->type )
    {
    case xrm_String:
        print_option_string ( xo, is_term );
        break;
    case xrm_Number:
        print_option_number ( xo, is_term );
        break;
    case xrm_SNumber:
        print_option_snumber ( xo, is_term );
        break;
    case xrm_Boolean:
        print_option_boolean ( xo, is_term );
        break;
    case xrm_Char:
        print_option_char ( xo, is_term );
        break;
    default:
        break;
    }
}
void print_options ( void )
{
    // Check output filedescriptor
    int          is_term = isatty ( fileno ( stdout ) );
    unsigned int entries = sizeof ( xrmOptions ) / sizeof ( *xrmOptions );
    for ( unsigned int i = 0; i < entries; ++i ) {
        if ( ( i + 1 ) < entries ) {
            if ( xrmOptions[i].value.str == xrmOptions[i + 1].value.str ) {
                continue;
            }
        }
        print_option ( &xrmOptions[i], is_term );
    }
    for ( unsigned int i = 0; i < num_extra_options; i++ ) {
        print_option ( &extra_options[i], is_term );
    }
}

void print_help_msg ( const char *option, const char *type, const char*text, const char *def, int isatty )
{
    int l = 37 - strlen ( option ) - strlen ( type );
    if ( isatty ) {
        printf ( "\t%s%s%s %s %-*c%s\n", color_bold, option, color_reset, type, l, ' ', text );
        if ( def != NULL ) {
            printf ( "\t\t%s%s%s\n", color_italic, def, color_reset );
        }
    }
    else{
        printf ( "\t%s %s %-*c%s\n", option, type, l, ' ', text );
        if ( def != NULL ) {
            printf ( "\t\t%s\n", def );
        }
    }
}

void config_parse_xresources_theme_dump ( void )
{
    printf ( "! ------------------------------------------------------------------------------\n" );
    printf ( "! ROFI Color theme\n" );
    printf ( "! User: %s\n", g_get_user_name () );
    printf ( "! ------------------------------------------------------------------------------\n" );
    const char   * const namePrefix       = "rofi";
    const char           colorPrefix[]    = "color-";
    const char           separatorStyle[] = "separator-style";
    unsigned int         entries          = sizeof ( xrmOptions ) / sizeof ( *xrmOptions );
    for ( unsigned int i = 0; i < entries; ++i ) {
        if ( strncmp ( xrmOptions[i].name, colorPrefix, sizeof ( colorPrefix ) - 1 ) == 0 ) {
            xresource_dump_entry ( namePrefix, &xrmOptions[i] );
        }
        else if ( strcmp ( xrmOptions[i].name, separatorStyle ) == 0 ) {
            xresource_dump_entry ( namePrefix, &xrmOptions[i] );
        }
    }
}

static char * config_parser_return_display_help_entry ( XrmOption *option )
{
    switch ( option->type )
    {
    case xrm_Number:
        return g_markup_printf_escaped ( "<b%s</b> (%u) <span style='italic' size='small'>%s</span>",
                                         option->name, *( option->value.num ), option->comment );
    case xrm_SNumber:
        return g_markup_printf_escaped ( "<b%s</b> (%d) <span style='italic' size='small'>%s</span>",
                                         option->name, *( option->value.snum ), option->comment );
    case xrm_String:
        return g_markup_printf_escaped ( "<b>%s</b> (%s) <span style='italic' size='small'>%s</span>",
                                         option->name,
                                         ( *( option->value.str ) != NULL ) ? *( option->value.str ) : "null",
                                         option->comment
                                         );
    case xrm_Boolean:
        return g_markup_printf_escaped ( "<b>%s</b> (%s) <span style='italic' size='small'>%s</span>",
                                         option->name, ( *( option->value.num ) == TRUE ) ? "true" : "false", option->comment );
    case xrm_Char:
        if ( *( option->value.charc ) > 32 && *( option->value.charc ) < 127 ) {
            return g_markup_printf_escaped ( "<b>%s</b> (%c) <span style='italic' size='small'>%s</span>",
                                             option->name, *( option->value.charc ), option->comment );
        }
        else {
            return g_markup_printf_escaped ( "<b%s</b> (\\x%02X) <span style='italic' size='small'>%s</span>",
                                             option->name, *( option->value.charc ), option->comment );
        }
    default:
        break;
    }

    return g_strdup ( "failed" );
}

char ** config_parser_return_display_help ( unsigned int *length )
{
    unsigned int entries = sizeof ( xrmOptions ) / sizeof ( *xrmOptions );
    char         **retv  = NULL;
    for ( unsigned int i = 0; i < entries; ++i ) {
        if ( ( i + 1 ) < entries ) {
            if ( xrmOptions[i].value.str == xrmOptions[i + 1].value.str ) {
                continue;
            }
        }
        if ( strncmp ( xrmOptions[i].name, "kb", 2 ) != 0 ) {
            continue;
        }

        retv = g_realloc ( retv, ( ( *length ) + 2 ) * sizeof ( char* ) );

        retv[( *length )] = config_parser_return_display_help_entry ( &xrmOptions[i] );
        ( *length )++;
    }
    for ( unsigned int i = 0; i < num_extra_options; i++ ) {
        if ( strncmp ( extra_options[i].name, "kb", 2 ) != 0 ) {
            continue;
        }
        retv              = g_realloc ( retv, ( ( *length ) + 2 ) * sizeof ( char* ) );
        retv[( *length )] = config_parser_return_display_help_entry ( &extra_options[i] );
        ( *length )++;
    }
    if ( ( *length ) > 0 ) {
        retv[( *length )] = NULL;
    }
    return retv;
}
