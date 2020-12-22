/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "system.c"

/******************************************************************************/
/* User Global Variable Declaration                                           */
#define VOL_P GP1
#define VOL_M GP2
#define PLAY GP4
#define NEXT GP5
#define _XTAL_FREQ 4000000  // 4MHZ internal crystal

/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

// Divider is 10K/10K (x 0.5)
// VOL_P = 1.21V (0.6 V = 122.7 after divider)
// VOL_M = 0.1 V (0.05 V = 10 after divider)
// PLAY = 2.19 V (1.1 V = 225 after divider)
// NEXT = 3.8 V (1.9 V = 388.7 after divider)

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main()
{
    /* Configure the oscillator for the device */
    //ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
    
    unsigned int ADC_value = 0;


    while(1)
    {
    

        
    ADC_value = GetADCValue();

        if (ADC_value < 10) 
            {
            VOL_M = 0;
            __delay_ms(1);
            }
   else if (ADC_value > 110 && ADC_value < 130) 
            {
            VOL_P = 0; 
            __delay_ms(1);
            }
   else if (ADC_value > 210 && ADC_value < 240) 
            {
            PLAY = 0; 
            __delay_ms(1);
            }
   else if (ADC_value > 370 && ADC_value < 400) 
            {
            NEXT = 0;       
            __delay_ms(1);
            }     
   else
   {
    VOL_M = 1;
    VOL_P = 1;
    PLAY = 1;
    NEXT = 1;
    __delay_ms(1);   
    }
    }
}

