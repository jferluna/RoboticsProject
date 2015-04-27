#ifndef UART_H
#define	UART_H

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

void configureUART1();
void configureUART2();
void transmitDataUART1(const char *data, int length);
void transmitDataUART2(const char *data, int length);

#endif

