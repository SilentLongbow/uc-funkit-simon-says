#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "led.h"

int main (void)
{
    system_init ();
    led_init ();
    while (1) {
    }
}
