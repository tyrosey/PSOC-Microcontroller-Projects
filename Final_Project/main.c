/* ==========================================================================
 *
 * Tyler Rose
 * ECE -- Microcontrollers
 *
 * Final Project Description:
 * 
 * Use Interrupts, debouncers, PWM, a speaker, an encoder, push buttons, and an
 * LCD to implement a word guessing game with selectable background music.
 *
 * ==========================================================================
*/

#include "project.h"
#include <stdio.h>

void backgroundSong();
volatile int songCount = 0;
volatile int songPlay = 0;
volatile int screenCount = 0;
volatile int levelCount = 1;
volatile int i = 0;
volatile int letterPosition = 0;
volatile int lifeCount = 3;


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    // start modules
    LCD_Start();
    ENC_ISR_Start();
    BUTTON_1_ISR_Start();
    BUTTON_2_ISR_Start();
    REFRESH_ISR_Start();
    Refresh_Timer_Start();

    for(;;)
    {
        //  if game has begun, start playing music
        if (songPlay == 1) {
        backgroundSong(songCount);
        }
    }
}


void backgroundSong(int songCount) {
    
    // Sweet Child O'Mine
    if (songCount == 0) {
                
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
            
        
    }
    
    // Thunderstruck
    if (songCount == 1) {
               
        // Part 1
        PWM_WritePeriod(3822);      // sets period
        PWM_WriteCompare(1911);     // 50% duty cycle
        CyDelay(125);               // delay
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);
        
        //repeat 2
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);
        
        //repeat 3
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);
        
        // repeat 4
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);
        
        // repeat 5
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);
        
        //repeat 6
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);;
        
        //repeat 7
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);
        
        // repeat 8
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);
        
        
         // Part 2
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2407);      
        PWM_WriteCompare(1203);     
        CyDelay(125);
        
        //repeat 2
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2407);      
        PWM_WriteCompare(1203);     
        CyDelay(125);
        
        //repeat 3
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2407);      
        PWM_WriteCompare(1203);     
        CyDelay(125);
        
        // repeat 4
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2407);      
        PWM_WriteCompare(1203);     
        CyDelay(125);
        
        // repeat 5
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2407);      
        PWM_WriteCompare(1203);     
        CyDelay(125);
        
        //repeat 6
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2407);      
        PWM_WriteCompare(1203);     
        CyDelay(125);
        
        //repeat 7
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2407);      
        PWM_WriteCompare(1203);     
        CyDelay(125);
        
        // repeat 8
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2407);      
        PWM_WriteCompare(1203);     
        CyDelay(125);
        
        // Part 3
        PWM_WritePeriod(3822);      // A
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(1911);      
        PWM_WriteCompare(955);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2145);      
        PWM_WriteCompare(1072);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2145);      
        PWM_WriteCompare(1072);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);

        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        // repeat 2
        PWM_WritePeriod(3822);      // A
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(1911);      
        PWM_WriteCompare(955);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2145);      
        PWM_WriteCompare(1072);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2145);      
        PWM_WriteCompare(1072);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);

        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        // repeat 3
        PWM_WritePeriod(3822);      // A
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(1911);      
        PWM_WriteCompare(955);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2145);      
        PWM_WriteCompare(1072);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2145);      
        PWM_WriteCompare(1072);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);

        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        // repeat 4
        PWM_WritePeriod(3822);      // A
        PWM_WriteCompare(1911);     
        CyDelay(125);               
        
        PWM_WritePeriod(1911);      
        PWM_WriteCompare(955);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2145);      
        PWM_WriteCompare(1072);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2145);      
        PWM_WriteCompare(1072);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);

        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(125);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(125);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(125);
        
   }
    
    // Crazy Train
    if (songCount == 2) {
                
        // begin
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(0);
        CyDelay(5);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(225);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2145);      
        PWM_WriteCompare(1072);     
        CyDelay(225);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(225);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(225);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(225);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(225);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(225);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(225);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(225);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(225);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(225);
        
        // repeat 2
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);       
        
        PWM_WritePeriod(0);
        CyDelay(5);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(225);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2145);      
        PWM_WriteCompare(1072);     
        CyDelay(225);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(225);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(225);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(225);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(225);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(225);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(225);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(225);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(225);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(225);
        
        //repeat 3
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);               
        
        PWM_WritePeriod(0);
        CyDelay(5);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(225);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2145);      
        PWM_WriteCompare(1072);     
        CyDelay(225);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(225);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(225);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(225);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(225);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(225);
        
        PWM_WritePeriod(2551);      
        PWM_WriteCompare(1275);     
        CyDelay(225);
        
        PWM_WritePeriod(2863);      
        PWM_WriteCompare(1431);     
        CyDelay(225);
        
        PWM_WritePeriod(3033);      
        PWM_WriteCompare(1516);     
        CyDelay(225);
        
        PWM_WritePeriod(3822);      
        PWM_WriteCompare(1911);     
        CyDelay(225);
        
        // repeat 4
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);              
        
        PWM_WritePeriod(0);
        CyDelay(5);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(225);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2145);      
        PWM_WriteCompare(1072);     
        CyDelay(225);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2272);      
        PWM_WriteCompare(1136);     
        CyDelay(225);
        
        PWM_WritePeriod(3406);      
        PWM_WriteCompare(1703);     
        CyDelay(225);
        
        PWM_WritePeriod(2145);      
        PWM_WriteCompare(1072);     
        CyDelay(900);
        
        PWM_WritePeriod(1911);      
        PWM_WriteCompare(955);     
        CyDelay(900);
        
    }
    
    // Master of Puppets
    if (songCount == 3) {
               
        //begin
        PWM_WritePeriod(1912);
        PWM_WriteCompare(956);
        CyDelay(450);
        
        PWM_WritePeriod(0);
        CyDelay(150);
        
        PWM_WritePeriod(2145);
        PWM_WriteCompare(1072);
        CyDelay(150);

        PWM_WritePeriod(2272);
        PWM_WriteCompare(1136);
        CyDelay(150);

        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(600);
        
        // main repeat
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(1911);
        PWM_WriteCompare(955);
        CyDelay(150);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(2024);
        PWM_WriteCompare(1012);
        CyDelay(150);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(2145);
        PWM_WriteCompare(1072);
        CyDelay(300);

        PWM_WritePeriod(2272);
        PWM_WriteCompare(1136);
        CyDelay(300);

        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(600);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(2702);
        PWM_WriteCompare(1351);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(2863);
        PWM_WriteCompare(1431);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3033);
        PWM_WriteCompare(1517);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);
        
        // repeat 2
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(1911);
        PWM_WriteCompare(955);
        CyDelay(150);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(2024);
        PWM_WriteCompare(1012);
        CyDelay(150);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(2145);
        PWM_WriteCompare(1072);
        CyDelay(300);

        PWM_WritePeriod(2272);
        PWM_WriteCompare(1136);
        CyDelay(300);

        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(600);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(2702);
        PWM_WriteCompare(1351);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(2863);
        PWM_WriteCompare(1431);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3033);
        PWM_WriteCompare(1517);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);
        
        // repeat 3
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(1911);
        PWM_WriteCompare(955);
        CyDelay(150);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(2024);
        PWM_WriteCompare(1012);
        CyDelay(150);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(2145);
        PWM_WriteCompare(1072);
        CyDelay(300);

        PWM_WritePeriod(2272);
        PWM_WriteCompare(1136);
        CyDelay(300);

        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(600);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(2702);
        PWM_WriteCompare(1351);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(2863);
        PWM_WriteCompare(1431);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3033);
        PWM_WriteCompare(1517);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);
        
        // repeat 4
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(1911);
        PWM_WriteCompare(955);
        CyDelay(150);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(2024);
        PWM_WriteCompare(1012);
        CyDelay(150);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(2145);
        PWM_WriteCompare(1072);
        CyDelay(300);

        PWM_WritePeriod(2272);
        PWM_WriteCompare(1136);
        CyDelay(300);

        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(600);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(2702);
        PWM_WriteCompare(1351);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);

        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(2863);
        PWM_WriteCompare(1431);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3033);
        PWM_WriteCompare(1517);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);
        
        // second riff
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2272);
        PWM_WriteCompare(1136);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(150);
        
        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        //FDAFDAFD
        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);

        // repeat 2
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2272);
        PWM_WriteCompare(1136);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(150);
        
        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        //FDAFDAFD
        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);

        // repeat 3
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2272);
        PWM_WriteCompare(1136);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(150);
        
        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        //FDAFDAFD
        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);

        // repeat 4
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2272);
        PWM_WriteCompare(1136);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(0);
        CyDelay(5);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);

        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(2407);
        PWM_WriteCompare(1203);
        CyDelay(150);
        
        PWM_WritePeriod(3607);
        PWM_WriteCompare(1803);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        //FDAFDAFD
        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(150);
        
        PWM_WritePeriod(3214);
        PWM_WriteCompare(1607);
        CyDelay(150);
        
        PWM_WritePeriod(3406);
        PWM_WriteCompare(1703);
        CyDelay(150);
        
    }
    
    // Walk This Way
    if (songCount == 4) {
                
        //begin
        PWM_WritePeriod(2863);
        PWM_WriteCompare(1431);
        CyDelay(150);
        
        PWM_WritePeriod(2702);
        PWM_WriteCompare(1351);
        CyDelay(150);

        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);

        PWM_WritePeriod(1911);
        PWM_WriteCompare(955);
        CyDelay(300);
        
        PWM_WritePeriod(2863);
        PWM_WriteCompare(1431);
        CyDelay(150);
        
        PWM_WritePeriod(2702);
        PWM_WriteCompare(1351);
        CyDelay(150);

        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);

        PWM_WritePeriod(1911);
        PWM_WriteCompare(955);
        CyDelay(300);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(300);
        
        PWM_WritePeriod(0);
        CyDelay(600);
        
        PWM_WritePeriod(2863);
        PWM_WriteCompare(1431);
        CyDelay(150);
        
        PWM_WritePeriod(2702);
        PWM_WriteCompare(1351);
        CyDelay(150);

        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);

        PWM_WritePeriod(1911);
        PWM_WriteCompare(955);
        CyDelay(300);
        
        PWM_WritePeriod(2863);
        PWM_WriteCompare(1431);
        CyDelay(150);
        
        PWM_WritePeriod(2702);
        PWM_WriteCompare(1351);
        CyDelay(150);

        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);

        PWM_WritePeriod(1911);
        PWM_WriteCompare(955);
        CyDelay(300);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(300);
        
        PWM_WritePeriod(1911);
        PWM_WriteCompare(955);
        CyDelay(600);
        
        PWM_WritePeriod(2863);
        PWM_WriteCompare(1431);
        CyDelay(150);
        
        PWM_WritePeriod(2702);
        PWM_WriteCompare(1351);
        CyDelay(150);

        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);

        PWM_WritePeriod(1911);
        PWM_WriteCompare(955);
        CyDelay(300);
        
        PWM_WritePeriod(2863);
        PWM_WriteCompare(1431);
        CyDelay(150);
        
        PWM_WritePeriod(2702);
        PWM_WriteCompare(1351);
        CyDelay(150);

        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);

        PWM_WritePeriod(1911);
        PWM_WriteCompare(955);
        CyDelay(300);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(300);
        
        PWM_WritePeriod(0);
        CyDelay(600);
        
        PWM_WritePeriod(2863);
        PWM_WriteCompare(1431);
        CyDelay(150);
        
        PWM_WritePeriod(2702);
        PWM_WriteCompare(1351);
        CyDelay(150);

        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);

        PWM_WritePeriod(1911);
        PWM_WriteCompare(955);
        CyDelay(300);
        
        PWM_WritePeriod(2863);
        PWM_WriteCompare(1431);
        CyDelay(150);
        
        PWM_WritePeriod(2702);
        PWM_WriteCompare(1351);
        CyDelay(150);

        PWM_WritePeriod(2551);
        PWM_WriteCompare(1275);
        CyDelay(150);

        PWM_WritePeriod(1911);
        PWM_WriteCompare(955);
        CyDelay(300);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(300);
        
        PWM_WritePeriod(1911);
        PWM_WriteCompare(955);
        CyDelay(300);
        
        PWM_WritePeriod(3822);
        PWM_WriteCompare(1911);
        CyDelay(300);
        
    }
}
    
/* [] END OF FILE */
