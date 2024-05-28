/**
 * mcaf_sample_application.c
 *
 * Sample application for MCAF
 * 
 * Component: main application
 */
/*
 *
 * Motor Control Application Framework
 * R7/RC37 (commit 116330, build on 2023 Feb 09)
 *
 * (c) 2017 - 2023 Microchip Technology Inc. and its subsidiaries. You may use
 * this software and any derivatives exclusively with Microchip products.
 *
 * This software and any accompanying information is for suggestion only.
 * It does not modify Microchip's standard warranty for its products.
 * You agree that you are solely responsible for testing the software and
 * determining its suitability.  Microchip has no obligation to modify,
 * test, certify, or support the software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE, OR ITS INTERACTION WITH
 * MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY
 * APPLICATION.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL,
 * PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF
 * ANY KIND WHATSOEVER RELATED TO THE USE OF THIS SOFTWARE, THE
 * motorBench(R) DEVELOPMENT SUITE TOOL, PARAMETERS AND GENERATED CODE,
 * HOWEVER CAUSED, BY END USERS, WHETHER MICROCHIP'S CUSTOMERS OR
 * CUSTOMER'S CUSTOMERS, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
 * CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
 * OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
 * SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF
 * THESE TERMS.
 *
 *
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "mcapi.h"
#include "mcaf_sample_application.h"
#include "util.h"
#include "board_service.h"
#include "hal/hardware_access_functions.h"
#include "system_state.h"

APPLICATION_DATA app;
int8_t position_sensor;
bool zero_position_detected = false;
bool switch_released = false;
uint32_t release_start_time = 0;
uint32_t release_duration_ms = 500; // 0.5 seconds

void APP_TimerCallback(void);

/**
 * Determines the appropriate velocity command for a given input of unipolar
 * speed reference.
 * @param app application state data
 * @param rawUnipolarValue unipolar speed reference input
 * @return velocity command
 */
inline static int16_t APP_DetermineVelocityCommand(APPLICATION_DATA *app, uint16_t rawUnipolarValue)
{
    int16_t velocityRange = app->motorVelocityCommandMaximum - app->motorVelocityCommandMinimum;
    int16_t unsignedSpeed = 
              (UTIL_mulus(rawUnipolarValue, velocityRange) >> 16)
              + app->motorVelocityCommandMinimum;
    return unsignedSpeed*app->motorDirection;
}

void APP_ApplicationInitialize(volatile MCAPI_MOTOR_DATA *apiData, MCAF_BOARD_DATA *pboard)
{
    APPLICATION_DATA *appData = &app;
    
    appData->apiData = apiData;
    appData->motorDirection = 1;
    appData->motorVelocityCommand = MCAPI_VelocityReferenceMinimumGet(apiData);
    appData->hardwareUiEnabled = true;
    appData->motorVelocityCommandMinimum = MCAPI_VelocityReferenceMinimumGet(apiData);
    appData->motorVelocityCommandMaximum = MCAPI_VelocityReferenceMaximumGet(apiData);
    appData->pboard = pboard;
    HAL_TMR_TICK_SetCallbackFunction(APP_TimerCallback);
}

