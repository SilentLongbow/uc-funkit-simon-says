#include "system.h"
#include "pio.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font5x7_1.h"

void display_scrolling_message(void)
{
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    while (1) {
        pacer_wait();
        tinygl_update();
    }

}

void display_char(char character[])
{
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    

void message_display_init(const pio_t rows[], const pio_t cols[])
{
    //LED matrix initialiser
    int i;
    for (i = 0; i < 7; i++) {
        pio_config_set(rows[i], PIO_OUTPUT_HIGH);
    }
    for (i = 0; i < 5; i++) {
        pio_config_set(cols[i], PIO_OUTPUT_HIGH);
    }
}

void text_display_setup
