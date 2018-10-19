/* Author: Siyuan WEI(ID: 022883373)
 *         Matthew Kenny(ID: 11031880)
 * Description: The main game file
 */

#include <string.h>
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
#include "../fonts/font5x7_1.h"

#define PACER_RATE 1000
#define MESSAGE_RATE 15

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
    system_init();
    navswitch_init();
    pacer_init(PACER_RATE);
    ir_uart_init(); 
    message_display_init(rows, cols); // Initialises
    led_init ();
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

/*decide which player send message first
 * return mode(1 or 2) 1 for send, 2
 * for receive
 */
int start_screen(void)
{

    int player_mode = 0;
    int flag = 0;
    char character = 0;
    // wait until either player has pressed down the nav-switch
    while(flag != 1) {
        pacer_wait();
        navswitch_update();
        // push to be first player (send message)
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

/** Increases the score of the winning player by 1 */
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

/** Displays the winning or losing message on the display when the game is over */
void display_victory(int* my_score)
{
    if (*my_score >= 3) {
        display_scrolling_message("WINNER");
    } else {
        display_scrolling_message("LOSER");
    }
}

/** The set of tasks performed by the sender of the round */
int sender_task(int result)
{
    display_character('S');
    send_message();
    result = wait_for_other();  // Wait for the receiver to finish their activities
    return result;
}

/** The set of tasks performed by the reciver*/
int receiver_task(void)
{ 
    char message[7] = {'\0'};
    char attempt[7] = {'\0'};
    int result = 0;
    display_character('R');
    receive_message(message);
    int i = 0;
    int length = strlen(message);
    while (i < length) {    // Display the message across the screen
        pacer_wait();
        display_arrow_scrolling(message[i]);
        i++;
    }
    create_message(attempt);    // Attempt to replicate message
    if (strncmp(attempt, message, 6) == 0) {
        display_scrolling_message("YES");
        result = 1;
    } else {
        display_scrolling_message("NO");
    }
    give_go_ahead(result);  // Let the sender know the process is complete
    return result;
    
}

// play the game
int main (void)
{
    system_initialise();
    blue_led_off();
    int winning_score = 3;  // End goal
    int my_score = 0;
    int opponent_score = 0;
    int role;
    role = start_screen();
    while (my_score < winning_score && opponent_score < winning_score) {
        pacer_wait();
        int result = 0;
        if (role == 1) { 
            // Sender -> role == 1
            result = sender_task(result);
        } else {
            // Receiver -> role = 2
            result = receiver_task();
        }
        post_round(role, result, &my_score, &opponent_score);
        // Swap the roles
        if (role == 1) {
            role = 2;
        } else {
            role = 1;
        }
    }
    display_victory(&my_score);
    return 1;
}








