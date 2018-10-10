/* Author: Siyuan WEI(ID: 022883373)
 *         Matthew Kenny(ID: 11031880)
 * Description: The main game file
 */



#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "led.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"

#define PACER_RATE 500

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
    // general system initialiser
    system_init();

    // navigational switch initialiser
    navswitch_init();

    //timer initialiser
    pacer_init(PACER_RATE);


    //IR initialiser
    ir_uart_init();


    //LED matrix initialiser
    int i;
    for (i = 0; i < 7; i++) {
        pio_config_set(rows[i], PIO_OUTPUT_HIGH);
    }
    for (i = 0; i < 5; i++) {
        pio_config_set(cols[i], PIO_OUTPUT_HIGH);
    }


    //LED initialiser (might be useful)
    led_init ();



}

/*dicide which player send message first*/
/*
int decide_first_player(void)
{
}
* */

/** Turns on the blue LED when called */
void blue_led_on()
{
    led_set(LED1, 1);
}

/** Turns off the blue LED when called */
void  blue_led_off()
{
    led_set(LED1, 0);
}

// play the game
int main (void)
{
    system_initialise();    // Turn on the blue LED
    blue_led_on();
    while (1) {
    }
}
