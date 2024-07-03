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
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "ConvFnc_HFInjectionSquare_FiP16.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#define TIME_STEPS 4
/* USERCODE-END:PreProcessor                                                                                          */

extern uint8 MaskParamBuffer[];
extern uint8 ImplParamBuffer[];
extern uint8 SaveFncDataBuffer[];

/** Implementation parameter data structure */
typedef struct {
    int16 uInjAmp;
    int16 vGain;
    int8 sfrGain;
    int32 b0_torque;
    int32 b1_torque;
    int8 sfrb0_torque;
    int8 sfrb1_torque;
    int16 b0_speed;
    int16 b1_speed;
    int8 sfrb0_speed;
    int8 sfrb1_speed;
    int16 b0_angle;
    int16 b1_angle;
    int8 sfrb0_angle;
    int8 sfrb1_angle;
    bool rawSpeed;
} HFINJECTIONSQUARE_FIP16_IMPL_PARAM;

/** estimation enumeration */
typedef enum {
    ESTIMATION_HIGH_DYNAMIC_RANGE = 0,
    ESTIMATION_LESS_NOISE = 1
} testimation;

/** method enumeration */
typedef enum {
    METHOD_ZOH = 0,
    METHOD_TUSTIN = 1
} tmethod;

/** Private prototypes */
static uint8 convertM2I(const HFINJECTIONSQUARE_FIP16_MASK_PARAM *maskParam, HFINJECTIONSQUARE_FIP16_IMPL_PARAM *impParam, float_CoT ts);

/**
 * @brief Converts Mask parameters to Implementation parameters.
 *
 * @param[in] maskParam Mask parameters
 * @param[out] impParam Implementation parameters
 * @param[in] ts Block sample time
 *
 * @return Error: zero on success, not zero in case of conversion error
 */
