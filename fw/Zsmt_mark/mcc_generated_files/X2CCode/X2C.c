/* This file is part of X2C. http://x2c.lcm.at/                                                                       */

/* Model: MC_FOC_ZSMT_FIP_dsPIC33CK_POWERTOOL                                                                         */
/* Date:  2024-06-25 17:03                                                                                            */

/* X2C-Version: 6.4.3142                                                                                              */
/* X2C-Edition: Free                                                                                                  */

/* Common includes                                                                                                    */
#include <stddef.h>
#include "TableStruct.h"
/* Generated file includes                                                                                            */
#include "FlashTable.h"
#include "RamTable.h"
#include "X2C.h"

/**********************************************************************************************************************/
/**                                                       Model                                                      **/
/**********************************************************************************************************************/
struct x2cModel x2cModel;

/**********************************************************************************************************************/
/**                                                       Scope                                                      **/
/**********************************************************************************************************************/
SCOPE_MAIN x2cScope;

/* Block function table                                                                                               */
const tBlockFunctions blockFunctionTable[] = {
    FUNCTIONS,
    { 0U, NULL, NULL, NULL, NULL, NULL } /* End of table entry */
};

/* Parameter identifier table                                                                                         */
const tParameterTable parameterIdTable[] = {
    PARAMETER_TABLE,
    { 0U, NULL } /* End of table entry */
};

/* Inport Parameter identifier table                                                                                  */
const tIoParamIdEntry inportParamIdTable[] = {
    INPORT_PARAMID_TABLE, 
    { 0U, 0U, NULL } /* End of table entry */
};

/* Outport Parameter identifier table                                                                                 */
const tIoParamIdEntry outportParamIdTable[] = {
    OUTPORT_PARAMID_TABLE, 
    { 0U, 0U, NULL } /* End of table entry */
};

/* Mask Parameter identifier table                                                                                    */
const tMaskParameterEntry maskParamIdTable[] = {
    { 0U, NULL, NULL, NULL, NULL } /* End of table entry */
};

/* Extended Mask Parameter identifier table (used by Model API)                                                       */
const tMaskParamExtRecord maskParamExtTable[] = {
    { 0U, 0U, NULL, NULL, NULL, NULL, NULL } /* End of table entry */
};

/* Mask Parameter data table (used by Model API)                                                                      */
const tMaskParamDataRecord maskParamDataTable[] = {
    { 0U, 0U, NULL, 0U, 0U } /* End of table entry */
};

/**********************************************************************************************************************/
/** Model Sample Time                                                                                                **/
/**********************************************************************************************************************/
float_CoT getModelSampleTime()
{
    return ((float_CoT)5.0E-5);
}

