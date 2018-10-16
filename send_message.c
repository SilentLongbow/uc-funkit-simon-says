/* Author: Siyuan WEI(ID: 022883373)
 * Description: set message, called by game.c
 */


#include <stdio.h>
#include "system.h"
#include "pacer.h"
#include "led.h"
#include "tinygl.h"

// message length default as 5
char send_message(int message_length)
{
    // local variable
    char motion = 0; // variable to get player's motion
    int count_sent; // count how many letters sent
    int flag = 0; // to controll while loop
    char is_success;



    // Display starting massage
    tinygl_text("  SEND MESSAGE:  ");


    //after full message is sent, break loop
    while(flag != 1) {
        pacer_wait ();
        tinygl_update();
        motion = nav_motion();

        //send message to opponent
        if(motion != 0 && count_sent < message_length && ir_uart_write_ready_p()) {
            ir_uart_putc(motion);
            count_sent++;
        }

        if(count_sent >= message_length) {
            flag = 1;
        }
    }




    tinygl_text(" wating to complete ");


    flag = 0;
    // wait opponent to complete and check
    while (flag != 1) {
        pacer_wait ();
        tinygl_update ();

        if (ir_uart_read_ready_p()) {
            is_success = ir_uart_getc(); // receive check result from receive_message, Y or N
            flag = 1;
        }
    }


    return is_success;



}




