/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */

/* USERCODE-BEGIN:ExternalModules                                                                                     */
/* USERCODE-END:ExternalModules                                                                                       */

/* Block sample time                                                                                                  */
/* bp_ts                                                                                                              */

/* Mask parameter values                                                                                              */
/* mp_n_max (Number)                                                                                                  */
/* mp_p (Number)                                                                                                      */
/* mp_ts_fact (Number)                                                                                                */
/* mp_I_max (Number)                                                                                                  */
/* mp_Jp (Number)                                                                                                     */
/* mp_Keps (Number)                                                                                                   */
/* mp_rho (Number)                                                                                                    */
/* mp_method (String)                                                                                                 */
/* mp_selSpeedProp (String)                                                                                           */

/* USERCODE-BEGIN:Convert                                                                                             */
/* *************************************** PI-Controller *************************************** */
/* design rule for observer parameter:
 * kp = 3*rho^2*Jp  (integral-term of observer)
 * ki = rho^3*Jp	(double-integral-term of observer))
 */

var Kp, Ki;											// mask params of PI controller
var b0, b1;											// implementation params of PI Controller
var phi2speed = 30/mp_n_max/mp_p;					// factors due to scaling 
var I2phi     = mp_I_max/Math.PI*1/(2*mp_Keps);		// factors due to scaling

/* apply design rule */
Kp = I2phi*phi2speed* 3*mp_rho*mp_rho*mp_Jp;
Ki = I2phi*phi2speed*mp_rho*mp_rho*mp_rho*mp_Jp;

// calculate coefficients
if (mp_method == "zoh") {
	// Zero order hold (zoh):
	// G(s) = Kp + Ki/s -> G(z) = Kp + Ki*Ts*1/(z-1)
	b0 = Ki * bp_ts;
	b1 = Kp;
} else if (mp_method == "tustin") {
	// G(s) = Kp + Ki/s -> G(z) = ( (Ki*Ts/2+Kp)*z + Ki*Ts/2-Kp )/(z-1)
	b0 = Ki * bp_ts;
	b1 = Ki * bp_ts/2 + Kp;
} 
/* set implementation param */
cp_sfrb0 = getQFormat(b0, 32, true);
cp_b0    = getQValue(b0, cp_sfrb0, 32, true);

cp_sfrb1 = getQFormat(b1, 32, true);
cp_b1    = getQValue(b1, cp_sfrb1, 32, true);

/* *************************************** uI ****************************************/

Ki = 2*mp_n_max*mp_p/60;
// calculate coefficients
 if (mp_method == "zoh") {
	//Zero order hold (zoh):
	// G(s) = Ki/s -> G(z) = Ki*Ts*1/(z-1)
	b0 = Ki * bp_ts;
	b1 = 0;
} else if (mp_method == "tustin") {
	// G(s) = Ki/s -> G(z) = 1/2*Ki*Ts*(z+1)/(z-1)
	b0 = Ki * bp_ts;
	b1 = (Ki * bp_ts)/2;
}
cp_sfr_uI = getQFormat(b0, 16, true);
cp_b0_uI  = getQValue(b0, cp_sfr_uI, 16, true);

cp_sfrb1_uI = getQFormat(b1, 16, true);
cp_b1_uI    = getQValue(b1, cp_sfrb1_uI, 16, true);

// integrator parameter
cp_i_old_uI = 0;  

/* check accuracy */
if (cp_b0_uI < 20){
	throw "SquareInj_Slow_Model-Block: Accuracy-Error: unsigned Integrator DSP-Coeff is too small!\n";
}

/************************************** I *********************************************/ 
Ki = 1/mp_Jp; 
// calculate coefficients
if (mp_method == "zoh") {
	// G(s) = Ki/s -> G(z) = Ki*Ts*1/(z-1)
	b0 = Ki * bp_ts;
	b1 = 0;
}else if (mp_method == "tustin") {
	// G(s) = Ki/s -> G(z) = 1/2*Ki*Ts*(z+1)/(z-1)
	b0 = Ki * bp_ts;
	b1 = (Ki * bp_ts)/2;
}  
cp_sfr_I = getQFormat(b0, 16, true);
cp_b0_I  = getQValue(b0, cp_sfr_I, 16, true);

cp_sfrb1_I = getQFormat(b1, 16, true);
cp_b1_I    = getQValue(b1, cp_sfrb1_I, 16, true);

