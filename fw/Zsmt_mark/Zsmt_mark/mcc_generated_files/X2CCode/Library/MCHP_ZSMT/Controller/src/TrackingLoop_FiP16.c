/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1603 $
 * $LastChangedDate:: 2019-01-21 19:02:13 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "TrackingLoop_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TrackingLoop_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define PHI_EPS         (*pTTrackingLoop_FiP16->phi_eps)
#define INIT_SPEED      (*pTTrackingLoop_FiP16->n0)
#define INIT_PHI        (*pTTrackingLoop_FiP16->phi0)
#define ENABLE          (*pTTrackingLoop_FiP16->Enable)

/* Outputs */
#define SPEED           (pTTrackingLoop_FiP16->n)
#define PHI             (pTTrackingLoop_FiP16->phi)

#define V_GAIN          (pTTrackingLoop_FiP16->vGain)
#define SFR_GAIN        (pTTrackingLoop_FiP16->sfrGain)
#define B0_T            (pTTrackingLoop_FiP16->b0_torque)      /* Qx */
#define B1_T            (pTTrackingLoop_FiP16->b1_torque)      /* Qy */
#define SFRB0_T         (pTTrackingLoop_FiP16->sfrb0_torque)   /* x */
#define SFRB1_T         (pTTrackingLoop_FiP16->sfrb1_torque)   /* y */
#define B0_S            (pTTrackingLoop_FiP16->b0_speed)       /* Qx */
#define B1_S            (pTTrackingLoop_FiP16->b1_speed)       /* Qy */
#define SFRB0_S         (pTTrackingLoop_FiP16->sfrb0_speed)    /* x */
#define SFRB1_S         (pTTrackingLoop_FiP16->sfrb1_speed)    /* y */
#define B0_A            (pTTrackingLoop_FiP16->b0_angle)       /* Qx */
#define B1_A            (pTTrackingLoop_FiP16->b1_angle)       /* Qy */
#define SFRB0_A         (pTTrackingLoop_FiP16->sfrb0_angle)    /* x */
#define SFRB1_A         (pTTrackingLoop_FiP16->sfrb1_angle)    /* y */
#define USE_RAW_SPEED   (pTTrackingLoop_FiP16->rawSpeed)

#define ENABLE_OLD      (pTTrackingLoop_FiP16->enable_old)
#define I_OLD_T         (pTTrackingLoop_FiP16->i_old_torque)   /* Q46 */
#define I_OLD_S         (pTTrackingLoop_FiP16->i_old_speed)    /* Q46 */
#define I_OLD_A         (pTTrackingLoop_FiP16->i_old_angle)    /* Q30 */

