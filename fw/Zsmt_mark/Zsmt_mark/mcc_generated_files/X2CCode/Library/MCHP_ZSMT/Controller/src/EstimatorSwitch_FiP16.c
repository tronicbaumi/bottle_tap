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
#include "EstimatorSwitch_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(EstimatorSwitch_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define PHI_LOW			(*pTEstimatorSwitch_FiP16->phi_L)		/* estimated rotor angle from sensorless algorithm for low speeds */
#define PHI_HIGH		(*pTEstimatorSwitch_FiP16->phi_H)		/* estimated rotor angle from sensorless algorithm for high speeds */
#define N_LOW			(*pTEstimatorSwitch_FiP16->n_L)			/* estimated rotor speed from sensorless algorithm for low speeds */
#define N_HIGH			(*pTEstimatorSwitch_FiP16->n_H)			/* estimated rotor speed from sensorless algorithm for high speeds */

/* Outputs */
#define PHI 		    (pTEstimatorSwitch_FiP16->phi)			/* chosen estimated rotor angle */
#define N			    (pTEstimatorSwitch_FiP16->n)			/* chosen estimated rotor speed */
#define ENABLE_LOW		(pTEstimatorSwitch_FiP16->Enable_L)		/* enable signal for low speed estimator */
#define ENABLE_HIGH		(pTEstimatorSwitch_FiP16->Enable_H)		/* enable signal for high speed estimator */

/* Parameter */
#define THRESH_UP		(pTEstimatorSwitch_FiP16->thresh_up)	/* speed up threshold: above this speed high speed estimator is used */
#define THRESH_DOWN		(pTEstimatorSwitch_FiP16->thresh_down)  /* speed down threshold: below this speed low speed estimator is used */

/* Variables */
#define STATE 	        (pTEstimatorSwitch_FiP16->status)	    /* current state of internal state machine */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void EstimatorSwitch_FiP16_Update(ESTIMATORSWITCH_FIP16 *pTEstimatorSwitch_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    int16 absN;

    /* calculate absolute speed */
    absN = getAbsValI16(N);
    
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
void EstimatorSwitch_FiP16_Init(ESTIMATORSWITCH_FIP16 *pTEstimatorSwitch_FiP16)
{
    pTEstimatorSwitch_FiP16->ID = ESTIMATORSWITCH_FIP16_ID;
    pTEstimatorSwitch_FiP16->phi = 0;
    pTEstimatorSwitch_FiP16->n = 0;
    pTEstimatorSwitch_FiP16->Enable_H = 0;
    pTEstimatorSwitch_FiP16->Enable_L = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    /* start with estimator for low speeds */
    STATE = 0;
    ENABLE_LOW = true;
    
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 EstimatorSwitch_FiP16_Load(const ESTIMATORSWITCH_FIP16 *pTEstimatorSwitch_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)4 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTEstimatorSwitch_FiP16->thresh_up & 0x00FF);
        data[1] = (uint8)((pTEstimatorSwitch_FiP16->thresh_up >> 8) & 0x00FF);
        data[2] = (uint8)(pTEstimatorSwitch_FiP16->thresh_down & 0x00FF);
        data[3] = (uint8)((pTEstimatorSwitch_FiP16->thresh_down >> 8) & 0x00FF);
        *dataLength = (uint16)4;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 EstimatorSwitch_FiP16_Save(ESTIMATORSWITCH_FIP16 *pTEstimatorSwitch_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)4)
    {
        error = (uint8)1;
    }
    else
    {
        pTEstimatorSwitch_FiP16->thresh_up = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTEstimatorSwitch_FiP16->thresh_down = UINT16_TO_INT16((uint16)data[2] + \
            ((uint16)data[3] << 8));
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(ESTIMATORSWITCH_FIP16_ISLINKED)
void* EstimatorSwitch_FiP16_GetAddress(const ESTIMATORSWITCH_FIP16* block, uint16 elementId)
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
