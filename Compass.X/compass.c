#include <p32xxxx.h>

#define _SUPPRESS_PLIB_WARNING
#include <plib.h>
// Configuration Bits
#pragma config FNOSC = FRCPLL       // Internal Fast RC oscillator (8 MHz) w/ PLL
#pragma config FPLLIDIV = DIV_2     // Divide FRC before PLL (now 4 MHz)
#pragma config FPLLMUL = MUL_20     // PLL (now 80 MHz)
#pragma config FPLLODIV = DIV_2     // Divide After PLL (now 40 MHz)
                                    // see figure 8.1 in datasheet for more info
#pragma config FWDTEN = OFF         // Watchdog Timer Disabled
#pragma config FSOSCEN = OFF        // Disable Secondary Oscillator

//Debugging configuration
#pragma config ICESEL = ICS_PGx2// ICE / ICD Comm Channel Select
#pragma config DEBUG = ON       // Debugger Disabled for Starter Kit

#define SYSCLK  40000000L
#define setPR1(seconds)   (seconds * SYSCLK / 256)
#define PWM_FREQ    16000
#define DUTY_CYCLE  60

#define COMPASS_CLK_PERIOD 1

/*
 * Din, Dout    RD0
 * Enable       RD1
 * CLK          RD2
*/
int compasX, compasY, compasStatus, compasState = 0;
int count = 0;

void setTimer3(int microSec) {
    //Disable the timer
    T3CON = 0x00000000;

    TMR3 = 0;
    PR3 = 40 * microSec;
    //Enable interrupts for timer3
    IFS0bits.T3IF = 0;
    IPC3 = 0xC;
    IEC0bits.T3IE = 1;
    //Turn ON timer 3
    T3CONbits.ON = 1;
}

void setCompass() {
    //Din, En & CLK as outputs
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;

    //Set CLK interval in microseconds
    setTimer3(1);
    PORTDbits.RD0 = 0;
    //Enable to High
    PORTDbits.RD1 = 1;
    compasState = 0;
}

void __ISR(12, IPL3) Timer3IntHandler(void){
    switch(compasState) {
        //Test
        case 0:
            //Clock signal
            PORTDbits.RD2 = !(PORTDbits.RD2);

        //Reset
        case 1:
            //Clock signal
            PORTDbits.RD2 = !(PORTDbits.RD2);

            //Din & Enable -> LOW
            if(count <= 7) {
                //Enable = Low throught all message
                PORTDbits.RD0 = 0;
                PORTDbits.RD1 = 0;
                count++;
            }
            //Change compasState and reset count
            if(count > 7) {
                PORTDbits.RD0 = 1;
                PORTDbits.RD1 = 1;
                count = 0;
                compasState++;
            }
            break;

        //Start measurement
        case 2:
            //Clock signal
            PORTDbits.RD2 = !(PORTDbits.RD2);

            //Enable -> LOW
            PORTDbits.RD1 = 0;

            if(count < 2) {
                PORTDbits.RD0 = 1;
                count++;
            } else if(count > 7) {
                PORTDbits.RD2 = 0;
                PR3 = 40000;
                compasState++;
                count = 0;
            } else {
                PORTDbits.RD0 = 0;
                count++;
            }
            break;
        //Check measurement compasStatus
        case 3:
            if(count == 0){
                PR3 = 40;
            }
            if(count >= 2) {
                //Clock signal
                PORTDbits.RD2 = !(PORTDbits.RD2);
            }
            //Enable
            switch(count) {
                case 0:
                    PORTDbits.RD1 = 1;
                    break;
                case 1:
                    PORTDbits.RD1 = 0;
                    break;
                case 2:
                    PORTDbits.RD0 = 1;
                    break;
                case 6:
                    PORTDbits.RD0 = 0;
                    break;
                case 10:
                     TRISDbits.TRISD0 = 1;
                    break;
            }

            if((count > 10) && ((count%2)) == 1) {
                compasStatus <<= 1;
                compasStatus |= PORTDbits.RD0;
                compasStatus &= 0x0F;
                if(compasStatus == 0x0C){
                    PORTDbits.RD2 = 0;
                    compasState++;
                    count = 0;
                }
            }
///*DEBUG
            if(count > 10 && PORTDbits.RD0 == 1){
                PORTDbits.RD3 = 1;
            }
//*/

            count++;
            break;
        //Read measurement
        case 4:
            //Clock signal
            PORTDbits.RD2 = !(PORTDbits.RD2);
            if(count < 22 && (count%2 == 1)) {
                compasX <<= 1;
                compasX |= PORTDbits.RD0;
                count++;
            } else if(count >= 22 && count < 44 && (count%2 == 1)) {
                compasY <<= 1;
                compasY |= PORTDbits.RD0;
                count++;
            } else if(count >= 44) {

                count = 0;
                PORTDbits.RD1 = 1;
                PORTDbits.RD2 = 0;
                compasState = 1;
                T3CON = 0x00000000;
                TMR3 = 0;
            } else {
                count++;
            }
            break;
    }
    
    IFS0bits.T3IF = 0;
}

int main(void){
    SYSTEMConfigPerformance(SYSCLK);
    INTEnableSystemMultiVectoredInt();
    setCompass();
    while(1) {

    }
}
