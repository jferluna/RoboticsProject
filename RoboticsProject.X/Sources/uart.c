#include <p32xxxx.h>
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

#include "uart.h"
#include "robotics.h"

//UART Configurations
#define U1BRG_BAUDRATE 259
#define U2BRG_BAUDRATE 259

void configureUART1() {

    //Dissable UART module
    U1MODEbits.ON = 0;

    //Configure BaudRate
    U1BRG = U1BRG_BAUDRATE;

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

void configureUART2() {

    //Dissable UART module
    U2MODEbits.ON = 0;

    //Configure BaudRate
    U2BRG = U2BRG_BAUDRATE;

    //8-bits, no parity bit and 1 stop bit
    U2MODEbits.PDSEL = 00;
    U2MODEbits.STSEL = 0;

    //Enable Transmit and Receive
    U2STAbits.URXEN = 1;
    U2STAbits.UTXEN = 1;

    //Enable transmit interrupt
    U2STAbits.UTXISEL = 01; //Interrupt when all characters have been transmited
    IEC1bits.U2TXIE = 1;
    IFS1bits.U2TXIF = 0;

    //Enable receive interrupt
    U2STAbits.URXISEL = 0;  //Interrupt when a character is received
    IEC1bits.U2RXIE = 1;
    IFS1bits.U2RXIF = 0;

    //Set priotiry and subpriority interrupt
    IPC8bits.U2IP = 0;
    IPC8bits.U2IS = 0;

    //Enable UART module
    U2MODEbits.ON = 1;
}

/* transmitDataUART1
 * ---------------------------------
 * Sends command characters from chipkit Uno32 to the Raspberry Pi
 * using the serial protocol
 *
 * *data: pointer to the first char of the array to send
 * length: length of the array to send
 */
void transmitDataUART1(const char *data, int length) {
    int i;
    for(i = 0; i < length; i++) {
        while(U1STAbits.UTXBF);
        U1TXREG = *data;
        data++;
    }
    while(!U1STAbits.TRMT);
}

/* transmitDataUART1
 * ---------------------------------
 * Sends command characters from chipkit Uno32 to the servo controller
 * using the serial protocol
 *
 * *data: pointer to the first char of the array to send
 * length: length of the array to send
 */
void transmitDataUART2(const char *data, int length) {
    int i;
    for(i = 0; i < length; i++) {
        while(U2STAbits.UTXBF);
        U2TXREG = *data;
        data++;
    }
    while(!U2STAbits.TRMT);
}

/* UART1_RX_IntHandler
 * ---------------------------------
 * Interrupt Service Routine
 */
void __ISR(24, IPL0AUTO) UART1_RX_IntHandler(void) {
    if(IFS0bits.U1TXIF = 1) {
        IFS0bits.U1TXIF = 0;    //Clear transmit interrupt flag
    }

    if(IFS0bits.U1RXIF = 1) {
        IFS0bits.U1RXIF = 0;    //Clear receive interrupt flag
    }
}

void __ISR(32, IPL0AUTO) UART2_RX_IntHandler(void) {
    if(IFS1bits.U2TXIF = 1) {
        IFS1bits.U2TXIF = 0;    //Clear transmit interrupt flag
    }

    if(IFS1bits.U2RXIF = 1) {
        IFS1bits.U2RXIF = 0;    //Clear receive interrupt flag
    }
}