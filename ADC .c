
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


void InitADC()
{

// Select Vref=AVcc
  CLR_BIT(ADMUX,REFS1);
  CLR_BIT(ADMUX,REFS0);
  ADCSRA|= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //set pre-scaler to 128
}

double Read_ADC()
{   double ADC_value=0;
    ADCSRA|= (1<< ADSC);
     while(ADCSRA&(1<<ADSC));
        ADC_value=ADC;
      return ADC_value;
}


void channel_select(uint8_t i)
{   if (i==1)
   {
    ADMUX= 0b00000001;
   }


    if (i==2)
    {
     /*wheel speed of vehicle sensor ADC channel is selected*/
     //ADMUX=0x00;
     ADMUX= 0b00000010;

    }
    if (i==3)
    {
      /*Steering angle is selected*/
        //ADMUX=0x02;
         ADMUX= 0b00000011;
    }

    if (i==4)
    {
    /*Yaw rate is selected*/
    //ADMUX=0x03;
     ADMUX= 0b00000100;
    }
    if (i==5)
    {   /*lead speed*/
      ADMUX= 0b00000101;
    }
    if(i==6)
    {  /*relative distance*/
     ADMUX= 0b00000110;
    }

}


/******************************************************************************
*                      Internal functions
******************************************************************************/


/******************************************************************************
*                      End of File
******************************************************************************/