/**********************************************************************************************************************/
/**                                                  Initialization                                                  **/
/**********************************************************************************************************************/
void X2C_Init(void)
{
    /******************************************************************************************************************/
    /**                                          Initialize Block Parameters                                         **/
    /******************************************************************************************************************/

    /* Block: Const_IdCmd                                                                                             */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.bConst_IdCmd.K = 0;

    /* Block: Const_IdCmd1                                                                                            */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.bConst_IdCmd1.K = 0;

    /* Block: Delay                                                                                                   */
    /* ts_fact = 4.0                                                                                                  */
    x2cModel.blocks.bDelay.In_old = 0;

    /* Block: Delay1                                                                                                  */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.bDelay1.In_old = 0;

    /* Block: FOC_main/AutoSwitch                                                                                     */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = 0.5                                                                                              */
    x2cModel.blocks.sFOC_main.bAutoSwitch.Thresh_up = 16384;
    x2cModel.blocks.sFOC_main.bAutoSwitch.Thresh_down = 16384;
    x2cModel.blocks.sFOC_main.bAutoSwitch.Status = &RamTable_int16[0];

    /* Block: FOC_main/AutoSwitch1                                                                                    */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = 0.5                                                                                              */
    x2cModel.blocks.sFOC_main.bAutoSwitch1.Thresh_up = 16384;
    x2cModel.blocks.sFOC_main.bAutoSwitch1.Thresh_down = 16384;
    x2cModel.blocks.sFOC_main.bAutoSwitch1.Status = &RamTable_int16[1];

    /* Block: FOC_main/AutoSwitch2                                                                                    */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = 0.5                                                                                              */
    x2cModel.blocks.sFOC_main.bAutoSwitch2.Thresh_up = 16384;
    x2cModel.blocks.sFOC_main.bAutoSwitch2.Thresh_down = 16384;
    x2cModel.blocks.sFOC_main.bAutoSwitch2.Status = &RamTable_int16[2];

    /* Block: FOC_main/Clarke_Park_MCHP                                                                               */

    /* Block: FOC_main/Const_FocAngle                                                                                 */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sFOC_main.bConst_FocAngle.K = 0;

    /* Block: FOC_main/Const_IdRef                                                                                    */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sFOC_main.bConst_IdRef.K = 0;

    /* Block: FOC_main/Const_IqRef                                                                                    */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sFOC_main.bConst_IqRef.K = 0;

    /* Block: FOC_main/DisableFOC                                                                                     */
    /* Toggle = 0.0                                                                                                   */
    x2cModel.blocks.sFOC_main.bDisableFOC.Toggle = 0;

    /* Block: FOC_main/EnableVsat1                                                                                    */
    /* Value = 1.0                                                                                                    */
    x2cModel.blocks.sFOC_main.bEnableVsat1.K = 1;

    /* Block: FOC_main/FluxError                                                                                      */

    /* Block: FOC_main/ForwardPath_HFI                                                                                */
    /* HF_InjectionPolarity = Non inverting (Add)                                                                     */
    x2cModel.blocks.sFOC_main.bForwardPath_HFI.HF_InjectionPolarity = 0;

    /* Block: FOC_main/HFI/Delay                                                                                      */
    /* ts_fact = 4.0                                                                                                  */
    x2cModel.blocks.sFOC_main.sHFI.bDelay.In_old = 0;

    /* Block: FOC_main/HFI/EnableHF                                                                                   */
    /* Toggle = 0.0                                                                                                   */
    x2cModel.blocks.sFOC_main.sHFI.bEnableHF.Toggle = 0;

    /* Block: FOC_main/HFI/EnableHFI                                                                                  */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sFOC_main.sHFI.bEnableHFI.K = 0;

    /* Block: FOC_main/HFI/HFInjectionSquare                                                                          */
    /* U_inj = 5.0                                                                                                    */
    /* Jp = 0.0012                                                                                                    */
    /* I_inj = 0.4                                                                                                    */
    /* fo = 200.0                                                                                                     */
    /* p = 4.0                                                                                                        */
    /* n_max = 3000.0                                                                                                 */
    /* I_max = 22.0                                                                                                   */
    /* U_max = 24.0                                                                                                   */
    /* ts_fact = 1.0                                                                                                  */
    /* estimation = less noise                                                                                        */
    /* method = tustin                                                                                                */
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.uInjAmp = 6827;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.sampleCnt = 0;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.iyArr = &RamTable_int32[0];
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.enable_old = 0;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.i_old_torque = 0;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.i_old_speed = 0;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.i_old_angle = 0;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.vGain = 21120;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.sfrGain = 11;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.b0_torque = 1092857600;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.b1_torque = 1698931936;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.sfrb0_torque = 23;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.sfrb1_torque = 20;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.b0_speed = 55;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.b1_speed = 27;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.sfrb0_speed = 15;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.sfrb1_speed = 15;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.b0_angle = 2621;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.b1_angle = 1311;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.sfrb0_angle = 15;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.sfrb1_angle = 15;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.rawSpeed = 0;

    /* Block: FOC_main/HFI/InitPosDetect                                                                              */
    /* U_pulse = 8.0                                                                                                  */
    /* T_pulse = 4.0                                                                                                  */
    /* T_pause = 3.0                                                                                                  */
    /* U_max = 24.0                                                                                                   */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.u_pulse = 10923;
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.t_pulse = 4;
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.t_period = 68;
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.timer = 0;
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.dir = 0;
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.phi = 0;
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.max_ia_pos = 0;
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.max_ia_neg = 0;
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.max_ib_pos = 0;
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.max_ib_neg = 0;
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.max_ic_pos = 0;
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.max_ic_neg = 0;

    /* Block: FOC_main/HFI/Negation1                                                                                  */

    /* Block: FOC_main/HFI/Sub                                                                                        */

    /* Block: FOC_main/HFI/nInit3                                                                                     */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sFOC_main.sHFI.bnInit3.K = 0;

    /* Block: FOC_main/IdAvg4                                                                                         */
    /* n = 4                                                                                                          */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sFOC_main.bIdAvg4.n = 4;
    x2cModel.blocks.sFOC_main.bIdAvg4.sfrn = 2;
    x2cModel.blocks.sFOC_main.bIdAvg4.sum = 0;
    x2cModel.blocks.sFOC_main.bIdAvg4.count = 0;
    x2cModel.blocks.sFOC_main.bIdAvg4.avg = &RamTable_int16[3];

    /* Block: FOC_main/IqAvg4                                                                                         */
    /* n = 4                                                                                                          */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sFOC_main.bIqAvg4.n = 4;
    x2cModel.blocks.sFOC_main.bIqAvg4.sfrn = 2;
    x2cModel.blocks.sFOC_main.bIqAvg4.sum = 0;
    x2cModel.blocks.sFOC_main.bIqAvg4.count = 0;
    x2cModel.blocks.sFOC_main.bIqAvg4.avg = &RamTable_int16[259];

    /* Block: FOC_main/Iq_SlowAvg                                                                                     */
    /* n = 256                                                                                                        */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sFOC_main.bIq_SlowAvg.n = 256;
    x2cModel.blocks.sFOC_main.bIq_SlowAvg.sfrn = 8;
    x2cModel.blocks.sFOC_main.bIq_SlowAvg.sum = 0;
    x2cModel.blocks.sFOC_main.bIq_SlowAvg.count = 0;
    x2cModel.blocks.sFOC_main.bIq_SlowAvg.avg = &RamTable_int16[515];

    /* Block: FOC_main/LoopBreakerSpeed1                                                                              */

    /* Block: FOC_main/OverrideAngle                                                                                  */
    /* Toggle = 0.0                                                                                                   */
    x2cModel.blocks.sFOC_main.bOverrideAngle.Toggle = 0;

    /* Block: FOC_main/OverrideId                                                                                     */
    /* Toggle = 1.0                                                                                                   */
    x2cModel.blocks.sFOC_main.bOverrideId.Toggle = 1;

    /* Block: FOC_main/OverrideIq                                                                                     */
    /* Toggle = 0.0                                                                                                   */
    x2cModel.blocks.sFOC_main.bOverrideIq.Toggle = 0;

    /* Block: FOC_main/PI_Flux                                                                                        */
    /* Kp = 2.0                                                                                                       */
    /* Ki = 500.0                                                                                                     */
    /* ts_fact = 4.0                                                                                                  */
    x2cModel.blocks.sFOC_main.bPI_Flux.b0 = 3277;
    x2cModel.blocks.sFOC_main.bPI_Flux.b1 = 16384;
    x2cModel.blocks.sFOC_main.bPI_Flux.sfrb0 = 15;
    x2cModel.blocks.sFOC_main.bPI_Flux.sfrb1 = 13;
    x2cModel.blocks.sFOC_main.bPI_Flux.i_old = 0;
    x2cModel.blocks.sFOC_main.bPI_Flux.enable_old = 0;

    /* Block: FOC_main/PI_Torque                                                                                      */
    /* Kp = 2.0                                                                                                       */
    /* Ki = 500.0                                                                                                     */
    /* ts_fact = 4.0                                                                                                  */
    x2cModel.blocks.sFOC_main.bPI_Torque.b0 = 3277;
    x2cModel.blocks.sFOC_main.bPI_Torque.b1 = 16384;
    x2cModel.blocks.sFOC_main.bPI_Torque.sfrb0 = 15;
    x2cModel.blocks.sFOC_main.bPI_Torque.sfrb1 = 13;
    x2cModel.blocks.sFOC_main.bPI_Torque.i_old = 0;
    x2cModel.blocks.sFOC_main.bPI_Torque.enable_old = 0;

    /* Block: FOC_main/TorqueError                                                                                    */

    /* Block: FOC_main/Ts/Isat1                                                                                       */
    /* Value = 0.05                                                                                                   */
    x2cModel.blocks.sFOC_main.sTs.bIsat1.K = 1638;

    /* Block: FOC_main/Ts/Isat2                                                                                       */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sFOC_main.sTs.bIsat2.K = 0;

    /* Block: FOC_main/Ts/PerturbationGen                                                                             */
    /* fmax = 910.0                                                                                                   */
    /* LL = 0.0                                                                                                       */
    /* LH = 0.0                                                                                                       */
    /* Tr = 0.0                                                                                                       */
    /* Tf = 0.0                                                                                                       */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sFOC_main.sTs.bPerturbationGen.delta_phi = 2982;
    x2cModel.blocks.sFOC_main.sTs.bPerturbationGen.phi = 0;
    x2cModel.blocks.sFOC_main.sTs.bPerturbationGen.level_low = 0;
    x2cModel.blocks.sFOC_main.sTs.bPerturbationGen.level_high = 0;
    x2cModel.blocks.sFOC_main.sTs.bPerturbationGen.RateUp = 2147483647;
    x2cModel.blocks.sFOC_main.sTs.bPerturbationGen.RateDown = 2147483647;
    x2cModel.blocks.sFOC_main.sTs.bPerturbationGen.out_old = 0;
    x2cModel.blocks.sFOC_main.sTs.bPerturbationGen.out_ramp = 0;

    /* Block: FOC_main/TypeConv                                                                                       */

    /* Block: FOC_main/VoltageSaturation/-Vsat                                                                        */

    /* Block: FOC_main/VoltageSaturation/-Vsat1                                                                       */

    /* Block: FOC_main/VoltageSaturation/Const_Vmax                                                                   */
    /* Value = 0.9999                                                                                                 */
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bConst_Vmax.K = 32765;

    /* Block: FOC_main/VoltageSaturation/TypeConv                                                                     */

    /* Block: FOC_main/VoltageSaturation/VdSat_Switch                                                                 */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = 0.5                                                                                              */
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bVdSat_Switch.Thresh_up = 16384;
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bVdSat_Switch.Thresh_down = 16384;
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bVdSat_Switch.Status = &RamTable_int16[771];

    /* Block: FOC_main/VoltageSaturation/Vdsat                                                                        */
    /* Value = 0.1                                                                                                    */
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bVdsat.K = 3277;

    /* Block: FOC_main/VoltageSaturation/VqSat_Switch                                                                 */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = 0.5                                                                                              */
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bVqSat_Switch.Thresh_up = 16384;
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bVqSat_Switch.Thresh_down = 16384;
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bVqSat_Switch.Status = &RamTable_int16[772];

    /* Block: FOC_main/VoltageSaturation/Vqsat                                                                        */
    /* Value = 0.3                                                                                                    */
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bVqsat.K = 9830;

    /* Block: FOC_main/zConst1                                                                                        */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sFOC_main.bzConst1.K = 0;

    /* Block: Gain                                                                                                    */
    /* Gain = 0.01                                                                                                    */
    x2cModel.blocks.bGain.V = 328;
    x2cModel.blocks.bGain.sfr = 15;

    /* Block: PI                                                                                                      */
    /* Kp = 20.0                                                                                                      */
    /* Ki = 5.0                                                                                                       */
    /* ts_fact = 4.0                                                                                                  */
    x2cModel.blocks.bPI.b0 = 33;
    x2cModel.blocks.bPI.b1 = 20480;
    x2cModel.blocks.bPI.sfrb0 = 15;
    x2cModel.blocks.bPI.sfrb1 = 10;
    x2cModel.blocks.bPI.i_old = 0;
    x2cModel.blocks.bPI.enable_old = 0;

    /* Block: StartOverride                                                                                           */
    /* Toggle = 0.0                                                                                                   */
    x2cModel.blocks.bStartOverride.Toggle = 0;

    /* Block: Sub                                                                                                     */

    /* Block: UseCurrCtr                                                                                              */
    /* Toggle = 1.0                                                                                                   */
    x2cModel.blocks.bUseCurrCtr.Toggle = 1;

    /* Block: angleError                                                                                              */

    /* Block: angleErrorLpf/LPF                                                                                       */
    /* V = 1.0                                                                                                        */
    /* fc = 10.0                                                                                                      */
    /* ts_fact = 1.0                                                                                                  */
    /* method = tustin                                                                                                */
    x2cModel.blocks.sangleErrorLpf.bLPF.b0 = 3367969;
    x2cModel.blocks.sangleErrorLpf.bLPF.b1 = 3367969;
    x2cModel.blocks.sangleErrorLpf.bLPF.a0 = -2140747710;
    x2cModel.blocks.sangleErrorLpf.bLPF.sfrb = 31;
    x2cModel.blocks.sangleErrorLpf.bLPF.sfra = 31;
    x2cModel.blocks.sangleErrorLpf.bLPF.in_old = 0;

    /* Block: angleErrorLpf/TypeConv                                                                                  */

    /* Block: angleErrorLpf/TypeConv1                                                                                 */

    /* Block: zConst1                                                                                                 */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.bzConst1.K = 0;

    /* Block: zConst2                                                                                                 */
    /* Value = 1.0                                                                                                    */
    x2cModel.blocks.bzConst2.K = 1;

    /* Block: zConst3                                                                                                 */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.bzConst3.K = 0;


    /* Initialize RAM table content */
    initRamTables();

    /******************************************************************************************************************/
    /**                                              Initialize Inports                                              **/
    /******************************************************************************************************************/
    x2cModel.inports.bCPU_LOAD = (int16)0;
    x2cModel.inports.bHall_state = (int16)0;
    x2cModel.inports.bI_a = (int16)0;
    x2cModel.inports.bI_b = (int16)0;
    x2cModel.inports.bI_sum = (int16)0;
    x2cModel.inports.bQEI_POS = (int16)0;
    x2cModel.inports.bQEI_VEL = (int16)0;
    x2cModel.inports.bS2 = false;
    x2cModel.inports.bS3 = false;
    x2cModel.inports.bV_DCLINK = (int16)0;
    x2cModel.inports.bV_POT = (int16)0;
    x2cModel.inports.bVa = (int16)0;
    x2cModel.inports.bVb = (int16)0;
    x2cModel.inports.bVc = (int16)0;

    /******************************************************************************************************************/
    /**                                               Link Block Inputs                                              **/
    /******************************************************************************************************************/

    /* Block Const_IdCmd                                                                                              */

    /* Block Const_IdCmd1                                                                                             */

    /* Block Delay                                                                                                    */
    x2cModel.blocks.bDelay.In =
        &x2cModel.blocks.bStartOverride.Out;

    /* Block Delay1                                                                                                   */
    x2cModel.blocks.bDelay1.In =
        &x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.n;

    /* Block AutoSwitch                                                                                               */
    x2cModel.blocks.sFOC_main.bAutoSwitch.In1 =
        &x2cModel.blocks.sFOC_main.bForwardPath_HFI.Vc;
    x2cModel.blocks.sFOC_main.bAutoSwitch.Switch =
        &x2cModel.blocks.sFOC_main.bTypeConv.Out;
    x2cModel.blocks.sFOC_main.bAutoSwitch.In3 =
        &x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.U_C;

    /* Block AutoSwitch1                                                                                              */
    x2cModel.blocks.sFOC_main.bAutoSwitch1.In1 =
        &x2cModel.blocks.sFOC_main.bForwardPath_HFI.Va;
    x2cModel.blocks.sFOC_main.bAutoSwitch1.Switch =
        &x2cModel.blocks.sFOC_main.bTypeConv.Out;
    x2cModel.blocks.sFOC_main.bAutoSwitch1.In3 =
        &x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.U_A;

    /* Block AutoSwitch2                                                                                              */
    x2cModel.blocks.sFOC_main.bAutoSwitch2.In1 =
        &x2cModel.blocks.sFOC_main.bForwardPath_HFI.Vb;
    x2cModel.blocks.sFOC_main.bAutoSwitch2.Switch =
        &x2cModel.blocks.sFOC_main.bTypeConv.Out;
    x2cModel.blocks.sFOC_main.bAutoSwitch2.In3 =
        &x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.U_B;

    /* Block Clarke_Park_MCHP                                                                                         */
    x2cModel.blocks.sFOC_main.bClarke_Park_MCHP.a =
        &x2cModel.inports.bI_a;
    x2cModel.blocks.sFOC_main.bClarke_Park_MCHP.b =
        &x2cModel.inports.bI_b;
    x2cModel.blocks.sFOC_main.bClarke_Park_MCHP.theta =
        &x2cModel.blocks.sFOC_main.bOverrideAngle.Out;

    /* Block Const_FocAngle                                                                                           */

    /* Block Const_IdRef                                                                                              */

    /* Block Const_IqRef                                                                                              */

    /* Block DisableFOC                                                                                               */
    x2cModel.blocks.sFOC_main.bDisableFOC.In1 =
        &x2cModel.blocks.sFOC_main.sHFI.bDelay.Out;
    x2cModel.blocks.sFOC_main.bDisableFOC.In2 =
        &x2cModel.blocks.sFOC_main.bzConst1.Out;

    /* Block EnableVsat1                                                                                              */

    /* Block FluxError                                                                                                */
    x2cModel.blocks.sFOC_main.bFluxError.Plus =
        &x2cModel.blocks.sFOC_main.sTs.bPerturbationGen.u;
    x2cModel.blocks.sFOC_main.bFluxError.Minus =
        &x2cModel.blocks.sFOC_main.bIdAvg4.Out;

    /* Block ForwardPath_HFI                                                                                          */
    x2cModel.blocks.sFOC_main.bForwardPath_HFI.Ud =
        &x2cModel.blocks.sFOC_main.bPI_Flux.Out;
    x2cModel.blocks.sFOC_main.bForwardPath_HFI.Uq =
        &x2cModel.blocks.sFOC_main.bPI_Torque.Out;
    x2cModel.blocks.sFOC_main.bForwardPath_HFI.UdHF =
        &x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.ud;
    x2cModel.blocks.sFOC_main.bForwardPath_HFI.theta =
        &x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.phi;

    /* Block Delay                                                                                                    */
    x2cModel.blocks.sFOC_main.sHFI.bDelay.In =
        &x2cModel.blocks.sFOC_main.sHFI.bEnableHF.Out;

    /* Block EnableHF                                                                                                 */
    x2cModel.blocks.sFOC_main.sHFI.bEnableHF.In1 =
        &x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.Ready;
    x2cModel.blocks.sFOC_main.sHFI.bEnableHF.In2 =
        &x2cModel.blocks.sFOC_main.sHFI.bEnableHFI.Out;

    /* Block EnableHFI                                                                                                */

    /* Block HFInjectionSquare                                                                                        */
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.iAlpha =
        &x2cModel.blocks.sFOC_main.bClarke_Park_MCHP.alpha;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.iBeta =
        &x2cModel.blocks.sFOC_main.bClarke_Park_MCHP.beta;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.n0 =
        &x2cModel.blocks.sFOC_main.sHFI.bnInit3.Out;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.phi0 =
        &x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.phi0;
    x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.Enable =
        &x2cModel.blocks.sFOC_main.sHFI.bDelay.Out;

    /* Block InitPosDetect                                                                                            */
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.I_A =
        &x2cModel.inports.bI_a;
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.I_B =
        &x2cModel.inports.bI_b;
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.I_C =
        &x2cModel.blocks.sFOC_main.sHFI.bSub.Out;
    x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect.Enable =
        &x2cModel.blocks.bDelay.Out;

    /* Block Negation1                                                                                                */
    x2cModel.blocks.sFOC_main.sHFI.bNegation1.In =
        &x2cModel.inports.bI_a;

    /* Block Sub                                                                                                      */
    x2cModel.blocks.sFOC_main.sHFI.bSub.Plus =
        &x2cModel.blocks.sFOC_main.sHFI.bNegation1.Out;
    x2cModel.blocks.sFOC_main.sHFI.bSub.Minus =
        &x2cModel.inports.bI_b;

    /* Block nInit3                                                                                                   */

    /* Block IdAvg4                                                                                                   */
    x2cModel.blocks.sFOC_main.bIdAvg4.In =
        &x2cModel.blocks.sFOC_main.bClarke_Park_MCHP.d;

    /* Block IqAvg4                                                                                                   */
    x2cModel.blocks.sFOC_main.bIqAvg4.In =
        &x2cModel.blocks.sFOC_main.bClarke_Park_MCHP.q;

    /* Block Iq_SlowAvg                                                                                               */
    x2cModel.blocks.sFOC_main.bIq_SlowAvg.In =
        &x2cModel.blocks.sFOC_main.bClarke_Park_MCHP.q;

    /* Block LoopBreakerSpeed1                                                                                        */
    x2cModel.blocks.sFOC_main.bLoopBreakerSpeed1.In =
        &x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.phi;

    /* Block OverrideAngle                                                                                            */
    x2cModel.blocks.sFOC_main.bOverrideAngle.In1 =
        &x2cModel.blocks.sFOC_main.bLoopBreakerSpeed1.Out;
    x2cModel.blocks.sFOC_main.bOverrideAngle.In2 =
        &x2cModel.blocks.sFOC_main.bConst_FocAngle.Out;

    /* Block OverrideId                                                                                               */
    x2cModel.blocks.sFOC_main.bOverrideId.In1 =
        &x2cModel.blocks.bConst_IdCmd.Out;
    x2cModel.blocks.sFOC_main.bOverrideId.In2 =
        &x2cModel.blocks.sFOC_main.bConst_IdRef.Out;

    /* Block OverrideIq                                                                                               */
    x2cModel.blocks.sFOC_main.bOverrideIq.In1 =
        &x2cModel.blocks.bUseCurrCtr.Out;
    x2cModel.blocks.sFOC_main.bOverrideIq.In2 =
        &x2cModel.blocks.sFOC_main.bConst_IqRef.Out;

    /* Block PI_Flux                                                                                                  */
    x2cModel.blocks.sFOC_main.bPI_Flux.In =
        &x2cModel.blocks.sFOC_main.bFluxError.Out;
    x2cModel.blocks.sFOC_main.bPI_Flux.Init =
        &x2cModel.blocks.sFOC_main.bFluxError.Out;
    x2cModel.blocks.sFOC_main.bPI_Flux.max =
        &x2cModel.blocks.sFOC_main.sVoltageSaturation.bVdSat_Switch.Out;
    x2cModel.blocks.sFOC_main.bPI_Flux.min =
        &x2cModel.blocks.sFOC_main.sVoltageSaturation.b_Vsat1.Out;
    x2cModel.blocks.sFOC_main.bPI_Flux.Enable =
        &x2cModel.blocks.sFOC_main.bDisableFOC.Out;

    /* Block PI_Torque                                                                                                */
    x2cModel.blocks.sFOC_main.bPI_Torque.In =
        &x2cModel.blocks.sFOC_main.bTorqueError.Out;
    x2cModel.blocks.sFOC_main.bPI_Torque.Init =
        &x2cModel.blocks.sFOC_main.bTorqueError.Out;
    x2cModel.blocks.sFOC_main.bPI_Torque.max =
        &x2cModel.blocks.sFOC_main.sVoltageSaturation.bVqSat_Switch.Out;
    x2cModel.blocks.sFOC_main.bPI_Torque.min =
        &x2cModel.blocks.sFOC_main.sVoltageSaturation.b_Vsat.Out;
    x2cModel.blocks.sFOC_main.bPI_Torque.Enable =
        &x2cModel.blocks.sFOC_main.bDisableFOC.Out;

    /* Block TorqueError                                                                                              */
    x2cModel.blocks.sFOC_main.bTorqueError.Plus =
        &x2cModel.blocks.sFOC_main.bOverrideIq.Out;
    x2cModel.blocks.sFOC_main.bTorqueError.Minus =
        &x2cModel.blocks.sFOC_main.bIqAvg4.Out;

    /* Block Isat1                                                                                                    */

    /* Block Isat2                                                                                                    */

    /* Block PerturbationGen                                                                                          */
    x2cModel.blocks.sFOC_main.sTs.bPerturbationGen.f =
        &x2cModel.blocks.sFOC_main.sTs.bIsat1.Out;
    x2cModel.blocks.sFOC_main.sTs.bPerturbationGen.dc =
        &x2cModel.blocks.sFOC_main.sTs.bIsat2.Out;
    x2cModel.blocks.sFOC_main.sTs.bPerturbationGen.S_in =
        &x2cModel.blocks.sFOC_main.bOverrideId.Out;

    /* Block TypeConv                                                                                                 */
    x2cModel.blocks.sFOC_main.bTypeConv.In =
        &x2cModel.blocks.sFOC_main.sHFI.bDelay.Out;

    /* Block -Vsat                                                                                                    */
    x2cModel.blocks.sFOC_main.sVoltageSaturation.b_Vsat.In =
        &x2cModel.blocks.sFOC_main.sVoltageSaturation.bVqSat_Switch.Out;

    /* Block -Vsat1                                                                                                   */
    x2cModel.blocks.sFOC_main.sVoltageSaturation.b_Vsat1.In =
        &x2cModel.blocks.sFOC_main.sVoltageSaturation.bVdSat_Switch.Out;

    /* Block Const_Vmax                                                                                               */

    /* Block TypeConv                                                                                                 */
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bTypeConv.In =
        &x2cModel.blocks.sFOC_main.bEnableVsat1.Out;

    /* Block VdSat_Switch                                                                                             */
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bVdSat_Switch.In1 =
        &x2cModel.blocks.sFOC_main.sVoltageSaturation.bVdsat.Out;
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bVdSat_Switch.Switch =
        &x2cModel.blocks.sFOC_main.sVoltageSaturation.bTypeConv.Out;
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bVdSat_Switch.In3 =
        &x2cModel.blocks.sFOC_main.sVoltageSaturation.bConst_Vmax.Out;

    /* Block Vdsat                                                                                                    */

    /* Block VqSat_Switch                                                                                             */
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bVqSat_Switch.In1 =
        &x2cModel.blocks.sFOC_main.sVoltageSaturation.bVqsat.Out;
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bVqSat_Switch.Switch =
        &x2cModel.blocks.sFOC_main.sVoltageSaturation.bTypeConv.Out;
    x2cModel.blocks.sFOC_main.sVoltageSaturation.bVqSat_Switch.In3 =
        &x2cModel.blocks.sFOC_main.sVoltageSaturation.bConst_Vmax.Out;

    /* Block Vqsat                                                                                                    */

    /* Block zConst1                                                                                                  */

    /* Block Gain                                                                                                     */
    x2cModel.blocks.bGain.In =
        &x2cModel.inports.bV_POT;

    /* Block PI                                                                                                       */
    x2cModel.blocks.bPI.In =
        &x2cModel.blocks.bSub.Out;
    x2cModel.blocks.bPI.Init =
        &x2cModel.blocks.bzConst3.Out;
    x2cModel.blocks.bPI.Enable =
        &x2cModel.blocks.bDelay.Out;

    /* Block StartOverride                                                                                            */
    x2cModel.blocks.bStartOverride.In1 =
        &x2cModel.inports.bS2;
    x2cModel.blocks.bStartOverride.In2 =
        &x2cModel.blocks.bzConst2.Out;

    /* Block Sub                                                                                                      */
    x2cModel.blocks.bSub.Plus =
        &x2cModel.blocks.bGain.Out;
    x2cModel.blocks.bSub.Minus =
        &x2cModel.blocks.bDelay1.Out;

    /* Block UseCurrCtr                                                                                               */
    x2cModel.blocks.bUseCurrCtr.In1 =
        &x2cModel.blocks.bConst_IdCmd1.Out;
    x2cModel.blocks.bUseCurrCtr.In2 =
        &x2cModel.blocks.bPI.Out;

    /* Block angleError                                                                                               */
    x2cModel.blocks.bangleError.Plus =
        &x2cModel.inports.bQEI_POS;
    x2cModel.blocks.bangleError.Minus =
        &x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.phi;

    /* Block LPF                                                                                                      */
    x2cModel.blocks.sangleErrorLpf.bLPF.In =
        &x2cModel.blocks.sangleErrorLpf.bTypeConv.Out;

    /* Block TypeConv                                                                                                 */
    x2cModel.blocks.sangleErrorLpf.bTypeConv.In =
        &x2cModel.blocks.bangleError.Out;

    /* Block TypeConv1                                                                                                */
    x2cModel.blocks.sangleErrorLpf.bTypeConv1.In =
        &x2cModel.blocks.sangleErrorLpf.bLPF.Out;

    /* Block zConst1                                                                                                  */

    /* Block zConst2                                                                                                  */

    /* Block zConst3                                                                                                  */

    /******************************************************************************************************************/
    /**                                                 Link Outports                                                **/
    /******************************************************************************************************************/
    x2cModel.outports.bCONTROL_ENABLED =
        &x2cModel.blocks.bDelay.Out;
    x2cModel.outports.sFOC_main.bEstimated_angle =
        &x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.phi;
    x2cModel.outports.sFOC_main.bEstimated_speed =
        &x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare.n;
    x2cModel.outports.bHOME_INIT =
        &x2cModel.blocks.bzConst1.Out;
    x2cModel.outports.bPWM1 =
        &x2cModel.blocks.sFOC_main.bAutoSwitch1.Out;
    x2cModel.outports.bPWM2 =
        &x2cModel.blocks.sFOC_main.bAutoSwitch2.Out;
    x2cModel.outports.bPWM3 =
        &x2cModel.blocks.sFOC_main.bAutoSwitch.Out;
    x2cModel.outports.bTHETA_ERROR =
        &x2cModel.blocks.sangleErrorLpf.bTypeConv1.Out;

    /******************************************************************************************************************/
    /**                                           Run Block Init Functions                                           **/
    /******************************************************************************************************************/
    Constant_FiP16_Init(&x2cModel.blocks.bConst_IdCmd);
    Constant_FiP16_Init(&x2cModel.blocks.bConst_IdCmd1);
    Delay_Bool_Init(&x2cModel.blocks.bDelay);
    Delay_FiP16_Init(&x2cModel.blocks.bDelay1);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sFOC_main.bAutoSwitch);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sFOC_main.bAutoSwitch1);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sFOC_main.bAutoSwitch2);
    Clarke_Park_MCHP_FiP16_Init(&x2cModel.blocks.sFOC_main.bClarke_Park_MCHP);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.bConst_FocAngle);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.bConst_IdRef);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.bConst_IqRef);
    ManualSwitch_Bool_Init(&x2cModel.blocks.sFOC_main.bDisableFOC);
    Constant_Bool_Init(&x2cModel.blocks.sFOC_main.bEnableVsat1);
    Sub_FiP16_Init(&x2cModel.blocks.sFOC_main.bFluxError);
    ForwardPath_HFI_FiP16_Init(&x2cModel.blocks.sFOC_main.bForwardPath_HFI);
    Delay_Bool_Init(&x2cModel.blocks.sFOC_main.sHFI.bDelay);
    ManualSwitch_Bool_Init(&x2cModel.blocks.sFOC_main.sHFI.bEnableHF);
    Constant_Bool_Init(&x2cModel.blocks.sFOC_main.sHFI.bEnableHFI);
    HFInjectionSquare_FiP16_Init(&x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare);
    InitPosDetect_FiP16_Init(&x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect);
    Negation_FiP16_Init(&x2cModel.blocks.sFOC_main.sHFI.bNegation1);
    Sub_FiP16_Init(&x2cModel.blocks.sFOC_main.sHFI.bSub);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.sHFI.bnInit3);
    Average_FiP16_Init(&x2cModel.blocks.sFOC_main.bIdAvg4);
    Average_FiP16_Init(&x2cModel.blocks.sFOC_main.bIqAvg4);
    Average_FiP16_Init(&x2cModel.blocks.sFOC_main.bIq_SlowAvg);
    LoopBreaker_FiP16_Init(&x2cModel.blocks.sFOC_main.bLoopBreakerSpeed1);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.sFOC_main.bOverrideAngle);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.sFOC_main.bOverrideId);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.sFOC_main.bOverrideIq);
    PILimit_FiP16_Init(&x2cModel.blocks.sFOC_main.bPI_Flux);
    PILimit_FiP16_Init(&x2cModel.blocks.sFOC_main.bPI_Torque);
    Sub_FiP16_Init(&x2cModel.blocks.sFOC_main.bTorqueError);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.sTs.bIsat1);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.sTs.bIsat2);
    PerturbationGen_FiP16_Init(&x2cModel.blocks.sFOC_main.sTs.bPerturbationGen);
    TypeConv_Bool_FiP16_Init(&x2cModel.blocks.sFOC_main.bTypeConv);
    Negation_FiP16_Init(&x2cModel.blocks.sFOC_main.sVoltageSaturation.b_Vsat);
    Negation_FiP16_Init(&x2cModel.blocks.sFOC_main.sVoltageSaturation.b_Vsat1);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.sVoltageSaturation.bConst_Vmax);
    TypeConv_Bool_FiP16_Init(&x2cModel.blocks.sFOC_main.sVoltageSaturation.bTypeConv);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sFOC_main.sVoltageSaturation.bVdSat_Switch);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.sVoltageSaturation.bVdsat);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sFOC_main.sVoltageSaturation.bVqSat_Switch);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.sVoltageSaturation.bVqsat);
    Constant_Bool_Init(&x2cModel.blocks.sFOC_main.bzConst1);
    Gain_FiP16_Init(&x2cModel.blocks.bGain);
    PI_FiP16_Init(&x2cModel.blocks.bPI);
    ManualSwitch_Bool_Init(&x2cModel.blocks.bStartOverride);
    Sub_FiP16_Init(&x2cModel.blocks.bSub);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.bUseCurrCtr);
    uSub_FiP16_Init(&x2cModel.blocks.bangleError);
    PT1_FiP32_Init(&x2cModel.blocks.sangleErrorLpf.bLPF);
    TypeConv_FiP16_32_Init(&x2cModel.blocks.sangleErrorLpf.bTypeConv);
    TypeConv_FiP32_16_Init(&x2cModel.blocks.sangleErrorLpf.bTypeConv1);
    Constant_FiP16_Init(&x2cModel.blocks.bzConst1);
    Constant_Bool_Init(&x2cModel.blocks.bzConst2);
    Constant_FiP16_Init(&x2cModel.blocks.bzConst3);
    Scope_Main_Init(&x2cScope);

    /* Initialize TableStruct tables                                                                                  */
    TableStruct->TFncTable = blockFunctionTable;
    TableStruct->TParamTable = parameterIdTable;
    TableStruct->inportParamTable = inportParamIdTable;
    TableStruct->outportParamTable = outportParamIdTable;
    TableStruct->maskParameterTable = maskParamIdTable;
}

