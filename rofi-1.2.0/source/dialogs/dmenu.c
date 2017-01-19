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
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>
#include "rofi.h"
#include "settings.h"
#include "textbox.h"
#include "dialogs/dmenu.h"
#include "helper.h"
#include "xrmoptions.h"
#include "view.h"
// We limit at 1000000 rows for now.
#define DMENU_MAX_ROWS    1000000

struct range_pair
{
    unsigned int start;
    unsigned int stop;
};

static inline unsigned int bitget ( uint32_t *array, unsigned int index )
{
    uint32_t bit = index % 32;
    uint32_t val = array[index / 32];
    return ( val >> bit ) & 1;
}

static inline void bittoggle ( uint32_t *array, unsigned int index )
{
    uint32_t bit = index % 32;
    uint32_t *v  = &array[index / 32];
    *v ^= 1 << bit;
}

typedef struct
{
    /** Settings */
    // Prompt
    char              *prompt;
    // Separator.
    char              separator;

    unsigned int      selected_line;
    char              *message;
    char              *format;
    struct range_pair * urgent_list;
    unsigned int      num_urgent_list;
    struct range_pair * active_list;
    unsigned int      num_active_list;
    uint32_t          *selected_list;
    unsigned int      num_selected_list;
    unsigned int      do_markup;
    // List with entries.
    char              **cmd_list;
    unsigned int      cmd_list_length;
    unsigned int      only_selected;
    unsigned int      selected_count;

    gchar             **columns;
    gchar             *column_separator;
    gboolean          multi_select;
} DmenuModePrivateData;

static char **get_dmenu ( DmenuModePrivateData *pd, FILE *fd, unsigned int *length )
{
    TICK_N ( "Read stdin START" );
    char         **retv   = NULL;
    unsigned int rvlength = 1;

    *length = 0;
    gchar   *data  = NULL;
    size_t  data_l = 0;
    ssize_t l      = 0;
    while ( ( l = getdelim ( &data, &data_l, pd->separator, fd ) ) > 0 ) {
        if ( rvlength < ( *length + 2 ) ) {
            rvlength *= 2;
            retv      = g_realloc ( retv, ( rvlength ) * sizeof ( char* ) );
        }
        if ( data[l - 1] == pd->separator ) {
            data[l - 1] = '\0';
            l--;
        }
        char *utfstr = rofi_force_utf8 ( data, l );

        retv[( *length )] = utfstr;

        ( *length )++;
        // Stop when we hit 2³¹ entries.
        if ( ( *length ) >= DMENU_MAX_ROWS ) {
            break;
        }
    }
    if ( data != NULL ) {
        free ( data );
        data = NULL;
    }
    if ( retv != NULL ) {
        retv               = g_realloc ( retv, ( *length + 1 ) * sizeof ( char* ) );
        retv[( *length ) ] = NULL;
    }
    TICK_N ( "Read stdin STOP" );
    return retv;
}

static unsigned int dmenu_mode_get_num_entries ( const Mode *sw )
{
    const DmenuModePrivateData *rmpd = (const DmenuModePrivateData *) mode_get_private_data ( sw );
    return rmpd->cmd_list_length;
}

static void parse_pair ( char  *input, struct range_pair  *item )
{
    int                index = 0;
    const char * const sep   = "-";
    for ( char *token = strsep ( &input, sep ); token != NULL; token = strsep ( &input, sep ) ) {
        if ( index == 0 ) {
            item->start = item->stop = (unsigned int) strtoul ( token, NULL, 10 );
            index++;
        }
        else {
            if ( token[0] == '\0' ) {
                item->stop = 0xFFFFFFFF;
            }
            else{
                item->stop = (unsigned int) strtoul ( token, NULL, 10 );
            }
        }
    }
}

static void parse_ranges ( char *input, struct range_pair **list, unsigned int *length )
{
    char *endp;
    if ( input == NULL ) {
        return;
    }
    const char *const sep = ",";
    for ( char *token = strtok_r ( input, sep, &endp ); token != NULL; token = strtok_r ( NULL, sep, &endp ) ) {
        // Make space.
        *list = g_realloc ( ( *list ), ( ( *length ) + 1 ) * sizeof ( struct range_pair ) );
        // Parse a single pair.
        parse_pair ( token, &( ( *list )[*length] ) );

        ( *length )++;
    }
}

