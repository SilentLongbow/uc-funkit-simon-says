/**  @file   displayMessage.h
     @author Siyuan Wei
     @ header file of receive_message
*/


#ifndef RECEIVE_MESSAGE_H
#define RECEIVE_MESSAGE_H


#include "system.h"



void receive_message(char message[]);

void clear_buffer(void);

int wait_for_other(void);

#endif
