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
#include "mcc_generated_files/X2CCode/X2CUtils.h"
#include "mcc_generated_files/X2CCode/X2CMain.h"
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/adc/adc1.h"
#include "pwm_hs/pwm.h"
#include "userparms.h"
#include "system/pins.h"
#include "system/clock.h"
#include "system/interrupt.h"
#include "qei/qei1.h"

#include <stdbool.h>

//Local function
bool measureOffset(void);
void errorTrap(void);
/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();
    PWM_Enable(); // Enable PWM, by default doe not start (MCC config)
    QEI1_Enable();
    
    INTERRUPT_GlobalDisable();
    
    if( measureOffset() == false){ //if offset measure fail
        errorTrap(); // Stop operation
    }
    
    INTERRUPT_GlobalEnable(); // Start MC and X2C calculation at interrupt    
    
    while(1)
    {
        X2C_Communicate();
    }    
}

void ADC1_CommonCallback (void)
{ 
    X2C_Task();
} 


/**
 * Measure offset before starting the motor control algorithm
 * ADC sampling must be triggered automatically
 * @return true - if measurement successful
 *         false - if offset is too high
 */

#define FCY CLOCK_InstructionFrequencyGet()
#include <libpic30.h>

extern int16_t offset_AN1_IA, offset_AN4_IB;
bool measureOffset(void){
    uint32_t adcOffsetIa = 0, adcOffsetIb = 0, adcOffsetIc = 0;
    uint32_t i = 0;
    bool result = false;

    LED2_SetHigh(); // Signal the measurement is running
    __delay_ms(10); //wait some measurements
    /* Taking multiple samples to measure voltage
     * offset in all the channels */
    for (i = 0; i < CURRENT_OFFSET_SAMPLE_COUNT; i++)
    {
        while(!IFS5bits.ADCAN4IF); //Wait until both AN1 and AN4 conversion not complete
        
        /* Sum up the converted results */
        adcOffsetIa = adcOffsetIa - (int16_t)ADC1_ConversionResultGet(I_A);
        adcOffsetIb = adcOffsetIb - (int16_t)ADC1_ConversionResultGet(I_B);
        
        IFS5bits.ADCAN4IF = 0;
    }
    
    /* Averaging to find current offsets */
    offset_AN1_IA = (int16_t) (adcOffsetIa >> CURRENT_OFFSET_SAMPLE_SCALER);
    offset_AN4_IB = (int16_t) (adcOffsetIb >> CURRENT_OFFSET_SAMPLE_SCALER);
    
    LED2_SetLow(); // Signal the measurement is finished
    result = true;
    
    //Check, if offset not too high
    if( offset_AN1_IA > 0) {
        if( offset_AN1_IA > CURRENT_MAX_OFFSET) result = false; //Offset over the limit
    }
    else{
        if(offset_AN1_IA < (-((int16_t)CURRENT_MAX_OFFSET))) result = false; //Offset over the limit (negative)
    }
    if( offset_AN4_IB > 0) {
        if( offset_AN4_IB > CURRENT_MAX_OFFSET) result = false; //Offset over the limit
    }
    else{
        if(offset_AN4_IB < (-((int16_t)CURRENT_MAX_OFFSET))) result = false; //Offset over the limit (negative)
    }

    return result;
}

void errorTrap(void){
    while(1){
        __delay_ms(100);
        LED2_Toggle(); // 10Hz blinking
        
    }
}