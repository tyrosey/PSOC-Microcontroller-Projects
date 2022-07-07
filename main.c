/* ==========================================================================
 *
 * Tyler Rose
 * ECE -- Microcontrollers
 *
 * Project 7 Description:
 * 
 * Use Serial Peripheral Interface (SPI) SRAM and a temperature sensor to
 * record temperature. Use Analog to Digital Converters (ADCs) and Digital
 * to Analog Converters (DACs) to make a visual thermometer
 *
 * ==========================================================================
*/
#include "project.h"
#include <stdlib.h>
#include <stdio.h>

char blocking_put_char();
void sram_WRITE(uint16 address, uint8 data);
uint8 sram_READ(uint16 address);
float convertADC(uint16 counts);

char uartOutput[81];
uint8 spiBuf[4];

int main(void) {
    CyGlobalIntEnable; /* Enable global interrupts. */
    SPIM_Start();
    UART_Start();
    ADC_Start();
    ADC_StartConvert();
    DAC_Start();
    DAC_BUF_Start();    
    
    char userInput;
    uint16 resetAddress;
    uint16 addressCount = 0;
    uint8 MS_Address_Byte;
    uint8 LS_Address_Byte;
    float32 vMIN = 0.68f, vMAX = 0.72f;
    float32 dacVoltageBrightness, adcVoltage, m, b;

 for(;;) {
        
        UART_PutString("(R)ecord, (P)layback, or (V)isual\r\n\r\nHit ENTER key when ready to exit Visual mode\r\n");            // default statement
        
        userInput = blocking_put_char();                                        // waiting for user input
        
        if (userInput == 'R' || userInput == 'r'){                              // if r or R is pressed
            addressCount = 0;                                                   // set address count to 0

                while (addressCount < 16384){                                   // check if SRAM is maxed out, continues loop if not maxed out
                    resetAddress = (uint16)ADC_GetResult16();                   // sets resetAddress to the value of the latest ADC conversion
                    MS_Address_Byte = (uint8)(resetAddress & 0xFF00) >> 8;      // sets variable as the MS byte of the address and shifts by 8
                    snprintf(uartOutput, sizeof uartOutput," Address Count: %d, MS Byte: 0x%x\r\n", resetAddress, MS_Address_Byte); 	// organizing display
                    UART_PutString(uartOutput);                                                                                     	// prints display
                    sram_WRITE(addressCount, MS_Address_Byte);                                                                      	// calls the write function for MS Byte
                    addressCount++;                                                                                                 	// increments the address count
                    LS_Address_Byte = (uint8)(resetAddress & 0x00FF);                                                               	// sets variable to LS byte of address
                    snprintf(uartOutput, sizeof uartOutput," Address Count: %d, LS Byte: 0x%x\r\n", resetAddress, LS_Address_Byte); 	// organize display
                    UART_PutString(uartOutput);                                                                                     	// print display
                    sram_WRITE(addressCount, LS_Address_Byte);                                                                         	// calls write function for LS Byte
                    snprintf(uartOutput, sizeof uartOutput," Temp: %f --> Address [0x%d], [0x%d]\r\n\r\n", convertADC(resetAddress)*100,addressCount-1,addressCount);
                    UART_PutString(uartOutput);                                                                                     	// print display
                    addressCount++;                                                                                                 	// increments address count
                }
        }
        
        else if (userInput == 'P' || userInput == 'p'){                                                 // if P or p is pressed
            addressCount = 0;                                                                           // set addressCount to zero
            
                while (addressCount < 16384){                                                           // check if SRAM is maxed out, continues loop if not maxed out
                    MS_Address_Byte = sram_READ(addressCount);                                          // set MS address byte to the first byte stored in the SRAM
                    snprintf(uartOutput, sizeof uartOutput," MS Byte: 0x%x\r\n", MS_Address_Byte);
                    UART_PutString(uartOutput);                                                         
                    addressCount++;                                                                     // increment the address count
                    LS_Address_Byte = sram_READ(addressCount);                                          // set LS address byte to the second byte stored in the SRAM
                    snprintf(uartOutput, sizeof uartOutput," LS Byte: 0x%x\r\n", LS_Address_Byte);
                    UART_PutString(uartOutput);                                                        
                    resetAddress = (((uint16)MS_Address_Byte<<8) | LS_Address_Byte);                    // shifting MSByte back to MSB position and bitwise or the address back together
                    snprintf(uartOutput, sizeof uartOutput,"\r\n Sample Number: 0x%x\r\n\r\n", resetAddress);   // organize display
                    UART_PutString(uartOutput);                                                         // print display
                    snprintf(uartOutput, sizeof uartOutput," Temp: %f --> Address [0x%d], [0x%d]\r\n\r\n", convertADC(resetAddress)*100,addressCount-1,addressCount);
                    UART_PutString(uartOutput);
                    addressCount++;                                                                     // increment address count
                }
            }
        
        else if (userInput == 'V' || userInput == 'v'){                                             // if V or v is pressed

                while (userInput != 0x0D){                                                          // waiting for enter to be hit
                    userInput = UART_GetChar();                                                     // set input to get char function
                    adcVoltage = convertADC((uint16)ADC_GetResult16());                             // set adcVoltage to the conversion value from the ADC_Convert function
                    
                    m = (4.08f - 2.4f) /(vMAX - vMIN);                                              // describing the slope for a linear fit
                    b = 2.4f - (m*vMIN);                                                            // setting the offset
                    dacVoltageBrightness = (m * adcVoltage + b);                                    // slope times the sample voltage plus the offset
                    
                    DAC_SetValue((uint8)dacVoltageBrightness / 0.016f);                             // sets the Voltage/Brighteness level
                    
                    snprintf(uartOutput, sizeof uartOutput,"Brightness:%f\r\n", dacVoltageBrightness);          // organize display    
                    UART_PutString(uartOutput);                                                                 // print display
                    CyDelay(100);                                                                               // delay
                }
                DAC_SetValue(0);                                                                                // set the DAC output to zero
        }
        else {  
            UART_PutString("\r\n\r\n~INVALID INPUT~ Please Try Again\r\n\r\n");                                 // error message for invalid entries
        }
    }   
}