// integrator parameter
cp_i_old_I  = 0; 

/* check accuracy */
if (cp_b0_I < 20){
	throw "SquareInj_Slow_Model-Block: Accuracy-Error: mech. Integrator DSP-Coeff is too small!";
}

/************************************** Gain ******************************************/
var V = I2phi*phi2speed*3*mp_rho;
cp_sfrGain = getQFormat(V, 16, true);
cp_vGain   = getQValue(V, cp_sfrGain, 16, true);


/************************************** select speed output ******************************************/
if (mp_selSpeedProp == "high-dynamic-range") {
	cp_rawSpeed = 1;
}
else if (mp_selSpeedProp == "less-noise"){
	cp_rawSpeed = 0;
}


/* *******************************************************************************/
/* qFormat functions */
/* - getQFormat() */
/* - getQValue() */
/* *******************************************************************************/
function getQFormat(decValue, maxBits, isSigned) {
	var qFormat, maxExp;
	var maxValue, minValue;

	qFormat = maxBits;

	do {
		qFormat--;

		if (qFormat < 0) {
			throw "Q Format error";
		}

		if (isSigned) {
			maxExp = (-qFormat + maxBits) - 2;
			minValue = -Math.pow(2, maxExp + 1) + Math.pow(2, -qFormat);
			maxValue = Math.pow(2, maxExp + 1) - Math.pow(2, -qFormat);
		} else {
			maxExp = (-qFormat + maxBits) - 1;
			minValue = 0;
			maxValue = Math.pow(2, maxExp + 1) - Math.pow(2, -qFormat);
		}

	} while ((decValue > maxValue) || (decValue < minValue));

	return (qFormat);
}

function getQValue(decValue, qFormat, maxBits, isSigned) {
	var maxExp;
	var maxValue;

	if (isSigned) {
		maxExp = (-qFormat + maxBits) - 2;
		var minValue = -Math.pow(2, maxExp + 1) + Math.pow(2, -qFormat);
		maxValue = Math.pow(2, maxExp + 1) - Math.pow(2, -qFormat);
		if (decValue > maxValue) {
			return (Math.pow(2, maxBits - 1) - 1);
		} else if (decValue < minValue) {
			return (-(Math.pow(2, maxBits - 1) - 1));
		} else {
			return (Math.round(decValue * Math.pow(2, qFormat)));
		}
	} else {
		maxExp = (-qFormat + maxBits) - 1;
		maxValue = Math.pow(2, maxExp + 1) - Math.pow(2, -qFormat);
		if (decValue > maxValue) {
			return (Math.pow(2, maxBits) - 1);
		} else if (decValue < 0) {
			return (0);
		} else {
			return (Math.round(decValue * (Math.pow(2, qFormat + 1))) / 2);
		}
	}
}
 // not used Implementation Parameters                                                                                              
 cp_a0_PT1   = 0;                                                                                                
 cp_b0_PT1   = 0;                                                                                            
 cp_b1_PT1   = 0;                                                                                            
 cp_sfra_PT1 = 0;                                                                                            
 cp_sfrb_PT1 = 0;  
 // cp_useLP    = 0;
 cp_dphiOld  = 0;   

/* USERCODE-END:Convert                                                                                               */

/* Implementation Parameter values                                                                                    */
/* cp_b0                                                                                                              */
/* cp_b1                                                                                                              */
/* cp_sfrb0                                                                                                           */
/* cp_sfrb1                                                                                                           */
/* cp_a0_PT1                                                                                                          */
/* cp_b0_PT1                                                                                                          */
/* cp_b1_PT1                                                                                                          */
/* cp_sfra_PT1                                                                                                        */
/* cp_sfrb_PT1                                                                                                        */
/* cp_dphiOld                                                                                                         */
/* cp_b0_uI                                                                                                           */
/* cp_sfr_uI                                                                                                          */
/* cp_i_old_uI                                                                                                        */
/* cp_b0_I                                                                                                            */
/* cp_sfr_I                                                                                                           */
/* cp_i_old_I                                                                                                         */
/* cp_rawSpeed                                                                                                        */
/* cp_vGain                                                                                                           */
/* cp_sfrGain                                                                                                         */
/* cp_b1_I                                                                                                            */
/* cp_b1_uI                                                                                                           */
/* cp_sfrb1_I                                                                                                         */
/* cp_sfrb1_uI                                                                                                        */

