/* ==========================================================================
 *
 * Tyler Rose
 * ECE -- Microcontrollers
 *
 * Project 5 Description:
 * 
 * Use I2C bus protocol (EEPROMs), PWM, and UARTs to implement a player piano
 * that can record (both notes and durations), playback,, and set a tempo
 *
 * ==========================================================================
*/

#include "project.h"
#include <stdlib.h>
#include <stdio.h>

char blocking_char();
char output[81];
int getNote(char note);
int getDuration(char duration,int bpm);
uint8 i2c_write(unsigned char i2cAddress,unsigned char* bufferPointerWrite,int bytes);
uint8 i2c_read(unsigned char i2cAddress,unsigned char* bufferPointerRead,int readAddy, int bytes);
uint8 readWriteReturn;
int period = 0;

int main(void) {
    CyGlobalIntEnable;
    
    // start modules
    PWM_Start();    
    I2C_Start();
    UART_Start();
    
    // declarations
    uint8 tempoCount;
    char tempoInput;
    char tempoArray[4];
    int bpm = 600;
    
    int newLine = 0;
    char input;
    uint8 recordCount;
    char recordInput;
    char recordArray[2];
    unsigned char noteBuffer[255] = {0};
    unsigned char durationBuffer[255] = {0};
    unsigned char dataOut[2];
    
    unsigned char dataIn;
    int holdPeriod;
    int i = 0;

    PWM_WritePeriod(0);
    
    for(;;) {
		
		// for printintg a new line after the first display start up message appears
        if (newLine == 1) {         	
            UART_PutString("\r\n\r\n");
        }
        
        UART_PutString("Choose one of the following: (R)ecord, (P)layback, or (T)empo\r\n");           //display start up message
        newLine = 1;
        input = blocking_char();            	// set input to function for getting character input from user
        
        if(input == 'R' || input == 'r') {      // if R or r key is pressed
            recordCount = 0;                    // set the count to zero
            UART_PutString("\r\nChoose a note, then choose the duration (e)ight, (q)uarter, (h)alf), or (w)hole.\r\nHit enter when finished.\r\n"); // display message
            UART_PutString("\r\nRecording...\r\n\r\n");
            
            do {    
                recordInput = blocking_char();               // set the input to function for getting character input from user
                
                if(getNote(recordInput) !=0) {               // checks if the input is not zero and is a valid character
                    UART_PutChar(recordInput);               // displays the character from the input
                    recordArray[0] = recordInput;            // stores input character to position zero of the record array
                    UART_PutChar(' ');                       // displays a space
                    recordInput = blocking_char();           // set the input to function for getting character input from user
                    
                    if(getDuration(recordInput, bpm) != 0) {     // checks if the duration input is not zero and is a valid character
                        UART_PutChar(recordInput);               // displays the character from the input
                        recordArray[1] = recordInput;            // stores duration input character to position 1 od the record array
                    }
                    
                    else{
                        
                        while(getDuration(recordInput, bpm) == 0) {   // while no key has been pressed
                            recordInput = blocking_char();            // wait for key to be pressed
                            recordArray[1] = recordInput;             // stores duration input character to position 1 of the record array
                        }
                        
                        UART_PutChar(recordInput);                    // displays the input character
                    }
                    
                    noteBuffer[recordCount] = recordArray[0];          // stores note from record input into a buffer
                    durationBuffer[recordCount] = recordArray[1];      // stores duration from record input into a buffer
                    recordCount++;                                     // increments the count which increments the buffer array position
                }
                
                else if((recordInput == 0x08 || recordInput == 0x7F) && recordInput > 0) {       // if backspace or delete is pressed and there has been input already displayed
                    UART_PutChar(0x08);         // backspace ascii code
                    UART_PutChar(' ');          // displays a space 
                    UART_PutChar(0x08);         // backspaces again
                    recordCount--;              // decrements the count
                }
                
                else { 
                    UART_PutChar(0x07);         // ASCII BEL sound
                }  
                
                UART_PutString("\r\n");         // prints a new line
                
            }
			
            while(recordInput != 0x0D);        //waiting for enter key to be pressed
            
            for(int i = 0; i < recordCount; i++){           // for loop for writing each note until all input characters are stored
                dataOut[0] = i;                             // sets position 0 to i
                dataOut[1] = noteBuffer[i];                 // sets position 1 to whatever is stored in the "i" position in the note buffer
                i2c_write(0x50, dataOut, 2);                // calls write function with notes address, the data, and writes 2 bytes
                dataOut[1] = durationBuffer[i];             // sets position 1 to whatever is stored in the "i" position in the duration buffer 
                i2c_write(0x51, dataOut, 2);                // calls write function with duration address, the data, and writes 2 bytes
            }

            dataOut[0] = recordCount;                       // stores the count in position 0 of the data array
            dataOut[1] = 0;                                 // stores 0 in position 1 of the data array
            i2c_write(0x50, dataOut,2);                     // calls write function with notes address, the data, and writes 2 bytes     
            i2c_write(0x51, dataOut, 2);                    // calls write function with duration address, the data, and writes 2 bytes
            UART_PutString("\r\n\r\n");                           // prints a new line
            UART_PutString("SONG SUCCESSFULLY RECORDED!\r\n");    // prints success message
            
        }
        
        else if(input == 'P' || input == 'p') {	                // if P or p is pressed
        
            i2c_read(0x50,&dataIn, 0, 1);                       // reads notes data from eeprom into dataIn

            if (dataIn != 0) {
                UART_PutString("\r\nPlayback In Progress...\r\n\r\n");    // display message
            }
            
            while(dataIn != 0) {                              // while there are still notes and durations to be read
                i2c_read(0x50, &dataIn, i, 1);                // calls read function with notes address, the data, the position of the data array, and 1 byte 
                holdPeriod = getNote(dataIn);                 // sets holdPeriod to function getNote based on the stored data
                PWM_Start();                                  // start the pwm
                PWM_WritePeriod(holdPeriod);                  // writes the period as the holdPeriod from the stored character
                PWM_WriteCompare(holdPeriod/2);               // writes a 50% duty cycle
                i2c_read(0x51, &dataIn, i, 1);                // calls read function with duration address, the data, the position of the data array, and 1 byte
                holdPeriod = getDuration(dataIn, bpm);        // sets holdPeriod to function for setting the duration pending which valid key is pressed
                CyDelay(holdPeriod);                          // delay by the chosen duration
                PWM_Stop();                                   // stop the pwm
                i++;                                          // increment i
            }
			
            i =0;                                             // sets i back to zero
            UART_PutString("\r\n\r\nPlayback Finished!\r\n");    // display message
        }
		
        else if(input == 'T' || input == 't') {              // if T or t is pressed
            
            tempoCount = 0;                                 // set count to zero

            UART_PutString("\r\nEnter BPM (0 to 999): ");              // display message
            
            do {
                tempoInput = blocking_char();                                   // set input to function for character input
                if(tempoInput >= '0' && tempoInput <= '9' && tempoCount < 3){   // checks for valid integer input
                    UART_PutChar(tempoInput);                                   // displays integer
                    tempoArray[tempoCount++] = tempoInput;                      // stores the input into a tempoNumber array, position based on count
                }
                else if((tempoInput == 0x08 || tempoInput == 0x7F) && tempoCount > 0){      // if backspace or delete is pressed
                    UART_PutChar(0x08);         // backspace ascii code 
                    UART_PutChar(' ');          // displays a space
                    UART_PutChar(0x08);         // backspaces again
                    tempoCount--;               // decrements the count
                }
                else{
                    UART_PutChar(0x07);         // ASCII BEL sound
                }
                
            }
            while(tempoInput != 0x0D);          // waiting for enter key to be pressed before continuing
            UART_PutString("\r\n\r\n");         // prints a new line
            UART_PutString("New Tempo Set!");   // prints message
            UART_PutString("\r\n");             // prints a new line
            
            tempoArray[tempoCount] = 0;        // sets the last position of the counter array to 0
            bpm =  60000 / atoi(tempoArray);   // sets the beats per minute
        }
        
        else{
            UART_PutString("\r\n~~INVALID MODE---TRY AGAIN~~\r\n\r\n");    // display error message
            UART_PutChar(0x07);             // ASCII BEL sound
        }
    }   
}