static gchar * dmenu_format_output_string ( const DmenuModePrivateData *pd, const char *input )
{
    if ( pd->columns == NULL ) {
        return g_strdup ( input );
    }
    char     *retv       = NULL;
    char     ** splitted = g_regex_split_simple ( pd->column_separator, input, G_REGEX_CASELESS, 00 );
    uint32_t ns          = 0;
    for (; splitted && splitted[ns]; ns++ ) {
        ;
    }
    for ( uint32_t i = 0; pd->columns && pd->columns[i]; i++ ) {
        unsigned int index = (unsigned int ) g_ascii_strtoull ( pd->columns[i], NULL, 10 );
        if ( index < ns && index > 0 ) {
            if ( retv == NULL ) {
                retv = g_strdup ( splitted[index - 1] );
            }
            else {
                gchar *t = g_strjoin ( "\t", retv, splitted[index - 1], NULL );
                g_free ( retv );
                retv = t;
            }
        }
    }
    g_strfreev ( splitted );
    return retv ? retv : g_strdup ( "" );
}

static char *get_display_data ( const Mode *data, unsigned int index, int *state, int get_entry )
{
    Mode                 *sw    = (Mode *) data;
    DmenuModePrivateData *pd    = (DmenuModePrivateData *) mode_get_private_data ( sw );
    char                 **retv = (char * *) pd->cmd_list;
    for ( unsigned int i = 0; i < pd->num_active_list; i++ ) {
        if ( index >= pd->active_list[i].start && index <= pd->active_list[i].stop ) {
            *state |= ACTIVE;
        }
    }
    for ( unsigned int i = 0; i < pd->num_urgent_list; i++ ) {
        if ( index >= pd->urgent_list[i].start && index <= pd->urgent_list[i].stop ) {
            *state |= URGENT;
        }
    }
    if ( pd->selected_list && bitget ( pd->selected_list, index ) == TRUE ) {
        *state |= SELECTED;
    }
    if ( pd->do_markup ) {
        *state |= MARKUP;
    }
    return get_entry ? dmenu_format_output_string ( pd, retv[index] ) : NULL;
}

/**
 * @param format The format string used. See below for possible syntax.
 * @param string The selected entry.
 * @param selected_line The selected line index.
 * @param filter The entered filter.
 *
 * Function that outputs the selected line in the user-specified format.
 * Currently the following formats are supported:
 *   * i: Print the index (0-(N-1))
 *   * d: Print the index (1-N)
 *   * s: Print input string.
 *   * q: Print quoted input string.
 *   * f: Print the entered filter.
 *   * F: Print the entered filter, quoted
 *
 * This functions outputs the formatted string to stdout, appends a newline (\n) character and
 * calls flush on the file descriptor.
 */
static void dmenu_output_formatted_line ( const char *format, const char *string, int selected_line,
                                          const char *filter )
{
    for ( int i = 0; format && format[i]; i++ ) {
        if ( format[i] == 'i' ) {
            fprintf ( stdout, "%d", selected_line );
        }
        else if ( format[i] == 'd' ) {
            fprintf ( stdout, "%d", ( selected_line + 1 ) );
        }
        else if ( format[i] == 's' ) {
            fputs ( string, stdout );
        }
        else if ( format[i] == 'q' ) {
            char *quote = g_shell_quote ( string );
            fputs ( quote, stdout );
            g_free ( quote );
        }
        else if ( format[i] == 'f' ) {
            fputs ( filter, stdout );
        }
        else if ( format[i] == 'F' ) {
            char *quote = g_shell_quote ( filter );
            fputs ( quote, stdout );
            g_free ( quote );
        }
        else {
            fputc ( format[i], stdout );
        }
    }
    fputc ( '\n', stdout );
    fflush ( stdout );
}
static void dmenu_mode_free ( Mode *sw )
{
    if ( mode_get_private_data ( sw ) == NULL ) {
        return;
    }
    DmenuModePrivateData *pd = (DmenuModePrivateData *) mode_get_private_data ( sw );
    if ( pd != NULL ) {
        for ( size_t i = 0; i < pd->cmd_list_length; i++ ) {
            if ( pd->cmd_list[i] ) {
                free ( pd->cmd_list[i] );
            }
        }
        g_free ( pd->cmd_list );
        g_free ( pd->urgent_list );
        g_free ( pd->active_list );
        g_free ( pd->selected_list );

        g_free ( pd );
        mode_set_private_data ( sw, NULL );
    }
}

