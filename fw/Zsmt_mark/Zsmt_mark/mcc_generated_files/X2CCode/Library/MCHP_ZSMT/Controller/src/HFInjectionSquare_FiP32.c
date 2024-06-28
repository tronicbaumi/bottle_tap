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
#include "HFInjectionSquare_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(HFInjectionSquare_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Sin_Data.h"


/* Inputs */
#define IN_ALPHA        (*pTHFInjectionSquare_FiP32->iAlpha)
#define IN_BETA         (*pTHFInjectionSquare_FiP32->iBeta)
#define INIT_SPEED      (*pTHFInjectionSquare_FiP32->n0)
#define INIT_PHI        (*pTHFInjectionSquare_FiP32->phi0)
#define ENABLE          (*pTHFInjectionSquare_FiP32->Enable)

/* Outputs */
#define UD              (pTHFInjectionSquare_FiP32->ud)
#define I_EPS           (pTHFInjectionSquare_FiP32->i_eps)
#define SPEED           (pTHFInjectionSquare_FiP32->n)
#define PHI             (pTHFInjectionSquare_FiP32->phi)

/* Parameters */
#define U_INJ_AMP       (pTHFInjectionSquare_FiP32->uInjAmp)        /* amplitude of injected square-wave voltage */

#define	V_GAIN		    (pTHFInjectionSquare_FiP32->vGain)
#define	SFR_GAIN        (pTHFInjectionSquare_FiP32->sfrGain)
#define	B0_T		    (pTHFInjectionSquare_FiP32->b0_torque)		/* Qx */
#define	B1_T		    (pTHFInjectionSquare_FiP32->b1_torque)		/* Qy */
#define SFRB0_T		    (pTHFInjectionSquare_FiP32->sfrb0_torque)	/* x */
#define SFRB1_T		    (pTHFInjectionSquare_FiP32->sfrb1_torque)	/* y */
#define	B0_S		    (pTHFInjectionSquare_FiP32->b0_speed)		/* Qx */
#define	B1_S		    (pTHFInjectionSquare_FiP32->b1_speed)		/* Qy */
#define SFRB0_S		    (pTHFInjectionSquare_FiP32->sfrb0_speed)	/* x */
#define SFRB1_S		    (pTHFInjectionSquare_FiP32->sfrb1_speed)	/* y */
#define	B0_A		    (pTHFInjectionSquare_FiP32->b0_angle)		/* Qx */
#define	B1_A		    (pTHFInjectionSquare_FiP32->b1_angle)		/* Qy */
#define SFRB0_A		    (pTHFInjectionSquare_FiP32->sfrb0_angle)	/* x */
#define SFRB1_A		    (pTHFInjectionSquare_FiP32->sfrb1_angle)	/* y */
#define USE_RAW_SPEED   (pTHFInjectionSquare_FiP32->rawSpeed)

/* Variables */
#define SAMPLE_CNT      (pTHFInjectionSquare_FiP32->sampleCnt)      /* sample counter */
#define IY              (pTHFInjectionSquare_FiP32->iyArr)          /* array holding the last current values in y coordinate */

#define ENABLE_OLD      (pTHFInjectionSquare_FiP32->enable_old)
#define I_OLD_T		    (pTHFInjectionSquare_FiP32->i_old_torque)   /* Q62 */
#define I_OLD_S		    (pTHFInjectionSquare_FiP32->i_old_speed)    /* Q31 */
#define I_OLD_A		    (pTHFInjectionSquare_FiP32->i_old_angle)    /* Q31 */

