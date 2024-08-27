/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "SquareInjection_Fast_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(SquareInjection_Fast_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Atan_Data.h"

/* inputs */
#define I_D			(*pTSquareInjection_Fast_FiP16->Ix)
#define I_Y			(*pTSquareInjection_Fast_FiP16->Iy)
#define SYNC		(*pTSquareInjection_Fast_FiP16->Sync)
#define ENABLE_INJ	(*pTSquareInjection_Fast_FiP16->EnableInj)
#define ENABLE		(*pTSquareInjection_Fast_FiP16->Enable)

/* outputs */
#define U_D			(pTSquareInjection_Fast_FiP16->Ud)
#define PHI_INIT	(pTSquareInjection_Fast_FiP16->PhiInit)			/* holds initial angle estimation value */
#define EN_PLL		(pTSquareInjection_Fast_FiP16->EnablePLL)
#define EN_CTRL		(pTSquareInjection_Fast_FiP16->EnableCtrl)
#define DPHI		(pTSquareInjection_Fast_FiP16->dPhi)


/* variables */
#define LCNT		(pTSquareInjection_Fast_FiP16->tmp1)			/* loop-counter */
#define PHI			(pTSquareInjection_Fast_FiP16->tmp2)			/* commutation angle during pulsing */
#define DIR			(pTSquareInjection_Fast_FiP16->tmp3)			/* direction of voltage pulse */
#define ID_MAX		(pTSquareInjection_Fast_FiP16->tmp4)			/* maximum current in d-direction */
#define ID_MIN		(pTSquareInjection_Fast_FiP16->tmp5)			/* maximum current in -d-direction */
#define IQ_MAX		(pTSquareInjection_Fast_FiP16->tmp6)			/* maximum current in q-direction */
#define IQ_MIN		(pTSquareInjection_Fast_FiP16->tmp7)			/* maximum current in -q-direction */
#define FOUND_PHI_INIT (pTSquareInjection_Fast_FiP16->foundPhiInit) /* flag that signals whether initial rotor angle was already calculated or not */
#define TOGGLE_STATUS	(pTSquareInjection_Fast_FiP16->toggleStatus)
#define IY_0		(pTSquareInjection_Fast_FiP16->iy0)				/* Array holding the last current values in y coordinate */
#define IY_1		(pTSquareInjection_Fast_FiP16->iy1)				/* Array holding the last current values in y coordinate */
#define IY_2		(pTSquareInjection_Fast_FiP16->iy2)				/* Array holding the last current values in y coordinate */
#define IY_3		(pTSquareInjection_Fast_FiP16->iy3)				/* Array holding the last current values in y coordinate */
#define IY_4		(pTSquareInjection_Fast_FiP16->iy4)				/* Array holding the last current values in y coordinate */
#define INJ_ACTIVE	(pTSquareInjection_Fast_FiP16->actInj)			/* flag that signals whether injection is activated or not */


/* mask parameter */
#define T1			(pTSquareInjection_Fast_FiP16->t1)			/* time-delay after 'enable' of first pulse */
#define DELTA_T		(pTSquareInjection_Fast_FiP16->deltaT)		/* time between consecutive pulses (D,-D,Q,-Q) */
#define T_PULSE		(pTSquareInjection_Fast_FiP16->t_pulse)		/* duration of one pulse */

#define DELAY_PLL	(pTSquareInjection_Fast_FiP16->delayPLL)	/* time delay after witch PLL is enabled */
#define DELAY_CTRL	(pTSquareInjection_Fast_FiP16->delayCtrl)	/* time delay after witch controllers are enabled */

#define US_AMP		(pTSquareInjection_Fast_FiP16->iUsAmp)			/* amplitude of voltage-pulses for determining initial rotor angle */
#define U_INJ_AMP	(pTSquareInjection_Fast_FiP16->uInjAmp)		/* amplitude of injected square-wave voltage */


/* time macros */
#define T2			(T1 + DELTA_T)
#define T3			(T2 + DELTA_T)
#define T4			(T3 + DELTA_T)
#define T5			(T4 + DELTA_T)
#define	T_END		(T5 + DELTA_T)

