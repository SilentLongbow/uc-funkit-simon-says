/* Author: Matthew Kenny(ID: 11031880)
 *
 * Description: Handles all actions regarding displaying messages
 *              to the LED matrix.
 */

#include <string.h>
#include "system.h"
#include "pio.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font5x7_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10


static const uint8_t up_arrow[] = {
    0x04, 0x02, 0xff, 0x02, 0x04
};

static const uint8_t down_arrow[] = {
    0x10, 0x20, 0xff, 0x20, 0x10
};

static const uint8_t left_arrow[] = {
    0x08, 0x1c,0x2a,0x08, 0x08
};

static const uint8_t right_arrow[]= {
    0x08, 0x08, 0x2a, 0x1c, 0x08
};

/** Compares the message and the buffer and returns the length of the shorter two */
int evaluate_lengths(char message[], char buffer[])
{
    int buffer_length = strlen(buffer);
    int message_length = strlen(message);
    if (buffer_length <= message_length) {
        return buffer_length;
    } else {
        return message_length;
    }
}

/** Displays a single message of at most 10 characters, once */
void display_scrolling_message(const char message[])
{
    pacer_init(500);
    int message_tick = 0;
    char buffer[11] = "";
    strncpy(buffer, message, 10);
    buffer[10] = '\0';
    int message_length = strlen(buffer);
    double duration = (1 / (MESSAGE_RATE / 10.0)) * (message_length + (0.2 * message_length));   // Get how many seconds are needed to display message
    int tick_target = duration * PACER_RATE;    // Multiply by pacer frequency to get number of ticks needed
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(buffer);
    while (message_tick < tick_target) {
        pacer_wait();
        tinygl_update();
        message_tick++;
    }
    tinygl_clear();
}

/** Displays a given character for 3 seconds */
void display_character(const char character)
{
    int char_tick = 0;
    char buffer[2] = {character, '\0'};
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    tinygl_text(buffer);
    while (char_tick < 1500) { // Display character for 3 seconds
        pacer_wait();
        tinygl_update();
        char_tick++;
    }
    tinygl_clear();
}

void message_display_init(const pio_t rows[], const pio_t cols[])
{
    //LED matrix initialiser
    int i;
    for (i = 0; i < 7; i++) {
        pio_config_set(rows[i], PIO_OUTPUT_HIGH);
    }
    for (i = 0; i < 5; i++) {
        pio_config_set(cols[i], PIO_OUTPUT_HIGH);
    }
    // Initialise the tinygl system
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
}
