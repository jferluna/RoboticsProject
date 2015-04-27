#include <p32xxxx.h>
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

#include "Motors.h"
#include "robotics.h"

#define TIMER2_VECTOR 8
#define TIMER2_PRIORITY 4
#define BASE_PWM 1000
#define BASE_FLOAT_PWM 1000.0

float newVal;
float newVal2;

void PWMConfig(){
    //Timer 2 is the source clock
    OC1CONSET = 0x0006;     //PWM mode on OC1
    OC2CONSET = 0x0006;     //PWM mode on OC2
    //(SYSCLK / PWM_FREQ) - 1;
    PR2 = 2499;             //Timer 2 Period - 63 microseconds
    //(PR2 + 1) * ((float)DUTY_CYCLE / 100);
    OC1RS = BASE_PWM;            //Dutty cyccle - 13 microseconds
    OC2RS = BASE_PWM;            //13 microseconds(PR2 + 1) * ((float)DUTY_CYCLE / 100);
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
void newPWM(float val){
    newVal=val;
}
void newPWM2(float val){
    newVal2=val;
}
void __ISR(TIMER2_VECTOR, IPL4) Timer2_IntHandler (void) {
    OC1RS = (int)BASE_FLOAT_PWM + (int)(newVal * 50.0);
    OC2RS = (int)BASE_FLOAT_PWM + (int)(newVal2 * 50.0);
    IFS0CLR = 0x0100; // Clearing Timer2 interrupt flag
}