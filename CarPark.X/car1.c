/***************************************************
	Tommy Gartlan April 2011
Car Park project using PIC18F4520 
LEDs connected to PORTB keep track of number of cars
SW0 connected to PORTA.0 is in gate sensor
SW1 connected to PORTA.1 is in gate sensor

Issue with using 'if' statement to check switch since
switch is only checked as pass through.
Should use 'while' to wait for switch to be pressed.
 * 
 * 
 * Remember:-
 * USe TRISX to set directions of pins
 * USe LATX when pins are outputs and you want to write value
 * Use PORTX when pins are inputs and you want to read value
 * 
 *where X in name stands for A,B,C,D depending on port
*****************************************************/


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
void Initial(void);

/*****************************************
				Macros
******************************************/

/*****************************************
 Global Variables
******************************************/

/*****************************************
 			Main Program
******************************************/
void main(void)
{
	unsigned char count = 0;
	Initial();
	
	//foreground program
	while(1)
	{
		if (PORTAbits.RA0)      //this doesn't work since we cycle the loop so fast
			count++;
		LATB = count;
	}
	
}


/************************************************
 				Initial
    This function initialises SFRs and 
	global variables
*************************************************/

void Initial(void)
{

	ADCON1 = 0x0f; //pic18f4520
	
	TRISA = 0xff;
	TRISB = 0x00;
	LATB = 0x00;
    delay_1s();
    delay_1s();
    LATB = 0xFF;
    delay_1s();
    delay_1s();
    LATB = 0x00;
    delay_1s();
    delay_1s();
}



void delay_1s(void)
{
    unsigned char i;
    for (i=0;i<25;i++)
            __delay_ms(40);  //max value is 40 since this depends on the _delay() function which has a max number of cycles
    
}

