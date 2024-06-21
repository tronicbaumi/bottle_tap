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
#include "HFInjectionSquare_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(HFInjectionSquare_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>


/* Inputs */
#define IN_ALPHA        (*pTHFInjectionSquare_Float32->iAlpha)
#define IN_BETA         (*pTHFInjectionSquare_Float32->iBeta)
#define INIT_SPEED      (*pTHFInjectionSquare_Float32->n0)
#define INIT_PHI        (*pTHFInjectionSquare_Float32->phi0)
#define ENABLE          (*pTHFInjectionSquare_Float32->Enable)

/* Outputs */
#define UD              (pTHFInjectionSquare_Float32->ud)
#define I_EPS           (pTHFInjectionSquare_Float32->i_eps)
#define SPEED           (pTHFInjectionSquare_Float32->n)
#define PHI             (pTHFInjectionSquare_Float32->phi)

/* Parameters */
#define U_INJ_AMP       (pTHFInjectionSquare_Float32->uInjAmp)        /* amplitude of injected square-wave voltage */

#define	V_GAIN		    (pTHFInjectionSquare_Float32->vGain)
#define	B0_T		    (pTHFInjectionSquare_Float32->b0_torque)
#define	B1_T		    (pTHFInjectionSquare_Float32->b1_torque)
#define	B0_S		    (pTHFInjectionSquare_Float32->b0_speed)
#define	B1_S		    (pTHFInjectionSquare_Float32->b1_speed)
#define	B0_A		    (pTHFInjectionSquare_Float32->b0_angle)
#define	B1_A		    (pTHFInjectionSquare_Float32->b1_angle)
#define USE_RAW_SPEED   (pTHFInjectionSquare_Float32->rawSpeed)

/* Variables */
#define SAMPLE_CNT      (pTHFInjectionSquare_Float32->sampleCnt)      /* sample counter */
#define IY              (pTHFInjectionSquare_Float32->iyArr)          /* array holding the last current values in y coordinate */

#define ENABLE_OLD      (pTHFInjectionSquare_Float32->enable_old)
#define I_OLD_T		    (pTHFInjectionSquare_Float32->i_old_torque)
#define I_OLD_S		    (pTHFInjectionSquare_Float32->i_old_speed)
#define I_OLD_A		    (pTHFInjectionSquare_Float32->i_old_angle)

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
void HFInjectionSquare_Float32_Update(HFINJECTIONSQUARE_FLOAT32 *pTHFInjectionSquare_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    if (ENABLE)
    {
        float32 sine, cosine;
        float32	iY;
		
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
        sine   = sinf(PHI);		/* sin(phi) */
        cosine = cosf(PHI);		/* cos(phi) */
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
            float32 dPhi;     /* angle error equivalent */
            float32 y, yp;
            float32 temp, tempSpeed, tempAngle;
            
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
void HFInjectionSquare_Float32_Init(HFINJECTIONSQUARE_FLOAT32 *pTHFInjectionSquare_Float32)
{
    pTHFInjectionSquare_Float32->ID = HFINJECTIONSQUARE_FLOAT32_ID;
    pTHFInjectionSquare_Float32->ud = 0;
    pTHFInjectionSquare_Float32->i_eps = 0;
    pTHFInjectionSquare_Float32->n = 0;
    pTHFInjectionSquare_Float32->phi = 0;
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
uint8 HFInjectionSquare_Float32_Load(const HFINJECTIONSQUARE_FLOAT32 *pTHFInjectionSquare_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)33 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->uInjAmp)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->uInjAmp) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->uInjAmp) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->uInjAmp) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->vGain)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->vGain) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->vGain) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->vGain) >> 24) & 0x000000FF);
        data[8] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b0_torque)) & 0x000000FF);
        data[9] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b0_torque) >> 8) & 0x000000FF);
        data[10] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b0_torque) >> 16) & 0x000000FF);
        data[11] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b0_torque) >> 24) & 0x000000FF);
        data[12] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b1_torque)) & 0x000000FF);
        data[13] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b1_torque) >> 8) & 0x000000FF);
        data[14] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b1_torque) >> 16) & 0x000000FF);
        data[15] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b1_torque) >> 24) & 0x000000FF);
        data[16] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b0_speed)) & 0x000000FF);
        data[17] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b0_speed) >> 8) & 0x000000FF);
        data[18] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b0_speed) >> 16) & 0x000000FF);
        data[19] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b0_speed) >> 24) & 0x000000FF);
        data[20] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b1_speed)) & 0x000000FF);
        data[21] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b1_speed) >> 8) & 0x000000FF);
        data[22] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b1_speed) >> 16) & 0x000000FF);
        data[23] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b1_speed) >> 24) & 0x000000FF);
        data[24] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b0_angle)) & 0x000000FF);
        data[25] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b0_angle) >> 8) & 0x000000FF);
        data[26] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b0_angle) >> 16) & 0x000000FF);
        data[27] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b0_angle) >> 24) & 0x000000FF);
        data[28] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b1_angle)) & 0x000000FF);
        data[29] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b1_angle) >> 8) & 0x000000FF);
        data[30] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b1_angle) >> 16) & 0x000000FF);
        data[31] = (uint8)((*(uint32*)&(pTHFInjectionSquare_Float32->b1_angle) >> 24) & 0x000000FF);
        data[32] = (uint8)pTHFInjectionSquare_Float32->rawSpeed;
        *dataLength = (uint16)33;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 HFInjectionSquare_Float32_Save(HFINJECTIONSQUARE_FLOAT32 *pTHFInjectionSquare_Float32, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint32 tmp32;

    if (dataLength != (uint16)33)
    {
        error = (uint8)1;
    }
    else
    {
        tmp32 = (uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24);
        pTHFInjectionSquare_Float32->uInjAmp = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTHFInjectionSquare_Float32->vGain = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24);
        pTHFInjectionSquare_Float32->b0_torque = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[12] + \
            ((uint32)data[13] << 8) + ((uint32)data[14] << 16) + \
            ((uint32)data[15] << 24);
        pTHFInjectionSquare_Float32->b1_torque = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[16] + \
            ((uint32)data[17] << 8) + ((uint32)data[18] << 16) + \
            ((uint32)data[19] << 24);
        pTHFInjectionSquare_Float32->b0_speed = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[20] + \
            ((uint32)data[21] << 8) + ((uint32)data[22] << 16) + \
            ((uint32)data[23] << 24);
        pTHFInjectionSquare_Float32->b1_speed = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[24] + \
            ((uint32)data[25] << 8) + ((uint32)data[26] << 16) + \
            ((uint32)data[27] << 24);
        pTHFInjectionSquare_Float32->b0_angle = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[28] + \
            ((uint32)data[29] << 8) + ((uint32)data[30] << 16) + \
            ((uint32)data[31] << 24);
        pTHFInjectionSquare_Float32->b1_angle = (float32)(*(float32*)&tmp32);
        pTHFInjectionSquare_Float32->rawSpeed = ((uint8)data[32]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(HFINJECTIONSQUARE_FLOAT32_ISLINKED)
void* HFInjectionSquare_Float32_GetAddress(const HFINJECTIONSQUARE_FLOAT32* block, uint16 elementId)
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