/* Constants */
#define HALFPI  	    0x40000000		/* Pi/2	in Q31 format */
#define LIMIT_UP 	    ( INT32_MAX)	/* Q31 */
#define LIMIT_DOWN 	    (-INT32_MAX)	/* Q31 */
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void HFInjectionSquare_FiP32_Update(HFINJECTIONSQUARE_FIP32 *pTHFInjectionSquare_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    if (ENABLE)
    {
        int32 	sine, cosine;
        uint32	angle;
        int64	iY;
        
		/** - pre-load integrator and output values */
		if (!ENABLE_OLD)	/* rising edge of enable signal occurred */
		{
			/* preset integrator values */
			I_OLD_T = ((int64)0) << 31;		        /* torque init Q62 */
			I_OLD_S = INIT_SPEED;	                /* speed init Q31 */
			I_OLD_A = INIT_PHI;		                /* angle init Q31 */
			
			/* preset outputs */
			SPEED = INIT_SPEED;
			PHI = INIT_PHI;
		}
		
		/* save enable value for next cycle */
		ENABLE_OLD = ENABLE;
        
        /** - calculate current in estimated reference frame (partial Park transformation) */
        LOOKUP16(Sin_Table16, PHI, sine);		    /* sin(phi) */
        angle   = PHI + HALFPI;     			    /* -> cos(phi)	= sin(phi + pi/2) */
        LOOKUP32(Sin_Table32, angle, cosine);   /* cos(phi) */
        iY  =  (int64)cosine * (int64)IN_BETA;		/* cos(phi)*Q */
        iY -= ((int64)sine   * (int64)IN_ALPHA);	/* cos(phi)*Q - sin(phi)*D */
        iY  = iY >> 31;							/* scale to 32 Bit (Q62 -> Q31) */
        
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
            int64 dPhi;     /* angle error equivalent */
            int64 y, yp;
            int64 temp, tempSpeed;
            
            /* reset sample counter */
            SAMPLE_CNT = 0;
                      
            /*--------------------------------------------------------------------------------------------------------*/
            /* calculate HF component of y-current = calculate angle error
             *   quadratic model: i = i0 + ic + m*t + q*t^2
             *   coefficients: [-1/8 3/8 -3/8 1/8]
             *    -> division by 8 is skipped due to already low input signals (is compensated in conversion function)
             */
            dPhi = -IY[0] + 3*IY[1] - 3*IY[2] + IY[3];  /* use 1*Ts delayed currents, since input value IY is stored */
            LIMIT(dPhi, INT32_MAX);
            I_EPS = dPhi;                               /* write error current to the output */
            
            /*--------------------------------------------------------------------------------------------------------*/
            /* calculate angle and speed estimates
			 * PLL PI-Controller: feeding controller with filtered angle error signal
            */
            /* first integrator stage (torque) */
			/* Proportional term */
	        yp = ((int64)B1_T * (int64)dPhi) >> SFRB1_T;	/* Qx*Q31/Qx -> Q31 */

			/* Sum of proportional and integral term */
			y = (int32)yp + (int32)(I_OLD_T>>31);						/* Q31 + Q31 */

			/* Output limitation and anti wind-up */
			if (y > LIMIT_UP)			/* output is beyond upper limit */
			{
				/* output limitation to upper boundary */
				y = LIMIT_UP;

				/* limitation of integral part */
				if (yp > LIMIT_UP)
				{
					yp = LIMIT_UP;
				}
				I_OLD_T = ((int64)(LIMIT_UP - (int32)yp)) << 31;			/* Q62 */

			}
			else if (y < LIMIT_DOWN)	/* output is beyond lower limit */
			{
				/* output limitation to lower boundary */
				y = LIMIT_DOWN;

				/* limitation of integral part */
				if (yp < LIMIT_DOWN)
				{
					yp = LIMIT_DOWN;
				}
				I_OLD_T = ((int64)(LIMIT_DOWN - (int32)yp)) << 31;		/* Q62 */
			}
			else
			{
				/* No output limitation -> no limitation of integral term */
	            I_OLD_T += (((int64)B0_T * (int64)dPhi));	/* Q62 = Q31+31*/
			}

			/* ********************************************/
            /* second integrator stage (speed) */
			/*      Calculate proportional term           */
			tempSpeed = ((int64)V_GAIN*(int64)dPhi) >> SFR_GAIN;		/* Q31 */

			/* add Integrator-Term */
			yp = ((int64)B1_S * (int64)y) >> SFRB1_S;					/* proportional term of integrator: if bilinear transform is used b1 is different from 0 */
	        temp = yp + I_OLD_S;                                        /* Q31*/
	        tempSpeed += temp;
            LIMIT(tempSpeed, INT32_MAX);                                /* limit the calculated speed */

			/* Integral term */
		    I_OLD_S += (((int64)B0_S * (int64)y) >> SFRB0_S);	        /* Q31 */

			/* ****************************** */
            /* third integrator stage (angle) */
			/* calculate rotor angle estimate */
			yp   = ((int64)B1_A * (int64)tempSpeed) >> SFRB1_A;			/* proportional term of integrator: if bilinear-transform is used b1 is different from 0 */
			PHI  = yp + I_OLD_A;							            /* Q31 */

			/* Integral term */
	        I_OLD_A += (((int64)B0_A * (int64)tempSpeed) >> SFRB0_A);	/* Q31 */
            
            /* calculate angular speed estimate */
            if (USE_RAW_SPEED)
            {
	            SPEED = (int32)(tempSpeed); /* high dynamic range */
	        }
            else
            {
                //LIMIT(temp, INT32_MAX);                                /* limit the calculated speed */
                SPEED = (int32)(temp);      /* less noise */
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
void HFInjectionSquare_FiP32_Init(HFINJECTIONSQUARE_FIP32 *pTHFInjectionSquare_FiP32)
{
    pTHFInjectionSquare_FiP32->ID = HFINJECTIONSQUARE_FIP32_ID;
    pTHFInjectionSquare_FiP32->ud = 0;
    pTHFInjectionSquare_FiP32->i_eps = 0;
    pTHFInjectionSquare_FiP32->n = 0;
    pTHFInjectionSquare_FiP32->phi = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    SAMPLE_CNT = 0;
    IY[0] = 0;
    IY[1] = 0;
    IY[2] = 0;
    IY[3] = 0;
    IY[4] = 0;
    
    I_OLD_T = ((int64)0) << 31; /* torque init Q62 */
    I_OLD_S = INIT_SPEED;	    /* speed init Q31 */
    I_OLD_A = INIT_PHI;		    /* angle init Q31 */
    ENABLE_OLD = false;
    
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 HFInjectionSquare_FiP32_Load(const HFINJECTIONSQUARE_FIP32 *pTHFInjectionSquare_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)40 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTHFInjectionSquare_FiP32->uInjAmp & 0x000000FF);
        data[1] = (uint8)((pTHFInjectionSquare_FiP32->uInjAmp >> 8) & 0x000000FF);
        data[2] = (uint8)((pTHFInjectionSquare_FiP32->uInjAmp >> 16) & 0x000000FF);
        data[3] = (uint8)((pTHFInjectionSquare_FiP32->uInjAmp >> 24) & 0x000000FF);
        data[4] = (uint8)(pTHFInjectionSquare_FiP32->vGain & 0x000000FF);
        data[5] = (uint8)((pTHFInjectionSquare_FiP32->vGain >> 8) & 0x000000FF);
        data[6] = (uint8)((pTHFInjectionSquare_FiP32->vGain >> 16) & 0x000000FF);
        data[7] = (uint8)((pTHFInjectionSquare_FiP32->vGain >> 24) & 0x000000FF);
        data[8] = (uint8)pTHFInjectionSquare_FiP32->sfrGain;
        data[9] = (uint8)(pTHFInjectionSquare_FiP32->b0_torque & 0x000000FF);
        data[10] = (uint8)((pTHFInjectionSquare_FiP32->b0_torque >> 8) & 0x000000FF);
        data[11] = (uint8)((pTHFInjectionSquare_FiP32->b0_torque >> 16) & 0x000000FF);
        data[12] = (uint8)((pTHFInjectionSquare_FiP32->b0_torque >> 24) & 0x000000FF);
        data[13] = (uint8)(pTHFInjectionSquare_FiP32->b1_torque & 0x000000FF);
        data[14] = (uint8)((pTHFInjectionSquare_FiP32->b1_torque >> 8) & 0x000000FF);
        data[15] = (uint8)((pTHFInjectionSquare_FiP32->b1_torque >> 16) & 0x000000FF);
        data[16] = (uint8)((pTHFInjectionSquare_FiP32->b1_torque >> 24) & 0x000000FF);
        data[17] = (uint8)pTHFInjectionSquare_FiP32->sfrb0_torque;
        data[18] = (uint8)pTHFInjectionSquare_FiP32->sfrb1_torque;
        data[19] = (uint8)(pTHFInjectionSquare_FiP32->b0_speed & 0x000000FF);
        data[20] = (uint8)((pTHFInjectionSquare_FiP32->b0_speed >> 8) & 0x000000FF);
        data[21] = (uint8)((pTHFInjectionSquare_FiP32->b0_speed >> 16) & 0x000000FF);
        data[22] = (uint8)((pTHFInjectionSquare_FiP32->b0_speed >> 24) & 0x000000FF);
        data[23] = (uint8)(pTHFInjectionSquare_FiP32->b1_speed & 0x000000FF);
        data[24] = (uint8)((pTHFInjectionSquare_FiP32->b1_speed >> 8) & 0x000000FF);
        data[25] = (uint8)((pTHFInjectionSquare_FiP32->b1_speed >> 16) & 0x000000FF);
        data[26] = (uint8)((pTHFInjectionSquare_FiP32->b1_speed >> 24) & 0x000000FF);
        data[27] = (uint8)pTHFInjectionSquare_FiP32->sfrb0_speed;
        data[28] = (uint8)pTHFInjectionSquare_FiP32->sfrb1_speed;
        data[29] = (uint8)(pTHFInjectionSquare_FiP32->b0_angle & 0x000000FF);
        data[30] = (uint8)((pTHFInjectionSquare_FiP32->b0_angle >> 8) & 0x000000FF);
        data[31] = (uint8)((pTHFInjectionSquare_FiP32->b0_angle >> 16) & 0x000000FF);
        data[32] = (uint8)((pTHFInjectionSquare_FiP32->b0_angle >> 24) & 0x000000FF);
        data[33] = (uint8)(pTHFInjectionSquare_FiP32->b1_angle & 0x000000FF);
        data[34] = (uint8)((pTHFInjectionSquare_FiP32->b1_angle >> 8) & 0x000000FF);
        data[35] = (uint8)((pTHFInjectionSquare_FiP32->b1_angle >> 16) & 0x000000FF);
        data[36] = (uint8)((pTHFInjectionSquare_FiP32->b1_angle >> 24) & 0x000000FF);
        data[37] = (uint8)pTHFInjectionSquare_FiP32->sfrb0_angle;
        data[38] = (uint8)pTHFInjectionSquare_FiP32->sfrb1_angle;
        data[39] = (uint8)pTHFInjectionSquare_FiP32->rawSpeed;
        *dataLength = (uint16)40;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 HFInjectionSquare_FiP32_Save(HFINJECTIONSQUARE_FIP32 *pTHFInjectionSquare_FiP32, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)40)
    {
        error = (uint8)1;
    }
    else
    {
        pTHFInjectionSquare_FiP32->uInjAmp = UINT32_TO_INT32((uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24));
        pTHFInjectionSquare_FiP32->vGain = UINT32_TO_INT32((uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24));
        pTHFInjectionSquare_FiP32->sfrGain = UINT8_TO_INT8((uint8)data[8]);
        pTHFInjectionSquare_FiP32->b0_torque = UINT32_TO_INT32((uint32)data[9] + \
            ((uint32)data[10] << 8) + ((uint32)data[11] << 16) + \
            ((uint32)data[12] << 24));
        pTHFInjectionSquare_FiP32->b1_torque = UINT32_TO_INT32((uint32)data[13] + \
            ((uint32)data[14] << 8) + ((uint32)data[15] << 16) + \
            ((uint32)data[16] << 24));
        pTHFInjectionSquare_FiP32->sfrb0_torque = UINT8_TO_INT8((uint8)data[17]);
        pTHFInjectionSquare_FiP32->sfrb1_torque = UINT8_TO_INT8((uint8)data[18]);
        pTHFInjectionSquare_FiP32->b0_speed = UINT32_TO_INT32((uint32)data[19] + \
            ((uint32)data[20] << 8) + ((uint32)data[21] << 16) + \
            ((uint32)data[22] << 24));
        pTHFInjectionSquare_FiP32->b1_speed = UINT32_TO_INT32((uint32)data[23] + \
            ((uint32)data[24] << 8) + ((uint32)data[25] << 16) + \
            ((uint32)data[26] << 24));
        pTHFInjectionSquare_FiP32->sfrb0_speed = UINT8_TO_INT8((uint8)data[27]);
        pTHFInjectionSquare_FiP32->sfrb1_speed = UINT8_TO_INT8((uint8)data[28]);
        pTHFInjectionSquare_FiP32->b0_angle = UINT32_TO_INT32((uint32)data[29] + \
            ((uint32)data[30] << 8) + ((uint32)data[31] << 16) + \
            ((uint32)data[32] << 24));
        pTHFInjectionSquare_FiP32->b1_angle = UINT32_TO_INT32((uint32)data[33] + \
            ((uint32)data[34] << 8) + ((uint32)data[35] << 16) + \
            ((uint32)data[36] << 24));
        pTHFInjectionSquare_FiP32->sfrb0_angle = UINT8_TO_INT8((uint8)data[37]);
        pTHFInjectionSquare_FiP32->sfrb1_angle = UINT8_TO_INT8((uint8)data[38]);
        pTHFInjectionSquare_FiP32->rawSpeed = ((uint8)data[39]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(HFINJECTIONSQUARE_FIP32_ISLINKED)
void* HFInjectionSquare_FiP32_GetAddress(const HFINJECTIONSQUARE_FIP32* block, uint16 elementId)
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
