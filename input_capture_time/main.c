

/**
 * main.c
 */

#include "C:\ti\TivaWare_C_Series-2.1.3.156\inc\TM4C123GH6PM.h"
#include "stdint.h"

void timer0_init_input_capture(){
    SYSCTL_RCGCTIMER_R = (1<<0);//ENABLE TIMER BLOCK 0
    SYSCTL_RCGCGPIO_R  = (1<<1);//ENABLE PORTB
    TIMER0_CTL_R = 0;//DISABLE TIMER0
    /*specify PB6 to work in capture mode with timer0*/
    GPIO_PORTB_DIR_R &=~(1<<6);
    GPIO_PORTB_DEN_R |=(1<<6);
    GPIO_PORTB_AFSEL_R |=(1<<6);
    GPIO_PORTB_PCTL_R =0X07000000;
    /*configure the timer0 to work in capture mode edge-time mode*/
    TIMER0_CFG_R =0X4; // 16BIT TIMERA
    TIMER0_TAMR_R =0x17; /* up-count, edge-time, capture mode */
    TIMER0_CTL_R |= 1;//ENABLE TIMER0

}
/* This function captures two consecutive rising edges of a periodic signal from Timer Block 0 Timer A and returns the time difference (the period of the signal). */
int Timer0A_periodCapture(void)
{
    int lastEdge, thisEdge;

    /* capture the first rising edge */
    TIMER0_ICR_R = 4;            /* clear timer0A capture flag */
    while((TIMER0_ICR_R &(1<<3)) == 0) ;    /* wait till captured */
    lastEdge = TIMER0_TAR_R;     /* save the timestamp */

    /* capture the second rising edge */
    TIMER0_ICR_R= 4;            /* clear timer0A capture flag */
    while((TIMER0_ICR_R & (1<<3)) == 0) ;    /* wait till captured */
    thisEdge = TIMER0_TAR_R;     /* save the timestamp */

    return (thisEdge - lastEdge) & 0x00FFFFFF; /* return the time difference */
}


int main(void)
{
    timer0_init_input_capture();
    Timer0A_periodCapture();
    while(1);
	return 0;
}
