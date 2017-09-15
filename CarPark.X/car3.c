/**************************************************
	Tommy Gartlan September 2011
Car Park project using PIC16F877A 
LEDs connected to PORTB keep track of number of cars
SW0 connected to PORTA.0 is in gate sensor
SW1 connected to PORTA.1 is out gate sensor

 * CAR 3 
Add a function to software 'debounce' the key
***************************************************/

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
bit key ();

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
		while (!(key()));  //wait for switch to be pushed
		count++;
		while (key());   //wait for switch to be released
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
}


/*******************************************
			Debounce
  This function debounces switch
********************************************/

bit key () 
{
	//local variables
    unsigned char count = 0 ;  
    unsigned char oldv, newv ;
    
    
    oldv = PORTAbits.RA0 ;        //Not very versatile since tied to pin 0 of porta
    while ( count < 20 ) {
        newv = PORTAbits.RA0 ;
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


void delay_1s(void)
{
    unsigned char i;
    for (i=0;i<25;i++)
            __delay_ms(40);  //max value is 40 since this depends on the _delay() function which has a max number of cycles
    
}

