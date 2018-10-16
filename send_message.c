/* Author: Siyuan WEI(ID: 022883373)
 *         Matthew Kenny (ID: 11031880)
 * Description: set message, called by game.c
 */


#include <stdio.h>
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
    display_scrolling_message("D");
    ir_uart_puts(message);
    ir_uart_putc('\0');
}

void give_go_ahead(int result) {
    if (result == 1) {
        ir_uart_putc('1');
    } else {
        ir_uart_putc('0');
    }
}




