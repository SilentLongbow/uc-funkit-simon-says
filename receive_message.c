/* Author: Siyuan Wei(ID: 022883373)
 *         Matthew Kenny (ID: 11031880)
 * Description: receive a message through serial communication
 */

#include <string.h>
#include "receive_message.h"
#include "system.h"
#include "pacer.h"
#include "ir_uart.h"
#include "displayMessage.h"

/** The receiver's method of receiving the message created by the sender */
void receive_message(char message[])
{
    char received[2] = {1, '\0'};
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
        } else {
            display_scrolling_message("...");
        }
    }
    message[index+1] = '\0';    // End the message with a string terminator
}

/** Wait for the receiver to finish their actions */
int wait_for_other(void) {
    char character = '\0';
    while (character != '1' && character != '0') {  // Wait until a go-ahead message is received
        pacer_wait();
        if (ir_uart_read_ready_p()) {
            character=ir_uart_getc();
        } else {
            display_scrolling_message("...");
        }
    }
    // See what the result of the receiver's task was
    int result;
    if (character == '1') {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

