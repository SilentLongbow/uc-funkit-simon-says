/* Author: Siyuan WEI(ID:22883373)
 *         Matthew Kenny(ID:)
 * 
 * describle: main file that run the game
 */



#include "system.h"
#include "navswitch.h"
#include "pacer.h"
#include "tinygl.h"






#define PACER_RATE 500  












/* init drivers */
void system_initialise(void)
{
    // general system init
    system_init();
    
    // naveswitch init
    navswitch_init();
    
    //timer init
    pacer_init(PACER_RATE);
    
    
    //IR init
    ir_uart_init();
    
    
    //LED matrix init
    //trying to figure it out
    
    
    
    //LED1 init(might be useful)
    led_init ();
    led_set(LED1, 0);
    
    
}



/*dicide which player send message first*/
int decide_first_player(void)
{
    
    
    
    
    
    
}
    













// play the game
int main (void)
{
    


    while (1)
    {

    }
}
