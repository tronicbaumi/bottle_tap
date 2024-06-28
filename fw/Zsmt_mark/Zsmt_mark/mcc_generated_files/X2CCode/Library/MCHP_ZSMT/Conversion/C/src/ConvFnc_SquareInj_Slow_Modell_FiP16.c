/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "ConvFnc_SquareInj_Slow_Modell_FiP16.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* USERCODE-END:PreProcessor                                                                                          */

extern uint8 MaskParamBuffer[];
extern uint8 ImplParamBuffer[];
extern uint8 SaveFncDataBuffer[];

/** Implementation parameter data structure */
typedef struct {
    int32 b0;
    int32 b1;
    int8 sfrb0;
    int8 sfrb1;
    int16 a0_PT1;
    int16 b0_PT1;
    int16 b1_PT1;
    int16 sfra_PT1;
    int16 sfrb_PT1;
    int16 dphiOld;
    int16 b0_uI;
    int16 sfr_uI;
    int32 i_old_uI;
    int16 b0_I;
    int16 sfr_I;
    int32 i_old_I;
    int8 rawSpeed;
    int16 vGain;
    int16 sfrGain;
    int16 b1_I;
    int16 b1_uI;
    int16 sfrb1_I;
    int16 sfrb1_uI;
} SQUAREINJ_SLOW_MODELL_FIP16_IMPL_PARAM;

/** method enumeration */
typedef enum {
    METHOD_ZOH = 0,
    METHOD_TUSTIN = 1
} tmethod;

/** selSpeedProp enumeration */
typedef enum {
    SELSPEEDPROP_HIGHMDYNAMICMRANGE = 0,
    SELSPEEDPROP_LESSMNOISE = 1
} tselSpeedProp;

/** Private prototypes */
static uint8 convertM2I(const SQUAREINJ_SLOW_MODELL_FIP16_MASK_PARAM *maskParam, SQUAREINJ_SLOW_MODELL_FIP16_IMPL_PARAM *impParam, float_CoT ts);

/**
 * @brief Converts Mask parameters to Implementation parameters.
 *
 * @param[in] maskParam Mask parameters
 * @param[out] impParam Implementation parameters
 * @param[in] ts Block sample time
 *
 * @return Error: zero on success, not zero in case of conversion error
 */
