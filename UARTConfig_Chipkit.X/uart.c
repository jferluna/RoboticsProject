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

    //Dissable UART module
    U1MODEbits.ON = 0;

    //Configure BaudRate
    U1BRG = U0BRG_9600_BAUDRATE;

    //8-bits, no parity bit and 1 stop bit
    U1MODEbits.PDSEL = 00;
    U1MODEbits.STSEL = 0;

    //Enable Transmit and Receive
    U1STAbits.URXEN = 1;
    U1STAbits.UTXEN = 1;

    //Enable transmit interrupt
    U1STAbits.UTXISEL = 01; //Interrupt when all characters have been transmited
    IEC0bits.U1TXIE = 1;
    IFS0bits.U1TXIF = 0;

    //Enable receive interrupt
    U1STAbits.URXISEL = 0;  //Interrupt when a character is received
    IEC0bits.U1RXIE = 1;
    IFS0bits.U1RXIF = 0;

    //Set priotiry and subpriority interrupt
    IPC6bits.U1IP = 0;
    IPC6bits.U1IS = 0;

    //Enable UART module
    U1MODEbits.ON = 1;
}

int transmitData(const char *data, int length) {
    int i;
    while( U1STAbits.UTXBF);
    for(i = 0; i < length; i++) {
        U1TXREG = *data;
        data++;
    }

    while(!U1STAbits.TRMT);
}

void __ISR(24, IPL0AUTO) UART1_RX_IntHandler(void) {
    if(IFS0bits.U1TXIF = 1) {
        IFS0bits.U1TXIF = 0;    //Clear transmit interrupt flag
    }

    if(IFS0bits.U1RXIF = 1) {
        *
        IFS0bits.U1RXIF = 0;    //Clear receive interrupt flag
    }
}


int main(void){
    char data[] = {'H', 'O', 'L', 'A', '!'};
    SYSTEMConfigPerformance(SYSCLK);
    INTEnableSystemMultiVectoredInt();
    configureUART();
    int t;
    for( t=0 ; t < 100000 ; t++) ;

    transmitData("Hola\r\n", 5);
}
