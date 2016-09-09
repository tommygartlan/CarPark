/***************************************************
	Tommy Gartlan April 2011
Car Park project using PIC18F4520 
LEDs connected to PORTB keep track of number of cars
SW0 connected to PORTA.0 is in gate sensor
SW1 connected to PORTA.1 is in gate sensor

Issue with using 'if' statment to check switch since
switch is only checked as pass through.
Should use 'while' to wait for switch to be pressed.
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
		PORTB = count;
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
	PORTB = 0x00;
}





