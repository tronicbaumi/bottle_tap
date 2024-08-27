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
    motorName = 'ACT57BLF02';
else
    if motorName == 'ACT57BLF02'
        if isdef(['Vbus'])==%T then
            if Vbus == 0 then
                Vbus = 18;   // in volts
            end
        end
        
        Rs = 40e-3;      	// line-to-line
        Ld = 26e-3;   	// line-to-line
        Lq = 31e-3;    	// line-to-line
        Lnom = (Ld+Lq)/2;
        Kell = 4.1;    	    // 
        
        n_p = 4;           // number of polepairs
        
        nominalSpeed = 3000;    // in RPM mechanical
        maximumSpeed = 4500;
        
        J_nmradss = 0.000600;       // inertia Nm/rad/s/s
        
        motorRatedCurrent = 7;		// can be reduced to 12 to avoid saturation and loss in saliency in A 
        motorStartupCurrent = 7;  // in A 
        
        kpCurrent = 1;
        kiCurrent = 500;
        
        //kpVelocity = 0.2; no speed control
        //kiVelocity = 1;
        
        ipdPulseVoltageAmplitude = 8;     
        ipdPulseWidth = 4;						
        hfiUcAmplitude = 4;
        keps_measured = 0.75;						
        hfiTrackingLoopBandwidth = 100;  
        
        VdsatNorm = 0.1    
    end
end
