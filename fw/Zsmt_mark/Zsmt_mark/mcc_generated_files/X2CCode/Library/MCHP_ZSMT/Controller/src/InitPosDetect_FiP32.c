/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2108 $
 * $LastChangedDate:: 2020-12-07 19:09:57 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: 
    Calculation of initial rotor angle. */
/* USERCODE-END:Description                                                                                           */
#include "InitPosDetect_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(InitPosDetect_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Atan_Data.h"

/* Inputs */
#define IA         	    getAbsValI32(*pTInitPosDetect_FiP32->I_A)
#define IB         	    getAbsValI32(*pTInitPosDetect_FiP32->I_B)
#define IC         	    getAbsValI32(*pTInitPosDetect_FiP32->I_C)
#define ENABLE      	(*pTInitPosDetect_FiP32->Enable)

/* Outputs */
#define UA         	    (pTInitPosDetect_FiP32->U_A)
#define UB         	    (pTInitPosDetect_FiP32->U_B)
#define UC         	    (pTInitPosDetect_FiP32->U_C)
#define PHI_INIT    	(pTInitPosDetect_FiP32->phi0)          /* holds initial angle estimation value */
#define READY           (pTInitPosDetect_FiP32->Ready)

/* Parameters */
#define T_PERIOD     	(pTInitPosDetect_FiP32->t_period)       /* time between consecutive pulses (-A, -B, -C, A, B, C) */
#define T_PULSE     	(pTInitPosDetect_FiP32->t_pulse)        /* duration of one pulse */
#define U_PULSE        	(pTInitPosDetect_FiP32->u_pulse)        /* amplitude of voltage-pulses for determining initial rotor angle */

/* Variables */
#define TIMER           (pTInitPosDetect_FiP32->timer)          /* loop-counter */
#define PHI             (pTInitPosDetect_FiP32->phi)            /* commutation angle during pulsing */
#define DIR             (pTInitPosDetect_FiP32->dir)            /* direction of voltage pulse: DIR=-1->neg. Phase A, -2=neg. phase B, -3=neg. phase C, 1=phase A, 2=phase B, 3=phase C */
#define MAX_IA_POS      (pTInitPosDetect_FiP32->max_ia_pos)     /* maximum current in phase A direction */
#define MAX_IA_NEG      (pTInitPosDetect_FiP32->max_ia_neg)     /* maximum current in negative phase A direction */
#define MAX_IB_POS      (pTInitPosDetect_FiP32->max_ib_pos)     /* maximum current in phase B direction */
#define MAX_IB_NEG      (pTInitPosDetect_FiP32->max_ib_neg)     /* maximum current in negative phase B direction */
#define MAX_IC_POS      (pTInitPosDetect_FiP32->max_ic_pos)     /* maximum current in phase C direction */
#define MAX_IC_NEG      (pTInitPosDetect_FiP32->max_ic_neg)     /* maximum current in negative phase C direction */

/* Time macros */
#define T1          	( 0 + T_PERIOD)
#define T2              (T1 + T_PERIOD)
#define T3              (T2 + T_PERIOD)
#define T4              (T3 + T_PERIOD)
#define T5              (T4 + T_PERIOD)
#define T6              (T5 + T_PERIOD)
#define T_END           (T6)

/* Quadrant offset macros */
#define ATAN2_OFFSET_Q2     0x40000000
#define ATAN2_OFFSET_Q34    0x80000000
#define ATAN2_OFFSET_COT    0x3FFFFFFF
#define QUARTER_PI          0x20000000      /* 45 degrees */

