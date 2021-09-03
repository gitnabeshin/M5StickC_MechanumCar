#include "MotorDrive.h"

#define DELAY_TIME (500)

void motor_setup() {
    pinMode(M1_IN_A, OUTPUT);
    pinMode(M1_IN_B, OUTPUT);
    pinMode(M2_IN_A, OUTPUT);
    pinMode(M2_IN_B, OUTPUT);
    pinMode(M3_IN_A, OUTPUT);
    pinMode(M3_IN_B, OUTPUT);
    pinMode(M4_IN_A, OUTPUT);
    pinMode(M4_IN_B, OUTPUT);
}

void motor_stop() {
    digitalWrite(M1_IN_A, 0);
    digitalWrite(M1_IN_B, 0);
    digitalWrite(M2_IN_A, 0);
    digitalWrite(M2_IN_B, 0);
    digitalWrite(M3_IN_A, 0);
    digitalWrite(M3_IN_B, 0);
    digitalWrite(M4_IN_A, 0);
    digitalWrite(M4_IN_B, 0);
    delay(DELAY_TIME);
}

void motor_forward() {
    digitalWrite(M1_IN_A, 1);
    digitalWrite(M1_IN_B, 0);
    digitalWrite(M2_IN_A, 1);
    digitalWrite(M2_IN_B, 0);
    digitalWrite(M3_IN_A, 1);
    digitalWrite(M3_IN_B, 0);
    digitalWrite(M4_IN_A, 1);
    digitalWrite(M4_IN_B, 0);
    delay(DELAY_TIME);
}

void motor_left_forward() {
    digitalWrite(M1_IN_A, 0);
    digitalWrite(M1_IN_B, 0);
    digitalWrite(M2_IN_A, 1);
    digitalWrite(M2_IN_B, 0);
    digitalWrite(M3_IN_A, 1);
    digitalWrite(M3_IN_B, 0);
    digitalWrite(M4_IN_A, 0);
    digitalWrite(M4_IN_B, 0);
    delay(DELAY_TIME);
}

void motor_left() {
    digitalWrite(M1_IN_A, 0);
    digitalWrite(M1_IN_B, 1);
    digitalWrite(M2_IN_A, 1);
    digitalWrite(M2_IN_B, 0);
    digitalWrite(M3_IN_A, 1);
    digitalWrite(M3_IN_B, 0);
    digitalWrite(M4_IN_A, 0);
    digitalWrite(M4_IN_B, 1);
    delay(DELAY_TIME);
}

void motor_left_backward() {
    digitalWrite(M1_IN_A, 0);
    digitalWrite(M1_IN_B, 1);
    digitalWrite(M2_IN_A, 0);
    digitalWrite(M2_IN_B, 0);
    digitalWrite(M3_IN_A, 0);
    digitalWrite(M3_IN_B, 0);
    digitalWrite(M4_IN_A, 0);
    digitalWrite(M4_IN_B, 1);
    delay(DELAY_TIME);
}

void motor_backward() {
    digitalWrite(M1_IN_A, 0);
    digitalWrite(M1_IN_B, 1);
    digitalWrite(M2_IN_A, 0);
    digitalWrite(M2_IN_B, 1);
    digitalWrite(M3_IN_A, 0);
    digitalWrite(M3_IN_B, 1);
    digitalWrite(M4_IN_A, 0);
    digitalWrite(M4_IN_B, 1);
    delay(DELAY_TIME);
}

void motor_right_backward() {
    digitalWrite(M1_IN_A, 0);
    digitalWrite(M1_IN_B, 0);
    digitalWrite(M2_IN_A, 0);
    digitalWrite(M2_IN_B, 1);
    digitalWrite(M3_IN_A, 0);
    digitalWrite(M3_IN_B, 1);
    digitalWrite(M4_IN_A, 0);
    digitalWrite(M4_IN_B, 0);
    delay(DELAY_TIME);
}

void motor_right() {
    digitalWrite(M1_IN_A, 1);
    digitalWrite(M1_IN_B, 0);
    digitalWrite(M2_IN_A, 0);
    digitalWrite(M2_IN_B, 1);
    digitalWrite(M3_IN_A, 0);
    digitalWrite(M3_IN_B, 1);
    digitalWrite(M4_IN_A, 1);
    digitalWrite(M4_IN_B, 0);
    delay(DELAY_TIME);
}

void motor_right_forward() {
    digitalWrite(M1_IN_A, 1);
    digitalWrite(M1_IN_B, 0);
    digitalWrite(M2_IN_A, 0);
    digitalWrite(M2_IN_B, 0);
    digitalWrite(M3_IN_A, 0);
    digitalWrite(M3_IN_B, 0);
    digitalWrite(M4_IN_A, 1);
    digitalWrite(M4_IN_B, 0);
    delay(DELAY_TIME);
}

void motor_right_rotate() {
    digitalWrite(M1_IN_A, 1);
    digitalWrite(M1_IN_B, 0);
    digitalWrite(M2_IN_A, 1);
    digitalWrite(M2_IN_B, 0);
    digitalWrite(M3_IN_A, 0);
    digitalWrite(M3_IN_B, 1);
    digitalWrite(M4_IN_A, 0);
    digitalWrite(M4_IN_B, 1);
    delay(DELAY_TIME);
}

void motor_left_rotate() {
    digitalWrite(M1_IN_A, 0);
    digitalWrite(M1_IN_B, 1);
    digitalWrite(M2_IN_A, 0);
    digitalWrite(M2_IN_B, 1);
    digitalWrite(M3_IN_A, 1);
    digitalWrite(M3_IN_B, 0);
    digitalWrite(M4_IN_A, 1);
    digitalWrite(M4_IN_B, 0);
    delay(DELAY_TIME);
}

void motor_test() {

    motor_stop();
    motor_forward();
    motor_backward();

    motor_left_forward();
    motor_left();
    motor_left_backward();

    motor_stop();
    motor_right_forward();
    motor_right();
    motor_right_backward();

    motor_stop();
    motor_left_rotate();
    motor_stop();
    motor_right_rotate();
}
