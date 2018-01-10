

/**
 * main.c
 */

#include "C:\ti\TivaWare_C_Series-2.1.3.156\inc\TM4C123GH6PM.h"
#include "stdint.h"


void pwm_pf3_init(){

    /*GPIO ALTERNATIVE FUNCTION*/
    SYSCTL_RCGCGPIO_R =(1<<5);
    SYSCTL_RCGCPWM_R  =(1<<1);
    SYSCTL_RCC_R &= ~0x00100000;

    GPIO_PORTF_AFSEL_R = (1<<3);
    GPIO_PORTF_DEN_R  =(1<<3);
    //GPIO_PORTF_PCTL_R =(5<<3);
    GPIO_PORTF_PCTL_R &= ~0x0000F000; /* make PF3 PWM output pin */
    GPIO_PORTF_PCTL_R  |= 0x00005000;

    PWM1_3_CTL_R =0; //STOP PWM
    PWM1_3_GENB_R =(1<<6); //RELOAD OUTPUT IS HIGH , MATCH CMPA OUTPUT IS LOW
    PWM1_3_LOAD_R=16000;
    PWM1_3_CMPA_R=8000;


    PWM1_3_CTL_R |=1; //enable PWM
    PWM1_ENABLE_R = (1<<7);



}
int main(void)
{
    pwm_pf3_init();


    while(1);


	return 0;
}


