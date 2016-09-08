/*************************************************
 * File:   led1.c
 * Author: Tommy Gartlan, Dundalk Institute of Technology
 * Created on 7 September 2016, 10:21
 * Simple main application file to toggle the digital pins of PORTB
 */

/*************************************************************
    Device Header File (Indirectly pulls in the pic18f4520.h
*************************************************************/
#include <xc.h>


/*************************************************************
 Compiler Directive to tell he compiler what clock freq is being used
*************************************************************/
#define _XTAL_FREQ 19660800
//#define _XTAL_FREQ 1

/*************************************************************
 Function Prototypes
*************************************************************/
void delay_1s(void);
//#include <delays.h>


void main(void) {
    unsigned char i=0;
    
    TRISB = 0;
 
    PORTB = 0x5A;

 //   Delay10KTCYx(100);
 //   Delay10KTCYx(100);
 //   Delay10KTCYx(100);

    while(1)
    {

        PORTB = 0x0F;
        delay_1s();
      
   

        PORTB = 0xF0;
        delay_1s();
       
        PORTB = 0xFF;
        delay_1s();
        

    }

    return;
}

void delay_1s(void)
{
    unsigned char i;
    for (i=0;i<25;i++)
            __delay_ms(40);  //max value is 40 since this depends on the _delay() function which has a max number of cycles
    
}
