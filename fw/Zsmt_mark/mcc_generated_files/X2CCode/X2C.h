/**
 * @file
 * @brief Generated model file.
 * 
 * Date:  2024-06-25 17:03
 * 
 * X2C-Version: 6.4.3142
 * X2C-Edition: Free
 */
/* This file is part of X2C. http://x2c.lcm.at/                                                                       */

/* Model: MC_FOC_ZSMT_FIP_dsPIC33CK_POWERTOOL                                                                         */
/* Date:  2024-06-25 17:03                                                                                            */

/* X2C-Version: 6.4.3142                                                                                              */
/* X2C-Edition: Free                                                                                                  */

#ifndef X2C_H
#define X2C_H

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************************************************************/
/**     Includes                                                                                                     **/
/**********************************************************************************************************************/
/* Common includes                                                                                                    */
#include "Constant_Bool.h"
#include "Gain_FiP16.h"
#include "TypeConv_Bool_FiP16.h"
#include "TypeConv_FiP32_16.h"
#include "Sub_FiP16.h"
#include "Clarke_Park_MCHP_FiP16.h"
#include "Negation_FiP16.h"
#include "Average_FiP16.h"
#include "PerturbationGen_FiP16.h"
#include "Delay_Bool.h"
#include "ForwardPath_HFI_FiP16.h"
#include "LoopBreaker_FiP16.h"
#include "ManualSwitch_FiP16.h"
#include "Delay_FiP16.h"
#include "TypeConv_FiP16_32.h"
#include "Constant_FiP16.h"
#include "PT1_FiP32.h"
#include "uSub_FiP16.h"
#include "ManualSwitch_Bool.h"
#include "PI_FiP16.h"
#include "PILimit_FiP16.h"
#include "AutoSwitch_FiP16.h"
#include "InitPosDetect_FiP16.h"
#include "HFInjectionSquare_FiP16.h"
#include "Scope_Main.h"
#include "CommonFcts.h"

/**********************************************************************************************************************/
/**     Defines                                                                                                      **/
/**********************************************************************************************************************/
#define FUNCTIONS \
    CONSTANT_BOOL_FUNCTIONS , \
    GAIN_FIP16_FUNCTIONS , \
    TYPECONV_BOOL_FIP16_FUNCTIONS , \
    TYPECONV_FIP32_16_FUNCTIONS , \
    SUB_FIP16_FUNCTIONS , \
    CLARKE_PARK_MCHP_FIP16_FUNCTIONS , \
    NEGATION_FIP16_FUNCTIONS , \
    AVERAGE_FIP16_FUNCTIONS , \
    PERTURBATIONGEN_FIP16_FUNCTIONS , \
    DELAY_BOOL_FUNCTIONS , \
    FORWARDPATH_HFI_FIP16_FUNCTIONS , \
    LOOPBREAKER_FIP16_FUNCTIONS , \
    MANUALSWITCH_FIP16_FUNCTIONS , \
    DELAY_FIP16_FUNCTIONS , \
    TYPECONV_FIP16_32_FUNCTIONS , \
    CONSTANT_FIP16_FUNCTIONS , \
    PT1_FIP32_FUNCTIONS , \
    USUB_FIP16_FUNCTIONS , \
    MANUALSWITCH_BOOL_FUNCTIONS , \
    PI_FIP16_FUNCTIONS , \
    PILIMIT_FIP16_FUNCTIONS , \
    AUTOSWITCH_FIP16_FUNCTIONS , \
    INITPOSDETECT_FIP16_FUNCTIONS , \
    HFINJECTIONSQUARE_FIP16_FUNCTIONS , \
    SCOPE_MAIN_FUNCTIONS

