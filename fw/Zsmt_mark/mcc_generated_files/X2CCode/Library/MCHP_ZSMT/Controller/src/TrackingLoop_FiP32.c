/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1603 $
 * $LastChangedDate:: 2019-01-21 19:02:13 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "TrackingLoop_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TrackingLoop_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define PHI_EPS         (*pTTrackingLoop_FiP32->phi_eps)
#define INIT_SPEED      (*pTTrackingLoop_FiP32->n0)
#define INIT_PHI        (*pTTrackingLoop_FiP32->phi0)
#define ENABLE          (*pTTrackingLoop_FiP32->Enable)

/* Outputs */
#define SPEED           (pTTrackingLoop_FiP32->n)
#define PHI             (pTTrackingLoop_FiP32->phi)

/* Parameters */
#define V_GAIN          (pTTrackingLoop_FiP32->vGain)
#define SFR_GAIN        (pTTrackingLoop_FiP32->sfrGain)
#define B0_T            (pTTrackingLoop_FiP32->b0_torque)      /* Qx */
#define B1_T            (pTTrackingLoop_FiP32->b1_torque)      /* Qy */
#define SFRB0_T         (pTTrackingLoop_FiP32->sfrb0_torque)   /* x */
#define SFRB1_T         (pTTrackingLoop_FiP32->sfrb1_torque)   /* y */
#define B0_S            (pTTrackingLoop_FiP32->b0_speed)       /* Qx */
#define B1_S            (pTTrackingLoop_FiP32->b1_speed)       /* Qy */
#define SFRB0_S         (pTTrackingLoop_FiP32->sfrb0_speed)    /* x */
#define SFRB1_S         (pTTrackingLoop_FiP32->sfrb1_speed)    /* y */
#define B0_A            (pTTrackingLoop_FiP32->b0_angle)       /* Qx */
#define B1_A            (pTTrackingLoop_FiP32->b1_angle)       /* Qy */
#define SFRB0_A         (pTTrackingLoop_FiP32->sfrb0_angle)    /* x */
#define SFRB1_A         (pTTrackingLoop_FiP32->sfrb1_angle)    /* y */
#define USE_RAW_SPEED   (pTTrackingLoop_FiP32->rawSpeed)

/* Variables */
#define ENABLE_OLD      (pTTrackingLoop_FiP32->enable_old)
#define I_OLD_T         (pTTrackingLoop_FiP32->i_old_torque)   /* Q62 */
#define I_OLD_S         (pTTrackingLoop_FiP32->i_old_speed)    /* Q31 */
#define I_OLD_A         (pTTrackingLoop_FiP32->i_old_angle)    /* Q31 */

