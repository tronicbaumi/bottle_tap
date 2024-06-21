/* ************************************************************************** */
/** X2CMain.c

  @Company
    Microchip Technology

  @Summary
 Implementation of X2C In and Outport connections

 */
/* ************************************************************************** */
#include <xc.h>
#include "X2CMain.h"
#include "X2C.h"
#include "../userparms.h"
#include "../adc/adc1.h"
#include "../system/pins.h"
#include "pwm_hs/pwm.h"
#include "qei/qei1.h"

#ifndef X2C_H
#warning "Please generate the code from the model!"
#endif

    static unsigned int pwmFaultCounter = 0;
    static unsigned int pwmFaultActive = 0;
    static unsigned char S2_Value;
    static unsigned char S2_Value_old = 1;
    static unsigned char DebounceCnt;
    static unsigned char edge=0;
    static int16_t CpuLoad;
    static uint16_t POS1CNTtemp;

    volatile int16_t offset_AN1_IA=0, offset_AN4_IB=0;

void UpdateInports(void) {

    /*
     * Pass the peripheral values to model Inports
     * if (PORTA & 1) { 
     *    x2cModel.inports.bInport = INT16_MAX;
     * }else {
     *    x2cModel.inports.bInport = 0;
     * }
     * 
     * The following inputs of the model can be used:
      x2cModel.inports.bCPU_LOAD = Scaling*A_PeripheralVariable
      x2cModel.inports.bI_a = Scaling*A_PeripheralVariable
      x2cModel.inports.bI_b = Scaling*A_PeripheralVariable
      x2cModel.inports.bI_sum = Scaling*A_PeripheralVariable
      x2cModel.inports.bQEI_POS = Scaling*A_PeripheralVariable
      x2cModel.inports.bQEI_VEL = Scaling*A_PeripheralVariable
      x2cModel.inports.bSW1 = Scaling*A_PeripheralVariable
      x2cModel.inports.bSW2 = Scaling*A_PeripheralVariable
      x2cModel.inports.bV_POT = Scaling*A_PeripheralVariable

     */
    
    if(SW1_GetValue() == 0) x2cModel.inports.bS3 = false;
    else  x2cModel.inports.bS3 = true;
    
    /* Button latch and debounce */
    S2_Value = SW2_GetValue();
    
    if(edge==0)
    {
        if (S2_Value != S2_Value_old) 
        {
            S2_Value_old = S2_Value;
            if(S2_Value)
            {
                DebounceCnt = 0;
                edge = 1;
            }
        }
    }
    else
    {
        DebounceCnt++;
        if(DebounceCnt >= 10)
        {           
            if(x2cModel.inports.bS2==0)
            {
                x2cModel.inports.bS2 = INT16_MAX;
            }
            else
            {
                x2cModel.inports.bS2 = 0;
                /* Clear PWM fault */
                pwmFaultCounter = 0;
                pwmFaultActive = 0;
                PG1FPCILbits.SWTERM = 1;
                PG2FPCILbits.SWTERM = 1;
                PG3FPCILbits.SWTERM = 1;
            }
            
            DebounceCnt = 0;
            edge=0;
        }    
    }  

#ifdef FAULT_ON
    /* Handle PWM fault */
    if(_PWM1IF == 1)
    {
        _PWM1IF = 0;
        pwmFaultActive = 1;
        /* stop Motor */
        x2cModel.inports.bS3 = false;           //Switch off Motor
        x2cModel.inports.bS2 = false;           //Switch off Status LED
    }
    
    /* If PWM fault is active, clear it after a preset
     * duration of time and then allow the motor to start up */
    if(pwmFaultActive == 1)
    {
        if(pwmFaultCounter < 20000)
        {
            pwmFaultCounter++;
            x2cModel.inports.bS2 = false;   //Set LED to show restart possibility
        }
        else
        {
            /* Clear PWM fault */
            pwmFaultCounter = 0;
            pwmFaultActive = 0;
            PG1FPCILbits.SWTERM = 1;
            PG2FPCILbits.SWTERM = 1;
            PG3FPCILbits.SWTERM = 1;
        }
    }
#endif

    /* ADC */   
    //x2cModel.inports.bI_sum = ADC1_ConversionResultGet(???)
    x2cModel.inports.bI_a = (-ADCBUF1) - offset_AN1_IA; 
    x2cModel.inports.bI_b = (-ADCBUF4) - offset_AN4_IB;
    x2cModel.inports.bV_POT = ADCBUF17;   

    //Encoder caculation
    x2cModel.inports.bQEI_POS = (int16_t) (__builtin_mulss(QEI1_PositionCount16bitRead(), QEI_FACT));
//    x2cModel.inports.bQEI_VEL = QEI;
    
    x2cModel.inports.bCPU_LOAD = CpuLoad;
    

}

