/* ==========================================================================
 *
 * Tyler Rose
 * ECE -- Microcontrollers
 *
 * Project 2.B Description:
 * 
 * Use the process of interrupts to detect the rotation of a rotary encoder
 * to act as a volume control that outputs to an LCD display. 
 * CW increases, CCW decreases.
 *
 * ==========================================================================
*/
#include "project.h"

volatile int increment;                                                 // Declare increment flag
volatile int decrement;                                                 // Declare decrement flag



int main(void) {
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    LCD_Start();                                                        	// Start LCD module
    ENC_ISR_Start();                                                    	// Start ENC_ISR module
    
    
    LCD_Position(0,5);                                                  	// Position LCD to top row, after space 5
    LCD_PrintString("Volume");                                          	// Print Volume
    
    uint16 count = 50;                                                  	// Initialize count to 50
    
    LCD_Position(1,7);                                                  	// Position LCD to top row, after space 2
    LCD_PrintNumber(count);                                             	// Display the current count
    
    for(;;) {                                                           	// Infinite loop 
    /*  Place your application code here. */
   
		// If encoder is twisted cw (increase)    
		if (increment == 1) {                                               // Read what direction encoder is twisted
			if (count <100) {                                               // Check if count is less than 100
				count++;                                                    // Increment count     
		
				LCD_ClearDisplay();                                         // Clear the display
				LCD_Position(0,5);                                          // Position LCD to top row, after space 5
				LCD_PrintString("Volume");                                  // Display "Volume"
		
				LCD_Position(1,7);                                          // Position LCD to top row, after space 7
				LCD_PrintNumber(count);                                     // Display the current count
		
				ncrement = 0;                                               // Reset flag to 0
			}
		
			if (count == 100) {                                             // Checking if the count is 100 
				LCD_ClearDisplay();                                         // Clear display
				LCD_Position(0,3);                                          // Position LCD to top row after space 3
				LCD_PrintString("Max Volume");                              // Print "Max Volume"
				
				CyDelay(1000);                                              // Delay
				
				LCD_ClearDisplay();                                         // Clear display
				LCD_Position(0,5);                                          // Position LCD to top row, after space 5 
				LCD_PrintString("Volume");                                  // Display "Volume"
				
				LCD_Position(1,7);                                          // Position LCD to bottom row, after space 7
				LCD_PrintNumber(count);                                     // Display the current number count
				
				increment  = 0;                                             // Reset flag to 0
			}
		}
    
    // If encoder is twisted to left (decrease)
		if (decrement == 2) {                                               // Read what direction encoder is twisted
			if (count > 0) {                                               	// Check if count is greater than 0
				count--;                                                    // Decrement count     
				
				LCD_ClearDisplay();    
				LCD_Position(0,5);                                          // Position LCD to top row, after space 5
				LCD_PrintString("Volume");                                  // Display "Volume"
				
				LCD_Position(1,7);                                          // Position LCD to bottom row, after space 7
				LCD_PrintNumber(count);                                     // Display the current number count
				
				decrement = 0;                                              // Reset flag to 0
			}
			if (count == 0) {                                               // Check is the count is equal to 0
				LCD_ClearDisplay();                                         // Clear display
				LCD_Position(0,3);                                          // Position LCD to top row, after space 3
				LCD_PrintString("Min Volume");                              // Display "Max Volume"
				
				CyDelay(1000);                                              // Delay
				
				LCD_ClearDisplay();                                         // Clear Display
				LCD_Position(0,5);                                          // Position LCD to top row, after space 5
				LCD_PrintString("Volume");                                  // Display Volume
				
				LCD_Position(1,7);                                          // Position LCD to bottom row, after space 7
				LCD_PrintNumber(count);                                     // Display the current number count
				
				decrement = 0;                                              // Reset the flag to 0
			}
		}
    } 
}

/* [] END OF FILE */
