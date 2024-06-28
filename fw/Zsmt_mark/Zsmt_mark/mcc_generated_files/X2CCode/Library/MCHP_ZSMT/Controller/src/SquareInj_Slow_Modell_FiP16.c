/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "SquareInj_Slow_Modell_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(SquareInj_Slow_Modell_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* inputs */
#define ENABLE 			(*pTSquareInj_Slow_Modell_FiP16->Enable)	/* Q0 */
#define INIT_SPEED 		(*pTSquareInj_Slow_Modell_FiP16->n0)		/* Q15 */
#define INIT_PHI 		(*pTSquareInj_Slow_Modell_FiP16->phi0)	/* Q15 */
#define DPHI 			(*pTSquareInj_Slow_Modell_FiP16->dphi)	/* Q15 */

/* outputs */
#define	PHI				(pTSquareInj_Slow_Modell_FiP16->phi)
#define	SPEED			(pTSquareInj_Slow_Modell_FiP16->speed)
#define	SYNC			(pTSquareInj_Slow_Modell_FiP16->Sync)

/* proportional Gain Parameter */
#define	V_GAIN			(pTSquareInj_Slow_Modell_FiP16->vGain)
#define	SFR_GAIN		(pTSquareInj_Slow_Modell_FiP16->sfrGain)


/* PT1 Parameter */
//#define	A0_PT1			(pTSquareInj_Slow_Modell_FiP16->a0_PT1)		/* Qa */
//#define	B0_PT1			(pTSquareInj_Slow_Modell_FiP16->b0_PT1)		/* Qb */
//#define	B1_PT1			(pTSquareInj_Slow_Modell_FiP16->b1_PT1)		/* Qb */
//#define SFRA_PT1		(pTSquareInj_Slow_Modell_FiP16->sfra_PT1)		/* a */
//#define SFRB_PT1		(pTSquareInj_Slow_Modell_FiP16->sfrb_PT1)		/* b */

/* PT1 Variables */
// #define DPHI_OLD		(pTSquareInj_Slow_Modell_FiP16->dphiOld)
// #define FILT_DPHI		(pTSquareInj_Slow_Modell_FiP16->filtDphi)


/* PI Controller Parameter */
#define	B0				(pTSquareInj_Slow_Modell_FiP16->b0)			/* Qx */
#define	B1				(pTSquareInj_Slow_Modell_FiP16->b1)			/* Qy */
#define SFR0			(pTSquareInj_Slow_Modell_FiP16->sfrb0)		/* x */
#define SFR1			(pTSquareInj_Slow_Modell_FiP16->sfrb1)		/* y */

/* PI Controller Variables */
#define I_OLD			(pTSquareInj_Slow_Modell_FiP16->i_old)		/* Q30 */
#define ENABLE_OLD		(pTSquareInj_Slow_Modell_FiP16->enable_old)


/* Parameter I-Block */
#define	B0_I			(pTSquareInj_Slow_Modell_FiP16->b0_I)		/* Qy */
#define SFR0_I			(pTSquareInj_Slow_Modell_FiP16->sfr_I)		/* y */

#define	B1_I			(pTSquareInj_Slow_Modell_FiP16->b1_I)		/* Qy */
#define SFR_B1_I		(pTSquareInj_Slow_Modell_FiP16->sfrb1_I)	/* y */

/* Variables I-Block */
#define I_OLD_I		(pTSquareInj_Slow_Modell_FiP16->i_old_I)		/* Q30 */


/* Parameter uI-Block */
#define	B0_UI			(pTSquareInj_Slow_Modell_FiP16->b0_uI)		/* Qy */
#define SFR0_UI			(pTSquareInj_Slow_Modell_FiP16->sfr_uI)		/* y */

#define	B1_UI			(pTSquareInj_Slow_Modell_FiP16->b1_uI)		/* Qy */
#define SFR_B1_UI		(pTSquareInj_Slow_Modell_FiP16->sfrb1_uI)	/* y */

/* Variables uI-Block */
#define I_OLD_UI		(pTSquareInj_Slow_Modell_FiP16->i_old_uI)		/* Q30 */


#define TOGGLE_STATUS	(pTSquareInj_Slow_Modell_FiP16->toggleState)

