/*
 * Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision: 2108 $
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
public class ConvFnc_EstimatorSwitch_FiP32 extends JavaConversionFunction {
    private static final long serialVersionUID = 1L;

    @Override
    public void convertMaskToImplementation() throws Exception {

        // Mask Parameter: thresh_up                                                                                    
        MaskDouble thresh_upMaskVal = 
            (MaskDouble)this.getMaskParameter("thresh_up").getMaskDataType();
        TNumeric thresh_upMaskData = 
            (TNumeric)thresh_upMaskVal.getData();
        // Mask Parameter: thresh_down                                                                                  
        MaskDouble thresh_downMaskVal = 
            (MaskDouble)this.getMaskParameter("thresh_down").getMaskDataType();
        TNumeric thresh_downMaskData = 
            (TNumeric)thresh_downMaskVal.getData();
        // Mask Parameter: n_max                                                                                        
        MaskDouble n_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("n_max").getMaskDataType();
        TNumeric n_maxMaskData = 
            (TNumeric)n_maxMaskVal.getData();
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();

        // Implementation Parameter: thresh_up                                                                          
        TNumeric thresh_upCtrVal = this.getImplementationParameterData("thresh_up");
        // Implementation Parameter: thresh_down                                                                        
        TNumeric thresh_downCtrVal = this.getImplementationParameterData("thresh_down");
        // Implementation Parameter: status                                                                             
        TNumeric statusCtrVal = this.getImplementationParameterData("status");

// USERCODE-BEGIN:ConvMaskToImplementation                                                                              
        final int BITS = 32;
        double Thresh_up, Thresh_down, n_max;

        // get mask parameter value
        Thresh_up = Double.valueOf(thresh_upMaskVal.getValue());
        Thresh_down = Double.valueOf(thresh_downMaskVal.getValue());
        n_max = Double.valueOf(n_maxMaskVal.getValue());

        // validation
        n_max = Math.abs(n_max);
        if (Thresh_up < 0) {
            throw new Exception("Threshold level conflict: up value must not be negative!");
        }
        if (Thresh_down < 0) {
            throw new Exception("Threshold level conflict: down value must not be negative!");
        }
        if (Thresh_up < Thresh_down) {
            throw new Exception("Threshold level conflict: up value must not be smaller than down value!");
        }

        // calculate implementation parameter value
        thresh_upCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(Thresh_up / n_max, BITS - 1, BITS, true)));
        thresh_downCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(Thresh_down / n_max, BITS - 1, BITS, true)));

// USERCODE-END:ConvMaskToImplementation                                                                                
        this.setImplementationParameterData("thresh_up", thresh_upCtrVal);
        this.setImplementationParameterData("thresh_down", thresh_downCtrVal);
        this.setImplementationParameterData("status", statusCtrVal);
    }

    @Override
    public void convertImplementationToMask() throws Exception {

        // Mask Parameter: thresh_up                                                                                    
        MaskDouble thresh_upMaskVal = 
            (MaskDouble)this.getMaskParameter("thresh_up").getMaskDataType();
        TNumeric thresh_upMaskData = 
            (TNumeric)thresh_upMaskVal.getData();
        // Mask Parameter: thresh_down                                                                                  
        MaskDouble thresh_downMaskVal = 
            (MaskDouble)this.getMaskParameter("thresh_down").getMaskDataType();
        TNumeric thresh_downMaskData = 
            (TNumeric)thresh_downMaskVal.getData();
        // Mask Parameter: n_max                                                                                        
        MaskDouble n_maxMaskVal = 
            (MaskDouble)this.getMaskParameter("n_max").getMaskDataType();
        TNumeric n_maxMaskData = 
            (TNumeric)n_maxMaskVal.getData();
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();

        // Implementation Parameter: thresh_up                                                                          
        TNumeric thresh_upCtrVal = this.getImplementationParameterData("thresh_up");
        // Implementation Parameter: thresh_down                                                                        
        TNumeric thresh_downCtrVal = this.getImplementationParameterData("thresh_down");
        // Implementation Parameter: status                                                                             
        TNumeric statusCtrVal = this.getImplementationParameterData("status");

// USERCODE-BEGIN:ConvImplementationToMask                                                                              
        if (true) {
            throw new Exception("Implementation-to-Mask conversion not implemented");
        }
// USERCODE-END:ConvImplementationToMask                                                                                
        this.getMaskParameter("thresh_up").setValue(thresh_upMaskData.toFullString());
        this.getMaskParameter("thresh_down").setValue(thresh_downMaskData.toFullString());
        this.getMaskParameter("n_max").setValue(n_maxMaskData.toFullString());
        this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
    }
}
