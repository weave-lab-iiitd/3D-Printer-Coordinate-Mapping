#include <Arduino.h>
#include "BasicStepperDriver.h"

#define MOTOR_STEPS 200
#define RPM 3500
#define MICROSTEPS 1

int endstop1 = 3;
int endstop2 = 14;
int endstop3 = 18;

BasicStepperDriver stepper1(MOTOR_STEPS, 55, 54, 38);
BasicStepperDriver stepper2(MOTOR_STEPS, 61, 60, 56);
BasicStepperDriver stepper3(MOTOR_STEPS, 48, 46, 62);

int prev_x = 0;
int prev_y = 0;
int prev_z = 0;

void setup() {
  Serial.begin(9600);
  stepper1.begin(RPM, MICROSTEPS);
  stepper2.begin(RPM, MICROSTEPS);
  stepper3.begin(RPM, MICROSTEPS);
  pinMode(endstop1, INPUT);
  pinMode(endstop2, INPUT);
  pinMode(endstop3, INPUT);
  movex(-30);
  movex(10.5);
  movey(30);
  movey(-6);
  movez(-30);
}

void loop() {
  while (Serial.available()) {
    String str = Serial.readString();
    int c1 = str.indexOf(',');
    int c2 = str.lastIndexOf(',');
    String _x = str.substring(0, c1);
    String _y = str.substring(c1 + 1, c2);
    String _z = str.substring(c2 + 1, str.length() - 1);
    int x = _x.toInt();
    int y = _y.toInt();
    int z = _z.toInt();
    movex(x-prev_x);
    movey(y-prev_y);
    movez(z-prev_z);
    prev_x = x;
    prev_y = y;
    prev_z = z;
  }
}

void movex(float x) {
  stepper2.enable();
  x = x * 10;
  if (x > 0) {
    while (x-- > 0) {
      stepper2.move(MOTOR_STEPS * 0.4);
    }
  }
  else {
    while (x++ < 0) {
      if (digitalRead(endstop2) == false)
        break;
      stepper2.move(-MOTOR_STEPS * 0.4);
    }
  }
  stepper2.disable();
}

void movey(float y) {
  stepper1.enable();
  y = y * 10;
  if (y > 0) {
    while (y-- > 0) {
      if (digitalRead(endstop1) == false)
        break;
      stepper1.move(MOTOR_STEPS * 0.4);
    }
  }
  else {
    while (y++ < 0) {
      stepper1.move(-MOTOR_STEPS * 0.4);
    }
  }
  stepper1.disable();
}

void movez(float z) {
  stepper3.enable();
  z = z * 10;
  if (z > 0) {
    while (z-- > 0) {
      stepper3.move(MOTOR_STEPS * 20);
    }
  }
  else {
    while (z++ < 0) {
      if (digitalRead(endstop3) == false)
        break;
      stepper3.move(-MOTOR_STEPS * 20);
    }
  }
  stepper3.disable();
}

