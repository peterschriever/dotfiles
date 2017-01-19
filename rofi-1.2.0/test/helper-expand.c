#include <assert.h>
#include <locale.h>
#include <glib.h>
#include <stdio.h>
#include <helper.h>
#include <string.h>
#include <xcb/xcb_ewmh.h>
#include "xcb-internal.h"
#include "rofi.h"
#include "settings.h"

static int       test = 0;
struct xcb_stuff *xcb;

#define TASSERT( a )        {                            \
        assert ( a );                                    \
        printf ( "Test %i passed (%s)\n", ++test, # a ); \
}
#define TASSERTE( a, b )    {                                                            \
        if ( ( a ) == ( b ) ) {                                                          \
            printf ( "Test %i passed (%s == %s) (%u == %u)\n", ++test, # a, # b, a, b ); \
        }else {                                                                          \
            printf ( "Test %i failed (%s == %s) (%u != %u)\n", ++test, # a, # b, a, b ); \
            abort ( );                                                                   \
        }                                                                                \
}

int rofi_view_error_dialog ( const char *msg, G_GNUC_UNUSED int markup )
{
    fputs ( msg, stderr );
    return TRUE;
}

int show_error_message ( const char *msg, int markup )
{
    rofi_view_error_dialog ( msg, markup );
    return 0;
}
xcb_screen_t          *xcb_screen;
xcb_ewmh_connection_t xcb_ewmh;
int                   xcb_screen_nbr;
#include <x11-helper.h>

int main ( int argc, char ** argv )
{
    cmd_set_arguments ( argc, argv );

    if ( setlocale ( LC_ALL, "" ) == NULL ) {
        fprintf ( stderr, "Failed to set locale.\n" );
        return EXIT_FAILURE;
    }

    /**
     * Test some path functions. Not easy as not sure what is right output on travis.
     */
    // Test if root is preserved.
    char *str = rofi_expand_path ( "/" );
    TASSERT ( strcmp ( str, "/" ) == 0 );
    g_free ( str );
    // Test is relative path is preserved.
    str = rofi_expand_path ( "../AUTHORS" );
    TASSERT ( strcmp ( str, "../AUTHORS" ) == 0 );
    g_free ( str );
    // Test another one.
    str = rofi_expand_path ( "/bin/false" );
    TASSERT ( strcmp ( str, "/bin/false" ) == 0 );
    g_free ( str );
    // See if user paths get expanded in full path.
    str = rofi_expand_path ( "~/" );
    const char *hd = g_get_home_dir ();
    TASSERT ( strcmp ( str, hd ) == 0 );
    g_free ( str );
    str = rofi_expand_path ( "~root/" );
    TASSERT ( str[0] == '/' );
    g_free ( str );
}
