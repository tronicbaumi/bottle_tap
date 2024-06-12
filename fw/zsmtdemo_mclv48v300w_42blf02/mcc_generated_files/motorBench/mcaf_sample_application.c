#include <stdint.h>
#include <stdbool.h>
#include "mcapi.h"
#include "mcaf_sample_application.h"
#include "util.h"
#include "board_service.h"
#include "hal/hardware_access_functions.h"
#include "system_state.h"

#define ROTATION_COUNT_THRESHOLD 20 // number of rotations after zero position

APPLICATION_DATA app;
int8_t position_sensor;
void APP_TimerCallback(void);

typedef enum {
    INIT_DOWNWARD,
    INIT_UPWARD,
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
                int16_t potentiometerValue = MCAF_BoardServicePotentiometerValue(pboard);
                appData->motorVelocityCommand = APP_DetermineVelocityCommand(appData, potentiometerValue);
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
                appState = INIT_UPWARD; // Transition to the next state
            }
            break;

        case INIT_UPWARD:
            if (appData->rotationCounter < ROTATION_COUNT_THRESHOLD)
            {
                // Rotate the motor upwards for a few rotations to prevent damage to the sensor
                appData->motorDirection = 1;
                appData->motorVelocityCommand = appData->motorVelocityCommandMinimum;
                MCAPI_VelocityReferenceSet(apiData, appData->motorVelocityCommand);

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

                // Increment the rotation counter
                appData->rotationCounter++;
            }
            else
            {
                appState = NORMAL_OPERATION; // Transition to normal operation
            }
            break;

        case NORMAL_OPERATION:
            if (appData->hardwareUiEnabled)
            {
                // Use potentiometer to set motor velocity command
                int16_t potentiometerValue = MCAF_BoardServicePotentiometerValue(pboard);
                appData->motorVelocityCommand = APP_DetermineVelocityCommand(appData, potentiometerValue);
                MCAPI_VelocityReferenceSet(apiData, appData->motorVelocityCommand);

                // Determine direction based on button presses and sensor values
                if (MCAF_ButtonGp2_EventGet(pboard) && !MCAF_ButtonGp1_EventGet(pboard) && !appData->zeroPositionDetected)
                {
                    appData->motorDirection = -1;
                    MCAPI_MOTOR_STATE motorState = MCAPI_OperatingStatusGet(apiData);
                    if (motorState == MCAPI_MOTOR_STOPPED || motorState == MCAPI_MOTOR_STOPPING)
                    {
                        MCAPI_MotorStart(apiData);
                    }
                }
                else if (MCAF_ButtonGp1_EventGet(pboard) && !MCAF_ButtonGp2_EventGet(pboard) && !appData->maxPositionDetected)
                {
                    appData->motorDirection = 1;
                    MCAPI_MOTOR_STATE motorState = MCAPI_OperatingStatusGet(apiData);
                    if (motorState == MCAPI_MOTOR_STOPPED || motorState == MCAPI_MOTOR_STOPPING)
                    {
                        MCAPI_MotorStart(apiData);
                    }
                }
                else
                {
                    // If no button is pressed, stop the motor
                    MCAPI_MOTOR_STATE motorState = MCAPI_OperatingStatusGet(apiData);
                    if (motorState == MCAPI_MOTOR_STARTING || motorState == MCAPI_MOTOR_RUNNING)
                    {
                        MCAPI_MotorStop(apiData);
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
void position_Check(APPLICATION_DATA *appData)
{
    volatile MCAPI_MOTOR_DATA *apiData = appData->apiData;
    MCAF_BOARD_DATA *pboard = appData->pboard;
    position_sensor = Position_sensor_GetValue();
    
    if (position_sensor == 0 && appData->motorDirection == -1)
    {
        app.zeroPositionDetected = true;
        app.maxPositionDetected = false; // Reset the max position flag
        app.rotationCounter = 0; // Reset the rotation counter
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
    else if (position_sensor == 0 && appData->motorDirection == 1)
    {
        app.maxPositionDetected = true;
        app.zeroPositionDetected = false; // Reset the zero position flag
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

void APP_TimerCallback(void)
{
    position_Check(&app);
    MCAF_BoardServiceTasks(app.pboard);
    APP_ApplicationStep(&app);
}
