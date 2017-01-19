#include <glib.h>
#include "widget.h"

int widget_intersect ( const Widget *widget, int x, int y )
{
    if ( widget == NULL ) {
        return FALSE;
    }

    if ( x >= ( widget->x ) && x < ( widget->x + widget->w ) ) {
        if ( y >= ( widget->y ) && y < ( widget->y + widget->h ) ) {
            return TRUE;
        }
    }
    return FALSE;
}

void widget_move ( Widget *widget, short x, short y )
{
    if ( widget != NULL ) {
        widget->x = x;
        widget->y = y;
    }
}

gboolean widget_enabled ( Widget *widget )
{
    if ( widget != NULL ) {
        return widget->enabled;
    }
    return FALSE;
}

void widget_enable ( Widget *widget )
{
    if ( widget ) {
        widget->enabled = TRUE;
    }
}
void widget_disable ( Widget *widget )
{
    if ( widget ) {
        widget->enabled = FALSE;
    }
}
