/**********************************************
	Tommy Gartlan April 2011
Car Park project using PIC18F4520 
LEDs connected to PORTB keep track of number of cars
SW0 connected to PORTA.0 is in gate sensor
SW1 connected to PORTA.1 is in gate sensor

 * CAR6
Demonstrates use of inline function
Look at the assembly to note the difference
between the way an inline functions is compiled as opposed a normal 
 * function

************************************************/

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
//void increase_cars(void);
void decrease_cars(void);

/*****************************************
				Macros
******************************************/
#define PARK_SIZE 20     //constant..ends up in program memory so doesn't use RAM

/*****************************************
 Global Variables
******************************************/
unsigned char car_count=0;






/****************************************
*  Inline Functions
*****************************************/

/****************************************
*  increase_cars
*  This function increases running number 
*  of cars and checks if car is full 
* This time it's an inline function
******************************************/

inline void increase_cars(void)
{
	if (car_count < PARK_SIZE)
		car_count ++;
}


/****************************************
*  Main Program
*****************************************/
void main(void)
{
	//unsigned char car_count = 0;
	Initial();
	
	//foreground program
	while(1)
	{
		
		while ( !(key(0)) && !(key(1)) );  //wait for any switch to be pressed
		
		if (key(0))
			increase_cars();
		else
			decrease_cars();
			
		LATB = car_count;
		
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
	LATB = 0x00;
    delay_1s();
    delay_1s();
    LATB = 0xFF;
    delay_1s();
    delay_1s();
    LATB = 0x00;
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


/****************************************
*  decrease_cars
*  This function decreases running number 
*  of cars and checks if car is full 
*****************************************
*/
void decrease_cars(void)
{
	if (car_count > 0)
		car_count --;


}


