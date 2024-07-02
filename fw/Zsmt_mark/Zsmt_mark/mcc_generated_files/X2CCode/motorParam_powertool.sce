// (c) 2020 Microchip Technology Inc. and its subsidiaries
// Subject to your compliance with these terms, you may use Microchip software and any derivatives exclusively 
// with Microchip products. You’re responsible for complying with 3rd party license terms applicable to your use 
// of 3rd party software (including open source software) that may accompany Microchip software. 
// SOFTWARE IS “AS IS.” NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
// IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP 
// BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
// KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR 
// THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP’S TOTAL LIABILITY ON ALL CLAIMS RELATED 
// TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

if isdef(['motorName'])==%F then
    mprintf("[Warning] - No motorName defined, defining this now.");
    motorName = 'POWERTOOL';
else
    if motorName == 'POWERTOOL'
        if isdef(['Vbus'])==%T then
            if Vbus == 0 then
                Vbus = 18;   // in volts
            end
        end
        
        Rs = 32.2;      	// line-to-line
        Ld = 120e-3;   	// line-to-line
        Lq = 125e-3;    	// line-to-line
        Lnom = (Ld+Lq)/2;
        Kell = 14.7/1.137;    	    // 0pll/1000RPM
        
        n_p = 2;           // number of polepairs
        
        nominalSpeed = 22500;    // in RPM mechanical
        maximumSpeed = 25000;
        
        J_nmradss = 0.000600;       // inertia Nm/rad/s/s
        
        motorRatedCurrent = 30;		// can be reduced to 12 to avoid saturation and loss in saliency in A 
        motorStartupCurrent = 50;  // in A 
        
        kpCurrent = 0.6;
        kiCurrent = 1400;
        
        //kpVelocity = 0.2; no speed control
        //kiVelocity = 1;
        
        ipdPulseVoltageAmplitude = 8;     
        ipdPulseWidth = 4;						
        hfiUcAmplitude = 4;
        keps_measured = 6;						
        hfiTrackingLoopBandwidth = 300;  
        
        VdsatNorm = 0.1    
    end
end
