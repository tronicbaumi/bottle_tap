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

/* USERCODE-BEGIN:ExternalModules                                                                                     */
/* USERCODE-END:ExternalModules                                                                                       */

/* Block sample time                                                                                                  */
/* bp_ts                                                                                                              */

/* Mask parameter values                                                                                              */
/* mp_HF_InjectionPolarity (String)                                                                                   */

/* USERCODE-BEGIN:Convert                                                                                             */
if (mp_HF_InjectionPolarity == "Non inverting (Add)") {
	cp_HF_InjectionPolarity = false;
} else if (mp_HF_InjectionPolarity == "Inverting (Subtract)") {
	cp_HF_InjectionPolarity = true;
} 
/* USERCODE-END:Convert                                                                                               */

/* Implementation Parameter values                                                                                    */
/* cp_HF_InjectionPolarity                                                                                            */