#define PARAMETER_TABLE \
    { 1U, &x2cModel.blocks.bConst_IdCmd } , \
    { 2U, &x2cModel.blocks.bConst_IdCmd1 } , \
    { 3U, &x2cModel.blocks.bDelay } , \
    { 4U, &x2cModel.blocks.bDelay1 } , \
    { 5U, &x2cModel.blocks.sFOC_main.bAutoSwitch } , \
    { 6U, &x2cModel.blocks.sFOC_main.bAutoSwitch1 } , \
    { 7U, &x2cModel.blocks.sFOC_main.bAutoSwitch2 } , \
    { 8U, &x2cModel.blocks.sFOC_main.bClarke_Park_MCHP } , \
    { 9U, &x2cModel.blocks.sFOC_main.bConst_FocAngle } , \
    { 10U, &x2cModel.blocks.sFOC_main.bConst_IdRef } , \
    { 11U, &x2cModel.blocks.sFOC_main.bConst_IqRef } , \
    { 12U, &x2cModel.blocks.sFOC_main.bDisableFOC } , \
    { 13U, &x2cModel.blocks.sFOC_main.bEnableVsat1 } , \
    { 14U, &x2cModel.blocks.sFOC_main.bFluxError } , \
    { 15U, &x2cModel.blocks.sFOC_main.bForwardPath_HFI } , \
    { 16U, &x2cModel.blocks.sFOC_main.sHFI.bDelay } , \
    { 17U, &x2cModel.blocks.sFOC_main.sHFI.bEnableHF } , \
    { 18U, &x2cModel.blocks.sFOC_main.sHFI.bEnableHFI } , \
    { 19U, &x2cModel.blocks.sFOC_main.sHFI.bHFInjectionSquare } , \
    { 20U, &x2cModel.blocks.sFOC_main.sHFI.bInitPosDetect } , \
    { 21U, &x2cModel.blocks.sFOC_main.sHFI.bNegation1 } , \
    { 22U, &x2cModel.blocks.sFOC_main.sHFI.bSub } , \
    { 23U, &x2cModel.blocks.sFOC_main.sHFI.bnInit3 } , \
    { 24U, &x2cModel.blocks.sFOC_main.bIdAvg4 } , \
    { 25U, &x2cModel.blocks.sFOC_main.bIqAvg4 } , \
    { 26U, &x2cModel.blocks.sFOC_main.bIq_SlowAvg } , \
    { 27U, &x2cModel.blocks.sFOC_main.bLoopBreakerSpeed1 } , \
    { 28U, &x2cModel.blocks.sFOC_main.bOverrideAngle } , \
    { 29U, &x2cModel.blocks.sFOC_main.bOverrideId } , \
    { 30U, &x2cModel.blocks.sFOC_main.bOverrideIq } , \
    { 31U, &x2cModel.blocks.sFOC_main.bPI_Flux } , \
    { 32U, &x2cModel.blocks.sFOC_main.bPI_Torque } , \
    { 33U, &x2cModel.blocks.sFOC_main.bTorqueError } , \
    { 34U, &x2cModel.blocks.sFOC_main.sTs.bIsat1 } , \
    { 35U, &x2cModel.blocks.sFOC_main.sTs.bIsat2 } , \
    { 36U, &x2cModel.blocks.sFOC_main.sTs.bPerturbationGen } , \
    { 37U, &x2cModel.blocks.sFOC_main.bTypeConv } , \
    { 38U, &x2cModel.blocks.sFOC_main.sVoltageSaturation.b_Vsat } , \
    { 39U, &x2cModel.blocks.sFOC_main.sVoltageSaturation.b_Vsat1 } , \
    { 40U, &x2cModel.blocks.sFOC_main.sVoltageSaturation.bConst_Vmax } , \
    { 41U, &x2cModel.blocks.sFOC_main.sVoltageSaturation.bTypeConv } , \
    { 42U, &x2cModel.blocks.sFOC_main.sVoltageSaturation.bVdSat_Switch } , \
    { 43U, &x2cModel.blocks.sFOC_main.sVoltageSaturation.bVdsat } , \
    { 44U, &x2cModel.blocks.sFOC_main.sVoltageSaturation.bVqSat_Switch } , \
    { 45U, &x2cModel.blocks.sFOC_main.sVoltageSaturation.bVqsat } , \
    { 46U, &x2cModel.blocks.sFOC_main.bzConst1 } , \
    { 47U, &x2cModel.blocks.bGain } , \
    { 48U, &x2cModel.blocks.bPI } , \
    { 49U, &x2cModel.blocks.bStartOverride } , \
    { 50U, &x2cModel.blocks.bSub } , \
    { 51U, &x2cModel.blocks.bUseCurrCtr } , \
    { 52U, &x2cModel.blocks.bangleError } , \
    { 53U, &x2cModel.blocks.sangleErrorLpf.bLPF } , \
    { 54U, &x2cModel.blocks.sangleErrorLpf.bTypeConv } , \
    { 55U, &x2cModel.blocks.sangleErrorLpf.bTypeConv1 } , \
    { 56U, &x2cModel.blocks.bzConst1 } , \
    { 57U, &x2cModel.blocks.bzConst2 } , \
    { 58U, &x2cModel.blocks.bzConst3 } , \
    { 81U, &x2cScope }

