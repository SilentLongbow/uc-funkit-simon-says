/* Author: Siyuan WEI(ID: 022883373)
 *         Matthew Kenny(ID: 11031880)
 * Description: The main game file
 */


#include <stdio.h>
#include "system.h"
#include "displayMessage.h"
#include "create_message.h"
#include "receive_message.h"
#include "send_message.h"
#include "pacer.h"
#include "led.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../fonts/font5x7_1.h"

#define PACER_RATE 1000
#define MESSAGE_RATE 15
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








/*dicide which player send message first
 * return mode(1 or 2) 1 for send, 2
 * for receive
 */
int start_screen(void)
{

    int player_mode = 0;
    int flag = 0;
    char character = 0;
    // keep display message before push nav_switch
    while(flag != 1) {
        blue_led_on();
        pacer_wait();
        navswitch_update();
        // push to be first player(send message)
        if (ir_uart_read_ready_p()) {
            character = ir_uart_getc();
            if (character == 'P') {
                player_mode = 2; // receive
                blue_led_off();
                flag = 1;
            }
        }
        if(navswitch_push_event_p(NAVSWITCH_PUSH)) {
            player_mode = 1; // first player
            ir_uart_putc('P');
            blue_led_off();
            flag = 1;
        }
    }
    return player_mode;

}

void post_round(int role, int result, int* my_score, int* opponent_score)
{
    blue_led_on();
    if (result == 1) {
        if (role == 1) {
            display_character('X');
            *opponent_score += 1;
        } else {
            display_character('Y');
            *my_score += 1;
        }
    } else {
        if (role == 1) {
            display_character('Y');
            *my_score += 1;
        } else {
            display_character('X');
            *opponent_score += 1;
        }
    }
}

void display_victory(int* my_score)
{
    if (*my_score >= 3) {
        display_scrolling_message("WINNER");
    } else {
        display_scrolling_message("LOSER");
    }
}

// play the game
int main (void)
{

    //int my_fail;
    //int opponent_fail;

    system_initialise();
    blue_led_off();
    //display_scrolling_message("MATTHEW");
    //display_character('X');
    int winning_score = 3;
    int my_score = 0;
    int opponent_score = 0;
    int role;
    role = start_screen();
    while (my_score < winning_score && opponent_score < winning_score) {
        pacer_wait();
        int result = 0;
        char message[7] = {'\0'};
        if (role == 1) {
            display_character('S');
            send_message();
            result = wait_for_other();
        } else {
            char attempt[7] = {'\0'};
            display_character('R');
            receive_message(message);
            int i = 0;
            int length = strlen(message);
            while (i < length) {
                pacer_wait();
                display_arrow_scrolling(message[i]);
                i++;
            }
            // Try copy original
            create_message(attempt);
            if (strncmp(attempt, message, 6) == 0) {
                display_scrolling_message("YES");
                result = 1;
            } else {
                display_scrolling_message("NO");
            }
            give_go_ahead(result);
        }
        post_round(role, result, &my_score, &opponent_score);
        if (role == 1) {
            role = 2;
        } else {
            role = 1;
        }
    }
    display_victory(&my_score);
    return 1;
}








