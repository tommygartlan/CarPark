/***************************************************
	Tommy Gartlan September 2011
Car Park project using PIC16F877A 
LEDs connected to PORTB keep track of number of cars
SW0 connected to PORTA.0 is in gate sensor
SW1 connected to PORTA.1 is in gate sensor

(see flowchart for car park)
Add a function to software 'debounce' the key

Explain function prototypes
 * CAR 4
 * Modified debounce function so is more useful in that can pass the pin number
 * to debounce
 * Also added exit sensor key
****************************************************/

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

void Initial(void);
void delay_1s(void);
bit key (unsigned char bitnum);

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
	
	//Flash sequence to test board at startup
    //checks the port and the timing.....good idea!!!
	PORTB = 0xff;
	delay_1s();
	PORTB = 0x00;
	
	//foreground program
	while(1)
	{
		while ( !(key(0)) && !(key(1)) );  //wait for any switch to be pressed
		
		if (key(0))
			count++;
		else
		{
			if (count != 0)
				count--;
		}
		PORTB = count;
		
		while ( key(0) || key(1) );   //wait for switches to be released
		
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

void delay_1s(void)
{
    unsigned char i;
    for (i=0;i<25;i++)
            __delay_ms(40);  //max value is 40 since this depends on the _delay() function which has a max number of cycles
    
}

/*******************************************
			Debounce
  This function debounces switch
********************************************/

bit key ( unsigned char bitnum ) 
{
	//local variables
    unsigned char count = 0 ;  
    unsigned char oldv, newv ;
    unsigned char mask_val;
    
    mask_val = 0x01 << bitnum;
    
    oldv = PORTA & mask_val ;
    while ( count < 2 ) {
        newv = PORTA & mask_val ;
        if ( oldv == newv ) {
            count++ ;
        }
        else {
            count = 0 ;
            oldv = newv ;
        }
    }
  
	if (oldv)   //true if oldv is non zero value
	  return 1;
	else
	  return 0;  
   
}    




