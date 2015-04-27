#include <p32xxxx.h>
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

#include "uart.h"
#include "robotics.h"

//Channel 0 - Right ultrasonic edge detector
//Channel 1 - Left ultrasonic edge detector
//Channel 2 - Right ultrasonic wall distance
//Channel 3 - Left ultrasonic wall distance
//Channel 4 -
//Channel 5 -


/* pwmControl
 * ---------------------------------
 * Sends rotation angle to the servo controller throught UART2
 *
 * servoChannel: selects the servo motor to control
 * range: angle in digital format to rotate the servo motor (0 to 254)
 *
 */
void pwmControl(int servoChannel, int range) {
    char data[] = {0xFF, servoChannel, range};
    transmitDataUART2(&data[0], 3);
}