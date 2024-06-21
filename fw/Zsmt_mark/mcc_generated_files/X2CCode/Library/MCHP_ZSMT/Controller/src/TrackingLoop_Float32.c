/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1603 $
 * $LastChangedDate:: 2019-01-21 19:02:13 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "TrackingLoop_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TrackingLoop_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define PHI_EPS         (*pTTrackingLoop_Float32->phi_eps)
#define INIT_SPEED      (*pTTrackingLoop_Float32->n0)
#define INIT_PHI        (*pTTrackingLoop_Float32->phi0)
#define ENABLE          (*pTTrackingLoop_Float32->Enable)

/* Outputs */
#define SPEED           (pTTrackingLoop_Float32->n)
#define PHI             (pTTrackingLoop_Float32->phi)

/* Parameters */
#define V_GAIN          (pTTrackingLoop_Float32->vGain)
#define B0_T            (pTTrackingLoop_Float32->b0_torque)
#define B1_T            (pTTrackingLoop_Float32->b1_torque)
#define B0_S            (pTTrackingLoop_Float32->b0_speed)
#define B1_S            (pTTrackingLoop_Float32->b1_speed)
#define B0_A            (pTTrackingLoop_Float32->b0_angle)
#define B1_A            (pTTrackingLoop_Float32->b1_angle)
#define USE_RAW_SPEED   (pTTrackingLoop_Float32->rawSpeed)

/* Variables */
#define ENABLE_OLD      (pTTrackingLoop_Float32->enable_old)
#define I_OLD_T         (pTTrackingLoop_Float32->i_old_torque)
#define I_OLD_S         (pTTrackingLoop_Float32->i_old_speed)
#define I_OLD_A         (pTTrackingLoop_Float32->i_old_angle)