char blocking_char(){       	// function for waiting for input
    char input = 0;             // sets input to zero
    while(input == 0) input = UART_GetChar();   // while input is zero, set input to get char function
    return input;                               // return the input
}

int getNote(char note){     // function for getting the correct period based on what character is inputted
    switch(note){           // case statement for each character is based off of previous lab periods
        case 'z':
            period = 3822;
            break;
        
        case 'x':
            period = 3405;
            break; 
        
        case 'c':
            period = 3034;
            break; 
        
        case 'v':
            period = 2863;
            break; 
        
        case 'b':
            period = 2551;
            break;
        
        case 'n':
            period = 2273;
            break;
        
        case 'm':
            period = 2025;
            break;
        
        case ',':
            period = 1911;
            break;
        
        case 'a':
            period = 1911;
            break; 
        
        case 's':
            period = 1703;
            break; 
        
        case 'd':
            period = 1517;
            break; 
        
        case 'f':
            period = 1432;
            break; 
        
        case 'g':
            period = 1276;
            break; 
        
        case 'h':
            period = 1136;
            break; 
        
        case 'j':
            period = 1012;
            break; 
        
        case 'k':
            period = 956;
            break; 
        
       case 'q':
            period = 956;
            break;
        
        case 'w':
            period = 851;
            break;
        
        case 'e':
            period = 760;
            break;
        
        case 'r':
            period = 716;
            break;
        
        case 't':
            period = 638;
            break;
        
        case 'y':
            period = 569;
            break;
        
        case 'u':
            period = 506;
            break;  
        
        case 'i':
            period = 478;
            break; 
        
        default: 
            period = 0;
        }
    return period;
}

