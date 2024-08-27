/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1603 $
 * $LastChangedDate:: 2019-01-21 19:02:13 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "ConvFnc_TrackingLoop_FiP16.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* USERCODE-END:PreProcessor                                                                                          */

extern uint8 MaskParamBuffer[];
extern uint8 ImplParamBuffer[];
extern uint8 SaveFncDataBuffer[];

/** Implementation parameter data structure */
typedef struct {
    int16 vGain;
    int8 sfrGain;
    int32 b0_torque;
    int32 b1_torque;
    int8 sfrb0_torque;
    int8 sfrb1_torque;
    int32 b0_speed;
    int32 b1_speed;
    int8 sfrb0_speed;
    int8 sfrb1_speed;
    int16 b0_angle;
    int16 b1_angle;
    int8 sfrb0_angle;
    int8 sfrb1_angle;
    bool rawSpeed;
} TRACKINGLOOP_FIP16_IMPL_PARAM;

/** estimation enumeration */
typedef enum {
    ESTIMATION_HIGH_DYNAMICS = 0,
    ESTIMATION_LESS_NOISE = 1
} testimation;

/** method enumeration */
typedef enum {
    METHOD_ZOH = 0,
    METHOD_TUSTIN = 1
} tmethod;

/** Private prototypes */
static uint8 convertM2I(const TRACKINGLOOP_FIP16_MASK_PARAM *maskParam, TRACKINGLOOP_FIP16_IMPL_PARAM *impParam, float_CoT ts);

/**
 * @brief Converts Mask parameters to Implementation parameters.
 *
 * @param[in] maskParam Mask parameters
 * @param[out] impParam Implementation parameters
 * @param[in] ts Block sample time
 *
 * @return Error: zero on success, not zero in case of conversion error
 */
