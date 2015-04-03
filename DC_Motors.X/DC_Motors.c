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
#pragma config ICESEL = ICS_PGx2    // ICE / ICD Comm Channel Select
#pragma config DEBUG = ON           // Debugger Disabled for Starter Kit

#define SYSCLK  40000000L
#define TIMER2_VECTOR 8
#define TIMER2_PRIORITY 4

void PWMConfig(){
    //Timer 2 is the source clock

    OC1CONSET = 0x0006;     //PWM mode on OC1
    OC2CONSET = 0x0006;     //PWM mode on OC2

    //(SYSCLK / PWM_FREQ) - 1;
    PR2 = 2499;             //Timer 2 Period - 63 microseconds

    //(PR2 + 1) * ((float)DUTY_CYCLE / 100);
    OC1RS = 1000;            //Dutty cyccle - 13 microseconds
    OC2RS = 1000;            //13 microseconds(PR2 + 1) * ((float)DUTY_CYCLE / 100);

    IFS0CLR = 0x00000100;   // Clear the T2 interrupt flag
    IEC0SET = 0x00000100;   // Enable T2 interrupt
    IPC2bits.T2IP = TIMER2_PRIORITY;    //Timer2 priority 4

    T2CONSET = 0x8000;      // Enable Timer2, prescaler 1:1
    OC1CONbits.ON = 1;      // Enable Output Compare Module 1
    OC2CONbits.ON = 1;      // Enable Output Compare Module 1
}

void Forward(){
    LATEbits.LATE0 = 1; //BIN1 - Right rear motor
    LATEbits.LATE1 = 0; //BIN2 - Right rear motor
    LATEbits.LATE2 = 0; //BIN1 - Left rear motor
    LATEbits.LATE3 = 1; //BIN2 - Left rear motor
    LATEbits.LATE4 = 1; //AIN1 - Right front motor
    LATEbits.LATE5 = 0; //AIN2 - Right front motor
    LATEbits.LATE6 = 0; //AIN1 - Left front motor
    LATEbits.LATE7 = 1; //AIN2 - Left front motor
}

void Backward(){
    LATEbits.LATE0 = 0; //BIN1 - Right rear motor
    LATEbits.LATE1 = 1; //BIN2 - Right rear motor
    LATEbits.LATE2 = 1; //BIN1 - Left rear motor
    LATEbits.LATE3 = 0; //BIN2 - Left rear motor
    LATEbits.LATE4 = 0; //AIN1 - Right front motor
    LATEbits.LATE5 = 1; //AIN2 - Right front motor
    LATEbits.LATE6 = 1; //AIN1 - Left front motor
    LATEbits.LATE7 = 0; //AIN2 - Left front motor
}

void Stop() {
    LATEbits.LATE0 = 1; //BIN1 - Right rear motor
    LATEbits.LATE1 = 1; //BIN2 - Right rear motor
    LATEbits.LATE2 = 1; //BIN1 - Left rear motor
    LATEbits.LATE3 = 1; //BIN2 - Left rear motor
    LATEbits.LATE4 = 1; //AIN1 - Right front motor
    LATEbits.LATE5 = 1; //AIN2 - Right front motor
    LATEbits.LATE6 = 1; //AIN1 - Left front motor
    LATEbits.LATE7 = 1; //AIN2 - Left front motor
}

void Right() {
    LATEbits.LATE0 = 1; //BIN1 - Right rear motor
    LATEbits.LATE1 = 0; //BIN2 - Right rear motor
    LATEbits.LATE2 = 1; //BIN1 - Left rear motor
    LATEbits.LATE3 = 0; //BIN2 - Left rear motor
    LATEbits.LATE4 = 0; //AIN1 - Right front motor
    LATEbits.LATE5 = 1; //AIN2 - Right front motor
    LATEbits.LATE6 = 0; //AIN1 - Left front motor
    LATEbits.LATE7 = 1; //AIN2 - Left front motor
}

void Left() {
    LATEbits.LATE0 = 0; //BIN1 - Right rear motor
    LATEbits.LATE1 = 1; //BIN2 - Right rear motor
    LATEbits.LATE2 = 0; //BIN1 - Left rear motor
    LATEbits.LATE3 = 1; //BIN2 - Left rear motor
    LATEbits.LATE4 = 1; //AIN1 - Right front motor
    LATEbits.LATE5 = 0; //AIN2 - Right front motor
    LATEbits.LATE6 = 1; //AIN1 - Left front motor
    LATEbits.LATE7 = 0; //AIN2 - Left front motor
}

void RotateRight() {
    LATEbits.LATE0 = 0; //BIN1 - Right rear motor
    LATEbits.LATE1 = 1; //BIN2 - Right rear motor
    LATEbits.LATE2 = 0; //BIN1 - Left rear motor
    LATEbits.LATE3 = 1; //BIN2 - Left rear motor
    LATEbits.LATE4 = 0; //AIN1 - Right front motor
    LATEbits.LATE5 = 1; //AIN2 - Right front motor
    LATEbits.LATE6 = 0; //AIN1 - Left front motor
    LATEbits.LATE7 = 1; //AIN2 - Left front motor
}

void RotateLeft() {
    LATEbits.LATE0 = 1; //BIN1 - Right rear motor
    LATEbits.LATE1 = 0; //BIN2 - Right rear motor
    LATEbits.LATE2 = 1; //BIN1 - Left rear motor
    LATEbits.LATE3 = 0; //BIN2 - Left rear motor
    LATEbits.LATE4 = 1; //AIN1 - Right front motor
    LATEbits.LATE5 = 0; //AIN2 - Right front motor
    LATEbits.LATE6 = 1; //AIN1 - Left front motor
    LATEbits.LATE7 = 0; //AIN2 - Left front motor
}

int main(void) {
    SYSTEMConfigPerformance(SYSCLK);
    INTEnableSystemMultiVectoredInt();

    TRISE = 0x00;   //PORTE as Outputs
    LATE = 0x00;    //Clear motor digital inputs

    PWMConfig();
    while(1) {
        Right();
    }
}


void __ISR(TIMER2_VECTOR, IPL4) Timer2_IntHandler (void) {

    IFS0CLR = 0x0100; // Clearing Timer2 interrupt flag
}