/**********************************************************************************************************************/
/**                                            Run Block Update Functions                                            **/
/**********************************************************************************************************************/
static uint16 cnt_4 = X2C_UPDATE_4_DIVIDER - 1;
void X2C_Update(void)
{
    X2C_Update_1();
    if (cnt_4 == 0)
    {
        cnt_4 = X2C_UPDATE_4_DIVIDER;
        X2C_Update_4();
    }

    cnt_4--;
}

/* X2C_Update for blocks with 1*Ts                                                                                    */
void X2C_Update_1(void)
{
    LoopBreaker_FiP16_Update(&x2cModel.blocks.sFOC_main.bLoopBreakerSpeed1);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bOverrideId);
    PerturbationGen_FiP16_Update(&x2cModel.blocks.sFOC_main.sTs.bPerturbationGen);
    Negation_FiP16_Update(&x2cModel.blocks.sFOC_main.sHFI.bNegation1);
    Sub_FiP16_Update(&x2cModel.blocks.sFOC_main.sHFI.bSub);
    InitPosDetect_FiP16_Update(&x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bOverrideAngle);
    Clarke_Park_MCHP_FiP16_Update(&x2cModel.blocks.sFOC_main.bClarke_Park_MCHP);
    HFInjectionSquare_FiP16_Update(&x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare);
    Average_FiP16_Update(&x2cModel.blocks.sFOC_main.bIdAvg4);
    Average_FiP16_Update(&x2cModel.blocks.sFOC_main.bIqAvg4);
    Average_FiP16_Update(&x2cModel.blocks.sFOC_main.bIq_SlowAvg);
    Delay_FiP16_Update(&x2cModel.blocks.bDelay1);
    uSub_FiP16_Update(&x2cModel.blocks.bangleError);
    TypeConv_FiP16_32_Update(&x2cModel.blocks.sangleErrorLpf.bTypeConv);
    PT1_FiP32_Update(&x2cModel.blocks.sangleErrorLpf.bLPF);
    TypeConv_FiP32_16_Update(&x2cModel.blocks.sangleErrorLpf.bTypeConv1);
    ForwardPath_HFI_FiP16_Update(&x2cModel.blocks.sFOC_main.bForwardPath_HFI);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bAutoSwitch);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bAutoSwitch1);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bAutoSwitch2);
    Scope_Main_Update(&x2cScope);
}

