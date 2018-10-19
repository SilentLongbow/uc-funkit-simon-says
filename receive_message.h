/**  @file   receive_message.h
     @author Matthew Kenny (ID: 11031880)
     @author Siyuan Wei (ID: 22883373)
     @date   16 Oct 2018
     @brief  Receive a message through serial communicaiton
*/


#ifndef RECEIVE_MESSAGE_H
#define RECEIVE_MESSAGE_H


#include "system.h"

/** Wait until the sender has created and set their message, then receive & parse it */
void receive_message(char message[]);

/** The sender waits for the receiver to finish their tasks */
int wait_for_other(void);

#endif
