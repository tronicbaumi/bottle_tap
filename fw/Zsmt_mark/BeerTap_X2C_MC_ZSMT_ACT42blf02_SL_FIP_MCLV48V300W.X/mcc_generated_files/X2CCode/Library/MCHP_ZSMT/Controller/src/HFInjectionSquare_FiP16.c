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
#include "HFInjectionSquare_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(HFInjectionSquare_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Sin_Data.h"


/* Inputs */
#define IN_ALPHA        (*pTHFInjectionSquare_FiP16->iAlpha)
#define IN_BETA         (*pTHFInjectionSquare_FiP16->iBeta)
#define INIT_SPEED      (*pTHFInjectionSquare_FiP16->n0)
#define INIT_PHI        (*pTHFInjectionSquare_FiP16->phi0)
#define ENABLE          (*pTHFInjectionSquare_FiP16->Enable)

/* Outputs */
#define UD              (pTHFInjectionSquare_FiP16->ud)
#define I_EPS           (pTHFInjectionSquare_FiP16->i_eps)
#define SPEED           (pTHFInjectionSquare_FiP16->n)
#define PHI             (pTHFInjectionSquare_FiP16->phi)

/* Parameters */
#define U_INJ_AMP       (pTHFInjectionSquare_FiP16->uInjAmp)        /* amplitude of injected square-wave voltage */

#define	V_GAIN		    (pTHFInjectionSquare_FiP16->vGain)
#define	SFR_GAIN        (pTHFInjectionSquare_FiP16->sfrGain)
#define	B0_T		    (pTHFInjectionSquare_FiP16->b0_torque)		/* Qx */
#define	B1_T		    (pTHFInjectionSquare_FiP16->b1_torque)		/* Qy */
#define SFRB0_T		    (pTHFInjectionSquare_FiP16->sfrb0_torque)	/* x */
#define SFRB1_T		    (pTHFInjectionSquare_FiP16->sfrb1_torque)	/* y */
#define	B0_S		    (pTHFInjectionSquare_FiP16->b0_speed)		/* Qx */
#define	B1_S		    (pTHFInjectionSquare_FiP16->b1_speed)		/* Qy */
#define SFRB0_S		    (pTHFInjectionSquare_FiP16->sfrb0_speed)	/* x */
#define SFRB1_S		    (pTHFInjectionSquare_FiP16->sfrb1_speed)	/* y */
#define	B0_A		    (pTHFInjectionSquare_FiP16->b0_angle)		/* Qx */
#define	B1_A		    (pTHFInjectionSquare_FiP16->b1_angle)		/* Qy */
#define SFRB0_A		    (pTHFInjectionSquare_FiP16->sfrb0_angle)	/* x */
#define SFRB1_A		    (pTHFInjectionSquare_FiP16->sfrb1_angle)	/* y */
#define USE_RAW_SPEED   (pTHFInjectionSquare_FiP16->rawSpeed)

/* Variables */
#define SAMPLE_CNT      (pTHFInjectionSquare_FiP16->sampleCnt)      /* sample counter */
#define IY              (pTHFInjectionSquare_FiP16->iyArr)          /* array holding the last current values in y coordinate */

#define ENABLE_OLD      (pTHFInjectionSquare_FiP16->enable_old)
#define I_OLD_T		    (pTHFInjectionSquare_FiP16->i_old_torque)   /* Q46 */
#define I_OLD_S		    (pTHFInjectionSquare_FiP16->i_old_speed)    /* Q30 */
#define I_OLD_A		    (pTHFInjectionSquare_FiP16->i_old_angle)    /* Q30 */

