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

//UART Configurations
#define U0BRG_9600_BAUDRATE 259

void configureUART() {
    
}

int main(void){
    SYSTEMConfigPerformance(SYSCLK);
    INTEnableSystemMultiVectoredInt();

}