/* */
#define USE_RAW_SPEED	(pTSquareInj_Slow_Modell_FiP16->rawSpeed)   /* boolean: if true  -> input to uI-Block is used for speed outport
                                                                                if false -> output of I-Block used for speed outport */

#define LIMIT_UP 				( INT16_MAX)	/* Q15 */
#define LIMIT_DOWN 				(-INT16_MAX)	/* Q15 */
#define PERIOD				(2)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void SquareInj_Slow_Modell_FiP16_Update(SQUAREINJ_SLOW_MODELL_FIP16 *pTSquareInj_Slow_Modell_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32 y, yp;
	int32 temp, tempSpeed;

	temp = (int32)DPHI;								/* Q15 */

	/* Block is enabled */
	if (ENABLE != false)
	{
		/****************************************************************************/
		/* PLL PI-Controller: feeding controller with filtered angle-error signal   */
		if (ENABLE_OLD == false)	/* rising edge of enable signal occurred */
		{
		 	/* preset old speed value to zero */
			I_OLD = ((int32)0) << 31;		        /* torque init Q46 */
		 	I_OLD_I = ((int32)INIT_SPEED) << 15;	/* speed init Q30 */
		 	I_OLD_UI = ((int32)INIT_PHI) << 15;		/* angle init Q30 */
		}

		/* Proportional term */
        #ifdef __COMPILER_MICROCHIP__
            yp = __builtin_mulss(B1, temp) >> SFR1;	/* Q15 */
        #else
            yp = ((int64)B1 * (int64)temp) >> SFR1;	/* Qx*Q15/Qx -> Q15 */
        #endif

		/* Sum of proportional and integral term */
		y = (int32)yp + (int32)(I_OLD>>31);						/* Q15 + Q15 */

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
			I_OLD = ((int64)(LIMIT_UP - (int16)yp)) << 31;			/* Q46 */

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
			I_OLD = ((int64)(LIMIT_DOWN - (int16)yp)) << 31;		/* Q46 */
		}
		else
		{
			/* No output limitation -> no limitation of integral term */
            #ifdef __COMPILER_MICROCHIP__
                yp = __builtin_mulss(B1, IN) >> SFR1;	/* Q15 */
                I_OLD += (__builtin_mulss(B0, temp) << (31-SFR0));	/* Q46 = Q15+31*/
            #else
                I_OLD += (((int64)B0 * (int64)temp) << (31-SFR0));	/* Q46 = Q15+31*/
            #endif
		}
		/* ********************************************/
		/*      Calculate proportional term           */
		tempSpeed = ((int32)V_GAIN*temp) >> SFR_GAIN;				/* Q15 */


		/* add Integrator-Term */
		yp = ((int32)B1_I * (int32)y) >> SFR_B1_I;					/* proportional term of integrator: if bilinear transform is used b1 is different from 0 */
		// tempSpeed +=  (yp + (int32)(I_OLD_I >> 15));				/* Q15 */
        temp = (yp + (int32)(I_OLD_I >> 15));                       /* Q15 */
        tempSpeed += temp;
        if (USE_RAW_SPEED==0){
            SPEED = (int16)(temp);
        }

		/* Integral term */
		#ifdef __XC16__
			I_OLD_I += ((__builtin_mulss(B0_I,y)) << (15-SFR0_I));	/* Q30 */
		#else
			I_OLD_I += (((int32)B0_I * (int32)y) << (15-SFR0_I));	/* Q30 */
		#endif

		/* ****************************** */
		/* Calculate rotor angle phi ******/
		yp   = ((int32)B1_UI * (int32)tempSpeed) >> SFR_B1_UI;			/* proportional term of integrator: if bilinear-transform is used b1 is different from 0 */
		PHI  = yp + (int32)(I_OLD_UI >> 15);							/* Q15 */
        if (USE_RAW_SPEED == 1){
            SPEED = (int16)(tempSpeed);
        }
		SYNC = 0;

		/* Integral term */
        #ifdef __COMPILER_MICROCHIP__
            I_OLD_UI += ((__builtin_mulss(B0_UI,(int16)tempSpeed)) << (15-SFR0_UI));	/* Q30 */
        #else
            I_OLD_UI += (((int32)B0_UI * tempSpeed) << (15-SFR0_UI));	/* Q30 */
        #endif

	}
	else
	{
		/* Block disabled:
		 * -calculation of PHI is disabled, but
		 * -Sync-Pulse generation is done
		 * */
		if (TOGGLE_STATUS == PERIOD){
			TOGGLE_STATUS = 1;
		}
		else{
			TOGGLE_STATUS++;
		}

		switch (TOGGLE_STATUS){
			case 1:
				/* out=amp*/
				SYNC = 0;
				break;

			case 2:
				/* out=-amp */
				SYNC = INT16_MAX;
				break;
		}

		/* set PHI to phiInit Input */
		PHI   = INIT_PHI;
        SPEED = INIT_SPEED;
	}
	ENABLE_OLD = ENABLE;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void SquareInj_Slow_Modell_FiP16_Init(SQUAREINJ_SLOW_MODELL_FIP16 *pTSquareInj_Slow_Modell_FiP16)
{
    pTSquareInj_Slow_Modell_FiP16->ID = SQUAREINJ_SLOW_MODELL_FIP16_ID;
    pTSquareInj_Slow_Modell_FiP16->phi = 0;
    pTSquareInj_Slow_Modell_FiP16->Sync = 0;
    pTSquareInj_Slow_Modell_FiP16->speed = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    I_OLD = ((int32)0) << 31;		        /* torque init Q46 */
    I_OLD_I = ((int32)INIT_SPEED) << 15;	/* speed init Q30 */
    I_OLD_UI = ((int32)INIT_PHI) << 15;		/* angle init Q30 */
    ENABLE_OLD = false;
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 SquareInj_Slow_Modell_FiP16_Load(const SQUAREINJ_SLOW_MODELL_FIP16 *pTSquareInj_Slow_Modell_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)51 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTSquareInj_Slow_Modell_FiP16->b0 & 0x000000FF);
        data[1] = (uint8)((pTSquareInj_Slow_Modell_FiP16->b0 >> 8) & 0x000000FF);
        data[2] = (uint8)((pTSquareInj_Slow_Modell_FiP16->b0 >> 16) & 0x000000FF);
        data[3] = (uint8)((pTSquareInj_Slow_Modell_FiP16->b0 >> 24) & 0x000000FF);
        data[4] = (uint8)(pTSquareInj_Slow_Modell_FiP16->b1 & 0x000000FF);
        data[5] = (uint8)((pTSquareInj_Slow_Modell_FiP16->b1 >> 8) & 0x000000FF);
        data[6] = (uint8)((pTSquareInj_Slow_Modell_FiP16->b1 >> 16) & 0x000000FF);
        data[7] = (uint8)((pTSquareInj_Slow_Modell_FiP16->b1 >> 24) & 0x000000FF);
        data[8] = (uint8)pTSquareInj_Slow_Modell_FiP16->sfrb0;
        data[9] = (uint8)pTSquareInj_Slow_Modell_FiP16->sfrb1;
        data[10] = (uint8)(pTSquareInj_Slow_Modell_FiP16->a0_PT1 & 0x00FF);
        data[11] = (uint8)((pTSquareInj_Slow_Modell_FiP16->a0_PT1 >> 8) & 0x00FF);
        data[12] = (uint8)(pTSquareInj_Slow_Modell_FiP16->b0_PT1 & 0x00FF);
        data[13] = (uint8)((pTSquareInj_Slow_Modell_FiP16->b0_PT1 >> 8) & 0x00FF);
        data[14] = (uint8)(pTSquareInj_Slow_Modell_FiP16->b1_PT1 & 0x00FF);
        data[15] = (uint8)((pTSquareInj_Slow_Modell_FiP16->b1_PT1 >> 8) & 0x00FF);
        data[16] = (uint8)(pTSquareInj_Slow_Modell_FiP16->sfra_PT1 & 0x00FF);
        data[17] = (uint8)((pTSquareInj_Slow_Modell_FiP16->sfra_PT1 >> 8) & 0x00FF);
        data[18] = (uint8)(pTSquareInj_Slow_Modell_FiP16->sfrb_PT1 & 0x00FF);
        data[19] = (uint8)((pTSquareInj_Slow_Modell_FiP16->sfrb_PT1 >> 8) & 0x00FF);
        data[20] = (uint8)(pTSquareInj_Slow_Modell_FiP16->dphiOld & 0x00FF);
        data[21] = (uint8)((pTSquareInj_Slow_Modell_FiP16->dphiOld >> 8) & 0x00FF);
        data[22] = (uint8)(pTSquareInj_Slow_Modell_FiP16->b0_uI & 0x00FF);
        data[23] = (uint8)((pTSquareInj_Slow_Modell_FiP16->b0_uI >> 8) & 0x00FF);
        data[24] = (uint8)(pTSquareInj_Slow_Modell_FiP16->sfr_uI & 0x00FF);
        data[25] = (uint8)((pTSquareInj_Slow_Modell_FiP16->sfr_uI >> 8) & 0x00FF);
        data[26] = (uint8)(pTSquareInj_Slow_Modell_FiP16->i_old_uI & 0x000000FF);
        data[27] = (uint8)((pTSquareInj_Slow_Modell_FiP16->i_old_uI >> 8) & 0x000000FF);
        data[28] = (uint8)((pTSquareInj_Slow_Modell_FiP16->i_old_uI >> 16) & 0x000000FF);
        data[29] = (uint8)((pTSquareInj_Slow_Modell_FiP16->i_old_uI >> 24) & 0x000000FF);
        data[30] = (uint8)(pTSquareInj_Slow_Modell_FiP16->b0_I & 0x00FF);
        data[31] = (uint8)((pTSquareInj_Slow_Modell_FiP16->b0_I >> 8) & 0x00FF);
        data[32] = (uint8)(pTSquareInj_Slow_Modell_FiP16->sfr_I & 0x00FF);
        data[33] = (uint8)((pTSquareInj_Slow_Modell_FiP16->sfr_I >> 8) & 0x00FF);
        data[34] = (uint8)(pTSquareInj_Slow_Modell_FiP16->i_old_I & 0x000000FF);
        data[35] = (uint8)((pTSquareInj_Slow_Modell_FiP16->i_old_I >> 8) & 0x000000FF);
        data[36] = (uint8)((pTSquareInj_Slow_Modell_FiP16->i_old_I >> 16) & 0x000000FF);
        data[37] = (uint8)((pTSquareInj_Slow_Modell_FiP16->i_old_I >> 24) & 0x000000FF);
        data[38] = (uint8)pTSquareInj_Slow_Modell_FiP16->rawSpeed;
        data[39] = (uint8)(pTSquareInj_Slow_Modell_FiP16->vGain & 0x00FF);
        data[40] = (uint8)((pTSquareInj_Slow_Modell_FiP16->vGain >> 8) & 0x00FF);
        data[41] = (uint8)(pTSquareInj_Slow_Modell_FiP16->sfrGain & 0x00FF);
        data[42] = (uint8)((pTSquareInj_Slow_Modell_FiP16->sfrGain >> 8) & 0x00FF);
        data[43] = (uint8)(pTSquareInj_Slow_Modell_FiP16->b1_I & 0x00FF);
        data[44] = (uint8)((pTSquareInj_Slow_Modell_FiP16->b1_I >> 8) & 0x00FF);
        data[45] = (uint8)(pTSquareInj_Slow_Modell_FiP16->b1_uI & 0x00FF);
        data[46] = (uint8)((pTSquareInj_Slow_Modell_FiP16->b1_uI >> 8) & 0x00FF);
        data[47] = (uint8)(pTSquareInj_Slow_Modell_FiP16->sfrb1_I & 0x00FF);
        data[48] = (uint8)((pTSquareInj_Slow_Modell_FiP16->sfrb1_I >> 8) & 0x00FF);
        data[49] = (uint8)(pTSquareInj_Slow_Modell_FiP16->sfrb1_uI & 0x00FF);
        data[50] = (uint8)((pTSquareInj_Slow_Modell_FiP16->sfrb1_uI >> 8) & 0x00FF);
        *dataLength = (uint16)51;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 SquareInj_Slow_Modell_FiP16_Save(SQUAREINJ_SLOW_MODELL_FIP16 *pTSquareInj_Slow_Modell_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)51)
    {
        error = (uint8)1;
    }
    else
    {
        pTSquareInj_Slow_Modell_FiP16->b0 = UINT32_TO_INT32((uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24));
        pTSquareInj_Slow_Modell_FiP16->b1 = UINT32_TO_INT32((uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24));
        pTSquareInj_Slow_Modell_FiP16->sfrb0 = UINT8_TO_INT8((uint8)data[8]);
        pTSquareInj_Slow_Modell_FiP16->sfrb1 = UINT8_TO_INT8((uint8)data[9]);
        pTSquareInj_Slow_Modell_FiP16->a0_PT1 = UINT16_TO_INT16((uint16)data[10] + \
            ((uint16)data[11] << 8));
        pTSquareInj_Slow_Modell_FiP16->b0_PT1 = UINT16_TO_INT16((uint16)data[12] + \
            ((uint16)data[13] << 8));
        pTSquareInj_Slow_Modell_FiP16->b1_PT1 = UINT16_TO_INT16((uint16)data[14] + \
            ((uint16)data[15] << 8));
        pTSquareInj_Slow_Modell_FiP16->sfra_PT1 = UINT16_TO_INT16((uint16)data[16] + \
            ((uint16)data[17] << 8));
        pTSquareInj_Slow_Modell_FiP16->sfrb_PT1 = UINT16_TO_INT16((uint16)data[18] + \
            ((uint16)data[19] << 8));
        pTSquareInj_Slow_Modell_FiP16->dphiOld = UINT16_TO_INT16((uint16)data[20] + \
            ((uint16)data[21] << 8));
        pTSquareInj_Slow_Modell_FiP16->b0_uI = UINT16_TO_INT16((uint16)data[22] + \
            ((uint16)data[23] << 8));
        pTSquareInj_Slow_Modell_FiP16->sfr_uI = UINT16_TO_INT16((uint16)data[24] + \
            ((uint16)data[25] << 8));
        pTSquareInj_Slow_Modell_FiP16->i_old_uI = UINT32_TO_INT32((uint32)data[26] + \
            ((uint32)data[27] << 8) + ((uint32)data[28] << 16) + \
            ((uint32)data[29] << 24));
        pTSquareInj_Slow_Modell_FiP16->b0_I = UINT16_TO_INT16((uint16)data[30] + \
            ((uint16)data[31] << 8));
        pTSquareInj_Slow_Modell_FiP16->sfr_I = UINT16_TO_INT16((uint16)data[32] + \
            ((uint16)data[33] << 8));
        pTSquareInj_Slow_Modell_FiP16->i_old_I = UINT32_TO_INT32((uint32)data[34] + \
            ((uint32)data[35] << 8) + ((uint32)data[36] << 16) + \
            ((uint32)data[37] << 24));
        pTSquareInj_Slow_Modell_FiP16->rawSpeed = UINT8_TO_INT8((uint8)data[38]);
        pTSquareInj_Slow_Modell_FiP16->vGain = UINT16_TO_INT16((uint16)data[39] + \
            ((uint16)data[40] << 8));
        pTSquareInj_Slow_Modell_FiP16->sfrGain = UINT16_TO_INT16((uint16)data[41] + \
            ((uint16)data[42] << 8));
        pTSquareInj_Slow_Modell_FiP16->b1_I = UINT16_TO_INT16((uint16)data[43] + \
            ((uint16)data[44] << 8));
        pTSquareInj_Slow_Modell_FiP16->b1_uI = UINT16_TO_INT16((uint16)data[45] + \
            ((uint16)data[46] << 8));
        pTSquareInj_Slow_Modell_FiP16->sfrb1_I = UINT16_TO_INT16((uint16)data[47] + \
            ((uint16)data[48] << 8));
        pTSquareInj_Slow_Modell_FiP16->sfrb1_uI = UINT16_TO_INT16((uint16)data[49] + \
            ((uint16)data[50] << 8));
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(SQUAREINJ_SLOW_MODELL_FIP16_ISLINKED)
void* SquareInj_Slow_Modell_FiP16_GetAddress(const SQUAREINJ_SLOW_MODELL_FIP16* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->dphi;
            break;
        case 2:
            addr = (void*)block->phi0;
            break;
        case 3:
            addr = (void*)block->n0;
            break;
        case 4:
            addr = (void*)block->Enable;
            break;
        case 5:
            addr = (void*)&block->phi;
            break;
        case 6:
            addr = (void*)&block->Sync;
            break;
        case 7:
            addr = (void*)&block->speed;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
