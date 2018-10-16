/* Author: Siyuan WEI(ID: 022883373)
 * Description: receive and check message, called by game.c
 */

#include <stdio.h>
#include <string.h>
#include "system.h"
#include "pacer.h"
#include "led.h"
#include "tinygl.h"
#include "ir_uart.h"

#include "displayMessage.h"


void receive_message(char message[])
{
    led_set(LED1, 1);
    char received[2] = " ";
    char expected[7] = "NSEW10";
    int index = 0;
    while (received[0] != '\0' && index < 6) {
        pacer_wait();
        if (ir_uart_read_ready_p()) {
            received[0] = ir_uart_getc();
            if (strpbrk(received, expected) != NULL) {
                message[index] = received[0];
                index++;
            }

        }

    }
    message[6] = '\0';
    led_set(LED1, 0);
}

int wait_for_other(void) {
    char character = '\0';
    led_set(LED1, 1);
    while (character != '1' && character != '0') {
        pacer_wait();
        if (ir_uart_read_ready_p()) {
            character=ir_uart_getc();
        }
    }
    int result;
    if (character == '1') {
        result = 1;
    } else {
        result = 0;
    }
    led_set(LED1, 0);
    return result;
}

