/* Author: Siyuan WEI(ID: 022883373)
 * Description: receive and check message, called by game.c
 */

#include <stdio.h>
#include "system.h"
#include "pacer.h"
#include "led.h"
#include "tinygl.h"
#include "ir_uart.h"



#include <stdio.h>

char receive_message(int message_length)
{
    char message[message_length];
    int flag1 = 0;
    char my_motion;
    char is_success;

    tinygl_text("  WAIT TO RECEIVE");



    //after full message is received, break loop
    int i = 0;
    while(flag1 != 1) {

        pacer_wait ();
        tinygl_update ();


        if(ir_uart_read_ready_p()) {
            message[i] = ir_uart_getc(); // save the received message in message array from send_message
            i++;
        }

        if(i >= message_length) {
            flag1 = 1;
        }

    }



    // display received message one by one
    flag1 = 0; //reuse flag1
    i = 0;
    while(flag1 != 1) {

        pacer_wait ();
        tinygl_update ();


        if (message[i] == 'N') {
            tinygl_text(" N \0");
        }
        if (message[i] == 'E') {
            tinygl_text(" E \0");
        }
        if (message[i] == 'S') {
            tinygl_text(" S \0");
        }
        if (message[i] == 'W') {
            tinygl_text(" W \0");
        }
        if (message[i] == 'P') {
            tinygl_text(" P \0");
        }
        i++;


        // break is all char displayed
        if(i >= message_length) {
            flag1 = 1;
        }

    }



    //get your nav_motion and compare with opponent's message

    flag1 = 0;
    i = 0;
    while (flag1 != 1) {
        pacer_wait ();
        tinygl_update ();

        // get your nav_motion
        my_motion = nav_motion();


        // if the characters are same, move to next one
        if(my_motion != 0 && message[i] == my_motion) {
            i++;
        }

        if(my_motion != 0 && message[i] != my_motion) {
            is_success = 'N';
            tinygl_text("  oops ");
            break;
        }

        if(i >= message_length) {
            is_success = 'Y';
            flag1 = 1;
        }
    }


    // send check result back to opponent
    flag1 = 0;
    while(flag1 != 1) {
        pacer_wait ();
        if (ir_uart_write_ready_p()) {
            ir_uart_putc(is_success);
            flag1 = 1;
        }
    }

    return is_success;
}