static uint8 convertM2I(const HFINJECTIONSQUARE_FIP16_MASK_PARAM *maskParam, HFINJECTIONSQUARE_FIP16_IMPL_PARAM *impParam, float_CoT ts)
{
    uint8 error = (uint8)0;
/* USERCODE-BEGIN:Conversion                                                                                          */
        float_CoT Kp, Ki;
        float_CoT b0 = 0, b1 = 0;
        float_CoT Ts, omegaScale, torqueScale , phi2speed , torque2speed , I2phi, V;

        /** - get mask parameter value */
        float_CoT ampHF = maskParam->U_inj;         /* amplitude of injection voltage */
        float_CoT p = maskParam->p;                 /* number of pole pairs */
        float_CoT Jp = maskParam->Jp;               /* moment of inertia */
        float_CoT Keps = maskParam->I_inj;
        float_CoT rho = 2 * (float_CoT)PI_R64 * maskParam->fo;
        float_CoT UDCmax = maskParam->U_max;        /* max DC link voltage */
        float_CoT n_max = maskParam->n_max;         /* max speed */
        float_CoT I_max = maskParam->I_max;         /* max current */


        /** - validation */
        if (p < 1)
        {
            error += 1;     /* Number of pole pairs must not be smaller than one */
        }
        if (n_max == 0)
        {
            error += 2;     /* n_max must not be zero */
        }
        if (Jp == 0)
        {
            error += 4;     /* Moment of inertia must not be zero */
        }
        if (Keps == 0)
        {
            error += 8;     /* HF current amplitude must not be zero */
        }
        if (error != 0)
        {
            return error;   /* exit conversion function */
        }

        /** - calculation of implementation parameters */
        Ts = ts * TIME_STEPS;
        omegaScale = n_max * (float_CoT)PI_R64 * p / 30; /* omega = n*pi/30*pz */
        torqueScale = omegaScale / 100; /* magic number 100: empirically obtained factor */
        phi2speed = 30 / n_max / p; /* normalization factor from angle to speed */
        torque2speed = torqueScale / omegaScale * 1 / Jp;
        I2phi = I_max / (float_CoT)PI_R64 * 1 / (2 * 8 * Keps); /* factor from error-current to error-angle (factor 8 is needed to compensate missing 1/8 in the C-code) */

        
        /******************** HF injection ********************/
        impParam->uInjAmp = getQx16Value(ampHF / UDCmax, 15);

        
        /******************** Torque (PI controller) ********************/
        /*
         * design rule for observer parameter: kp = 3*rho^2*Jp (integral-term of observer); ki = rho^3*Jp
         * (double-integral-term of observer))
         */
        Kp = I2phi * phi2speed * 3 * rho * rho / torque2speed;
        Ki = I2phi * phi2speed * rho * rho * rho / torque2speed;

        /* calculate coefficients */
        switch (maskParam->method)
        {
            case METHOD_ZOH:
                /* Zero order hold (zoh): */
                /* G(s) = Kp + Ki/s -> G(z) = Kp + Ki*Ts*1/(z-1) */
                b0 = Ki * Ts;
                b1 = Kp;
                break;
            case METHOD_TUSTIN:
                /* G(s) = Kp + Ki/s -> G(z) = ( (Ki*Ts/2+Kp)*z + Ki*Ts/2-Kp )/(z-1) */
                b0 = Ki * Ts;
                b1 = Ki * Ts / 2 + Kp;
                break;
            default:
                error += 16;
                break;           
        }
        /* b0 */
        impParam->sfrb0_torque = getQFormat(b0, 32);
        impParam->b0_torque = getQx32Value(b0, impParam->sfrb0_torque);
        /* b1 */
        impParam->sfrb1_torque = getQFormat(b1, 32);
        impParam->b1_torque = getQx32Value(b1, impParam->sfrb1_torque);
        
        
        /******************** Speed (I controller) ********************/
        Ki = torque2speed;
        Kp = 0;

        /* calculate coefficients */
        switch (maskParam->method)
        {
            case METHOD_ZOH:
                /* Zero order hold (zoh): */
                /* G(s) = Kp + Ki/s -> G(z) = Kp + Ki*Ts*1/(z-1) */
                b0 = Ki * Ts;
                b1 = Kp;
                break;
            case METHOD_TUSTIN:
                /* G(s) = Kp + Ki/s -> G(z) = ( (Ki*Ts/2+Kp)*z + Ki*Ts/2-Kp )/(z-1) */
                b0 = Ki * Ts;
                b1 = Ki * Ts / 2 + Kp;
                break;
            default:
                error += 32;
                break;           
        }
        /* b0 */
        impParam->sfrb0_speed = getQFormat(b0, 16);
        impParam->b0_speed = getQx16Value(b0, impParam->sfrb0_speed);
        /* b1 */
        impParam->sfrb1_speed = getQFormat(b1, 16);
        impParam->b1_speed = getQx16Value(b1, impParam->sfrb1_speed);

        
        /******************** Angle (uI controller) ********************/
        Ki = 2 * n_max * p / 60;
        Kp = 0;

        /* calculate coefficients */
        switch (maskParam->method)
        {
            case METHOD_ZOH:
                /* Zero order hold (zoh): */
                /* G(s) = Kp + Ki/s -> G(z) = Kp + Ki*Ts*1/(z-1) */
                b0 = Ki * Ts;
                b1 = Kp;
                break;
            case METHOD_TUSTIN:
                /* G(s) = Kp + Ki/s -> G(z) = ( (Ki*Ts/2+Kp)*z + Ki*Ts/2-Kp )/(z-1) */
                b0 = Ki * Ts;
                b1 = Ki * Ts / 2 + Kp;
                break;
            default:
                error += 64;
                break;           
        }
        /* b0 */
        impParam->sfrb0_angle = getQFormat(b0, 16);
        impParam->b0_angle = getQx16Value(b0, impParam->sfrb0_angle);
        /* b1 */
        impParam->sfrb1_angle = getQFormat(b1, 16);
        impParam->b1_angle = getQx16Value(b1, impParam->sfrb1_angle);

        
        /******************** Gain ********************/
        V = I2phi * phi2speed * 3 * rho;

        impParam->sfrGain = getQFormat(V, 16);
        impParam->vGain = getQx16Value(V, impParam->sfrGain);


        /******************** Speed estimation type ********************/
        switch (maskParam->estimation)
        {
            case ESTIMATION_HIGH_DYNAMIC_RANGE:
                impParam->rawSpeed = true;
            
                break;
            case ESTIMATION_LESS_NOISE:
                impParam->rawSpeed = false;
                break;
            default:
                error += 128;
                break;           
        }

/* USERCODE-END:Conversion                                                                                            */
    return (error);
}

/**
 * @brief Load block mask parameter data.
 *
 * @param[in] maskParam Mask parameter data structure
 * @param[out] data Data
 * @param[out] dataLen Data length
 * @param[in] maxSize Maximum Service data length
 *
 * @return Error: zero on success, not zero in case of load- or conversion error
 */
