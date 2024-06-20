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

#define Upper_limit 1450000
#define Lower_Limit 0 
int32_t Calculated_position = 0;
/** Global instance of the main set of motor state variables */
extern MCAF_MOTOR_DATA motor;

APPLICATION_DATA app;
int8_t position_sensor;
void APP_TimerCallback(void);

typedef enum {
    INIT_DOWNWARD,
    NORMAL_OPERATION
} APP_STATE;

APP_STATE appState = INIT_DOWNWARD; // Initialize the application state

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
    return unsignedSpeed * app->motorDirection;
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
    appData->zeroPositionDetected = false; // Initialize the zero position flag
    appData->maxPositionDetected = false;  // Initialize the max position flag
    appData->rotationCounter = 0;          // Initialize the rotation counter
    HAL_TMR_TICK_SetCallbackFunction(APP_TimerCallback);
}

void APP_ApplicationStep(APPLICATION_DATA *appData)
{
    volatile MCAPI_MOTOR_DATA *apiData = appData->apiData;
    MCAF_BOARD_DATA *pboard = appData->pboard;

    switch (appState)
    {
        case INIT_DOWNWARD:
            if (!appData->zeroPositionDetected)
            {
         
                // Run the motor in downwards direction until zero position is detected
                //int16_t potentiometerValue = MCAF_BoardServicePotentiometerValue(pboard);
                appData->motorVelocityCommand = APP_DetermineVelocityCommand(appData, 1000);
                MCAPI_VelocityReferenceSet(apiData, appData->motorVelocityCommand);
                appData->motorDirection = -1;

                MCAPI_MOTOR_STATE motorState = MCAPI_OperatingStatusGet(apiData);
                switch (motorState)
                {
                    case MCAPI_MOTOR_STOPPED:
                    case MCAPI_MOTOR_STOPPING:
                    {
                        MCAPI_MotorStart(apiData);
                        break;
                    }
                    case MCAPI_MOTOR_FAULT:
                    {
                        uint16_t faultFlags = MCAPI_FaultStatusGet(apiData);
                        MCAPI_FaultStatusClear(apiData, faultFlags);
                        break;
                    }
                    case MCAPI_MOTOR_DIAGSTATE:
                    {
                        /* do nothing */
                        break;
                    }
                }
            }
            else
            {
                appState = NORMAL_OPERATION; // Transition to normal operation
            }
            break;

        case NORMAL_OPERATION:
            if (appData->hardwareUiEnabled)
            {
                Calculated_position += motor.apiData.velocityMeasured ; 
                // Use potentiometer to set motor velocity command
                //int16_t potentiometerValue = MCAF_BoardServicePotentiometerValue(pboard);
                appData->motorVelocityCommand = APP_DetermineVelocityCommand(appData, 100);
                MCAPI_VelocityReferenceSet(apiData, appData->motorVelocityCommand);

                // Determine direction based on button presses and sensor values
                if (MCAF_ButtonGp2_EventGet(pboard) && !MCAF_ButtonGp1_EventGet(pboard) && Calculated_position > Lower_Limit  )
                {
                    appData->motorDirection = -1;
                    
                        MCAPI_MOTOR_STATE motorState = MCAPI_OperatingStatusGet(apiData); //YA
                         switch (motorState)
                        {
                            case MCAPI_MOTOR_STOPPED:
                            case MCAPI_MOTOR_STOPPING:
                            {
                                MCAPI_MotorStart(apiData);
                                break;
                            }
                            case MCAPI_MOTOR_FAULT:
                            {
                                uint16_t faultFlags = MCAPI_FaultStatusGet(apiData);
                                MCAPI_FaultStatusClear(apiData, faultFlags);
                                break;
                            }
                            case MCAPI_MOTOR_DIAGSTATE:
                            {
                                /* do nothing */
                                break;
                            }
                        }   
                    
                }
                else if (MCAF_ButtonGp1_EventGet(pboard) && !MCAF_ButtonGp2_EventGet(pboard) && Calculated_position < Upper_limit)
                {
                    appData->motorDirection = 1;  //YA
              
                    
                        MCAPI_MOTOR_STATE motorState = MCAPI_OperatingStatusGet(apiData);
                        switch (motorState)
                        {
                            case MCAPI_MOTOR_STOPPED:
                            case MCAPI_MOTOR_STOPPING:
                            {
                                MCAPI_MotorStart(apiData);
                                break;
                            }
                            case MCAPI_MOTOR_FAULT:
                            {
                                uint16_t faultFlags = MCAPI_FaultStatusGet(apiData);
                                MCAPI_FaultStatusClear(apiData, faultFlags);
                                break;
                            }
                            case MCAPI_MOTOR_DIAGSTATE:
                            {
                                /* do nothing */
                                break;
                            }
                           
                        }
                }
                else
                {
                    // If no button is pressed, stop the motor
                    MCAPI_MOTOR_STATE motorState = MCAPI_OperatingStatusGet(apiData);
                     switch (motorState)
                        {
                            case MCAPI_MOTOR_STARTING:
                            case MCAPI_MOTOR_RUNNING:
                            {
                                MCAPI_MotorStop(apiData);
                                break;
                            }
                            case MCAPI_MOTOR_FAULT:
                            {
                                uint16_t faultFlags = MCAPI_FaultStatusGet(apiData);
                                MCAPI_FaultStatusClear(apiData, faultFlags);
                                break;
                            }
                            case MCAPI_MOTOR_DIAGSTATE:
                            {
                                /* do nothing */
                                break;
                            }
                           
                        }
                }
            }
            break;
    }
}

/**
 * This is an application owned timer the user is responsible for configuring. 
 * The application timer period needs to match the value set in motorBench Customize page.
 */
void position_Check(APPLICATION_DATA *appData) //YA
{
    volatile MCAPI_MOTOR_DATA *apiData = appData->apiData;
    MCAF_BOARD_DATA *pboard = appData->pboard;
    position_sensor = Position_sensor_GetValue();
    
    if (position_sensor == 0 && appData->motorDirection == -1)
    {
        app.zeroPositionDetected = true;
        app.maxPositionDetected = false; // Reset the max position flag
        app.rotationCounter = 0; // Reset the rotation counter
    }
    else if (position_sensor == 0 && appData->motorDirection == 1)
    {
        app.maxPositionDetected = true;
        app.zeroPositionDetected = false; // Reset the zero position flag
    }
}

void APP_TimerCallback(void)
{
    position_Check(&app); //YA
    MCAF_BoardServiceTasks(app.pboard);
    APP_ApplicationStep(&app);
}