static int dmenu_mode_init ( Mode *sw )
{
    if ( mode_get_private_data ( sw ) != NULL ) {
        return TRUE;
    }
    mode_set_private_data ( sw, g_malloc0 ( sizeof ( DmenuModePrivateData ) ) );
    DmenuModePrivateData *pd = (DmenuModePrivateData *) mode_get_private_data ( sw );

    pd->prompt        = "dmenu ";
    pd->separator     = '\n';
    pd->selected_line = UINT32_MAX;

    find_arg_str ( "-mesg", &( pd->message ) );

    // Input data separator.
    find_arg_char ( "-sep", &( pd->separator ) );

    // Check prompt
    find_arg_str (  "-p", &( pd->prompt ) );
    find_arg_uint (  "-selected-row", &( pd->selected_line ) );
    // By default we print the unescaped line back.
    pd->format = "s";

    // Allow user to override the output format.
    find_arg_str ( "-format", &( pd->format ) );
    // Urgent.
    char *str = NULL;
    find_arg_str (  "-u", &str );
    if ( str != NULL ) {
        parse_ranges ( str, &( pd->urgent_list ), &( pd->num_urgent_list ) );
    }
    // Active
    str = NULL;
    find_arg_str (  "-a", &str );
    if ( str != NULL ) {
        parse_ranges ( str, &( pd->active_list ), &( pd->num_active_list ) );
    }

    // DMENU COMPATIBILITY
    find_arg_uint (  "-l", &( config.menu_lines ) );

    /**
     * Dmenu compatibility.
     * `-b` put on bottom.
     */
    if ( find_arg ( "-b" ) >= 0 ) {
        config.location = 6;
    }
    /* -i case insensitive */
    config.case_sensitive = TRUE;
    if ( find_arg ( "-i" ) >= 0 ) {
        config.case_sensitive = FALSE;
    }
    FILE *fd = NULL;
    str = NULL;
    if ( find_arg_str ( "-input", &str ) ) {
        char *estr = rofi_expand_path ( str );
        fd = fopen ( str, "r" );
        if ( fd == NULL ) {
            char *msg = g_markup_printf_escaped ( "Failed to open file: <b>%s</b>:\n\t<i>%s</i>", estr, strerror ( errno ) );
            rofi_view_error_dialog ( msg, TRUE );
            g_free ( msg );
            g_free ( estr );
            return TRUE;
        }
        g_free ( estr );
    }
    pd->cmd_list = get_dmenu ( pd, fd == NULL ? stdin : fd, &( pd->cmd_list_length ) );
    if ( fd != NULL ) {
        fclose ( fd );
    }

    gchar *columns = NULL;
    if ( find_arg_str ( "-display-columns", &columns ) ) {
        pd->columns          = g_strsplit ( columns, ",", 0 );
        pd->column_separator = "\t";
        find_arg_str ( "-display-column-separator", &pd->column_separator );
    }
    return TRUE;
}

static int dmenu_token_match ( const Mode *sw, GRegex **tokens, unsigned int index )
{
    DmenuModePrivateData *rmpd = (DmenuModePrivateData *) mode_get_private_data ( sw );
    return token_match ( tokens, rmpd->cmd_list[index] );
}

#include "mode-private.h"
Mode dmenu_mode =
{
    .name               = "dmenu",
    .cfg_name_key       = "display-combi",
    ._init              = dmenu_mode_init,
    ._get_num_entries   = dmenu_mode_get_num_entries,
    ._result            = NULL,
    ._destroy           = dmenu_mode_free,
    ._token_match       = dmenu_token_match,
    ._get_display_value = get_display_data,
    ._get_completion    = NULL,
    ._preprocess_input  = NULL,
    .private_data       = NULL,
    .free               = NULL
};

static void dmenu_finish ( RofiViewState *state, int retv )
{
    if ( retv == FALSE ) {
        rofi_set_return_code ( EXIT_FAILURE );
    }
    else if ( retv >= 10 ) {
        rofi_set_return_code ( retv );
    }
    else{
        rofi_set_return_code ( EXIT_SUCCESS );
    }
    rofi_view_set_active ( NULL );
    rofi_view_free ( state );
    mode_destroy ( &dmenu_mode );
}

