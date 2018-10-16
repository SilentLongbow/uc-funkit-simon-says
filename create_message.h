/**  @file   create_message.h
     @author Matthew Kenny
     @date   16 Oct 2018
     @brief  Creating the message through the navbutton
*/

#include "system.h"

/** Message creation at the start of a round, returns the message */
char* create_initial_message(void);

/** Response message creation on the receiver's side */
char* create_response_message(void);
