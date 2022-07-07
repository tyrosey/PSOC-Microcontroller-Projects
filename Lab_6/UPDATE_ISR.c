/*******************************************************************************
* File Name: UPDATE_ISR.c  
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
#include <UPDATE_ISR.h>
#include "cyapicallbacks.h"

#if !defined(UPDATE_ISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START UPDATE_ISR_intc` */
#include "project.h"
#include <stdio.h>

extern volatile int tolerance;
extern volatile int setTemp;
volatile int i;
volatile int j;

char display[17];
char mode[3][5] = {"OFF ","HEAT","COOL" };
char speed[4][5] = {"OFF","HI ","MED","LOW" };

extern volatile uint8 READ_TEMP;
uint8 tempArrayTwo[2];

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
* Function Name: UPDATE_ISR_Start
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
void UPDATE_ISR_Start(void)
{
    /* For all we know the interrupt is active. */
    UPDATE_ISR_Disable();

    /* Set the ISR to point to the UPDATE_ISR Interrupt. */
    UPDATE_ISR_SetVector(&UPDATE_ISR_Interrupt);

    /* Set the priority. */
    UPDATE_ISR_SetPriority((uint8)UPDATE_ISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    UPDATE_ISR_Enable();
}


/*******************************************************************************
* Function Name: UPDATE_ISR_StartEx
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
void UPDATE_ISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    UPDATE_ISR_Disable();

    /* Set the ISR to point to the UPDATE_ISR Interrupt. */
    UPDATE_ISR_SetVector(address);

    /* Set the priority. */
    UPDATE_ISR_SetPriority((uint8)UPDATE_ISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    UPDATE_ISR_Enable();
}


/*******************************************************************************
* Function Name: UPDATE_ISR_Stop
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
void UPDATE_ISR_Stop(void)
{
    /* Disable this interrupt. */
    UPDATE_ISR_Disable();

    /* Set the ISR to point to the passive one. */
    UPDATE_ISR_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: UPDATE_ISR_Interrupt
*
*			 	BELOW IS THE ALTERED CODE FOR THE UPDATE LCD INTERRUPT 
*
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for UPDATE_ISR.
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
CY_ISR(UPDATE_ISR_Interrupt)
{
    #ifdef UPDATE_ISR_INTERRUPT_INTERRUPT_CALLBACK
        UPDATE_ISR_Interrupt_InterruptCallback();
    #endif /* UPDATE_ISR_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START UPDATE_ISR_Interrupt` */
    
    
    // Getting the current temp from the I2C
    I2C_MasterWriteBuf(0x48, (uint8*)&READ_TEMP, 1, I2C_MODE_COMPLETE_XFER);
    while (!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
    I2C_MasterClearStatus();
    
    I2C_MasterReadBuf(0x48, tempArrayTwo, 2, I2C_MODE_COMPLETE_XFER);
    while (!(I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));
    I2C_MasterClearStatus();

    
    // Organazing and Displaying to LCD
    snprintf(display, 17, "SET:%d  %d S:%s", setTemp, tolerance, *speed+j);
    LCD_Position(1,0);
    LCD_PrintString(display);
    LCD_Position(1,7);
    LCD_PutChar(LCD_CUSTOM_0);
    
    if(tempArrayTwo[1] != 0){                                                       // if the temp has .5
        snprintf(display, 17, "TEMP:%d.5 M:%s", tempArrayTwo[0], *mode + i);
        LCD_Position(0,0);
        LCD_PrintString(display);
    }
    else{                                                                           // else the temp does not have .5
        snprintf(display, 17,"TEMP:%d.0 M:%s", tempArrayTwo[0], *mode + i);
        LCD_Position(0,0);
        LCD_PrintString(display);
    }
    
    Update_Timer_ReadStatusRegister();                                              // clear interrupt
    
    /* `#END` */
}


/*******************************************************************************
* Function Name: UPDATE_ISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling UPDATE_ISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use UPDATE_ISR_StartEx instead.
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
void UPDATE_ISR_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)UPDATE_ISR__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: UPDATE_ISR_GetVector
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
cyisraddress UPDATE_ISR_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)UPDATE_ISR__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: UPDATE_ISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. 
*
*   Note calling UPDATE_ISR_Start or UPDATE_ISR_StartEx will 
*   override any effect this API would have had. This API should only be called
*   after UPDATE_ISR_Start or UPDATE_ISR_StartEx has been called. 
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
void UPDATE_ISR_SetPriority(uint8 priority)
{
    *UPDATE_ISR_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: UPDATE_ISR_GetPriority
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
uint8 UPDATE_ISR_GetPriority(void)
{
    uint8 priority;


    priority = *UPDATE_ISR_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: UPDATE_ISR_Enable
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
void UPDATE_ISR_Enable(void)
{
    /* Enable the general interrupt. */
    *UPDATE_ISR_INTC_SET_EN = UPDATE_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: UPDATE_ISR_GetState
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
uint8 UPDATE_ISR_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*UPDATE_ISR_INTC_SET_EN & (uint32)UPDATE_ISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: UPDATE_ISR_Disable
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
void UPDATE_ISR_Disable(void)
{
    /* Disable the general interrupt. */
    *UPDATE_ISR_INTC_CLR_EN = UPDATE_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: UPDATE_ISR_SetPending
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
void UPDATE_ISR_SetPending(void)
{
    *UPDATE_ISR_INTC_SET_PD = UPDATE_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: UPDATE_ISR_ClearPending
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
void UPDATE_ISR_ClearPending(void)
{
    *UPDATE_ISR_INTC_CLR_PD = UPDATE_ISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
