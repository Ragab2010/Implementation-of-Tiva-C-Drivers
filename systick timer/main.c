

/**
 * main.c
 */

#include "C:\ti\TivaWare_C_Series-2.1.3.156\inc\TM4C123GH6PM.h"
#include "stdint.h"

void systick_init(){
    NVIC_ST_RELOAD_R  = 7999999;//LOAD IN RELOAD REG
    NVIC_ST_CURRENT_R = 0;      //MAKE SYSTICK TIMER BY VALUE ZERO TO COUNT
    NVIC_ST_CTRL_R    = (1<<0 | 1<<2 );//ENABLE  SYSTICK TIMER , CLOCK FROM SYSTEM
}

int main(void)
{
    systick_init();
    SYSCTL_RCGCGPIO_R = (1<<5);// ENABLE CLOCK FOR PORTF
    GPIO_PORTF_DIR_R  = (1<<2);//MAKE PF4 OUTPUT  GREEN LED
    GPIO_PORTF_DEN_R  = (1<<2);//MAKE PF4 DIGITAL
    while(1){
        if(NVIC_ST_CTRL_R & 1<<16){
            GPIO_PORTF_DATA_R ^= (1<<2);
        }
    }


	return 0;
}