int getDuration(char duration, int bpm){        // function for setting the bpm based off which key is pressed
    switch(duration){
            case 'w':
                return bpm * 4; // returns bpm times 4 (2400) for whole note
            case 'W':
                return bpm * 4; // returns bpm times 4 (2400) for whole note
        
            case 'h':
                return bpm * 2; // returns bpm times 2 (1200) for half note
            case 'H':
                return bpm * 2; // returns bpm times 2 (1200) for half note
        
            case 'q':           
                return bpm;     // returns bpm which is already set to 600 for quarter note
            case 'Q':
                return bpm;     // returns bpm which is already set to 600 for quarter note

            case 'e':
                return bpm / 2; // returns bpm divided by 2 (300) for eighth note
            case 'E':
                return bpm / 2; // returns bpm divided by 2 (300) for eighth note
        
            default:
                UART_PutChar(0x07);     // ASCII BEL sound
                return 0;               // returns 0 if an invalid key is pressed
    }      
}

uint8 i2c_write(unsigned char  i2cAddress, unsigned char* bufferPointerWrite, int bytes){    

    readWriteReturn = I2C_MasterWriteBuf(i2cAddress, bufferPointerWrite, bytes, I2C_MODE_COMPLETE_XFER);    // API for writing to the I2C --> handles ACKs, starts, stops, etc
    while (!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));         // waits for I2C to write the # of bytes
    I2C_MasterClearStatus();    // clears all bits in the status register
 
    snprintf(output, sizeof output, "0x%x --> 0x%x[%c]\r\n", i2cAddress,bufferPointerWrite[0],bufferPointerWrite[1]); // formats the data for seeing that the data is stored properly
    UART_PutString(output); // prints string
    CyDelay(5);             // required delay to store data
    
    return readWriteReturn;
}

uint8 i2c_read(unsigned char i2cAddress, unsigned char* bufferPointerRead, int readAddy, int bytes){
    
    I2C_MasterWriteBuf(i2cAddress, (uint8*)&readAddy, bytes, I2C_MODE_COMPLETE_XFER);    // API for writting to the I2C --> handles ACKs, starts, stops, etc
    while (!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));     // waits for I2C to write the # of bytes
    I2C_MasterClearStatus();    // clears all bits in the status register
    
    readWriteReturn = I2C_MasterReadBuf(i2cAddress, bufferPointerRead, bytes, I2C_MODE_COMPLETE_XFER);     // API for reading to the I2C --> handles ACKs, starts, stops, etc
    while (!(I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));     // waits for I2C to read the # of bytes
    I2C_MasterClearStatus();    // clears all bits from the status register
    
    snprintf(output, sizeof output, "0x%x --> 0x%x[%c]\r\n", i2cAddress, readAddy, *bufferPointerRead); // formats the data for seeing that the data is read properly
    UART_PutString(output); // prints string
    
    return readWriteReturn;
}