uint8 HFInjectionSquare_FiP16_LoadMP(const HFINJECTIONSQUARE_FIP16_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)74 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(maskParam->U_inj)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(maskParam->U_inj) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(maskParam->U_inj) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(maskParam->U_inj) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(maskParam->U_inj) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(maskParam->U_inj) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(maskParam->U_inj) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(maskParam->U_inj) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(maskParam->Jp)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(maskParam->Jp) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(maskParam->Jp) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(maskParam->Jp) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(maskParam->Jp) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(maskParam->Jp) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(maskParam->Jp) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(maskParam->Jp) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(maskParam->I_inj)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(maskParam->I_inj) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(maskParam->I_inj) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(maskParam->I_inj) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(maskParam->I_inj) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(maskParam->I_inj) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(maskParam->I_inj) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(maskParam->I_inj) >> 56) & 0x00000000000000FF);
        data[24] = (uint8)((*(uint64*)&(maskParam->fo)) & 0x00000000000000FF);
        data[25] = (uint8)((*(uint64*)&(maskParam->fo) >> 8) & 0x00000000000000FF);
        data[26] = (uint8)((*(uint64*)&(maskParam->fo) >> 16) & 0x00000000000000FF);
        data[27] = (uint8)((*(uint64*)&(maskParam->fo) >> 24) & 0x00000000000000FF);
        data[28] = (uint8)((*(uint64*)&(maskParam->fo) >> 32) & 0x00000000000000FF);
        data[29] = (uint8)((*(uint64*)&(maskParam->fo) >> 40) & 0x00000000000000FF);
        data[30] = (uint8)((*(uint64*)&(maskParam->fo) >> 48) & 0x00000000000000FF);
        data[31] = (uint8)((*(uint64*)&(maskParam->fo) >> 56) & 0x00000000000000FF);
        data[32] = (uint8)((*(uint64*)&(maskParam->p)) & 0x00000000000000FF);
        data[33] = (uint8)((*(uint64*)&(maskParam->p) >> 8) & 0x00000000000000FF);
        data[34] = (uint8)((*(uint64*)&(maskParam->p) >> 16) & 0x00000000000000FF);
        data[35] = (uint8)((*(uint64*)&(maskParam->p) >> 24) & 0x00000000000000FF);
        data[36] = (uint8)((*(uint64*)&(maskParam->p) >> 32) & 0x00000000000000FF);
        data[37] = (uint8)((*(uint64*)&(maskParam->p) >> 40) & 0x00000000000000FF);
        data[38] = (uint8)((*(uint64*)&(maskParam->p) >> 48) & 0x00000000000000FF);
        data[39] = (uint8)((*(uint64*)&(maskParam->p) >> 56) & 0x00000000000000FF);
        data[40] = (uint8)((*(uint64*)&(maskParam->n_max)) & 0x00000000000000FF);
        data[41] = (uint8)((*(uint64*)&(maskParam->n_max) >> 8) & 0x00000000000000FF);
        data[42] = (uint8)((*(uint64*)&(maskParam->n_max) >> 16) & 0x00000000000000FF);
        data[43] = (uint8)((*(uint64*)&(maskParam->n_max) >> 24) & 0x00000000000000FF);
        data[44] = (uint8)((*(uint64*)&(maskParam->n_max) >> 32) & 0x00000000000000FF);
        data[45] = (uint8)((*(uint64*)&(maskParam->n_max) >> 40) & 0x00000000000000FF);
        data[46] = (uint8)((*(uint64*)&(maskParam->n_max) >> 48) & 0x00000000000000FF);
        data[47] = (uint8)((*(uint64*)&(maskParam->n_max) >> 56) & 0x00000000000000FF);
        data[48] = (uint8)((*(uint64*)&(maskParam->I_max)) & 0x00000000000000FF);
        data[49] = (uint8)((*(uint64*)&(maskParam->I_max) >> 8) & 0x00000000000000FF);
        data[50] = (uint8)((*(uint64*)&(maskParam->I_max) >> 16) & 0x00000000000000FF);
        data[51] = (uint8)((*(uint64*)&(maskParam->I_max) >> 24) & 0x00000000000000FF);
        data[52] = (uint8)((*(uint64*)&(maskParam->I_max) >> 32) & 0x00000000000000FF);
        data[53] = (uint8)((*(uint64*)&(maskParam->I_max) >> 40) & 0x00000000000000FF);
        data[54] = (uint8)((*(uint64*)&(maskParam->I_max) >> 48) & 0x00000000000000FF);
        data[55] = (uint8)((*(uint64*)&(maskParam->I_max) >> 56) & 0x00000000000000FF);
        data[56] = (uint8)((*(uint64*)&(maskParam->U_max)) & 0x00000000000000FF);
        data[57] = (uint8)((*(uint64*)&(maskParam->U_max) >> 8) & 0x00000000000000FF);
        data[58] = (uint8)((*(uint64*)&(maskParam->U_max) >> 16) & 0x00000000000000FF);
        data[59] = (uint8)((*(uint64*)&(maskParam->U_max) >> 24) & 0x00000000000000FF);
        data[60] = (uint8)((*(uint64*)&(maskParam->U_max) >> 32) & 0x00000000000000FF);
        data[61] = (uint8)((*(uint64*)&(maskParam->U_max) >> 40) & 0x00000000000000FF);
        data[62] = (uint8)((*(uint64*)&(maskParam->U_max) >> 48) & 0x00000000000000FF);
        data[63] = (uint8)((*(uint64*)&(maskParam->U_max) >> 56) & 0x00000000000000FF);
        data[64] = (uint8)((*(uint64*)&(maskParam->ts_fact)) & 0x00000000000000FF);
        data[65] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 8) & 0x00000000000000FF);
        data[66] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 16) & 0x00000000000000FF);
        data[67] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 24) & 0x00000000000000FF);
        data[68] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 32) & 0x00000000000000FF);
        data[69] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 40) & 0x00000000000000FF);
        data[70] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 48) & 0x00000000000000FF);
        data[71] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 56) & 0x00000000000000FF);
        data[72] = (uint8)(maskParam->estimation);
        data[73] = (uint8)(maskParam->method);
        *dataLen = (uint16)74;
    }
    return (error);
}

