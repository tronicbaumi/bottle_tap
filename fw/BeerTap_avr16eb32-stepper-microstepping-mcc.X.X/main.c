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

#define SPEED_RPM 3
#define STEPS   5
#define HIGH_LIMIT -100000
#define LOW_LIMIT 0
#define BUTTON_PRESS_DURATION_MS 3000  // 3 seconds
#define BUTTON_CHECK_INTERVAL_MS 100  // Check buttons every 100ms

bool DriveToZeroPosition(stepper_position_t position, stepper_position_t sub_steps, uint16_t count_delay)
{
    bool zero_position = false;
    while(PositionSensor_GetValue() == 0)
    {
        LED_SetHigh();
        position = Stepper_Move(position, sub_steps, count_delay);
    }
    
    LED_SetLow();
    zero_position = true;
    
    return zero_position;
}

stepper_position_t stepper_position = 0;

int main(void)
{
    

    /* System initialize */
    SYSTEM_Initialize();

    Stepper_Init();
    
    _delay_ms(2000);
    stepper_position_t sub_steps = STEPS_TO_SUBSTEPS(STEPS);  /* Positive: CW, Negative: CCW */
    uint16_t count_delay = RPS_TO_COUNT(SPEED_RPM);  /* revolutions per second */
    
    bool zero_position = false;
    if (!zero_position)
    {
        zero_position = DriveToZeroPosition(stepper_position, sub_steps, count_delay);
    }
    stepper_position = 0;

    while(1)
    {
        int button1_state = Button1_GetValue();
        int button2_state = Button2_GetValue();
        int both_buttons_pressed_duration = 0;

        if(button1_state == 0 && button2_state == 0)
        {
            while(button1_state == 0 && button2_state == 0 && both_buttons_pressed_duration < BUTTON_PRESS_DURATION_MS)
            {
                _delay_ms(BUTTON_CHECK_INTERVAL_MS);
                both_buttons_pressed_duration += BUTTON_CHECK_INTERVAL_MS;
                button1_state = Button1_GetValue();
                button2_state = Button2_GetValue();
            }

            if (both_buttons_pressed_duration >= BUTTON_PRESS_DURATION_MS)
            {
                // Both buttons are pressed for 3 seconds, move to zero position
                zero_position = DriveToZeroPosition(stepper_position, sub_steps, count_delay);
                if (zero_position)
                {
                    stepper_position = 0;
                }
            }
            else
            {
                // LED flashing
                LED_SetHigh();
                _delay_ms(200);
                LED_SetLow();
                _delay_ms(200);
            }
        }
        else
        {
            if(button1_state == 0) // move DOWN
            {
                // Only Button1 is pressed, move CW
                LED_SetHigh();
                if(stepper_position <= LOW_LIMIT)
                {
                    stepper_position = Stepper_Move(stepper_position, sub_steps, count_delay);
                }
            }
            else if(button2_state == 0) // move UP
            {
                // Only Button2 is pressed, move CCW
                LED_SetHigh();
                if(stepper_position >= HIGH_LIMIT)
                {
                    stepper_position = Stepper_Move(stepper_position, -sub_steps, count_delay);
                }
            }
            else
            {
                // No buttons are pressed, ensure LED is off
                LED_SetLow();
            }
        }
    }
}
