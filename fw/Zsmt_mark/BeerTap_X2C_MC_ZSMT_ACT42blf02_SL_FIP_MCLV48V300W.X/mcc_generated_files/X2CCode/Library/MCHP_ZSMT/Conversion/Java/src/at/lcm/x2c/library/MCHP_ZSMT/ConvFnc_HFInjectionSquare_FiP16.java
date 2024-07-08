/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2128 $
 * $LastChangedDate:: 2021-02-02 14:38:09 +0100#$
 */
// USERCODE-BEGIN:Description                                                                                           
/* Description: */
// USERCODE-END:Description                                                                                             

package at.lcm.x2c.library.mchp_zsmt;

import at.lcm.x2c.core.structure.*;
import at.lcm.bu21.general.dtypes.*;

// USERCODE-BEGIN:Imports                                                                                               
import at.lcm.x2c.utils.QFormat;
// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_HFInjectionSquare_FiP16 extends JavaConversionFunction {
    private static final long serialVersionUID = 1L;

    @Override
    public void convertMaskToImplementation() throws Exception {

        // Mask Parameter: U_inj                                                                                        
        MaskDouble U_injMaskVal = 
            (MaskDouble)this.getMaskParameter("U_inj").getMaskDataType();
        TNumeric U_injMaskData = 
            (TNumeric)U_injMaskVal.getData();
        // Mask Parameter: Jp                                                                                           
        MaskDouble JpMaskVal = 
            (MaskDouble)this.getMaskParameter("Jp").getMaskDataType();
        TNumeric JpMaskData = 
            (TNumeric)JpMaskVal.getData();
        // Mask Parameter: I_inj                                                                                        
        MaskDouble I_injMaskVal = 
            (MaskDouble)this.getMaskParameter("I_inj").getMaskDataType();
        TNumeric I_injMaskData = 
            (TNumeric)I_injMaskVal.getData();
        // Mask Parameter: fo                                                                                           
        MaskDouble foMaskVal = 
            (MaskDouble)this.getMaskParameter("fo").getMaskDataType();
        TNumeric foMaskData = 
            (TNumeric)foMaskVal.getData();
        // Mask Parameter: p                                                                                            
        MaskDouble pMaskVal = 
            (MaskDouble)this.getMaskParameter("p").getMaskDataType();
        TNumeric pMaskData = 
            (TNumeric)pMaskVal.getData();
        // Mask Parameter: n_max                                                                                        
        MaskDouble n_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("n_max").getMaskDataType();
        TNumeric n_maxMaskData = 
            (TNumeric)n_maxMaskVal.getData();
        // Mask Parameter: I_max                                                                                        
        MaskDouble I_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("I_max").getMaskDataType();
        TNumeric I_maxMaskData = 
            (TNumeric)I_maxMaskVal.getData();
        // Mask Parameter: U_max                                                                                        
        MaskDouble U_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("U_max").getMaskDataType();
        TNumeric U_maxMaskData = 
            (TNumeric)U_maxMaskVal.getData();
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();
        // Mask Parameter: estimation                                                                                   
        MaskComboBox estimationMaskVal = 
            (MaskComboBox)this.getMaskParameter("estimation").getMaskDataType();
        TString estimationMaskData = 
            (TString)estimationMaskVal.getData();
        // Mask Parameter: method                                                                                       
        MaskComboBox methodMaskVal = 
            (MaskComboBox)this.getMaskParameter("method").getMaskDataType();
        TString methodMaskData = 
            (TString)methodMaskVal.getData();

        // Implementation Parameter: uInjAmp                                                                            
        TNumeric uInjAmpCtrVal = this.getImplementationParameterData("uInjAmp");
        // Implementation Parameter: sampleCnt                                                                          
        TNumeric sampleCntCtrVal = this.getImplementationParameterData("sampleCnt");
        // Implementation Parameter: iyArr                                                                              
        TNumeric iyArrCtrVal = this.getImplementationParameterData("iyArr");
        // Implementation Parameter: enable_old                                                                         
        TNumeric enable_oldCtrVal = this.getImplementationParameterData("enable_old");
        // Implementation Parameter: i_old_torque                                                                       
        TNumeric i_old_torqueCtrVal = this.getImplementationParameterData("i_old_torque");
        // Implementation Parameter: i_old_speed                                                                        
        TNumeric i_old_speedCtrVal = this.getImplementationParameterData("i_old_speed");
        // Implementation Parameter: i_old_angle                                                                        
        TNumeric i_old_angleCtrVal = this.getImplementationParameterData("i_old_angle");
        // Implementation Parameter: vGain                                                                              
        TNumeric vGainCtrVal = this.getImplementationParameterData("vGain");
        // Implementation Parameter: sfrGain                                                                            
        TNumeric sfrGainCtrVal = this.getImplementationParameterData("sfrGain");
        // Implementation Parameter: b0_torque                                                                          
        TNumeric b0_torqueCtrVal = this.getImplementationParameterData("b0_torque");
        // Implementation Parameter: b1_torque                                                                          
        TNumeric b1_torqueCtrVal = this.getImplementationParameterData("b1_torque");
        // Implementation Parameter: sfrb0_torque                                                                       
        TNumeric sfrb0_torqueCtrVal = this.getImplementationParameterData("sfrb0_torque");
        // Implementation Parameter: sfrb1_torque                                                                       
        TNumeric sfrb1_torqueCtrVal = this.getImplementationParameterData("sfrb1_torque");
        // Implementation Parameter: b0_speed                                                                           
        TNumeric b0_speedCtrVal = this.getImplementationParameterData("b0_speed");
        // Implementation Parameter: b1_speed                                                                           
        TNumeric b1_speedCtrVal = this.getImplementationParameterData("b1_speed");
        // Implementation Parameter: sfrb0_speed                                                                        
        TNumeric sfrb0_speedCtrVal = this.getImplementationParameterData("sfrb0_speed");
        // Implementation Parameter: sfrb1_speed                                                                        
        TNumeric sfrb1_speedCtrVal = this.getImplementationParameterData("sfrb1_speed");
        // Implementation Parameter: b0_angle                                                                           
        TNumeric b0_angleCtrVal = this.getImplementationParameterData("b0_angle");
        // Implementation Parameter: b1_angle                                                                           
        TNumeric b1_angleCtrVal = this.getImplementationParameterData("b1_angle");
        // Implementation Parameter: sfrb0_angle                                                                        
        TNumeric sfrb0_angleCtrVal = this.getImplementationParameterData("sfrb0_angle");
        // Implementation Parameter: sfrb1_angle                                                                        
        TNumeric sfrb1_angleCtrVal = this.getImplementationParameterData("sfrb1_angle");
        // Implementation Parameter: rawSpeed                                                                           
        TNumeric rawSpeedCtrVal = this.getImplementationParameterData("rawSpeed");

// USERCODE-BEGIN:ConvMaskToImplementation                                                                              
        final int BITS = 16;
        final int BITS32 = 32;
        final int TIME_STEPS = 4;
        double Kp, Ki;
        double b0 = 0, b1 = 0, a0 = 0;

        // get mask parameter value
        double ampHF = Double.valueOf(U_injMaskVal.getValue()); /* amplitude of injection voltage */
        double p = Double.valueOf(pMaskVal.getValue()); /* number of pole pairs */
        double Jp = Double.valueOf(JpMaskVal.getValue()); /* moment of inertia */
        double Keps = Double.valueOf(I_injMaskVal.getValue());
        double rho = 2 * Math.PI * Double.valueOf(foMaskVal.getValue());
        double UDCmax = Double.valueOf(U_maxMaskVal.getValue()); /* max DC link voltage */
        double n_max = Double.valueOf(n_maxMaskVal.getValue()); /* max speed */
        double I_max = Double.valueOf(I_maxMaskVal.getValue()); /* max current */
        double ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();

        // validation
        if (ts_fact < 1) {
            throw new Exception("Sample time factor must not be smaller than one!");
        }
        if (p < 1) {
            throw new Exception("Number of pole pairs must not be smaller than one!");
        }
        if (n_max == 0) {
            throw new Exception("n_max must not be zero!");
        }
        if (Jp == 0) {
            throw new Exception("Moment of inertia must not be zero!");
        }
        if (Keps == 0) {
            throw new Exception("HF current amplitude must not be zero!");
        }

        // calculation of implementation parameters
        double Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime() * TIME_STEPS;
        double omegaScale = n_max * Math.PI * p / 30; /* omega = n*pi/30*pz */
        double torqueScale = omegaScale / 100; /* magic number 100: empirically obtained factor */
        double phi2speed = 30 / n_max / p; /* normalization factor from angle to speed */
        double torque2speed = torqueScale / omegaScale * 1 / Jp;
        double I2phi = I_max / Math.PI * 1 / (2 * 8 * Keps); /*
         * factor from error-current to error-angle (factor 8 is
         * needed to compensate missing 1/8 in the C-code)
         */

        /******************** HF injection ********************/
        uInjAmpCtrVal.setReal(0, 0, QFormat.getQValue(ampHF / UDCmax, BITS - 1, BITS, true));

        /******************** Torque (PI controller) ********************/
        /*
         * design rule for observer parameter: kp = 3*rho^2*Jp (integral-term of observer); ki = rho^3*Jp
         * (double-integral-term of observer))
         */
        Kp = I2phi * phi2speed * 3 * rho * rho / torque2speed;
        Ki = I2phi * phi2speed * rho * rho * rho / torque2speed;

        // calculate coefficients
        if (methodMaskVal.getValue().equals("zoh")) {
            // Zero order hold (zoh):
            // G(s) = Kp + Ki/s -> G(z) = Kp + Ki*Ts*1/(z-1)
            b0 = Ki * Ts;
            b1 = Kp;
        } else if (methodMaskVal.getValue().equals("tustin")) {
            // G(s) = Kp + Ki/s -> G(z) = ( (Ki*Ts/2+Kp)*z + Ki*Ts/2-Kp )/(z-1)
            b0 = Ki * Ts;
            b1 = Ki * Ts / 2 + Kp;
        }

        // b0
        sfrb0_torqueCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQFormat(b0, BITS32, true)));
        b0_torqueCtrVal.setReal(0, 0,
                Double.valueOf(QFormat.getQValue(b0, (int) sfrb0_torqueCtrVal.getReal(0, 0), BITS32, true)));

        // b1
        sfrb1_torqueCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQFormat(b1, BITS32, true)));
        b1_torqueCtrVal.setReal(0, 0,
                Double.valueOf(QFormat.getQValue(b1, (int) sfrb1_torqueCtrVal.getReal(0, 0), BITS32, true)));

        /******************** Speed (I controller) ********************/
        Ki = torque2speed;
        Kp = 0;

        // calculate coefficients
        if (methodMaskVal.getValue().equals("zoh")) {
            // Zero order hold (zoh):
            // G(s) = Kp + Ki/s -> G(z) = Kp + Ki*Ts*1/(z-1)
            b0 = Ki * Ts;
            b1 = Kp;
        } else if (methodMaskVal.getValue().equals("tustin")) {
            // G(s) = Kp + Ki/s -> G(z) = ( (Ki*Ts/2+Kp)*z + Ki*Ts/2-Kp )/(z-1)
            b0 = Ki * Ts;
            b1 = Ki * Ts / 2 + Kp;
        }

        // b0
        sfrb0_speedCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQFormat(b0, BITS, true)));
        b0_speedCtrVal.setReal(0, 0,
                Double.valueOf(QFormat.getQValue(b0, (int) sfrb0_speedCtrVal.getReal(0, 0), BITS, true)));

        // b1
        sfrb1_speedCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQFormat(b1, BITS, true)));
        b1_speedCtrVal.setReal(0, 0,
                Double.valueOf(QFormat.getQValue(b1, (int) sfrb1_speedCtrVal.getReal(0, 0), BITS, true)));

        if ((int) b0_speedCtrVal.getReal(0, 0) < 20) {
            throw new Exception("Accuracy-Error: speed system is ill conditioned -> try to increase Ts*ts_fact!\n");
        }

        /******************** Angle (uI controller) ********************/
        Ki = 2 * n_max * p / 60;
        Kp = 0;

        // calculate coefficients
        if (methodMaskVal.getValue().equals("zoh")) {
            // Zero order hold (zoh):
            // G(s) = Kp + Ki/s -> G(z) = Kp + Ki*Ts*1/(z-1)
            b0 = Ki * Ts;
            b1 = Kp;
        } else if (methodMaskVal.getValue().equals("tustin")) {
            // G(s) = Kp + Ki/s -> G(z) = ( (Ki*Ts/2+Kp)*z + Ki*Ts/2-Kp )/(z-1)
            b0 = Ki * Ts;
            b1 = Ki * Ts / 2 + Kp;
        }

        // b0
        sfrb0_angleCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQFormat(b0, BITS, true)));
        b0_angleCtrVal.setReal(0, 0,
                Double.valueOf(QFormat.getQValue(b0, (int) sfrb0_angleCtrVal.getReal(0, 0), BITS, true)));

        // b1
        sfrb1_angleCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQFormat(b1, BITS, true)));
        b1_angleCtrVal.setReal(0, 0,
                Double.valueOf(QFormat.getQValue(b1, (int) sfrb1_angleCtrVal.getReal(0, 0), BITS, true)));

        if ((int) b0_angleCtrVal.getReal(0, 0) < 20) {
            throw new Exception(
                    "Accuracy-Error: angle system is ill conditioned -> try to increase n_max and/or Ts*ts_fact!\n");
        }

        /******************** Gain ********************/
        double V = I2phi * phi2speed * 3 * rho;

        sfrGainCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQFormat(V, BITS, true)));
        vGainCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(V, (int) sfrGainCtrVal.getReal(0, 0), BITS, true)));

        /******************** Speed estimation type ********************/
        if (estimationMaskVal.getValue().equals("high dynamic range")) {
            rawSpeedCtrVal.setReal(0, 0, 1);
        } else if (estimationMaskVal.getValue().equals("less noise")) {
            rawSpeedCtrVal.setReal(0, 0, 0);
        }

