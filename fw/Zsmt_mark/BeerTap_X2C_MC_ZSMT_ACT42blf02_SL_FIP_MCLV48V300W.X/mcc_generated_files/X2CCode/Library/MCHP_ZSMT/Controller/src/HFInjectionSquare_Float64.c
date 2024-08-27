/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2128 $
 * $LastChangedDate:: 2021-02-02 14:38:09 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: 
 *  Angle observer based on evaluation of injected high frequency square wave voltage signal.
 */
/* USERCODE-END:Description                                                                                           */
#include "HFInjectionSquare_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(HFInjectionSquare_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>


/* Inputs */
#define IN_ALPHA        (*pTHFInjectionSquare_Float64->iAlpha)
#define IN_BETA         (*pTHFInjectionSquare_Float64->iBeta)
#define INIT_SPEED      (*pTHFInjectionSquare_Float64->n0)
#define INIT_PHI        (*pTHFInjectionSquare_Float64->phi0)
#define ENABLE          (*pTHFInjectionSquare_Float64->Enable)

/* Outputs */
#define UD              (pTHFInjectionSquare_Float64->ud)
#define I_EPS           (pTHFInjectionSquare_Float64->i_eps)
#define SPEED           (pTHFInjectionSquare_Float64->n)
#define PHI             (pTHFInjectionSquare_Float64->phi)

/* Parameters */
#define U_INJ_AMP       (pTHFInjectionSquare_Float64->uInjAmp)        /* amplitude of injected square-wave voltage */

#define	V_GAIN		    (pTHFInjectionSquare_Float64->vGain)
#define	B0_T		    (pTHFInjectionSquare_Float64->b0_torque)
#define	B1_T		    (pTHFInjectionSquare_Float64->b1_torque)
#define	B0_S		    (pTHFInjectionSquare_Float64->b0_speed)
#define	B1_S		    (pTHFInjectionSquare_Float64->b1_speed)
#define	B0_A		    (pTHFInjectionSquare_Float64->b0_angle)
#define	B1_A		    (pTHFInjectionSquare_Float64->b1_angle)
#define USE_RAW_SPEED   (pTHFInjectionSquare_Float64->rawSpeed)

/* Variables */
#define SAMPLE_CNT      (pTHFInjectionSquare_Float64->sampleCnt)      /* sample counter */
#define IY              (pTHFInjectionSquare_Float64->iyArr)          /* array holding the last current values in y coordinate */

#define ENABLE_OLD      (pTHFInjectionSquare_Float64->enable_old)
#define I_OLD_T		    (pTHFInjectionSquare_Float64->i_old_torque)
#define I_OLD_S		    (pTHFInjectionSquare_Float64->i_old_speed)
#define I_OLD_A		    (pTHFInjectionSquare_Float64->i_old_angle)