/* Constants */
#define LIMIT_UP        ( INT32_MAX)    /* Q31 */
#define LIMIT_DOWN      (-INT32_MAX)    /* Q31 */
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TrackingLoop_FiP32_Update(TRACKINGLOOP_FIP32 *pTTrackingLoop_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    if (ENABLE)
    {
        int64 y, yp;
        int64 temp, tempSpeed;

        /** - pre-load integrator and output values */
        if (!ENABLE_OLD)    /* rising edge of enable signal occurred */
        {
            /* preset integrator values */
            I_OLD_T = ((int64)0) << 31;             /* torque init Q62 */
            I_OLD_S = INIT_SPEED;                   /* speed init Q31 */
            I_OLD_A = INIT_PHI;                     /* angle init Q31 */

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
        yp = ((int64)B1_T * (int64)PHI_EPS) >> SFRB1_T;     /* Qx*Q31/Qx -> Q31 */

        /* Sum of proportional and integral term */
        y = (int32)yp + (int32)(I_OLD_T>>31);                       /* Q31 + Q31 */

        /* output limitation and anti wind-up */
        if (y > LIMIT_UP)           /* output is beyond upper limit */
        {
            /* output limitation to upper boundary */
            y = LIMIT_UP;

            /* limitation of integral part */
            if (yp > LIMIT_UP)
            {
                yp = LIMIT_UP;
            }
            I_OLD_T = ((int64)(LIMIT_UP - (int32)yp)) << 31;            /* Q62 */

        }
        else if (y < LIMIT_DOWN)    /* output is beyond lower limit */
        {
            /* output limitation to lower boundary */
            y = LIMIT_DOWN;

            /* limitation of integral part */
            if (yp < LIMIT_DOWN)
            {
                yp = LIMIT_DOWN;
            }
            I_OLD_T = ((int64)(LIMIT_DOWN - (int32)yp)) << 31;      /* Q62 */
        }
        else
        {
            /* no output limitation -> no limitation of integral term */
            I_OLD_T += (((int64)B0_T * (int64)PHI_EPS));   /* Q62 = Q31+31*/
        }

        /* ******************************* */
        /* second integrator stage (speed) */
        /* calculate proportional term*/
        tempSpeed = ((int64)V_GAIN*(int64)PHI_EPS) >> SFR_GAIN;        /* Q31 */

        /* add integrator term */
        yp = ((int64)B1_S * (int64)y) >> SFRB1_S;                   /* proportional term of integrator: if bilinear transform is used b1 is different from 0 */
        temp = yp + I_OLD_S;                                        /* Q31*/
        tempSpeed += temp;
        LIMIT(tempSpeed, INT32_MAX);                                /* limit the calculated speed */

        /* integral term */
        I_OLD_S += (((int64)B0_S * (int64)y) >> SFRB0_S);           /* Q31 */

        /* ****************************** */
        /* third integrator stage (angle) */
        /* calculate rotor angle estimate */
        yp   = ((int64)B1_A * (int64)tempSpeed) >> SFRB1_A;         /* proportional term of integrator: if bilinear-transform is used b1 is different from 0 */
        PHI  = yp + I_OLD_A;                                        /* Q31 */

        /* integral term */
        I_OLD_A += (((int64)B0_A * (int64)tempSpeed) >> SFRB0_A);   /* Q31 */

        /* calculate angular speed estimate */
        if (USE_RAW_SPEED)
        {
            SPEED = (int32)(tempSpeed); /* high dynamic range */
        }
        else
        {
            SPEED = (int32)(temp);      /* less noise */
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
void TrackingLoop_FiP32_Init(TRACKINGLOOP_FIP32 *pTTrackingLoop_FiP32)
{
    pTTrackingLoop_FiP32->ID = TRACKINGLOOP_FIP32_ID;
    pTTrackingLoop_FiP32->n = 0;
    pTTrackingLoop_FiP32->phi = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    I_OLD_T = ((int64)0) << 31;             /* torque init Q62 */
    I_OLD_S = INIT_SPEED;                   /* speed init Q31 */
    I_OLD_A = INIT_PHI;                     /* angle init Q31 */
    ENABLE_OLD = false;
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TrackingLoop_FiP32_Load(const TRACKINGLOOP_FIP32 *pTTrackingLoop_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)36 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTTrackingLoop_FiP32->vGain & 0x000000FF);
        data[1] = (uint8)((pTTrackingLoop_FiP32->vGain >> 8) & 0x000000FF);
        data[2] = (uint8)((pTTrackingLoop_FiP32->vGain >> 16) & 0x000000FF);
        data[3] = (uint8)((pTTrackingLoop_FiP32->vGain >> 24) & 0x000000FF);
        data[4] = (uint8)pTTrackingLoop_FiP32->sfrGain;
        data[5] = (uint8)(pTTrackingLoop_FiP32->b0_torque & 0x000000FF);
        data[6] = (uint8)((pTTrackingLoop_FiP32->b0_torque >> 8) & 0x000000FF);
        data[7] = (uint8)((pTTrackingLoop_FiP32->b0_torque >> 16) & 0x000000FF);
        data[8] = (uint8)((pTTrackingLoop_FiP32->b0_torque >> 24) & 0x000000FF);
        data[9] = (uint8)(pTTrackingLoop_FiP32->b1_torque & 0x000000FF);
        data[10] = (uint8)((pTTrackingLoop_FiP32->b1_torque >> 8) & 0x000000FF);
        data[11] = (uint8)((pTTrackingLoop_FiP32->b1_torque >> 16) & 0x000000FF);
        data[12] = (uint8)((pTTrackingLoop_FiP32->b1_torque >> 24) & 0x000000FF);
        data[13] = (uint8)pTTrackingLoop_FiP32->sfrb0_torque;
        data[14] = (uint8)pTTrackingLoop_FiP32->sfrb1_torque;
        data[15] = (uint8)(pTTrackingLoop_FiP32->b0_speed & 0x000000FF);
        data[16] = (uint8)((pTTrackingLoop_FiP32->b0_speed >> 8) & 0x000000FF);
        data[17] = (uint8)((pTTrackingLoop_FiP32->b0_speed >> 16) & 0x000000FF);
        data[18] = (uint8)((pTTrackingLoop_FiP32->b0_speed >> 24) & 0x000000FF);
        data[19] = (uint8)(pTTrackingLoop_FiP32->b1_speed & 0x000000FF);
        data[20] = (uint8)((pTTrackingLoop_FiP32->b1_speed >> 8) & 0x000000FF);
        data[21] = (uint8)((pTTrackingLoop_FiP32->b1_speed >> 16) & 0x000000FF);
        data[22] = (uint8)((pTTrackingLoop_FiP32->b1_speed >> 24) & 0x000000FF);
        data[23] = (uint8)pTTrackingLoop_FiP32->sfrb0_speed;
        data[24] = (uint8)pTTrackingLoop_FiP32->sfrb1_speed;
        data[25] = (uint8)(pTTrackingLoop_FiP32->b0_angle & 0x000000FF);
        data[26] = (uint8)((pTTrackingLoop_FiP32->b0_angle >> 8) & 0x000000FF);
        data[27] = (uint8)((pTTrackingLoop_FiP32->b0_angle >> 16) & 0x000000FF);
        data[28] = (uint8)((pTTrackingLoop_FiP32->b0_angle >> 24) & 0x000000FF);
        data[29] = (uint8)(pTTrackingLoop_FiP32->b1_angle & 0x000000FF);
        data[30] = (uint8)((pTTrackingLoop_FiP32->b1_angle >> 8) & 0x000000FF);
        data[31] = (uint8)((pTTrackingLoop_FiP32->b1_angle >> 16) & 0x000000FF);
        data[32] = (uint8)((pTTrackingLoop_FiP32->b1_angle >> 24) & 0x000000FF);
        data[33] = (uint8)pTTrackingLoop_FiP32->sfrb0_angle;
        data[34] = (uint8)pTTrackingLoop_FiP32->sfrb1_angle;
        data[35] = (uint8)pTTrackingLoop_FiP32->rawSpeed;
        *dataLength = (uint16)36;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TrackingLoop_FiP32_Save(TRACKINGLOOP_FIP32 *pTTrackingLoop_FiP32, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)36)
    {
        error = (uint8)1;
    }
    else
    {
        pTTrackingLoop_FiP32->vGain = UINT32_TO_INT32((uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24));
        pTTrackingLoop_FiP32->sfrGain = UINT8_TO_INT8((uint8)data[4]);
        pTTrackingLoop_FiP32->b0_torque = UINT32_TO_INT32((uint32)data[5] + \
            ((uint32)data[6] << 8) + ((uint32)data[7] << 16) + \
            ((uint32)data[8] << 24));
        pTTrackingLoop_FiP32->b1_torque = UINT32_TO_INT32((uint32)data[9] + \
            ((uint32)data[10] << 8) + ((uint32)data[11] << 16) + \
            ((uint32)data[12] << 24));
        pTTrackingLoop_FiP32->sfrb0_torque = UINT8_TO_INT8((uint8)data[13]);
        pTTrackingLoop_FiP32->sfrb1_torque = UINT8_TO_INT8((uint8)data[14]);
        pTTrackingLoop_FiP32->b0_speed = UINT32_TO_INT32((uint32)data[15] + \
            ((uint32)data[16] << 8) + ((uint32)data[17] << 16) + \
            ((uint32)data[18] << 24));
        pTTrackingLoop_FiP32->b1_speed = UINT32_TO_INT32((uint32)data[19] + \
            ((uint32)data[20] << 8) + ((uint32)data[21] << 16) + \
            ((uint32)data[22] << 24));
        pTTrackingLoop_FiP32->sfrb0_speed = UINT8_TO_INT8((uint8)data[23]);
        pTTrackingLoop_FiP32->sfrb1_speed = UINT8_TO_INT8((uint8)data[24]);
        pTTrackingLoop_FiP32->b0_angle = UINT32_TO_INT32((uint32)data[25] + \
            ((uint32)data[26] << 8) + ((uint32)data[27] << 16) + \
            ((uint32)data[28] << 24));
        pTTrackingLoop_FiP32->b1_angle = UINT32_TO_INT32((uint32)data[29] + \
            ((uint32)data[30] << 8) + ((uint32)data[31] << 16) + \
            ((uint32)data[32] << 24));
        pTTrackingLoop_FiP32->sfrb0_angle = UINT8_TO_INT8((uint8)data[33]);
        pTTrackingLoop_FiP32->sfrb1_angle = UINT8_TO_INT8((uint8)data[34]);
        pTTrackingLoop_FiP32->rawSpeed = ((uint8)data[35]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TRACKINGLOOP_FIP32_ISLINKED)
void* TrackingLoop_FiP32_GetAddress(const TRACKINGLOOP_FIP32* block, uint16 elementId)
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
