/******************************************************************************
*                      Includes
******************************************************************************/
#include"ADC.h"
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

/******************************************************************************
*                      Public functions
******************************************************************************/
//Commutation Logic:It gives information about which coil in stator has to be energized and when it has to be energized.
        void switchesfun()
        {


        if(READ_BIT(PIND,PD2)&& ~READ_BIT(PIND,PD3)&& READ_BIT(PIND,PD4))//Checking Hall sensor inputs
        {
            SET_BIT(PORTD,PD7);CLR_BIT(PORTB,PB0);CLR_BIT(PORTB,PB1);SET_BIT(PORTB,PB2);CLR_BIT(PORTB,PB3);CLR_BIT(PORTB,PB4);
        }
        if(READ_BIT(PIND,PD2)&&~READ_BIT(PIND,PD3)&&~READ_BIT(PIND,PD4))//Checking Hall sensor inputs
        {
            SET_BIT(PORTD,PD7);CLR_BIT(PORTB,PB0);CLR_BIT(PORTB,PB1);CLR_BIT(PORTB,PB2);CLR_BIT(PORTB,PB3);SET_BIT(PORTB,PB4);
        }//PWM signals for Switch S1 and switch S6 are made HIGH

        if(READ_BIT(PIND,PD2)&&READ_BIT(PIND,PD3)&&~READ_BIT(PIND,PD4))//Checking Hall sensor inputs
        {
            CLR_BIT(PORTD,PD7);CLR_BIT(PORTB,PB0);SET_BIT(PORTB,PB1);CLR_BIT(PORTB,PB2);CLR_BIT(PORTB,PB3);SET_BIT(PORTB,PB4);
        }//PWM signals for Switch S3 and switch S6 are made HIGH

        if(~READ_BIT(PIND,PD2)&&READ_BIT(PIND,PD3)&&~READ_BIT(PIND,PD4))//Checking Hall sensor inputs
        {
            CLR_BIT(PORTD,PD7);SET_BIT(PORTB,PB0);SET_BIT(PORTB,PB1);CLR_BIT(PORTB,PB2);CLR_BIT(PORTB,PB3);CLR_BIT(PORTB,PB4);
        }//PWM signals for Switch S3 and switch S2 are made HIGH

        if(~READ_BIT(PIND,PD2)&&READ_BIT(PIND,PD3)&&READ_BIT(PIND,PD4))//Checking Hall sensor inputs
        {
            CLR_BIT(PORTD,PD7);SET_BIT(PORTB,PB0);CLR_BIT(PORTB,PB1);CLR_BIT(PORTB,PB2);SET_BIT(PORTB,PB3);CLR_BIT(PORTB,PB4);
        }//PWM signals for Switch S5 and switch S2 are made HIGH

        if(~READ_BIT(PIND,PD2)&&~READ_BIT(PIND,PD3)&&READ_BIT(PIND,PD4))//Checking Hall sensor inputs
        {
            CLR_BIT(PORTD,PD7);CLR_BIT(PORTB,PB0);CLR_BIT(PORTB,PB1);SET_BIT(PORTB,PB2);SET_BIT(PORTB,PB3);CLR_BIT(PORTB,PB4);
        }//PWM signals for Switch S5 and switch S4 are made HIGH


        if(READ_BIT(PIND,PD2)&&READ_BIT(PIND,PD3)&&READ_BIT(PIND,PD4))//Checking Hall sensor inputs
        {
            CLR_BIT(PORTD,PD7);CLR_BIT(PORTB,PB0);CLR_BIT(PORTB,PB1);CLR_BIT(PORTB,PB2);CLR_BIT(PORTB,PB3);CLR_BIT(PORTB,PB4);
        }

        if(~READ_BIT(PIND,PD2)&&~READ_BIT(PIND,PD3)&&~READ_BIT(PIND,PD4))//Checking Hall sensor inputs
        {
            CLR_BIT(PORTD,PD7);CLR_BIT(PORTB,PB0);CLR_BIT(PORTB,PB1);CLR_BIT(PORTB,PB2);CLR_BIT(PORTB,PB3);CLR_BIT(PORTB,PB4);
        }
        }
/******************************************************************************
*                      Internal functions
******************************************************************************/


/******************************************************************************
*                      End of File
******************************************************************************/