void APP_ApplicationStep(APPLICATION_DATA *appData)
{
    volatile MCAPI_MOTOR_DATA *apiData = appData->apiData;
    MCAF_BOARD_DATA *pboard = appData->pboard;

    // Check if zero position has been detected
    if (!zero_position_detected)
    {
        // Run motor in negative direction to find zero position
        appData->motorDirection = -1;
        appData->motorVelocityCommand = appData->motorVelocityCommandMinimum;
        MCAPI_VelocityReferenceSet(apiData, appData->motorVelocityCommand);
        
        // Check the position sensor
        if (position_sensor == 0)
        {
            zero_position_detected = true;
            switch_released = false;
            release_start_time = HAL_GetTick();
        }
    }
    else if (!switch_released)
    {
        // Run motor in positive direction for 0.5 seconds to release the switch
        appData->motorDirection = 1;
        appData->motorVelocityCommand = appData->motorVelocityCommandMinimum;
        MCAPI_VelocityReferenceSet(apiData, appData->motorVelocityCommand);
        
        if (HAL_GetTick() - release_start_time >= release_duration_ms)
        {
            switch_released = true;
        }
    }
    else
    {
        if (appData->hardwareUiEnabled)
        {
            // Use potentiometer to set motor velocity command
            int16_t potentiometerValue = MCAF_BoardServicePotentiometerValue(pboard);
            appData->motorVelocityCommand = APP_DetermineVelocityCommand(appData, 
                                                                         potentiometerValue);
            MCAPI_VelocityReferenceSet(apiData, appData->motorVelocityCommand);
            
            // Button2 toggles motor direction
            if (MCAF_ButtonGp2_EventGet(pboard) && !MCAF_ButtonGp1_EventGet(pboard))
            {
                appData->motorDirection = -1;
                MCAPI_MOTOR_STATE motorState = MCAPI_OperatingStatusGet(apiData);
                switch (motorState)
                {
                    case MCAPI_MOTOR_STOPPED:
                    case MCAPI_MOTOR_STOPPING:
                        MCAPI_MotorStart(apiData);
                        break;

                    case MCAPI_MOTOR_FAULT:
                        uint16_t faultFlags = MCAPI_FaultStatusGet(apiData);
                        MCAPI_FaultStatusClear(apiData, faultFlags);
                        break;

                    case MCAPI_MOTOR_DIAGSTATE:
                        // do nothing
                        break;
                }
            }
            else if (!MCAF_ButtonGp2_EventGet(pboard) && !MCAF_ButtonGp1_EventGet(pboard))
            {
                MCAPI_MOTOR_STATE motorState = MCAPI_OperatingStatusGet(apiData);
                switch (motorState)
                {
                    case MCAPI_MOTOR_STARTING:
                    case MCAPI_MOTOR_RUNNING:
                        MCAPI_MotorStop(apiData);
                        break;

                    case MCAPI_MOTOR_FAULT:
                        uint16_t faultFlags = MCAPI_FaultStatusGet(apiData);
                        MCAPI_FaultStatusClear(apiData, faultFlags);
                        break;

                    case MCAPI_MOTOR_DIAGSTATE:
                        // do nothing
                        break;
                }
            }
            
            // Button1 toggles motor state + clears motor fault
            if (MCAF_ButtonGp1_EventGet(pboard) && !MCAF_ButtonGp2_EventGet(pboard))
            {
                appData->motorDirection = 1;
                MCAPI_MOTOR_STATE motorState = MCAPI_OperatingStatusGet(apiData);
                switch (motorState)
                {
                    case MCAPI_MOTOR_STOPPED:
                    case MCAPI_MOTOR_STOPPING:
                        MCAPI_MotorStart(apiData);
                        break;

                    case MCAPI_MOTOR_FAULT:
                        uint16_t faultFlags = MCAPI_FaultStatusGet(apiData);
                        MCAPI_FaultStatusClear(apiData, faultFlags);
                        break;

                    case MCAPI_MOTOR_DIAGSTATE:
                        // do nothing
                        break;
                }
            }
            else if (!MCAF_ButtonGp1_EventGet(pboard) && !MCAF_ButtonGp2_EventGet(pboard))
            {
                MCAPI_MOTOR_STATE motorState = MCAPI_OperatingStatusGet(apiData);
                switch (motorState)
                {
                    case MCAPI_MOTOR_STARTING:
                    case MCAPI_MOTOR_RUNNING:
                        MCAPI_MotorStop(apiData);
                        break;

                    case MCAPI_MOTOR_FAULT:
                        uint16_t faultFlags = MCAPI_FaultStatusGet(apiData);
                        MCAPI_FaultStatusClear(apiData, faultFlags);
                        break;

                    case MCAPI_MOTOR_DIAGSTATE:
                        // do nothing
                        break;
                }        
            }
        }
    }
}

/**
 * This is an application owned timer the user is responsible for configuring. 
 * The application timer period needs to match the value set in motorBench Customize page.
 */
void position_Check()
{
    position_sensor = Position_sensor_GetValue();
}

void APP_TimerCallback(void)
{
    position_Check();
    MCAF_BoardServiceTasks(app.pboard);
    APP_ApplicationStep(&app);
}

