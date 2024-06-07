/*
 * Multi-motor control (experimental)
 *
 * Move two or three motors at the same time.
 * This module is still work in progress and may not work well or at all.
 *
 * Copyright (C)2017 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>
#include "BasicStepperDriver.h"
#include "MultiDriver.h"
#include "SyncDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
// Target RPM for X axis motor
#define MOTOR_BOTTLE_RPM 100
// Target RPM for Y axis motor
#define MOTOR_GLASS_RPM 100

#define ENABLE_BOTTLE 12
#define ENABLE_GLASS  9

// X motor
#define DIR_BOTTLE 10
#define STEP_BOTTLE 11

// Y motor
#define DIR_GLASS 7
#define STEP_GLASS 8

// If microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS 2

#define BOTTLE_UP 6
#define BOTTLE_DOWN 5
#define GLASS_UP 3
#define GLASS_DOWN 4

int bottle_up;
int bottle_down;
int bottle_enable;
int glass_up;
int glass_down;
int glass_enable;

// 2-wire basic config, microstepping is hardwired on the driver
// Other drivers can be mixed and matched but must be configured individually
BasicStepperDriver stepperBOTTLE(MOTOR_STEPS, DIR_BOTTLE, STEP_BOTTLE);
BasicStepperDriver stepperGLASS(MOTOR_STEPS, DIR_GLASS, STEP_GLASS);

// Pick one of the two controllers below
// each motor moves independently, trajectory is a hockey stick
// MultiDriver controller(stepperX, stepperY);
// OR
// synchronized move, trajectory is a straight line
SyncDriver controller(stepperBOTTLE, stepperGLASS);

void setup() {
  Serial.begin(115200);
  Serial.println("bottle tap started....");
  Serial.println("==========================");
  /*
    * Set target motors RPM.
    */
  Serial.print("init motors ... ");
  stepperBOTTLE.begin(MOTOR_BOTTLE_RPM, MICROSTEPS);
  stepperGLASS.begin(MOTOR_GLASS_RPM, MICROSTEPS);
  Serial.println("done !");
  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next two lines
  // stepperX.setEnableActiveState(LOW);
  // stepperY.setEnableActiveState(LOW);

  pinMode(BOTTLE_UP, INPUT);
  pinMode(BOTTLE_DOWN, INPUT);

  pinMode(GLASS_UP, INPUT);
  pinMode(GLASS_DOWN, INPUT);

  pinMode(ENABLE_BOTTLE, OUTPUT);
  pinMode(ENABLE_GLASS, OUTPUT);

  digitalWrite(ENABLE_BOTTLE,HIGH);

}

void loop() {
  //Serial.println("loop !");

  bottle_up = digitalRead(BOTTLE_UP);
  bottle_down = digitalRead(BOTTLE_DOWN);
  glass_up = digitalRead(GLASS_UP);
  glass_down = digitalRead(GLASS_DOWN);
  

  if (bottle_up == LOW) {
    
    Serial.print("BOTTLE UP ");
    controller.rotate(1, 0);
    
  } else {
    
    
  }

  if (bottle_down == LOW) {
    
    Serial.print("BOTTLE DOWN ");
    controller.rotate(-1, 0);
    
  } else {
    
    
  }

    if (glass_up == LOW) {
    Serial.print("GLASS UP ");
    
  } else {
    
    
  }

  if (glass_down == LOW) {
    Serial.print("GLASS DOWN ");
    
  } else {
    
    
  }
  Serial.println();

  // controller.rotate(180, 0);
  // delay(1000);
  // controller.rotate(-180, 0);
  // // delay(1000);
  // // controller.rotate(0, -30*15);
  // delay(2000);

  // controller.rotate(0, 180);
  // delay(1000);
  // controller.rotate(0,-180);
  // // delay(1000);
  // // controller.rotate(0, -30*15);
  // delay(2000);
}