void UpdateOutports(void) {
    
    /*
     * Pass model outports to peripherals e.g.:
     * 
     * if (*x2cModel.outports.bOutport) {  // if model Outport differ than zero 
     *    LATB |= 1; // set LATB0 
     * } else {
     *    LATB &= ~1; // clear LATB0
     * }    
     * 
     * The following outputs of the model can be used:
      A_PeripheralVariable = *x2cModel.outports.bEstimated_angle*Scaling
      A_PeripheralVariable = *x2cModel.outports.bEstimated_speed*Scaling
      A_PeripheralVariable = *x2cModel.outports.bHOME_INIT*Scaling
      A_PeripheralVariable = *x2cModel.outports.bLED1*Scaling
      A_PeripheralVariable = *x2cModel.outports.bLED2*Scaling
      A_PeripheralVariable = *x2cModel.outports.bPWM1*Scaling
      A_PeripheralVariable = *x2cModel.outports.bPWM2*Scaling
      A_PeripheralVariable = *x2cModel.outports.bPWM3*Scaling
     */    
    
    if (x2cModel.inports.bS2)
    {
        PG1IOCONLbits.OVRENH = 0;
        PG1IOCONLbits.OVRENL = 0;
        PG2IOCONLbits.OVRENH = 0;
        PG2IOCONLbits.OVRENL = 0;
        PG3IOCONLbits.OVRENH = 0;
        PG3IOCONLbits.OVRENL = 0;        
        
        PG1DC = (PWM_PERIODE+(int16)(__builtin_mulss(*x2cModel.outports.bPWM1, PWM_PERIODE)>>15));
        PG2DC = (PWM_PERIODE+(int16)(__builtin_mulss(*x2cModel.outports.bPWM2, PWM_PERIODE)>>15));
        PG3DC = (PWM_PERIODE+(int16)(__builtin_mulss(*x2cModel.outports.bPWM3, PWM_PERIODE)>>15));
    }
    else
    {
        PG1DC = 0;
        PG2DC = 0;
        PG3DC = 0;        
        PG1IOCONLbits.OVRDAT = 0;
        PG2IOCONLbits.OVRDAT = 0;
        PG3IOCONLbits.OVRDAT = 0;
        PG1IOCONLbits.OVRENH = 1;
        PG1IOCONLbits.OVRENL = 1;
        PG2IOCONLbits.OVRENH = 1;
        PG2IOCONLbits.OVRENL = 1;
        PG3IOCONLbits.OVRENH = 1;
        PG3IOCONLbits.OVRENL = 1;        
        
    }
    
    /* Clear position counter on Home init */
    if (*x2cModel.outports.bHOME_INIT > 0) { 
    	QEI1_PositionCountWrite(0); //*x2cModel.outports.bHOME_INIT;
    }
    
    if (*x2cModel.outports.bCONTROL_ENABLED) {
        LED1_SetHigh();
    }
    else {
        LED1_SetLow();
    }    
    
    if (*x2cModel.outports.bTHETA_ERROR) {
        LED2_SetHigh();
    }
    else {
        LED2_SetLow();
    }

}
/**
 * Calls the inports update function
 * Then run model calculation
 * Last read model outports and update the peripherals
*/
/*
 * The selected model update mode is manual.
 * The X2C_Task() have to be called manually!
 * Note:
 * The model X2C sample time frequency must be the same 
 * as the X2C_X2C_Task() call frequency. 
*/

 void X2C_Task (void){
    UpdateInports();
    X2C_Update();
    UpdateOutports();
}


/* *****************************************************************************
 End of File
 */
