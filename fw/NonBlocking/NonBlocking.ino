/*
 * Example using non-blocking mode to move until a switch is triggered.
 *
 * Copyright (C)2015-2017 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>

// this pin should connect to Ground when want to stop the motor
#define STOPPER_PIN 2

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 120
// Microstepping mode. If you hardwired it to save pins, set to the same value here.
#define MICROSTEPS 1

#define DIR_BOTTLE 10
#define STEP_BOTTLE 11

#define DIR_GLASS 7
#define STEP_GLASS 8
//#define SLEEP 6 // optional (just delete SLEEP from everywhere if not used)

/*
 * Choose one of the sections below that match your board
 */

// #include "DRV8834.h"
// #define M0 10
// #define M1 11
// DRV8834 stepper(MOTOR_STEPS, DIR, STEP, SLEEP, M0, M1);

#include "A4988.h"
#define MS1 6
#define MS2 5
#define MS3 4
A4988 stepper_bottle(MOTOR_STEPS, DIR_BOTTLE, STEP_BOTTLE,  MS1, MS2, MS3);
A4988 stepper_glass(MOTOR_STEPS, DIR_GLASS, STEP_GLASS,  MS1, MS2, MS3);

// #include "DRV8825.h"
// #define MODE0 10
// #define MODE1 11
// #define MODE2 12
// DRV8825 stepper(MOTOR_STEPS, DIR, STEP, SLEEP, MODE0, MODE1, MODE2);

// #include "DRV8880.h"
// #define M0 10
// #define M1 11
// #define TRQ0 6
// #define TRQ1 7
// DRV8880 stepper(MOTORS_STEPS, DIR, STEP, SLEEP, M0, M1, TRQ0, TRQ1);

// #include "BasicStepperDriver.h" // generic
// BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

void setup() {
    Serial.begin(115200);

    // Configure stopper pin to read HIGH unless grounded
    pinMode(STOPPER_PIN, INPUT_PULLUP);
    
    // pinMode(STOPPER_PIN, INPUT_PULLUP);
    // pinMode(STOPPER_PIN, INPUT_PULLUP);

    stepper_bottle.begin(RPM, MICROSTEPS);
    stepper_glass.begin(RPM, MICROSTEPS);
    // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
    stepper_bottle.setEnableActiveState(HIGH);
    stepper_glass.setEnableActiveState(HIGH);
    //stepper.enable();

    // set current level (for DRV8880 only). Valid percent values are 25, 50, 75 or 100.
    // stepper.setCurrent(100);

    Serial.println("START");

    // set the motor to move continuously for a reasonable time to hit the stopper
    // let's say 100 complete revolutions (arbitrary number)
  //  stepper.startMove(100 * MOTOR_STEPS * MICROSTEPS);     // in microsteps
  stepper_glass.startRotate(100 * 360);
   stepper_bottle.startRotate(100 * 360);                     // or in degrees
   
}

void loop() {
    // first, check if stopper was hit
    if (digitalRead(STOPPER_PIN) == LOW){
        Serial.println("STOPPER REACHED");

        /*
         * Choosing stop() vs startBrake():
         *
         * constant speed mode, they are the same (stop immediately)
         * linear (accelerated) mode with brake, the motor will go past the stopper a bit
         */

        stepper_bottle.stop();
        // stepper.startBrake();
    }

    // motor control loop - send pulse and return how long to wait until next pulse
    unsigned wait_time_micros = stepper_bottle.nextAction();

    // 0 wait time indicates the motor has stopped
    if (wait_time_micros <= 0) {
        stepper_bottle.disable();       // comment out to keep motor powered
        delay(3600000);
    }

    // (optional) execute other code if we have enough time
    if (wait_time_micros > 100){
        // other code here
    }
}