/**
 * @brief Save block mask parameter data.
 *
 * @param[in] block Pointer to block structure
 * @param[out] maskParam Mask parameter data structure
 * @param[in] data Data
 * @param dataLen Length of mask parameter data stream
 *
 * @return Error: zero on success, not zero in case of save- or conversion error
 */
uint8 HFInjectionSquare_FiP16_SaveMP(HFINJECTIONSQUARE_FIP16 *block, HFINJECTIONSQUARE_FIP16_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen)
{
    uint8 error = (uint8)0;

    if (dataLen != (uint16)74)
    {
        error = (uint8)1;
    }
    else
    {
        uint64 tmp64;
        /** - Cache old mask parameters */
        HFInjectionSquare_FiP16_BackupMP(maskParam);

        /** - Save new mask parameters */
        tmp64 = (uint64)data[0] + \
            ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
            ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
            ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
            ((uint64)data[7] << 56);
        maskParam->U_inj = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        maskParam->Jp = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        maskParam->I_inj = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[24] + \
            ((uint64)data[25] << 8) + ((uint64)data[26] << 16) + \
            ((uint64)data[27] << 24) + ((uint64)data[28] << 32) + \
            ((uint64)data[29] << 40) + ((uint64)data[30] << 48) + \
            ((uint64)data[31] << 56);
        maskParam->fo = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[32] + \
            ((uint64)data[33] << 8) + ((uint64)data[34] << 16) + \
            ((uint64)data[35] << 24) + ((uint64)data[36] << 32) + \
            ((uint64)data[37] << 40) + ((uint64)data[38] << 48) + \
            ((uint64)data[39] << 56);
        maskParam->p = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[40] + \
            ((uint64)data[41] << 8) + ((uint64)data[42] << 16) + \
            ((uint64)data[43] << 24) + ((uint64)data[44] << 32) + \
            ((uint64)data[45] << 40) + ((uint64)data[46] << 48) + \
            ((uint64)data[47] << 56);
        maskParam->n_max = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[48] + \
            ((uint64)data[49] << 8) + ((uint64)data[50] << 16) + \
            ((uint64)data[51] << 24) + ((uint64)data[52] << 32) + \
            ((uint64)data[53] << 40) + ((uint64)data[54] << 48) + \
            ((uint64)data[55] << 56);
        maskParam->I_max = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[56] + \
            ((uint64)data[57] << 8) + ((uint64)data[58] << 16) + \
            ((uint64)data[59] << 24) + ((uint64)data[60] << 32) + \
            ((uint64)data[61] << 40) + ((uint64)data[62] << 48) + \
            ((uint64)data[63] << 56);
        maskParam->U_max = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[64] + \
            ((uint64)data[65] << 8) + ((uint64)data[66] << 16) + \
            ((uint64)data[67] << 24) + ((uint64)data[68] << 32) + \
            ((uint64)data[69] << 40) + ((uint64)data[70] << 48) + \
            ((uint64)data[71] << 56);
        maskParam->ts_fact = (float64)(*(float64*)&tmp64);
        maskParam->estimation = data[72];
        maskParam->method = data[73];

        error = HFInjectionSquare_FiP16_ConvertMP(block, maskParam);

        /** - Check for errors during execution of save function */
        if (error != 0)
        {
            /* Restore old mask parameter */
            HFInjectionSquare_FiP16_RestoreMP(maskParam);
        }

    }
    return (error);
}

