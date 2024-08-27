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
print('Parameter TrackingLoop:');

print('Mask-Parameter:');
print('Jp =', mp_Jp);
print('pz =', mp_p);
print('ts_fact =', mp_ts_fact);
print('n_scale =', mp_n_max);
print('bp_ts =',bp_ts);

// variables
var Kp, Ki;											// mask params of PI controller
var b0, b1;											// implementation params of PI Controller

// calculation of implementation parameters
var rho 	     = 2 * Math.PI * mp_fo;
var phi2speed    = 30 / mp_p / Math.PI;					
var torque2speed = 1 / mp_Jp;
var Ts = bp_ts;

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
	b0 = Ki * Ts;
	b1 = Kp;
} else if (mp_method == "tustin") {
	// G(s) = Kp + Ki/s -> G(z) = ( (Ki*Ts/2+Kp)*z + Ki*Ts/2-Kp )/(z-1)
	b0 = Ki * Ts;
	b1 = Ki * Ts/2 + Kp;
} 

/* set implementation param */
// b0
cp_b0_torque = b0;
// b1
cp_b1_torque = b1;


print('-----------------------');
print('Implementation Parameter PI-Controller');
print('b0 =', b0);
print('b1 =', b1);


/******************** Speed (I controller) ********************/
Ki = torque2speed;
Kp = 0;

// calculate coefficients
if (mp_method == "zoh") {
	// Zero order hold (zoh):
	// G(s) = Kp + Ki/s -> G(z) = Kp + Ki*Ts*1/(z-1)
	b0 = Ki * Ts;
	b1 = Kp;
} else if (mp_method == "tustin") {
	// G(s) = Kp + Ki/s -> G(z) = ( (Ki*Ts/2+Kp)*z + Ki*Ts/2-Kp )/(z-1)
	b0 = Ki * Ts;
	b1 = Ki * Ts / 2 + Kp;
}


/* set implementation param */
// b0
cp_b0_speed = b0;

// b1
cp_b1_speed = b1;

print('-----------------------');
print('Implementation Parameter I-controller');
print('b0 =', b0);
print('b1 =', b1);

/******************** Angle (uI controller) ********************/
Ki = 2 * Math.PI * mp_p / 60;
Kp = 0;
// calculate coefficients
 if (mp_method == "zoh") {
	//Zero order hold (zoh):
	// G(s) = Ki/s -> G(z) = Ki*Ts*1/(z-1)
	b0 = Ki * Ts;
	b1 = Kp;
} else if (mp_method == "tustin") {
	// G(s) = Ki/s -> G(z) = 1/2*Ki*Ts*(z+1)/(z-1)
	b0 = Ki * Ts;
	b1 = (Ki * Ts)/2 + Kp;
}
cp_b0_angle  = b0;
cp_b1_angle  = b1;

print('-----------------------');
print('Implementation Parameter uI-controller');
print('b0 =', b0);
print('b1 =', b1);

/******************** Gain ********************/
cp_vGain = phi2speed * 3 * rho;

print('-----------------------');
print('I-controller Gain');
print('VGain =', cp_vGain);


/******************** Speed estimation type ********************/
if ( mp_estimation == "high dynamics") {
	cp_rawSpeed = true;
} else if (mp_estimation == "less noise"){
	cp_rawSpeed = false;
}


/* USERCODE-END:Convert                                                                                               */

/* Implementation Parameter values                                                                                    */
/* cp_vGain                                                                                                           */
/* cp_b0_torque                                                                                                       */
/* cp_b1_torque                                                                                                       */
/* cp_b0_speed                                                                                                        */
/* cp_b1_speed                                                                                                        */
/* cp_b0_angle                                                                                                        */
/* cp_b1_angle                                                                                                        */
/* cp_rawSpeed                                                                                                        */