/* X2C_Update for blocks with 4*Ts                                                                                    */
void X2C_Update_4(void)
{
    Gain_FiP16_Update(&x2cModel.blocks.bGain);
    TypeConv_Bool_FiP16_Update(&x2cModel.blocks.sFOC_main.sVoltageSaturation.bTypeConv);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.sVoltageSaturation.bVdSat_Switch);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.sVoltageSaturation.bVqSat_Switch);
    ManualSwitch_Bool_Update(&x2cModel.blocks.bStartOverride);
    Delay_Bool_Update(&x2cModel.blocks.bDelay);
    Negation_FiP16_Update(&x2cModel.blocks.sFOC_main.sVoltageSaturation.b_Vsat);
    Negation_FiP16_Update(&x2cModel.blocks.sFOC_main.sVoltageSaturation.b_Vsat1);
    ManualSwitch_Bool_Update(&x2cModel.blocks.sFOC_main.sHFI.bEnableHF);
    Delay_Bool_Update(&x2cModel.blocks.sFOC_main.sHFI.bDelay);
    ManualSwitch_Bool_Update(&x2cModel.blocks.sFOC_main.bDisableFOC);
    TypeConv_Bool_FiP16_Update(&x2cModel.blocks.sFOC_main.bTypeConv);
    Sub_FiP16_Update(&x2cModel.blocks.sFOC_main.bFluxError);
    PILimit_FiP16_Update(&x2cModel.blocks.sFOC_main.bPI_Flux);
    Sub_FiP16_Update(&x2cModel.blocks.bSub);
    PI_FiP16_Update(&x2cModel.blocks.bPI);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.bUseCurrCtr);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bOverrideIq);
    Sub_FiP16_Update(&x2cModel.blocks.sFOC_main.bTorqueError);
    PILimit_FiP16_Update(&x2cModel.blocks.sFOC_main.bPI_Torque);
}

