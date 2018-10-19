/**  @file   send_message.h
     @author Matthew Kenny (ID: 11031880)
     @author Siyuan Wei (ID: 22883373)
     @date   16 Oct 2018
     @brief  Send a message through serial communication
*/


#ifndef SEND_MESSAGE_H
#define SEND_MESSAGE_H

#include "system.h"

/** Send the message made by the sender, to the receiver */
void send_message(void);

/** The inform the sender that the receiver has completed their tasks */
void give_go_ahead(int result);

#endif
