

/**
 * main.c
 */


#include "C:\ti\TivaWare_C_Series-2.1.3.156\inc\TM4C123GH6PM.h"
#include "stdint.h"
#include "uart.h"




void adc_init(unsigned char pin_number){

    /* enable clocks */
    SYSCTL_RCGCADC_R  = (1<<0  | 1<<1);//ENABLE ADC0 , ADC1
    SYSCTL_RCGCGPIO_R = (1<<4); //ENBLE PORTE

    /* initialize PE3 for AIN0 input */
    GPIO_PORTE_AFSEL_R = (1<<3);//ISOLATE PE3 THAT'S WILL WORK IN ALTERNATE FUNCTION (ADC0)
    GPIO_PORTE_DEN_R   = 0X00;
    GPIO_PORTE_AMSEL_R = (1<<3);//WORK IN ANALOG FUNCTION

    /* initialize ADC0 */
    ADC0_ACTSS_R =0X00;//DISABLE SS3 BEFORE configuration
    ADC0_EMUX_R  =0x00;//make triger is processor
    ADC0_SSMUX3_R=(0x0F & pin_number);
    ADC0_SSCTL3_R= (1<<0 | 1<<1); /* take one sample at a time, set flag at 1st sample */
    ADC0_ACTSS_R =(1<<3);//ENABLE SS3 BEFORE configuration

}

int main(void)
{
    adc_init(0);
    uart0_init();
    volatile char result=7;

    while(1){
//    ADC0_PSSI_R |=(1<<3);//START CONVERTION
//    while(!(ADC0_RIS_R & (1<<3) ));/* wait for conversion complete */
//    result = ADC0_SSFIFO3_R; /* read conversion result */
    uart0_sendString("73");
    ADC0_ISC_R |=(1<<3);/* clear completion flag */
    }

	return 0;
}
