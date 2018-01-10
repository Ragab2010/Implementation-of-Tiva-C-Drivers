

/**
 * main.c
 */

#include "C:\ti\TivaWare_C_Series-2.1.3.156\inc\TM4C123GH6PM.h"
#include "stdint.h"

void uart0_recieve_by_intrrupt(){
    SYSCTL_RCGCUART_R =(1<<0); //ENABLE UART0 CLOCK
    SYSCTL_RCGCGPIO_R =(1<<0)|(1<<5); //ENABLE PORTA CLOCK and PORTF CLOCK
    /*CONFIG  the PA0 , PA1 TO WOKE IN UART0*/
    GPIO_PORTA_AFSEL_R =(1<<0)|(1<<1);//ISOLATE PA0 , PA1 TO WORK IN UART0
    GPIO_PORTA_PCTL_R   = 0X11;//SET PA0 , PA1  WORK AS TX ,RX UART
    GPIO_PORTA_DEN_R = (1<<0  | 1<<1);//enable digital input

    /*CONFIG  PF1,PF2,PF3  AS OUTPUT*/
    GPIO_PORTF_DEN_R =(3<<1);
    GPIO_PORTF_DIR_R =(3<<1);
    GPIO_PORTF_DATA_R=0;

    /*CONFIG THE UART BAOUD RATE */
    UART0_CTL_R =0;//DISABLE THE UART0
    UART0_CTL_R |=(1<<9);//ENABLE RX
    UART0_CTL_R |=(1<<8);//ENABLE TX

    /*BOUD RATE*/
    UART0_IBRD_R =104;
    UART0_FBRD_R =11;
    UART0_LCRH_R |=(1<<5)|(1<<6); //frame is one byte , no fifo buffer , no parity bit

    UART0_CTL_R |=(1<<0);//ENABLE UART0 MODULE

    /*ENABLE INTERRUPT FOR UART0*/
    UART0_IM_R   |= (1<<4);//ENABLE RECIEVE INTERRUPT
    NVIC_EN0_R   |=(1<<5);
    //UART0_CTL_R |=(1<<0);//ENABLE UART0 MODULE




}


void uart0_handel(void){

   if(UART0_DR_R  == 'a')
    GPIO_PORTF_DATA_R =(1<<1);
   else if(UART0_DR_R  == 'b')
       GPIO_PORTF_DATA_R =(1<<2);
   else if(UART0_DR_R  == 'c')
       GPIO_PORTF_DATA_R =(1<<3);
   else
       GPIO_PORTF_DATA_R =0;

    UART0_RIS_R |=(1<<4);
}

int main(void)
{
    uart0_recieve_by_intrrupt();
    while(1);

	return 0;
}
