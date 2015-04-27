#include <p32xxxx.h>
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

#include "Headers/robotics.h"
#include "Headers/uart.h"
#include "Headers/servoController.h"
#include "Headers/timers.h"
#include "Headers/sensors.h"
#include "Headers/Motors.h"
#include "Headers/movements.h"

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

int state = 0;

/* initPIC32Config()
 * ---------------------------------
 * Configures PIC32 hardware modules to initial states
 */
void initPIC32Config() {
    TRISE = 0x00;
    PWMConfig();
    configTimer3();
    configureUART1();   //Configures Chipkit-Raspberry comunication
    configureUART2();   //Configures Chipkit-ServoController comunication
    miliWait(1);        //Wait 1 milisecond for modules be stable
    return;
}
/* initHW()
 * ---------------------------------
 * Configure robot hardware to initial positions
 */
void initHW() {
    pwmControl(0, 180);
    miliWait(2000);
    return;
}
void getDistances() {
    RightDistance();
    miliWait(60);
    disableIC2();
    LeftDistance();
    miliWait(60);
    disableIC3();
    return;
}
void getEdge(){
    LeftEdge();
    miliWait(60);
    disableIC4();
}
void controlPared() {
    getDistances();
    if((statusSensors[1]==3)&&(statusSensors[2]==3)){
        float dif = distanceSensors[2] -distanceSensors[1];
        newPWM(dif);
        Nop();
    }
}
void controlPared2() {
    getDistances();
    if((statusSensors[1]==3)&&(statusSensors[2]==3)){
        float dif = distanceSensors[2] -distanceSensors[1];
        newPWM2(dif);
        Nop();
    }
}

void findWave(){
    do{
        getDistances();
        if((statusSensors[1]==3)&&(statusSensors[2]==3)){
            if((distanceSensors[2]>25)&&(distanceSensors[1]>25)){
                Right();
                miliWait(4000);
                Left();
                miliWait(4000);
                Stop();
            }
        }
    }while((distanceSensors[2]>35)&&(distanceSensors[1]>35));
}

