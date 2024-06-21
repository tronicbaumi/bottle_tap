// This file was generated by createCFunction.sci on 10-08-2023 12:11

// Computational function for X2C block SquareInj_Slow_Modell

#define SCILAB_SIM_FILE /* mark this file as Scilab simulation file */

/* include Scicos / Xcos headers */
#include <scicos.h>
#include <scicos_block4.h>
#include <scicos_malloc.h>
#include <scicos_free.h>
#include <Simulation_PortConversion.h>
//#define DEBUG // uncomment to enable debugging
#ifdef DEBUG
    #include <stdio.h>
#endif

/* include block implementation */
#include <SquareInj_Slow_Modell_FiP16.h>
#include <SquareInj_Slow_Modell_FiP16.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_SquareInj_Slow_FiP16_C(scicos_block* block, scicos_flag flag);
static void x2c_SquareInj_Slow_FiP16_C__OutputUpdate(scicos_block* block);
static void x2c_SquareInj_Slow_FiP16_C__StateUpdate(scicos_block* block);
static void x2c_SquareInj_Slow_FiP16_C__Initialization(scicos_block* block);
static void x2c_SquareInj_Slow_FiP16_C__Ending(scicos_block* block);


void x2c_SquareInj_Slow_FiP16_C(scicos_block* block, scicos_flag flag) {
    /*
     * This function will be called by Xcos
     */
    switch (flag) {
        case DerivativeState:  /* 0 */
        {
            break;
        }
        case OutputUpdate:     /* 1 */
        {
            x2c_SquareInj_Slow_FiP16_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_SquareInj_Slow_FiP16_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_SquareInj_Slow_FiP16_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_SquareInj_Slow_FiP16_C__Ending(block);
            break;
        }
        case ReInitialization: /* 6 */
        {
            break;
        }
        case ZeroCrossing:     /* 9 */
        {
           break;
        }
        default:     /* ContinousPropertiesUpdate (v5.5.x) Jacobian (v5.5.x) or Residute (v5.4.1) or something else */
        {
           break;
        }
    }
}


static void x2c_SquareInj_Slow_FiP16_C__set_parameter(scicos_block* block, SQUAREINJ_SLOW_MODELL_FIP16 *blockParam) {
    int *paramI;
    double *paramR;
    SQUAREINJ_SLOW_MODELL_FIP16 *pTSquareInj_Slow_Modell_FiP16;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTSquareInj_Slow_Modell_FiP16 = GetWorkPtrs(block);
    blockParam->b0 = (int32)paramI[0];
    blockParam->b1 = (int32)paramI[1];
    blockParam->sfrb0 = (int8)paramI[2];
    blockParam->sfrb1 = (int8)paramI[3];
    blockParam->a0_PT1 = (int16)paramI[4];
    blockParam->b0_PT1 = (int16)paramI[5];
    blockParam->b1_PT1 = (int16)paramI[6];
    blockParam->sfra_PT1 = (int16)paramI[7];
    blockParam->sfrb_PT1 = (int16)paramI[8];
    blockParam->dphiOld = (int16)paramI[9];
    blockParam->b0_uI = (int16)paramI[10];
    blockParam->sfr_uI = (int16)paramI[11];
    blockParam->i_old_uI = (int32)paramI[12];
    blockParam->b0_I = (int16)paramI[13];
    blockParam->sfr_I = (int16)paramI[14];
    blockParam->i_old_I = (int32)paramI[15];
    blockParam->rawSpeed = (int8)paramI[16];
    blockParam->vGain = (int16)paramI[17];
    blockParam->sfrGain = (int16)paramI[18];
    blockParam->b1_I = (int16)paramI[19];
    blockParam->b1_uI = (int16)paramI[20];
    blockParam->sfrb1_I = (int16)paramI[21];
    blockParam->sfrb1_uI = (int16)paramI[22];
}


