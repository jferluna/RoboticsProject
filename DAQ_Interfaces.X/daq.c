#include <p32xxxx.h>

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

// Configuration Bits
#pragma config FNOSC = FRCPLL       // Internal Fast RC oscillator (8 MHz) w/ PLL
#pragma config FPLLIDIV = DIV_2     // Divide FRC before PLL (now 4 MHz)
#pragma config FPLLMUL = MUL_20     // PLL (now 80 MHz)
#pragma config FPLLODIV = DIV_2     // Divide After PLL (now 40 MHz)
#pragma config FWDTEN = OFF         // Watchdog Timer Disabled
#pragma config FSOSCEN = OFF        // Disable Secondary Oscillator

//Debugging configuration
#pragma config ICESEL = ICS_PGx2// ICE / ICD Comm Channel Select
#pragma config DEBUG = ON       // Debugger Disabled for Starter Kit

#define SYSCLK  40000000L

void configADC() {
    TRISB = 0xFFFF;     //Analog pin as input
    AD1PCFG = 0x0000;   //Analog pin in analog mode

    AD1CHSbits.CH0NA = 0;    //Channel A negative is VR-
    AD1CHSbits.CH0NB = 0;
    AD1CHSbits.CH0SA = 0;
    AD1CHSbits.CH0SB = 1;

    AD1CON1bits.FORM = 0x5; //Signed integer 32-bits

    AD1CON1bits.SSRC = 0x7; //Auto-convert

    AD1CON1bits.ASAM = 0x1; //Sampling begins after last conversion

    AD1CON2bits.VCFG = 0x0; //AVDD - AVSS

    AD1CON2bits.CSCNA = 0x1; //Scan inputs


}

int main(int argc, char** argv) {



}

