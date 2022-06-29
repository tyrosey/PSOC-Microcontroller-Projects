/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <string.h>
#include <stdio.h>

volatile unsigned char * PRT2_DR = (unsigned char *)0x40005120;
volatile unsigned char * PRT2_PS = (unsigned char *)0x40005121;
volatile unsigned char * PRT2_DM0 = (unsigned char *)0x40005122;
volatile unsigned char * PRT2_DM1 = (unsigned char *)0x40005123;
volatile unsigned char * PRT2_DM2 = (unsigned char *)0x40005124;

static const unsigned char LED_MASK = 0b00000010;
static const unsigned char SW_MASK = 0b00000100;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    //Port2 Pin in resistive pull mode
    *PRT2_DM0 = *PRT2_DM0 & ~SW_MASK;
    *PRT2_DM1 = *PRT2_DM1 | SW_MASK;
    *PRT2_DM2 = *PRT2_DM2 & SW_MASK;
    
    *PRT2_DR = *PRT2_DR | SW_MASK;
    
    //LED
    *PRT2_DM0 = *PRT2_DM0 & ~LED_MASK;
    *PRT2_DM1 = *PRT2_DM1 | LED_MASK;
    *PRT2_DM2 = *PRT2_DM2 | ~LED_MASK;
    
    
    for(;;)
    {
      /* Place your application code here. */
        while ((*PRT2_PS & SW_MASK));
        CyDelay(1);
        if ((*PRT2_PS & SW_MASK) == 0) {
            *PRT2_DR ^= LED_MASK;
    }   
        while ((*PRT2_PS & SW_MASK) == 0);
}}

/* [] END OF FILE */