static void x2c_SquareInj_Slow_FiP16_C__Initialization(scicos_block* block) {
    SQUAREINJ_SLOW_MODELL_FIP16 *pTSquareInj_Slow_Modell_FiP16;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_dphi_p;
    int16 inport_dphi;
    double *inport_phi0_p;
    int16 inport_phi0;
    double *inport_n0_p;
    int16 inport_n0;
    double *inport_Enable_p;
    bool inport_Enable;

    /* Declaration of outports */
    double *outport_phi;
    double *outport_Sync;
    double *outport_speed;

    /* *** */
    pTSquareInj_Slow_Modell_FiP16 = scicos_malloc(sizeof(SQUAREINJ_SLOW_MODELL_FIP16));
    GetWorkPtrs(block) = pTSquareInj_Slow_Modell_FiP16;
    x2c_SquareInj_Slow_FiP16_C__set_parameter(block, pTSquareInj_Slow_Modell_FiP16);

    /* Assignment of inports */
    inport_dphi_p = GetInPortPtrs(block, 1);
    inport_dphi = convert_double_to_Q15(*inport_dphi_p);
    pTSquareInj_Slow_Modell_FiP16->dphi = &inport_dphi;
    inport_phi0_p = GetInPortPtrs(block, 2);
    inport_phi0 = convert_double_to_Q15(*inport_phi0_p);
    pTSquareInj_Slow_Modell_FiP16->phi0 = &inport_phi0;
    inport_n0_p = GetInPortPtrs(block, 3);
    inport_n0 = convert_double_to_Q15(*inport_n0_p);
    pTSquareInj_Slow_Modell_FiP16->n0 = &inport_n0;
    inport_Enable_p = GetInPortPtrs(block, 4);
    inport_Enable = convert_double_to_bool(*inport_Enable_p);
    pTSquareInj_Slow_Modell_FiP16->Enable = &inport_Enable;

    /* Assignment of parameter arrays */
    arrayStart = 0;

    /* Initialization */
    SquareInj_Slow_Modell_FiP16_Init(pTSquareInj_Slow_Modell_FiP16);

    /* Assignment of outports */
    outport_phi = GetOutPortPtrs(block, 1);
    *outport_phi = convert_Q15_to_double(pTSquareInj_Slow_Modell_FiP16->phi);
    outport_Sync = GetOutPortPtrs(block, 2);
    *outport_Sync = convert_Q15_to_double(pTSquareInj_Slow_Modell_FiP16->Sync);
    outport_speed = GetOutPortPtrs(block, 3);
    *outport_speed = convert_Q15_to_double(pTSquareInj_Slow_Modell_FiP16->speed);

    /* Update of parameter arrays */
    arrayStart = 0;
}


static void x2c_SquareInj_Slow_FiP16_C__Ending(scicos_block* block) {
    SQUAREINJ_SLOW_MODELL_FIP16 *pTSquareInj_Slow_Modell_FiP16;
    pTSquareInj_Slow_Modell_FiP16 = GetWorkPtrs(block);
    scicos_free(pTSquareInj_Slow_Modell_FiP16);
}


static void x2c_SquareInj_Slow_FiP16_C__StateUpdate_f(scicos_block* block) {
    SQUAREINJ_SLOW_MODELL_FIP16 *pTSquareInj_Slow_Modell_FiP16;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_dphi_p;
    int16 inport_dphi;
    double *inport_phi0_p;
    int16 inport_phi0;
    double *inport_n0_p;
    int16 inport_n0;
    double *inport_Enable_p;
    bool inport_Enable;

    /* Declaration of outports */
    double *outport_phi;
    double *outport_Sync;
    double *outport_speed;

    /* *** */
    pTSquareInj_Slow_Modell_FiP16 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_dphi_p = GetInPortPtrs(block, 1);
    inport_dphi = convert_double_to_Q15(*inport_dphi_p);
    pTSquareInj_Slow_Modell_FiP16->dphi = &inport_dphi;
    inport_phi0_p = GetInPortPtrs(block, 2);
    inport_phi0 = convert_double_to_Q15(*inport_phi0_p);
    pTSquareInj_Slow_Modell_FiP16->phi0 = &inport_phi0;
    inport_n0_p = GetInPortPtrs(block, 3);
    inport_n0 = convert_double_to_Q15(*inport_n0_p);
    pTSquareInj_Slow_Modell_FiP16->n0 = &inport_n0;
    inport_Enable_p = GetInPortPtrs(block, 4);
    inport_Enable = convert_double_to_bool(*inport_Enable_p);
    pTSquareInj_Slow_Modell_FiP16->Enable = &inport_Enable;

    /* Assignment of parameter arrays */

    /* Update */
    SquareInj_Slow_Modell_FiP16_Update(pTSquareInj_Slow_Modell_FiP16);

    /* Assignment of outports */
    outport_phi = GetOutPortPtrs(block, 1);
    *outport_phi = convert_Q15_to_double(pTSquareInj_Slow_Modell_FiP16->phi);
    outport_Sync = GetOutPortPtrs(block, 2);
    *outport_Sync = convert_Q15_to_double(pTSquareInj_Slow_Modell_FiP16->Sync);
    outport_speed = GetOutPortPtrs(block, 3);
    *outport_speed = convert_Q15_to_double(pTSquareInj_Slow_Modell_FiP16->speed);

    /* Update of parameter arrays */
    arrayStart = 0;
}


static void x2c_SquareInj_Slow_FiP16_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_SquareInj_Slow_FiP16_C__StateUpdate_f(block);
    }
}


static void x2c_SquareInj_Slow_FiP16_C__OutputUpdate(scicos_block* block) {
    /* Time dependency -> execute Update function and Output assignment in State Update function */
}


