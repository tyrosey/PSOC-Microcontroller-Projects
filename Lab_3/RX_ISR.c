/*******************************************************************************
* File Name: RX_ISR.c  
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
#include <RX_ISR.h>
#include "cyapicallbacks.h"

#if !defined(RX_ISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START RX_ISR_intc` */
#include "UART.h"
#include "PWM.h"
volatile int flag;    // declare flag
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
* Function Name: RX_ISR_Start
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
void RX_ISR_Start(void)
{
    /* For all we know the interrupt is active. */
    RX_ISR_Disable();

    /* Set the ISR to point to the RX_ISR Interrupt. */
    RX_ISR_SetVector(&RX_ISR_Interrupt);

    /* Set the priority. */
    RX_ISR_SetPriority((uint8)RX_ISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    RX_ISR_Enable();
}


/*******************************************************************************
* Function Name: RX_ISR_StartEx
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
void RX_ISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    RX_ISR_Disable();

    /* Set the ISR to point to the RX_ISR Interrupt. */
    RX_ISR_SetVector(address);

    /* Set the priority. */
    RX_ISR_SetPriority((uint8)RX_ISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    RX_ISR_Enable();
}


/*******************************************************************************
* Function Name: RX_ISR_Stop
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
void RX_ISR_Stop(void)
{
    /* Disable this interrupt. */
    RX_ISR_Disable();

    /* Set the ISR to point to the passive one. */
    RX_ISR_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: RX_ISR_Interrupt
*
*			 	BELOW IS THE ALTERED CODE FOR THE RX INTERRUPT 
*
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for RX_ISR.
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
CY_ISR(RX_ISR_Interrupt)
{
    #ifdef RX_ISR_INTERRUPT_INTERRUPT_CALLBACK
        RX_ISR_Interrupt_InterruptCallback();
    #endif /* RX_ISR_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START RX_ISR_Interrupt` */
    
    PWM_Start();        			// Start the PWM
    flag = 1;           			// Set the flag to 1
    char input = UART_GetChar();    // getting input form keyboard
    char error[] = " ~ERROR~ ";     // setting "error" to " ~ERROR~ " for when an invalid key is pressed
    
    
    // switch case statment for each keyboard button
    switch (input) {
        case 'z':                   // if 'z' is pressed
            PWM_WritePeriod(7634);  // set the period to 7634

            PWM_WriteCompare(3817); // set 50% duty cycle 
            UART_PutChar(input);    // display the character
            
            break;
        
        // This pattern repeats for each key and corresponding note's period and duty cycle    
            
        case 'x':
            PWM_WritePeriod(6802);

            PWM_WriteCompare(3401);
            UART_PutChar(input);
            
            break;
            
        case 'c':
            PWM_WritePeriod(6060);

            PWM_WriteCompare(3030);
            UART_PutChar(input);
            
            break;
            
        case 'v':
            PWM_WritePeriod(5727);

            PWM_WriteCompare(2864);
            UART_PutChar(input);
            
            break;
        
        case 'b':
            PWM_WritePeriod(5102);

            PWM_WriteCompare(2551);
            UART_PutChar(input);
            
            break;
            
        case 'n':
            PWM_WritePeriod(4545);

            PWM_WriteCompare(2273);
            UART_PutChar(input);
            
            break;    
            
        case 'm':
            PWM_WritePeriod(4048);

            PWM_WriteCompare(2024);
            UART_PutChar(input);
            
            break;
        
        case ',':
            PWM_WritePeriod(3822);

            PWM_WriteCompare(1911);
            UART_PutChar(input);
            
            break;
            
        case 'a':                       
            PWM_WritePeriod(3822);

            PWM_WriteCompare(1911);
            UART_PutChar(input);
            
            break;
            
        case 's':
            PWM_WritePeriod(3607);

            PWM_WriteCompare(1803);
            UART_PutChar(input);
            
            break;
            
        case 'd':
            PWM_WritePeriod(3406);

            PWM_WriteCompare(1703);
            UART_PutChar(input);
            
            break;
        
        case 'f':
            PWM_WritePeriod(3214);

            PWM_WriteCompare(1607);
            UART_PutChar(input);
            
            break;
            
            
        case 'g':
            PWM_WritePeriod(3033);

            PWM_WriteCompare(1517);
            UART_PutChar(input);
            
            break;
        
        case 'h':
            PWM_WritePeriod(2863);

            PWM_WriteCompare(1431);
            UART_PutChar(input);
            
            break;
            
        case 'j':
            PWM_WritePeriod(2702);

            PWM_WriteCompare(1351);
            UART_PutChar(input);
            
            break;        
            
        case 'k':
            PWM_WritePeriod(2551);

            PWM_WriteCompare(1275);
            UART_PutChar(input);
            
            break;    
            
        case 'q':
            PWM_WritePeriod(2407);

            PWM_WriteCompare(1203);
            UART_PutChar(input);
            
            break;
        
        case 'w':
            PWM_WritePeriod(2272);

            PWM_WriteCompare(1136);
            UART_PutChar(input);
            
            break;
            
        case 'e':
            PWM_WritePeriod(2145);

            PWM_WriteCompare(1072);
            UART_PutChar(input);
            
            break; 
            
        case 'r':
            PWM_WritePeriod(2024);

            PWM_WriteCompare(1012);
            UART_PutChar(input);
            
            break;
        
        case 't':                       
            PWM_WritePeriod(1911);

            PWM_WriteCompare(955);
            UART_PutChar(input);
            
            break;
            
        case 'y':
            PWM_WritePeriod(1275);

            PWM_WriteCompare(638);
            UART_PutChar(input);
            
            break;
            
        case 'u':
            PWM_WritePeriod(1136);

            PWM_WriteCompare(568);
            UART_PutChar(input);
            
            break;
        
        case 'i':
            PWM_WritePeriod(1012);

            PWM_WriteCompare(506);
            UART_PutChar(input);
            
            break;
            
        case 'o':
            PWM_WritePeriod(956);

            PWM_WriteCompare(478);
            UART_PutChar(input);
            
            break;        
           
        default:            // default case
            PWM_Stop();     // stop the PWM
            
            UART_PutString(error); // display th error message
            
            break;
            
    }
         
    /* `#END` */
}


/*******************************************************************************
* Function Name: RX_ISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling RX_ISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use RX_ISR_StartEx instead.
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
void RX_ISR_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)RX_ISR__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: RX_ISR_GetVector
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
cyisraddress RX_ISR_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)RX_ISR__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: RX_ISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. 
*
*   Note calling RX_ISR_Start or RX_ISR_StartEx will 
*   override any effect this API would have had. This API should only be called
*   after RX_ISR_Start or RX_ISR_StartEx has been called. 
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
void RX_ISR_SetPriority(uint8 priority)
{
    *RX_ISR_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: RX_ISR_GetPriority
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
uint8 RX_ISR_GetPriority(void)
{
    uint8 priority;


    priority = *RX_ISR_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: RX_ISR_Enable
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
void RX_ISR_Enable(void)
{
    /* Enable the general interrupt. */
    *RX_ISR_INTC_SET_EN = RX_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: RX_ISR_GetState
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
uint8 RX_ISR_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*RX_ISR_INTC_SET_EN & (uint32)RX_ISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: RX_ISR_Disable
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
void RX_ISR_Disable(void)
{
    /* Disable the general interrupt. */
    *RX_ISR_INTC_CLR_EN = RX_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: RX_ISR_SetPending
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
void RX_ISR_SetPending(void)
{
    *RX_ISR_INTC_SET_PD = RX_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: RX_ISR_ClearPending
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
void RX_ISR_ClearPending(void)
{
    *RX_ISR_INTC_CLR_PD = RX_ISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
