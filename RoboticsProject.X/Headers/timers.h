#ifndef TIMERS_H
#define	TIMERS_H

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

extern int flagT1;
void configTimer1(float time);
void configTimer2();
void configTimer3();
void configTimer5(int time, int prescaler);
void disableTimer5();
int miliWait(int time);
int microWait(int time);

#endif	/* TIMERS_H */

