#ifndef SENSORS_H
#define	SENSORS_H

extern float distanceSensors[4];
extern int statusSensors[4];
void configIC2(int mode, int fallingEdge);
void enableIC2();
void disableIC2();
void configIC3(int mode, int fallingEdge);
void enableIC3();
void disableIC3();
void RightDistance();
void LeftDistance();

#endif	/* SENSORS_H */



