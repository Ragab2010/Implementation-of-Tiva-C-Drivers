/*
 * main.c
 */

#include "C:\ti\TivaWare_C_Series-2.1.3.156\inc\TM4C123GH6PM.h"
#include "stdint.h"

///* PORTF data register */
//#define PORTFDAT (*((volatile unsigned int*)0x400253FC))
///* PORTF data direction register */
//#define PORTFDIR (*((volatile unsigned int*)0x40025400))
///* PORTF digital enable register */
//#define PORTFDEN (*((volatile unsigned int*)0x4002551C))
///* run mode clock gating register */
//#define RCGCGPIO (*((volatile unsigned int*)0x400FE608))
///* coprocessor access control register */
//#define SCB_CPAC (*((volatile unsigned int*)0xE000ED88))
int main(void) {
/*    SYSCTL->RCGCGPIO = (1<<5);
    GPIOF->DIR  |= (1<<2);// MAKE PF2 OUTPUT (GREEN LED)
    GPIOF->DIR  |= (1<<0);//make PF0 AS INPUT (SWITCH)
    GPIOF->DEN   = (1<< 0 | 1<<2);//MAKE PF0 , PF2  DIGITAL I/O
    GPIOF->PUR   = (1<< 0);//PULL-UP FOR SW1 PF0
    GPIOF->DATA &=~(1<<2);*/


   SYSCTL_RCGCGPIO_R     =(1<<5);//ENABLE CLOCK FOR PROTF
   SYSCTL_GPIOHBCTL_R    =(1<<5);
   GPIO_PORTF_AHB_DIR_R |=(1<<1);//PF1 OUTPUT  , PF0 INPUT
   GPIO_PORTF_AHB_LOCK_R = 0x4C4F434B;
   GPIO_PORTF_AHB_CR_R   = 0X01;
   GPIO_PORTF_AHB_DEN_R  =(1<<1 | 1<<0 );
   GPIO_PORTF_AHB_PUR_R |=(1<<0); // ENABLE PULL-UP FOR PF0
   GPIO_PORTF_AHB_DATA_R &=~(1<<1);

   while(1){
       while(!(GPIO_PORTF_AHB_DATA_R &(1<<0))){
           GPIO_PORTF_AHB_DATA_R |=(1<<1);
       }

       GPIO_PORTF_AHB_DATA_R &=~(1<<1);
    }


	return 0;
}

void SystemInit(void)
{
    /* Grant coprocessor access */
    /* This is required since TM4C123G has a floating point coprocessor */
    NVIC_CPAC_R |= 0x00F00000;
}

//#include "C:\Keil\TExaSware\TM4C123GH6PM.h"
//
//
//
///* PORTF data register */
//#define PORTFDAT (*((volatile unsigned int*)0x400253FC))
///* PORTF data direction register */
//#define PORTFDIR (*((volatile unsigned int*)0x40025400))
///* PORTF digital enable register */
//#define PORTFDEN (*((volatile unsigned int*)0x4002551C))
///* run mode clock gating register */
//#define RCGCGPIO (*((volatile unsigned int*)0x400FE608))
///* coprocessor access control register */
//#define SCB_CPAC (*((volatile unsigned int*)0xE000ED88))
//
//
//void delayMs(int n)
//{
//int i, j;
//for(i = 0 ; i < n; i++)
//for(j = 0; j < 3180; j++){} /* do nothing for 1 ms */
//}
//
//
///* This function is called by the startup assembly code to perform system specific
//initialization tasks. */
//void SystemInit(void)
//{
///* Grant coprocessor access*/
///* This is required since TM4C123G has a floating point coprocessor */
//SCB_CPAC |= 0x00F00000;
//}
//
//void GPIO_init(){
////  RCGCGPIO |=(1<<5);//enable clock for PROTF only
////  PORTFDIR |=(1<<1)|(1<<2)|(1<<3);//make PF1 ,PF2 ,PF3 ouput; 01110   (PROTF IS 5PIN only)
////  PORTFDEN |=(1<<1)|(1<<2)|(1<<3);
//
//    /*by the address from vendor*/
////  RCGCGPIO |=(1<<5);
////  GPIOF->DIR |=(1<<1)|(1<<2)|(1<<3);
////  GPIOF->DEN |=(1<<1)|(1<<2)|(1<<3);
//
//}
//void GPIO_SW_init(){
//    SYSCTL_RCGCGPIO_R = (1<<5); //enable clock for protf
//    /* Thesecond step is to unlock the port if we use portOnly PC3-0, PD7, and PFO on the TM4C need to be unloeked.
//            and GPIOLOCK  is locked by GPIOCR register */
//    GPIO_PORTF_LOCK_R =0x4C4F434B;// TO ENABLE GPIOCR
//    GPIO_PORTF_CR_R =(1<<0);/* SET BIT0 IN PROTF TO UNLOCK THIS REGISTER( GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN)
//                                                        TO WORK WITH SW2(PF0) , THIS BIT IS MULTIPLIXING WITH NMI */
//    GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
//  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
//    GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
//    GPIO_PORTF_DEN_R =0X1F;
//    GPIO_PORTF_DIR_R =(1<<1)|(1<<2)|(1<<3);//PF1 ,PF2 ,PF3 ouput and PF0,PF4 input
//
//    GPIO_PORTF_PUR_R =(1<<0)|(1<<4);//MAKE PF0 , PF4 AS INPUT
//}
//
//    unsigned int sw;
//int main(){
//    GPIO_SW_init();
//
//    while(1){
//        sw =GPIO_PORTF_DATA_R &0x01;
//
//        /*CHECK THE SW0 AND SET LED RED*/
//        while(!(GPIO_PORTF_DATA_R &1)){
//            GPIO_PORTF_DATA_R =2;
//        }
//        GPIO_PORTF_DATA_R =0;
//
////      PORTFDAT =(1<<1);
////      delayMs(500);
////      PORTFDAT =(1<<2);
////      delayMs(500);
////      PORTFDAT =(1<<3);
////      delayMs(500);
////      PORTFDAT =0;
////      delayMs(500);
//
//        /*using #define address vendor*/
////      GPIOF->DATA =(1<<1);
////      delayMs(500);
////      GPIOF->DATA =0;
////      delayMs(500);
//    }
//
//return  0;
//}

