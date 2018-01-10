

/**
 * main.c
 */

#include "C:\ti\TivaWare_C_Series-2.1.3.156\inc\TM4C123GH6PM.h"
#include "stdint.h"

void systick_timer_init_interrupt(){

    NVIC_ST_CTRL_R =(3<<1); // ENABLE INTERRUPT , CONNECT TO SYSTEM CLOCK
    NVIC_ST_RELOAD_R = 8999999;
    /*ENABLE NVIC INTERRUPT*/
    /*SYSTICK
     * -there is only one bit1 in NVIC_ST_CTRL_R that's enable interrupt.
     * -in NVIC_ST_CTRL_R the bit16 is the flage when it set and interrupt enable
     * the interrupt is occur
     * -gloable interupt enable by default is enable
     * */
    NVIC_ST_CTRL_R |=1;//enable systick

}
void systick_handle(void){
    if(NVIC_ST_CTRL_R &(1<<16))
            GPIO_PORTF_DATA_R ^=(1<<2);
}

int main(void)
{
    SYSCTL_RCGCGPIO_R =(1<<5);
    /*CONFIG  PF1,PF2,PF3  AS OUTPUT*/
    GPIO_PORTF_DEN_R =(14<<0);
    GPIO_PORTF_DIR_R =(14<<0);
    GPIO_PORTF_DATA_R=0;
    systick_timer_init_interrupt();
    while(1);
	return 0;
}
