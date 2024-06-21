/**
 * PINS Generated Driver Header File 
 * 
 * @file      pins.h
 *            
 * @defgroup  pinsdriver Pins Driver
 *            
 * @brief     The Pin Driver directs the operation and function of 
 *            the selected device pins using dsPIC MCUs.
 *
 * @skipline @version   Firmware Driver Version 1.0.2
 *
 * @skipline @version   PLIB Version 1.3.0
 *
 * @skipline  Device : dsPIC33CK256MP508
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

#ifndef PINS_H
#define PINS_H
// Section: Includes
#include <xc.h>

// Section: Device Pin Macros

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RE10 GPIO Pin which has a custom name of SW1 to High
 * @pre      The RE10 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define SW1_SetHigh()          (_LATE10 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RE10 GPIO Pin which has a custom name of SW1 to Low
 * @pre      The RE10 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define SW1_SetLow()           (_LATE10 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RE10 GPIO Pin which has a custom name of SW1
 * @pre      The RE10 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define SW1_Toggle()           (_LATE10 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RE10 GPIO Pin which has a custom name of SW1
 * @param    none
 * @return   none  
 */
#define SW1_GetValue()         _RE10

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RE10 GPIO Pin which has a custom name of SW1 as Input
 * @param    none
 * @return   none  
 */
#define SW1_SetDigitalInput()  (_TRISE10 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RE10 GPIO Pin which has a custom name of SW1 as Output
 * @param    none
 * @return   none  
 */
#define SW1_SetDigitalOutput() (_TRISE10 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RE11 GPIO Pin which has a custom name of SW2 to High
 * @pre      The RE11 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define SW2_SetHigh()          (_LATE11 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RE11 GPIO Pin which has a custom name of SW2 to Low
 * @pre      The RE11 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define SW2_SetLow()           (_LATE11 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RE11 GPIO Pin which has a custom name of SW2
 * @pre      The RE11 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define SW2_Toggle()           (_LATE11 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RE11 GPIO Pin which has a custom name of SW2
 * @param    none
 * @return   none  
 */
#define SW2_GetValue()         _RE11

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RE11 GPIO Pin which has a custom name of SW2 as Input
 * @param    none
 * @return   none  
 */
#define SW2_SetDigitalInput()  (_TRISE11 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RE11 GPIO Pin which has a custom name of SW2 as Output
 * @param    none
 * @return   none  
 */
#define SW2_SetDigitalOutput() (_TRISE11 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RE12 GPIO Pin which has a custom name of LED1 to High
 * @pre      The RE12 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define LED1_SetHigh()          (_LATE12 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RE12 GPIO Pin which has a custom name of LED1 to Low
 * @pre      The RE12 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define LED1_SetLow()           (_LATE12 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RE12 GPIO Pin which has a custom name of LED1
 * @pre      The RE12 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define LED1_Toggle()           (_LATE12 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RE12 GPIO Pin which has a custom name of LED1
 * @param    none
 * @return   none  
 */
#define LED1_GetValue()         _RE12

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RE12 GPIO Pin which has a custom name of LED1 as Input
 * @param    none
 * @return   none  
 */
#define LED1_SetDigitalInput()  (_TRISE12 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RE12 GPIO Pin which has a custom name of LED1 as Output
 * @param    none
 * @return   none  
 */
#define LED1_SetDigitalOutput() (_TRISE12 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RE13 GPIO Pin which has a custom name of LED2 to High
 * @pre      The RE13 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define LED2_SetHigh()          (_LATE13 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RE13 GPIO Pin which has a custom name of LED2 to Low
 * @pre      The RE13 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define LED2_SetLow()           (_LATE13 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RE13 GPIO Pin which has a custom name of LED2
 * @pre      The RE13 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define LED2_Toggle()           (_LATE13 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RE13 GPIO Pin which has a custom name of LED2
 * @param    none
 * @return   none  
 */
#define LED2_GetValue()         _RE13

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RE13 GPIO Pin which has a custom name of LED2 as Input
 * @param    none
 * @return   none  
 */
#define LED2_SetDigitalInput()  (_TRISE13 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RE13 GPIO Pin which has a custom name of LED2 as Output
 * @param    none
 * @return   none  
 */
#define LED2_SetDigitalOutput() (_TRISE13 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Initializes the PINS module
 * @param    none
 * @return   none  
 */
void PINS_Initialize(void);



#endif