/* Constants */
#define KAPPA               ((int32)-1239850262)    /* cos(2*pi/3)/sin(2*pi/3) = -0.5773503 */
#define PI                  (INT32_MAX)
#define PI_DIV_3            ((int32)715827883)
#define PI_2_DIV_3          ((int32)1431655765)
#define INV_3               ((int64)715827883)      /* 1/3 */
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void InitPosDetect_FiP32_Update(INITPOSDETECT_FIP32 *pTInitPosDetect_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    /* atan2 variables */
    int32   iFact, iY, iX;
    int64   arg  = (int64)0;
    int8    iTan =  (int8)1;        /* 1 -> tangent for Q1 & Q3, 0 -> cotangent for Q2 & Q4 */
    int8    Q13  =  (int8)1;        /* 1 -> Q1 or Q3 */
    int32   out1 = (int32)0;
    
    /* direction of maximal current */
    int8 max_dir = 0;
    int8 max_dir_pos, max_dir_neg;
            
    
    /* average currents */
    int32 I0 = 0;
    int32 I0_neg = 0;
    
    /* current changes */
    int64 diff_IA = 0;
    int64 diff_IB = 0;
    int64 diff_IC = 0;
    int64 max_dI  = 0;
    
    int64 diff_IA_neg = 0;
    int64 diff_IB_neg = 0;
    int64 diff_IC_neg = 0;
    int64 max_dI_neg  = 0;
    
    int32 phiOffset;
    int32 temp32;
    int64 temp64;
    

    if (ENABLE)
    {
        /* determine initial rotor angle */
        if (!READY)
        {
            /*------------------------------- -PHASE A ----------------------------------------*/
            /* negative voltage pulse in phase A-direction */
            if (TIMER < T_PULSE)
            {
                DIR = -1;
                UA = -U_PULSE;
                UB = U_PULSE>>1;
                UC = U_PULSE>>1;
                PHI_INIT = 0;
                READY = false;
            }

            /* output opposite voltage pulse */
            else if (TIMER < (2*T_PULSE))
            {
                UA = U_PULSE;
                UB = -(U_PULSE>>1);
                UC = -(U_PULSE>>1);
                PHI_INIT = 0;
                READY = false;
            }

            /* output zero */
            else if (TIMER < T1)
            {
                UA = 0;
                UB = 0;
                UC = 0;
                PHI_INIT = 0;
                READY = false;
            }

            /*------------------------------- -PHASE B-----------------------------------------*/
            /* negative voltage pulse in phase B-direction */
            else if (TIMER < (T1 + T_PULSE))
            {
                DIR = -2;
                UA = (U_PULSE>>1);
                UB = -U_PULSE;
                UC = (U_PULSE>>1);
                PHI_INIT = 0;
                READY = false;
            }

            /* output opposite voltage pulse */
            else if (TIMER < (T1 + (2*T_PULSE)))
            {
                UA = -(U_PULSE>>1);
                UB = U_PULSE;
                UC = -(U_PULSE>>1);
                PHI_INIT = 0;
                READY = false;
            }

            /* output zero */
            else if (TIMER < T2)
            {
                UA = 0;
                UB = 0;
                UC = 0;
                PHI_INIT = 0;
                READY = false;
            }

            /*------------------------------- -PHASE C-----------------------------------------*/
            /* negative voltage pulse in phase C-direction */
            else if (TIMER < (T2 + T_PULSE))
            {
                DIR = -3;
                UA = (U_PULSE>>1);
                UB = (U_PULSE>>1);
                UC = -U_PULSE;
                PHI_INIT = 0;
                READY = false;
            }

            /* output opposite voltage pulse */
            else if (TIMER < (T2 + (2*T_PULSE)))
            {
                UA = -(U_PULSE>>1);
                UB = -(U_PULSE>>1);
                UC = U_PULSE;
                PHI_INIT = 0;
                READY = false;
            }

            /* output zero */
            else if (TIMER < T3)
            {
                UA = 0;
                UB = 0;
                UC = 0;
                PHI_INIT = 0;
                READY = false;
            }

            /*------------------------------- PHASE A -----------------------------------------*/
            /* positive voltage pulse in phase A-direction */
            else if (TIMER < (T3 + T_PULSE))
            {
                DIR = 1;
                UA = U_PULSE;
                UB = -(U_PULSE>>1);
                UC = -(U_PULSE>>1);
                PHI_INIT = 0;
                READY = false;
            }

            /* output opposite voltage pulse */
            else if (TIMER < (T3 + (2*T_PULSE)))
            {
                UA = -U_PULSE;
                UB = (U_PULSE>>1);
                UC = (U_PULSE>>1);
                PHI_INIT = 0;
                READY = false;
            }

            /* output zero */
            else if (TIMER < T4)
            {
                UA = 0;
                UB = 0;
                UC = 0;
                PHI_INIT = 0;
                READY = false;
            }

            /*------------------------------- PHASE B -----------------------------------------*/
            /* positive voltage pulse in phase B-direction */
            else if (TIMER < (T4 + T_PULSE))
            {
                DIR = 2;
                UA = -(U_PULSE>>1);
                UB = U_PULSE;
                UC = -(U_PULSE>>1);
                PHI_INIT = 0;
                READY = false;
            }
            /* output opposite voltage pulse */
            else if (TIMER < (T4 + (2*T_PULSE)))
            {
                UA = (U_PULSE>>1);
                UB = -U_PULSE;
                UC = (U_PULSE>>1);
                PHI_INIT = 0;
                READY = false;
            }
            /* output zero */
            else if (TIMER < T5)
            {
                UA = 0;
                UB = 0;
                UC = 0;
                PHI_INIT = 0;
                READY = false;
            }

            /*------------------------------- PHASE C -----------------------------------------*/
            /* positive voltage pulse in phase B-direction */
            else if (TIMER < (T5 + T_PULSE))
            {
                DIR = 3;
                UA = -(U_PULSE>>1);
                UB = -(U_PULSE>>1);
                UC = U_PULSE;
                PHI_INIT = 0;
                READY = false;
            }
            /* output opposite voltage pulse */
            else if (TIMER < (T5 + (2*T_PULSE)))
            {
                UA = (U_PULSE>>1);
                UB = (U_PULSE>>1);
                UC = -U_PULSE;
                PHI_INIT = 0;
                READY = false;
            }
            /* output zero */
            else if (TIMER < T6)
            {
                UA = 0;
                UB = 0;
                UC = 0;
                PHI_INIT = 0;
                READY = false;
            }


            /*----------------------------CALC CURRENT MAXIMA----------------------------------*/
            if (TIMER <  T6)
            {
                /* -A direction */
                if (DIR==-1)             /* neg. A direction */
                {
                    if (IA > MAX_IA_NEG)
                    {
                        MAX_IA_NEG = IA;
                    }
                }
                /* -B direction */
                else if (DIR==-2)       /* neg. B direction */
                {
                    if (IB > MAX_IB_NEG)
                    {
                        MAX_IB_NEG = IB;
                    }                    
                }
                /* -C direction */
                else if (DIR==-3)        /* neg. C direction */
                {
                    if (IC > MAX_IC_NEG)
                    {
                        MAX_IC_NEG = IC;
                    }
                }
                /* A direction */
                else if (DIR==1)       /* pos. A direction */
                {
                    if (IA > MAX_IA_POS)
                    {
                        MAX_IA_POS = IA;
                    }
                }
                /* B direction */
                else if (DIR==2)       /* pos. B direction */
                {
                    if (IB > MAX_IB_POS)
                    {
                        MAX_IB_POS = IB;
                    }
                }
                /* C direction */
                else if (DIR==3)        /* pos. C direction */
                {
                    if (IC > MAX_IC_POS)
                    {
                        MAX_IC_POS = IC;
                    }
                }

            }
            /*---------------------------CALCULATIONS--------------------------------------*/
            if (TIMER >= T6 )
            {
                /* calculate current averages */
                temp64 = (int64)MAX_IA_POS + (int64)MAX_IB_POS + (int64)MAX_IC_POS;  /* Q31 */
                I0     = (temp64 * INV_3) >> 31;
                
                temp64 = (int64)MAX_IA_NEG + (int64)MAX_IB_NEG + (int64)MAX_IC_NEG;  /* Q31 */
                I0_neg = (temp64 * INV_3) >> 31;
                
                /* subtract averages from currents = calculate current changes */
                diff_IA      = (int64)MAX_IA_POS - I0;
                diff_IB      = (int64)MAX_IB_POS - I0;
                diff_IC      = (int64)MAX_IC_POS - I0; 
                diff_IA_neg  = (int64)MAX_IA_NEG - I0_neg;
                diff_IB_neg  = (int64)MAX_IB_NEG - I0_neg;
                diff_IC_neg  = (int64)MAX_IC_NEG - I0_neg;                
                
                /* find max pos phase currents */
                if (diff_IA > diff_IB)
                {
                    if (diff_IA > diff_IC)
                    {
                        max_dI = diff_IA;
                        max_dir_pos = 1;
                    }
                    else
                    {
                        max_dI = diff_IC;
                        max_dir_pos = 5;
                    }
                }
                else
                {
                    if (diff_IB > diff_IC)
                    {
                        max_dI = diff_IB;
                        max_dir_pos = 3;
                    }
                    else
                    {
                        max_dI = diff_IC;
                        max_dir_pos = 5;
                    }
                }
                
                /* find max neg phase currents */
                if (diff_IA_neg > diff_IB_neg)
                {
                    if (diff_IA_neg > diff_IC_neg)
                    {
                        max_dI_neg = diff_IA_neg;
                        max_dir_neg = 4;
                    }
                    else
                    {
                        max_dI_neg = diff_IC_neg;
                        max_dir_neg = 2;
                    }
                }
                else
                {
                    if (diff_IB_neg > diff_IC_neg)
                    {
                        max_dI_neg = diff_IB_neg;
                        max_dir_neg = 6;
                    }
                    else
                    {
                        max_dI_neg = diff_IC_neg;
                        max_dir_neg = 2;
                    }
                }
                
                /* compare the two maxima and set final direction index */
                if (max_dI > max_dI_neg)
                {
                    max_dir = max_dir_pos;
                }
                else
                {
                    max_dir = max_dir_neg;
                }

                /* calculate x, y for  atan2 function */
                switch(max_dir) {
                    case 1: /* = maximum current change in phase A */
                        temp64 = diff_IC - diff_IB;                 /* Q31 */
                        temp64 = temp64 * (int64)KAPPA;             /* Q62 */
                        iY     = (int32)(temp64>>31);               /* Q31 */
                        iX     = (int32)(diff_IC + diff_IB);
                        phiOffset = 0;
                        break;
                        
                    case 2: /* = maximum current change in phase -C */
                        temp64 = diff_IB_neg - diff_IA_neg;         /* Q31 */
                        temp64 = temp64 * (int64)KAPPA;             /* Q62 */
                        iY     = (int32)(temp64>>31);               /* Q31 */
                        iX     = (int32)(diff_IB_neg + diff_IA_neg);
                        phiOffset = PI_DIV_3;
                        break;
                        
                    case 3: /* = maximum current change in phase B */
                        temp64 = diff_IA - diff_IC;                 /* Q31 */
                        temp64 = temp64 * (int64)KAPPA;             /* Q62 */
                        iY     = (int32)(temp64>>31);               /* Q31 */
                        iX     = (int32)(diff_IA + diff_IC);
                        phiOffset = PI_2_DIV_3;
                        break;
                        
                    case 4: /* = maximum current change in phase -A */
                        temp64 = diff_IC_neg - diff_IB_neg;         /* Q31 */
                        temp64 = temp64 * (int64)KAPPA;             /* Q62 */
                        iY     = (int32)(temp64>>31);               /* Q31 */
                        iX     = (int32)(diff_IC_neg + diff_IB_neg);
                        phiOffset = PI;
                        break;
                        
                    case 5: /* = maximum current change in phase C */
                        temp64 = diff_IB - diff_IA;                 /* Q31 */
                        temp64 = temp64 * (int64)KAPPA;             /* Q62 */
                        iY     = (int32)(temp64>>31);               /* Q31 */
                        iX     = (int32)(diff_IB + diff_IA);
                        phiOffset = -PI_2_DIV_3;
                        break;
                        
                    case 6: /* = maximum current change in phase -B */
                        temp64 = diff_IA_neg - diff_IC_neg;         /* Q31 */
                        temp64 = temp64 * (int64)KAPPA;             /* Q62 */
                        iY     = (int32)(temp64>>31);               /* Q31 */
                        iX     = (int32)(diff_IA_neg + diff_IC_neg);
                        phiOffset = -PI_DIV_3;                       
                        break;
                }               

                /*---------------------------CALC ATAN2 --------------------------------------*/
                if (iX == (int32)0x80000000)
                {
                    iX = (int32)0x80000001;
                }
                if (iY == (int32)0x80000000)
                {
                    iY = (int32)0x80000001;
                }

                if ((iY == 0) && (iX == 0))
                {
                    out1 = 0;
                }
                else
                {
                    /* Check quadrants */
                    if (iY < (int32)0)
                    {
                        iY   = -iY;
                        out1 = ATAN2_OFFSET_Q34;
                        if (iX > (int32)0)  /* 4th quadrant */
                        {
                            out1 += ATAN2_OFFSET_Q2;
                            Q13   = (int8)0;
                        }
                        else
                        {           /* 3rd quadrant */
                            iX   = -iX;
                        }
                    }
                    else
                    {
                        if (iX < (int32)0)  /* 2nd quadrant */
                        {
                            iX   = -iX;
                            out1 = ATAN2_OFFSET_Q2;
                            Q13  = (int8)0;
                        }
                    }

                    /* Check region in quadrant */
                    if (iY > iX)    /* angle > 45deg */
                    {
                        iFact = iX;         /* swap input arguments  (iFact is used as temporary variable) */
                        iX    = iY;         /* swap input arguments */
                        iY    = iFact;      /* swap input arguments */
                        iTan  = (int8)0;    /* use cotangent */
                    }

                    if (iY != iX)
                    {
                        /* Calculation of y/x */
                        arg  = (int64)iY << 32;	/* Q63,64 */
                        arg /= iX;				/* Q32,64 */

                        /* Interpolation */
                        LOOKUP32(Atan_Table32, (uint32)arg, iFact);
                    }
                    else
                    {
                        iFact = QUARTER_PI;     /* angle = 45deg */
                    }

                    /* Check for need of cotangent correction */
                    if (Q13 ^ iTan)
                    {
                        out1 += ((int32)ATAN2_OFFSET_COT - iFact);
                    }
                    else
                    {
                        out1 += iFact;
                    }
                }

                /* correct calculated angle estimate from atan2 */
                temp32 = out1 >> 1;
                if (temp32 < 0)
                {
                    /* add pi/2 */
                    PHI = temp32 + INT31_MAX;
                }
                else
                {
                    /* atan2 angle is greater or equal zero -> subtract pi/2 */                    
                    PHI = temp32 - INT31_MAX;
                }
                
                /* add offset angle */
                PHI = PHI + phiOffset;
                
                /* assign block outputs */
                UA = 0;
                UB = 0;
                UC = 0;
                PHI_INIT = PHI;
                READY = true;
            }
            
            /* increment timer */
            TIMER++;
            if (TIMER > T_END)
            {
                TIMER = T_END;
            }
        }
        /* initial rotor angle was found */
        else
        {
            UA = 0;
            UB = 0;
            UC = 0;
            PHI_INIT = PHI;
            READY   = true;
        }
    }
    /* enable == false */
    else
    {
        /* reset outputs */
        UA = 0;
        UB = 0;
        UC = 0;
        PHI_INIT = 0;
        READY = false;

        /* reset vars */
        PHI = 0;
        TIMER = 0;
        DIR = 0;
        MAX_IA_NEG = 0;
        MAX_IA_POS = 0;
        MAX_IB_NEG = 0;
        MAX_IB_POS = 0;
        MAX_IC_NEG = 0;
        MAX_IC_POS = 0;        
    }
/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void InitPosDetect_FiP32_Init(INITPOSDETECT_FIP32 *pTInitPosDetect_FiP32)
{
    pTInitPosDetect_FiP32->ID = INITPOSDETECT_FIP32_ID;
    pTInitPosDetect_FiP32->U_A = 0;
    pTInitPosDetect_FiP32->U_B = 0;
    pTInitPosDetect_FiP32->U_C = 0;
    pTInitPosDetect_FiP32->Ready = 0;
    pTInitPosDetect_FiP32->phi0 = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    PHI = 0;
    TIMER = 0;
    DIR = 0;
    MAX_IA_NEG = 0;
    MAX_IA_POS = 0;
    MAX_IB_NEG = 0;
    MAX_IB_POS = 0;
    MAX_IC_NEG = 0;
    MAX_IC_POS = 0;
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 InitPosDetect_FiP32_Load(const INITPOSDETECT_FIP32 *pTInitPosDetect_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)8 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTInitPosDetect_FiP32->u_pulse & 0x000000FF);
        data[1] = (uint8)((pTInitPosDetect_FiP32->u_pulse >> 8) & 0x000000FF);
        data[2] = (uint8)((pTInitPosDetect_FiP32->u_pulse >> 16) & 0x000000FF);
        data[3] = (uint8)((pTInitPosDetect_FiP32->u_pulse >> 24) & 0x000000FF);
        data[4] = (uint8)(pTInitPosDetect_FiP32->t_pulse & 0x00FF);
        data[5] = (uint8)((pTInitPosDetect_FiP32->t_pulse >> 8) & 0x00FF);
        data[6] = (uint8)(pTInitPosDetect_FiP32->t_period & 0x00FF);
        data[7] = (uint8)((pTInitPosDetect_FiP32->t_period >> 8) & 0x00FF);
        *dataLength = (uint16)8;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 InitPosDetect_FiP32_Save(INITPOSDETECT_FIP32 *pTInitPosDetect_FiP32, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)8)
    {
        error = (uint8)1;
    }
    else
    {
        pTInitPosDetect_FiP32->u_pulse = UINT32_TO_INT32((uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24));
        pTInitPosDetect_FiP32->t_pulse = UINT16_TO_INT16((uint16)data[4] + \
            ((uint16)data[5] << 8));
        pTInitPosDetect_FiP32->t_period = UINT16_TO_INT16((uint16)data[6] + \
            ((uint16)data[7] << 8));
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(INITPOSDETECT_FIP32_ISLINKED)
void* InitPosDetect_FiP32_GetAddress(const INITPOSDETECT_FIP32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->I_A;
            break;
        case 2:
            addr = (void*)block->I_B;
            break;
        case 3:
            addr = (void*)block->I_C;
            break;
        case 4:
            addr = (void*)block->Enable;
            break;
        case 5:
            addr = (void*)&block->U_A;
            break;
        case 6:
            addr = (void*)&block->U_B;
            break;
        case 7:
            addr = (void*)&block->U_C;
            break;
        case 8:
            addr = (void*)&block->Ready;
            break;
        case 9:
            addr = (void*)&block->phi0;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
