/* ==========================================================================
 *
 * Tyler Rose
 * ECE -- Microcontrollers
 *
 * Project 3 Description:
 * 
 * Use Universal asynchronous receiver transmitters (UARTs) and Pulse-Width
 * Modulation (PWM) to generate different notes of a piano by pressing
 * different keys on the PC keyboard to transport the data throught the UART
 * and outputting to a speaker connected to the microcontroller.
 *
 * ==========================================================================
*/

#include "project.h"
#include "UART.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    UART_Start();   		// Start UART module
    RX_ISR_Start(); 		// Start RX_ISR module
    SleepTimer_Start(); 	// Start SleepTimer module
    SLEEP_ISR_Start();  	// Start SLEEP_ISR module
    
    char string[] = " Lab3 - UART Keyboard Piano! ---->  ";     // sets string to " Lab3 - UART Keyboard Piano! ---->  "
    
    UART_PutString(string);                     				// displays string 
    
    
    for(;;)
    {
        /* Place your application code here. */
        CyPmAltAct(PM_ALT_ACT_SRC_NONE, PM_ALT_ACT_SRC_INTERRUPT | PM_ALT_ACT_SRC_CTW );        // puts cpu in standby mode until RX_ISR wakes it up
        }
    }

/* [] END OF FILE */
