/*
 * Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision: 2108 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description:
    Implements switching policy between sensorless algorithms for low and high speeds.
    Decision base is the speed magnitude. */
/* USERCODE-END:Description                                                                                           */
#include "EstimatorSwitch_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(EstimatorSwitch_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define PHI_LOW			(*pTEstimatorSwitch_Float32->phi_L)		/* estimated rotor angle from sensorless algorithm for low speeds */
#define PHI_HIGH		(*pTEstimatorSwitch_Float32->phi_H)		/* estimated rotor angle from sensorless algorithm for high speeds */
#define N_LOW			(*pTEstimatorSwitch_Float32->n_L)		/* estimated rotor speed from sensorless algorithm for low speeds */
#define N_HIGH			(*pTEstimatorSwitch_Float32->n_H)		/* estimated rotor speed from sensorless algorithm for high speeds */

/* Outputs */
#define PHI 		    (pTEstimatorSwitch_Float32->phi)		/* chosen estimated rotor angle */
#define N			    (pTEstimatorSwitch_Float32->n)			/* chosen estimated rotor speed */
#define ENABLE_LOW		(pTEstimatorSwitch_Float32->Enable_L)	/* enable signal for low speed estimator */
#define ENABLE_HIGH		(pTEstimatorSwitch_Float32->Enable_H)	/* enable signal for high speed estimator */

/* Parameter */
#define THRESH_UP		(pTEstimatorSwitch_Float32->thresh_up)	/* speed up threshold: above this speed high speed estimator is used */
#define THRESH_DOWN		(pTEstimatorSwitch_Float32->thresh_down)/* speed down threshold: below this speed low speed estimator is used */

/* Variables */
#define STATE 	        (pTEstimatorSwitch_Float32->status)	    /* current state of internal state machine */
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void EstimatorSwitch_Float32_Update(ESTIMATORSWITCH_FLOAT32 *pTEstimatorSwitch_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    float32 absN;

    /* calculate absolute speed */
    absN = getAbsValR32(N);
    
    switch (STATE)
    {
        case 0:     /* speed is below lower threshold */
            if (absN >= THRESH_DOWN)
            {
                STATE = 1;
                ENABLE_LOW = true;
                ENABLE_HIGH = true;
            }
            PHI = PHI_LOW;
            N   = N_LOW;
            break;
        case 1:     /* speed is between lower and upper threshold (coming from lower threshold) */
            if (absN >= THRESH_UP)
            {
                STATE = 2;
                ENABLE_LOW = false;
                ENABLE_HIGH = true;
                PHI = PHI_HIGH;
                N   = N_HIGH;
            }
            else
            {
                if (absN < THRESH_DOWN)
                {
                    STATE = 0;
                    ENABLE_LOW = true;
                    ENABLE_HIGH = false;
                }
                PHI = PHI_LOW;
                N   = N_LOW;
            }
            break;
        case 2:     /* speed is above upper threshold */
            if (absN < THRESH_UP)
            {
                STATE = 3;
                ENABLE_LOW = true;
                ENABLE_HIGH = true;
            }
            PHI = PHI_HIGH;
            N   = N_HIGH;
            break;
        case 3:     /* speed is between lower and upper threshold (coming from upper threshold) */
            if (absN < THRESH_DOWN)
            {
                STATE = 0;
                ENABLE_LOW = true;
                ENABLE_HIGH = false;
                PHI = PHI_LOW;
                N   = N_LOW;
            }
            else
            {
                if (absN >= THRESH_UP)
                {
                    STATE = 2;
                    ENABLE_LOW = false;
                    ENABLE_HIGH = true;
                }
                PHI = PHI_HIGH;
                N   = N_HIGH;
            }
            break;
        default:
            STATE = 0;
        break;
    }
    
/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void EstimatorSwitch_Float32_Init(ESTIMATORSWITCH_FLOAT32 *pTEstimatorSwitch_Float32)
{
    pTEstimatorSwitch_Float32->ID = ESTIMATORSWITCH_FLOAT32_ID;
    pTEstimatorSwitch_Float32->phi = 0;
    pTEstimatorSwitch_Float32->n = 0;
    pTEstimatorSwitch_Float32->Enable_H = 0;
    pTEstimatorSwitch_Float32->Enable_L = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    /* start with estimator for low speeds */
    STATE = 0;
    ENABLE_LOW = true;
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 EstimatorSwitch_Float32_Load(const ESTIMATORSWITCH_FLOAT32 *pTEstimatorSwitch_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)8 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTEstimatorSwitch_Float32->thresh_up)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTEstimatorSwitch_Float32->thresh_up) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTEstimatorSwitch_Float32->thresh_up) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTEstimatorSwitch_Float32->thresh_up) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTEstimatorSwitch_Float32->thresh_down)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTEstimatorSwitch_Float32->thresh_down) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTEstimatorSwitch_Float32->thresh_down) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTEstimatorSwitch_Float32->thresh_down) >> 24) & 0x000000FF);
        *dataLength = (uint16)8;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 EstimatorSwitch_Float32_Save(ESTIMATORSWITCH_FLOAT32 *pTEstimatorSwitch_Float32, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint32 tmp32;

    if (dataLength != (uint16)8)
    {
        error = (uint8)1;
    }
    else
    {
        tmp32 = (uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24);
        pTEstimatorSwitch_Float32->thresh_up = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTEstimatorSwitch_Float32->thresh_down = (float32)(*(float32*)&tmp32);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(ESTIMATORSWITCH_FLOAT32_ISLINKED)
void* EstimatorSwitch_Float32_GetAddress(const ESTIMATORSWITCH_FLOAT32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->phi_H;
            break;
        case 2:
            addr = (void*)block->phi_L;
            break;
        case 3:
            addr = (void*)block->n_H;
            break;
        case 4:
            addr = (void*)block->n_L;
            break;
        case 5:
            addr = (void*)&block->phi;
            break;
        case 6:
            addr = (void*)&block->n;
            break;
        case 7:
            addr = (void*)&block->Enable_H;
            break;
        case 8:
            addr = (void*)&block->Enable_L;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
