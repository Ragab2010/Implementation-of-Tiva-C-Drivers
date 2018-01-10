/*
 * uart.h
 *
 *  Created on: ??�/??�/????
 *      Author: RAGAB
 */

#ifndef UART_H_
#define UART_H_

#include <stdio.h>
#include <stdlib.h>



void uart0_init(){
    SYSCTL_RCGCUART_R =(1<<0); //enable clock for UART0
    SYSCTL_RCGCGPIO_R =(1<<0); //enable clock for PORTA
    UART0_CTL_R = 0;           //Disable UART peripheral(UART Module)
    /*THE BAOUD RATE IS 9800*/
    UART0_IBRD_R = 104;
    UART0_FBRD_R =11;
    UART0_CC_R = 0X00 ;//USE SYSTEM CLOCK
    UART0_LCRH_R =(1<<5 )|( 1<<6); //frame is one byte , no fifo buffer , no parity bit
    UART0_CTL_R  = (1<<8) |(1<<9)|(1<<0); //ENABLE TX , RX , UART Module
    /********************************************/
    GPIO_PORTA_DEN_R = (1<<0  | 1<<1);//enable digital input
    GPIO_PORTA_AFSEL_R = (1<<0  | 1<<1);//isolate PA0 ,PA1 to work as alternate  fun
    GPIO_PORTA_PCTL_R = 0x11; //SET PA0 , PA1  WORK AS TX ,RX UART


}

void uart0_send( char byte ){
    while(UART0_FR_R &(1<<5));
    UART0_DR_R = byte;

}

char uart0_receive(){
//    while(!(UART0_FR_R &(1<<5)));
    while(UART0_FR_R & 0x10);
    return UART0_DR_R;
}

void uart0_sendString( char *str ){
    char i;
    for(i=0 ; str[i] ; i++)
        uart0_send(str[i]);

}
void uart0_receiveString(char *str){
    char i;
    for(i=0 ; str[i] ; i++)
        str[i]=uart0_receive();

}








#endif /* UART_H_ */
