/* Author: Siyuan WEI(ID:22883373)
 *
 * describle: record players motion
 */




#include <stdio.h>
#include "system.h"
#include "navswitch.h"

/* record players motion as character
 * return 0 if do nothing
 * return N,E,S,W corresponding direction
 * return p if push button
 */
char nav_motion(void)
{
    char player_motion = 0;
    navswitch_update();

    // save motion as char
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        player_motion = 'N';
    }
    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        player_motion = 'E';
    }
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        player_motion = 'S';
    }
    if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        player_motion = 'W';
    }
    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
        player_motion = 'P';
    }

    return player_motion;
}

























