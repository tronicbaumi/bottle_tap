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
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2108 $
 * $LastChangedDate:: 2020-12-07 19:09:57 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                                                       */
/* Description: */
/* USERCODE-END:Description                                                                                                                         */

package at.lcm.x2c.library.mchp_zsmt;

import java.util.HashMap;
import java.util.Map;

import at.lcm.bu21.general.dtypes.TData;
import at.lcm.bu21.general.dtypes.TNumeric;
import at.lcm.bu21.general.dtypes.TString;
import at.lcm.communication.hardware.Serial;
import at.lcm.x2c.blocktest.ConversionOnTargetTest;
import at.lcm.x2c.blocktest.ConversionTest;
import at.lcm.x2c.blocktest.InportTest;
import at.lcm.x2c.blocktest.ParameterTest;
import at.lcm.x2c.blocktest.TestSuite;
import at.lcm.x2c.communication.protocol.Protocol;
import at.lcm.x2c.communication.protocol.ProtocolFactory;

public class Test_HFInjectionSquare_FiP32 {

    public Test_HFInjectionSquare_FiP32(Protocol protocol) throws Exception {
        /* Inport test variables start here */
        final int IT_LENGTH = 3;
        final boolean IT_DOINIT = true;
        final double IT_SAMPLETIME = 0.0;
        /* Inport: I_D */
        final double[] it_in_I_D = { 0, 0, 0 };
        /* Inport: I_Q */
        final double[] it_in_I_Q = { 0, 0, 0 };
        /* Inport: n0 */
        final double[] it_in_n0 = { 0, 0, 0 };
        /* Inport: phi0 */
        final double[] it_in_phi0 = { 0, 0, 0 };
        /* Inport: Enable */
        final double[] it_in_Enable = { 0, 0, 0 };
        /* Mask parameter: U_inj */
        final double[] it_mp_U_inj = { 0 };
        /* Mask parameter: Jp */
        final double[] it_mp_Jp = { 0 };
        /* Mask parameter: I_inj */
        final double[] it_mp_I_inj = { 0 };
        /* Mask parameter: fo */
        final double[] it_mp_fo = { 0 };
        /* Mask parameter: p */
        final double[] it_mp_p = { 0 };
        /* Mask parameter: n_max */
        final double[] it_mp_n_max = { 0 };
        /* Mask parameter: I_max */
        final double[] it_mp_I_max = { 0 };
        /* Mask parameter: U_max */
        final double[] it_mp_U_max = { 0 };
        /* Mask parameter: ts_fact */
        final double[] it_mp_ts_fact = { 0 };
        /* Mask parameter: estimation */
        final String it_mp_estimation = "Test";
        /* Mask parameter: method */
        final String it_mp_method = "Test";
        /* Outport: Ud */
        final double[] it_out_Ud = { 0, 0, 0 };
        /* Outport: I_eps */
        final double[] it_out_I_eps = { 0, 0, 0 };
        /* Outport: n */
        final double[] it_out_n = { 0, 0, 0 };
        /* Outport: phi */
        final double[] it_out_phi = { 0, 0, 0 };
        /* Outport tolerances: Ud */
        final double it_tol_Ud = Math.pow(2, -31);
        /* Outport tolerances: I_eps */
        final double it_tol_I_eps = Math.pow(2, -31);
        /* Outport tolerances: n */
        final double it_tol_n = Math.pow(2, -31);
        /* Outport tolerances: phi */
        final double it_tol_phi = Math.pow(2, -31);
        /* Inport test variables end here */

        /* Parameter test variables start here */
        final int PT_LENGTH = 3;
        final boolean PT_DOINIT = true;
        final double PT_SAMPLETIME = 0.0;
        /* Inport: I_D */
        final double pt_in_I_D = 0;
        /* Inport: I_Q */
        final double pt_in_I_Q = 0;
        /* Inport: n0 */
        final double pt_in_n0 = 0;
        /* Inport: phi0 */
        final double pt_in_phi0 = 0;
        /* Inport: Enable */
        final double pt_in_Enable = 0;
        /* Mask parameter: U_inj */
        final double[][] pt_mp_U_inj = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: Jp */
        final double[][] pt_mp_Jp = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: I_inj */
        final double[][] pt_mp_I_inj = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: fo */
        final double[][] pt_mp_fo = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: p */
        final double[][] pt_mp_p = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: n_max */
        final double[][] pt_mp_n_max = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: I_max */
        final double[][] pt_mp_I_max = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: U_max */
        final double[][] pt_mp_U_max = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: ts_fact */
        final double[][] pt_mp_ts_fact = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: estimation */
        final String[] pt_mp_estimation = { "Test", "Test", "Test" };
        /* Mask parameter: method */
        final String[] pt_mp_method = { "Test", "Test", "Test" };
        /* Outport: Ud */
        final double[] pt_out_Ud = { 0, 0, 0 };
        /* Outport: I_eps */
        final double[] pt_out_I_eps = { 0, 0, 0 };
        /* Outport: n */
        final double[] pt_out_n = { 0, 0, 0 };
        /* Outport: phi */
        final double[] pt_out_phi = { 0, 0, 0 };
        /* Outport tolerances: Ud */
        final double pt_tol_Ud = Math.pow(2, -31);
        /* Outport tolerances: I_eps */
        final double pt_tol_I_eps = Math.pow(2, -31);
        /* Outport tolerances: n */
        final double pt_tol_n = Math.pow(2, -31);
        /* Outport tolerances: phi */
        final double pt_tol_phi = Math.pow(2, -31);
        /* Parameter test variables end here */

        /* Conversion test variables start here */
        final int CT_LENGTH = 3;
        final double CT_SAMPLETIME = 1.000000e-04;
        /* Mask parameter: */
        final double[][] ct_mp_U_inj = { { 2 }, { 3 }, { 4 } };
        final double[][] ct_mp_Jp = { { 0.0010000000000000000208 }, { 0.0022999999999999999611 },
                { 0.0045000000000000005274 } };
        final double[][] ct_mp_I_inj = { { 0.2999999999999999889 }, { 0.4000000000000000222 }, { 0.5 } };
        final double[][] ct_mp_fo = { { 20 }, { 30 }, { 40 } };
        final double[][] ct_mp_p = { { 1 }, { 2 }, { 3 } };
        final double[][] ct_mp_n_max = { { 1000 }, { 1000 }, { 1000 } };
        final double[][] ct_mp_I_max = { { 10 }, { 10 }, { 10 } };
        final double[][] ct_mp_U_max = { { 5 }, { 5 }, { 5 } };
        final double[][] ct_mp_ts_fact = { { 1 }, { 1 }, { 1 } };
        final String[] ct_mp_estimation = { "less noise", "less noise", "high dynamic range" };
        final String[] ct_mp_method = { "tustin", "tustin", "zoh" };
        /* Implementation parameter: */
        final double[][] ct_cp_uInjAmp = { { 858993459 }, { 1288490189 }, { 1717986918 } };
        final double[][] ct_cp_vGain = { { 2013265920 }, { 1132462080 }, { 1610612736 } };
        final double[][] ct_cp_sfrGain = { { 28 }, { 28 }, { 29 } };
        final double[][] ct_cp_b0_torque = { { 1695585125 }, { 1233935581 }, { 1526026613 } };
        final double[][] ct_cp_b1_torque = { { 1594462115 }, { 1553553269 }, { 1423093820 } };
        final double[][] ct_cp_sfrb0_torque = { { 30 }, { 28 }, { 27 } };
        final double[][] ct_cp_sfrb1_torque = { { 24 }, { 23 }, { 22 } };
        final double[][] ct_cp_b0_speed = { { 8589935 }, { 3734754 }, { 1908874 } };
        final double[][] ct_cp_b1_speed = { { 4294967 }, { 1867377 }, { 0 } };
        final double[][] ct_cp_sfrb0_speed = { { 31 }, { 31 }, { 31 } };
        final double[][] ct_cp_sfrb1_speed = { { 31 }, { 31 }, { 31 } };
        final double[][] ct_cp_b0_angle = { { 28633115 }, { 57266231 }, { 85899346 } };
        final double[][] ct_cp_b1_angle = { { 14316558 }, { 28633115 }, { 0 } };
        final double[][] ct_cp_sfrb0_angle = { { 31 }, { 31 }, { 31 } };
        final double[][] ct_cp_sfrb1_angle = { { 31 }, { 31 }, { 31 } };
        final double[][] ct_cp_rawSpeed = { { 0 }, { 0 }, { 1 } };
        /* Implementation Parameter tolerances: uInjAmp */
        final double ct_tol_uInjAmp = 0.0;
        /* Implementation Parameter tolerances: vGain */
        final double ct_tol_vGain = 0.0;
        /* Implementation Parameter tolerances: sfrGain */
        final double ct_tol_sfrGain = 0.0;
        /* Implementation Parameter tolerances: b0_torque */
        final double ct_tol_b0_torque = 0.0;
        /* Implementation Parameter tolerances: b1_torque */
        final double ct_tol_b1_torque = 0.0;
        /* Implementation Parameter tolerances: sfrb0_torque */
        final double ct_tol_sfrb0_torque = 0.0;
        /* Implementation Parameter tolerances: sfrb1_torque */
        final double ct_tol_sfrb1_torque = 0.0;
        /* Implementation Parameter tolerances: b0_speed */
        final double ct_tol_b0_speed = 0.0;
        /* Implementation Parameter tolerances: b1_speed */
        final double ct_tol_b1_speed = 0.0;
        /* Implementation Parameter tolerances: sfrb0_speed */
        final double ct_tol_sfrb0_speed = 0.0;
        /* Implementation Parameter tolerances: sfrb1_speed */
        final double ct_tol_sfrb1_speed = 0.0;
        /* Implementation Parameter tolerances: b0_angle */
        final double ct_tol_b0_angle = 0.0;
        /* Implementation Parameter tolerances: b1_angle */
        final double ct_tol_b1_angle = 0.0;
        /* Implementation Parameter tolerances: sfrb0_angle */
        final double ct_tol_sfrb0_angle = 0.0;
        /* Implementation Parameter tolerances: sfrb1_angle */
        final double ct_tol_sfrb1_angle = 0.0;
        /* Implementation Parameter tolerances: rawSpeed */
        final double ct_tol_rawSpeed = 0.0;
        /* Conversion test variables end here */

        /* Conversion-on-Target test variables start here */
        /* ! Uses test vectors of Conversion test ! */
        /* Implementation Parameter tolerances: uInjAmp */
        final double cott_tol_uInjAmp = 100;
        /* Implementation Parameter tolerances: vGain */
        final double cott_tol_vGain = 1000;
        /* Implementation Parameter tolerances: sfrGain */
        final double cott_tol_sfrGain = 0.0;
        /* Implementation Parameter tolerances: b0_torque */
        final double cott_tol_b0_torque = 1000;
        /* Implementation Parameter tolerances: b1_torque */
        final double cott_tol_b1_torque = 1000;
        /* Implementation Parameter tolerances: sfrb0_torque */
        final double cott_tol_sfrb0_torque = 0.0;
        /* Implementation Parameter tolerances: sfrb1_torque */
        final double cott_tol_sfrb1_torque = 0.0;
        /* Implementation Parameter tolerances: b0_speed */
        final double cott_tol_b0_speed = 1;
        /* Implementation Parameter tolerances: b1_speed */
        final double cott_tol_b1_speed = 1;
        /* Implementation Parameter tolerances: sfrb0_speed */
        final double cott_tol_sfrb0_speed = 0.0;
        /* Implementation Parameter tolerances: sfrb1_speed */
        final double cott_tol_sfrb1_speed = 0.0;
        /* Implementation Parameter tolerances: b0_angle */
        final double cott_tol_b0_angle = 10;
        /* Implementation Parameter tolerances: b1_angle */
        final double cott_tol_b1_angle = 1;
        /* Implementation Parameter tolerances: sfrb0_angle */
        final double cott_tol_sfrb0_angle = 0.0;
        /* Implementation Parameter tolerances: sfrb1_angle */
        final double cott_tol_sfrb1_angle = 0.0;
        /* Implementation Parameter tolerances: rawSpeed */
        final double cott_tol_rawSpeed = 0.0;
        /* Conversion-on-Target test variables end here */

        try {
            TestSuite suite = new TestSuite(protocol, "mchp_zsmt", "HFInjectionSquare", "FiP32");

            /* INPORT TEST */
            InportTest it = new InportTest("mchp_zsmt", "HFInjectionSquare", "FiP32", protocol, IT_DOINIT);
            Map<String, TData> it_mp = new HashMap<String, TData>();
            it_mp.put("U_inj", new TNumeric(it_mp_U_inj));
            it_mp.put("Jp", new TNumeric(it_mp_Jp));
            it_mp.put("I_inj", new TNumeric(it_mp_I_inj));
            it_mp.put("fo", new TNumeric(it_mp_fo));
            it_mp.put("p", new TNumeric(it_mp_p));
            it_mp.put("n_max", new TNumeric(it_mp_n_max));
            it_mp.put("I_max", new TNumeric(it_mp_I_max));
            it_mp.put("U_max", new TNumeric(it_mp_U_max));
            it_mp.put("ts_fact", new TNumeric(it_mp_ts_fact));
            it_mp.put("estimation", new TString(it_mp_estimation));
            it_mp.put("method", new TString(it_mp_method));
            it.setMaskParameters(it_mp);
            Map<String,  Double> it_tol = new HashMap<String, Double>();
            it_tol.put("Ud", it_tol_Ud);
            it_tol.put("I_eps", it_tol_I_eps);
            it_tol.put("n", it_tol_n);
            it_tol.put("phi", it_tol_phi);
            it.setTolerances(it_tol);
            for (int i = 0; i < IT_LENGTH; i++) {
                Map<String,  TNumeric> it_in = new HashMap<String, TNumeric>();
                Map<String,  TNumeric> it_out = new HashMap<String, TNumeric>();
                it_in.put("I_D", new TNumeric(it_in_I_D[i]));
                it_in.put("I_Q", new TNumeric(it_in_I_Q[i]));
                it_in.put("n0", new TNumeric(it_in_n0[i]));
                it_in.put("phi0", new TNumeric(it_in_phi0[i]));
                it_in.put("Enable", new TNumeric(it_in_Enable[i]));
                it_out.put("Ud", new TNumeric(it_out_Ud[i]));
                it_out.put("I_eps", new TNumeric(it_out_I_eps[i]));
                it_out.put("n", new TNumeric(it_out_n[i]));
                it_out.put("phi", new TNumeric(it_out_phi[i]));
                it.addConfig(it_in, it_out);
            }
            it.setSampleTime(IT_SAMPLETIME);
            // suite.add(it);

            /* PARAMETER TEST */
            ParameterTest pt = new ParameterTest("mchp_zsmt", "HFInjectionSquare", "FiP32", protocol, PT_DOINIT);
            Map<String, TNumeric> pt_in = new HashMap<String, TNumeric>();
            pt_in.put("I_D", new TNumeric(pt_in_I_D));
            pt_in.put("I_Q", new TNumeric(pt_in_I_Q));
            pt_in.put("n0", new TNumeric(pt_in_n0));
            pt_in.put("phi0", new TNumeric(pt_in_phi0));
            pt_in.put("Enable", new TNumeric(pt_in_Enable));
            pt.setInports(pt_in);
            Map<String,  Double> pt_tol = new HashMap<String, Double>();
            pt_tol.put("Ud", pt_tol_Ud);
            pt_tol.put("I_eps", pt_tol_I_eps);
            pt_tol.put("n", pt_tol_n);
            pt_tol.put("phi", pt_tol_phi);
            pt.setTolerances(pt_tol);
            for (int i = 0; i < PT_LENGTH; i++) {
                Map<String,  TData> pt_mp = new HashMap<String, TData>();
                Map<String,  TNumeric> pt_out = new HashMap<String, TNumeric>();
                pt_mp.put("U_inj", new TNumeric(pt_mp_U_inj[i]));
                pt_mp.put("Jp", new TNumeric(pt_mp_Jp[i]));
                pt_mp.put("I_inj", new TNumeric(pt_mp_I_inj[i]));
                pt_mp.put("fo", new TNumeric(pt_mp_fo[i]));
                pt_mp.put("p", new TNumeric(pt_mp_p[i]));
                pt_mp.put("n_max", new TNumeric(pt_mp_n_max[i]));
                pt_mp.put("I_max", new TNumeric(pt_mp_I_max[i]));
                pt_mp.put("U_max", new TNumeric(pt_mp_U_max[i]));
                pt_mp.put("ts_fact", new TNumeric(pt_mp_ts_fact[i]));
                pt_mp.put("estimation", new TString(pt_mp_estimation[i]));
                pt_mp.put("method", new TString(pt_mp_method[i]));
                pt_out.put("Ud", new TNumeric(pt_out_Ud[i]));
                pt_out.put("I_eps", new TNumeric(pt_out_I_eps[i]));
                pt_out.put("n", new TNumeric(pt_out_n[i]));
                pt_out.put("phi", new TNumeric(pt_out_phi[i]));
                pt.addConfig(pt_mp, pt_out);
            }
            pt.setSampleTime(PT_SAMPLETIME);
            // suite.add(pt);

            /* CONVERSION TEST */
            ConversionTest ct = new ConversionTest("mchp_zsmt", "HFInjectionSquare", "FiP32");
            Map<String,  Double> ct_tol = new HashMap<String, Double>();
            ct_tol.put("uInjAmp", ct_tol_uInjAmp);
            ct_tol.put("vGain", ct_tol_vGain);
            ct_tol.put("sfrGain", ct_tol_sfrGain);
            ct_tol.put("b0_torque", ct_tol_b0_torque);
            ct_tol.put("b1_torque", ct_tol_b1_torque);
            ct_tol.put("sfrb0_torque", ct_tol_sfrb0_torque);
            ct_tol.put("sfrb1_torque", ct_tol_sfrb1_torque);
            ct_tol.put("b0_speed", ct_tol_b0_speed);
            ct_tol.put("b1_speed", ct_tol_b1_speed);
            ct_tol.put("sfrb0_speed", ct_tol_sfrb0_speed);
            ct_tol.put("sfrb1_speed", ct_tol_sfrb1_speed);
            ct_tol.put("b0_angle", ct_tol_b0_angle);
            ct_tol.put("b1_angle", ct_tol_b1_angle);
            ct_tol.put("sfrb0_angle", ct_tol_sfrb0_angle);
            ct_tol.put("sfrb1_angle", ct_tol_sfrb1_angle);
            ct_tol.put("rawSpeed", ct_tol_rawSpeed);
            ct.setTolerances(ct_tol);
            for (int i = 0; i < CT_LENGTH; i++) {
                Map<String, TData> ct_mp = new HashMap<String, TData>();
                Map<String, TNumeric> ct_cp = new HashMap<String, TNumeric>();
                ct_mp.put("U_inj", new TNumeric(ct_mp_U_inj[i]));
                ct_mp.put("Jp", new TNumeric(ct_mp_Jp[i]));
                ct_mp.put("I_inj", new TNumeric(ct_mp_I_inj[i]));
                ct_mp.put("fo", new TNumeric(ct_mp_fo[i]));
                ct_mp.put("p", new TNumeric(ct_mp_p[i]));
                ct_mp.put("n_max", new TNumeric(ct_mp_n_max[i]));
                ct_mp.put("I_max", new TNumeric(ct_mp_I_max[i]));
                ct_mp.put("U_max", new TNumeric(ct_mp_U_max[i]));
                ct_mp.put("ts_fact", new TNumeric(ct_mp_ts_fact[i]));
                ct_mp.put("estimation", new TString(ct_mp_estimation[i]));
                ct_mp.put("method", new TString(ct_mp_method[i]));
                ct_cp.put("uInjAmp", new TNumeric(ct_cp_uInjAmp[i]));
                ct_cp.put("vGain", new TNumeric(ct_cp_vGain[i]));
                ct_cp.put("sfrGain", new TNumeric(ct_cp_sfrGain[i]));
                ct_cp.put("b0_torque", new TNumeric(ct_cp_b0_torque[i]));
                ct_cp.put("b1_torque", new TNumeric(ct_cp_b1_torque[i]));
                ct_cp.put("sfrb0_torque", new TNumeric(ct_cp_sfrb0_torque[i]));
                ct_cp.put("sfrb1_torque", new TNumeric(ct_cp_sfrb1_torque[i]));
                ct_cp.put("b0_speed", new TNumeric(ct_cp_b0_speed[i]));
                ct_cp.put("b1_speed", new TNumeric(ct_cp_b1_speed[i]));
                ct_cp.put("sfrb0_speed", new TNumeric(ct_cp_sfrb0_speed[i]));
                ct_cp.put("sfrb1_speed", new TNumeric(ct_cp_sfrb1_speed[i]));
                ct_cp.put("b0_angle", new TNumeric(ct_cp_b0_angle[i]));
                ct_cp.put("b1_angle", new TNumeric(ct_cp_b1_angle[i]));
                ct_cp.put("sfrb0_angle", new TNumeric(ct_cp_sfrb0_angle[i]));
                ct_cp.put("sfrb1_angle", new TNumeric(ct_cp_sfrb1_angle[i]));
                ct_cp.put("rawSpeed", new TNumeric(ct_cp_rawSpeed[i]));
                ct.addConfig(ct_mp, ct_cp);
            }
            ct.setSampleTime(CT_SAMPLETIME);
            suite.add(ct);

            /* CONVERSION-ON-TARGET TEST */
            ConversionOnTargetTest cott = new ConversionOnTargetTest("mchp_zsmt", "HFInjectionSquare", "FiP32", protocol);
            Map<String,  Double> cott_tol = new HashMap<String, Double>();
            cott_tol.put("uInjAmp", cott_tol_uInjAmp);
            cott_tol.put("vGain", cott_tol_vGain);
            cott_tol.put("sfrGain", cott_tol_sfrGain);
            cott_tol.put("b0_torque", cott_tol_b0_torque);
            cott_tol.put("b1_torque", cott_tol_b1_torque);
            cott_tol.put("sfrb0_torque", cott_tol_sfrb0_torque);
            cott_tol.put("sfrb1_torque", cott_tol_sfrb1_torque);
            cott_tol.put("b0_speed", cott_tol_b0_speed);
            cott_tol.put("b1_speed", cott_tol_b1_speed);
            cott_tol.put("sfrb0_speed", cott_tol_sfrb0_speed);
            cott_tol.put("sfrb1_speed", cott_tol_sfrb1_speed);
            cott_tol.put("b0_angle", cott_tol_b0_angle);
            cott_tol.put("b1_angle", cott_tol_b1_angle);
            cott_tol.put("sfrb0_angle", cott_tol_sfrb0_angle);
            cott_tol.put("sfrb1_angle", cott_tol_sfrb1_angle);
            cott_tol.put("rawSpeed", cott_tol_rawSpeed);
            cott.setTolerances(cott_tol);
            for (int i = 0; i < CT_LENGTH; i++) {
                Map<String, TData> cott_mp = new HashMap<String, TData>();
                Map<String, TNumeric> cott_cp = new HashMap<String, TNumeric>();
                /* Uses test data of Conversion test */
                cott_mp.put("U_inj", new TNumeric(ct_mp_U_inj[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("Jp", new TNumeric(ct_mp_Jp[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("I_inj", new TNumeric(ct_mp_I_inj[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("fo", new TNumeric(ct_mp_fo[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("p", new TNumeric(ct_mp_p[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("n_max", new TNumeric(ct_mp_n_max[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("I_max", new TNumeric(ct_mp_I_max[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("U_max", new TNumeric(ct_mp_U_max[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("ts_fact", new TNumeric(ct_mp_ts_fact[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("estimation", new TString(ct_mp_estimation[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("method", new TString(ct_mp_method[i]));
                /* Use test data of Conversion test */
                cott_cp.put("uInjAmp", new TNumeric(ct_cp_uInjAmp[i]));
                /* Use test data of Conversion test */
                cott_cp.put("vGain", new TNumeric(ct_cp_vGain[i]));
                /* Use test data of Conversion test */
                cott_cp.put("sfrGain", new TNumeric(ct_cp_sfrGain[i]));
                /* Use test data of Conversion test */
                cott_cp.put("b0_torque", new TNumeric(ct_cp_b0_torque[i]));
                /* Use test data of Conversion test */
                cott_cp.put("b1_torque", new TNumeric(ct_cp_b1_torque[i]));
                /* Use test data of Conversion test */
                cott_cp.put("sfrb0_torque", new TNumeric(ct_cp_sfrb0_torque[i]));
                /* Use test data of Conversion test */
                cott_cp.put("sfrb1_torque", new TNumeric(ct_cp_sfrb1_torque[i]));
                /* Use test data of Conversion test */
                cott_cp.put("b0_speed", new TNumeric(ct_cp_b0_speed[i]));
                /* Use test data of Conversion test */
                cott_cp.put("b1_speed", new TNumeric(ct_cp_b1_speed[i]));
                /* Use test data of Conversion test */
                cott_cp.put("sfrb0_speed", new TNumeric(ct_cp_sfrb0_speed[i]));
                /* Use test data of Conversion test */
                cott_cp.put("sfrb1_speed", new TNumeric(ct_cp_sfrb1_speed[i]));
                /* Use test data of Conversion test */
                cott_cp.put("b0_angle", new TNumeric(ct_cp_b0_angle[i]));
                /* Use test data of Conversion test */
                cott_cp.put("b1_angle", new TNumeric(ct_cp_b1_angle[i]));
                /* Use test data of Conversion test */
                cott_cp.put("sfrb0_angle", new TNumeric(ct_cp_sfrb0_angle[i]));
                /* Use test data of Conversion test */
                cott_cp.put("sfrb1_angle", new TNumeric(ct_cp_sfrb1_angle[i]));
                /* Use test data of Conversion test */
                cott_cp.put("rawSpeed", new TNumeric(ct_cp_rawSpeed[i]));
                cott.addConfig(cott_mp, cott_cp);
            }
            /* Use sample time of Conversion test */
            cott.setSampleTime(CT_SAMPLETIME);
            suite.add(cott);

            suite.test();
            suite.report();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws Exception {
        final String port;
        if (args.length == 0) {
            port = "COM17";
        } else {
            port = args[0];
        }
        Protocol protocol = ProtocolFactory.getLNet(new Serial(115200, Serial.Databits.BITS_8, Serial.Parity.NONE, Serial.Stopbits.STOPBITS_1, port), 1);
        new Test_HFInjectionSquare_FiP32(protocol);
    }
}
