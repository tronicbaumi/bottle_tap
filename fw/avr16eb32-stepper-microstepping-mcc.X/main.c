 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include <stdio.h>
#include "mcc_generated_files/system/system.h"
#include "util/delay.h"
#include "stepper.h"

bool DriveToZeroPosition(stepper_position_t position, stepper_position_t sub_steps, uint16_t count_delay)
{
    bool zero_position = false;
    uint8_t sensordata;
    sensordata = PositionSensor_GetValue();
    while(PositionSensor_GetValue() == 0)
    {
        LED_SetHigh();
        position = Stepper_Move(position, -sub_steps, count_delay);
    }
    
    LED_SetLow();
    zero_position = true;
    
    return zero_position;
}

stepper_position_t MainMove(stepper_position_t position, stepper_position_t displacement, uint16_t count_delay)
{
    position = Stepper_Move(position, displacement, count_delay);
    return position;
}

int main(void)
{
    stepper_position_t stepper_position = 0;

    /* System initialize */
    SYSTEM_Initialize();

    Stepper_Init();
    
    _delay_ms(2000);
    stepper_position_t sub_steps;
    sub_steps = STEPS_TO_SUBSTEPS(25);        /* Positive: CW, Negative: CCW */
    uint16_t           count_delay;
    count_delay = RPS_TO_COUNT(1);            /* revolutions per second */
    
    bool zero_position = false;

    while(1)
    {
        while (!zero_position)
        {
            zero_position = DriveToZeroPosition(stepper_position, sub_steps, count_delay);
            continue;
        }

        // For CW
        while(Button1_GetValue() == 0)
        {
            LED_SetHigh();
            stepper_position = MainMove(stepper_position, sub_steps, count_delay);
        }

        // For CCW
        while(Button2_GetValue() == 0)
        {
            LED_SetHigh();
            stepper_position = MainMove(stepper_position, -sub_steps, count_delay);
        }
        
        LED_SetLow();  // Ensure LED is off when neither button is pressed
    }
}


