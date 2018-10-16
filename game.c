/* Author: Siyuan WEI(ID: 022883373)
 *         Matthew Kenny(ID: 11031880)
 * Description: The main game file
 */


#include <stdio.h>
#include "system.h"
#include "displayMessage.h"
#include "create_message.h"
#include "pacer.h"
#include "led.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include <stdbool.h>
#include "../fonts/font5x7_1.h"

#define PACER_RATE 1000
#define MESSAGE_RATE 15
#define DISPLAY_COUNT 6000
#define MAX_FAIL_TIMES 3

/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] = {
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] = {
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

/** Initialise all of the required drivers */
void system_initialise(void)
{

    system_init();  // general system initialiser

    navswitch_init();   // navigational switch initialiser

    pacer_init(PACER_RATE); //timer initialiser

    ir_uart_init(); //IR initialiser

    // Initialise the tinygl system
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);

    //LED matrix initialiser
    message_display_init(rows, cols);

    led_init ();    //LED initialiser
}

/*dicide which player send message first
 * return mode(1 or 2) 1 for send, 2
 * for receive
 */
int start_screen(void)
{
    int text_state = 0;
    int player_mode = 0;
    int counter = 0;
    // keep display message before push nav_switch
    while(player_mode == 0) {
        //led_set(LED1, 1);

        if (counter >= DISPLAY_COUNT) {

            if (text_state == 0) {
                tinygl_text("    CHOOSE START MODE   \0");
            }
            if (text_state == 1) {
                tinygl_text(" N FOR SEND S FOR RECIEVE  \0");
            }

            text_state = !text_state;
            counter = 0;
        }

        pacer_wait();
        navswitch_update();
        tinygl_update();

        // push north to be first player(send message)
        if(navswitch_push_event_p(NAVSWITCH_NORTH)) {
            player_mode = 1;
        }
        if(navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            player_mode = 2;
        }
    }

    tinygl_clear();
    tinygl_update();
    return player_mode;
}


// display result of the game;
void finish_screen(bool my_fail, bool opponent_fail)
{
    if (my_fail == MAX_FAIL_TIMES) {
        tinygl_text(" YOU LOST   \0");
    }
    if (opponent_fail == MAX_FAIL_TIMES) {
        tinygl_text(" YOU WON   \0");
    }
    //DISPLAY FINISH MESSGAE
    while (1)
    {
        pacer_wait();
        tinygl_update();
    }
}



/** Turns on the blue LED when called */
void blue_led_on(void)
{
    led_set(LED1, 1);
}

/** Turns off the blue LED when called */
void  blue_led_off(void)
{
    led_set(LED1, 0);
}

// play the game
int main (void)
{
    system_initialise();
    blue_led_on();
    //display_character('X');
    //display_scrolling_message("MATTHEW");
    char message[7];
    create_initial_message(message);
    int i = 0;
    for (i; i < 6; i++) {
        display_arrow_scrolling(message[i]);
    }
    //display_arrow_still('S');

    //tinygl_draw_line(tinygl_point (2, 0), tinygl_point(2, 6), 1);
    //display_arrow_scrolling('N');
    //display_arrow_scrolling('E');
    //display_arrow_scrolling('S');
    //display_arrow_scrolling('W');
    while (1) {
        pacer_wait();
    }
    return 1;
}