// USERCODE-END:ConvMaskToImplementation                                                                                
        this.setImplementationParameterData("uInjAmp", uInjAmpCtrVal);
        this.setImplementationParameterData("sampleCnt", sampleCntCtrVal);
        this.setImplementationParameterData("iyArr", iyArrCtrVal);
        this.setImplementationParameterData("enable_old", enable_oldCtrVal);
        this.setImplementationParameterData("i_old_torque", i_old_torqueCtrVal);
        this.setImplementationParameterData("i_old_speed", i_old_speedCtrVal);
        this.setImplementationParameterData("i_old_angle", i_old_angleCtrVal);
        this.setImplementationParameterData("vGain", vGainCtrVal);
        this.setImplementationParameterData("sfrGain", sfrGainCtrVal);
        this.setImplementationParameterData("b0_torque", b0_torqueCtrVal);
        this.setImplementationParameterData("b1_torque", b1_torqueCtrVal);
        this.setImplementationParameterData("sfrb0_torque", sfrb0_torqueCtrVal);
        this.setImplementationParameterData("sfrb1_torque", sfrb1_torqueCtrVal);
        this.setImplementationParameterData("b0_speed", b0_speedCtrVal);
        this.setImplementationParameterData("b1_speed", b1_speedCtrVal);
        this.setImplementationParameterData("sfrb0_speed", sfrb0_speedCtrVal);
        this.setImplementationParameterData("sfrb1_speed", sfrb1_speedCtrVal);
        this.setImplementationParameterData("b0_angle", b0_angleCtrVal);
        this.setImplementationParameterData("b1_angle", b1_angleCtrVal);
        this.setImplementationParameterData("sfrb0_angle", sfrb0_angleCtrVal);
        this.setImplementationParameterData("sfrb1_angle", sfrb1_angleCtrVal);
        this.setImplementationParameterData("rawSpeed", rawSpeedCtrVal);
    }

    @Override
    public void convertImplementationToMask() throws Exception {

        // Mask Parameter: U_inj                                                                                        
        MaskDouble U_injMaskVal = 
            (MaskDouble)this.getMaskParameter("U_inj").getMaskDataType();
        TNumeric U_injMaskData = 
            (TNumeric)U_injMaskVal.getData();
        // Mask Parameter: Jp                                                                                           
        MaskDouble JpMaskVal = 
            (MaskDouble)this.getMaskParameter("Jp").getMaskDataType();
        TNumeric JpMaskData = 
            (TNumeric)JpMaskVal.getData();
        // Mask Parameter: I_inj                                                                                        
        MaskDouble I_injMaskVal = 
            (MaskDouble)this.getMaskParameter("I_inj").getMaskDataType();
        TNumeric I_injMaskData = 
            (TNumeric)I_injMaskVal.getData();
        // Mask Parameter: fo                                                                                           
        MaskDouble foMaskVal = 
            (MaskDouble)this.getMaskParameter("fo").getMaskDataType();
        TNumeric foMaskData = 
            (TNumeric)foMaskVal.getData();
        // Mask Parameter: p                                                                                            
        MaskDouble pMaskVal = 
            (MaskDouble)this.getMaskParameter("p").getMaskDataType();
        TNumeric pMaskData = 
            (TNumeric)pMaskVal.getData();
        // Mask Parameter: n_max                                                                                        
        MaskDouble n_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("n_max").getMaskDataType();
        TNumeric n_maxMaskData = 
            (TNumeric)n_maxMaskVal.getData();
        // Mask Parameter: I_max                                                                                        
        MaskDouble I_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("I_max").getMaskDataType();
        TNumeric I_maxMaskData = 
            (TNumeric)I_maxMaskVal.getData();
        // Mask Parameter: U_max                                                                                        
        MaskDouble U_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("U_max").getMaskDataType();
        TNumeric U_maxMaskData = 
            (TNumeric)U_maxMaskVal.getData();
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();
        // Mask Parameter: estimation                                                                                   
        MaskComboBox estimationMaskVal = 
            (MaskComboBox)this.getMaskParameter("estimation").getMaskDataType();
        TString estimationMaskData = 
            (TString)estimationMaskVal.getData();
        // Mask Parameter: method                                                                                       
        MaskComboBox methodMaskVal = 
            (MaskComboBox)this.getMaskParameter("method").getMaskDataType();
        TString methodMaskData = 
            (TString)methodMaskVal.getData();

        // Implementation Parameter: uInjAmp                                                                            
        TNumeric uInjAmpCtrVal = this.getImplementationParameterData("uInjAmp");
        // Implementation Parameter: sampleCnt                                                                          
        TNumeric sampleCntCtrVal = this.getImplementationParameterData("sampleCnt");
        // Implementation Parameter: iyArr                                                                              
        TNumeric iyArrCtrVal = this.getImplementationParameterData("iyArr");
        // Implementation Parameter: enable_old                                                                         
        TNumeric enable_oldCtrVal = this.getImplementationParameterData("enable_old");
        // Implementation Parameter: i_old_torque                                                                       
        TNumeric i_old_torqueCtrVal = this.getImplementationParameterData("i_old_torque");
        // Implementation Parameter: i_old_speed                                                                        
        TNumeric i_old_speedCtrVal = this.getImplementationParameterData("i_old_speed");
        // Implementation Parameter: i_old_angle                                                                        
        TNumeric i_old_angleCtrVal = this.getImplementationParameterData("i_old_angle");
        // Implementation Parameter: vGain                                                                              
        TNumeric vGainCtrVal = this.getImplementationParameterData("vGain");
        // Implementation Parameter: sfrGain                                                                            
        TNumeric sfrGainCtrVal = this.getImplementationParameterData("sfrGain");
        // Implementation Parameter: b0_torque                                                                          
        TNumeric b0_torqueCtrVal = this.getImplementationParameterData("b0_torque");
        // Implementation Parameter: b1_torque                                                                          
        TNumeric b1_torqueCtrVal = this.getImplementationParameterData("b1_torque");
        // Implementation Parameter: sfrb0_torque                                                                       
        TNumeric sfrb0_torqueCtrVal = this.getImplementationParameterData("sfrb0_torque");
        // Implementation Parameter: sfrb1_torque                                                                       
        TNumeric sfrb1_torqueCtrVal = this.getImplementationParameterData("sfrb1_torque");
        // Implementation Parameter: b0_speed                                                                           
        TNumeric b0_speedCtrVal = this.getImplementationParameterData("b0_speed");
        // Implementation Parameter: b1_speed                                                                           
        TNumeric b1_speedCtrVal = this.getImplementationParameterData("b1_speed");
        // Implementation Parameter: sfrb0_speed                                                                        
        TNumeric sfrb0_speedCtrVal = this.getImplementationParameterData("sfrb0_speed");
        // Implementation Parameter: sfrb1_speed                                                                        
        TNumeric sfrb1_speedCtrVal = this.getImplementationParameterData("sfrb1_speed");
        // Implementation Parameter: b0_angle                                                                           
        TNumeric b0_angleCtrVal = this.getImplementationParameterData("b0_angle");
        // Implementation Parameter: b1_angle                                                                           
        TNumeric b1_angleCtrVal = this.getImplementationParameterData("b1_angle");
        // Implementation Parameter: sfrb0_angle                                                                        
        TNumeric sfrb0_angleCtrVal = this.getImplementationParameterData("sfrb0_angle");
        // Implementation Parameter: sfrb1_angle                                                                        
        TNumeric sfrb1_angleCtrVal = this.getImplementationParameterData("sfrb1_angle");
        // Implementation Parameter: rawSpeed                                                                           
        TNumeric rawSpeedCtrVal = this.getImplementationParameterData("rawSpeed");

// USERCODE-BEGIN:ConvImplementationToMask                                                                              
        if (true) {
            throw new Exception("Implementation-to-Mask conversion not implemented for Block 'HFInjectionSquare'");
        }
// USERCODE-END:ConvImplementationToMask                                                                                
        this.getMaskParameter("U_inj").setValue(U_injMaskData.toFullString());
        this.getMaskParameter("Jp").setValue(JpMaskData.toFullString());
        this.getMaskParameter("I_inj").setValue(I_injMaskData.toFullString());
        this.getMaskParameter("fo").setValue(foMaskData.toFullString());
        this.getMaskParameter("p").setValue(pMaskData.toFullString());
        this.getMaskParameter("n_max").setValue(n_maxMaskData.toFullString());
        this.getMaskParameter("I_max").setValue(I_maxMaskData.toFullString());
        this.getMaskParameter("U_max").setValue(U_maxMaskData.toFullString());
        this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
        this.getMaskParameter("estimation").setValue(estimationMaskData.getString());
        this.getMaskParameter("method").setValue(methodMaskData.getString());
    }
}
