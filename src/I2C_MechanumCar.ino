#include <Wire.h>
#include "MotorDrive.h"
#include "NeoPixelDrive.h"

#define VEHICLE_ADDR 0x5d   //I2C Address

//Mobile battery poweroff canceller
#define PIN_CANCELLER 10
uint32_t loopCount = 0;
uint32_t batteryPowerLoopCount = 0;

uint8_t preDirection = MOTOR_STOP;

uint8_t testLEDMode = NEOPIXEL_STOP;

// direction
// motor_speed: 0 to 128
void I2C_handle_command( uint8_t direction, uint8_t motor_speed ){

    if( preDirection != direction ){
        motor_stop();
    }
    preDirection = direction;

    switch (direction) {
        case MOTOR_STOP:
            motor_stop();
            neopixel_setMode(NEOPIXEL_STOP);
            break;
        case MOTOR_FORWARD:
            motor_forward();
            neopixel_setMode(NEOPIXEL_FORWARD);
            break;
        case MOTOR_LEFT_FORWARD:
            motor_left_forward();
            neopixel_setMode(NEOPIXEL_FORWARD);
            break;
        case MOTOR_RIGHT_FORWARD:
            motor_right_forward();
            neopixel_setMode(NEOPIXEL_FORWARD);
            break;
        case MOTOR_LEFT:
            motor_left();
            neopixel_setMode(NEOPIXEL_LEFT);
            break;
        case MOTOR_RIGHT:
            motor_right();
            neopixel_setMode(NEOPIXEL_RIGHT);
            break;
        case MOTOR_LEFT_BACKWARD:
            motor_left_backward();
            neopixel_setMode(NEOPIXEL_BACKWARD);
            break;
        case MOTOR_RIGHT_BACKWARD:
            motor_right_backward();
            neopixel_setMode(NEOPIXEL_BACKWARD);
            break;
        case MOTOR_BACKWARD:
            motor_backward();
            neopixel_setMode(NEOPIXEL_BACKWARD);
            break;
        case MOTOR_RIGHT_ROTATE:
            motor_right_rotate();
            neopixel_setMode(NEOPIXEL_RIGHT_ROTATE);
            break;
        case MOTOR_LEFT_ROTATE:
            motor_left_rotate();
            neopixel_setMode(NEOPIXEL_LEFT_ROTATE);
            break;
        default:
            break;
    }
}

void receiveEvent(int numBytes) {

    uint8_t direction = 0;
    uint8_t motor_speed = 0;

    if(Wire.available() > 0){
        direction = Wire.read();
        motor_speed = Wire.read();
        I2C_handle_command(direction, motor_speed);  
    }

}

void setup() {

    Wire.begin(VEHICLE_ADDR);
    Wire.onReceive(receiveEvent);

    Serial.begin(115200);
    Serial.println("ATMega328 initializing...");

    //battry off canceller
    pinMode(PIN_CANCELLER, OUTPUT);

    neopixel_setup();
    motor_setup();
}

void testLED(){
    if(loopCount != 40000){
        return;
    } else {
        testLEDMode++;
        if( testLEDMode == NEOPIXEL_MAX ){
            testLEDMode = NEOPIXEL_STOP;
        }
        neopixel_setMode(testLEDMode);
    }
}

void loop() {

//    testLED();
    neopixel_loop();

    // Battery Auto-OFF cancel.
    // keep about 0.5sec HIGH every 10sec.
    if( loopCount > 1200000 ){
        batteryPowerLoopCount++;
        if(batteryPowerLoopCount < 50000){
            digitalWrite(PIN_CANCELLER, HIGH);
        } else {
            batteryPowerLoopCount = 0;
            loopCount = 0;
        }
    } else {
        digitalWrite(PIN_CANCELLER, LOW);
    }
    loopCount++;
}