/* Constants */
#define LIMIT_UP        ( INT16_MAX)    /* Q15 */
#define LIMIT_DOWN      (-INT16_MAX)    /* Q15 */
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TrackingLoop_FiP16_Update(TRACKINGLOOP_FIP16 *pTTrackingLoop_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    if (ENABLE)
    {
        int32 y, yp;
        int32 temp, tempSpeed;

        /** - pre-load integrator and output values */
        if (!ENABLE_OLD)    /* rising edge of enable signal occurred */
        {
            /* preset integrator values */
            I_OLD_T = ((int32)0) << 31;             /* torque init Q46 */
            I_OLD_S = ((int32)INIT_SPEED) << 31;    /* speed init Q46 */
            I_OLD_A = ((int32)INIT_PHI) << 15;      /* angle init Q30 */

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
        /* calculate proportional term */
        yp = ((int64)B1_T * (int64)PHI_EPS) >> SFRB1_T;                /* Qx*Q15/Qx -> Q15 */

        /* sum of proportional and integral term */
        y = (int32)yp + (int32)(I_OLD_T>>31);                       /* Q15 + Q15 */

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
            I_OLD_T = ((int64)(LIMIT_UP - (int16)yp)) << 31;            /* Q46 */

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
            I_OLD_T = ((int64)(LIMIT_DOWN - (int16)yp)) << 31;      /* Q46 */
        }
        else
        {
            /* no output limitation -> no limitation of integral term */
            I_OLD_T += (((int64)B0_T * (int64)PHI_EPS) << (31-SFRB0_T));   /* Q46 = Q15+31*/
        }

        /* ******************************* */
        /* second integrator stage (speed) */
        /* calculate proportional term */
        tempSpeed = ((int32)V_GAIN*PHI_EPS) >> SFR_GAIN;               /* Q15 */

        /* add integrator term */
        yp = ((int64)B1_S * (int64)y) >> SFRB1_S;                   /* proportional term of integrator: if bilinear transform is used b1 is different from 0 */
        temp = (yp + (int32)(I_OLD_S >> 31));                       /* Q15 + Q15 */
        tempSpeed += temp;
        LIMIT(tempSpeed, INT16_MAX);                                /* limit the calculated speed */

        /* integral term */
        I_OLD_S += (((int64)B0_S * (int64)y) << (31-SFRB0_S));      /* Q46 = Q15+31*/

        /* ****************************** */
        /* third integrator stage (angle) */
        /* calculate rotor angle estimate */
        yp   = ((int32)B1_A * (int32)tempSpeed) >> SFRB1_A;         /* proportional term of integrator: if bilinear-transform is used b1 is different from 0 */
        PHI  = yp + (int32)(I_OLD_A >> 15);                         /* Q15 */

        /* integral term */
        #ifdef __COMPILER_MICROCHIP__
            I_OLD_A += ((__builtin_mulss(B0_A,(int16)tempSpeed)) << (15-SFRB0_A)); /* Q30 */
        #else
            I_OLD_A += (((int32)B0_A * tempSpeed) << (15-SFRB0_A)); /* Q30 */
        #endif

        /* calculate angular speed estimate */
        if (USE_RAW_SPEED)
        {
            SPEED = (int16)(tempSpeed); /* high dynamic range */
        }
        else
        {
            SPEED = (int16)(temp);      /* less noise */
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
void TrackingLoop_FiP16_Init(TRACKINGLOOP_FIP16 *pTTrackingLoop_FiP16)
{
    pTTrackingLoop_FiP16->ID = TRACKINGLOOP_FIP16_ID;
    pTTrackingLoop_FiP16->n = 0;
    pTTrackingLoop_FiP16->phi = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    I_OLD_T = ((int32)0) << 31;             /* torque init Q46 */
    I_OLD_S = ((int32)INIT_SPEED) << 15;    /* speed init Q30 */
    I_OLD_A = ((int32)INIT_PHI) << 15;      /* angle init Q30 */
    ENABLE_OLD = false;
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TrackingLoop_FiP16_Load(const TRACKINGLOOP_FIP16 *pTTrackingLoop_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)30 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTTrackingLoop_FiP16->vGain & 0x00FF);
        data[1] = (uint8)((pTTrackingLoop_FiP16->vGain >> 8) & 0x00FF);
        data[2] = (uint8)pTTrackingLoop_FiP16->sfrGain;
        data[3] = (uint8)(pTTrackingLoop_FiP16->b0_torque & 0x000000FF);
        data[4] = (uint8)((pTTrackingLoop_FiP16->b0_torque >> 8) & 0x000000FF);
        data[5] = (uint8)((pTTrackingLoop_FiP16->b0_torque >> 16) & 0x000000FF);
        data[6] = (uint8)((pTTrackingLoop_FiP16->b0_torque >> 24) & 0x000000FF);
        data[7] = (uint8)(pTTrackingLoop_FiP16->b1_torque & 0x000000FF);
        data[8] = (uint8)((pTTrackingLoop_FiP16->b1_torque >> 8) & 0x000000FF);
        data[9] = (uint8)((pTTrackingLoop_FiP16->b1_torque >> 16) & 0x000000FF);
        data[10] = (uint8)((pTTrackingLoop_FiP16->b1_torque >> 24) & 0x000000FF);
        data[11] = (uint8)pTTrackingLoop_FiP16->sfrb0_torque;
        data[12] = (uint8)pTTrackingLoop_FiP16->sfrb1_torque;
        data[13] = (uint8)(pTTrackingLoop_FiP16->b0_speed & 0x000000FF);
        data[14] = (uint8)((pTTrackingLoop_FiP16->b0_speed >> 8) & 0x000000FF);
        data[15] = (uint8)((pTTrackingLoop_FiP16->b0_speed >> 16) & 0x000000FF);
        data[16] = (uint8)((pTTrackingLoop_FiP16->b0_speed >> 24) & 0x000000FF);
        data[17] = (uint8)(pTTrackingLoop_FiP16->b1_speed & 0x000000FF);
        data[18] = (uint8)((pTTrackingLoop_FiP16->b1_speed >> 8) & 0x000000FF);
        data[19] = (uint8)((pTTrackingLoop_FiP16->b1_speed >> 16) & 0x000000FF);
        data[20] = (uint8)((pTTrackingLoop_FiP16->b1_speed >> 24) & 0x000000FF);
        data[21] = (uint8)pTTrackingLoop_FiP16->sfrb0_speed;
        data[22] = (uint8)pTTrackingLoop_FiP16->sfrb1_speed;
        data[23] = (uint8)(pTTrackingLoop_FiP16->b0_angle & 0x00FF);
        data[24] = (uint8)((pTTrackingLoop_FiP16->b0_angle >> 8) & 0x00FF);
        data[25] = (uint8)(pTTrackingLoop_FiP16->b1_angle & 0x00FF);
        data[26] = (uint8)((pTTrackingLoop_FiP16->b1_angle >> 8) & 0x00FF);
        data[27] = (uint8)pTTrackingLoop_FiP16->sfrb0_angle;
        data[28] = (uint8)pTTrackingLoop_FiP16->sfrb1_angle;
        data[29] = (uint8)pTTrackingLoop_FiP16->rawSpeed;
        *dataLength = (uint16)30;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TrackingLoop_FiP16_Save(TRACKINGLOOP_FIP16 *pTTrackingLoop_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)30)
    {
        error = (uint8)1;
    }
    else
    {
        pTTrackingLoop_FiP16->vGain = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTTrackingLoop_FiP16->sfrGain = UINT8_TO_INT8((uint8)data[2]);
        pTTrackingLoop_FiP16->b0_torque = UINT32_TO_INT32((uint32)data[3] + \
            ((uint32)data[4] << 8) + ((uint32)data[5] << 16) + \
            ((uint32)data[6] << 24));
        pTTrackingLoop_FiP16->b1_torque = UINT32_TO_INT32((uint32)data[7] + \
            ((uint32)data[8] << 8) + ((uint32)data[9] << 16) + \
            ((uint32)data[10] << 24));
        pTTrackingLoop_FiP16->sfrb0_torque = UINT8_TO_INT8((uint8)data[11]);
        pTTrackingLoop_FiP16->sfrb1_torque = UINT8_TO_INT8((uint8)data[12]);
        pTTrackingLoop_FiP16->b0_speed = UINT32_TO_INT32((uint32)data[13] + \
            ((uint32)data[14] << 8) + ((uint32)data[15] << 16) + \
            ((uint32)data[16] << 24));
        pTTrackingLoop_FiP16->b1_speed = UINT32_TO_INT32((uint32)data[17] + \
            ((uint32)data[18] << 8) + ((uint32)data[19] << 16) + \
            ((uint32)data[20] << 24));
        pTTrackingLoop_FiP16->sfrb0_speed = UINT8_TO_INT8((uint8)data[21]);
        pTTrackingLoop_FiP16->sfrb1_speed = UINT8_TO_INT8((uint8)data[22]);
        pTTrackingLoop_FiP16->b0_angle = UINT16_TO_INT16((uint16)data[23] + \
            ((uint16)data[24] << 8));
        pTTrackingLoop_FiP16->b1_angle = UINT16_TO_INT16((uint16)data[25] + \
            ((uint16)data[26] << 8));
        pTTrackingLoop_FiP16->sfrb0_angle = UINT8_TO_INT8((uint8)data[27]);
        pTTrackingLoop_FiP16->sfrb1_angle = UINT8_TO_INT8((uint8)data[28]);
        pTTrackingLoop_FiP16->rawSpeed = ((uint8)data[29]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TRACKINGLOOP_FIP16_ISLINKED)
void* TrackingLoop_FiP16_GetAddress(const TRACKINGLOOP_FIP16* block, uint16 elementId)
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
