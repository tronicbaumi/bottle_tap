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

// If microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS 2

#define AUTO 0

#define STEPS  1

// BOTTLE motor
#define MOTOR_BOTTLE_RPM 100
#define DIR_BOTTLE 10
#define STEP_BOTTLE 11
#define BOTTLE_UP 6
#define BOTTLE_DOWN 5
#define BOTTLE_END 13
#define ENABLE_BOTTLE 12
#define BOTTLE_MAX_POS 3800


// GLASS motor
#define MOTOR_GLASS_RPM 100
#define DIR_GLASS 7
#define STEP_GLASS 8
#define GLASS_UP 3
#define GLASS_DOWN 4
#define GLASS_END 2
#define ENABLE_GLASS  9
#define GLASS_MAX_POS 3600


#define MANUAL_FILL
int manual_fill = 255;

// 0.33 longneck beer
int bottle_auto_pos[12]=   {2100,  500,  100,  100,  200,  250,  250, 0, 0, 0, 0, 0};
int glass_auto_pos[12]=    {3200, -500, -200, -200, -400, -900, -900, 0, 0, 0, 0, 0};

int bottle_auto_speed[12]={  100,  100,   30,   10,   10,   10,   10, 0, 0, 0, 0, 0};
int glass_auto_speed[12]= {  100,   40,   40,   40,   40,   40,   10, 0, 0, 0, 0, 0};



int bottle_up;
int bottle_down;
int bottle_enable;
int bottle_pos;
int bottle_pos_old;
int glass_up;
int glass_down;
int glass_enable;
int glass_pos;
int glass_pos_old;

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

  pinMode(BOTTLE_UP, INPUT);
  pinMode(BOTTLE_DOWN, INPUT);

  pinMode(GLASS_UP, INPUT);
  pinMode(GLASS_DOWN, INPUT);
  pinMode(GLASS_END, INPUT);

  pinMode(ENABLE_BOTTLE, OUTPUT);
  pinMode(ENABLE_GLASS, OUTPUT);
  pinMode(BOTTLE_END, INPUT);

  digitalWrite(ENABLE_BOTTLE,HIGH);
  digitalWrite(ENABLE_GLASS,HIGH);

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

  digitalWrite(ENABLE_BOTTLE,LOW);
  digitalWrite(ENABLE_GLASS,LOW);

  
  ZeroPos();


}

void loop() {
  //Serial.println("loop !");

  bottle_up = digitalRead(BOTTLE_UP);
  bottle_down = digitalRead(BOTTLE_DOWN);
  glass_up = digitalRead(GLASS_UP);
  glass_down = digitalRead(GLASS_DOWN);

  if(!glass_down & !glass_up)
  {
    Serial.println("Auto");
    manual_fill = 0;
  }

  if(!bottle_up & !glass_up & !bottle_down & !glass_down)
  {
    Serial.println("Zero.....");
    ZeroPos();
  }

  if(!bottle_down & !glass_down)
  {
    Serial.println("Manual");
    manual_fill = 255;
  }

  if(manual_fill == 255)
  {
    Manual();
  }
  else
  {
    Auto();
  }


// #ifdef MANUAL_FILL
//   Manual();
// #else
//   Auto();
// #endif
  
  

  if(glass_pos != glass_pos_old or bottle_pos != bottle_pos_old)
  {
    Serial.print(bottle_pos);Serial.print(" ");Serial.println(glass_pos);
    bottle_pos_old = bottle_pos;
    glass_pos_old = glass_pos;
  }
}


void Manual(void)
{
  
  if (bottle_up == LOW & bottle_pos < BOTTLE_MAX_POS) 
  {
    
    Serial.print("BOTTLE UP ");
    controller.rotate(STEPS, 0);
    bottle_pos = bottle_pos + STEPS;
    
  } 
  else 
  {
    
    
  }

  if (bottle_down == LOW & bottle_pos > 0) 
  {
    
    Serial.print("BOTTLE DOWN ");
    controller.rotate(-STEPS, 0);
    bottle_pos = bottle_pos - STEPS;
    
  } 
  else
  {
    
    
  }

  if (glass_up == LOW & glass_pos < GLASS_MAX_POS) 
  {
    Serial.print("GLASS UP ");
    controller.rotate(0, STEPS);
    glass_pos = glass_pos + STEPS;
  } 
  else 
  {
    
    
  }

  if (glass_down == LOW & glass_pos > 0) 
  {
    Serial.print("GLASS DOWN ");
    controller.rotate(0, -STEPS);
    glass_pos = glass_pos - STEPS;
    
  } 
  else 
  {
    
    
  }


}

void Auto(void)
{
  ZeroPos();
  for(int i=0;i<10;i++)
  {
    stepperBOTTLE.begin(bottle_auto_speed[i], MICROSTEPS);
    stepperGLASS.begin(glass_auto_speed[i], MICROSTEPS); 
    controller.rotate(bottle_auto_pos[i],glass_auto_pos[i]);
    bottle_pos = bottle_pos + bottle_auto_pos[i];
    glass_pos = glass_pos + glass_auto_pos[i];
    Serial.print(i);Serial.print("  ");Serial.print(bottle_pos);Serial.print("  ");Serial.println(glass_pos);
    delay(1000);
  }
  Serial.println("Done!");
  delay(2000);
  ZeroPos();

  manual_fill = 255;

}

void ZeroPos(void)
{
  Serial.println("Bottle Zero.....");
  stepperBOTTLE.begin(MOTOR_BOTTLE_RPM, MICROSTEPS);
  stepperGLASS.begin(MOTOR_GLASS_RPM, MICROSTEPS);
  while(digitalRead(BOTTLE_END))
  {
    controller.rotate(-1, 0);
  }
  bottle_pos=0;
  Serial.println("Done!");
  Serial.println("Glass Zero.....");
  while(digitalRead(GLASS_END))
  {
    controller.rotate(0,-1);
  }
  glass_pos=0;
  Serial.println("Done!");
}