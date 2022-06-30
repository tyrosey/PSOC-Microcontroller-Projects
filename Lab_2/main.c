/* ==========================================================================
 *
 * Tyler Rose
 * ECE -- Microcontrollers
 *
 * Project 2.A Description:
 * 
 * Use the process of interrupts to read a button as input and toggle an LED
 * whenever the button is pushed.
 *
 * ==========================================================================
*/

#include "project.h"

volatile int flag;          // Declare volatile int


int main(void) {
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    flag = 0;               			// Set flag to zero
    SW1_ISR_Start();        			// Start SW1 module
    
    for(;;) {                 			// Infinite loop
        if (flag != 0) {    			// Checks if the button has been pressed
            flag = 0;          			// Resets the flag interrupt
            LED_Write(~LED_Read());     // Toggles the LED
        }    
    }
}

/* [] END OF FILE */