/* Quadrant Offset Macros */
#define ATAN2_OFFSET_Q2		0x4000
#define ATAN2_OFFSET_Q34	0x8000
#define ATAN2_OFFSET_COT	0x3FFF
#define QUARTER_PI			0x2000		/* 45� */


/* Toggle Macros */
#define PERIOD 		(2)

int16 sampleCnt = 0;
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void SquareInjection_Fast_FiP16_Update(SQUAREINJECTION_FAST_FIP16 *pTSquareInjection_Fast_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	/* atan2 variables */
	int16   iFact, iY, iX;
	int32	arg  = (int32)0;
	int8	iTan =  (int8)1;		/* 1 -> tangent for Q1 & Q3, 0 -> cotangent for Q2 & Q4 */
	int8	Q13  =  (int8)1;		/* 1 -> Q1 or Q3 */
	int16   out1 = (int16)0;

	if (ENABLE != false)
	{
		/* determine initial rotor- angle */
		if (FOUND_PHI_INIT == 0 ){
			/* limit increment of loop counter */
			if (LCNT < T_END) {
				LCNT++;
			}

			/*--------------------------------------------------------------------------------*/
			/* wait for T1 ms */
			if ( (LCNT>=1) && (LCNT < T1) ){
				U_D = 0;
				PHI_INIT = 0;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;

			}
			/*--------------------------------------------------------------------------------*/
			/* output ud in D-direction */
			else if ((LCNT >= T1) && (LCNT < T1 + T_PULSE)){
				DIR = 1;
				U_D = US_AMP;
				PHI_INIT = 0;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;
			}

			/* output -ud in D-direction */
			else if ((LCNT >= T1 + T_PULSE) && (LCNT < T1 + 2*T_PULSE)){
				U_D = -US_AMP;
				PHI_INIT = 0;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;
			}

			/* output zero */
			else if ((LCNT >= T1 + 2*T_PULSE) && (LCNT < T2-5)){
				U_D = 0;
				PHI_INIT = 0;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;
			}
			/*--------------------------------------------------------------------------------*/

			/* switch commutation angle */
			else if ((LCNT >= T2-5) && (LCNT < T2)){
				U_D = 0;
				PHI_INIT = INT16_MAX;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;
			}
			/*--------------------------------------------------------------------------------*/

			/* output ud in -D-direction */
			else if ((LCNT >= T2) && (LCNT < T2 + T_PULSE)){
				DIR = -1;
				U_D = US_AMP;
				PHI_INIT = INT16_MAX;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;
			}

			/* output -ud in -D-direction */
			else if ((LCNT >= T2 + T_PULSE) && (LCNT < T2 + 2*T_PULSE)){
				U_D = -US_AMP;
				PHI_INIT = INT16_MAX;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;
			}

			/* output zero */
			else if ((LCNT >= T2 + 2*T_PULSE) && (LCNT < T3-5)){
				U_D = 0;
				PHI_INIT = INT16_MAX;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;
			}
			/*--------------------------------------------------------------------------------*/

			/* switch commutation angle */
			else if ((LCNT >= T3-5) && (LCNT < T3)){
				U_D = 0;
				PHI_INIT = INT15_MAX;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;
			}
			/*--------------------------------------------------------------------------------*/

			/* output ud in Q-direction */
			else if ((LCNT >= T3) && (LCNT < T3 + T_PULSE)){
				DIR = 2;
				U_D = US_AMP;
				PHI_INIT = INT15_MAX;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;
			}

			/* output -ud in Q-direction */
			else if ((LCNT >= T3 + T_PULSE) && (LCNT < T3 + 2*T_PULSE)){
				U_D = -US_AMP;
				PHI_INIT = INT15_MAX;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;
			}

			/* output zero */
			else if ((LCNT >= T3 + 2*T_PULSE) && (LCNT < T4-5)){
				U_D = 0;
				PHI_INIT = INT15_MAX;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;
			}

			/*--------------------------------------------------------------------------------*/

			/* switch commutation angle */
			else if ((LCNT >= T4-5) && (LCNT < T4)){
				U_D = 0;
				PHI_INIT = INT15_MIN;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;			}
			/*--------------------------------------------------------------------------------*/

			/* output ud in -Q-direction */
			else if ((LCNT >= T4) && (LCNT < T4 + T_PULSE)){
				DIR = -2;
				U_D = US_AMP;
				PHI_INIT = INT15_MIN;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;			}

			/* output -ud in -Q-direction */
			else if ((LCNT >= T4 + T_PULSE) && (LCNT < T4 + 2*T_PULSE)){
				U_D = -US_AMP;
				PHI_INIT = INT15_MIN;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;			}

			/* output zero */
			else if ((LCNT >= T4 + 2*T_PULSE) && (LCNT < T5-5)){
				U_D = 0;
				PHI_INIT = INT15_MIN;
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;			}
			/*--------------------------------------------------------------------------------*/

			/* calc maxima and minima */
			if (LCNT <  T5 -5){
				/* D-Direction */
				if (DIR==1){			/* positive D direction */
					/* max */
					if (I_D > ID_MAX){
						ID_MAX = I_D;
					}
				}
				else if (DIR==-1){		/* negative D direction */
					/* min */
					if (I_D > ID_MIN){
						ID_MIN = I_D;
					}
				}
				/* Q-Direction */
				else if (DIR==2){		/* positive Q direction */
					/* max */
					if (I_D > IQ_MAX){
						IQ_MAX = I_D;
					}
				}
				else if (DIR==-2){		/* negative -Q direction */
					/* min */
					if (I_D > IQ_MIN){
						IQ_MIN = I_D;
					}
				}

			}
			/*--------------------------------------------------------------------------------*/

			/* calc differences of max/min and atan2 */
			if ((LCNT >=  T5 - 5 )&&(EN_PLL == false)){
				/* differences */
				iX = (int16)((int32)ID_MAX - (int32)ID_MIN);
				iY = (int16)((int32)IQ_MAX - (int32)IQ_MIN);

				/* atan2 */
                /* check input range (negating lowest negative number could lead to division by zero) */
                if (iX == (int16)0x8000)
                {
                    iX = (int16)0x8001;
                }
                if (iY == (int16)0x8000)
                {
                    iY = (int16)0x8001;
                }
                
				if ((iY == 0) && (iX == 0))
				{
					out1 = 0;
				}
				else
				{
					/* Check quadrants */
					if (iY < (int16)0)
					{
						iY   = -iY;
						out1 = ATAN2_OFFSET_Q34;
						if (iX > (int16)0)	/* 4th quadrant */
						{
							out1 += ATAN2_OFFSET_Q2;
							Q13   = (int8)0;
						}
						else
						{			/* 3rd quadrant */
							iX   = -iX;
						}
					}
					else
					{
						if (iX < (int16)0)	/* 2nd quadrant */
						{
							iX   = -iX;
							out1 = ATAN2_OFFSET_Q2;
							Q13  = (int8)0;
						}
					}

					/* Check region in quadrant */
					if (iY > iX)	/* angle > 45� */
					{
						iFact = iX;			/* swap input arguments	 (iFact is used as temporary variable) */
						iX	  = iY;			/* swap input arguments */
						iY    = iFact;		/* swap input arguments */
						iTan  = (int8)0;	/* use cotangent */
					}

					if (iY != iX)
					{
						/* Calculation of y/x */
						arg  = (int32)iY << 16;	/* Q15,32 */
#if defined(__XC16__)
                        arg = __builtin_divsd(arg, iX); /* Q16,32 */
#else
                        arg = arg / iX;                /* Q16,32 */
#endif

						/* Interpolation */
						LOOKUP16(Atan_Table16, (uint16)arg, iFact);
					}
					else
					{
						iFact = QUARTER_PI;		/* angle = 45� */
					}

					/* Check for need of cotangent correction */
					if (Q13 ^ iTan)
					{
						out1 += ((int16)ATAN2_OFFSET_COT - iFact);
					}
					else
					{
						out1 += iFact;
					}
				}


				PHI = out1;					/* assign output angle */

				/* assign block outputs */
				U_D = 0;
				PHI_INIT = PHI;				/* estimated angle */
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;

				/* set initial-rotor-angle-found flag */
				FOUND_PHI_INIT = INT16_MAX;
			}
		}

		/* initial rotor- angle was found */
		else{ /*  FOUND_PHI_INIT != 0 */

			/* synchronize fast-Task with slow-Task via SYNC input */
			if ((INJ_ACTIVE == 0)&&(SYNC != 0)){
				/* reset loop counter with rising edge of SYNC */
				LCNT = 0;
				sampleCnt = 0;
				/* activate injection of square wave voltage */
				INJ_ACTIVE = INT16_MAX;
			}


			/* if SYNC was done */
			if (INJ_ACTIVE){
				/* increment loop counter */
				if (LCNT < INT16_MAX){
					LCNT++;
				}


				if (ENABLE_INJ != false)	/* only if Enable-Injection input is set */
				{
					/* inject hf- voltage */
					if (TOGGLE_STATUS == PERIOD){
						TOGGLE_STATUS = 1;
					}
					else{
						TOGGLE_STATUS++;
					}

					switch (TOGGLE_STATUS){
						case 1:
							/* out=amp*/
							U_D = -U_INJ_AMP;
							break;

						case 2:
							/* out=-amp */
							U_D = U_INJ_AMP;
							break;
					}

					/* store current sample in estimated reference frame */
					IY_0 = IY_1;		/* currents in estimated q-direction */
					IY_1 = IY_2;
					IY_2 = IY_3;
					IY_3 = IY_4;
					IY_4 = (int32)I_Y;

					sampleCnt++;
					if (sampleCnt >= 4)
					{ /* calculate hf-component of y-current =  calculate angle error */
						int32 tmp32q;
						/* quadratc model i=i0+ic+m*t+q*t^2 */
						/*  skip division by 8; coeffs:[-1/8 3/8 -3/8 1/8] */
						tmp32q = -IY_0 + 3*IY_1 - 3*IY_2 + IY_3;	/* use 1*Ts delayed currents, since input-value IY is stored */
						//tmp32q = -IY_1 + 3*IY_2 - 3*IY_3 + IY_4;

						/* no limitation implemented due to small hf-currents */
						DPHI = (int16)tmp32q;
						sampleCnt = 0;
					}
				}
				else
			    /* if Enable-Injection input is false */
				{
					U_D = 0;
					DPHI = 0;
				}

				/* set Enables for PLL and controllers */
				if (LCNT >= DELAY_PLL){
					EN_PLL = true;
				}
				if (LCNT >= DELAY_CTRL){
					EN_CTRL = true;
				}
			}
			/* injection is not yet active */
			else{
				U_D = 0;
				PHI_INIT = PHI;				/* estimated angle */
				DPHI = 0;
				EN_PLL = false;
				EN_CTRL = false;
			}
		}
	}
	/* ENABLE == false */
	else{
		/* reset outputs */
		U_D = 0;
		PHI_INIT = 0;
		DPHI = 0;
		EN_PLL = false;
		EN_CTRL = false;

		/* reset vars */
		PHI = 0;
		LCNT = 0;
		ID_MAX = 0;
		ID_MIN = 0;
		IQ_MAX = 0;
		IQ_MIN = 0;
		DIR = 0;
		INJ_ACTIVE = 0;
		FOUND_PHI_INIT = 0;
		TOGGLE_STATUS = 0;
		IY_0= 0;
		IY_1= 0;
		IY_2= 0;
		IY_3= 0;
		IY_4= 0;
	}

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void SquareInjection_Fast_FiP16_Init(SQUAREINJECTION_FAST_FIP16 *pTSquareInjection_Fast_FiP16)
{
    pTSquareInjection_Fast_FiP16->ID = SQUAREINJECTION_FAST_FIP16_ID;
    pTSquareInjection_Fast_FiP16->Ud = 0;
    pTSquareInjection_Fast_FiP16->PhiInit = 0;
    pTSquareInjection_Fast_FiP16->EnablePLL = 0;
    pTSquareInjection_Fast_FiP16->EnableCtrl = 0;
    pTSquareInjection_Fast_FiP16->dPhi = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
	PHI = 0;
	LCNT = 0;
	ID_MAX = 0;
	ID_MIN = 0;
	IQ_MAX = 0;
	IQ_MIN = 0;
	DIR = 0;
	INJ_ACTIVE = 0;
	FOUND_PHI_INIT = 0;
	TOGGLE_STATUS = 0;
	IY_0= 0;
	IY_1= 0;
	IY_2= 0;
	IY_3= 0;
	IY_4= 0;
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 SquareInjection_Fast_FiP16_Load(const SQUAREINJECTION_FAST_FIP16 *pTSquareInjection_Fast_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)14 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTSquareInjection_Fast_FiP16->iUsAmp & 0x00FF);
        data[1] = (uint8)((pTSquareInjection_Fast_FiP16->iUsAmp >> 8) & 0x00FF);
        data[2] = (uint8)(pTSquareInjection_Fast_FiP16->t_pulse & 0x00FF);
        data[3] = (uint8)((pTSquareInjection_Fast_FiP16->t_pulse >> 8) & 0x00FF);
        data[4] = (uint8)(pTSquareInjection_Fast_FiP16->t1 & 0x00FF);
        data[5] = (uint8)((pTSquareInjection_Fast_FiP16->t1 >> 8) & 0x00FF);
        data[6] = (uint8)(pTSquareInjection_Fast_FiP16->deltaT & 0x00FF);
        data[7] = (uint8)((pTSquareInjection_Fast_FiP16->deltaT >> 8) & 0x00FF);
        data[8] = (uint8)(pTSquareInjection_Fast_FiP16->delayPLL & 0x00FF);
        data[9] = (uint8)((pTSquareInjection_Fast_FiP16->delayPLL >> 8) & 0x00FF);
        data[10] = (uint8)(pTSquareInjection_Fast_FiP16->delayCtrl & 0x00FF);
        data[11] = (uint8)((pTSquareInjection_Fast_FiP16->delayCtrl >> 8) & 0x00FF);
        data[12] = (uint8)(pTSquareInjection_Fast_FiP16->uInjAmp & 0x00FF);
        data[13] = (uint8)((pTSquareInjection_Fast_FiP16->uInjAmp >> 8) & 0x00FF);
        *dataLength = (uint16)14;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 SquareInjection_Fast_FiP16_Save(SQUAREINJECTION_FAST_FIP16 *pTSquareInjection_Fast_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)14)
    {
        error = (uint8)1;
    }
    else
    {
        pTSquareInjection_Fast_FiP16->iUsAmp = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTSquareInjection_Fast_FiP16->t_pulse = UINT16_TO_INT16((uint16)data[2] + \
            ((uint16)data[3] << 8));
        pTSquareInjection_Fast_FiP16->t1 = UINT16_TO_INT16((uint16)data[4] + \
            ((uint16)data[5] << 8));
        pTSquareInjection_Fast_FiP16->deltaT = UINT16_TO_INT16((uint16)data[6] + \
            ((uint16)data[7] << 8));
        pTSquareInjection_Fast_FiP16->delayPLL = ((uint16)data[8] + \
            ((uint16)data[9] << 8));
        pTSquareInjection_Fast_FiP16->delayCtrl = ((uint16)data[10] + \
            ((uint16)data[11] << 8));
        pTSquareInjection_Fast_FiP16->uInjAmp = UINT16_TO_INT16((uint16)data[12] + \
            ((uint16)data[13] << 8));
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(SQUAREINJECTION_FAST_FIP16_ISLINKED)
void* SquareInjection_Fast_FiP16_GetAddress(const SQUAREINJECTION_FAST_FIP16* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->Ix;
            break;
        case 2:
            addr = (void*)block->Iy;
            break;
        case 3:
            addr = (void*)block->Sync;
            break;
        case 4:
            addr = (void*)block->EnableInj;
            break;
        case 5:
            addr = (void*)block->Enable;
            break;
        case 6:
            addr = (void*)&block->Ud;
            break;
        case 7:
            addr = (void*)&block->PhiInit;
            break;
        case 8:
            addr = (void*)&block->EnablePLL;
            break;
        case 9:
            addr = (void*)&block->EnableCtrl;
            break;
        case 10:
            addr = (void*)&block->dPhi;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