static uint8 convertM2I(const SQUAREINJ_SLOW_MODELL_FIP16_MASK_PARAM *maskParam, SQUAREINJ_SLOW_MODELL_FIP16_IMPL_PARAM *impParam, float_CoT ts)
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
uint8 SquareInj_Slow_Modell_FiP16_LoadMP(const SQUAREINJ_SLOW_MODELL_FIP16_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)58 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(maskParam->n_max)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(maskParam->n_max) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(maskParam->n_max) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(maskParam->n_max) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(maskParam->n_max) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(maskParam->n_max) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(maskParam->n_max) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(maskParam->n_max) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(maskParam->p)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(maskParam->p) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(maskParam->p) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(maskParam->p) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(maskParam->p) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(maskParam->p) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(maskParam->p) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(maskParam->p) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(maskParam->ts_fact)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 56) & 0x00000000000000FF);
        data[24] = (uint8)((*(uint64*)&(maskParam->I_max)) & 0x00000000000000FF);
        data[25] = (uint8)((*(uint64*)&(maskParam->I_max) >> 8) & 0x00000000000000FF);
        data[26] = (uint8)((*(uint64*)&(maskParam->I_max) >> 16) & 0x00000000000000FF);
        data[27] = (uint8)((*(uint64*)&(maskParam->I_max) >> 24) & 0x00000000000000FF);
        data[28] = (uint8)((*(uint64*)&(maskParam->I_max) >> 32) & 0x00000000000000FF);
        data[29] = (uint8)((*(uint64*)&(maskParam->I_max) >> 40) & 0x00000000000000FF);
        data[30] = (uint8)((*(uint64*)&(maskParam->I_max) >> 48) & 0x00000000000000FF);
        data[31] = (uint8)((*(uint64*)&(maskParam->I_max) >> 56) & 0x00000000000000FF);
        data[32] = (uint8)((*(uint64*)&(maskParam->Jp)) & 0x00000000000000FF);
        data[33] = (uint8)((*(uint64*)&(maskParam->Jp) >> 8) & 0x00000000000000FF);
        data[34] = (uint8)((*(uint64*)&(maskParam->Jp) >> 16) & 0x00000000000000FF);
        data[35] = (uint8)((*(uint64*)&(maskParam->Jp) >> 24) & 0x00000000000000FF);
        data[36] = (uint8)((*(uint64*)&(maskParam->Jp) >> 32) & 0x00000000000000FF);
        data[37] = (uint8)((*(uint64*)&(maskParam->Jp) >> 40) & 0x00000000000000FF);
        data[38] = (uint8)((*(uint64*)&(maskParam->Jp) >> 48) & 0x00000000000000FF);
        data[39] = (uint8)((*(uint64*)&(maskParam->Jp) >> 56) & 0x00000000000000FF);
        data[40] = (uint8)((*(uint64*)&(maskParam->Keps)) & 0x00000000000000FF);
        data[41] = (uint8)((*(uint64*)&(maskParam->Keps) >> 8) & 0x00000000000000FF);
        data[42] = (uint8)((*(uint64*)&(maskParam->Keps) >> 16) & 0x00000000000000FF);
        data[43] = (uint8)((*(uint64*)&(maskParam->Keps) >> 24) & 0x00000000000000FF);
        data[44] = (uint8)((*(uint64*)&(maskParam->Keps) >> 32) & 0x00000000000000FF);
        data[45] = (uint8)((*(uint64*)&(maskParam->Keps) >> 40) & 0x00000000000000FF);
        data[46] = (uint8)((*(uint64*)&(maskParam->Keps) >> 48) & 0x00000000000000FF);
        data[47] = (uint8)((*(uint64*)&(maskParam->Keps) >> 56) & 0x00000000000000FF);
        data[48] = (uint8)((*(uint64*)&(maskParam->rho)) & 0x00000000000000FF);
        data[49] = (uint8)((*(uint64*)&(maskParam->rho) >> 8) & 0x00000000000000FF);
        data[50] = (uint8)((*(uint64*)&(maskParam->rho) >> 16) & 0x00000000000000FF);
        data[51] = (uint8)((*(uint64*)&(maskParam->rho) >> 24) & 0x00000000000000FF);
        data[52] = (uint8)((*(uint64*)&(maskParam->rho) >> 32) & 0x00000000000000FF);
        data[53] = (uint8)((*(uint64*)&(maskParam->rho) >> 40) & 0x00000000000000FF);
        data[54] = (uint8)((*(uint64*)&(maskParam->rho) >> 48) & 0x00000000000000FF);
        data[55] = (uint8)((*(uint64*)&(maskParam->rho) >> 56) & 0x00000000000000FF);
        data[56] = (uint8)(maskParam->method);
        data[57] = (uint8)(maskParam->selSpeedProp);
        *dataLen = (uint16)58;
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
uint8 SquareInj_Slow_Modell_FiP16_SaveMP(SQUAREINJ_SLOW_MODELL_FIP16 *block, SQUAREINJ_SLOW_MODELL_FIP16_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen)
{
    uint8 error = (uint8)0;

    if (dataLen != (uint16)58)
    {
        error = (uint8)1;
    }
    else
    {
        uint64 tmp64;
        /** - Cache old mask parameters */
        SquareInj_Slow_Modell_FiP16_BackupMP(maskParam);

        /** - Save new mask parameters */
        tmp64 = (uint64)data[0] + \
            ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
            ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
            ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
            ((uint64)data[7] << 56);
        maskParam->n_max = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        maskParam->p = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        maskParam->ts_fact = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[24] + \
            ((uint64)data[25] << 8) + ((uint64)data[26] << 16) + \
            ((uint64)data[27] << 24) + ((uint64)data[28] << 32) + \
            ((uint64)data[29] << 40) + ((uint64)data[30] << 48) + \
            ((uint64)data[31] << 56);
        maskParam->I_max = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[32] + \
            ((uint64)data[33] << 8) + ((uint64)data[34] << 16) + \
            ((uint64)data[35] << 24) + ((uint64)data[36] << 32) + \
            ((uint64)data[37] << 40) + ((uint64)data[38] << 48) + \
            ((uint64)data[39] << 56);
        maskParam->Jp = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[40] + \
            ((uint64)data[41] << 8) + ((uint64)data[42] << 16) + \
            ((uint64)data[43] << 24) + ((uint64)data[44] << 32) + \
            ((uint64)data[45] << 40) + ((uint64)data[46] << 48) + \
            ((uint64)data[47] << 56);
        maskParam->Keps = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[48] + \
            ((uint64)data[49] << 8) + ((uint64)data[50] << 16) + \
            ((uint64)data[51] << 24) + ((uint64)data[52] << 32) + \
            ((uint64)data[53] << 40) + ((uint64)data[54] << 48) + \
            ((uint64)data[55] << 56);
        maskParam->rho = (float64)(*(float64*)&tmp64);
        maskParam->method = data[56];
        maskParam->selSpeedProp = data[57];

        error = SquareInj_Slow_Modell_FiP16_ConvertMP(block, maskParam);

        /** - Check for errors during execution of save function */
        if (error != 0)
        {
            /* Restore old mask parameter */
            SquareInj_Slow_Modell_FiP16_RestoreMP(maskParam);
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
uint8 SquareInj_Slow_Modell_FiP16_InitMP(SQUAREINJ_SLOW_MODELL_FIP16 *block, const SQUAREINJ_SLOW_MODELL_FIP16_MASK_PARAM *maskParam)
{
    uint8 error = (uint8)0;
    float_CoT block_ts;

    SQUAREINJ_SLOW_MODELL_FIP16_IMPL_PARAM *implParam = (SQUAREINJ_SLOW_MODELL_FIP16_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)(implParam->b0 & 0x000000FF);
    SaveFncDataBuffer[1] = (uint8)((implParam->b0 >> 8) & 0x000000FF);
    SaveFncDataBuffer[2] = (uint8)((implParam->b0 >> 16) & 0x000000FF);
    SaveFncDataBuffer[3] = (uint8)((implParam->b0 >> 24) & 0x000000FF);
    SaveFncDataBuffer[4] = (uint8)(implParam->b1 & 0x000000FF);
    SaveFncDataBuffer[5] = (uint8)((implParam->b1 >> 8) & 0x000000FF);
    SaveFncDataBuffer[6] = (uint8)((implParam->b1 >> 16) & 0x000000FF);
    SaveFncDataBuffer[7] = (uint8)((implParam->b1 >> 24) & 0x000000FF);
    SaveFncDataBuffer[8] = (uint8)implParam->sfrb0;
    SaveFncDataBuffer[9] = (uint8)implParam->sfrb1;
    SaveFncDataBuffer[10] = (uint8)(implParam->a0_PT1 & 0x00FF);
    SaveFncDataBuffer[11] = (uint8)((implParam->a0_PT1 >> 8) & 0x00FF);
    SaveFncDataBuffer[12] = (uint8)(implParam->b0_PT1 & 0x00FF);
    SaveFncDataBuffer[13] = (uint8)((implParam->b0_PT1 >> 8) & 0x00FF);
    SaveFncDataBuffer[14] = (uint8)(implParam->b1_PT1 & 0x00FF);
    SaveFncDataBuffer[15] = (uint8)((implParam->b1_PT1 >> 8) & 0x00FF);
    SaveFncDataBuffer[16] = (uint8)(implParam->sfra_PT1 & 0x00FF);
    SaveFncDataBuffer[17] = (uint8)((implParam->sfra_PT1 >> 8) & 0x00FF);
    SaveFncDataBuffer[18] = (uint8)(implParam->sfrb_PT1 & 0x00FF);
    SaveFncDataBuffer[19] = (uint8)((implParam->sfrb_PT1 >> 8) & 0x00FF);
    SaveFncDataBuffer[20] = (uint8)(implParam->dphiOld & 0x00FF);
    SaveFncDataBuffer[21] = (uint8)((implParam->dphiOld >> 8) & 0x00FF);
    SaveFncDataBuffer[22] = (uint8)(implParam->b0_uI & 0x00FF);
    SaveFncDataBuffer[23] = (uint8)((implParam->b0_uI >> 8) & 0x00FF);
    SaveFncDataBuffer[24] = (uint8)(implParam->sfr_uI & 0x00FF);
    SaveFncDataBuffer[25] = (uint8)((implParam->sfr_uI >> 8) & 0x00FF);
    SaveFncDataBuffer[26] = (uint8)(implParam->i_old_uI & 0x000000FF);
    SaveFncDataBuffer[27] = (uint8)((implParam->i_old_uI >> 8) & 0x000000FF);
    SaveFncDataBuffer[28] = (uint8)((implParam->i_old_uI >> 16) & 0x000000FF);
    SaveFncDataBuffer[29] = (uint8)((implParam->i_old_uI >> 24) & 0x000000FF);
    SaveFncDataBuffer[30] = (uint8)(implParam->b0_I & 0x00FF);
    SaveFncDataBuffer[31] = (uint8)((implParam->b0_I >> 8) & 0x00FF);
    SaveFncDataBuffer[32] = (uint8)(implParam->sfr_I & 0x00FF);
    SaveFncDataBuffer[33] = (uint8)((implParam->sfr_I >> 8) & 0x00FF);
    SaveFncDataBuffer[34] = (uint8)(implParam->i_old_I & 0x000000FF);
    SaveFncDataBuffer[35] = (uint8)((implParam->i_old_I >> 8) & 0x000000FF);
    SaveFncDataBuffer[36] = (uint8)((implParam->i_old_I >> 16) & 0x000000FF);
    SaveFncDataBuffer[37] = (uint8)((implParam->i_old_I >> 24) & 0x000000FF);
    SaveFncDataBuffer[38] = (uint8)implParam->rawSpeed;
    SaveFncDataBuffer[39] = (uint8)(implParam->vGain & 0x00FF);
    SaveFncDataBuffer[40] = (uint8)((implParam->vGain >> 8) & 0x00FF);
    SaveFncDataBuffer[41] = (uint8)(implParam->sfrGain & 0x00FF);
    SaveFncDataBuffer[42] = (uint8)((implParam->sfrGain >> 8) & 0x00FF);
    SaveFncDataBuffer[43] = (uint8)(implParam->b1_I & 0x00FF);
    SaveFncDataBuffer[44] = (uint8)((implParam->b1_I >> 8) & 0x00FF);
    SaveFncDataBuffer[45] = (uint8)(implParam->b1_uI & 0x00FF);
    SaveFncDataBuffer[46] = (uint8)((implParam->b1_uI >> 8) & 0x00FF);
    SaveFncDataBuffer[47] = (uint8)(implParam->sfrb1_I & 0x00FF);
    SaveFncDataBuffer[48] = (uint8)((implParam->sfrb1_I >> 8) & 0x00FF);
    SaveFncDataBuffer[49] = (uint8)(implParam->sfrb1_uI & 0x00FF);
    SaveFncDataBuffer[50] = (uint8)((implParam->sfrb1_uI >> 8) & 0x00FF);

    /** - Execute save function of block */
    error = SquareInj_Slow_Modell_FiP16_Save(block, SaveFncDataBuffer, 51);

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
uint8 SquareInj_Slow_Modell_FiP16_ConvertMP(SQUAREINJ_SLOW_MODELL_FIP16 *block, SQUAREINJ_SLOW_MODELL_FIP16_MASK_PARAM *maskParam)
{
    uint8 error;
    float_CoT block_ts;
    SQUAREINJ_SLOW_MODELL_FIP16_IMPL_PARAM *implParam = (SQUAREINJ_SLOW_MODELL_FIP16_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);
    if (error)
    {
        return (error);
    }

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)(implParam->b0 & 0x000000FF);
    SaveFncDataBuffer[1] = (uint8)((implParam->b0 >> 8) & 0x000000FF);
    SaveFncDataBuffer[2] = (uint8)((implParam->b0 >> 16) & 0x000000FF);
    SaveFncDataBuffer[3] = (uint8)((implParam->b0 >> 24) & 0x000000FF);
    SaveFncDataBuffer[4] = (uint8)(implParam->b1 & 0x000000FF);
    SaveFncDataBuffer[5] = (uint8)((implParam->b1 >> 8) & 0x000000FF);
    SaveFncDataBuffer[6] = (uint8)((implParam->b1 >> 16) & 0x000000FF);
    SaveFncDataBuffer[7] = (uint8)((implParam->b1 >> 24) & 0x000000FF);
    SaveFncDataBuffer[8] = (uint8)implParam->sfrb0;
    SaveFncDataBuffer[9] = (uint8)implParam->sfrb1;
    SaveFncDataBuffer[10] = (uint8)(implParam->a0_PT1 & 0x00FF);
    SaveFncDataBuffer[11] = (uint8)((implParam->a0_PT1 >> 8) & 0x00FF);
    SaveFncDataBuffer[12] = (uint8)(implParam->b0_PT1 & 0x00FF);
    SaveFncDataBuffer[13] = (uint8)((implParam->b0_PT1 >> 8) & 0x00FF);
    SaveFncDataBuffer[14] = (uint8)(implParam->b1_PT1 & 0x00FF);
    SaveFncDataBuffer[15] = (uint8)((implParam->b1_PT1 >> 8) & 0x00FF);
    SaveFncDataBuffer[16] = (uint8)(implParam->sfra_PT1 & 0x00FF);
    SaveFncDataBuffer[17] = (uint8)((implParam->sfra_PT1 >> 8) & 0x00FF);
    SaveFncDataBuffer[18] = (uint8)(implParam->sfrb_PT1 & 0x00FF);
    SaveFncDataBuffer[19] = (uint8)((implParam->sfrb_PT1 >> 8) & 0x00FF);
    SaveFncDataBuffer[20] = (uint8)(implParam->dphiOld & 0x00FF);
    SaveFncDataBuffer[21] = (uint8)((implParam->dphiOld >> 8) & 0x00FF);
    SaveFncDataBuffer[22] = (uint8)(implParam->b0_uI & 0x00FF);
    SaveFncDataBuffer[23] = (uint8)((implParam->b0_uI >> 8) & 0x00FF);
    SaveFncDataBuffer[24] = (uint8)(implParam->sfr_uI & 0x00FF);
    SaveFncDataBuffer[25] = (uint8)((implParam->sfr_uI >> 8) & 0x00FF);
    SaveFncDataBuffer[26] = (uint8)(implParam->i_old_uI & 0x000000FF);
    SaveFncDataBuffer[27] = (uint8)((implParam->i_old_uI >> 8) & 0x000000FF);
    SaveFncDataBuffer[28] = (uint8)((implParam->i_old_uI >> 16) & 0x000000FF);
    SaveFncDataBuffer[29] = (uint8)((implParam->i_old_uI >> 24) & 0x000000FF);
    SaveFncDataBuffer[30] = (uint8)(implParam->b0_I & 0x00FF);
    SaveFncDataBuffer[31] = (uint8)((implParam->b0_I >> 8) & 0x00FF);
    SaveFncDataBuffer[32] = (uint8)(implParam->sfr_I & 0x00FF);
    SaveFncDataBuffer[33] = (uint8)((implParam->sfr_I >> 8) & 0x00FF);
    SaveFncDataBuffer[34] = (uint8)(implParam->i_old_I & 0x000000FF);
    SaveFncDataBuffer[35] = (uint8)((implParam->i_old_I >> 8) & 0x000000FF);
    SaveFncDataBuffer[36] = (uint8)((implParam->i_old_I >> 16) & 0x000000FF);
    SaveFncDataBuffer[37] = (uint8)((implParam->i_old_I >> 24) & 0x000000FF);
    SaveFncDataBuffer[38] = (uint8)implParam->rawSpeed;
    SaveFncDataBuffer[39] = (uint8)(implParam->vGain & 0x00FF);
    SaveFncDataBuffer[40] = (uint8)((implParam->vGain >> 8) & 0x00FF);
    SaveFncDataBuffer[41] = (uint8)(implParam->sfrGain & 0x00FF);
    SaveFncDataBuffer[42] = (uint8)((implParam->sfrGain >> 8) & 0x00FF);
    SaveFncDataBuffer[43] = (uint8)(implParam->b1_I & 0x00FF);
    SaveFncDataBuffer[44] = (uint8)((implParam->b1_I >> 8) & 0x00FF);
    SaveFncDataBuffer[45] = (uint8)(implParam->b1_uI & 0x00FF);
    SaveFncDataBuffer[46] = (uint8)((implParam->b1_uI >> 8) & 0x00FF);
    SaveFncDataBuffer[47] = (uint8)(implParam->sfrb1_I & 0x00FF);
    SaveFncDataBuffer[48] = (uint8)((implParam->sfrb1_I >> 8) & 0x00FF);
    SaveFncDataBuffer[49] = (uint8)(implParam->sfrb1_uI & 0x00FF);
    SaveFncDataBuffer[50] = (uint8)((implParam->sfrb1_uI >> 8) & 0x00FF);

    /** - Execute save function of block */
    error = SquareInj_Slow_Modell_FiP16_Save(block, SaveFncDataBuffer, 51);

    return (error);
}

/**
 * @brief Backups current Mask parameters into global Mask parameter backup array.
 *
 * @param[in] maskParam Mask parameters
 *
 * @return Nothing
 */
void SquareInj_Slow_Modell_FiP16_BackupMP(SQUAREINJ_SLOW_MODELL_FIP16_MASK_PARAM* maskParam)
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
void SquareInj_Slow_Modell_FiP16_RestoreMP(SQUAREINJ_SLOW_MODELL_FIP16_MASK_PARAM* maskParam)
{
    memcpy(maskParam, MaskParamBuffer, sizeof(*maskParam));
}
