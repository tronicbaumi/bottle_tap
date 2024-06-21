/**
 * @file
 * @brief Model API functions.
 */
/*
 * Copyright (c) 2020, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
 * $LastChangedRevision: 2027 $
 * $LastChangedDate:: 2020-08-26 20:06:22 +0200#$
 */
#ifndef MODELFCTS_H
#define MODELFCTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Target.h"

/* public prototypes */
/**
 * @brief Updates Mask Parameters of all Conversion-on-Target (CoT) Blocks.
 *
 * This function updates (converts) the Implementation Parameters by using the currently stored Mask Parameter data from all Conversion-on-Target Blocks.
 * It backups the Mask Parameter data before each conversion attempt and restores it in case of the conversion/update fails.
 * The function does not stop on an failed update but continues to update the remaining CoT Blocks.
 *
 * @note This function is intended to be used after restoring the Mask Parameter data from external sources (e.g. EEPROM).
 *
 * @return 0 if successful
 * @return 3 if at least one Mask Parameter conversion failed
 */
uint8 updateAllBlockMaskParamData(void);
/**
 * @brief Updates Mask Parameters of a single Conversion-on-Target Block.
 *
 * This function searches for the Block in the current X2C Model Conversion-on-Target Block table.
 * If the Block was found, the function updates (converts) the Implementation Parameters by using the currently stored Mask Parameter data.
 * This function backups the current Mask Parameter and restores them in case of the conversion/update fails.
 *
 * @note This function is intended to be used after restoring the Mask Parameter data from external sources (e.g. EEPROM).
 *
 * @param[in] blockParamId Block Parameter ID
 *
 * @return 0 if successful
 * @return 1 if record was not found in the table
 * @return 3 if Mask Parameter conversion failed
 */
uint8 updateBlockMaskParamData(uint16 blockParamId);
/**
 * @brief Returns the number of Mask Parameters of a Conversion-on-Target Block.
 *
 * This function searches for the Block in the current X2C Model Conversion-on-Target Block table.
 * If the Block was found, the function returns the number of Mask Parameters of this Block from the table.
 *
 * @param[in] blockParamId Block Parameter ID
 * @param[out] mpCount Number of Mask Parameters
 *
 * @return 0 if successful
 * @return 1 if record was not found in the table
 */
uint8 getMaskParamCount(uint16 blockParamId, uint8* mpCount);
/**
 * @brief Reads Mask Parameter data into buffer.
 *
 * This function searches for the Mask Parameter in the current X2C Model.
 * If the Mask Parameter record was found, the function copies the Mask Parameter data into the data buffer.
 *
 * @param[in] blockParamId Block Parameter ID
 * @param[in] maskParamId Mask Parameter ID
 * @param[out] buffer Mask Parameter data
 *
 * @return 0 if successful
 * @return 1 if Mask Parameter record was not found in Model
 * @return 2 if invalid Mask Parameter data type
 */
uint8 readMaskParamData(uint16 blockParamId, uint8 maskParamId, float64* buffer);
/**
 * @brief Writes Mask Parameter data from buffer.
 *
 * This function searches for the Mask Parameter in the current X2C Model.
 * If the Mask Parameter record was found, the function copies the data into the Mask Parameter data and updates (converts)
 * the Implementation Parameters by using the currently stored Mask Parameter data.
 *
 * @param[in] blockParamId Block Parameter ID
 * @param[in] maskParamId Mask Parameter ID
 * @param[in] buffer Mask Parameter data
 *
 * @return 0 if successful
 * @return 1 if Mask Parameter record was not found in Model
 * @return 2 if invalid Mask Parameter data type
 * @return 3 if Mask Parameter conversion failed
 */
uint8 writeMaskParamData(uint16 blockParamId, uint8 maskParamId, float64* buffer);

#ifdef __cplusplus
}
#endif

#endif
