/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2108 $
 * $LastChangedDate:: 2020-12-07 19:09:57 +0100#$
 */
// USERCODE-BEGIN:Description                                                                                           
/* Description: */
// USERCODE-END:Description                                                                                             

package at.lcm.x2c.library.mchp_zsmt;

import at.lcm.x2c.core.structure.*;
import at.lcm.bu21.general.dtypes.*;

// USERCODE-BEGIN:Imports                                                                                               
// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_InitPosDetect_Float32 extends JavaConversionFunction {
    private static final long serialVersionUID = 1L;

    @Override
    public void convertMaskToImplementation() throws Exception {

        // Mask Parameter: U_pulse                                                                                      
        MaskDouble U_pulseMaskVal = 
            (MaskDouble)this.getMaskParameter("U_pulse").getMaskDataType();
        TNumeric U_pulseMaskData = 
            (TNumeric)U_pulseMaskVal.getData();
        // Mask Parameter: T_pulse                                                                                      
        MaskDouble T_pulseMaskVal = 
            (MaskDouble)this.getMaskParameter("T_pulse").getMaskDataType();
        TNumeric T_pulseMaskData = 
            (TNumeric)T_pulseMaskVal.getData();
        // Mask Parameter: T_pause                                                                                      
        MaskDouble T_pauseMaskVal = 
            (MaskDouble)this.getMaskParameter("T_pause").getMaskDataType();
        TNumeric T_pauseMaskData = 
            (TNumeric)T_pauseMaskVal.getData();
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

        // Implementation Parameter: u_pulse                                                                            
        TNumeric u_pulseCtrVal = this.getImplementationParameterData("u_pulse");
        // Implementation Parameter: t_pulse                                                                            
        TNumeric t_pulseCtrVal = this.getImplementationParameterData("t_pulse");
        // Implementation Parameter: t_period                                                                           
        TNumeric t_periodCtrVal = this.getImplementationParameterData("t_period");
        // Implementation Parameter: timer                                                                              
        TNumeric timerCtrVal = this.getImplementationParameterData("timer");
        // Implementation Parameter: dir                                                                                
        TNumeric dirCtrVal = this.getImplementationParameterData("dir");
        // Implementation Parameter: phi                                                                                
        TNumeric phiCtrVal = this.getImplementationParameterData("phi");
        // Implementation Parameter: max_ia_pos                                                                         
        TNumeric max_ia_posCtrVal = this.getImplementationParameterData("max_ia_pos");
        // Implementation Parameter: max_ia_neg                                                                         
        TNumeric max_ia_negCtrVal = this.getImplementationParameterData("max_ia_neg");
        // Implementation Parameter: max_ib_pos                                                                         
        TNumeric max_ib_posCtrVal = this.getImplementationParameterData("max_ib_pos");
        // Implementation Parameter: max_ib_neg                                                                         
        TNumeric max_ib_negCtrVal = this.getImplementationParameterData("max_ib_neg");
        // Implementation Parameter: max_ic_pos                                                                         
        TNumeric max_ic_posCtrVal = this.getImplementationParameterData("max_ic_pos");
        // Implementation Parameter: max_ic_neg                                                                         
        TNumeric max_ic_negCtrVal = this.getImplementationParameterData("max_ic_neg");

// USERCODE-BEGIN:ConvMaskToImplementation                                                                              
        int nPulse, nPause, nPeriod;

        // get mask value
        double ampPhasor = Double.valueOf(U_pulseMaskVal.getValue()); /* get amplitude of voltage phasor */
        double deltaT = Double.valueOf(T_pauseMaskVal.getValue()); /* pause time */
        double ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();
        nPulse = Double.valueOf(T_pulseMaskVal.getValue()).intValue(); /* pulse duration in samples */

        // validation
        if (ts_fact <= 0) {
            throw new Exception("Sample time factor must not be smaller than one!");
        }
        if (nPulse < 1) {
            throw new Exception("Pulse duration must be at least one sample!");
        }
        if (deltaT < 0) {
            throw new Exception("Pause time must not be negative!");
        }

        // calculate implementation parameter value
        /* scaled voltage phasor amplitude */
        u_pulseCtrVal.setReal(0, 0, ampPhasor);

        /* pulse time in updates */
        if (nPulse > 32767) {
            nPulse = 32767;
        }
        t_pulseCtrVal.setReal(0, 0, nPulse);

        /* period in updates */
        nPause = (int) (deltaT / 1000 / (ts_fact * this.getDedicatedBlock().getModel().getSampleTime()));
        nPeriod = 2 * nPulse + nPause;
        if (nPeriod > 32767) {
            nPeriod = 32767;
        }
        t_periodCtrVal.setReal(0, 0, nPeriod);

// USERCODE-END:ConvMaskToImplementation                                                                                
        this.setImplementationParameterData("u_pulse", u_pulseCtrVal);
        this.setImplementationParameterData("t_pulse", t_pulseCtrVal);
        this.setImplementationParameterData("t_period", t_periodCtrVal);
        this.setImplementationParameterData("timer", timerCtrVal);
        this.setImplementationParameterData("dir", dirCtrVal);
        this.setImplementationParameterData("phi", phiCtrVal);
        this.setImplementationParameterData("max_ia_pos", max_ia_posCtrVal);
        this.setImplementationParameterData("max_ia_neg", max_ia_negCtrVal);
        this.setImplementationParameterData("max_ib_pos", max_ib_posCtrVal);
        this.setImplementationParameterData("max_ib_neg", max_ib_negCtrVal);
        this.setImplementationParameterData("max_ic_pos", max_ic_posCtrVal);
        this.setImplementationParameterData("max_ic_neg", max_ic_negCtrVal);
    }

    @Override
    public void convertImplementationToMask() throws Exception {

        // Mask Parameter: U_pulse                                                                                      
        MaskDouble U_pulseMaskVal = 
            (MaskDouble)this.getMaskParameter("U_pulse").getMaskDataType();
        TNumeric U_pulseMaskData = 
            (TNumeric)U_pulseMaskVal.getData();
        // Mask Parameter: T_pulse                                                                                      
        MaskDouble T_pulseMaskVal = 
            (MaskDouble)this.getMaskParameter("T_pulse").getMaskDataType();
        TNumeric T_pulseMaskData = 
            (TNumeric)T_pulseMaskVal.getData();
        // Mask Parameter: T_pause                                                                                      
        MaskDouble T_pauseMaskVal = 
            (MaskDouble)this.getMaskParameter("T_pause").getMaskDataType();
        TNumeric T_pauseMaskData = 
            (TNumeric)T_pauseMaskVal.getData();
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

        // Implementation Parameter: u_pulse                                                                            
        TNumeric u_pulseCtrVal = this.getImplementationParameterData("u_pulse");
        // Implementation Parameter: t_pulse                                                                            
        TNumeric t_pulseCtrVal = this.getImplementationParameterData("t_pulse");
        // Implementation Parameter: t_period                                                                           
        TNumeric t_periodCtrVal = this.getImplementationParameterData("t_period");
        // Implementation Parameter: timer                                                                              
        TNumeric timerCtrVal = this.getImplementationParameterData("timer");
        // Implementation Parameter: dir                                                                                
        TNumeric dirCtrVal = this.getImplementationParameterData("dir");
        // Implementation Parameter: phi                                                                                
        TNumeric phiCtrVal = this.getImplementationParameterData("phi");
        // Implementation Parameter: max_ia_pos                                                                         
        TNumeric max_ia_posCtrVal = this.getImplementationParameterData("max_ia_pos");
        // Implementation Parameter: max_ia_neg                                                                         
        TNumeric max_ia_negCtrVal = this.getImplementationParameterData("max_ia_neg");
        // Implementation Parameter: max_ib_pos                                                                         
        TNumeric max_ib_posCtrVal = this.getImplementationParameterData("max_ib_pos");
        // Implementation Parameter: max_ib_neg                                                                         
        TNumeric max_ib_negCtrVal = this.getImplementationParameterData("max_ib_neg");
        // Implementation Parameter: max_ic_pos                                                                         
        TNumeric max_ic_posCtrVal = this.getImplementationParameterData("max_ic_pos");
        // Implementation Parameter: max_ic_neg                                                                         
        TNumeric max_ic_negCtrVal = this.getImplementationParameterData("max_ic_neg");

// USERCODE-BEGIN:ConvImplementationToMask                                                                              
        if (true) {
            throw new Exception("Implementation-to-Mask conversion not implemented");
        }
// USERCODE-END:ConvImplementationToMask                                                                                
        this.getMaskParameter("U_pulse").setValue(U_pulseMaskData.toFullString());
        this.getMaskParameter("T_pulse").setValue(T_pulseMaskData.toFullString());
        this.getMaskParameter("T_pause").setValue(T_pauseMaskData.toFullString());
        this.getMaskParameter("U_max").setValue(U_maxMaskData.toFullString());
        this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
    }
}