/* Macros */
#define LIMIT_ANGLE(angle)  do{\
                                while ((angle) >= PI_R64)\
                                {\
                                    (angle) = (angle) - (2.0 * PI_R64);\
                                }\
                                while ((angle) < - PI_R64)\
                                {\
                                    (angle) = (angle) + (2.0 * PI_R64);\
                                }\
                            }while(0)
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void HFInjectionSquare_Float64_Update(HFINJECTIONSQUARE_FLOAT64 *pTHFInjectionSquare_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    if (ENABLE)
    {
        float64 sine, cosine;
        float64	iY;
		
		/** - pre-load integrator and output values */
		if (!ENABLE_OLD)	/* rising edge of enable signal occurred */
		{
			/* preset integrator values */
            I_OLD_T = 0;		    /* torque init */
            I_OLD_S = INIT_SPEED;	/* speed init */
            I_OLD_A = INIT_PHI;		/* angle init */
			
			/* preset outputs */
			SPEED = INIT_SPEED;
			PHI = INIT_PHI;
		}
		
		/* save enable value for next cycle */
		ENABLE_OLD = ENABLE;
        
        /** - calculate current in estimated reference frame (partial Park transformation) */
        sine   = sin(PHI);		/* sin(phi) */
        cosine = cos(PHI);		/* cos(phi) */
        iY  =  cosine * IN_BETA;	/* cos(phi)*Q */
        iY -= (sine   * IN_ALPHA);	/* cos(phi)*Q - sin(phi)*D */
        
        /** - store current sample in estimated reference frame */
        IY[0] = IY[1];
        IY[1] = IY[2];
        IY[2] = IY[3];
        IY[3] = IY[4];
        IY[4] = iY;
        
        /** - update sample counter */
        SAMPLE_CNT++;
        
        /** - inject HF voltage (alternate between positive and negative voltage pulses) */
        if (SAMPLE_CNT & 0x01)
        {
            UD = U_INJ_AMP;     /* positive voltage pulse */
        }
        else
        {
            UD = -U_INJ_AMP;    /* negative voltage pulse */
        }
		
        /** - calculate angle and speed estimation */
        if (SAMPLE_CNT >= 4)
        {
            float64 dPhi;     /* angle error equivalent */
            float64 y, yp;
            float64 temp, tempSpeed, tempAngle;
            
            /* reset sample counter */
            SAMPLE_CNT = 0;
                      
            /*--------------------------------------------------------------------------------------------------------*/
            /* calculate HF component of y-current = calculate angle error
             *   quadratic model: i = i0 + ic + m*t + q*t^2
             *   coefficients: [-1/8 3/8 -3/8 1/8]
             *    -> division by 8 is skipped due to computation time optimization (is compensated in conversion function)
             */
            dPhi = -IY[0] + 3*IY[1] - 3*IY[2] + IY[3];  /* use 1*Ts delayed currents, since input value IY is stored */
            I_EPS = dPhi;                               /* write error current to the output */
            
            /*--------------------------------------------------------------------------------------------------------*/
            /* calculate angle and speed estimates
			 * PLL PI-Controller: feeding controller with filtered angle error signal
             */
            /* ******************************* */
            /* first integrator stage (torque) */
			/* proportional term */
	        yp = B1_T * dPhi;

			/* sum of proportional and integral term */
			y = yp + I_OLD_T;

            /* integral term */
	        I_OLD_T += (B0_T * dPhi);

			/* ******************************* */
            /* second integrator stage (speed) */
			/* calculate proportional term */
			tempSpeed = V_GAIN * dPhi;

			/* add integrator term */
			yp = B1_S * y;					/* proportional term of integrator: if bilinear transform is used b1 is different from 0 */
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
    }
    /* enable == false */
    else
    {
        /* reset outputs */
        UD = 0;
        I_EPS = 0;
        SPEED = 0;
        PHI = 0;

        /* reset variables */
        SAMPLE_CNT = 0;
        IY[0] = 0;
        IY[1] = 0;
        IY[2] = 0;
        IY[3] = 0;
        IY[4] = 0;
        ENABLE_OLD = false;
    }
    
/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void HFInjectionSquare_Float64_Init(HFINJECTIONSQUARE_FLOAT64 *pTHFInjectionSquare_Float64)
{
    pTHFInjectionSquare_Float64->ID = HFINJECTIONSQUARE_FLOAT64_ID;
    pTHFInjectionSquare_Float64->ud = 0;
    pTHFInjectionSquare_Float64->i_eps = 0;
    pTHFInjectionSquare_Float64->n = 0;
    pTHFInjectionSquare_Float64->phi = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    SAMPLE_CNT = 0;
    IY[0] = 0;
    IY[1] = 0;
    IY[2] = 0;
    IY[3] = 0;
    IY[4] = 0;
    
    I_OLD_T = 0;		    /* torque init */
    I_OLD_S = INIT_SPEED;	/* speed init */
    I_OLD_A = INIT_PHI;		/* angle init */
    ENABLE_OLD = false;
    
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 HFInjectionSquare_Float64_Load(const HFINJECTIONSQUARE_FLOAT64 *pTHFInjectionSquare_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)65 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->uInjAmp)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->uInjAmp) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->uInjAmp) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->uInjAmp) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->uInjAmp) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->uInjAmp) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->uInjAmp) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->uInjAmp) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->vGain)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->vGain) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->vGain) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->vGain) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->vGain) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->vGain) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->vGain) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->vGain) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_torque)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_torque) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_torque) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_torque) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_torque) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_torque) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_torque) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_torque) >> 56) & 0x00000000000000FF);
        data[24] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_torque)) & 0x00000000000000FF);
        data[25] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_torque) >> 8) & 0x00000000000000FF);
        data[26] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_torque) >> 16) & 0x00000000000000FF);
        data[27] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_torque) >> 24) & 0x00000000000000FF);
        data[28] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_torque) >> 32) & 0x00000000000000FF);
        data[29] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_torque) >> 40) & 0x00000000000000FF);
        data[30] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_torque) >> 48) & 0x00000000000000FF);
        data[31] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_torque) >> 56) & 0x00000000000000FF);
        data[32] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_speed)) & 0x00000000000000FF);
        data[33] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_speed) >> 8) & 0x00000000000000FF);
        data[34] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_speed) >> 16) & 0x00000000000000FF);
        data[35] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_speed) >> 24) & 0x00000000000000FF);
        data[36] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_speed) >> 32) & 0x00000000000000FF);
        data[37] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_speed) >> 40) & 0x00000000000000FF);
        data[38] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_speed) >> 48) & 0x00000000000000FF);
        data[39] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_speed) >> 56) & 0x00000000000000FF);
        data[40] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_speed)) & 0x00000000000000FF);
        data[41] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_speed) >> 8) & 0x00000000000000FF);
        data[42] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_speed) >> 16) & 0x00000000000000FF);
        data[43] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_speed) >> 24) & 0x00000000000000FF);
        data[44] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_speed) >> 32) & 0x00000000000000FF);
        data[45] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_speed) >> 40) & 0x00000000000000FF);
        data[46] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_speed) >> 48) & 0x00000000000000FF);
        data[47] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_speed) >> 56) & 0x00000000000000FF);
        data[48] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_angle)) & 0x00000000000000FF);
        data[49] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_angle) >> 8) & 0x00000000000000FF);
        data[50] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_angle) >> 16) & 0x00000000000000FF);
        data[51] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_angle) >> 24) & 0x00000000000000FF);
        data[52] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_angle) >> 32) & 0x00000000000000FF);
        data[53] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_angle) >> 40) & 0x00000000000000FF);
        data[54] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_angle) >> 48) & 0x00000000000000FF);
        data[55] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b0_angle) >> 56) & 0x00000000000000FF);
        data[56] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_angle)) & 0x00000000000000FF);
        data[57] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_angle) >> 8) & 0x00000000000000FF);
        data[58] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_angle) >> 16) & 0x00000000000000FF);
        data[59] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_angle) >> 24) & 0x00000000000000FF);
        data[60] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_angle) >> 32) & 0x00000000000000FF);
        data[61] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_angle) >> 40) & 0x00000000000000FF);
        data[62] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_angle) >> 48) & 0x00000000000000FF);
        data[63] = (uint8)((*(uint64*)&(pTHFInjectionSquare_Float64->b1_angle) >> 56) & 0x00000000000000FF);
        data[64] = (uint8)pTHFInjectionSquare_Float64->rawSpeed;
        *dataLength = (uint16)65;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 HFInjectionSquare_Float64_Save(HFINJECTIONSQUARE_FLOAT64 *pTHFInjectionSquare_Float64, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint64 tmp64;

    if (dataLength != (uint16)65)
    {
        error = (uint8)1;
    }
    else
    {
        tmp64 = (uint64)data[0] + \
            ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
            ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
            ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
            ((uint64)data[7] << 56);
        pTHFInjectionSquare_Float64->uInjAmp = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        pTHFInjectionSquare_Float64->vGain = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        pTHFInjectionSquare_Float64->b0_torque = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[24] + \
            ((uint64)data[25] << 8) + ((uint64)data[26] << 16) + \
            ((uint64)data[27] << 24) + ((uint64)data[28] << 32) + \
            ((uint64)data[29] << 40) + ((uint64)data[30] << 48) + \
            ((uint64)data[31] << 56);
        pTHFInjectionSquare_Float64->b1_torque = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[32] + \
            ((uint64)data[33] << 8) + ((uint64)data[34] << 16) + \
            ((uint64)data[35] << 24) + ((uint64)data[36] << 32) + \
            ((uint64)data[37] << 40) + ((uint64)data[38] << 48) + \
            ((uint64)data[39] << 56);
        pTHFInjectionSquare_Float64->b0_speed = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[40] + \
            ((uint64)data[41] << 8) + ((uint64)data[42] << 16) + \
            ((uint64)data[43] << 24) + ((uint64)data[44] << 32) + \
            ((uint64)data[45] << 40) + ((uint64)data[46] << 48) + \
            ((uint64)data[47] << 56);
        pTHFInjectionSquare_Float64->b1_speed = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[48] + \
            ((uint64)data[49] << 8) + ((uint64)data[50] << 16) + \
            ((uint64)data[51] << 24) + ((uint64)data[52] << 32) + \
            ((uint64)data[53] << 40) + ((uint64)data[54] << 48) + \
            ((uint64)data[55] << 56);
        pTHFInjectionSquare_Float64->b0_angle = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[56] + \
            ((uint64)data[57] << 8) + ((uint64)data[58] << 16) + \
            ((uint64)data[59] << 24) + ((uint64)data[60] << 32) + \
            ((uint64)data[61] << 40) + ((uint64)data[62] << 48) + \
            ((uint64)data[63] << 56);
        pTHFInjectionSquare_Float64->b1_angle = (float64)(*(float64*)&tmp64);
        pTHFInjectionSquare_Float64->rawSpeed = ((uint8)data[64]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(HFINJECTIONSQUARE_FLOAT64_ISLINKED)
void* HFInjectionSquare_Float64_GetAddress(const HFINJECTIONSQUARE_FLOAT64* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->iAlpha;
            break;
        case 2:
            addr = (void*)block->iBeta;
            break;
        case 3:
            addr = (void*)block->n0;
            break;
        case 4:
            addr = (void*)block->phi0;
            break;
        case 5:
            addr = (void*)block->Enable;
            break;
        case 6:
            addr = (void*)&block->ud;
            break;
        case 7:
            addr = (void*)&block->i_eps;
            break;
        case 8:
            addr = (void*)&block->n;
            break;
        case 9:
            addr = (void*)&block->phi;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
