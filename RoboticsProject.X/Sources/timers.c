#include <p32xxxx.h>
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

#include "timers.h"
#include "robotics.h"

#define SYSCLK  40000000L
#define setPR1(seconds)   (seconds * SYSCLK / 256)

int flagT1=0;

void configTimer1(float time) {

    T1CON=0x8070;       //Enable Timer 1 prescaler 256
    PR1=setPR1(time);   //Set PR
    TMR1CLR = 0xFFFF;           //Clear timer 1 value
    IFS0bits.T1IF = 0;  //Clear timer 1 interrupt flag
    IPC1bits.T1IP = 4;  //Priority #4
    IPC1bits.T1IS = 0;  //Subpriority 0
    IEC0bits.T1IE = 1;  //Enable timer 1 Interrupt
    T1CONbits.ON = 1;   //Enable timer 1
    return;
}

void disableTimer1() {
    T1CONbits.ON = 0;
    PR1CLR = 0xFFFF;
    TMR1CLR = 0xFFFF;
}

/*void configTimer1(float time) {

    T1CON=0x8070;
    PR1=setPR1(time);






    T1CONbits.ON = 0;           //Disable timer 1
    T1CONCLR = 0x02;            //Internal PBCLK as source
    T1CONbits.TCKPS = prescaler;//Prescaler for timer 1
    TMR1CLR = 0xFFFF;           //Clear timer 1 value
    PR1 = time;                 //Set time period for timer 1

    IFS0bits.T1IF = 0;  //Clear timer 1 interrupt flag
    IPC1bits.T1IP = 4;  //Priority #4
    IPC1bits.T1IS = 0;  //Subpriority 0
    IEC0bits.T1IE = 1;  //Enable timer 1 Interrupt

    T1CONbits.ON = 1;   //Enable timer 1
    return;
}*/

void configTimer2() {
    T2CONbits.ON = 0;           //Disable timer
    T2CONCLR = 0x02;            //Internal PBCLK as source
    T2CONbits.TCKPS = 7;        //1:1 prescaler value
    TMR2CLR = 0xFFFF;           //Clear timer5 value
    PR2 = 0xFFFF;               //Full timer 2 count
    T2CONbits.ON = 1;           //Enable timer
    Nop();
    return;
}

void configTimer3() {
    T3CONbits.ON = 0;           //Disable timer
    T3CONCLR = 0x02;            //Internal PBCLK as source
    T3CONbits.TCKPS = 7;        //1:1 prescaler value
    TMR3CLR = 0xFFFF;           //Clear timer5 value
    PR3 = 0xFFFF;               //Full timer 2 count
    T3CONbits.ON = 1;           //Enable timer
    Nop();
    Nop();
    return;
}

/*
 * configTimer5(int time)
 * ----------------------------
 * Configure timer options
 *
 * time: decimal value for register PR5 based on PBCLK
 * prescaler: prescaler selector value for TCKPS bits
 */
void configTimer5(int time, int prescaler) {
    T5CONbits.ON = 0;           //Disable timer
    T5CONCLR = 0x02;            //Internal PBCLK as source
    T5CONbits.TCKPS = prescaler;//PreTCKPSscaler value
    TMR5CLR = 0xFFFF;           //Clear timer5 value
    PR5 = time;                 //Time defined
    T5CONbits.ON = 1;           //Enable timer
    Nop();
    Nop();
}

void disableTimer5() {
    T5CONbits.ON = 0;
    PR5CLR = 0xFFFF;
    TMR5CLR = 0xFFFF;
}

/*
 * void miliWait(int time)
 * -------------------------------------------
 * Waits "time" miliseconds on blocking mode
 *
 * time: "n" miliseconds to freeze
 */
int miliWait(int time) {
    int presSelec = -1;
    int validPR, timerVal;
    int prescaler[] = {1,2,4,8,16,32,64,256};

    for(timerVal =  time; timerVal > 400; time -= 400, timerVal = time) {
        //Puts timer 5 waiting for 400 miliseconds
        //(aproximate maximum value for 16-bit timer)
        configTimer5(62499, 7);
        while(!IFS0bits.T5IF);      //Checks that timer 5 has finished
        IFS0bits.T5IF = 0;          //Reset timer5 flag
    }

    do {
        if(presSelec >= 8)
            return -1;
        else
            presSelec++;
        timerVal = ((float)time / (1000 * prescaler[presSelec])) * SYSCLK - 1;
        validPR = timerVal >> 16;
    } while(validPR);

    if(!validPR)
        configTimer5(timerVal, presSelec);

    while(!IFS0bits.T5IF);      //Checks that timer 5 has finished
    IFS0bits.T5IF = 0;          //Reset timer5 flag
    disableTimer5();
    return 1;
}

/*
 * void microWait(int time)
 * -------------------------------------------
 * Waits "time" microseconds on blocking mode
 *
 * time: "n" microseconds to freeze
 */
int microWait(int time) {
    int presSelec = -1;
    int validPR, timerVal;
    int prescaler[] = {1,2,4,8,16,32,64,256};

//    for(timerVal =  time; timerVal > 400; time -= 400, timerVal = time) {
//        //Puts timer 5 waiting for 400 miliseconds
//        //(aproximate maximum value for 16-bit timer)
//        configTimer5(62499, 7);
//        while(!IFS0bits.T5IF);      //Checks that timer 5 has finished
//        IFS0bits.T5IF = 0;          //Reset timer5 flag
//    }

    do {
        if(presSelec >= 8)
            return -1;
        else
            presSelec++;
        timerVal = ((float)time / (1000000 * prescaler[presSelec])) * SYSCLK - 1;
        validPR = timerVal >> 16;
    } while(validPR);

    if(!validPR)
        configTimer5(timerVal, presSelec);

    while(!IFS0bits.T5IF);      //Checks that timer 5 has finished
    IFS0bits.T5IF = 0;          //Reset timer5 flag
    return 1;
}

void __ISR(4, IPL4) Timer1_IntHandler (void) {
    flagT1=1;
    IFS0CLR = 0x0010; // Clearing Timer2 interrupt flag
}