static void dmenu_print_results ( DmenuModePrivateData *pd, const char *input )
{
    char **cmd_list = pd->cmd_list;
    int  seen       = FALSE;
    if ( pd->selected_list != NULL ) {
        for ( unsigned int st = 0; st < pd->cmd_list_length; st++ ) {
            if ( bitget ( pd->selected_list, st ) ) {
                seen = TRUE;
                dmenu_output_formatted_line ( pd->format, cmd_list[st], st, input );
            }
        }
    }
    if ( !seen ) {
        const char *cmd = input;
        if ( pd->selected_line != UINT32_MAX ) {
            cmd = cmd_list[pd->selected_line];
        }
        dmenu_output_formatted_line ( pd->format, cmd, pd->selected_line, input );
    }
}

static void dmenu_finalize ( RofiViewState *state )
{
    int                  retv            = FALSE;
    DmenuModePrivateData *pd             = (DmenuModePrivateData *) rofi_view_get_mode ( state )->private_data;
    unsigned int         cmd_list_length = pd->cmd_list_length;
    char                 **cmd_list      = pd->cmd_list;

    char                 *input = g_strdup ( rofi_view_get_user_input ( state ) );
    pd->selected_line = rofi_view_get_selected_line ( state );;
    MenuReturn           mretv    = rofi_view_get_return_value ( state );
    unsigned int         next_pos = rofi_view_get_next_position ( state );
    int                  restart  = 0;
    // Special behavior.
    if ( pd->only_selected ) {
        /**
         * Select item mode.
         */
        restart = 1;
        // Skip if no valid item is selected.
        if ( ( mretv & MENU_CANCEL ) == MENU_CANCEL ) {
            // In no custom mode we allow canceling.
            restart = ( find_arg ( "-only-match" ) >= 0 );
        }
        else if ( pd->selected_line != UINT32_MAX ) {
            if ( ( mretv & ( MENU_OK | MENU_QUICK_SWITCH ) ) && cmd_list[pd->selected_line] != NULL ) {
                dmenu_print_results ( pd, input );
                retv = TRUE;
                if ( ( mretv & MENU_QUICK_SWITCH ) ) {
                    retv = 10 + ( mretv & MENU_LOWER_MASK );
                }
                g_free ( input );
                dmenu_finish ( state, retv );
                return;
            }
            pd->selected_line = next_pos - 1;
        }
        // Restart
        rofi_view_restart ( state );
        rofi_view_set_selected_line ( state, pd->selected_line );
        if ( !restart ) {
            dmenu_finish ( state, retv );
        }
        return;
    }
    // We normally do not want to restart the loop.
    restart = FALSE;
    // Normal mode
    if ( ( mretv & MENU_OK  ) && pd->selected_line != UINT32_MAX && cmd_list[pd->selected_line] != NULL ) {
        if ( ( mretv & MENU_CUSTOM_ACTION ) && pd->multi_select ) {
            restart = TRUE;
            if ( pd->selected_list == NULL ) {
                pd->selected_list = g_malloc0 ( sizeof ( uint32_t ) * ( pd->cmd_list_length / 32 + 1 ) );
            }
            pd->selected_count += ( bitget ( pd->selected_list, pd->selected_line ) ? ( -1 ) : ( 1 ) );
            bittoggle ( pd->selected_list, pd->selected_line );
            // Move to next line.
            pd->selected_line = MIN ( next_pos, cmd_list_length - 1 );
            if ( pd->selected_count > 0 ) {
                char *str = g_strdup_printf ( "%u/%u", pd->selected_count, pd->cmd_list_length );
                rofi_view_set_overlay ( state, str );
                g_free ( str );
            }
            else {
                rofi_view_set_overlay ( state, NULL );
            }
        }
        else {
            dmenu_print_results ( pd, input );
        }
        retv = TRUE;
    }
    // Custom input
    else if ( ( mretv & ( MENU_CUSTOM_INPUT ) ) ) {
        dmenu_print_results ( pd, input );

        retv = TRUE;
    }
    // Quick switch with entry selected.
    else if ( ( mretv & MENU_QUICK_SWITCH ) ) {
        dmenu_print_results ( pd, input );

        restart = FALSE;
        retv    = 10 + ( mretv & MENU_LOWER_MASK );
    }
    g_free ( input );
    if ( restart ) {
        rofi_view_restart ( state );
        rofi_view_set_selected_line ( state, pd->selected_line );
    }
    else {
        dmenu_finish ( state, retv );
    }
}

