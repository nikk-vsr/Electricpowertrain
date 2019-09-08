
/******************************************************************************
* File Name: timer.c
* Description:  Timer start and stop - function definition
* Tool-Chain: avr-gcc
*
*  Modification History:
*  Created by:      Utkarsh Bajpai    V1.0      08/Aug/19
*  Description:     V1.0
******************************************************************************/

/******************************************************************************
*                      Includes
******************************************************************************/

#include <avr/io.h>
#include "timer.h"
/******************************************************************************
*                      Defines and data types
******************************************************************************/

/******************************************************************************
*                      Global variables
******************************************************************************/

/******************************************************************************
*                      Static variables
******************************************************************************/


/******************************************************************************
*                      Internal function prototypes
******************************************************************************/

// code

/******************************************************************************
*                      Public functions
******************************************************************************/
/******************************************************************************
* Name: TCD_TemperatureType Tcd_CalcTemperature (void)
* Description:  Calculates the temperature using data from NTC in KELVIN
*  a)  Run time( typical ):  xx clock cycles
*  b)  Run time ( worst case ):  xx clock cycles
*
* Code Memory Used	: yy bytes	(ROM)
* Stack Used		: yy bytes	(RAM)
*
* Arguments: None
* Returns: TCD_TemperatureType - Temperature measured in KELVIN
******************************************************************************/

// code

/******************************************************************************
*                      Internal functions
******************************************************************************/
/******************************************************************************
* Name: uint16_t Binary_Search_u16 (uint16_t X_array[], uint16_t N,uint16_t Xin)
* Description:  Finds the index of the given input
*  a)  Run time( typical ):  xx clock cycles
*  b)  Run time ( worst case ):  xx clock cycles
*
* Code Memory Used	: yy bytes	(ROM)
* Stack Used		: yy bytes	(#include <avr/io.h>

******************************************************************************/



/******************************************************************************
* Name: Ifx_IntIpoCur_u16_s16(	uint16_t Xin,
*								uint16_t N,
*								uint16_t X_array[],
*								sint16_t Val_array[])
* Description:  interpolation library for calculating the temperature
*  a)  Run time( typical ):  xx clock cycles
*  b)  Run time ( worst case ):  xx clock cycles
*
* Code Memory Used	: yy bytes	(ROM)
* Stack Used		: yy bytes	(RAM)
******************************************************************************/
void TIMER_init()
{
    //SET_BIT(DDRD,PD7); //
    TCNT0 =0x00; // enables timer 0
    TCCR0A=0x00; //
    TCCR0B |= ((1<<CS00)|((1<<CS01)));
    //CLR_BIT(PORTD,PD7);
}


/******************************************************************************
*                      End of File
******************************************************************************/