/**
 * @brief Initializes Implementation parameters from Mask parameters.
 *
 * @param[out] block Block
 * @param[in] maskParam Mask parameters
 *
 * @return Error: zero on success, not zero in case of initialization error
 */
uint8 HFInjectionSquare_FiP16_InitMP(HFINJECTIONSQUARE_FIP16 *block, const HFINJECTIONSQUARE_FIP16_MASK_PARAM *maskParam)
{
    uint8 error = (uint8)0;
    float_CoT block_ts;

    HFINJECTIONSQUARE_FIP16_IMPL_PARAM *implParam = (HFINJECTIONSQUARE_FIP16_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)(implParam->uInjAmp & 0x00FF);
    SaveFncDataBuffer[1] = (uint8)((implParam->uInjAmp >> 8) & 0x00FF);
    SaveFncDataBuffer[2] = (uint8)(implParam->vGain & 0x00FF);
    SaveFncDataBuffer[3] = (uint8)((implParam->vGain >> 8) & 0x00FF);
    SaveFncDataBuffer[4] = (uint8)implParam->sfrGain;
    SaveFncDataBuffer[5] = (uint8)(implParam->b0_torque & 0x000000FF);
    SaveFncDataBuffer[6] = (uint8)((implParam->b0_torque >> 8) & 0x000000FF);
    SaveFncDataBuffer[7] = (uint8)((implParam->b0_torque >> 16) & 0x000000FF);
    SaveFncDataBuffer[8] = (uint8)((implParam->b0_torque >> 24) & 0x000000FF);
    SaveFncDataBuffer[9] = (uint8)(implParam->b1_torque & 0x000000FF);
    SaveFncDataBuffer[10] = (uint8)((implParam->b1_torque >> 8) & 0x000000FF);
    SaveFncDataBuffer[11] = (uint8)((implParam->b1_torque >> 16) & 0x000000FF);
    SaveFncDataBuffer[12] = (uint8)((implParam->b1_torque >> 24) & 0x000000FF);
    SaveFncDataBuffer[13] = (uint8)implParam->sfrb0_torque;
    SaveFncDataBuffer[14] = (uint8)implParam->sfrb1_torque;
    SaveFncDataBuffer[15] = (uint8)(implParam->b0_speed & 0x00FF);
    SaveFncDataBuffer[16] = (uint8)((implParam->b0_speed >> 8) & 0x00FF);
    SaveFncDataBuffer[17] = (uint8)(implParam->b1_speed & 0x00FF);
    SaveFncDataBuffer[18] = (uint8)((implParam->b1_speed >> 8) & 0x00FF);
    SaveFncDataBuffer[19] = (uint8)implParam->sfrb0_speed;
    SaveFncDataBuffer[20] = (uint8)implParam->sfrb1_speed;
    SaveFncDataBuffer[21] = (uint8)(implParam->b0_angle & 0x00FF);
    SaveFncDataBuffer[22] = (uint8)((implParam->b0_angle >> 8) & 0x00FF);
    SaveFncDataBuffer[23] = (uint8)(implParam->b1_angle & 0x00FF);
    SaveFncDataBuffer[24] = (uint8)((implParam->b1_angle >> 8) & 0x00FF);
    SaveFncDataBuffer[25] = (uint8)implParam->sfrb0_angle;
    SaveFncDataBuffer[26] = (uint8)implParam->sfrb1_angle;
    SaveFncDataBuffer[27] = (uint8)implParam->rawSpeed;

    /** - Execute save function of block */
    error = HFInjectionSquare_FiP16_Save(block, SaveFncDataBuffer, 28);

    return (error);
}