#define INPORT_PARAMID_TABLE \
    { 59U, 2U, &x2cModel.inports.bCPU_LOAD } , \
    { 60U, 2U, &x2cModel.inports.bHall_state } , \
    { 61U, 2U, &x2cModel.inports.bI_a } , \
    { 62U, 2U, &x2cModel.inports.bI_b } , \
    { 63U, 2U, &x2cModel.inports.bI_sum } , \
    { 64U, 2U, &x2cModel.inports.bQEI_POS } , \
    { 65U, 2U, &x2cModel.inports.bQEI_VEL } , \
    { 66U, 1U, &x2cModel.inports.bS2 } , \
    { 67U, 1U, &x2cModel.inports.bS3 } , \
    { 68U, 2U, &x2cModel.inports.bV_DCLINK } , \
    { 69U, 2U, &x2cModel.inports.bV_POT } , \
    { 70U, 2U, &x2cModel.inports.bVa } , \
    { 71U, 2U, &x2cModel.inports.bVb } , \
    { 72U, 2U, &x2cModel.inports.bVc } 

#define OUTPORT_PARAMID_TABLE \
    { 73U, 1U, &x2cModel.outports.bCONTROL_ENABLED } , \
    { 74U, 2U, &x2cModel.outports.sFOC_main.bEstimated_angle } , \
    { 75U, 2U, &x2cModel.outports.sFOC_main.bEstimated_speed } , \
    { 76U, 2U, &x2cModel.outports.bHOME_INIT } , \
    { 77U, 2U, &x2cModel.outports.bPWM1 } , \
    { 78U, 2U, &x2cModel.outports.bPWM2 } , \
    { 79U, 2U, &x2cModel.outports.bPWM3 } , \
    { 80U, 2U, &x2cModel.outports.bTHETA_ERROR } 