/* Macros */
#define LIMIT_ANGLE(angle)  do{\
                                while ((angle) >= PI_R32)\
                                {\
                                    (angle) = (angle) - (2.0f * PI_R32);\
                                }\
                                while ((angle) < - PI_R32)\
                                {\
                                    (angle) = (angle) + (2.0f * PI_R32);\
                                }\
                            }while(0)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TrackingLoop_Float32_Update(TRACKINGLOOP_FLOAT32 *pTTrackingLoop_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    if (ENABLE)
    {
        float32 y, yp;
        float32 temp, tempSpeed, tempAngle;

        /** - pre-load integrator and output values */
        if (!ENABLE_OLD)    /* rising edge of enable signal occurred */
        {
            /* preset integrator values */
            I_OLD_T = 0;            /* torque init */
            I_OLD_S = INIT_SPEED;   /* speed init */
            I_OLD_A = INIT_PHI;     /* angle init */

            /* preset outputs */
            SPEED = INIT_SPEED;
            PHI = INIT_PHI;
        }

        /* save enable value for next cycle */
        ENABLE_OLD = ENABLE;

        /*--------------------------------------------------------------------------------------------------------*/
        /* calculate angle and speed estimates
         * PLL PI-Controller: feeding controller with filtered angle error signal
         */
        /* ******************************* */
        /* first integrator stage (torque) */
        /* proportional term */
        yp = B1_T * PHI_EPS;

        /* sum of proportional and integral term */
        y = yp + I_OLD_T;

        /* integral term */
        I_OLD_T += (B0_T * PHI_EPS);

        /* ******************************* */
        /* second integrator stage (speed) */
        /* calculate proportional term */
        tempSpeed = V_GAIN * PHI_EPS;

        /* add integrator term */
        yp = B1_S * y;                  /* proportional term of integrator: if bilinear transform is used b1 is different from 0 */
        temp = yp + I_OLD_S;
        tempSpeed += temp;

        /* integral term */
        I_OLD_S += (B0_S * y);

        /* ****************************** */
        /* third integrator stage (angle) */
        /* calculate rotor angle estimate */
        yp = B1_A * tempSpeed;          /* proportional term of integrator: if bilinear-transform is used b1 is different from 0 */
        tempAngle = yp + I_OLD_A;
        LIMIT_ANGLE(tempAngle);         /* angle limitation to -pi...+pi */

        /* integral term */
        I_OLD_A += (B0_A * tempSpeed);
        LIMIT_ANGLE(I_OLD_A);           /* angle limitation to -pi...+pi */

        /* ouput angle */
        PHI = tempAngle;

        /* calculate angular speed estimate */
        if (USE_RAW_SPEED)
        {
            SPEED = tempSpeed; /* high dynamic range */
        }
        else
        {
            SPEED = temp;      /* less noise */
        }
    }
    else
    {
        /* reset outputs */
        SPEED = 0;
        PHI = 0;

        /* reset variables */
        ENABLE_OLD = false;
    }
/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void TrackingLoop_Float32_Init(TRACKINGLOOP_FLOAT32 *pTTrackingLoop_Float32)
{
    pTTrackingLoop_Float32->ID = TRACKINGLOOP_FLOAT32_ID;
    pTTrackingLoop_Float32->n = 0;
    pTTrackingLoop_Float32->phi = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    I_OLD_T = 0;            /* torque init */
    I_OLD_S = INIT_SPEED;   /* speed init */
    I_OLD_A = INIT_PHI;     /* angle init */
    ENABLE_OLD = false;
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TrackingLoop_Float32_Load(const TRACKINGLOOP_FLOAT32 *pTTrackingLoop_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)29 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->vGain)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->vGain) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->vGain) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->vGain) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b0_torque)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b0_torque) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b0_torque) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b0_torque) >> 24) & 0x000000FF);
        data[8] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b1_torque)) & 0x000000FF);
        data[9] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b1_torque) >> 8) & 0x000000FF);
        data[10] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b1_torque) >> 16) & 0x000000FF);
        data[11] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b1_torque) >> 24) & 0x000000FF);
        data[12] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b0_speed)) & 0x000000FF);
        data[13] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b0_speed) >> 8) & 0x000000FF);
        data[14] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b0_speed) >> 16) & 0x000000FF);
        data[15] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b0_speed) >> 24) & 0x000000FF);
        data[16] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b1_speed)) & 0x000000FF);
        data[17] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b1_speed) >> 8) & 0x000000FF);
        data[18] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b1_speed) >> 16) & 0x000000FF);
        data[19] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b1_speed) >> 24) & 0x000000FF);
        data[20] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b0_angle)) & 0x000000FF);
        data[21] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b0_angle) >> 8) & 0x000000FF);
        data[22] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b0_angle) >> 16) & 0x000000FF);
        data[23] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b0_angle) >> 24) & 0x000000FF);
        data[24] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b1_angle)) & 0x000000FF);
        data[25] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b1_angle) >> 8) & 0x000000FF);
        data[26] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b1_angle) >> 16) & 0x000000FF);
        data[27] = (uint8)((*(uint32*)&(pTTrackingLoop_Float32->b1_angle) >> 24) & 0x000000FF);
        data[28] = (uint8)pTTrackingLoop_Float32->rawSpeed;
        *dataLength = (uint16)29;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TrackingLoop_Float32_Save(TRACKINGLOOP_FLOAT32 *pTTrackingLoop_Float32, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint32 tmp32;

    if (dataLength != (uint16)29)
    {
        error = (uint8)1;
    }
    else
    {
        tmp32 = (uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24);
        pTTrackingLoop_Float32->vGain = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTTrackingLoop_Float32->b0_torque = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24);
        pTTrackingLoop_Float32->b1_torque = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[12] + \
            ((uint32)data[13] << 8) + ((uint32)data[14] << 16) + \
            ((uint32)data[15] << 24);
        pTTrackingLoop_Float32->b0_speed = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[16] + \
            ((uint32)data[17] << 8) + ((uint32)data[18] << 16) + \
            ((uint32)data[19] << 24);
        pTTrackingLoop_Float32->b1_speed = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[20] + \
            ((uint32)data[21] << 8) + ((uint32)data[22] << 16) + \
            ((uint32)data[23] << 24);
        pTTrackingLoop_Float32->b0_angle = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[24] + \
            ((uint32)data[25] << 8) + ((uint32)data[26] << 16) + \
            ((uint32)data[27] << 24);
        pTTrackingLoop_Float32->b1_angle = (float32)(*(float32*)&tmp32);
        pTTrackingLoop_Float32->rawSpeed = ((uint8)data[28]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TRACKINGLOOP_FLOAT32_ISLINKED)
void* TrackingLoop_Float32_GetAddress(const TRACKINGLOOP_FLOAT32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->phi_eps;
            break;
        case 2:
            addr = (void*)block->n0;
            break;
        case 3:
            addr = (void*)block->phi0;
            break;
        case 4:
            addr = (void*)block->Enable;
            break;
        case 5:
            addr = (void*)&block->n;
            break;
        case 6:
            addr = (void*)&block->phi;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
