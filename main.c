/* ==========================================================================
 *
 * Tyler Rose
 * ECE -- Microcontrollers
 *
 * Project 6 Description:
 * 
 * Use Interrupts, timers, debouncers, I2Cs, an encoder, push buttons, an
 * LCD, and a stepper motor to implement a heating/cooling system. The motor
 * will rotate clockwise when cooling, and counter clockwise when heating.
 *
 * ==========================================================================
*/

#include "project.h"

volatile uint8 READ_TEMP = 0xAA;
volatile uint8 ACCESS_TH = 0xA1;
volatile uint8 ACCESS_TL = 0xA2;
volatile uint8 ACCESS_CR = 0xAC;
uint8 START_CONVERT = 0xEE;
uint8 tempArrayOne[3];
volatile int setTemp = 23;
volatile int tolerance = 2;
volatile int motorCount = 0;
volatile int count = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // START MODULES
    LCD_Start();
    I2C_Start();
    ENC_ISR_Start();
    MODE_ISR_Start();
    UPDATE_ISR_Start();
    Update_Timer_Start();
    Motor_Timer_Start();

    // preparing I2C to read the temp
    tempArrayOne[0] = ACCESS_CR;                                                    // sets beginning byte of array to 0xAC for Access Config command
    tempArrayOne[1] = 0x02;                                                         // Polarity bit set to 'high'
    I2C_MasterWriteBuf(0x48, tempArrayOne, 2, I2C_MODE_COMPLETE_XFER);              // I2C write command
    while (!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));                             // I2C status
    I2C_MasterClearStatus();                                                        // clears I2C 
    
    // Setting the TH register to 1 degree above the current temp
    tempArrayOne[0] = ACCESS_TH;                                                    // sets beginning byte of array to 0xA1 to access TH register
    tempArrayOne[1] = (uint8)(setTemp + tolerance/2);                               // Sets the tolerance and stores it in the 2nd byte
    tempArrayOne[2] = 0;                                                            // writes 0 to end of array to let I2C know its at the end
    I2C_MasterWriteBuf(0x48, tempArrayOne, 3, I2C_MODE_COMPLETE_XFER);              // I2C address (0x48) -> data written to I2C -> bytes -> I2C mode
    while (!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));                             // Waiting for data to be written
    I2C_MasterClearStatus();                                                        // clear I2C
    
    // Setting the TL register to 1 degree below current temp  
    tempArrayOne[0] = ACCESS_TL;                                                    // sets beginning byte of array to 0xA2 to access TL register
    tempArrayOne[1] = (uint8)(setTemp - (tolerance/2));                             // Sets the tolerance and stores it in the 2nd byte
    tempArrayOne[2] = 0;                                                            // writes 0 to end of array to let I2C know its at the end
    I2C_MasterWriteBuf(0x48, tempArrayOne, 3, I2C_MODE_COMPLETE_XFER);              // I2C address (0x48) -> data written to I2C -> bytes -> I2C mode
    while (!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));                             // Waiting for data to be written
    I2C_MasterClearStatus();                                                        // clear I2C
    
    // Begin Temperature Conversion 
    I2C_MasterWriteBuf(0x48, &START_CONVERT, 1, I2C_MODE_COMPLETE_XFER);            // I2C address (0x48) -> data written to I2C -> bytes -> I2C mode
    while (!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));                             // Waiting for data to be written
    I2C_MasterClearStatus();                                                        // clear I2C

    
    for(;;)
    {
    }
}

/* [] END OF FILE */
