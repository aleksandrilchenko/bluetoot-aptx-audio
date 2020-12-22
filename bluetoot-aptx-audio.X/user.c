/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"

#define _XTAL_FREQ 4000000  // 4MHZ internal crystal
/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
 
    TRISIO = 0b00001001;  //  Gp0 input, rest all output   
    
    /* Setup analog functionality and port direction */
    
    ANSEL = 0b00010001;         //0x11 Clear Pin selection bits
    ADCON0 = 0b10000001;  //0x81 0b10000001 Turn on the A/D Converter ADFM and ADON
    CMCON = 0x07;         // Shut off the Comparator
    VRCON = 0x00;         // Shut off the Voltage Reference

    /* Initialize peripherals */

    /* Enable interrupts */
}

/* GetADCValue:
 * Gets the ADC value from GP0 , returns it as unsigned int 0-1023
 */
extern unsigned int GetADCValue()
{
    //ADCON0 &= 0b11110011;      // 0xf3 Clear Channel selection bits
    //ADCON0 |= 0b10000001;      //0x81 Select GP0 pin as ADC input CHS1:CHS0: to 11
    //ADON = 1;
    __delay_ms(10);      // Time for Acqusition capacitor to charge up and show correct value

	GO_nDONE  = 1;		 // Enable Go/Done

	while(GO_nDONE)    //wait for conversion completion
    __delay_ms(1);
    return ((ADRESH<<8)+ADRESL);   // Return 10 bit ADC value
}