

/**
 * main.c
 */

#include "C:\ti\TivaWare_C_Series-2.1.3.156\inc\TM4C123GH6PM.h"
#include "stdint.h"
/*timer0 as 16bit , down count mode , one-shot - delay 1 sec*/
void timer0_delay_500sec_oneshot_downmode_16bit(){
    SYSCTL_RCGCTIMER_R =(1<<0);//ENABLE TIMER0
    TIMER0_CTL_R  = 0; //DISABLE TIMER0
    TIMER0_CFG_R =0x04; // make timer0 16bit
    TIMER0_TAMR_R = (1<<1);// on-shot timer if count up made bit 4 bu one -->(1<<4)
    TIMER0_TAPR_R =255; //PRESCAL
    TIMER0_TAILR_R =62499; // RELAOD REGISTER
    TIMER0_CTL_R = 0X01;  //ENABLE TIMER0

    while(!(TIMER0_RIS_R &(1<<0))){

    }
    TIMER0_ICR_R |=(1<<0);//clear flage of one-shot;

}
void timer0_delay_500sec_periodic_downmode_16bit(){
    SYSCTL_RCGCTIMER_R =(1<<0);//ENABLE TIMER0
    TIMER0_CTL_R  = 0; //DISABLE TIMER0
    TIMER0_CFG_R =0x04; // make timer0 16bit
    TIMER0_TAMR_R = 0x2;// Periodic if count up made bit 4 bu one -->(1<<4)
    TIMER0_TAPR_R =255; //PRESCAL
    TIMER0_TAILR_R =62499; // RELAOD REGISTER
    TIMER0_CTL_R = 0X01;  //ENABLE TIMER0

}


int main(void)
{
      SYSCTL_RCGCGPIO_R = (1<<5);// ENABLE CLOCK FOR PORTF
      GPIO_PORTF_DIR_R  = (1<<2);//MAKE PF4 OUTPUT  GREEN LED
      GPIO_PORTF_DEN_R  = (1<<2);//MAKE PF4 DIGITAL
      timer0_delay_500sec_periodic_downmode_16bit();
      while(1){

          while(!(TIMER0_RIS_R &(1<<0))){

          }
          TIMER0_ICR_R |=(1<<0);//clear flage of one-shot;

           GPIO_PORTF_DATA_R ^= (1<<2);
//              timer0_delay_1sec_oneshot_downmode_16bit();
//              GPIO_PORTF_DATA_R ^= (1<<2);


      }

	return 0;
}
