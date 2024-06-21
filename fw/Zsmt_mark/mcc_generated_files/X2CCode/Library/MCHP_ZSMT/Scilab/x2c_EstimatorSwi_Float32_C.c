// This file was generated by createCFunction.sci on 10-08-2023 12:11

// Computational function for X2C block EstimatorSwitch

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
#include <EstimatorSwitch_Float32.h>
#include <EstimatorSwitch_Float32.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_EstimatorSwi_Float32_C(scicos_block* block, scicos_flag flag);
static void x2c_EstimatorSwi_Float32_C__OutputUpdate(scicos_block* block);
static void x2c_EstimatorSwi_Float32_C__StateUpdate(scicos_block* block);
static void x2c_EstimatorSwi_Float32_C__Initialization(scicos_block* block);
static void x2c_EstimatorSwi_Float32_C__Ending(scicos_block* block);


void x2c_EstimatorSwi_Float32_C(scicos_block* block, scicos_flag flag) {
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
            x2c_EstimatorSwi_Float32_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_EstimatorSwi_Float32_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_EstimatorSwi_Float32_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_EstimatorSwi_Float32_C__Ending(block);
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


static void x2c_EstimatorSwi_Float32_C__set_parameter(scicos_block* block, ESTIMATORSWITCH_FLOAT32 *blockParam) {
    int *paramI;
    double *paramR;
    ESTIMATORSWITCH_FLOAT32 *pTEstimatorSwitch_Float32;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTEstimatorSwitch_Float32 = GetWorkPtrs(block);
    blockParam->thresh_up = (float32)paramR[0];
    blockParam->thresh_down = (float32)paramR[1];
}


static void x2c_EstimatorSwi_Float32_C__Initialization(scicos_block* block) {
    ESTIMATORSWITCH_FLOAT32 *pTEstimatorSwitch_Float32;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_phi_H_p;
    float32 inport_phi_H;
    double *inport_phi_L_p;
    float32 inport_phi_L;
    double *inport_n_H_p;
    float32 inport_n_H;
    double *inport_n_L_p;
    float32 inport_n_L;

    /* Declaration of outports */
    double *outport_phi;
    double *outport_n;
    double *outport_Enable_H;
    double *outport_Enable_L;

    /* *** */
    pTEstimatorSwitch_Float32 = scicos_malloc(sizeof(ESTIMATORSWITCH_FLOAT32));
    GetWorkPtrs(block) = pTEstimatorSwitch_Float32;
    x2c_EstimatorSwi_Float32_C__set_parameter(block, pTEstimatorSwitch_Float32);

    /* Assignment of inports */
    inport_phi_H_p = GetInPortPtrs(block, 1);
    inport_phi_H = convert_double_to_float32(*inport_phi_H_p);
    pTEstimatorSwitch_Float32->phi_H = &inport_phi_H;
    inport_phi_L_p = GetInPortPtrs(block, 2);
    inport_phi_L = convert_double_to_float32(*inport_phi_L_p);
    pTEstimatorSwitch_Float32->phi_L = &inport_phi_L;
    inport_n_H_p = GetInPortPtrs(block, 3);
    inport_n_H = convert_double_to_float32(*inport_n_H_p);
    pTEstimatorSwitch_Float32->n_H = &inport_n_H;
    inport_n_L_p = GetInPortPtrs(block, 4);
    inport_n_L = convert_double_to_float32(*inport_n_L_p);
    pTEstimatorSwitch_Float32->n_L = &inport_n_L;

    /* Assignment of parameter arrays */
    arrayStart = 0;

    /* Initialization */
    EstimatorSwitch_Float32_Init(pTEstimatorSwitch_Float32);

    /* Assignment of outports */
    outport_phi = GetOutPortPtrs(block, 1);
    *outport_phi = convert_float32_to_double(pTEstimatorSwitch_Float32->phi);
    outport_n = GetOutPortPtrs(block, 2);
    *outport_n = convert_float32_to_double(pTEstimatorSwitch_Float32->n);
    outport_Enable_H = GetOutPortPtrs(block, 3);
    *outport_Enable_H = convert_bool_to_double(pTEstimatorSwitch_Float32->Enable_H);
    outport_Enable_L = GetOutPortPtrs(block, 4);
    *outport_Enable_L = convert_bool_to_double(pTEstimatorSwitch_Float32->Enable_L);

    /* Update of parameter arrays */
    arrayStart = 0;
}


static void x2c_EstimatorSwi_Float32_C__Ending(scicos_block* block) {
    ESTIMATORSWITCH_FLOAT32 *pTEstimatorSwitch_Float32;
    pTEstimatorSwitch_Float32 = GetWorkPtrs(block);
    scicos_free(pTEstimatorSwitch_Float32);
}


static void x2c_EstimatorSwi_Float32_C__StateUpdate_f(scicos_block* block) {
    ESTIMATORSWITCH_FLOAT32 *pTEstimatorSwitch_Float32;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_phi_H_p;
    float32 inport_phi_H;
    double *inport_phi_L_p;
    float32 inport_phi_L;
    double *inport_n_H_p;
    float32 inport_n_H;
    double *inport_n_L_p;
    float32 inport_n_L;

    /* Declaration of outports */
    double *outport_phi;
    double *outport_n;
    double *outport_Enable_H;
    double *outport_Enable_L;

    /* *** */
    pTEstimatorSwitch_Float32 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_phi_H_p = GetInPortPtrs(block, 1);
    inport_phi_H = convert_double_to_float32(*inport_phi_H_p);
    pTEstimatorSwitch_Float32->phi_H = &inport_phi_H;
    inport_phi_L_p = GetInPortPtrs(block, 2);
    inport_phi_L = convert_double_to_float32(*inport_phi_L_p);
    pTEstimatorSwitch_Float32->phi_L = &inport_phi_L;
    inport_n_H_p = GetInPortPtrs(block, 3);
    inport_n_H = convert_double_to_float32(*inport_n_H_p);
    pTEstimatorSwitch_Float32->n_H = &inport_n_H;
    inport_n_L_p = GetInPortPtrs(block, 4);
    inport_n_L = convert_double_to_float32(*inport_n_L_p);
    pTEstimatorSwitch_Float32->n_L = &inport_n_L;

    /* Assignment of parameter arrays */

    /* Update */
    EstimatorSwitch_Float32_Update(pTEstimatorSwitch_Float32);

    /* Assignment of outports */
    outport_phi = GetOutPortPtrs(block, 1);
    *outport_phi = convert_float32_to_double(pTEstimatorSwitch_Float32->phi);
    outport_n = GetOutPortPtrs(block, 2);
    *outport_n = convert_float32_to_double(pTEstimatorSwitch_Float32->n);
    outport_Enable_H = GetOutPortPtrs(block, 3);
    *outport_Enable_H = convert_bool_to_double(pTEstimatorSwitch_Float32->Enable_H);
    outport_Enable_L = GetOutPortPtrs(block, 4);
    *outport_Enable_L = convert_bool_to_double(pTEstimatorSwitch_Float32->Enable_L);

    /* Update of parameter arrays */
    arrayStart = 0;
}


static void x2c_EstimatorSwi_Float32_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_EstimatorSwi_Float32_C__StateUpdate_f(block);
    }
}


static void x2c_EstimatorSwi_Float32_C__OutputUpdate(scicos_block* block) {
    /* Time dependency -> execute Update function and Output assignment in State Update function */
}


