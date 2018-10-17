/* Author: Siyuan WEI(ID: 022883373)
 *         Matthew Kenny(ID: 11031880)
 * Description: Creates the message to be sent.
 */

#include "system.h"
#include "displayMessage.h"
#include "pacer.h"
#include "nav_motion.h"

/** Message creation at the start of a round, returns the message */
void create_message(char message[])
{
    char input = 0;
    int index = 0;
    while (input != 'P') {
        pacer_wait();
        input = nav_motion();
        if (input != 0 && input != 'P' && index <= 5) {
            message[index] = input;
            display_arrow_still(message[index]);
            index++;
        } else if (input != 0 && input != 'P' && index == 6) {
            display_character('X');
        }
    }
    message[index] = '\0';
}
