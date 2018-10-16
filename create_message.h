/**  @file   create_message.h
     @author Matthew Kenny
     @date   16 Oct 2018
     @brief  Creating the message through the navbutton
*/

#ifndef CREATE_MESSAGE_H
#define CREATE_MESSAGE_H

#include "system.h"

/** Message creation at the start of a round, returns the message */
char* create_initial_message(char message[]);

/** Response message creation on the receiver's side */
char* create_response_message(char message[]);

#endif
