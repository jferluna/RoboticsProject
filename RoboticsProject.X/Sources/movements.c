#include <p32xxxx.h>
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

#include "movements.h"
#include "robotics.h"
#include "Motors.h"
#include "sensors.h"
#include "timers.h"

#define DISTANCE_MARGIN 0.1
#define NUM_SENSORS 4
#define RIGHT_EDGE 0
#define RIGHT_FRONT 1
#define LEFT_FRONT 2
#define LEFT_EDGE 3

void alignInitialPosition() {
    getDistances();
    if(statusSensors[RIGHT_FRONT] == 3 && statusSensors[LEFT_FRONT] == 3) {
        if(distanceSensors[RIGHT_FRONT] > 10 || distanceSensors[LEFT_FRONT] > 10){
            Right();
            miliWait(3000);
            alinear();
            Stop();
            miliWait(2000);
            acercar();
            Stop();
            miliWait(2000);
            Left();
            miliWait(3000);
        } else {
            alinear();
        }
    }
    Stop();
}

void alinear(){
    do{
        getDistances();
        newPWM(-10.0);
        newPWM2(-10.0);
        if((statusSensors[1]==3)&&(statusSensors[2]==3)){
            if((distanceSensors[2]<(distanceSensors[1] + DISTANCE_MARGIN))&&(distanceSensors[2]>(distanceSensors[1] - DISTANCE_MARGIN))){
                Stop();
                Nop();
            }
            else if(distanceSensors[2]<distanceSensors[1]){
                RotateLeft();
            }
            else if(distanceSensors[2]>distanceSensors[1]){
                RotateRight();
            }
        }
    }while(!((distanceSensors[2]<(distanceSensors[1]+0.8))&&(distanceSensors[2]>(distanceSensors[1]-0.8))));
    newPWM(0);
    newPWM2(0);
}

void acercar(){
    do{
        getDistances();
        if((statusSensors[1]==3)&&(statusSensors[2]==3)){
            if((distanceSensors[2]<5)&&(distanceSensors[2]>5)){
                Stop();
            }
            else if(distanceSensors[2]<=5){
                Backward();
            }
            else {
                Forward();
            }
        }
    }while(!((distanceSensors[2]<10)&&(distanceSensors[2]>5)));
}