static uint8 convertM2I(const TRACKINGLOOP_FIP16_MASK_PARAM *maskParam, TRACKINGLOOP_FIP16_IMPL_PARAM *impParam, float_CoT ts)
{
    uint8 error = (uint8)0;
/* USERCODE-BEGIN:Conversion                                                                                          */
#error CONVERSION-ON-TARGET CURRENTLY NOT SUPPORTED / MASK-TO-IMPLEMENTATION CONVERSION MISSING
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
uint8 TrackingLoop_FiP16_LoadMP(const TRACKINGLOOP_FIP16_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)42 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(maskParam->Jp)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(maskParam->Jp) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(maskParam->Jp) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(maskParam->Jp) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(maskParam->Jp) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(maskParam->Jp) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(maskParam->Jp) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(maskParam->Jp) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(maskParam->fo)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(maskParam->fo) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(maskParam->fo) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(maskParam->fo) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(maskParam->fo) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(maskParam->fo) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(maskParam->fo) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(maskParam->fo) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(maskParam->p)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(maskParam->p) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(maskParam->p) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(maskParam->p) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(maskParam->p) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(maskParam->p) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(maskParam->p) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(maskParam->p) >> 56) & 0x00000000000000FF);
        data[24] = (uint8)(maskParam->estimation);
        data[25] = (uint8)(maskParam->method);
        data[26] = (uint8)((*(uint64*)&(maskParam->n_max)) & 0x00000000000000FF);
        data[27] = (uint8)((*(uint64*)&(maskParam->n_max) >> 8) & 0x00000000000000FF);
        data[28] = (uint8)((*(uint64*)&(maskParam->n_max) >> 16) & 0x00000000000000FF);
        data[29] = (uint8)((*(uint64*)&(maskParam->n_max) >> 24) & 0x00000000000000FF);
        data[30] = (uint8)((*(uint64*)&(maskParam->n_max) >> 32) & 0x00000000000000FF);
        data[31] = (uint8)((*(uint64*)&(maskParam->n_max) >> 40) & 0x00000000000000FF);
        data[32] = (uint8)((*(uint64*)&(maskParam->n_max) >> 48) & 0x00000000000000FF);
        data[33] = (uint8)((*(uint64*)&(maskParam->n_max) >> 56) & 0x00000000000000FF);
        data[34] = (uint8)((*(uint64*)&(maskParam->ts_fact)) & 0x00000000000000FF);
        data[35] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 8) & 0x00000000000000FF);
        data[36] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 16) & 0x00000000000000FF);
        data[37] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 24) & 0x00000000000000FF);
        data[38] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 32) & 0x00000000000000FF);
        data[39] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 40) & 0x00000000000000FF);
        data[40] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 48) & 0x00000000000000FF);
        data[41] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 56) & 0x00000000000000FF);
        *dataLen = (uint16)42;
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
uint8 TrackingLoop_FiP16_SaveMP(TRACKINGLOOP_FIP16 *block, TRACKINGLOOP_FIP16_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen)
{
    uint8 error = (uint8)0;

    if (dataLen != (uint16)42)
    {
        error = (uint8)1;
    }
    else
    {
        uint64 tmp64;
        /** - Cache old mask parameters */
        TrackingLoop_FiP16_BackupMP(maskParam);

        /** - Save new mask parameters */
        tmp64 = (uint64)data[0] + \
            ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
            ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
            ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
            ((uint64)data[7] << 56);
        maskParam->Jp = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        maskParam->fo = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        maskParam->p = (float64)(*(float64*)&tmp64);
        maskParam->estimation = data[24];
        maskParam->method = data[25];
        tmp64 = (uint64)data[26] + \
            ((uint64)data[27] << 8) + ((uint64)data[28] << 16) + \
            ((uint64)data[29] << 24) + ((uint64)data[30] << 32) + \
            ((uint64)data[31] << 40) + ((uint64)data[32] << 48) + \
            ((uint64)data[33] << 56);
        maskParam->n_max = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[34] + \
            ((uint64)data[35] << 8) + ((uint64)data[36] << 16) + \
            ((uint64)data[37] << 24) + ((uint64)data[38] << 32) + \
            ((uint64)data[39] << 40) + ((uint64)data[40] << 48) + \
            ((uint64)data[41] << 56);
        maskParam->ts_fact = (float64)(*(float64*)&tmp64);

        error = TrackingLoop_FiP16_ConvertMP(block, maskParam);

        /** - Check for errors during execution of save function */
        if (error != 0)
        {
            /* Restore old mask parameter */
            TrackingLoop_FiP16_RestoreMP(maskParam);
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
uint8 TrackingLoop_FiP16_InitMP(TRACKINGLOOP_FIP16 *block, const TRACKINGLOOP_FIP16_MASK_PARAM *maskParam)
{
    uint8 error = (uint8)0;
    float_CoT block_ts;

    TRACKINGLOOP_FIP16_IMPL_PARAM *implParam = (TRACKINGLOOP_FIP16_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)(implParam->vGain & 0x00FF);
    SaveFncDataBuffer[1] = (uint8)((implParam->vGain >> 8) & 0x00FF);
    SaveFncDataBuffer[2] = (uint8)implParam->sfrGain;
    SaveFncDataBuffer[3] = (uint8)(implParam->b0_torque & 0x000000FF);
    SaveFncDataBuffer[4] = (uint8)((implParam->b0_torque >> 8) & 0x000000FF);
    SaveFncDataBuffer[5] = (uint8)((implParam->b0_torque >> 16) & 0x000000FF);
    SaveFncDataBuffer[6] = (uint8)((implParam->b0_torque >> 24) & 0x000000FF);
    SaveFncDataBuffer[7] = (uint8)(implParam->b1_torque & 0x000000FF);
    SaveFncDataBuffer[8] = (uint8)((implParam->b1_torque >> 8) & 0x000000FF);
    SaveFncDataBuffer[9] = (uint8)((implParam->b1_torque >> 16) & 0x000000FF);
    SaveFncDataBuffer[10] = (uint8)((implParam->b1_torque >> 24) & 0x000000FF);
    SaveFncDataBuffer[11] = (uint8)implParam->sfrb0_torque;
    SaveFncDataBuffer[12] = (uint8)implParam->sfrb1_torque;
    SaveFncDataBuffer[13] = (uint8)(implParam->b0_speed & 0x000000FF);
    SaveFncDataBuffer[14] = (uint8)((implParam->b0_speed >> 8) & 0x000000FF);
    SaveFncDataBuffer[15] = (uint8)((implParam->b0_speed >> 16) & 0x000000FF);
    SaveFncDataBuffer[16] = (uint8)((implParam->b0_speed >> 24) & 0x000000FF);
    SaveFncDataBuffer[17] = (uint8)(implParam->b1_speed & 0x000000FF);
    SaveFncDataBuffer[18] = (uint8)((implParam->b1_speed >> 8) & 0x000000FF);
    SaveFncDataBuffer[19] = (uint8)((implParam->b1_speed >> 16) & 0x000000FF);
    SaveFncDataBuffer[20] = (uint8)((implParam->b1_speed >> 24) & 0x000000FF);
    SaveFncDataBuffer[21] = (uint8)implParam->sfrb0_speed;
    SaveFncDataBuffer[22] = (uint8)implParam->sfrb1_speed;
    SaveFncDataBuffer[23] = (uint8)(implParam->b0_angle & 0x00FF);
    SaveFncDataBuffer[24] = (uint8)((implParam->b0_angle >> 8) & 0x00FF);
    SaveFncDataBuffer[25] = (uint8)(implParam->b1_angle & 0x00FF);
    SaveFncDataBuffer[26] = (uint8)((implParam->b1_angle >> 8) & 0x00FF);
    SaveFncDataBuffer[27] = (uint8)implParam->sfrb0_angle;
    SaveFncDataBuffer[28] = (uint8)implParam->sfrb1_angle;
    SaveFncDataBuffer[29] = (uint8)implParam->rawSpeed;

    /** - Execute save function of block */
    error = TrackingLoop_FiP16_Save(block, SaveFncDataBuffer, 30);

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
uint8 TrackingLoop_FiP16_ConvertMP(TRACKINGLOOP_FIP16 *block, TRACKINGLOOP_FIP16_MASK_PARAM *maskParam)
{
    uint8 error;
    float_CoT block_ts;
    TRACKINGLOOP_FIP16_IMPL_PARAM *implParam = (TRACKINGLOOP_FIP16_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);
    if (error)
    {
        return (error);
    }

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)(implParam->vGain & 0x00FF);
    SaveFncDataBuffer[1] = (uint8)((implParam->vGain >> 8) & 0x00FF);
    SaveFncDataBuffer[2] = (uint8)implParam->sfrGain;
    SaveFncDataBuffer[3] = (uint8)(implParam->b0_torque & 0x000000FF);
    SaveFncDataBuffer[4] = (uint8)((implParam->b0_torque >> 8) & 0x000000FF);
    SaveFncDataBuffer[5] = (uint8)((implParam->b0_torque >> 16) & 0x000000FF);
    SaveFncDataBuffer[6] = (uint8)((implParam->b0_torque >> 24) & 0x000000FF);
    SaveFncDataBuffer[7] = (uint8)(implParam->b1_torque & 0x000000FF);
    SaveFncDataBuffer[8] = (uint8)((implParam->b1_torque >> 8) & 0x000000FF);
    SaveFncDataBuffer[9] = (uint8)((implParam->b1_torque >> 16) & 0x000000FF);
    SaveFncDataBuffer[10] = (uint8)((implParam->b1_torque >> 24) & 0x000000FF);
    SaveFncDataBuffer[11] = (uint8)implParam->sfrb0_torque;
    SaveFncDataBuffer[12] = (uint8)implParam->sfrb1_torque;
    SaveFncDataBuffer[13] = (uint8)(implParam->b0_speed & 0x000000FF);
    SaveFncDataBuffer[14] = (uint8)((implParam->b0_speed >> 8) & 0x000000FF);
    SaveFncDataBuffer[15] = (uint8)((implParam->b0_speed >> 16) & 0x000000FF);
    SaveFncDataBuffer[16] = (uint8)((implParam->b0_speed >> 24) & 0x000000FF);
    SaveFncDataBuffer[17] = (uint8)(implParam->b1_speed & 0x000000FF);
    SaveFncDataBuffer[18] = (uint8)((implParam->b1_speed >> 8) & 0x000000FF);
    SaveFncDataBuffer[19] = (uint8)((implParam->b1_speed >> 16) & 0x000000FF);
    SaveFncDataBuffer[20] = (uint8)((implParam->b1_speed >> 24) & 0x000000FF);
    SaveFncDataBuffer[21] = (uint8)implParam->sfrb0_speed;
    SaveFncDataBuffer[22] = (uint8)implParam->sfrb1_speed;
    SaveFncDataBuffer[23] = (uint8)(implParam->b0_angle & 0x00FF);
    SaveFncDataBuffer[24] = (uint8)((implParam->b0_angle >> 8) & 0x00FF);
    SaveFncDataBuffer[25] = (uint8)(implParam->b1_angle & 0x00FF);
    SaveFncDataBuffer[26] = (uint8)((implParam->b1_angle >> 8) & 0x00FF);
    SaveFncDataBuffer[27] = (uint8)implParam->sfrb0_angle;
    SaveFncDataBuffer[28] = (uint8)implParam->sfrb1_angle;
    SaveFncDataBuffer[29] = (uint8)implParam->rawSpeed;

    /** - Execute save function of block */
    error = TrackingLoop_FiP16_Save(block, SaveFncDataBuffer, 30);

    return (error);
}

/**
 * @brief Backups current Mask parameters into global Mask parameter backup array.
 *
 * @param[in] maskParam Mask parameters
 *
 * @return Nothing
 */
void TrackingLoop_FiP16_BackupMP(TRACKINGLOOP_FIP16_MASK_PARAM* maskParam)
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
void TrackingLoop_FiP16_RestoreMP(TRACKINGLOOP_FIP16_MASK_PARAM* maskParam)
{
    memcpy(maskParam, MaskParamBuffer, sizeof(*maskParam));
}
