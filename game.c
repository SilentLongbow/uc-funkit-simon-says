/* Author: Siyuan WEI(ID: 022883373)
 *         Matthew Kenny(ID: 11031880)
 * Description: The main game file
 */


#include <stdio.h>
#include "system.h"
#include "displayMessage.h"
#include "pacer.h"
#include "led.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "../fonts/font5x7_1.h"

#define PACER_RATE 2000
#define MESSAGE_RATE 20
#define DISPLAY_COUNT 1000
#define MAX_FAIL_TIMES 3
#define MESSAGE_LENGTH 10

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
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

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
    int counter = 1000;
    int flag = 0;
    char character = 0;

    // keep display message before push nav_switch
    while(flag != 1) {
        blue_led_on();
        
        tinygl_update();
        
        if (counter >= DISPLAY_COUNT) {
            tinygl_text("N FOR SEND S FOR RECIEVE");
            //tinygl_text("N FOR SEND S FOR RECIEVE  \0");
           
            counter = 0;
        }
        
        pacer_wait();
        navswitch_update();
        tinygl_update();

        // push to be first player(send message)
        if (ir_uart_read_ready_p()) {
            character = ir_uart_getc();
            if (character == 'p') {
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
        
        
        
        
        /*if(navswitch_push_event_p(NAVSWITCH_NORTH)) {
            player_mode = 1;
            blue_led_off();
            flag = 1;
        }
        if(navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            player_mode = 2;
            flag = 1;
            blue_led_off();
        }*/
    }
    
    tinygl_clear();
    tinygl_update();
    return player_mode;
    
}




// display result of the game;
void finish_screen(int my_fail, int opponent_fail)
{
    
    if (my_fail >= MAX_FAIL_TIMES) {
        tinygl_text("YOU LOST");
    }
    if (opponent_fail >= MAX_FAIL_TIMES) {
        tinygl_text("YOU WON ");
    }
    //DISPLAY FINISH MESSGAE
    while (1)
    {
        pacer_wait();
        tinygl_update();
    }
}









// play the game

int main (void)
{
    
    //int my_fail;
    //int opponent_fail;
    
    system_initialise();
    blue_led_off();
    //display_character('X');
    //display_scrolling_message("HELLO");

    //tinygl_text("CHOOSE FIRST PLAYER");
    while (1) {

        
        tinygl_update();
        //int mode = start_screen();
        
        //my_fail = 3;
        //opponent_fail = 2;
        
        pacer_wait ();
        //tinygl_update();
        finish_screen(4, 1);
    }
    return 1;

}

