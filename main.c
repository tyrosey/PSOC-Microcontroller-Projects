/* ==========================================================================
 *
 * Tyler Rose
 * ECE -- Microcontrollers
 *
 * Project 4 Description:
 * 
 * Use timers to make interrupts happen at specific intervals to implement
 * a side-scrolling action game using the LCD and push buttons. Add PWM and
 * a speaker to create background music
 *
 * ==========================================================================
*/

#include "project.h"

void backgroundSong(void);
volatile int posCharacter;


int main(void) {
    CyGlobalIntEnable; 
    LCD_Start();                		// start module
    Refresh_Timer_Start();      		// start module
    Refresh_Timer_WritePeriod(999);     // set initial speed for scrolling
    
    //prints the starting screen
    LCD_PrintString("Press Any Button");
    LCD_Position(1,4);
    LCD_PrintString("To Begin");

    //checks for any button to be pressed
    while(Control_Read() == 0);     	// While button is not pressed
    REFRESH_ISR_Start();            	// start module
    
    for (;;){
        backgroundSong();    			// plays "Sweet Child O'Mine" intro in the background while game is being playeed
            }
}

// function for setting the pwm for the background music
void backgroundSong(void) {
    
    PWM_Start();
    
    //First Wave

    PWM_WritePeriod(3822);      // sets period
    PWM_WriteCompare(1911);     // 50% duty cycle
    CyDelay(250);               // delay
    
    PWM_WritePeriod(1912);
    PWM_WriteCompare(956);
    CyDelay(250);
    
    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(2865);
    PWM_WriteCompare(1433);
    CyDelay(250);

    PWM_WritePeriod(1432);
    PWM_WriteCompare(716);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(1517);
    PWM_WriteCompare(759);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);
    
    //Repeat

    PWM_WritePeriod(3822);
    PWM_WriteCompare(1911);
    CyDelay(250);

    PWM_WritePeriod(1912);
    PWM_WriteCompare(956);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(2865);
    PWM_WriteCompare(1433);
    CyDelay(250);

    PWM_WritePeriod(1432);
    PWM_WriteCompare(716);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(1517);
    PWM_WriteCompare(759);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);
    
    //Second Wave

    PWM_WritePeriod(3406);
    PWM_WriteCompare(1703);
    CyDelay(250);

    PWM_WritePeriod(1912);
    PWM_WriteCompare(956);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(2865);
    PWM_WriteCompare(1433);
    CyDelay(250);

    PWM_WritePeriod(1432);
    PWM_WriteCompare(716);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(1517);
    PWM_WriteCompare(759);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);
    
    // Repeat

    PWM_WritePeriod(3406);
    PWM_WriteCompare(1703);
    CyDelay(250);

    PWM_WritePeriod(1912);
    PWM_WriteCompare(956);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(2865);
    PWM_WriteCompare(1433);
    CyDelay(250);

    PWM_WritePeriod(1432);
    PWM_WriteCompare(716);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(1517);
    PWM_WriteCompare(759);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);
    
    //Third Wave

    PWM_WritePeriod(2865);
    PWM_WriteCompare(1433);
    CyDelay(250);

    PWM_WritePeriod(1912);
    PWM_WriteCompare(956);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(2865);
    PWM_WriteCompare(1433);
    CyDelay(250);

    PWM_WritePeriod(1432);
    PWM_WriteCompare(716);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(1517);
    PWM_WriteCompare(759);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);
    
    //Repeat

    PWM_WritePeriod(2865);
    PWM_WriteCompare(1433);
    CyDelay(250);

    PWM_WritePeriod(1912);
    PWM_WriteCompare(956);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(2865);
    PWM_WriteCompare(1433);
    CyDelay(250);

    PWM_WritePeriod(1432);
    PWM_WriteCompare(716);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(1517);
    PWM_WriteCompare(759);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);
    
    //Fourth Wave
    
    PWM_WritePeriod(3822);
    PWM_WriteCompare(1911);
    CyDelay(250);

    PWM_WritePeriod(1912);
    PWM_WriteCompare(956);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(2865);
    PWM_WriteCompare(1433);
    CyDelay(250);

    PWM_WritePeriod(1432);
    PWM_WriteCompare(716);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(1517);
    PWM_WriteCompare(759);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);
    
    //Repeat

    PWM_WritePeriod(3822);
    PWM_WriteCompare(1911);
    CyDelay(250);

    PWM_WritePeriod(1912);
    PWM_WriteCompare(956);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(2865);
    PWM_WriteCompare(1433);
    CyDelay(250);

    PWM_WritePeriod(1432);
    PWM_WriteCompare(716);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);

    PWM_WritePeriod(1517);
    PWM_WriteCompare(759);
    CyDelay(250);

    PWM_WritePeriod(2551);
    PWM_WriteCompare(1275);
    CyDelay(250);
        
    
    PWM_Stop();
    
}

/* [] END OF FILE */


