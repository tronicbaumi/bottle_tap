// This file was generated by createCFunction.sci on 10-08-2023 12:11

// Computational function for X2C block HFInjectionSquare

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
#include <HFInjectionSquare_FiP16.h>
#include <HFInjectionSquare_FiP16.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_HFInjectionS_FiP16_C(scicos_block* block, scicos_flag flag);
static void x2c_HFInjectionS_FiP16_C__OutputUpdate(scicos_block* block);
static void x2c_HFInjectionS_FiP16_C__StateUpdate(scicos_block* block);
static void x2c_HFInjectionS_FiP16_C__Initialization(scicos_block* block);
static void x2c_HFInjectionS_FiP16_C__Ending(scicos_block* block);


void x2c_HFInjectionS_FiP16_C(scicos_block* block, scicos_flag flag) {
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
            x2c_HFInjectionS_FiP16_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_HFInjectionS_FiP16_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_HFInjectionS_FiP16_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_HFInjectionS_FiP16_C__Ending(block);
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


static void x2c_HFInjectionS_FiP16_C__set_parameter(scicos_block* block, HFINJECTIONSQUARE_FIP16 *blockParam) {
    int *paramI;
    double *paramR;
    HFINJECTIONSQUARE_FIP16 *pTHFInjectionSquare_FiP16;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTHFInjectionSquare_FiP16 = GetWorkPtrs(block);
    blockParam->uInjAmp = (int16)paramI[0];
    blockParam->vGain = (int16)paramI[1];
    blockParam->sfrGain = (int8)paramI[2];
    blockParam->b0_torque = (int32)paramI[3];
    blockParam->b1_torque = (int32)paramI[4];
    blockParam->sfrb0_torque = (int8)paramI[5];
    blockParam->sfrb1_torque = (int8)paramI[6];
    blockParam->b0_speed = (int16)paramI[7];
    blockParam->b1_speed = (int16)paramI[8];
    blockParam->sfrb0_speed = (int8)paramI[9];
    blockParam->sfrb1_speed = (int8)paramI[10];
    blockParam->b0_angle = (int16)paramI[11];
    blockParam->b1_angle = (int16)paramI[12];
    blockParam->sfrb0_angle = (int8)paramI[13];
    blockParam->sfrb1_angle = (int8)paramI[14];
    blockParam->rawSpeed = (bool)paramI[15];
}


static void x2c_HFInjectionS_FiP16_C__Initialization(scicos_block* block) {
    HFINJECTIONSQUARE_FIP16 *pTHFInjectionSquare_FiP16;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_iAlpha_p;
    int16 inport_iAlpha;
    double *inport_iBeta_p;
    int16 inport_iBeta;
    double *inport_n0_p;
    int16 inport_n0;
    double *inport_phi0_p;
    int16 inport_phi0;
    double *inport_Enable_p;
    bool inport_Enable;

    /* Declaration of outports */
    double *outport_ud;
    double *outport_i_eps;
    double *outport_n;
    double *outport_phi;

    /* *** */
    pTHFInjectionSquare_FiP16 = scicos_malloc(sizeof(HFINJECTIONSQUARE_FIP16) + sizeof(int32)*5);
    GetWorkPtrs(block) = pTHFInjectionSquare_FiP16;
    x2c_HFInjectionS_FiP16_C__set_parameter(block, pTHFInjectionSquare_FiP16);

    /* Assignment of inports */
    inport_iAlpha_p = GetInPortPtrs(block, 1);
    inport_iAlpha = convert_double_to_Q15(*inport_iAlpha_p);
    pTHFInjectionSquare_FiP16->iAlpha = &inport_iAlpha;
    inport_iBeta_p = GetInPortPtrs(block, 2);
    inport_iBeta = convert_double_to_Q15(*inport_iBeta_p);
    pTHFInjectionSquare_FiP16->iBeta = &inport_iBeta;
    inport_n0_p = GetInPortPtrs(block, 3);
    inport_n0 = convert_double_to_Q15(*inport_n0_p);
    pTHFInjectionSquare_FiP16->n0 = &inport_n0;
    inport_phi0_p = GetInPortPtrs(block, 4);
    inport_phi0 = convert_double_to_Q15(*inport_phi0_p);
    pTHFInjectionSquare_FiP16->phi0 = &inport_phi0;
    inport_Enable_p = GetInPortPtrs(block, 5);
    inport_Enable = convert_double_to_bool(*inport_Enable_p);
    pTHFInjectionSquare_FiP16->Enable = &inport_Enable;

    /* Assignment of parameter arrays */
    arrayStart = 0;
    pTHFInjectionSquare_FiP16->iyArr = (int32*)((int8*)(pTHFInjectionSquare_FiP16 + 1) + arrayStart);
    arrayStart = arrayStart + sizeof(int32)*5;

    /* Initialization */
    HFInjectionSquare_FiP16_Init(pTHFInjectionSquare_FiP16);

    /* Assignment of outports */
    outport_ud = GetOutPortPtrs(block, 1);
    *outport_ud = convert_Q15_to_double(pTHFInjectionSquare_FiP16->ud);
    outport_i_eps = GetOutPortPtrs(block, 2);
    *outport_i_eps = convert_Q15_to_double(pTHFInjectionSquare_FiP16->i_eps);
    outport_n = GetOutPortPtrs(block, 3);
    *outport_n = convert_Q15_to_double(pTHFInjectionSquare_FiP16->n);
    outport_phi = GetOutPortPtrs(block, 4);
    *outport_phi = convert_Q15_to_double(pTHFInjectionSquare_FiP16->phi);

    /* Update of parameter arrays */
    arrayStart = 0;
    *((int32*)(pTHFInjectionSquare_FiP16 + 1) + arrayStart) = *(pTHFInjectionSquare_FiP16->iyArr);
    arrayStart = arrayStart + sizeof(int32)*5;
}


static void x2c_HFInjectionS_FiP16_C__Ending(scicos_block* block) {
    HFINJECTIONSQUARE_FIP16 *pTHFInjectionSquare_FiP16;
    pTHFInjectionSquare_FiP16 = GetWorkPtrs(block);
    scicos_free(pTHFInjectionSquare_FiP16);
}


static void x2c_HFInjectionS_FiP16_C__StateUpdate_f(scicos_block* block) {
    HFINJECTIONSQUARE_FIP16 *pTHFInjectionSquare_FiP16;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_iAlpha_p;
    int16 inport_iAlpha;
    double *inport_iBeta_p;
    int16 inport_iBeta;
    double *inport_n0_p;
    int16 inport_n0;
    double *inport_phi0_p;
    int16 inport_phi0;
    double *inport_Enable_p;
    bool inport_Enable;

    /* Declaration of outports */
    double *outport_ud;
    double *outport_i_eps;
    double *outport_n;
    double *outport_phi;

    /* *** */
    pTHFInjectionSquare_FiP16 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_iAlpha_p = GetInPortPtrs(block, 1);
    inport_iAlpha = convert_double_to_Q15(*inport_iAlpha_p);
    pTHFInjectionSquare_FiP16->iAlpha = &inport_iAlpha;
    inport_iBeta_p = GetInPortPtrs(block, 2);
    inport_iBeta = convert_double_to_Q15(*inport_iBeta_p);
    pTHFInjectionSquare_FiP16->iBeta = &inport_iBeta;
    inport_n0_p = GetInPortPtrs(block, 3);
    inport_n0 = convert_double_to_Q15(*inport_n0_p);
    pTHFInjectionSquare_FiP16->n0 = &inport_n0;
    inport_phi0_p = GetInPortPtrs(block, 4);
    inport_phi0 = convert_double_to_Q15(*inport_phi0_p);
    pTHFInjectionSquare_FiP16->phi0 = &inport_phi0;
    inport_Enable_p = GetInPortPtrs(block, 5);
    inport_Enable = convert_double_to_bool(*inport_Enable_p);
    pTHFInjectionSquare_FiP16->Enable = &inport_Enable;

    /* Assignment of parameter arrays */
    pTHFInjectionSquare_FiP16->iyArr = (int32*)(pTHFInjectionSquare_FiP16 + 1) + arrayStart;
    arrayStart = arrayStart + sizeof(int32)*5;

    /* Update */
    HFInjectionSquare_FiP16_Update(pTHFInjectionSquare_FiP16);

    /* Assignment of outports */
    outport_ud = GetOutPortPtrs(block, 1);
    *outport_ud = convert_Q15_to_double(pTHFInjectionSquare_FiP16->ud);
    outport_i_eps = GetOutPortPtrs(block, 2);
    *outport_i_eps = convert_Q15_to_double(pTHFInjectionSquare_FiP16->i_eps);
    outport_n = GetOutPortPtrs(block, 3);
    *outport_n = convert_Q15_to_double(pTHFInjectionSquare_FiP16->n);
    outport_phi = GetOutPortPtrs(block, 4);
    *outport_phi = convert_Q15_to_double(pTHFInjectionSquare_FiP16->phi);

    /* Update of parameter arrays */
    arrayStart = 0;
    *((int32*)(pTHFInjectionSquare_FiP16 + 1) + arrayStart) = *(pTHFInjectionSquare_FiP16->iyArr);
    arrayStart = arrayStart + sizeof(int32)*5;
}


static void x2c_HFInjectionS_FiP16_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_HFInjectionS_FiP16_C__StateUpdate_f(block);
    }
}


static void x2c_HFInjectionS_FiP16_C__OutputUpdate(scicos_block* block) {
    /* Time dependency -> execute Update function and Output assignment in State Update function */
}


