/**  @file   displayMessage.h
     @author Matthew Kenny (ID: 11031880)
     @author Siyuan Wei (ID: 22883373)
     @date   16 Oct 2018
     @brief  Visualising information on the display.
*/


#ifndef DISPLAYMESSAGE_H
#define DISPLAYMESSAGE_H

#include "system.h"
#include "pio.h"

/** Displays a directional arrow across the display from left to right */
void display_arrow_scrolling(const char direction);

void display_arrow_still(const char direction);

/** Displays a scrolling message on the display */
void display_scrolling_message(char message[]);

/** Displays a single character on the display */
void display_character(const char character);

/** Initialises every column and row of the LED matrix */
void message_display_init(const pio_t rows[], const pio_t cols[]);

#endif
