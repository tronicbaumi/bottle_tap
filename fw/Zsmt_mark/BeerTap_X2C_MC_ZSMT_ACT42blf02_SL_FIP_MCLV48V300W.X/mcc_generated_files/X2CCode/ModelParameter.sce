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


// Microchip ZS/MT Sensorless FOC
// version: R0-RC1

// ******* Universal constants *******
Nm_ozin = 7.061552e-3;
KRPM_rads = 0.060/2/%pi;
Vbus = 0;                  // override value in volts

// ******* Choose motor and board *******
//boardName = 'MCLV-2 board';
 boardName = 'MCLV48 board';
//boardName = 'POWERTOOL';

// motorName = 'VT100 blade motor';
// motorName = 'DCD996 drill driver';
// motorName = 'M18 Fuel drill driver';
// motorName = 'AT2303KV1500';
// motorName = 'Ryobi P251 drill driver';
// motorName = 'Linix 45ZWN24-40';
// motorName = 'Linix 45ZWN24-40-v2';
// motorName = 'ECI-63.20-K1-B00';
// motorName = 'Woodpecker drill';
//motorName = 'POWERTOOL';
motorName = 'ACT57BLF02';

// ******* Load all motor and board parameter files *******
//exec("motorParam_dcd996drill.sce", -1);
//exec("motorParam_powertool.sce", -1);
exec("motorParam_ACT57BLF02.sce", -1);
//exec("motorParam_m18drill.sce", -1);
//exec("motorParam_AT2303KV1500.sce", -1);
//exec("motorParam_eci6320k1b00.sce", -1);
//exec("motorParam_p251drill.sce", -1);
//exec("motorParam_linix45zwn2440.sce", -1);
//exec("motorParam_linix45zwn2440v2.sce", -1);
//exec("motorParam_woodpecker.sce", -1);
//exec("motorParam_Buehler.sce", -1);

//exec("boardParam_mclv2.sce", -1);
//exec("boardParam_mclv2-tc1.sce", -1);
//exec("boardParam_powertool.sce", -1);
exec("boardParam_mclv48.sce", -1);


// ******* Derived parameters *******
X2C_sampleTime = 1/fPWM;
Vdc_phase = Vbus/sqrt(3);
Ipeakfullscale = 1.65/(abs(Igain)*Rshunt);
startupCurrentNorm = motorStartupCurrent/Ipeakfullscale;
Isat = min(maxCurrentCommand*0.85,motorRatedCurrent);
IsatNorm = Isat/Ipeakfullscale;

// ******* Choose one of the saturation modes *******
SaturationModeBalancedDQ = %F;
SaturationModeQheavy = %T;

if SaturationModeBalancedDQ then
    // voltage saturation scheme:
    // remaining voltage after HFI is shared equally 
    // between d axis and q axis controllers
    VmaxAmp = Vdc_phase - hfiUcAmplitude;
    Vsat = sqrt((VmaxAmp^2)/2);
    Vdsat = Vsat;
    Vqsat = Vsat;
    VdsatNorm = Vdsat/Vdc_phase;
    VqsatNorm = Vqsat/Vdc_phase;
end

if SaturationModeQheavy then
    // voltage saturation scheme:
    // 95% of remaining voltage after HFI is shared 1x in 
    // d axis controller and 4x in q axis controller
    VmaxAmp = (Vdc_phase - hfiUcAmplitude)*0.95;
    Vsat = sqrt((VmaxAmp^2)/17);
    Vdsat = Vsat;
    Vqsat = 4*Vsat;
    VdsatNorm = Vdsat/Vdc_phase;
    VqsatNorm = Vqsat/Vdc_phase;
end

// rescaled motor parameters
Ld = Ld/2;
Lq = Lq/2;
Rs = Rs/2;
Ls_mH = (1e3)*(Ld+Lq)/2;

// ZS/MT tuning parameters
n_scale = nominalSpeed;
UDCLink_scale = Vbus;
I_scale = Ipeakfullscale;
vdcNormalization = Vbus/sqrt(3);
if keps_measured == 0 then
    keps = ((hfiUcAmplitude)/(4*(fPWM/2)*Ld*Lq))*((Lq-Ld)/2)*sind(2*45)*8;
    kepsScaled = keps + keps*0.5;
else
    keps = keps_measured;
    kepsScaled = keps;
end

// ******* Load simulation data *******
//exec("./gen_inputs.sci");
//exec("./qei_sim.sce");
//exec("./qei_sim2.sce");

// ******* Derived constants *******
speed2mechAngle     = (2*%pi*n_scale/60)/%pi;
speed2elAngle       = speed2mechAngle * n_p;

// ******* Simulation motor model parameters *******
psi_pm = Kell/sqrt(3)*60/(2*%pi*1000)/n_p;
alphaCU = 0;
Temp_nom = 25;
alphaPM = 0;
ded = 0;
d = 0;
ced = 0;
cf = 0;
chy = 0;
theta_r0 = 1.0;
omega_r0 = 1.0;
J = J_nmradss;
omega0 = 1/(nominalSpeed*(1/60)*n_p);
