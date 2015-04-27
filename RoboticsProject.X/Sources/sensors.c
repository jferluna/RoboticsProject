#include <p32xxxx.h>
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

#include "sensors.h"
#include "robotics.h"
#include "timers.h"

#define NUM_SENSORS 4
#define RIGHT_EDGE 0
#define RIGHT_FRONT 1
#define LEFT_FRONT 2
#define LEFT_EDGE 3

// 0 - Right Edge, 1 - Right Distance, 2 - Left Distance, 3 - Left edge
int statusSensors[NUM_SENSORS] = {0, 0, 0, 0};
float distanceSensors[NUM_SENSORS] = {0, 0, 0, 0};

void configIC2(int mode, int fallingEdge) {
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 0;
    TMR3 = 0x000;
    TRISDbits.TRISD9 = 1;           //IC2 pin as input
    IC2CONbits.ON = 0;              //Disable the input capture 2
    IC2CONbits.ICM = mode;          //IC2 event mode
    IC2CONbits.FEDGE = fallingEdge; //Capture rising
    IC2CONbits.ICTMR = 0;           //Timer 3 as counter source
    IC2CONbits.ICI = 0;             //Interrupt on every capture event
    IFS0bits.IC2IF = 0;             //Clear interrupt flag
    IEC0bits.IC2IE = 1;             //Enable interrupt events
    IPC2bits.IC2IP = 1;             //Interrupt priority #1
    IPC2bits.IC2IS = 0;             //Interrupt subpriority #0
    TMR3 = 0x0000;                  //Clears timer 3 count
    IC2CONbits.ON = 1;              //Enable IC2 module
    return;
}
void enableIC2() {
    IEC0bits.IC2IE = 1;     //Enable interrupts
    IC2CONbits.ON = 1;      //Enable IC3 module
    T3CONbits.ON = 1;       //Enable timer 3
    return;
}
void disableIC2() {
    IEC0bits.IC2IE = 0;     //Disable interrupts
    IFS0bits.IC2IF = 0;     //Clear IC3 flag
    IC2CONbits.ON = 0;      //Disable module and reset
    T3CONbits.ON = 0;       //Disable timer 3
    TMR3 = 0x00;            //Clear timer 3 count
    return;
}
void configIC4(int mode, int fallingEdge) {
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 0;
    TMR3 = 0x000;
    TRISDbits.TRISD11 = 1;           //IC2 pin as input
    IC4CONbits.ON = 0;              //Disable the input capture 2
    IC4CONbits.ICM = mode;          //IC2 event mode
    IC4CONbits.FEDGE = fallingEdge; //Capture rising
    IC4CONbits.ICTMR = 0;           //Timer 3 as counter source
    IC4CONbits.ICI = 0;             //Interrupt on every capture event
    IFS0bits.IC4IF = 0;             //Clear interrupt flag
    IEC0bits.IC4IE = 1;             //Enable interrupt events
    IPC4bits.IC4IP = 1;             //Interrupt priority #1
    IPC4bits.IC4IS = 0;             //Interrupt subpriority #0
    TMR3 = 0x0000;                  //Clears timer 3 count
    IC4CONbits.ON = 1;              //Enable IC2 module
    return;
}
void enableIC4() {
    IEC0bits.IC4IE = 1;     //Enable interrupts
    IC4CONbits.ON = 1;      //Enable IC3 module
    T3CONbits.ON = 1;       //Enable timer 3
    return;
}
void disableIC4() {
    IEC0bits.IC4IE = 0;     //Disable interrupts
    IFS0bits.IC4IF = 0;     //Clear IC4 flag
    IC4CONbits.ON = 0;      //Disable module and reset
    T3CONbits.ON = 0;       //Disable timer 3
    TMR3 = 0x00;            //Clear timer 3 count
    return;
}
void configIC3(int mode, int fallingEdge) {
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 0;
    TMR3 = 0x000;
    TRISDbits.TRISD10 = 1;          //IC3 pin as input
    IC3CONbits.ON = 0;              //Disable the input capture 3
    IC3CONbits.ICM = mode;          //IC3 event mode
    IC3CONbits.FEDGE = fallingEdge; //Capture rising
    IC3CONbits.ICTMR = 0;           //Timer 3 as counter source
    IC3CONbits.ICI = 0;             //Interrupt on every capture event
    IFS0bits.IC3IF = 0;             //Clear interrupt flag
    IEC0bits.IC3IE = 1;             //Enable interrupt events
    IPC3bits.IC3IP = 1;             //Interrupt priority #1
    IPC3bits.IC3IS = 0;             //Interrupt subpriority #0
    TMR3 = 0x0000;                  //Clears timer 3 count
    IC3CONbits.ON = 1;              //Enable IC3 module
    return;
}
void enableIC3() {
    IEC0bits.IC3IE = 1;     //Enable interrupts
    IC3CONbits.ON = 1;      //Enable IC3 module
    T3CONbits.ON = 1;       //Enable timer 3
    return;
}
void disableIC3() {
    IEC0bits.IC3IE = 0;     //Disable interrupts
    IFS0bits.IC3IF = 0;     //Clear IC3 flag
    IC3CONbits.ON = 0;      //Disable module and reset
    T3CONbits.ON = 0;       //Disable timer 3
    TMR3 = 0x00;            //Clear timer 3 count
    return;
}
void RightDistance() {
    statusSensors[1] = 1;
    TRISDbits.TRISD9 = 0;   //RD9 as outpur for 10us pulse
    LATDbits.LATD9 = 1;
    configTimer5(399, 0);   //Wait 10us
    while(!IFS0bits.T5IF);  //Wait for timer 5 flag
    IFS0bits.T5IF = 0;
    LATDbits.LATD9 = 0;
    enableIC2();
    configIC2(6, 1);
    miliWait(70);
    return;
}
void LeftDistance() {
    statusSensors[2] = 1;
    TRISDbits.TRISD10 = 0;  //RD10 as output for 10us pulse
    LATDbits.LATD10 = 1;
    configTimer5(399, 0);   //Wait 10us
    while(!IFS0bits.T5IF);  //Wait for timer 5 flag
    IFS0bits.T5IF = 0;
    LATDbits.LATD10 = 0;
    enableIC3();
    configIC3(6, 1); //Simple capture mode, first capture on rising edge
    //while(statusSensors[LEFT_FRONT] != 3);
    miliWait(70);
    return;
}
void LeftEdge() {
    statusSensors[3] = 1;
    TRISDbits.TRISD11 = 0;  //RD10 as output for 10us pulse
    LATDbits.LATD11 = 1;
    configTimer5(399, 0);   //Wait 10us
    while(!IFS0bits.T5IF);  //Wait for timer 5 flag
    IFS0bits.T5IF = 0;
    LATDbits.LATD11 = 0;
    enableIC4();
    configIC4(6, 1); //Simple capture mode, first capture on rising edge
    //while(statusSensors[LEFT_FRONT] != 3);
    miliWait(70);
    return;
}
void __ISR(9, IPL1) InputCapture2_IntHandler(void) {
    if(PORTDbits.RD9 == 1) {
        TMR3 = 0x00;
        statusSensors[RIGHT_FRONT] = 2; //Processing status
        distanceSensors[RIGHT_FRONT] = IC2BUF;//clear ICBNE
    } else {
        statusSensors[RIGHT_FRONT] = 3;             //Finish status
        distanceSensors[RIGHT_FRONT] = (float)TMR3 * 0.1103;  //Get distance(cms)
        Nop();
        disableIC2();
    }
    IFS0bits.IC2IF = 0;    //Clear ISC3 interrupt flag
    return;
}
void __ISR(13, IPL1) InputCapture3_IntHandler(void) {
    if(PORTDbits.RD10 == 1) {
        TMR3 = 0x00;
        statusSensors[LEFT_FRONT] = 2;          //Processing status
        distanceSensors[LEFT_FRONT] = IC3BUF;   //clear ICBNE
        Nop();
    } else {
        statusSensors[LEFT_FRONT] = 3;
            //Finish status
        distanceSensors[LEFT_FRONT] = (float)TMR3 * 0.1103;  //Get distance(cms)
        Nop();
        disableIC3();
    }
    IFS0bits.IC3IF = 0;    //Clear IC3 interrupt flag
    return;
}
void __ISR(17, IPL1) InputCapture4_IntHandler(void) {
    if(PORTDbits.RD11 == 1) {
        TMR3 = 0x00;
        statusSensors[LEFT_EDGE] = 2;          //Processing status
        distanceSensors[LEFT_EDGE] = IC4BUF;   //clear ICBNE
        Nop();
    } else {
        statusSensors[LEFT_EDGE] = 3;
            //Finish status
        distanceSensors[LEFT_EDGE] = (float)TMR3 * 0.1103;  //Get distance(cms)
        Nop();
        disableIC4();
    }
    IFS0bits.IC4IF = 0;    //Clear IC4 interrupt flag
    return;
}