/**
 * @brief Converts Mask parameters into Implementation parameters and executes Block Save function.
 *
 * @param[out] block Block Implementation
 * @param[in] maskParam Mask Parameters
 *
 * @return 0 if successful, greater than 0 if conversion failed
 */
uint8 HFInjectionSquare_FiP16_ConvertMP(HFINJECTIONSQUARE_FIP16 *block, HFINJECTIONSQUARE_FIP16_MASK_PARAM *maskParam)
{
    uint8 error;
    float_CoT block_ts;
    HFINJECTIONSQUARE_FIP16_IMPL_PARAM *implParam = (HFINJECTIONSQUARE_FIP16_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);
    if (error)
    {
        return (error);
    }

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)(implParam->uInjAmp & 0x00FF);
    SaveFncDataBuffer[1] = (uint8)((implParam->uInjAmp >> 8) & 0x00FF);
    SaveFncDataBuffer[2] = (uint8)(implParam->vGain & 0x00FF);
    SaveFncDataBuffer[3] = (uint8)((implParam->vGain >> 8) & 0x00FF);
    SaveFncDataBuffer[4] = (uint8)implParam->sfrGain;
    SaveFncDataBuffer[5] = (uint8)(implParam->b0_torque & 0x000000FF);
    SaveFncDataBuffer[6] = (uint8)((implParam->b0_torque >> 8) & 0x000000FF);
    SaveFncDataBuffer[7] = (uint8)((implParam->b0_torque >> 16) & 0x000000FF);
    SaveFncDataBuffer[8] = (uint8)((implParam->b0_torque >> 24) & 0x000000FF);
    SaveFncDataBuffer[9] = (uint8)(implParam->b1_torque & 0x000000FF);
    SaveFncDataBuffer[10] = (uint8)((implParam->b1_torque >> 8) & 0x000000FF);
    SaveFncDataBuffer[11] = (uint8)((implParam->b1_torque >> 16) & 0x000000FF);
    SaveFncDataBuffer[12] = (uint8)((implParam->b1_torque >> 24) & 0x000000FF);
    SaveFncDataBuffer[13] = (uint8)implParam->sfrb0_torque;
    SaveFncDataBuffer[14] = (uint8)implParam->sfrb1_torque;
    SaveFncDataBuffer[15] = (uint8)(implParam->b0_speed & 0x00FF);
    SaveFncDataBuffer[16] = (uint8)((implParam->b0_speed >> 8) & 0x00FF);
    SaveFncDataBuffer[17] = (uint8)(implParam->b1_speed & 0x00FF);
    SaveFncDataBuffer[18] = (uint8)((implParam->b1_speed >> 8) & 0x00FF);
    SaveFncDataBuffer[19] = (uint8)implParam->sfrb0_speed;
    SaveFncDataBuffer[20] = (uint8)implParam->sfrb1_speed;
    SaveFncDataBuffer[21] = (uint8)(implParam->b0_angle & 0x00FF);
    SaveFncDataBuffer[22] = (uint8)((implParam->b0_angle >> 8) & 0x00FF);
    SaveFncDataBuffer[23] = (uint8)(implParam->b1_angle & 0x00FF);
    SaveFncDataBuffer[24] = (uint8)((implParam->b1_angle >> 8) & 0x00FF);
    SaveFncDataBuffer[25] = (uint8)implParam->sfrb0_angle;
    SaveFncDataBuffer[26] = (uint8)implParam->sfrb1_angle;
    SaveFncDataBuffer[27] = (uint8)implParam->rawSpeed;

    /** - Execute save function of block */
    error = HFInjectionSquare_FiP16_Save(block, SaveFncDataBuffer, 28);

    return (error);
}

/**
 * @brief Backups current Mask parameters into global Mask parameter backup array.
 *
 * @param[in] maskParam Mask parameters
 *
 * @return Nothing
 */
void HFInjectionSquare_FiP16_BackupMP(HFINJECTIONSQUARE_FIP16_MASK_PARAM* maskParam)
{
    memcpy(MaskParamBuffer, maskParam, sizeof(*maskParam));
}

/**
 * @brief Restores Mask parameters from global Mask parameter backup array.
 *
 * @param[out] maskParam Mask parameters
 *
 * @return Nothing
 */
void HFInjectionSquare_FiP16_RestoreMP(HFINJECTIONSQUARE_FIP16_MASK_PARAM* maskParam)
{
    memcpy(maskParam, MaskParamBuffer, sizeof(*maskParam));
}
