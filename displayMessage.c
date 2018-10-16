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

#define PACER_RATE 2000
#define MESSAGE_RATE 10

/** A struct of the arror end point corrdinates */
typedef struct arrow_s {
    int top[2];
    int bottom[2];
    int left_tip[2];
    int right_tip[2];
} Arrow;

/** Takes the input direction, creates a set of arrow corrdiantes and returns it */
Arrow parse_arrow(char direction) {
    Arrow arrow;
    switch(direction) {
        case 'N':
            arrow.top[0] = 7;
            arrow.top[1] = 0;
            arrow.bottom[0] = 7;
            arrow.bottom[1] = 6;
            arrow.left_tip[0] = 5;
            arrow.left_tip[1] = 2;
            arrow.right_tip[0] = 9;
            arrow.right_tip[1] = 2;
            return arrow;
        case 'S':
            arrow.top[0] = 7;
            arrow.top[1] = 6;
            arrow.bottom[0] = 7;
            arrow.bottom[1] = 0;
            arrow.left_tip[0] = 9;
            arrow.left_tip[1] = 4;
            arrow.right_tip[0] = 5;
            arrow.right_tip[1] = 4;
            return arrow;
        case 'W':
            arrow.top[0] = 5;
            arrow.top[1] = 3;
            arrow.bottom[0] = 9;
            arrow.bottom[1] = 3;
            arrow.left_tip[0] = 7;
            arrow.left_tip[1] = 5;
            arrow.right_tip[0] = 7;
            arrow.right_tip[1] = 1;
            return arrow;
        case 'E':
            arrow.top[0] = 9;
            arrow.top[1] = 3;
            arrow.bottom[0] = 5;
            arrow.bottom[1] = 3;
            arrow.left_tip[0] = 7;
            arrow.left_tip[1] = 1;
            arrow.right_tip[0] = 7;
            arrow.right_tip[1] = 5;
            return arrow;
    }
}

/** Function used to display the direction arrow from right to left */
void display_arrow(const char direction)
{
    Arrow arrow = parse_arrow(direction);
    int i = 0;
    int counter = 0;
    while (i <= 10) {
        pacer_wait ();
        tinygl_clear();
        tinygl_draw_line (tinygl_point (arrow.top[0] - i, arrow.top[1]), tinygl_point (arrow.bottom[0] - i, arrow.bottom[1]), 1);
        tinygl_draw_line (tinygl_point (arrow.left_tip[0] - i, arrow.left_tip[1]), tinygl_point (arrow.top[0] - i, arrow.top[1]), 1);
        tinygl_draw_line (tinygl_point (arrow.right_tip[0] - i, arrow.right_tip[1]), tinygl_point (arrow.top[0] - i, arrow.top[1]), 1);
        if (counter >= 200) {
            i += 1;
            counter = 0;
        }
        tinygl_update();
        counter++;
    }

}

/** Displays a single message of at most 10 characters, once */
void display_scrolling_message(const char message[])
{
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
    while (char_tick < 6000) { // Display character for 3 seconds
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
