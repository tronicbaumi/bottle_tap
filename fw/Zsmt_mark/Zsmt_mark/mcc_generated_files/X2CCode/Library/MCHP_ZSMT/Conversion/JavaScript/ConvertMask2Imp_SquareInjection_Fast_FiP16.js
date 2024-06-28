/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */

/* USERCODE-BEGIN:ExternalModules                                                                                     */
/* USERCODE-END:ExternalModules                                                                                       */

/* Block sample time                                                                                                  */
/* bp_ts                                                                                                              */

/* Mask parameter values                                                                                              */
/* mp_VoltPhasor (Number)                                                                                             */
/* mp_T1 (Number)                                                                                                     */
/* mp_deltaT (Number)                                                                                                 */
/* mp_Tpulse (Number)                                                                                                 */
/* mp_DelayPLL (Number)                                                                                               */
/* mp_DelayCtrl (Number)                                                                                              */
/* mp_uInj (Number)                                                                                                   */
/* mp_uDCmax (Number)                                                                                                 */
/* mp_ts_fact (Number)                                                                                                */

/* USERCODE-BEGIN:Convert                                                                                             */
var INT16_MAX = 32768;

/* calc amplitude of voltage phasor in Q15 format */
cp_iUsAmp  = mp_VoltPhasor/mp_uDCmax*INT16_MAX;

/* calc pulse duration in samples */
cp_t_pulse = Math.round(mp_Tpulse);

/* block sample time */
if (mp_ts_fact <= 0){
	mp_ts_fact = 1;
}
/* sample time in ms */
var Ts_ms = 1000*bp_ts;	// unit is ms
var Ts_s = bp_ts		// unit is s

print("Ts_s");

/***** Params of initial angle estimation ******/
/* starting point in time: [mp_T1] = ms  */
cp_t1 	  = mp_T1/Ts_ms; 		// t1 in samples (updates)
cp_deltaT = mp_deltaT/Ts_ms;	// period in samples (updates)

/* check user input */
if (2*mp_Tpulse >= mp_deltaT/Ts_ms - 5){
 throw "SquareInjection_Fast-Block: Wrong Mask-Input! 2*TPulse < deltaT-5 must be satisfied!";
}
 
/***** Params of HF injection ******/
/* calc amplitude of HF-Voltage in Q15 format */
cp_uInjAmp = mp_uInj/mp_uDCmax*INT16_MAX;

/* get delays [] = s */
var defaultDelay = 0.01; // []=s

/* check user input */
if (mp_DelayPLL<0){
	mp_DelayPLL = 0;
}
if ((mp_DelayCtrl<0)||(mp_DelayCtrl <= mp_DelayPLL)){
	mp_DelayCtrl = mp_DelayPLL + defaultDelay;
}

cp_delayPLL  = mp_DelayPLL/Ts_s;	// delay in samples
if (cp_delayPLL > INT16_MAX){
	throw "SquareInjection_Fast-Block: Wrong Mask-Input! The PLL-Delay is too high!";
}
cp_delayCtrl = mp_DelayCtrl/Ts_s;	// delay in samples
if (cp_delayCtrl > INT16_MAX){
	throw "SquareInjection_Fast-Block: Wrong Mask-Input! The Controller-Delay is too high!";
}

/* USERCODE-END:Convert                                                                                               */

/* Implementation Parameter values                                                                                    */
/* cp_iUsAmp                                                                                                          */
/* cp_t_pulse                                                                                                         */
/* cp_t1                                                                                                              */
/* cp_deltaT                                                                                                          */
/* cp_delayPLL                                                                                                        */
/* cp_delayCtrl                                                                                                       */
/* cp_uInjAmp                                                                                                         */

