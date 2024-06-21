/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1603 $
 * $LastChangedDate:: 2019-01-21 19:02:13 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */

/* USERCODE-BEGIN:ExternalModules                                                                                     */
/* USERCODE-END:ExternalModules                                                                                       */

/* Block sample time                                                                                                  */
/* bp_ts                                                                                                              */

/* Mask parameter values                                                                                              */
/* mp_Jp (Number)                                                                                                     */
/* mp_fo (Number)                                                                                                     */
/* mp_p (Number)                                                                                                      */
/* mp_estimation (String)                                                                                             */
/* mp_method (String)                                                                                                 */
/* mp_n_max (Number)                                                                                                  */
/* mp_ts_fact (Number)                                                                                                */

/* USERCODE-BEGIN:Convert                                                                                             */
// validation
if (mp_ts_fact != 4) {
	throw "Sample time factor must be 4!\n";
}
if (mp_p < 1) {
	throw "Number of pole pairs must not be smaller than one!\n";
}
if (mp_n_max == 0) {
	throw "n_max must not be zero!\n";
}

if (mp_Jp == 0) {
	throw "Moment of inertia must not be zero!\n";
}


print('Tracking Loop FiP32 Parameter:');
print('Mask Parameter:');
print('pz=', mp_p);
print('nmax=', mp_n_max);
print('Jp=', mp_Jp);
print('fo=', mp_fo);
print('bp_ts=', bp_ts);


// constants
var BITS32 = 32;
var MIN_INT_COEFF = 15;								// minimal allowed integration coefficient

// variables
var Kp, Ki;											// mask params of PI controller
var b0, b1;											// implementation params of PI Controller

// calculation of implementation parameters
var rho = 2 * Math.PI * mp_fo;
var phi2speed    = 30 / mp_n_max / mp_p;			// factor due to scaling 			
var torque2speed = 1 / mp_Jp;				 

/********** Torque (PI controller) **********/
/*
 * design rule for observer parameter: kp = 3*rho^2*Jp (integral-term of observer); ki = rho^3*Jp
 * (double-integral-term of observer))
 */

/* apply design rule */
Kp = phi2speed * 3 * rho * rho / torque2speed;
Ki = phi2speed * rho * rho * rho / torque2speed;

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
// b0
cp_sfrb0_torque = getQFormat(b0, BITS32, true);
cp_b0_torque    = getQValue(b0, cp_sfrb0_torque, BITS32, true);
// b1
cp_sfrb1_torque = getQFormat(b1, BITS32, true);
cp_b1_torque    = getQValue(b1, cp_sfrb1_torque, BITS32, true);

print('Implementation Parameter PI-Controller:');
print('b0_torque=', cp_b0_torque);
print('b1_torque=', cp_b1_torque);

/******************** Speed (I controller) ********************/
Ki = torque2speed;
Kp = 0;

// calculate coefficients
if (mp_method == "zoh") {
	// Zero order hold (zoh):
	// G(s) = Kp + Ki/s -> G(z) = Kp + Ki*Ts*1/(z-1)
	b0 = Ki * bp_ts;
	b1 = Kp;
} else if (mp_method == "tustin") {
	// G(s) = Kp + Ki/s -> G(z) = ( (Ki*Ts/2+Kp)*z + Ki*Ts/2-Kp )/(z-1)
	b0 = Ki * bp_ts;
	b1 = Ki * bp_ts / 2 + Kp;
}

/* set implementation param */
// b0
cp_sfrb0_speed = getQFormat(b0, BITS32, true);
cp_b0_speed   = getQValue(b0, cp_sfrb0_speed, BITS32, true);
// b1
cp_sfrb1_speed = getQFormat(b1, BITS32, true);
cp_b1_speed    = getQValue(b1, cp_sfrb1_speed, BITS32, true);

if (cp_b0_speed < MIN_INT_COEFF) {
	throw "Accuracy-Error: speed system is ill conditioned -> try to decrease Jp or increase the sample time factor!\n";
}

print('Implementation Parameter I-Controller:');
print('b0_speed=', cp_b0_speed);
print('b1_speed=', cp_b1_speed);

/******************** Angle (uI controller) ********************/
Ki = 2 * mp_n_max * mp_p / 60;
Kp = 0;
// calculate coefficients
 if (mp_method == "zoh") {
	//Zero order hold (zoh):
	// G(s) = Ki/s -> G(z) = Ki*Ts*1/(z-1)
	b0 = Ki * bp_ts;
	b1 = Kp;
} else if (mp_method == "tustin") {
	// G(s) = Ki/s -> G(z) = 1/2*Ki*Ts*(z+1)/(z-1)
	b0 = Ki * bp_ts;
	b1 = (Ki * bp_ts)/2 + Kp;
}
cp_sfrb0_angle = getQFormat(b0, BITS32, true);
cp_b0_angle  = getQValue(b0, cp_sfrb0_angle, BITS32, true);

cp_sfrb1_angle = getQFormat(b1, BITS32, true);
cp_b1_angle    = getQValue(b1, cp_sfrb1_angle, BITS32, true);

if (cp_b0_angle < MIN_INT_COEFF) {
	throw "Accuracy-Error: angle system is ill conditioned -> try to increase nmax or the sample time factor!\n";
}
print('Implementation Parameter uI-Controller:');
print('b0_angle=', cp_b0_angle);
print('b1_angle=', cp_b1_angle);

/******************** Gain ********************/
var V = phi2speed * 3 * rho;
cp_sfrGain  = getQFormat(V, BITS32, true);
cp_vGain    = getQValue(V, cp_sfrGain, BITS32, true);
print('Implementation Parameter Gain:');
print('sfr Gain=', cp_sfrGain);
print('v Gain=', cp_vGain);

/******************** Speed estimation type ********************/
if ( mp_estimation == "high dynamics") {
	cp_rawSpeed = true;
} else if (mp_estimation == "less noise"){
	cp_rawSpeed = false;
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

/* USERCODE-END:Convert                                                                                               */

/* Implementation Parameter values                                                                                    */
/* cp_vGain                                                                                                           */
/* cp_sfrGain                                                                                                         */
/* cp_b0_torque                                                                                                       */
/* cp_b1_torque                                                                                                       */
/* cp_sfrb0_torque                                                                                                    */
/* cp_sfrb1_torque                                                                                                    */
/* cp_b0_speed                                                                                                        */
/* cp_b1_speed                                                                                                        */
/* cp_sfrb0_speed                                                                                                     */
/* cp_sfrb1_speed                                                                                                     */
/* cp_b0_angle                                                                                                        */
/* cp_b1_angle                                                                                                        */
/* cp_sfrb0_angle                                                                                                     */
/* cp_sfrb1_angle                                                                                                     */
/* cp_rawSpeed                                                                                                        */

