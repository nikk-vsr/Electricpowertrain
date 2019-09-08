//Created by : nikhil Valiveti Batch 1 Employee ID 141708
// PD0 -> Engine input
// PC0 -> right motor speed
// PC1 -> left motor speed
// PC2 -> steering angle
// PC3 -> Yaw rate
// PD6  ->  Right motor PWM       PD6 OC0A
// PD5/PB3  -> left motor PWM     PD5 OC0B
#include"timer.h"
#include"ADC.h"
#include<stdlib.h>
#include<math.h>
#include"Hallsensor.h"
/******************************************************************************
*                      Global variables
******************************************************************************/


double Timer_count=0;
volatile uint8_t index_value=0;
double Final_value=0;

double h_speed=0;
double l_speed=0;
double r_dist=0;
double set_dist = 40;
double acc  = 0;
double p1=0;


/*******************************************************************************/
/*typedef struct
{
    volatile unsigned int BIT_FLAG:1;

}FLAG;
FLAG Engine_FLAG;
//Engine_FLAG.BIT_FLAG;*/
static int8_t absol(int8_t);

int main(void)
{   CLR_BIT(DDRD,PD0);
   /* SET_BIT(PORTD,PD0);     setting engine pin as input*/

    CLR_BIT(DDRD,PD1);     /* gear neutral*/
    /*SET_BIT(PORTD,PD1)*/

    CLR_BIT(DDRD,PD2);//Hall Sensor A Input signal
    CLR_BIT(DDRD,PD3);//Hall Sensor B Input signal
    CLR_BIT(DDRD,PD4);//Hall Sensor C Input signal


    SET_BIT(DDRD,PD7);//PWM signal for Switch S1 in Inverter circuit
    SET_BIT(DDRB,PB0);//PWM signal for Switch S2 in Inverter circuit
    SET_BIT(DDRB,PB1);//PWM signal for Switch S3 in Inverter circuit
    SET_BIT(DDRB,PB2);//PWM signal for Switch S4 in Inverter circuit
    SET_BIT(DDRB,PB3);//PWM signal for Switch S5 in Inverter circuit
    SET_BIT(DDRB,PB4);//PWM signal for Switch S6 in Inverter circuit




    /*CLR_BIT(EICRA,ISC01);
    SET_BIT(EICRA ,ISC00); //set logical change as interrupt for INT0*/

    SET_BIT(DDRD,PD5);   //set PD5 as output
    SET_BIT(DDRD,PD6);   // set PD6 as output
    SET_BIT(DDRB,PB5);    //set PB5 as output for understeer detection


    float steering_value;
    float yaw_rate;
    float Wheel_base=5.24; //5.24 m
    float Car_width=1.81;   //1.81m
    float Wheel_radius=0.40;  //40cm   ---12inches
    float P_Left_Error=0;  // change in speed of left motor
    float P_Right_Error=0;    // change in speed of right motor
    float motor_speed=0;
    //float Angular_velocity_wheel=0;
    float turning_radius=0;
    float Radius_turn= 3.0;
    float set_leftmotor_speed=0;
    float set_rightmotor_speed=0;     //range taken as 0-1000RPM , 0-104 rad/s
    float Angularvelocity_rightmotor=0;
    float Angularvelocity_leftmotor=0;
    InitADC();
    ENABLE_ADC();
    TIMER_init();
    timer_PWM_Init();
    double feature_select=0;
    //Enable_PWM();
    sei();
    //int x=0;
    //int y=0;
    //int flag=0;

    while(1)
    {
        //if((Engine_FLAG.BIT_FLAG )%2!=0)   // if engine is on then only check
       // if(flag%2 ==0)
       if((READ_BIT(PIND,PD0)) && READ_BIT(PIND,PD1) )

       //if((EIFR)==0x01)  // set the flag for the interrupt)
        {       Enable_PWM();
                channel_select(1);
                feature_select = (Read_ADC()*(5.0/1024.0));
                if (feature_select> 2.5)
                {
                    TIMSK0 |= (1<<TOIE0); // check it
                    if(index_value == 1)
                    {  channel_select(5);
                       l_speed = Read_ADC();
                       l_speed = ((25.0/1024.0)*l_speed);
                       channel_select(6);
                       r_dist = Read_ADC();
                       r_dist = ((100.0/1024.0)*r_dist);
                       channel_select(2);
                        h_speed = Read_ADC();
                        h_speed = ((25.0/1024.0)*h_speed);
                    if(h_speed > l_speed)
                    {
                        acc = ((l_speed - h_speed)*(l_speed - h_speed))/(2*(set_dist - r_dist));
                        acc = acc * (-1);
                    }
                    else if(h_speed < l_speed)
                    {
                        acc = ((r_dist - (h_speed*(set_dist/l_speed)))/((1/2)*(set_dist/l_speed)*(set_dist/l_speed)));
                    }

                    p1 = ((123 + (5.0*acc)/255.0)*100.0);
                    Fix_Right_PWM(p1);
                    Fix_Left_PWM(p1);

                    index_value=0;
                    }
                    switchesfun();
                }
                else
                {

                     channel_select(3);
                     steering_value=(-65.0+ ((Read_ADC()*(130.0))/1024.0));  /*-65 to +65 degrees are taken as range of steering angle*/
                                                                    /* 0-2.5v is left , 2.5-5V is right*/
                     channel_select(4);
                     yaw_rate=(-50.0+ ((Read_ADC()*(100.0))/1024.0));    /*-50 to  +50 to degree per sec taken as range*/

                     channel_select(2);
                     motor_speed=((Read_ADC()*(100.0))/(1024.0));    /*assuming it is given in rad/s*/
                     turning_radius= (Wheel_base/tan(abs(steering_value)));  //Radius of turn making by the car  (meters)

                     set_leftmotor_speed=  (absol(yaw_rate)*(turning_radius+(Car_width/2.0)));   //translational velocity   m/s
                     set_rightmotor_speed= (absol(yaw_rate)*(turning_radius-(Car_width/2.0)));   // m/s

                     if ((steering_value- (57.3*(Wheel_base/Radius_turn))-(0.5*(yaw_rate)*(yaw_rate)*Radius_turn))> 0)   /* check for under steer*/
                     {
                      CLR_BIT(PORTB,PB5);  //under steer is occurring
                     }
                    else
                    {
                      SET_BIT(PORTB,PB5);
                    }

                    Angularvelocity_rightmotor=(set_rightmotor_speed/ Wheel_radius);   // motor angular velocity rad/ s
                    Angularvelocity_leftmotor=(set_leftmotor_speed/ Wheel_radius);     // rad/s

                    P_Left_Error= (((motor_speed- Angularvelocity_leftmotor)/(motor_speed))*(100.0));
                    P_Right_Error= (((motor_speed- Angularvelocity_rightmotor)/(motor_speed))*(100.0));
                    Fix_Left_PWM(P_Left_Error);
                    Fix_Right_PWM(P_Right_Error);
                    switchesfun();
                }


        }
        else
        {
               TIMSK0 &= ~(1<<TOIE0);
               OCR0A = 0;
               Disable_PWM();
               CLR_BIT(PORTD,PD5);
               CLR_BIT(PORTD,PD6);
               CLR_BIT(PORTB,PB0);CLR_BIT(PORTB,PB1);CLR_BIT(PORTB,PB2);CLR_BIT(PORTB,PB3);CLR_BIT(PORTB,PB4) ;
        }
    }

    return 0;
}

static int8_t absol(int8_t val)
{
  if (val<0)
  {
    return (val*-1);
  }
  else
  {
    return val;
  }

}
//ISR(INT0_vect)
   //   {    cli();
           //Engine_FLAG.BIT_FLAG= Engine_FLAG.BIT_FLAG +1; /* set the flag for the interrupt*/
          //flag=flag+1;
   //        EIFR=0x01; // set the flag for the interrupt
   //        sei();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   ;
   //   }
