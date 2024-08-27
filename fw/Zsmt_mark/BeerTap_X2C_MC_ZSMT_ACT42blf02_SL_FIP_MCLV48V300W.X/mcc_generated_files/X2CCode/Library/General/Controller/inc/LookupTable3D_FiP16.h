/*
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the "Linz Center of Mechatronics GmbH" and "LCM" nor
 *       the names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "Linz Center of Mechatronics GmbH" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2584 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: Three dimensional look-up table with selectable number of entries and trilinear interpolation */
/* USERCODE-END:Description                                                                                           */
#ifndef LOOKUPTABLE3D_FIP16_H
#define LOOKUPTABLE3D_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(LOOKUPTABLE3D_FIP16_ISLINKED)
#define LOOKUPTABLE3D_FIP16_ID ((uint16)465)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int16           *x;
    int16           *y;
    int16           *z;
    int16           Out;
const  int16        *Table;
    int8            sfrX;
    int8            sfrY;
    int8            sfrZ;
    uint16          maskX;
    uint16          maskY;
    uint16          maskZ;
    uint16          idxOffsetX;
    uint16          idxOffsetY;
    uint16          idxOffsetZ;
    uint16          sizeX;
    uint16          sizeY;
    uint16          sizeXY;
    int16           gainX;
    int16           gainY;
    int16           gainZ;
    int8            gainXsfr;
    int8            gainYsfr;
    int8            gainZsfr;
    int16           offsetX;
    int16           offsetY;
    int16           offsetZ;
    int16           minX;
    int16           maxX;
    int16           minY;
    int16           maxY;
    int16           minZ;
    int16           maxZ;
} LOOKUPTABLE3D_FIP16;
#else
typedef struct {
    uint16          ID;
    INT16_PTR       x;
    INT16_PTR       y;
    INT16_PTR       z;
    int16           Out;
const  INT16_PTR    Table;
    int8            sfrX;
    int8            sfrY;
    int8            sfrZ;
    uint16          maskX;
    uint16          maskY;
    uint16          maskZ;
    uint16          idxOffsetX;
    uint16          idxOffsetY;
    uint16          idxOffsetZ;
    uint16          sizeX;
    uint16          sizeY;
    uint16          sizeXY;
    int16           gainX;
    int16           gainY;
    int16           gainZ;
    int8            gainXsfr;
    int8            gainYsfr;
    int8            gainZsfr;
    int16           offsetX;
    int16           offsetY;
    int16           offsetZ;
    int16           minX;
    int16           maxX;
    int16           minY;
    int16           maxY;
    int16           minZ;
    int16           maxZ;
} LOOKUPTABLE3D_FIP16;
#endif

#define LOOKUPTABLE3D_FIP16_FUNCTIONS { \
    LOOKUPTABLE3D_FIP16_ID, \
    (void (*)(void*))LookupTable3D_FiP16_Update, \
    (void (*)(void*))LookupTable3D_FiP16_Init, \
    (tLoadImplementationParameter)LookupTable3D_FiP16_Load, \
    (tSaveImplementationParameter)LookupTable3D_FiP16_Save, \
    (void* (*)(const void*, uint16))LookupTable3D_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void LookupTable3D_FiP16_Update(LOOKUPTABLE3D_FIP16 *pTLookupTable3D_FiP16);
void LookupTable3D_FiP16_Init(LOOKUPTABLE3D_FIP16 *pTLookupTable3D_FiP16);
uint8 LookupTable3D_FiP16_Load(const LOOKUPTABLE3D_FIP16 *pTLookupTable3D_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 LookupTable3D_FiP16_Save(LOOKUPTABLE3D_FIP16 *pTLookupTable3D_FiP16, const uint8 data[], uint16 dataLength);
void* LookupTable3D_FiP16_GetAddress(const LOOKUPTABLE3D_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