/**********************************************************************************************************************/
/**                                            Model structure definition                                            **/
/**********************************************************************************************************************/
struct x2cModel {
/*  Control Blocks                                                                                                    */
    struct {
/*      Sub-system FOC_main                                                                                           */
        struct {
/*          Sub-system HFI                                                                                            */
            struct {
                DELAY_BOOL bDelay;
                MANUALSWITCH_BOOL bEnableHF;
                CONSTANT_BOOL bEnableHFI;
                HFINJECTIONSQUARE_FIP16 bHFInjectionSquare;
                INITPOSDETECT_FIP16 bInitPosDetect;
                NEGATION_FIP16 bNegation1;
                SUB_FIP16 bSub;
                CONSTANT_FIP16 bnInit3;
            } sHFI;
/*          Sub-system Ts                                                                                             */
            struct {
                CONSTANT_FIP16 bIsat1;
                CONSTANT_FIP16 bIsat2;
                PERTURBATIONGEN_FIP16 bPerturbationGen;
            } sTs;
/*          Sub-system VoltageSaturation                                                                              */
            struct {
                NEGATION_FIP16 b_Vsat;
                NEGATION_FIP16 b_Vsat1;
                CONSTANT_FIP16 bConst_Vmax;
                TYPECONV_BOOL_FIP16 bTypeConv;
                AUTOSWITCH_FIP16 bVdSat_Switch;
                CONSTANT_FIP16 bVdsat;
                AUTOSWITCH_FIP16 bVqSat_Switch;
                CONSTANT_FIP16 bVqsat;
            } sVoltageSaturation;
            AUTOSWITCH_FIP16 bAutoSwitch;
            AUTOSWITCH_FIP16 bAutoSwitch1;
            AUTOSWITCH_FIP16 bAutoSwitch2;
            CLARKE_PARK_MCHP_FIP16 bClarke_Park_MCHP;
            CONSTANT_FIP16 bConst_FocAngle;
            CONSTANT_FIP16 bConst_IdRef;
            CONSTANT_FIP16 bConst_IqRef;
            MANUALSWITCH_BOOL bDisableFOC;
            CONSTANT_BOOL bEnableVsat1;
            SUB_FIP16 bFluxError;
            FORWARDPATH_HFI_FIP16 bForwardPath_HFI;
            AVERAGE_FIP16 bIdAvg4;
            AVERAGE_FIP16 bIqAvg4;
            AVERAGE_FIP16 bIq_SlowAvg;
            LOOPBREAKER_FIP16 bLoopBreakerSpeed1;
            MANUALSWITCH_FIP16 bOverrideAngle;
            MANUALSWITCH_FIP16 bOverrideId;
            MANUALSWITCH_FIP16 bOverrideIq;
            PILIMIT_FIP16 bPI_Flux;
            PILIMIT_FIP16 bPI_Torque;
            SUB_FIP16 bTorqueError;
            TYPECONV_BOOL_FIP16 bTypeConv;
            CONSTANT_BOOL bzConst1;
        } sFOC_main;
/*      Sub-system angleErrorLpf                                                                                      */
        struct {
            PT1_FIP32 bLPF;
            TYPECONV_FIP16_32 bTypeConv;
            TYPECONV_FIP32_16 bTypeConv1;
        } sangleErrorLpf;
        CONSTANT_FIP16 bConst_IdCmd;
        CONSTANT_FIP16 bConst_IdCmd1;
        DELAY_BOOL bDelay;
        DELAY_FIP16 bDelay1;
        GAIN_FIP16 bGain;
        PI_FIP16 bPI;
        MANUALSWITCH_BOOL bStartOverride;
        SUB_FIP16 bSub;
        MANUALSWITCH_FIP16 bUseCurrCtr;
        USUB_FIP16 bangleError;
        CONSTANT_FIP16 bzConst1;
        CONSTANT_BOOL bzConst2;
        CONSTANT_FIP16 bzConst3;
    } blocks;
/*  Inports                                                                                                           */
    struct {
        int16 bCPU_LOAD;
        int16 bHall_state;
        int16 bI_a;
        int16 bI_b;
        int16 bI_sum;
        int16 bQEI_POS;
        int16 bQEI_VEL;
        bool bS2;
        bool bS3;
        int16 bV_DCLINK;
        int16 bV_POT;
        int16 bVa;
        int16 bVb;
        int16 bVc;
    } inports;
/*  Outports                                                                                                          */
    struct {
/*      Sub-system FOC_main                                                                                           */
        struct {
            int16* bEstimated_angle;
            int16* bEstimated_speed;
        } sFOC_main;
        bool* bCONTROL_ENABLED;
        int16* bHOME_INIT;
        int16* bPWM1;
        int16* bPWM2;
        int16* bPWM3;
        int16* bTHETA_ERROR;
    } outports;
};

/**********************************************************************************************************************/
/**     Externals                                                                                                    **/
/**********************************************************************************************************************/
extern struct x2cModel x2cModel;

extern const tBlockFunctions blockFunctionTable[];
extern const tParameterTable parameterIdTable[];
extern const tIoParamIdEntry inportParamIdTable[];
extern const tIoParamIdEntry outportParamIdTable[];
extern const tMaskParameterEntry maskParamIdTable[];
extern const tMaskParamExtRecord maskParamExtTable[];
extern const tMaskParamDataRecord maskParamDataTable[];

#define X2C_UPDATE_4_DIVIDER 4

/**********************************************************************************************************************/
/**     Prototypes                                                                                                   **/
/**********************************************************************************************************************/
void X2C_Init(void);
void X2C_Update(void);
void X2C_Update_1(void);
void X2C_Update_4(void);

#ifdef __cplusplus
}
#endif

#endif
