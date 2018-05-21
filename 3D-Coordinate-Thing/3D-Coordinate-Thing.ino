#include <Arduino.h>
#include "BasicStepperDriver.h"

#define MOTOR_STEPS 200
#define RPM 3500
#define MICROSTEPS 1

BasicStepperDriver stepper_x(MOTOR_STEPS, 55, 54, 38);
BasicStepperDriver stepper_y(MOTOR_STEPS, 61, 60, 56);
BasicStepperDriver stepper_z(MOTOR_STEPS, 48, 46, 62);

int prev_x = 0;
int prev_y = 0;
int prev_z = 0;

void setup() {
    Serial.begin(9600);
    stepper_x.begin(RPM, MICROSTEPS);
    stepper_y.begin(RPM, MICROSTEPS);
    stepper_z.begin(RPM, MICROSTEPS);
}

void loop() {
  while(Serial.available()) {
    String str = Serial.readString();
    int c1 = str.indexOf(',');
    int c2 = str.lastIndexOf(',');
    String _x = str.substring(0, c1);
    String _y = str.substring(c1+1, c2);
    String _z = str.substring(c2+1, str.length()-1);
    int x = _x.toInt();
    int y = _y.toInt();
    int z = _z.toInt();
    stepper_x.enable();
    stepper_y.enable();
    stepper_z.enable();
    if(x > 0) {
      while(x-->0) {
        stepper_x.move(MOTOR_STEPS*4);   
      }
    }
    else {
      while(x++<0) {
        stepper_x.move(-MOTOR_STEPS*4);   
      }
    }
    if(y > 0) {
      while(y-->0) {
        stepper_y.move(MOTOR_STEPS*4);   
      }
    }
    else {
      while(y++<0) {
        stepper_y.move(-MOTOR_STEPS*4);   
      }
    }
    if(z > 0) {
      while(z-->0) {
        stepper_z.move(MOTOR_STEPS*200);   
      }
    }
    else {
      while(z++<0) {
        stepper_z.move(-MOTOR_STEPS*200);   
      }
    }
    stepper_x.disable();
    stepper_y.disable();
    stepper_z.disable();
  }
}
