/*******************************************************************************
* File Name: MODE_ISR.c  
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
#include <MODE_ISR.h>
#include "cyapicallbacks.h"

#if !defined(MODE_ISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START MODE_ISR_intc` */
#include "project.h"    
#include "MODE.h"
#include "MOTOR.h"
#include "MOTOR_ISR.h"
#include "Motor_Timer.h"
#include "Tout.h"
#include "TOUT_ISR.h"
    
extern volatile int i;
extern volatile int j;
extern volatile int speedCount;
extern volatile int motorCount;
volatile int modeCount;    
  
extern volatile uint8 ACCESS_CR;
uint8 tempArrayOne[3];
 
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
* Function Name: MODE_ISR_Start
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
void MODE_ISR_Start(void)
{
    /* For all we know the interrupt is active. */
    MODE_ISR_Disable();

    /* Set the ISR to point to the MODE_ISR Interrupt. */
    MODE_ISR_SetVector(&MODE_ISR_Interrupt);

    /* Set the priority. */
    MODE_ISR_SetPriority((uint8)MODE_ISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    MODE_ISR_Enable();
}


/*******************************************************************************
* Function Name: MODE_ISR_StartEx
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
void MODE_ISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    MODE_ISR_Disable();

    /* Set the ISR to point to the MODE_ISR Interrupt. */
    MODE_ISR_SetVector(address);

    /* Set the priority. */
    MODE_ISR_SetPriority((uint8)MODE_ISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    MODE_ISR_Enable();
}


/*******************************************************************************
* Function Name: MODE_ISR_Stop
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
void MODE_ISR_Stop(void)
{
    /* Disable this interrupt. */
    MODE_ISR_Disable();

    /* Set the ISR to point to the passive one. */
    MODE_ISR_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: MODE_ISR_Interrupt
*
*			 	BELOW IS THE ALTERED CODE FOR THE MODE INTERRUPT 
*
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for MODE_ISR.
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
CY_ISR(MODE_ISR_Interrupt)
{
    #ifdef MODE_ISR_INTERRUPT_INTERRUPT_CALLBACK
        MODE_ISR_Interrupt_InterruptCallback();
    #endif /* MODE_ISR_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START MODE_ISR_Interrupt` */
    
    
    if (MODE_Read() == 1) {             // if mode button is pressed
        
        if (modeCount == 0) {           // if modeCount is zero
            SPEED_ISR_Start();          // start speed ISR
            motorCount = 4;             // sets the switch motor case to heat cycle (ccw)
            i = 5;                      // set i to 5th position of mode array (Heat)
            modeCount = 1;              // increment modeCount
            
            TOUT_ISR_Start();           // enable Tout ISR
            
            tempArrayOne[0] = ACCESS_CR;                                                // sets beginning byte of array to 0xAC Access Configure command
            tempArrayOne[1] = 0x00;                                                     // Polarity bit set to 'low'
            I2C_MasterWriteBuf(0x48, tempArrayOne, 2, I2C_MODE_COMPLETE_XFER);          // I2C write command
            while (!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));                         // I2C status
            I2C_MasterClearStatus();                                                    // clears I2C
            
            if(Tout_Read() == 0) {  // if tout is not beyond the threshold
                j = 0;              // set j to 0 position of speed array (off)
                SPEED_ISR_Stop();   // stop speed ISR
            }
            
            if(Tout_Read()==1) {    // if Tout past the threshold
                MOTOR_ISR_Start();  // turn motor ISR on
            }
        }
        
        else if (modeCount == 1) {      // COOL mode
            SPEED_ISR_Start();          // start speed ISR
            motorCount = 0;             // sets the switch motor case to cool cycle (cw)
            i = 10;                     // set i to 10th position of mode array (Heat)
            modeCount = 2;              // increment modeCount
                
            TOUT_ISR_Start();           // turn Tout ISR on
            
            tempArrayOne[0] = ACCESS_CR;                                                     // sets beginning byte of array to 0xAC Access Configure command
            tempArrayOne[1] = 0x02;                                                          // Polarity bit set to 'high'
            I2C_MasterWriteBuf(0x48, tempArrayOne, 2, I2C_MODE_COMPLETE_XFER);               // I2C write command
            while (!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));                              // I2C status
            I2C_MasterClearStatus();                                                         // clears I2C 
            
            if(Tout_Read() == 0) {  // if tout is not beyond the threshold
                j = 0;              // set j to 0 position of speed array (off)
                SPEED_ISR_Stop();   // stop speed ISR
            }
            
            if(Tout_Read()==1) {    // if Tout past the threshold
                MOTOR_ISR_Start();  // turn motor ISR on
            }
        }
        
        else if (modeCount == 2) {      // OFF mode
            i = 0;                      // set i to 0 position of mode array (off)
            j = 0;                      // set j to 0 position of mode array (off)
            modeCount = 0;              // reset modeCount to zero
            speedCount = 0;             // reset speedCount to zero
            Motor_Timer_WritePeriod(0); // turn off motor timer
            TOUT_ISR_Stop();            // stop Tout ISR
            MOTOR_ISR_Stop();           // stop motor ISR
            SPEED_ISR_Stop();           // stop speed ISR
            MOTOR_Write(0);             // turn off motor    
        }
        
    }
    
    /* `#END` */
}


/*******************************************************************************
* Function Name: MODE_ISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling MODE_ISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use MODE_ISR_StartEx instead.
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
void MODE_ISR_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)MODE_ISR__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: MODE_ISR_GetVector
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
cyisraddress MODE_ISR_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)MODE_ISR__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: MODE_ISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. 
*
*   Note calling MODE_ISR_Start or MODE_ISR_StartEx will 
*   override any effect this API would have had. This API should only be called
*   after MODE_ISR_Start or MODE_ISR_StartEx has been called. 
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
void MODE_ISR_SetPriority(uint8 priority)
{
    *MODE_ISR_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: MODE_ISR_GetPriority
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
uint8 MODE_ISR_GetPriority(void)
{
    uint8 priority;


    priority = *MODE_ISR_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: MODE_ISR_Enable
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
void MODE_ISR_Enable(void)
{
    /* Enable the general interrupt. */
    *MODE_ISR_INTC_SET_EN = MODE_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: MODE_ISR_GetState
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
uint8 MODE_ISR_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*MODE_ISR_INTC_SET_EN & (uint32)MODE_ISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: MODE_ISR_Disable
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
void MODE_ISR_Disable(void)
{
    /* Disable the general interrupt. */
    *MODE_ISR_INTC_CLR_EN = MODE_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: MODE_ISR_SetPending
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
void MODE_ISR_SetPending(void)
{
    *MODE_ISR_INTC_SET_PD = MODE_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: MODE_ISR_ClearPending
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
void MODE_ISR_ClearPending(void)
{
    *MODE_ISR_INTC_CLR_PD = MODE_ISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
