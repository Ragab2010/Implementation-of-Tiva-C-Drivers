

/**
 * main.c
 */

#include "C:\ti\TivaWare_C_Series-2.1.3.156\inc\TM4C123GH6PM.h"
#include "stdint.h"
//#include "driverlib/interrupt.h"

void portf_sw0_interrupt_init(){
    SYSCTL_RCGCGPIO_R =(1<<5);
    GPIO_PORTF_DIR_R  =(1<<1)|(1<<2);//MAKE PF1--->OUTPUT , PF0 OUTPUT
    GPIO_PORTF_DEN_R  =(1<<4)|(1<<1)|(1<<2);//MAKE PF1 , PF0  WORK AS DIGITAL
    GPIO_PORTF_PUR_R  =(1<<4);//PULL UP PF0


    /*TO WORK IN EDGE SENSITIVE IN RISING EDGE*/
    GPIO_PORTF_IS_R   =0; //EDGE SENSITIVE
    GPIO_PORTF_IEV_R  =0;//WORK WITH PF0 RISING TRIGGER
    GPIO_PORTF_IBE_R  =0;//Interrupt generation is controlled (GPIOIEV)
    /******************************************/
    /*TO ENABLE INTERRUPT*/
    GPIO_PORTF_IM_R   =(1<<4);//UNMASKE PF0
    /*********************/
    /*CLEAR */
    GPIO_PORTF_ICR_R  =(1<<4);//Interrupt generation is controlled (GPIOIEV)


    /*ENABLE ENTERRUPT TO PROTF IN NVIC*/
    NVIC_EN0_R       |=(1<<30);//FOR PORTF
    NVIC_PRI17_R      =(3<<21);//SET PRIORTY 3 FOR PORTF


    /**********Enable global interrupt***********/
    NVIC_ST_CTRL_R |=(1<<1);//ENABLE Global INTERRUPT bit
    __asm("    mrs     r0, PRIMASK\n"
          "    cpsie   i\n"
          "    bx      lr\n");
    /*************************************/

    /*********to Disable global interrupt******************/
    __asm("    mrs     r0, PRIMASK\n"
          "    cpsid   i\n"
          "    bx      lr\n");
    /******************************************************/
}

void printf(){

}


void GPIOF_HANDLER(void)
{
    GPIO_PORTF_ICR_R  |=(1<<4);//to clear interrupt flage
    GPIO_PORTF_DATA_R ^=(1<<1);

}



int main(void)
{

    printf();
    portf_sw0_interrupt_init();

    //GPIO_PORTF_DATA_R ^=(1<<1);

       while(1);
//    while(1){
//      while(!(GPIO_PORTF_DATA_R &(1<<4))){
//             GPIO_PORTF_DATA_R |=(1<<1);
//            }
//
//      GPIO_PORTF_DATA_R &=~(1<<1);
//    }
	return 0;
}
