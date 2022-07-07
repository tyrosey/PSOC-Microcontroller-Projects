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
#include <stdio.h>

#if !defined(REFRESH_ISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START REFRESH_ISR_intc` */
#include "project.h"
#include "PWM.h"
#include "Refresh_Timer.h"
#include "LCD.h"
#include "Control.h"
 
char hero = LCD_CUSTOM_1;    
volatile int posCharacter;
    
int levelCount = 0;
char level[] = "Level";
char displayLevels[17];

int lifeCount = 3;
char lives[] = "Lives:";
char displayLives[17];

char winner[] = "  WINNER!!!";
char loser[] = " You Lost!";
char restart[] = "Hit Restart";

int count = 0; 
int posTop = 17;
int posBottom = 17;

char trackOne[19] = {'X',' ',' ',' ',' ','X','X',' ',' ',' ',' ',' ',' ','X','X','X',' ',' ',' '};
char trackTwo[19] = {' ',' ',' ','X',' ',' ',' ',' ',' ','X',' ','X',' ',' ',' ',' ',' ','X','X'};
char trackThree[19] = {' ',' ','X',' ',' ',' ',' ',' ','X','X',' ',' ',' ',' ',' ','X',' ',' ',' '};
char trackFour[19] = {'X',' ',' ',' ',' ','X','X',' ',' ',' ',' ',' ','X','X',' ',' ',' ','X','X'};
char trackFive[19] = {' ',' ',' ','X','X','X',' ',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X'};
char trackSix[19] = {'X','X',' ',' ',' ',' ',' ','X','X',' ',' ',' ','X','X',' ',' ','X',' ',' '};
char trackSeven[19] = {' ',' ',' ',' ','X',' ',' ',' ','X',' ',' ',' ',' ','X','X','X',' ',' ',' '};
char trackEight[19] = {'X','X','X',' ',' ',' ','X',' ',' ',' ',' ','X',' ',' ',' ',' ',' ','X','X'};
char trackNine[19] = {' ',' ',' ','X','X',' ',' ',' ',' ',' ',' ','X','X','X',' ',' ',' ','X','X'};
char trackTen[19] = {'X',' ',' ',' ',' ',' ',' ','X','X',' ',' ',' ',' ',' ',' ','X',' ',' ',' '};
    
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
*			 	BELOW IS THE ALTERED CODE FOR THE REFRESH INTERRUPT 
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
    
    CONTROL_ISR_Start();

    // Displays and Scrolls level 1 and life count across LCD
    
    if (levelCount == 0) {      
        levelCount = 1;
        Refresh_Timer_WritePeriod(400);         // changes speed of scrolling
        posTop--;                       		// increments to implement scrolling on top
        posBottom--;                    		// decrements to implement scrolling on bottom
        LCD_ClearDisplay();						// clear LCD
        LCD_Position(0,posTop);         		// position LCD
        snprintf(displayLevels, 17, "%s %d          \n", level , levelCount);   // organizes display 
        LCD_PrintString(displayLevels);
        LCD_Position(1,posBottom);
        snprintf(displayLives, 17, "%s %d          \n", lives , lifeCount);
        LCD_PrintString(displayLives);
        levelCount = 0;                     	// sets count back to zero for the loop to continue
        LCD_Position(posCharacter,0);       	// sets position for character guy
        LCD_PutChar(LCD_CUSTOM_0);          	// displays character guy
        
        
        // starts screen scrolling over if LCD has reached the end
        if(posTop == 1) {                   
            posTop = 17;
            posBottom = 17;
            levelCount++;
        }    
    }
    
    // LEVEl 1 begins
	if (levelCount == 1) {
		
		// begin scrolling first track
		Refresh_Timer_WritePeriod(900);                  
		posTop--;
		posBottom--;
		LCD_ClearDisplay();
		LCD_Position(0,posTop);
		LCD_PrintString(trackOne);
		LCD_Position(1,posBottom);
		LCD_PrintString(trackTwo);
		count++;
		LCD_Position(posCharacter,0);
		LCD_PutChar(LCD_CUSTOM_0);
		
		// checks for collisons on top row
		if (posCharacter == 0 && posTop == 0 && trackOne[0] =='X' ) {     
			if (trackOne[0] == 'X') {
				lifeCount--;  	// decrement life if collison has ocurred
			}
		}
		
		// checks for collisons on bottom row
		if (posCharacter == 1 && posBottom == 0) {  
			if (trackTwo[0] == 'X') {
				lifeCount--;  	// decrement life if collison has ocurred
			}
		}
		
		// checks if any lives are left
		if (lifeCount == 0) {                       
			levelCount = 11;  	// sets level to 11 for losers screen
		}
		
		// shifts array elements by 1 to the left when the end of the lcd has been reached to continue scrolling   
		if (posTop == 0) {
			memmove(trackOne, trackOne+1, strlen(trackOne));
			memmove(trackTwo, trackTwo+1, strlen(trackTwo));
			posTop = 1;
			posBottom = 1;
		}
	
		//checks if all elements of array have been scrolled across the screen completely, resets positions and count for next level
		if (count == (sizeof(trackOne)/sizeof(trackOne[0])) + 17) {
			levelCount++;
			posTop = 17;
			posBottom = 17;
			count = 0;
		}
	}
    
    // Displays and Scrolls level 2 and life count across LCD    
    if (levelCount == 2) {
        Refresh_Timer_WritePeriod(400);
        posTop--;
        posBottom--;
        LCD_ClearDisplay();
        LCD_Position(0,posTop);
        snprintf(displayLevels, 17, "%s %d          \n", level , levelCount);
        LCD_PrintString(displayLevels);
        LCD_Position(1,posBottom);
        snprintf(displayLives, 17, "%s %d          \n", lives , lifeCount);
        LCD_PrintString(displayLives);
        LCD_Position(posCharacter,0);
        LCD_PutChar(LCD_CUSTOM_0);
        
        if(posTop == 1) {
            posTop = 17;
            posBottom = 17;
            levelCount++;
        }    
    }
    
    //LEVEL 2 begins
	if (levelCount == 3) {
		
		Refresh_Timer_WritePeriod(800);
		posTop--;
		posBottom--;
		LCD_ClearDisplay();
		LCD_Position(0,posTop);
		LCD_PrintString(trackThree);
		LCD_Position(1,posBottom);
		LCD_PrintString(trackFour);
		count++;
		LCD_Position(posCharacter,0);
		LCD_PutChar(LCD_CUSTOM_0);
		
		if (posCharacter == 0 && posTop == 0) {
			if (trackThree[0] == 'X') {
				lifeCount--;
			}
		}
		if (posCharacter == 1 && posBottom == 0) {
			if (trackFour[0] == 'X') {
				lifeCount--;
			}
		}
		if (lifeCount == 0) {
			levelCount = 11;
		}
 
		if (posTop == 0) {
			memmove(trackThree, trackThree+1, strlen(trackThree));
			memmove(trackFour, trackFour+1, strlen(trackFour));
			posTop = 1;
			posBottom = 1;
		}
	

		if (count == (sizeof(trackThree)/sizeof(trackThree[0])) + 17) {
			levelCount++;
			posTop = 17;
			posBottom = 17;
			count = 0;
		}
	}
        
    // Displays and Scrolls level 3 and life count across LCD      
    if (levelCount == 4) {
        levelCount = 3;    
        Refresh_Timer_WritePeriod(400);
        posTop--;
        posBottom--;
        LCD_ClearDisplay();
        LCD_Position(0,posTop);
        snprintf(displayLevels, 17, "%s %d          \n", level , levelCount);
        LCD_PrintString(displayLevels);
        LCD_Position(1,posBottom);
        snprintf(displayLives, 17, "%s %d          \n", lives , lifeCount);
        LCD_PrintString(displayLives);
        levelCount = 4;
        LCD_Position(posCharacter,0);
        LCD_PutChar(LCD_CUSTOM_0);
        
        if(posTop == 1) {
            posTop = 17;
            posBottom = 17;
            levelCount = 5;
        }    
    }    

    
    //LEVEL 3 begins
	if (levelCount == 5) {
		
		Refresh_Timer_WritePeriod(600);
		posTop--;
		posBottom--;
		LCD_ClearDisplay();
		LCD_Position(0,posTop);
		LCD_PrintString(trackFive);
		LCD_Position(1,posBottom);
		LCD_PrintString(trackSix);
		count++;
		LCD_Position(posCharacter,0);
		LCD_PutChar(LCD_CUSTOM_0);
		
		if (posCharacter == 0 && posTop == 0) {
			if (trackFive[0] == 'X') {
				lifeCount--;
			}
		}
		if (posCharacter == 1 && posBottom == 0) {
			if (trackSix[0] == 'X') {
				lifeCount--;
			}
		}
		if (lifeCount == 0) {
			levelCount = 11;
		}
 
		if (posTop == 0) {
			memmove(trackFive, trackFive+1, strlen(trackFive));
			memmove(trackSix, trackSix+1, strlen(trackSix));
			posTop = 1;
			posBottom = 1;
		}
	

		if (count == (sizeof(trackFive)/sizeof(trackFive[0])) + 17) {
			levelCount++;
			posTop = 17;
			posBottom = 17;
			count = 0;
		}
	}

    // Displays and Scrolls level 4 and life count across LCD   
        
    if (levelCount == 6) {
        levelCount = 4;
        Refresh_Timer_WritePeriod(400);
        posTop--;
        posBottom--;
        LCD_ClearDisplay();
        LCD_Position(0,posTop);
        snprintf(displayLevels, 17, "%s %d          \n", level , levelCount);
        LCD_PrintString(displayLevels);
        LCD_Position(1,posBottom);
        snprintf(displayLives, 17, "%s %d          \n", lives , lifeCount);
        LCD_PrintString(displayLives);
        levelCount = 6;
        LCD_Position(posCharacter,0);
        LCD_PutChar(LCD_CUSTOM_0);
        
        if(posTop == 1) {
            posTop = 17;
            posBottom = 17;
            levelCount = 7;
        }    
    }

    
    //LEVEL 4 begins
	if (levelCount == 7) {
		
		Refresh_Timer_WritePeriod(400);
		posTop--;
		posBottom--;
		LCD_ClearDisplay();
		LCD_Position(0,posTop);
		LCD_PrintString(trackSeven);
		LCD_Position(1,posBottom);
		LCD_PrintString(trackEight);
		count++;
		LCD_Position(posCharacter,0);
		LCD_PutChar(LCD_CUSTOM_0);
		
		if (posCharacter == 0 && posTop == 0) {
			if (trackSeven[0] == 'X') {
				lifeCount--;
			}
		}
		if (posCharacter == 1 && posBottom == 0) {
			if (trackEight[0] == 'X') {
				lifeCount--;
			}
		}
		if (lifeCount == 0) {
			levelCount = 11;
		}
 
		if (posTop == 0) {
			memmove(trackSeven, trackSeven+1, strlen(trackSeven));
			memmove(trackEight, trackEight+1, strlen(trackEight));
			posTop = 1;
			posBottom = 1;
		}
	

		if (count == (sizeof(trackSeven)/sizeof(trackSeven[0])) + 17) {
			levelCount++;
			posTop = 17;
			posBottom = 17;
			count = 0;
		}
	}

    // Displays and Scrolls level 5 and life count across LCD    
        
    if (levelCount == 8) {
        levelCount = 5;
        Refresh_Timer_WritePeriod(400);
        posTop--;
        posBottom--;
        LCD_ClearDisplay();
        LCD_Position(0,posTop);
        snprintf(displayLevels, 17, "%s %d          \n", level , levelCount);
        LCD_PrintString(displayLevels);
        LCD_Position(1,posBottom);
        snprintf(displayLives, 17, "%s %d          \n", lives , lifeCount);
        LCD_PrintString(displayLives);
        levelCount = 8;
        LCD_Position(posCharacter,0);
        LCD_PutChar(LCD_CUSTOM_0);
        
        if(posTop == 1) {
            posTop = 17;
            posBottom = 17;
            levelCount = 9;
        }    
    }    
       
    
    //LEVEL 5 begins
	if (levelCount == 9) {
		
		Refresh_Timer_WritePeriod(200);
		posTop--;
		posBottom--;
		LCD_ClearDisplay();
		LCD_Position(0,posTop);
		LCD_PrintString(trackNine);
		LCD_Position(1,posBottom);
		LCD_PrintString(trackTen);
		count++;
		LCD_Position(posCharacter,0);
		LCD_PutChar(LCD_CUSTOM_0);
		
		if (posCharacter == 0 && posTop == 0) {
			if (trackNine[0] == 'X') {
				lifeCount--;
			}
		}
		if (posCharacter == 1 && posBottom == 0) {
			if (trackTen[0] == 'X') {
				lifeCount--;
			}
		if (lifeCount == 0) {
			levelCount = 11;
		}
		}
 
		if (posTop == 0) {
			memmove(trackNine, trackNine+1, strlen(trackNine));
			memmove(trackTen, trackTen+1, strlen(trackTen));
			posTop = 1;
			posBottom = 1;
		}  
	
	
		if (count == (sizeof(trackNine)/sizeof(trackNine[0])) + 17) {
			count = 0;
			levelCount = 10;
			posTop = 16;
			posBottom = 16;
		}
	}
        
    // WINNING SCREEN scrolls repeatedly if all levels are beaten  
    if (levelCount == 10) {
        Refresh_Timer_WritePeriod(400);
        posTop--;
        posBottom--;
        LCD_ClearDisplay();
        LCD_Position(0,posTop);
        LCD_PrintString(winner);
        LCD_Position(1,posBottom);
        LCD_PrintString(restart);
        LCD_Position(posCharacter,0);
        LCD_PutChar(LCD_CUSTOM_0);
                
        if (posTop == 1) {
            posTop = 16;
        }
        if (posBottom == 1) {
            posBottom = 16;
        }      
    }
    
    // LOSING SCREEN scrolls repeatedly if all lives are lost before end of game
    if (levelCount == 11) {
        levelCount = 12;
        posTop = 17;
        posBottom = 17;
    }
	
    if (levelCount == 12) {
        Refresh_Timer_WritePeriod(400);
        posTop--;
        posBottom--;
        LCD_ClearDisplay();
        LCD_Position(0,posTop);
        LCD_PrintString(loser);
        LCD_Position(1,posBottom);
        LCD_PrintString(restart);
                
        if (posTop == 1) {
            posTop = 16;
        }
		
        if (posBottom == 1) {
            posBottom = 16;
        }      
    }
   
    Refresh_Timer_ReadStatusRegister();
    
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
