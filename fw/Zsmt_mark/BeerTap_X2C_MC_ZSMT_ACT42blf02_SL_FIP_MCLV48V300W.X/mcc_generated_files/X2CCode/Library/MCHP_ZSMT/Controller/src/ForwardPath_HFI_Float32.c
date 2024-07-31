/*
 * Copyright (c) {YEAR}, {ORGANIZATION_NAME}, {ORGANIZATION_WEB}
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the "{ORGANIZATION_NAME}" nor
 *     the names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "{ORGANIZATION_NAME}" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision: 1996 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "ForwardPath_HFI_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(ForwardPath_HFI_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define D 			(*pTForwardPath_HFI_Float32->Ud)
#define Q 			(*pTForwardPath_HFI_Float32->Uq)
#define DHF 			(*pTForwardPath_HFI_Float32->UdHF)
#define THETA		(*pTForwardPath_HFI_Float32->theta)

#define HF_INJECTIONPOLARITY  (pTForwardPath_HFI_Float32->HF_InjectionPolarity)

#define 	A_OUT	(pTForwardPath_HFI_Float32->Va)
#define 	B_OUT 	(pTForwardPath_HFI_Float32->Vb)
#define		C_OUT	(pTForwardPath_HFI_Float32->Vc)

#define 	V_ALPHA (pTForwardPath_HFI_Float32->Valpha)
#define		V_BETA	(pTForwardPath_HFI_Float32->Vbeta)
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void ForwardPath_HFI_Float32_Update(FORWARDPATH_HFI_FLOAT32 *pTForwardPath_HFI_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float32 sin_theta, cos_theta;
	float32 alpha, beta;
	float32 a,b,c;
 	float32 temp; 
    float32 D_temp;
	
    //HF injection
    if(HF_INJECTIONPOLARITY == 0){ //non inverting
        D_temp = D + DHF;
    }
    else{
        D_temp = D - DHF;
    }
	
/*Park_inverse*/
	cos_theta = cos ( THETA );
	sin_theta = sin ( THETA );
	
	alpha = ( D_temp * cos_theta ) - ( Q * sin_theta );
	beta  = ( D_temp * sin_theta ) + ( Q * cos_theta );
  
  	V_ALPHA = alpha ;
	V_BETA 	= beta;

/*Clark_inverse*/
	a =  alpha;		/*sqrt(3)/2 = 0.8660254*/
	b = (alpha * -0.5 ) + ( beta * 0.8660254); /* (BETA*sqrt(3)/2) - ALPHA/2 */
	c = (alpha * -0.5 ) + ( beta * -0.8660254); /* - (BETA*sqrt(3)/2) - ALPHA/2 */

/*Space vector modulation*/

	/* Calculate (MAX(A,B,C)+MIN(A,B,C))/2 */
	temp =          ( MAX ( MAX ( a , b ) , c) );
	temp = temp + ( ( MIN ( MIN ( a , b ) , c) ));
	temp = temp * 0.5;
	
	/* Calculate out = (IN-temp)*(1.1) */
    //Not inverting
	A_OUT = ( a - temp  )*1.1; 
	B_OUT = ( b - temp  )*1.1; 
	C_OUT = ( c - temp  )*1.1; 
/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void ForwardPath_HFI_Float32_Init(FORWARDPATH_HFI_FLOAT32 *pTForwardPath_HFI_Float32)
{
    pTForwardPath_HFI_Float32->ID = FORWARDPATH_HFI_FLOAT32_ID;
    pTForwardPath_HFI_Float32->Va = 0;
    pTForwardPath_HFI_Float32->Vb = 0;
    pTForwardPath_HFI_Float32->Vc = 0;
    pTForwardPath_HFI_Float32->Valpha = 0;
    pTForwardPath_HFI_Float32->Vbeta = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 ForwardPath_HFI_Float32_Load(const FORWARDPATH_HFI_FLOAT32 *pTForwardPath_HFI_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)1 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)pTForwardPath_HFI_Float32->HF_InjectionPolarity;
        *dataLength = (uint16)1;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 ForwardPath_HFI_Float32_Save(FORWARDPATH_HFI_FLOAT32 *pTForwardPath_HFI_Float32, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)1)
    {
        error = (uint8)1;
    }
    else
    {
        pTForwardPath_HFI_Float32->HF_InjectionPolarity = ((uint8)data[0]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(FORWARDPATH_HFI_FLOAT32_ISLINKED)
void* ForwardPath_HFI_Float32_GetAddress(const FORWARDPATH_HFI_FLOAT32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->Ud;
            break;
        case 2:
            addr = (void*)block->Uq;
            break;
        case 3:
            addr = (void*)block->UdHF;
            break;
        case 4:
            addr = (void*)block->theta;
            break;
        case 5:
            addr = (void*)&block->Va;
            break;
        case 6:
            addr = (void*)&block->Vb;
            break;
        case 7:
            addr = (void*)&block->Vc;
            break;
        case 8:
            addr = (void*)&block->Valpha;
            break;
        case 9:
            addr = (void*)&block->Vbeta;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
