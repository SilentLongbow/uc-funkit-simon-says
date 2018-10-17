/* Author: Siyuan WEI(ID: 022883373)
 *         Matthew Kenny (ID: 11031880)
 * Description: set message, called by game.c
 */


#include <stdio.h>
#include <string.h>
#include "system.h"
#include "pacer.h"
#include "led.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "create_message.h"
#include "displayMessage.h"

/** Sends the given message over IR */
void send_message(void)
{
    char message[7];
    create_message(message);
    display_scrolling_message("SND");
    int length = strlen(message);
    int i = 0;
    for (i; i <= length; i++) {
        int counter = 0;
        while (counter < 700) {
            pacer_wait();
            counter++;
        }
        ir_uart_putc(message[i]);
    }
}

void give_go_ahead(int result) {
    if (result == 1) {
        ir_uart_putc('1');
    } else {
        ir_uart_putc('0');
    }
}




