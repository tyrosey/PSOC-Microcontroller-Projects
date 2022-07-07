/*******************************************************************************
* File Name: REFRESH_ISR.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <REFRESH_ISR.h>
#include "cyapicallbacks.h"

#if !defined(REFRESH_ISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START REFRESH_ISR_intc` */

#include "project.h"
#include <stdio.h>
    
volatile int songCount;
volatile int screenCount;
volatile int levelCount;  
volatile int songPlay;
volatile int i;
volatile int letterPosition;
    
char display[17];
char letterCount[26][1] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char word1 [3][1] = {'D','O','G'};
char word2 [4][1] = {'C','A','K','E'};
char word3 [4][1] = {'F','I','R','E'};
char word4 [5][1] = {'T','I','G','E','R'};
char word5 [5][1] = {'C','A','N','D','Y'};
char word6 [6][1] = {'S','P','R','I','N','G'};
char word7 [6][1] = {'S','P','I','D','E','R'};
char word8 [7][1] = {'P','I','C','T','U','R','E'};
char word9 [8][1] = {'D','I','N','O','S','A','U','R'};
    
/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: REFRESH_ISR_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it. This function disables the interrupt, 
*  sets the default interrupt vector, sets the priority from the value in the
*  Design Wide Resources Interrupt Editor, then enables the interrupt to the 
*  interrupt controller.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void REFRESH_ISR_Start(void)
{
    /* For all we know the interrupt is active. */
    REFRESH_ISR_Disable();

    /* Set the ISR to point to the REFRESH_ISR Interrupt. */
    REFRESH_ISR_SetVector(&REFRESH_ISR_Interrupt);

    /* Set the priority. */
    REFRESH_ISR_SetPriority((uint8)REFRESH_ISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    REFRESH_ISR_Enable();
}


/*******************************************************************************
* Function Name: REFRESH_ISR_StartEx
********************************************************************************
*
* Summary:
*  Sets up the interrupt and enables it. This function disables the interrupt,
*  sets the interrupt vector based on the address passed in, sets the priority 
*  from the value in the Design Wide Resources Interrupt Editor, then enables 
*  the interrupt to the interrupt controller.
*  
*  When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*  used to provide consistent definition across compilers:
*  
*  Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*   Function prototype example:
*   CY_ISR_PROTO(MyISR);
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void REFRESH_ISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    REFRESH_ISR_Disable();

    /* Set the ISR to point to the REFRESH_ISR Interrupt. */
    REFRESH_ISR_SetVector(address);

    /* Set the priority. */
    REFRESH_ISR_SetPriority((uint8)REFRESH_ISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    REFRESH_ISR_Enable();
}


/*******************************************************************************
* Function Name: REFRESH_ISR_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void REFRESH_ISR_Stop(void)
{
    /* Disable this interrupt. */
    REFRESH_ISR_Disable();

    /* Set the ISR to point to the passive one. */
    REFRESH_ISR_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: REFRESH_ISR_Interrupt
*
*			 	BELOW IS THE ALTERED CODE FOR THE LCD REFRESH INTERRUPT 
*
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for REFRESH_ISR.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(REFRESH_ISR_Interrupt)
{
    #ifdef REFRESH_ISR_INTERRUPT_INTERRUPT_CALLBACK
        REFRESH_ISR_Interrupt_InterruptCallback();
    #endif /* REFRESH_ISR_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START REFRESH_ISR_Interrupt` */

    // Song Choice
    if (screenCount == 0) {
        
        // display Sweet Child O'Mine
        if (songCount == 0) {                     
            LCD_ClearDisplay();
            LCD_Position(1,0);
            LCD_PrintString("Sweet Child O'Mine");
            LCD_Position(0,1);
            LCD_PrintString("Choose a Song:");
        }
        
        // display Thunderstruck
        if (songCount == 1) {                   
            LCD_ClearDisplay();
            LCD_Position(1,0);
            LCD_PrintString(" Thunderstruck");
            LCD_Position(0,1);
            LCD_PrintString("Choose a Song:");
        }
        
        // display Crazy Train
        if (songCount == 2) {
            LCD_ClearDisplay();
            LCD_Position(1,0);
            LCD_PrintString("   Crazy Train");
            LCD_Position(0,1);
            LCD_PrintString("Choose a Song:");
        }
        
        // display Master of Puppets
        if (songCount == 3) {
            LCD_ClearDisplay();
            LCD_Position(1,0);
            LCD_PrintString("Master Of Puppets");
            LCD_Position(0,1);
            LCD_PrintString("Choose a Song:");
        }
        
        // display Walk This Way
        if (songCount == 4) {
            LCD_ClearDisplay();
            LCD_Position(1,0);
            LCD_PrintString(" Walk This Way");
            LCD_Position(0,1);
            LCD_PrintString("Choose a Song:");
        }
        
    }
    
    // Level Choice
    if (screenCount == 1) {
        
        // display Choose A Level: #
        LCD_ClearDisplay();
        LCD_Position(0,0);
        LCD_PrintString("<Choose a Level>");
        LCD_Position(1,4);
        snprintf(display, 17, "Level: %d", levelCount);
        LCD_PrintString(display);
    }
    
    // Display Hint
    if (screenCount == 2) {
        
        // display each hint (briefly) depending on which level was selected
        switch(levelCount) {
            case 1:
                LCD_ClearDisplay();
                LCD_Position(0,4);
                LCD_PrintString("A Popular");
                LCD_Position(1,4);
                LCD_PrintString("House Pet");
                CyDelay(3000);
                
                // Change to main game screen and begin playing backgruond music
                screenCount = 3;
                PWM_Start();
                songPlay = 1;
                
                break;
                
            case 2:
                LCD_ClearDisplay();
                LCD_Position(0,1);
                LCD_PrintString("Birthday Party");
                LCD_Position(1,4);
                LCD_PrintString("Dessert");
                CyDelay(3000);
                
                screenCount = 3;
                PWM_Start();
                songPlay = 1;
                
                break;
                
            case 3:
                LCD_ClearDisplay();
                LCD_Position(0,1);
                LCD_PrintString("VERY VERY VERY");
                LCD_Position(1,2);
                LCD_PrintString("HOT HOT HOT");
                CyDelay(3000);
                
                screenCount = 3;
                PWM_Start();
                songPlay = 1;
                
                break;
                
            case 4:
                LCD_ClearDisplay();
                LCD_Position(0,3);
                LCD_PrintString("A Big Cat");
                LCD_Position(1,2);
                LCD_PrintString("With Stripes");
                CyDelay(3000);
                
                screenCount = 3;
                PWM_Start();
                songPlay = 1;
                
                break;
                
            case 5:
                LCD_ClearDisplay();
                LCD_Position(0,2);
                LCD_PrintString("Sugary Sweet");
                LCD_Position(1,5);
                LCD_PrintString("Treats");
                CyDelay(3000);
                
                screenCount = 3;
                PWM_Start();
                songPlay = 1;
                
                break;
                
            case 6:
                LCD_ClearDisplay();
                LCD_Position(0,2);
                LCD_PrintString("Warm Season");
                LCD_Position(1,0);
                LCD_PrintString("Think 'Flowers'");
                CyDelay(3000);
                
                screenCount = 3;
                PWM_Start();
                songPlay = 1;
                
                break;
                
            case 7:
                LCD_ClearDisplay();
                LCD_Position(0,3);
                LCD_PrintString("Eight Legs");
                LCD_Position(1,3);
                LCD_PrintString("Many Eyes");
                CyDelay(3000);
                
                screenCount = 3;
                PWM_Start();
                songPlay = 1;
                
                break;
                
            case 8:
                LCD_ClearDisplay();
                LCD_Position(0,5);
                LCD_PrintString("Says A");
                LCD_Position(1,1);
                LCD_PrintString("Thousand Words");
                CyDelay(3000);
                
                screenCount = 3;
                PWM_Start();
                songPlay = 1;
                
                break;
                
            case 9:
                LCD_ClearDisplay();
                LCD_Position(0,1);
                LCD_PrintString("Lived Millions");
                LCD_Position(1,2);
                LCD_PrintString("Of Years Ago");
                CyDelay(3000);
                
                screenCount = 3;
                PWM_Start();
                songPlay = 1;
                
                break;
        }   
    }
    
    // Actual Level
    if (screenCount == 3) {
        
        // display the game depending on which level is selected
        switch(levelCount) {
            
            // level 1: DOG
            case 1:
                if (letterPosition == 0) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: ___");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, "First Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 1) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: D__");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 2) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: DO_");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 3) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: DOG");
                    LCD_Position(1,0);
                    LCD_PrintString("WINNER WINNER!!!");
                }
                
                break;
                
            // level 2: CAKE    
            case 2:
                if (letterPosition == 0) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: ____");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, "First Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 1) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: C___");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 2) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: CA__");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 3) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: CAK_");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 4) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: CAKE");
                    LCD_Position(1,0);
                    LCD_PrintString("WINNER WINNER!!!");
                }
                
                break;
            
            // level 3: FIRE    
            case 3:
              if (letterPosition == 0) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: ____");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, "First Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 1) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: F___");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 2) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: FI__");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 3) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: FIR_");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 4) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: FIRE");
                    LCD_Position(1,0);
                    LCD_PrintString("WINNER WINNER!!!");
                }
                
                break;
                
            // level 4: TIGER    
            case 4:
                if (letterPosition == 0) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: _____");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, "First Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 1) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: T____");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 2) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: TI___");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 3) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: TIG__");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 4) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: TIGE_");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 5) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: TIGER");
                    LCD_Position(1,0);
                    LCD_PrintString("WINNER WINNER!!!");
                }
                
                break;
                
            // level 5: CANDY    
            case 5:
                if (letterPosition == 0) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: _____");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, "First Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 1) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: C____");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 2) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: CA___");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 3) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: CAN__");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 4) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: CAND_");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 5) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: CANDY");
                    LCD_Position(1,0);
                    LCD_PrintString("WINNER WINNER!!!");
                }
                
                break;
                
            // level 6: SPRING    
            case 6:
                if (letterPosition == 0) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: ______");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, "First Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 1) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: S_____");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 2) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: SP____");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 3) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: SPR___");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 4) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: SPRI__");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 5) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: SPRIN_");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 6) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: SPRING");
                    LCD_Position(1,0);
                    LCD_PrintString("WINNER WINNER!!!");
                }
                
                break; 
                
            // level 7: SPIDER    
            case 7:
                if (letterPosition == 0) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: ______");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, "First Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 1) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: S_____");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 2) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: SP____");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 3) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: SPI___");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 4) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: SPID__");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 5) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: SPIDE_");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 6) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: SPIDER");
                    LCD_Position(1,0);
                    LCD_PrintString("WINNER WINNER!!!");
                }
                
                break;
                
            // level 8: PICTURE    
            case 8:
                if (letterPosition == 0) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: _______");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, "First Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 1) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: P______");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 2) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: PI_____");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 3) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: PIC____");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 4) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: PICT___");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 5) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: PICTU__");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 6) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: PICTUR_");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 7) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: PICTURE");
                    LCD_Position(1,0);
                    LCD_PrintString("WINNER WINNER!!!");
                }
                
                break; 
                
            // level 9: DINOSAUR    
            case 9:
                if (letterPosition == 0) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: ________");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, "First Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 1) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: D_______");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 2) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: DI______");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Next Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 3) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: DIN_____");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 4) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: DINO____");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 5) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: DINOS___");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 6) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: DINOSA__");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 7) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: DINOSAU_");
                    
                    LCD_Position(1,0);
                    snprintf(display, 17, " Last Letter:  %s", *letterCount + i);
                    LCD_PrintString(display);
                }
                else if (letterPosition == 8) {
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("Word: DINOSAUR");
                    LCD_Position(1,0);
                    LCD_PrintString("WINNER WINNER!!!");
                }
                
                break;    
        }
    }    
    
    // Losers Screen
    if (screenCount == 4) {
        LCD_ClearDisplay();
        LCD_Position(0,2);
        LCD_PrintString("AWE YOU LOST");
        LCD_Position(1,2);
        LCD_PrintString("PLAY AGAIN!!");
    }
    
    Refresh_Timer_ReadStatusRegister();                                              // clear interrupt
    /* `#END` */
}


