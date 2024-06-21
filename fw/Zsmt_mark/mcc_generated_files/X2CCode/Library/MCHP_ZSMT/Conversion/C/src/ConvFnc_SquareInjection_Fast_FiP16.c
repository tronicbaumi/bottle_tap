/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "ConvFnc_SquareInjection_Fast_FiP16.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* USERCODE-END:PreProcessor                                                                                          */

extern uint8 MaskParamBuffer[];
extern uint8 ImplParamBuffer[];
extern uint8 SaveFncDataBuffer[];

/** Implementation parameter data structure */
typedef struct {
    int16 iUsAmp;
    int16 t_pulse;
    int16 t1;
    int16 deltaT;
    uint16 delayPLL;
    uint16 delayCtrl;
    int16 uInjAmp;
} SQUAREINJECTION_FAST_FIP16_IMPL_PARAM;

/** Private prototypes */
static uint8 convertM2I(const SQUAREINJECTION_FAST_FIP16_MASK_PARAM *maskParam, SQUAREINJECTION_FAST_FIP16_IMPL_PARAM *impParam, float_CoT ts);

/**
 * @brief Converts Mask parameters to Implementation parameters.
 *
 * @param[in] maskParam Mask parameters
 * @param[out] impParam Implementation parameters
 * @param[in] ts Block sample time
 *
 * @return Error: zero on success, not zero in case of conversion error
 */
