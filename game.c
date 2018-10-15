/* Author: Siyuan WEI(ID: 022883373)
 *         Matthew Kenny(ID: 11031880)
 * Description: The main game file
 */



#include "system.h"
#include "displayMessage.h"
#include "pacer.h"
#include "led.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "../fonts/font5x7_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10

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

/*dicide which player send message first*/
/*
int decide_first_player(void)
{
}
* */

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
    //display_character('y');
    display_scrolling_message("Hi");
    blue_led_off();
    while (1) {
        tinygl_update();
    }
    return 1;
}