/*******************************************************************************
* Function Name: REFRESH_ISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling REFRESH_ISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use REFRESH_ISR_StartEx instead.
* 
*   When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*   used to provide consistent definition across compilers:
*
*   Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*
*   Function prototype example:
*     CY_ISR_PROTO(MyISR);
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void REFRESH_ISR_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)REFRESH_ISR__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: REFRESH_ISR_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress REFRESH_ISR_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)REFRESH_ISR__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: REFRESH_ISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. 
*
*   Note calling REFRESH_ISR_Start or REFRESH_ISR_StartEx will 
*   override any effect this API would have had. This API should only be called
*   after REFRESH_ISR_Start or REFRESH_ISR_StartEx has been called. 
*   To set the initial priority for the component, use the Design-Wide Resources
*   Interrupt Editor.
*
*   Note This API has no effect on Non-maskable interrupt NMI).
*
* Parameters:
*   priority: Priority of the interrupt, 0 being the highest priority
*             PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*             PSoC 4: Priority is from 0 to 3.
*
* Return:
*   None
*
*******************************************************************************/
void REFRESH_ISR_SetPriority(uint8 priority)
{
    *REFRESH_ISR_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: REFRESH_ISR_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt, 0 being the highest priority
*    PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*    PSoC 4: Priority is from 0 to 3.
*
*******************************************************************************/
uint8 REFRESH_ISR_GetPriority(void)
{
    uint8 priority;


    priority = *REFRESH_ISR_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: REFRESH_ISR_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt to the interrupt controller. Do not call this function
*   unless ISR_Start() has been called or the functionality of the ISR_Start() 
*   function, which sets the vector and the priority, has been called.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void REFRESH_ISR_Enable(void)
{
    /* Enable the general interrupt. */
    *REFRESH_ISR_INTC_SET_EN = REFRESH_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: REFRESH_ISR_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 REFRESH_ISR_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*REFRESH_ISR_INTC_SET_EN & (uint32)REFRESH_ISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: REFRESH_ISR_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt in the interrupt controller.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void REFRESH_ISR_Disable(void)
{
    /* Disable the general interrupt. */
    *REFRESH_ISR_INTC_CLR_EN = REFRESH_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: REFRESH_ISR_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
* Side Effects:
*   If interrupts are enabled and the interrupt is set up properly, the ISR is
*   entered (depending on the priority of this interrupt and other pending 
*   interrupts).
*
*******************************************************************************/
void REFRESH_ISR_SetPending(void)
{
    *REFRESH_ISR_INTC_SET_PD = REFRESH_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: REFRESH_ISR_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt in the interrupt controller.
*
*   Note Some interrupt sources are clear-on-read and require the block 
*   interrupt/status register to be read/cleared with the appropriate block API 
*   (GPIO, UART, and so on). Otherwise the ISR will continue to remain in 
*   pending state even though the interrupt itself is cleared using this API.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void REFRESH_ISR_ClearPending(void)
{
    *REFRESH_ISR_INTC_CLR_PD = REFRESH_ISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
