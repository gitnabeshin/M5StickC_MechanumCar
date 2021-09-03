#ifndef __MOTOR_DRIVE_H__
#define __MOTOR_DRIVE_H__

#include <Arduino.h>

//Motor Pin
//     (front)
//   [M1]    [M3]
//    |       |
//    |       |
//   [M2]    [M4]
const int M1_IN_A = 2;  //LEFT Front
const int M1_IN_B = 3;  //LEFT Front
const int M2_IN_A = 4;  //LEFT Rear
const int M2_IN_B = 5;  //LEFT Rear
const int M3_IN_A = 6;  //RIGHT Front 
const int M3_IN_B = 7;  //RIGHT Front
const int M4_IN_A = 8;  //RIGHT Rear
const int M4_IN_B = 9;  //RIGHT Rear

//direction
#define MOTOR_STOP              0x00
#define MOTOR_FORWARD           0x01
#define MOTOR_LEFT_FORWARD      0x02
#define MOTOR_RIGHT_FORWARD     0x03
#define MOTOR_LEFT              0x04
#define MOTOR_RIGHT             0x05
#define MOTOR_LEFT_BACKWARD     0x06
#define MOTOR_RIGHT_BACKWARD    0x07
#define MOTOR_BACKWARD          0x08
#define MOTOR_RIGHT_ROTATE      0x10
#define MOTOR_LEFT_ROTATE       0x11

void motor_setup(void);
void motor_test(void);

void motor_stop(void);
void motor_forward(void);
void motor_backward(void);

void motor_left_forward(void);
void motor_left(void);
void motor_left_backward(void);
void motor_left_rotate(void);

void motor_right_forward(void);
void motor_right(void);
void motor_right_backward(void);
void motor_right_rotate(void);

// direction 
// motor_speed: 0 to 128
void motor_wire_value( uint8_t direction, uint8_t motor_speed );

#endif /* __MOTOR_DRIVE_H__ */
