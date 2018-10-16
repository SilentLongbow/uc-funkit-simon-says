#include "system.h"
#include "displayMessage.h"
#include <string.h>
#include "led.h"
#include "pacer.h"
#include "nav_motion.h"

/** Message creation at the start of a round, returns the message */
char* create_initial_message(char message[])
{
    message[6] = '\0';
    //display_scrolling_message("ENTER MESSAGE");
    led_set(LED1, 1);
    char input = 0;
    int index = 0;
    while (input != 'P') {
        pacer_wait();
        input = nav_motion();
        if (input != 0 && index <= 5) {
            message[index] = input;
            display_arrow_still(message[index]);
            index++;
        } else if (input != 0 && input != 'P' && index == 6) {
            display_character('X');
        }
    }
    message[6] = '\0';
    display_scrolling_message("DONE");
    return message;
}

/** Response message creation on the receiver's side */
char* create_response_message(char message[11])
{
    message[10] = '\0';
    return message;
}