int moveEdge(){
    while(1){
        getEdge();
        if(statusSensors[3]==3){
            controlPared2();
            if(distanceSensors[3]>10){
                Stop();
                Right();
                miliWait(500);
                Stop();
                return 0;
            }
            else if((distanceSensors[1]>20)||(distanceSensors[2]>20)){
                return 1;
            }
            else{
                Left();
            }
        }
    }
    newPWM(0);
    newPWM2(0);
}
void findPiece(){
    Right();
    miliWait(15000);
    acercar();
    alinear();
    Backward();
    miliWait(200);
    RotateRight();
    miliWait(2600);
    Stop();
    miliWait(1000);
    RotateLeft();
    miliWait(2200);
    acercar();
    Stop();
}
int main(void){
    SYSTEMConfigPerformance(SYSCLK);
    INTEnableSystemMultiVectoredInt();
    int cont=1;
    int piece=3;
    int nPiece=1;
    while(state != 2000) {
        switch(state) {
        //Reset state
        case 0:
            Stop();
            initPIC32Config();
            initHW();
            state++;
            break;
        //Check align to lane for precise flame detection
        case 1:
            getDistances();
            alignInitialPosition();
            state = 9999;
            break;
        //Send order to Raspberry Pi to check flame
        case 2:
            

            break;
        //Find piece
        case 3:
            findPiece();
            state=1001;
            break;
        //FindWave
        case 996:
            TRISE = 0x00;
            PWMConfig();
            configTimer3();
            newPWM(0);
            newPWM2(0);
            Stop();
            findWave();
            Stop();
            state=997;
            break;
        //Align
        case 997:
            Stop();
            alinear();
            Stop();
            state=998;
            break;
        //Move Forward/Backward
        case 998:
            newPWM(0);
            newPWM2(0);
            Stop();
            acercar();
            state=999;
            break;
        //Move Right
        case 999:
            Stop();
            newPWM(0);
            newPWM2(0);
            do{
                controlPared();
                Right();
            }while((distanceSensors[1]<15)&&(distanceSensors[2]<15));
            Stop();
            state=1000;
            break;
        //Align to the next step
        case 1000:
            newPWM(0);
            newPWM2(0);
            do{
                getDistances();
                if((statusSensors[1]==3)&&(statusSensors[2]==3)){
                    Right();
                }
            }while((distanceSensors[1]<15)||(distanceSensors[2]<15));
            miliWait(400);
            Forward();
            cont++;
            if(cont == 3){
                miliWait(4700);
            }
            else{
                miliWait(4100);
            }
            Stop();
            state=1001;
            break;
        //Find whether there is a wave in front
        case 1001:
            getDistances();
            if(cont<4){
                if((statusSensors[1]==3)&&(statusSensors[2]==3)){
                    if((distanceSensors[1]>45)||(distanceSensors[2]>45)){
                        cont++;
                        Forward();
                        if(cont == 3){
                            miliWait(4700);
                        }
                        else{
                            miliWait(4100);
                        }
                        Stop();
                        state=1001;
                    }
                    else{
                        state=1006;
                    }
                }
            }
            else{
                state=1006;
            }
            /*
            if(cont<4){
                do{
                    getDistances();
                    if((statusSensors[1]==3)&&(statusSensors[2]==3)){
                        Forward();
                    }
                }while((distanceSensors[1]>10)&&(distanceSensors[2]>10));
                Stop();
                 state=1002;
            }
            else
            {
             //   Forward();
             //   miliWait(4000);
             //   Stop();
                do{
                    getEdge();
                    if(statusSensors[3]==3){
                        if(distanceSensors[3]>10){
                            Stop();
                            Right();
                            miliWait(500);
                            Stop();
                            state=1003;
                        }
                        else{
                            Left();
                        }
                    }
                }while(state!=1003);
            }*/
            break;
        //Find Edge or next step
        case 1002:
            newPWM(0);
            newPWM2(0);
            if(moveEdge()){
                newPWM(0);
                newPWM2(0);
                do{
                    getDistances();
                    if((statusSensors[1]==3)&&(statusSensors[2]==3)){
                        Left();
                    }
                }while((distanceSensors[1]<15)||(distanceSensors[2]<15));
                miliWait(400);
                cont++;
                Forward();
                if(cont == 3){
                    miliWait(4700);
                }
                else{
                    miliWait(4100);
                }
                Stop();
                state=1001;
            }
            else{
                state=997;
            }
            break;
        //Find yellow piece
        case 1003:
            newPWM(0);
            newPWM2(0);
            do{
                getDistances();
                if(statusSensors[1]==3){
                    if(distanceSensors[1]<45){
                        switch(piece){
                            case 1:
                                miliWait(1500);
                                Stop();
                                state=1004;
                                break;
                            case 2:
                                if (nPiece!=2){
                                    nPiece++;
                                    miliWait(2500);
                                }
                                else{
                                    miliWait(1500);
                                    Stop();
                                    state=1004;
                                }
                                break;
                            case 3:
                                if (nPiece!=3){
                                    nPiece++;
                                    miliWait(2500);
                                }
                                else{
                                    miliWait(1500);
                                    Stop();
                                    state=1004;
                                }
                                break;
                        }
                    }
                    else{
                        Right();
                    }
                }
            }while(state != 1004);
            break;
        //Approach the yellow piece
        case 1004:
            do{
                getDistances();
                if(statusSensors[1]==3){
                    if(distanceSensors[1]>5){
                        Forward();
                    }
                    else{
                       Stop();
                       state=1005;
                    }
                }
            }while(state != 1005);
            break;
        //Find the target
        case 1005:
            do{
                getDistances();
                if(statusSensors[1]==3){
                    if(distanceSensors[1]>10){
                        Stop();
                        Left();
                        miliWait(220);
                        Stop();
                        state=2000;
                    }
                    else{
                       Right();
                    }
                }
            }while(state != 2000);
            break;
         case 1006:
                if(cont<4){
                    do{
                        getDistances();
                        if((statusSensors[1]==3)&&(statusSensors[2]==3)){
                            Forward();
                        }
                    }while((distanceSensors[1]>10)&&(distanceSensors[2]>10));
                    Stop();
                    state=1002;
                }
                else{
                    do{
                        getEdge();
                        if(statusSensors[3]==3){
                            if(distanceSensors[3]>10){
                                Stop();
                                Right();
                                miliWait(500);
                                Stop();
                                state=1003;
                            }
                            else{
                                Left();
                            }
                        }
                    }while(state!=1003);
                }
              break;
        case 9999:
            Stop();
            break; 
        }
    }
}