static uint8 convertM2I(const SQUAREINJECTION_FAST_FIP16_MASK_PARAM *maskParam, SQUAREINJECTION_FAST_FIP16_IMPL_PARAM *impParam, float_CoT ts)
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
uint8 SquareInjection_Fast_FiP16_LoadMP(const SQUAREINJECTION_FAST_FIP16_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)72 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(maskParam->VoltPhasor)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(maskParam->VoltPhasor) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(maskParam->VoltPhasor) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(maskParam->VoltPhasor) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(maskParam->VoltPhasor) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(maskParam->VoltPhasor) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(maskParam->VoltPhasor) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(maskParam->VoltPhasor) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(maskParam->T1)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(maskParam->T1) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(maskParam->T1) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(maskParam->T1) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(maskParam->T1) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(maskParam->T1) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(maskParam->T1) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(maskParam->T1) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(maskParam->deltaT)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(maskParam->deltaT) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(maskParam->deltaT) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(maskParam->deltaT) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(maskParam->deltaT) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(maskParam->deltaT) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(maskParam->deltaT) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(maskParam->deltaT) >> 56) & 0x00000000000000FF);
        data[24] = (uint8)((*(uint64*)&(maskParam->Tpulse)) & 0x00000000000000FF);
        data[25] = (uint8)((*(uint64*)&(maskParam->Tpulse) >> 8) & 0x00000000000000FF);
        data[26] = (uint8)((*(uint64*)&(maskParam->Tpulse) >> 16) & 0x00000000000000FF);
        data[27] = (uint8)((*(uint64*)&(maskParam->Tpulse) >> 24) & 0x00000000000000FF);
        data[28] = (uint8)((*(uint64*)&(maskParam->Tpulse) >> 32) & 0x00000000000000FF);
        data[29] = (uint8)((*(uint64*)&(maskParam->Tpulse) >> 40) & 0x00000000000000FF);
        data[30] = (uint8)((*(uint64*)&(maskParam->Tpulse) >> 48) & 0x00000000000000FF);
        data[31] = (uint8)((*(uint64*)&(maskParam->Tpulse) >> 56) & 0x00000000000000FF);
        data[32] = (uint8)((*(uint64*)&(maskParam->DelayPLL)) & 0x00000000000000FF);
        data[33] = (uint8)((*(uint64*)&(maskParam->DelayPLL) >> 8) & 0x00000000000000FF);
        data[34] = (uint8)((*(uint64*)&(maskParam->DelayPLL) >> 16) & 0x00000000000000FF);
        data[35] = (uint8)((*(uint64*)&(maskParam->DelayPLL) >> 24) & 0x00000000000000FF);
        data[36] = (uint8)((*(uint64*)&(maskParam->DelayPLL) >> 32) & 0x00000000000000FF);
        data[37] = (uint8)((*(uint64*)&(maskParam->DelayPLL) >> 40) & 0x00000000000000FF);
        data[38] = (uint8)((*(uint64*)&(maskParam->DelayPLL) >> 48) & 0x00000000000000FF);
        data[39] = (uint8)((*(uint64*)&(maskParam->DelayPLL) >> 56) & 0x00000000000000FF);
        data[40] = (uint8)((*(uint64*)&(maskParam->DelayCtrl)) & 0x00000000000000FF);
        data[41] = (uint8)((*(uint64*)&(maskParam->DelayCtrl) >> 8) & 0x00000000000000FF);
        data[42] = (uint8)((*(uint64*)&(maskParam->DelayCtrl) >> 16) & 0x00000000000000FF);
        data[43] = (uint8)((*(uint64*)&(maskParam->DelayCtrl) >> 24) & 0x00000000000000FF);
        data[44] = (uint8)((*(uint64*)&(maskParam->DelayCtrl) >> 32) & 0x00000000000000FF);
        data[45] = (uint8)((*(uint64*)&(maskParam->DelayCtrl) >> 40) & 0x00000000000000FF);
        data[46] = (uint8)((*(uint64*)&(maskParam->DelayCtrl) >> 48) & 0x00000000000000FF);
        data[47] = (uint8)((*(uint64*)&(maskParam->DelayCtrl) >> 56) & 0x00000000000000FF);
        data[48] = (uint8)((*(uint64*)&(maskParam->uInj)) & 0x00000000000000FF);
        data[49] = (uint8)((*(uint64*)&(maskParam->uInj) >> 8) & 0x00000000000000FF);
        data[50] = (uint8)((*(uint64*)&(maskParam->uInj) >> 16) & 0x00000000000000FF);
        data[51] = (uint8)((*(uint64*)&(maskParam->uInj) >> 24) & 0x00000000000000FF);
        data[52] = (uint8)((*(uint64*)&(maskParam->uInj) >> 32) & 0x00000000000000FF);
        data[53] = (uint8)((*(uint64*)&(maskParam->uInj) >> 40) & 0x00000000000000FF);
        data[54] = (uint8)((*(uint64*)&(maskParam->uInj) >> 48) & 0x00000000000000FF);
        data[55] = (uint8)((*(uint64*)&(maskParam->uInj) >> 56) & 0x00000000000000FF);
        data[56] = (uint8)((*(uint64*)&(maskParam->uDCmax)) & 0x00000000000000FF);
        data[57] = (uint8)((*(uint64*)&(maskParam->uDCmax) >> 8) & 0x00000000000000FF);
        data[58] = (uint8)((*(uint64*)&(maskParam->uDCmax) >> 16) & 0x00000000000000FF);
        data[59] = (uint8)((*(uint64*)&(maskParam->uDCmax) >> 24) & 0x00000000000000FF);
        data[60] = (uint8)((*(uint64*)&(maskParam->uDCmax) >> 32) & 0x00000000000000FF);
        data[61] = (uint8)((*(uint64*)&(maskParam->uDCmax) >> 40) & 0x00000000000000FF);
        data[62] = (uint8)((*(uint64*)&(maskParam->uDCmax) >> 48) & 0x00000000000000FF);
        data[63] = (uint8)((*(uint64*)&(maskParam->uDCmax) >> 56) & 0x00000000000000FF);
        data[64] = (uint8)((*(uint64*)&(maskParam->ts_fact)) & 0x00000000000000FF);
        data[65] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 8) & 0x00000000000000FF);
        data[66] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 16) & 0x00000000000000FF);
        data[67] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 24) & 0x00000000000000FF);
        data[68] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 32) & 0x00000000000000FF);
        data[69] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 40) & 0x00000000000000FF);
        data[70] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 48) & 0x00000000000000FF);
        data[71] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 56) & 0x00000000000000FF);
        *dataLen = (uint16)72;
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
uint8 SquareInjection_Fast_FiP16_SaveMP(SQUAREINJECTION_FAST_FIP16 *block, SQUAREINJECTION_FAST_FIP16_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen)
{
    uint8 error = (uint8)0;

    if (dataLen != (uint16)72)
    {
        error = (uint8)1;
    }
    else
    {
        uint64 tmp64;
        /** - Cache old mask parameters */
        SquareInjection_Fast_FiP16_BackupMP(maskParam);

        /** - Save new mask parameters */
        tmp64 = (uint64)data[0] + \
            ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
            ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
            ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
            ((uint64)data[7] << 56);
        maskParam->VoltPhasor = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        maskParam->T1 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        maskParam->deltaT = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[24] + \
            ((uint64)data[25] << 8) + ((uint64)data[26] << 16) + \
            ((uint64)data[27] << 24) + ((uint64)data[28] << 32) + \
            ((uint64)data[29] << 40) + ((uint64)data[30] << 48) + \
            ((uint64)data[31] << 56);
        maskParam->Tpulse = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[32] + \
            ((uint64)data[33] << 8) + ((uint64)data[34] << 16) + \
            ((uint64)data[35] << 24) + ((uint64)data[36] << 32) + \
            ((uint64)data[37] << 40) + ((uint64)data[38] << 48) + \
            ((uint64)data[39] << 56);
        maskParam->DelayPLL = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[40] + \
            ((uint64)data[41] << 8) + ((uint64)data[42] << 16) + \
            ((uint64)data[43] << 24) + ((uint64)data[44] << 32) + \
            ((uint64)data[45] << 40) + ((uint64)data[46] << 48) + \
            ((uint64)data[47] << 56);
        maskParam->DelayCtrl = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[48] + \
            ((uint64)data[49] << 8) + ((uint64)data[50] << 16) + \
            ((uint64)data[51] << 24) + ((uint64)data[52] << 32) + \
            ((uint64)data[53] << 40) + ((uint64)data[54] << 48) + \
            ((uint64)data[55] << 56);
        maskParam->uInj = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[56] + \
            ((uint64)data[57] << 8) + ((uint64)data[58] << 16) + \
            ((uint64)data[59] << 24) + ((uint64)data[60] << 32) + \
            ((uint64)data[61] << 40) + ((uint64)data[62] << 48) + \
            ((uint64)data[63] << 56);
        maskParam->uDCmax = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[64] + \
            ((uint64)data[65] << 8) + ((uint64)data[66] << 16) + \
            ((uint64)data[67] << 24) + ((uint64)data[68] << 32) + \
            ((uint64)data[69] << 40) + ((uint64)data[70] << 48) + \
            ((uint64)data[71] << 56);
        maskParam->ts_fact = (float64)(*(float64*)&tmp64);

        error = SquareInjection_Fast_FiP16_ConvertMP(block, maskParam);

        /** - Check for errors during execution of save function */
        if (error != 0)
        {
            /* Restore old mask parameter */
            SquareInjection_Fast_FiP16_RestoreMP(maskParam);
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
uint8 SquareInjection_Fast_FiP16_InitMP(SQUAREINJECTION_FAST_FIP16 *block, const SQUAREINJECTION_FAST_FIP16_MASK_PARAM *maskParam)
{
    uint8 error = (uint8)0;
    float_CoT block_ts;

    SQUAREINJECTION_FAST_FIP16_IMPL_PARAM *implParam = (SQUAREINJECTION_FAST_FIP16_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)(implParam->iUsAmp & 0x00FF);
    SaveFncDataBuffer[1] = (uint8)((implParam->iUsAmp >> 8) & 0x00FF);
    SaveFncDataBuffer[2] = (uint8)(implParam->t_pulse & 0x00FF);
    SaveFncDataBuffer[3] = (uint8)((implParam->t_pulse >> 8) & 0x00FF);
    SaveFncDataBuffer[4] = (uint8)(implParam->t1 & 0x00FF);
    SaveFncDataBuffer[5] = (uint8)((implParam->t1 >> 8) & 0x00FF);
    SaveFncDataBuffer[6] = (uint8)(implParam->deltaT & 0x00FF);
    SaveFncDataBuffer[7] = (uint8)((implParam->deltaT >> 8) & 0x00FF);
    SaveFncDataBuffer[8] = (uint8)(implParam->delayPLL & 0x00FF);
    SaveFncDataBuffer[9] = (uint8)((implParam->delayPLL >> 8) & 0x00FF);
    SaveFncDataBuffer[10] = (uint8)(implParam->delayCtrl & 0x00FF);
    SaveFncDataBuffer[11] = (uint8)((implParam->delayCtrl >> 8) & 0x00FF);
    SaveFncDataBuffer[12] = (uint8)(implParam->uInjAmp & 0x00FF);
    SaveFncDataBuffer[13] = (uint8)((implParam->uInjAmp >> 8) & 0x00FF);

    /** - Execute save function of block */
    error = SquareInjection_Fast_FiP16_Save(block, SaveFncDataBuffer, 14);

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
uint8 SquareInjection_Fast_FiP16_ConvertMP(SQUAREINJECTION_FAST_FIP16 *block, SQUAREINJECTION_FAST_FIP16_MASK_PARAM *maskParam)
{
    uint8 error;
    float_CoT block_ts;
    SQUAREINJECTION_FAST_FIP16_IMPL_PARAM *implParam = (SQUAREINJECTION_FAST_FIP16_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);
    if (error)
    {
        return (error);
    }

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)(implParam->iUsAmp & 0x00FF);
    SaveFncDataBuffer[1] = (uint8)((implParam->iUsAmp >> 8) & 0x00FF);
    SaveFncDataBuffer[2] = (uint8)(implParam->t_pulse & 0x00FF);
    SaveFncDataBuffer[3] = (uint8)((implParam->t_pulse >> 8) & 0x00FF);
    SaveFncDataBuffer[4] = (uint8)(implParam->t1 & 0x00FF);
    SaveFncDataBuffer[5] = (uint8)((implParam->t1 >> 8) & 0x00FF);
    SaveFncDataBuffer[6] = (uint8)(implParam->deltaT & 0x00FF);
    SaveFncDataBuffer[7] = (uint8)((implParam->deltaT >> 8) & 0x00FF);
    SaveFncDataBuffer[8] = (uint8)(implParam->delayPLL & 0x00FF);
    SaveFncDataBuffer[9] = (uint8)((implParam->delayPLL >> 8) & 0x00FF);
    SaveFncDataBuffer[10] = (uint8)(implParam->delayCtrl & 0x00FF);
    SaveFncDataBuffer[11] = (uint8)((implParam->delayCtrl >> 8) & 0x00FF);
    SaveFncDataBuffer[12] = (uint8)(implParam->uInjAmp & 0x00FF);
    SaveFncDataBuffer[13] = (uint8)((implParam->uInjAmp >> 8) & 0x00FF);

    /** - Execute save function of block */
    error = SquareInjection_Fast_FiP16_Save(block, SaveFncDataBuffer, 14);

    return (error);
}

/**
 * @brief Backups current Mask parameters into global Mask parameter backup array.
 *
 * @param[in] maskParam Mask parameters
 *
 * @return Nothing
 */
void SquareInjection_Fast_FiP16_BackupMP(SQUAREINJECTION_FAST_FIP16_MASK_PARAM* maskParam)
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
void SquareInjection_Fast_FiP16_RestoreMP(SQUAREINJECTION_FAST_FIP16_MASK_PARAM* maskParam)
{
    memcpy(maskParam, MaskParamBuffer, sizeof(*maskParam));
}
