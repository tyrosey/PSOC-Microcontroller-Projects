/* ==========================================================================
 *
 * Tyler Rose
 * ECE -- Microcontrollers
 *
 * Project 1.B Description:
 * 
 * Create a volume control interface using two push buttons and a Hitachi LCD.
 * No volume will be controlled. PSOC Creator's API is used. 
 *
 * ==========================================================================
*/

#include "project.h"
#include <string.h>
#include <stdio.h>


int main(void) {
    CyGlobalIntEnable;                                                  /* Enable global interrupts. */
    
    // Start the display at 50
    LCD_Start();                                                        // Start LCD Module
    LCD_Position(0,5);                                                  // Position LCD to top row, after space 5
    LCD_PrintString("Volume");						// Print Volume on the LCD

    LCD_Position(1,0);                                                  // Position LCD bottom row far left
    char displayString[17];                                             // Initialize displayString 17 bits
    uint16 count = 50;                                                  // Initialize count to 50
    char decString[] = "Dec";                                           // Set decString as "dec"
    
    snprintf(displayString, 17, "%s %d        \n", decString, count);   // Organize display
    LCD_PrintString(displayString);                                     // Display "Dec 50"
    
    LCD_Position (1, 10);                                               // Position LCD to bottom row, after space 10
    LCD_PrintString("Hex");                                             // Display "Hex"
    
    LCD_Position (1, 14);                                               // Position LCD to bottom row, after space 14
    LCD_PrintInt8(count);                                               // Display the count in hexadecimal form
   
    

	for(;;) {
  
		//Increment when SW1 is pushed  
		if (SW1_Read() == 1) {                                               		    // Read what switch 1 is
			if (count <100) {                                                   	    // Check if count is less than 100
				LCD_ClearDisplay();                                                 // Clear LCD display
				count++;                                                            // Increment count
				LCD_Position(0,2);                                                  // Position LCD to top row, after space 2
				LCD_PrintString("Incrementing");                                    // Display "Incrementing"
			   
				LCD_Position(1,0);                                                  // Position LCD
				snprintf(displayString, 17, "%s %d         \n", decString, count);  // Organize display
				LCD_PrintString(displayString);                                     // Display "Dec" and current count
				
				LCD_Position (1, 10);                                               // Position LCD
				LCD_PrintString("Hex");                                             // Display "Hex"
				LCD_Position (1, 14);                                               // Position LCD
				LCD_PrintInt8(count);                                               // Display the current count in hex
				
				CyDelay(500);                                                       // Delay before clearing
				LCD_ClearDisplay();                                                 // Clear LCD display
				
				LCD_Position(0,5);                                                  // Position LCD
				LCD_PrintString("Volume");                                          // Display "Volume"
				
				LCD_Position(1,0);                                                  // Position LCD
				snprintf(displayString, 17, "%s %d         \n", decString, count);  // Organize display
				LCD_PrintString(displayString);                                     // Display "Dec" and current count
				
				LCD_Position (1, 10);                                               // Position LCD
				LCD_PrintString("Hex");                                             // Display "Hex"
				
				LCD_Position (1, 14);                                               // Position LCD
				LCD_PrintInt8(count);                                               // Display current count in hex                                        
			}
		
			if (count == 100) {                                                 	    // Checks if count is 100
				LCD_ClearDisplay();                                                 // Clear Display
				LCD_Position(0,3);                                                  // Position LCD
				LCD_PrintString("Max Volume");                                      // Display "Max Volume"
				CyDelay(1000);                                                      // Delay Clear
				LCD_ClearDisplay();                                                 // Clear LCD
				LCD_Position(0,5);                                                  // Position LCD
				LCD_PrintString("Volume");                                          // Display "Volume"
				LCD_Position(1,0);                                                  // Position LCD
				snprintf(displayString, 17, "%s %d         \n", decString, count);  // Organize display
				LCD_PrintString(displayString);                                     // display "dec" and current count
				LCD_Position (1, 10);                                               // Position LCD
				LCD_PrintString("Hex");                                             // Display "Hex"
				
				LCD_Position (1, 14);                                               // Position LCD
				LCD_PrintInt8(count);                                               // Display count in hex form
			}
		}
    
		//Decrement when SW2 is pushed -- implementation is identical to increment block, just decrementing to 0
		if (SW2_Read() == 1) {
			if (count > 0) {
				LCD_ClearDisplay();
				count--;
				LCD_Position(0,2);
				LCD_PrintString("Decrementing");
				
				LCD_Position(1,0);
				snprintf(displayString, 17, "%s %d         \n", decString, count);
				LCD_PrintString(displayString);
				
				LCD_Position (1, 10);
				LCD_PrintString("Hex");
				LCD_Position (1, 14);
				LCD_PrintInt8(count);
				
				CyDelay(500);
				LCD_ClearDisplay();
				
				LCD_Position(0,5);                                                  
				LCD_PrintString("Volume");
				
				LCD_Position(1,0);
				snprintf(displayString, 17, "%s %d        \n", decString, count);
				LCD_PrintString(displayString);
				
				LCD_Position (1, 10);
				LCD_PrintString("Hex");
				
				LCD_Position (1, 14);
				LCD_PrintInt8(count);
			}
    
			if (count == 0) { 
				LCD_ClearDisplay();
				LCD_Position(0,3);
				LCD_PrintString("Min Volume");
				CyDelay(1000);
				LCD_ClearDisplay();
				LCD_Position(0,5);
				LCD_PrintString("Volume");
				LCD_Position(1,0);
				snprintf(displayString, 17, "%s %d         \n", decString, count);
				LCD_PrintString(displayString);
				LCD_Position (1, 10);
				LCD_PrintString("Hex");
				
				LCD_Position (1, 14);
				LCD_PrintInt8(count);
			}
		}
    }
}