// function for writing to the SRAM
void sram_WRITE(uint16 address, uint8 data){     
    uint8 MS_Address_Byte = (uint8)(address >> 8);     // taking first byte of address
    uint8 LS_Address_Byte = (uint8)(address & 0x00FF); // taking last byte of address
    
    spiBuf[0] = 0x02;                                   // hex code for write command
    spiBuf[1] = MS_Address_Byte;                        // first byte of address
    spiBuf[2] = LS_Address_Byte;                        // second byte of address
    spiBuf[3] = data;                                   // writting the data to the 4th byte
    
    SPIM_PutArray(spiBuf,4);                            // loading the 4 bytes from spibuf to SPIM_PutArray
    
    while(!(SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE));  // polling loop until SPI is finished

}

// function for reading from SRAM
uint8 sram_READ(uint16 address){
    
    uint8 MS_Address_Byte = (uint8)(address >> 8);      // taking firt byte of address
    uint8 LS_Address_Byte = (uint8)(address & 0x00FF);  // taking second byte of address
    uint8 data = 0;                                 
    
    spiBuf[0] = 0x03;                                   // hex code for read command
    spiBuf[1] = MS_Address_Byte;                        // first byte of address
    spiBuf[2] = LS_Address_Byte;                        // second byte of address
    spiBuf[3] = 0xAA;                                   // Dummy byte
    
    SPIM_ClearRxBuffer();                               // clear recieve buffer
    SPIM_PutArray(spiBuf,4);                            // loading the 4 bytes from spibuf to SPIM_PutArray
    while(!(SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE));  // polling loop until SPI is finished
    SPIM_ReadRxData();                                  // calling READ command 3 times for address before returning value in fourth byte
    SPIM_ReadRxData();                                      
    SPIM_ReadRxData();
    data = SPIM_ReadRxData();                           // setting dataBytes to the 4th call of the READ command (to get the values at that address)
    return data;                                        // returns data stored from the 4th call of the Read command
}


// function for converting ADC to voltage
float convertADC(uint16 counts){                        
    float voltage;                                                               // declare float voltage 

    voltage = ((5.0 / 32768) * counts)*10;                                       // ACD reference divided by the resolution then multiplied by the count and 100 to get the voltage
    snprintf(uartOutput, sizeof uartOutput,"\r\n Voltage: %f\r\n\r\n", voltage); // organize display
    UART_PutString(uartOutput);                                                  // print display
    
    return voltage;                                                              // returns the value stored in 'voltage'
}

// function for waiting for input from user
char blocking_put_char(){                           
    char input = 0;
    while(input == 0) input = UART_GetChar();
    return input;
}

/* [] END OF FILE */