/* Constants */
#define HALFPI  	    0x4000			/* Pi/2	in Q15 format */
#define LIMIT_UP 	    ( INT16_MAX)	/* Q15 */
#define LIMIT_DOWN 	    (-INT16_MAX)	/* Q15 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void HFInjectionSquare_FiP16_Update(HFINJECTIONSQUARE_FIP16 *pTHFInjectionSquare_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    if (ENABLE)
    {
        int16 	sine, cosine;
        uint16	angle;
        int32	iY;
		
		/** - pre-load integrator and output values */
		if (!ENABLE_OLD)	/* rising edge of enable signal occurred */
		{
			/* preset integrator values */
			I_OLD_T = ((int32)0) << 31;		        /* torque init Q46 */
			I_OLD_S = ((int32)INIT_SPEED) << 15;	/* speed init Q30 */
			I_OLD_A = ((int32)INIT_PHI) << 15;		/* angle init Q30 */
			
			/* preset outputs */
			SPEED = INIT_SPEED;
			PHI = INIT_PHI;
		}
		
		/* save enable value for next cycle */
		ENABLE_OLD = ENABLE;
        
        /** - calculate current in estimated reference frame (partial Park transformation) */
        LOOKUP16(Sin_Table16, PHI, sine);		    /* sin(phi) */
        angle   = PHI + HALFPI;     			    /* -> cos(phi)	= sin(phi + pi/2) */
        LOOKUP16(Sin_Table16, angle, cosine);		/* cos(phi) */
        #ifdef __XC16__
            iY  =  __builtin_mulss(cosine, IN_BETA);	/* cos(phi)*Q */
            iY -= (__builtin_mulss(sine, IN_ALPHA));	/* cos(phi)*Q - sin(phi)*D */
        #else
            iY  =  (int32)cosine * (int32)IN_BETA;		/* cos(phi)*Q */
            iY -= ((int32)sine   * (int32)IN_ALPHA);	/* cos(phi)*Q - sin(phi)*D */
        #endif
        iY  = iY >> 15;							    /* scale to 16 Bit (Q30 -> Q15) */
        
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
            int32 dPhi;     /* angle error equivalent */
            int32 y, yp;
            int32 temp, tempSpeed;
            
            /* reset sample counter */
            SAMPLE_CNT = 0;
                      
            /*--------------------------------------------------------------------------------------------------------*/
            /* calculate HF component of y-current = calculate angle error
             *   quadratic model: i = i0 + ic + m*t + q*t^2
             *   coefficients: [-1/8 3/8 -3/8 1/8]
             *    -> division by 8 is skipped due to already low input signals (is compensated in conversion function)
             */
            dPhi = -IY[0] + 3*IY[1] - 3*IY[2] + IY[3];  /* use 1*Ts delayed currents, since input value IY is stored */
            LIMIT(dPhi, INT16_MAX);
            I_EPS = dPhi;                               /* write error current to the output */
            
            /*--------------------------------------------------------------------------------------------------------*/
            /* calculate angle and speed estimates
			 * PLL PI-Controller: feeding controller with filtered angle error signal
            */
            /* first integrator stage (torque) */
			/* Proportional term */
	        yp = ((int64)B1_T * (int64)dPhi) >> SFRB1_T;	            /* Qx*Q15/Qx -> Q15 */

			/* Sum of proportional and integral term */
			y = (int32)yp + (int32)(I_OLD_T>>31);						/* Q15 + Q15 */

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
				I_OLD_T = ((int64)(LIMIT_UP - (int16)yp)) << 31;			/* Q46 */

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
				I_OLD_T = ((int64)(LIMIT_DOWN - (int16)yp)) << 31;		/* Q46 */
			}
			else
			{
				/* No output limitation -> no limitation of integral term */
	            I_OLD_T += (((int64)B0_T * (int64)dPhi) << (31-SFRB0_T));	/* Q46 = Q15+31*/
			}

			/* ********************************************/
            /* second integrator stage (speed) */
			/*      Calculate proportional term           */
			tempSpeed = ((int32)V_GAIN*dPhi) >> SFR_GAIN;				/* Q15 */

			/* add Integrator-Term */
			yp = ((int32)B1_S * (int32)y) >> SFRB1_S;					/* proportional term of integrator: if bilinear transform is used b1 is different from 0 */
	        temp = (yp + (int32)(I_OLD_S >> 15));                       /* Q15 */
	        tempSpeed += temp;
            LIMIT(tempSpeed, INT16_MAX);                                /* limit the calculated speed */

			/* Integral term */
			#ifdef __XC16__
				I_OLD_S += ((__builtin_mulss(B0_S,y)) << (15-SFRB0_S));	/* Q30 */
			#else
				I_OLD_S += (((int32)B0_S * (int32)y) << (15-SFRB0_S));	/* Q30 */
			#endif

			/* ****************************** */
            /* third integrator stage (angle) */
			/* calculate rotor angle estimate */
			yp   = ((int32)B1_A * (int32)tempSpeed) >> SFRB1_A;			/* proportional term of integrator: if bilinear-transform is used b1 is different from 0 */
			PHI  = yp + (int32)(I_OLD_A >> 15);							/* Q15 */

			/* Integral term */
	        #ifdef __COMPILER_MICROCHIP__
	            I_OLD_UI += ((__builtin_mulss(B0_A,(int16)tempSpeed)) << (15-SFRB0_A));	/* Q30 */
	        #else
	            I_OLD_A += (((int32)B0_A * tempSpeed) << (15-SFRB0_A));	/* Q30 */
	        #endif
            
            /* calculate angular speed estimate */
            if (USE_RAW_SPEED)
            {
	            SPEED = (int16)(tempSpeed); /* high dynamic range */
	        }
            else
            {
                //LIMIT(temp, INT16_MAX);                                /* limit the calculated speed */
                SPEED = (int16)(temp);      /* less noise */
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
void HFInjectionSquare_FiP16_Init(HFINJECTIONSQUARE_FIP16 *pTHFInjectionSquare_FiP16)
{
    pTHFInjectionSquare_FiP16->ID = HFINJECTIONSQUARE_FIP16_ID;
    pTHFInjectionSquare_FiP16->ud = 0;
    pTHFInjectionSquare_FiP16->i_eps = 0;
    pTHFInjectionSquare_FiP16->n = 0;
    pTHFInjectionSquare_FiP16->phi = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    SAMPLE_CNT = 0;
    IY[0] = 0;
    IY[1] = 0;
    IY[2] = 0;
    IY[3] = 0;
    IY[4] = 0;
    
    I_OLD_T = ((int32)0) << 31;		        /* torque init Q46 */
    I_OLD_S = ((int32)INIT_SPEED) << 15;	/* speed init Q30 */
    I_OLD_A = ((int32)INIT_PHI) << 15;		/* angle init Q30 */
    ENABLE_OLD = false;
    
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 HFInjectionSquare_FiP16_Load(const HFINJECTIONSQUARE_FIP16 *pTHFInjectionSquare_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)28 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTHFInjectionSquare_FiP16->uInjAmp & 0x00FF);
        data[1] = (uint8)((pTHFInjectionSquare_FiP16->uInjAmp >> 8) & 0x00FF);
        data[2] = (uint8)(pTHFInjectionSquare_FiP16->vGain & 0x00FF);
        data[3] = (uint8)((pTHFInjectionSquare_FiP16->vGain >> 8) & 0x00FF);
        data[4] = (uint8)pTHFInjectionSquare_FiP16->sfrGain;
        data[5] = (uint8)(pTHFInjectionSquare_FiP16->b0_torque & 0x000000FF);
        data[6] = (uint8)((pTHFInjectionSquare_FiP16->b0_torque >> 8) & 0x000000FF);
        data[7] = (uint8)((pTHFInjectionSquare_FiP16->b0_torque >> 16) & 0x000000FF);
        data[8] = (uint8)((pTHFInjectionSquare_FiP16->b0_torque >> 24) & 0x000000FF);
        data[9] = (uint8)(pTHFInjectionSquare_FiP16->b1_torque & 0x000000FF);
        data[10] = (uint8)((pTHFInjectionSquare_FiP16->b1_torque >> 8) & 0x000000FF);
        data[11] = (uint8)((pTHFInjectionSquare_FiP16->b1_torque >> 16) & 0x000000FF);
        data[12] = (uint8)((pTHFInjectionSquare_FiP16->b1_torque >> 24) & 0x000000FF);
        data[13] = (uint8)pTHFInjectionSquare_FiP16->sfrb0_torque;
        data[14] = (uint8)pTHFInjectionSquare_FiP16->sfrb1_torque;
        data[15] = (uint8)(pTHFInjectionSquare_FiP16->b0_speed & 0x00FF);
        data[16] = (uint8)((pTHFInjectionSquare_FiP16->b0_speed >> 8) & 0x00FF);
        data[17] = (uint8)(pTHFInjectionSquare_FiP16->b1_speed & 0x00FF);
        data[18] = (uint8)((pTHFInjectionSquare_FiP16->b1_speed >> 8) & 0x00FF);
        data[19] = (uint8)pTHFInjectionSquare_FiP16->sfrb0_speed;
        data[20] = (uint8)pTHFInjectionSquare_FiP16->sfrb1_speed;
        data[21] = (uint8)(pTHFInjectionSquare_FiP16->b0_angle & 0x00FF);
        data[22] = (uint8)((pTHFInjectionSquare_FiP16->b0_angle >> 8) & 0x00FF);
        data[23] = (uint8)(pTHFInjectionSquare_FiP16->b1_angle & 0x00FF);
        data[24] = (uint8)((pTHFInjectionSquare_FiP16->b1_angle >> 8) & 0x00FF);
        data[25] = (uint8)pTHFInjectionSquare_FiP16->sfrb0_angle;
        data[26] = (uint8)pTHFInjectionSquare_FiP16->sfrb1_angle;
        data[27] = (uint8)pTHFInjectionSquare_FiP16->rawSpeed;
        *dataLength = (uint16)28;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 HFInjectionSquare_FiP16_Save(HFINJECTIONSQUARE_FIP16 *pTHFInjectionSquare_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)28)
    {
        error = (uint8)1;
    }
    else
    {
        pTHFInjectionSquare_FiP16->uInjAmp = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTHFInjectionSquare_FiP16->vGain = UINT16_TO_INT16((uint16)data[2] + \
            ((uint16)data[3] << 8));
        pTHFInjectionSquare_FiP16->sfrGain = UINT8_TO_INT8((uint8)data[4]);
        pTHFInjectionSquare_FiP16->b0_torque = UINT32_TO_INT32((uint32)data[5] + \
            ((uint32)data[6] << 8) + ((uint32)data[7] << 16) + \
            ((uint32)data[8] << 24));
        pTHFInjectionSquare_FiP16->b1_torque = UINT32_TO_INT32((uint32)data[9] + \
            ((uint32)data[10] << 8) + ((uint32)data[11] << 16) + \
            ((uint32)data[12] << 24));
        pTHFInjectionSquare_FiP16->sfrb0_torque = UINT8_TO_INT8((uint8)data[13]);
        pTHFInjectionSquare_FiP16->sfrb1_torque = UINT8_TO_INT8((uint8)data[14]);
        pTHFInjectionSquare_FiP16->b0_speed = UINT16_TO_INT16((uint16)data[15] + \
            ((uint16)data[16] << 8));
        pTHFInjectionSquare_FiP16->b1_speed = UINT16_TO_INT16((uint16)data[17] + \
            ((uint16)data[18] << 8));
        pTHFInjectionSquare_FiP16->sfrb0_speed = UINT8_TO_INT8((uint8)data[19]);
        pTHFInjectionSquare_FiP16->sfrb1_speed = UINT8_TO_INT8((uint8)data[20]);
        pTHFInjectionSquare_FiP16->b0_angle = UINT16_TO_INT16((uint16)data[21] + \
            ((uint16)data[22] << 8));
        pTHFInjectionSquare_FiP16->b1_angle = UINT16_TO_INT16((uint16)data[23] + \
            ((uint16)data[24] << 8));
        pTHFInjectionSquare_FiP16->sfrb0_angle = UINT8_TO_INT8((uint8)data[25]);
        pTHFInjectionSquare_FiP16->sfrb1_angle = UINT8_TO_INT8((uint8)data[26]);
        pTHFInjectionSquare_FiP16->rawSpeed = ((uint8)data[27]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(HFINJECTIONSQUARE_FIP16_ISLINKED)
void* HFInjectionSquare_FiP16_GetAddress(const HFINJECTIONSQUARE_FIP16* block, uint16 elementId)
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
