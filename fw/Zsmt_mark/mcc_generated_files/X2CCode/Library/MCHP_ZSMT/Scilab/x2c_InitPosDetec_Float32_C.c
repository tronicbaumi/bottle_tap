// This file was generated by createCFunction.sci on 10-08-2023 12:11

// Computational function for X2C block InitPosDetect

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
#include <InitPosDetect_Float32.h>
#include <InitPosDetect_Float32.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_InitPosDetec_Float32_C(scicos_block* block, scicos_flag flag);
static void x2c_InitPosDetec_Float32_C__OutputUpdate(scicos_block* block);
static void x2c_InitPosDetec_Float32_C__StateUpdate(scicos_block* block);
static void x2c_InitPosDetec_Float32_C__Initialization(scicos_block* block);
static void x2c_InitPosDetec_Float32_C__Ending(scicos_block* block);


void x2c_InitPosDetec_Float32_C(scicos_block* block, scicos_flag flag) {
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
            x2c_InitPosDetec_Float32_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_InitPosDetec_Float32_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_InitPosDetec_Float32_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_InitPosDetec_Float32_C__Ending(block);
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


static void x2c_InitPosDetec_Float32_C__set_parameter(scicos_block* block, INITPOSDETECT_FLOAT32 *blockParam) {
    int *paramI;
    double *paramR;
    INITPOSDETECT_FLOAT32 *pTInitPosDetect_Float32;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTInitPosDetect_Float32 = GetWorkPtrs(block);
    blockParam->u_pulse = (float32)paramR[0];
    blockParam->t_pulse = (int16)paramI[0];
    blockParam->t_period = (int16)paramI[1];
}


static void x2c_InitPosDetec_Float32_C__Initialization(scicos_block* block) {
    INITPOSDETECT_FLOAT32 *pTInitPosDetect_Float32;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_I_A_p;
    float32 inport_I_A;
    double *inport_I_B_p;
    float32 inport_I_B;
    double *inport_I_C_p;
    float32 inport_I_C;
    double *inport_Enable_p;
    bool inport_Enable;

    /* Declaration of outports */
    double *outport_U_A;
    double *outport_U_B;
    double *outport_U_C;
    double *outport_Ready;
    double *outport_phi0;

    /* *** */
    pTInitPosDetect_Float32 = scicos_malloc(sizeof(INITPOSDETECT_FLOAT32));
    GetWorkPtrs(block) = pTInitPosDetect_Float32;
    x2c_InitPosDetec_Float32_C__set_parameter(block, pTInitPosDetect_Float32);

    /* Assignment of inports */
    inport_I_A_p = GetInPortPtrs(block, 1);
    inport_I_A = convert_double_to_float32(*inport_I_A_p);
    pTInitPosDetect_Float32->I_A = &inport_I_A;
    inport_I_B_p = GetInPortPtrs(block, 2);
    inport_I_B = convert_double_to_float32(*inport_I_B_p);
    pTInitPosDetect_Float32->I_B = &inport_I_B;
    inport_I_C_p = GetInPortPtrs(block, 3);
    inport_I_C = convert_double_to_float32(*inport_I_C_p);
    pTInitPosDetect_Float32->I_C = &inport_I_C;
    inport_Enable_p = GetInPortPtrs(block, 4);
    inport_Enable = convert_double_to_bool(*inport_Enable_p);
    pTInitPosDetect_Float32->Enable = &inport_Enable;

    /* Assignment of parameter arrays */
    arrayStart = 0;

    /* Initialization */
    InitPosDetect_Float32_Init(pTInitPosDetect_Float32);

    /* Assignment of outports */
    outport_U_A = GetOutPortPtrs(block, 1);
    *outport_U_A = convert_float32_to_double(pTInitPosDetect_Float32->U_A);
    outport_U_B = GetOutPortPtrs(block, 2);
    *outport_U_B = convert_float32_to_double(pTInitPosDetect_Float32->U_B);
    outport_U_C = GetOutPortPtrs(block, 3);
    *outport_U_C = convert_float32_to_double(pTInitPosDetect_Float32->U_C);
    outport_Ready = GetOutPortPtrs(block, 4);
    *outport_Ready = convert_bool_to_double(pTInitPosDetect_Float32->Ready);
    outport_phi0 = GetOutPortPtrs(block, 5);
    *outport_phi0 = convert_float32_to_double(pTInitPosDetect_Float32->phi0);

    /* Update of parameter arrays */
    arrayStart = 0;
}


static void x2c_InitPosDetec_Float32_C__Ending(scicos_block* block) {
    INITPOSDETECT_FLOAT32 *pTInitPosDetect_Float32;
    pTInitPosDetect_Float32 = GetWorkPtrs(block);
    scicos_free(pTInitPosDetect_Float32);
}


static void x2c_InitPosDetec_Float32_C__StateUpdate_f(scicos_block* block) {
    INITPOSDETECT_FLOAT32 *pTInitPosDetect_Float32;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_I_A_p;
    float32 inport_I_A;
    double *inport_I_B_p;
    float32 inport_I_B;
    double *inport_I_C_p;
    float32 inport_I_C;
    double *inport_Enable_p;
    bool inport_Enable;

    /* Declaration of outports */
    double *outport_U_A;
    double *outport_U_B;
    double *outport_U_C;
    double *outport_Ready;
    double *outport_phi0;

    /* *** */
    pTInitPosDetect_Float32 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_I_A_p = GetInPortPtrs(block, 1);
    inport_I_A = convert_double_to_float32(*inport_I_A_p);
    pTInitPosDetect_Float32->I_A = &inport_I_A;
    inport_I_B_p = GetInPortPtrs(block, 2);
    inport_I_B = convert_double_to_float32(*inport_I_B_p);
    pTInitPosDetect_Float32->I_B = &inport_I_B;
    inport_I_C_p = GetInPortPtrs(block, 3);
    inport_I_C = convert_double_to_float32(*inport_I_C_p);
    pTInitPosDetect_Float32->I_C = &inport_I_C;
    inport_Enable_p = GetInPortPtrs(block, 4);
    inport_Enable = convert_double_to_bool(*inport_Enable_p);
    pTInitPosDetect_Float32->Enable = &inport_Enable;

    /* Assignment of parameter arrays */

    /* Update */
    InitPosDetect_Float32_Update(pTInitPosDetect_Float32);

    /* Assignment of outports */
    outport_U_A = GetOutPortPtrs(block, 1);
    *outport_U_A = convert_float32_to_double(pTInitPosDetect_Float32->U_A);
    outport_U_B = GetOutPortPtrs(block, 2);
    *outport_U_B = convert_float32_to_double(pTInitPosDetect_Float32->U_B);
    outport_U_C = GetOutPortPtrs(block, 3);
    *outport_U_C = convert_float32_to_double(pTInitPosDetect_Float32->U_C);
    outport_Ready = GetOutPortPtrs(block, 4);
    *outport_Ready = convert_bool_to_double(pTInitPosDetect_Float32->Ready);
    outport_phi0 = GetOutPortPtrs(block, 5);
    *outport_phi0 = convert_float32_to_double(pTInitPosDetect_Float32->phi0);

    /* Update of parameter arrays */
    arrayStart = 0;
}


static void x2c_InitPosDetec_Float32_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_InitPosDetec_Float32_C__StateUpdate_f(block);
    }
}


static void x2c_InitPosDetec_Float32_C__OutputUpdate(scicos_block* block) {
    /* Time dependency -> execute Update function and Output assignment in State Update function */
}