int dmenu_switcher_dialog ( void )
{
    mode_init ( &dmenu_mode );
    MenuFlags            menu_flags      = MENU_NORMAL;
    DmenuModePrivateData *pd             = (DmenuModePrivateData *) dmenu_mode.private_data;
    char                 *input          = NULL;
    unsigned int         cmd_list_length = pd->cmd_list_length;
    char                 **cmd_list      = pd->cmd_list;

    pd->only_selected = FALSE;
    pd->multi_select  = FALSE;
    if ( find_arg ( "-multi-select" ) >= 0 ) {
        menu_flags       = MENU_INDICATOR;
        pd->multi_select = TRUE;
    }
    if ( find_arg ( "-markup-rows" ) >= 0 ) {
        pd->do_markup = TRUE;
    }
    if ( find_arg ( "-only-match" ) >= 0 || find_arg ( "-no-custom" ) >= 0 ) {
        pd->only_selected = TRUE;
        if ( cmd_list_length == 0 ) {
            return TRUE;
        }
    }
    if ( config.auto_select && cmd_list_length == 1 ) {
        dmenu_output_formatted_line ( pd->format, cmd_list[0], 0, config.filter );
        return TRUE;
    }
    if ( find_arg ( "-password" ) >= 0 ) {
        menu_flags |= MENU_PASSWORD;
    }
    /* copy filter string */
    input = g_strdup ( config.filter );

    char *select = NULL;
    find_arg_str ( "-select", &select );
    if ( select != NULL ) {
        GRegex       **tokens = tokenize ( select, config.case_sensitive );
        unsigned int i        = 0;
        for ( i = 0; i < cmd_list_length; i++ ) {
            if ( token_match ( tokens, cmd_list[i] ) ) {
                pd->selected_line = i;
                break;
            }
        }
        tokenize_free ( tokens );
    }
    if ( find_arg ( "-dump" ) >= 0 ) {
        GRegex       **tokens = tokenize ( config.filter ? config.filter : "", config.case_sensitive );
        unsigned int i        = 0;
        for ( i = 0; i < cmd_list_length; i++ ) {
            if ( token_match ( tokens, cmd_list[i] ) ) {
                dmenu_output_formatted_line ( pd->format, cmd_list[i], i, config.filter );
            }
        }
        tokenize_free ( tokens );
        dmenu_mode_free ( &dmenu_mode );
        g_free ( input );
        return TRUE;
    }
    // TODO remove
    RofiViewState *state = rofi_view_create ( &dmenu_mode, input, pd->prompt, pd->message, menu_flags, dmenu_finalize );
    rofi_view_set_selected_line ( state, pd->selected_line );
    rofi_view_set_active ( state );

    return FALSE;
}

void print_dmenu_options ( void )
{
    int is_term = isatty ( fileno ( stdout ) );
    print_help_msg ( "-mesg", "[string]", "Print a small user message under the prompt (uses pango markup)", NULL, is_term );
    print_help_msg ( "-p", "[string]", "Prompt to display left of entry field", NULL, is_term );
    print_help_msg ( "-selected-row", "[integer]", "Select row", NULL, is_term );
    print_help_msg ( "-format", "[string]", "Output format string", "s", is_term );
    print_help_msg ( "-u", "[list]", "List of row indexes to mark urgent", NULL, is_term );
    print_help_msg ( "-a", "[list]", "List of row indexes to mark active", NULL, is_term );
    print_help_msg ( "-l", "[integer] ", "Number of rows to display", NULL, is_term );
    print_help_msg ( "-i", "", "Set filter to be case insensitive", NULL, is_term );
    print_help_msg ( "-only-match", "", "Force selection or custom entry", NULL, is_term );
    print_help_msg ( "-no-custom", "", "Don't accept custom entry", NULL, is_term );
    print_help_msg ( "-select", "[string]", "Select the first row that matches", NULL, is_term );
    print_help_msg ( "-password", "", "Do not show what the user inputs. Show '*' instead.", NULL, is_term );
    print_help_msg ( "-markup-rows", "", "Allow and render pango markup as input data.", NULL, is_term );
    print_help_msg ( "-sep", "[char]", "Element separator.", "'\\n'", is_term );
    print_help_msg ( "-input", "[filename]", "Read input from file instead from standard input.", NULL, is_term );
}
