/* This is an autogenerated file from a template. Do not edit this file as it will be overwritten.*/
/**
 *
 * startup_params.h
 * 
 * Startup parameters
 *
 * Component: state machine
 */ /*
 *
 * Motor Control Application Framework
 * R7/RC37 (commit 116330, build on 2023 Feb 09)
 *
 * (c) 2017 - 2023 Microchip Technology Inc. and its subsidiaries. You may use
 * this software and any derivatives exclusively with Microchip products.
 *
 * This software and any accompanying information is for suggestion only.
 * It does not modify Microchip's standard warranty for its products.
 * You agree that you are solely responsible for testing the software and
 * determining its suitability.  Microchip has no obligation to modify,
 * test, certify, or support the software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE, OR ITS INTERACTION WITH
 * MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY
 * APPLICATION.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL,
 * PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF
 * ANY KIND WHATSOEVER RELATED TO THE USE OF THIS SOFTWARE, THE
 * motorBench(R) DEVELOPMENT SUITE TOOL, PARAMETERS AND GENERATED CODE,
 * HOWEVER CAUSED, BY END USERS, WHETHER MICROCHIP'S CUSTOMERS OR
 * CUSTOMER'S CUSTOMERS, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
 * CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
 * OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
 * SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF
 * THESE TERMS.
 *
 *
 ******************************************************************************/
#ifndef __STARTUP_PARAMS_H
#define __STARTUP_PARAMS_H

#ifdef  __cplusplus
extern "C" {
#endif

//************** Start-Up Parameters **************

/*
 * Startup operating parameters:
 *
 * Istartup:                     340.000 mA
 * Kspring:                       56.604 mNm/rad
 * omega_crit:                   253.984  rad/s
 *                                 2.425 kRPM
 * omega0:                        10.471  rad/s
 *                                99.991  RPM
 * omega_min:                      9.540  rad/s
 *                                91.100  RPM
 * omega1:                        10.471  rad/s
 *                                99.991  RPM
 * accel_limit_0:                725.715 mrad/s^2
 *                                 6.930  RPM/s
 * accel_limit_1:                  3.629  rad/s^2
 *                                34.650  RPM/s
 * accel0:                       725.715 mrad/s^2
 *                                 6.930  RPM/s
 * accel1:                         3.629  rad/s^2
 *                                34.650  RPM/s
 * t1:                            14.429  s
 * t2:                             0.000  s
 * B_desired:                    445.732 uNm/(rad/s)
 * B_added:                      440.309 uNm/(rad/s)
 * damping_gain_ideal:            10.579 mA/(rad/s)
 * damping_gain_max:             811.690 mA/(rad/s)
 * damping_gain:                  10.579 mA/(rad/s)
 * damping_threshold:              4.188  rad/s
 *                                39.997  RPM
 * damping_Imax:                   1.700  A
 * t_rampup:                      10.863 ms
 * dIdt_rampup:                   31.300  A/s
 * t_align:                        0.000  s
 * t_hold:                         0.000  s
 * t_rampdown_decay:             157.490 ms
 * Irampdown_end:                 17.000 mA
 * rampup_angle:                 -523.599 mrad
 * align_angle_delta:            523.599 mrad
 * theta_error_converge_rate:     17.453  rad/s
 *                               166.667  RPM
 */

/* first startup threshold velocity */
#define STARTUP_ACCEL0_VELOCITY_THRESHOLD        599      // Q15(  0.01828) =  +99.91864 RPM         =  +99.99136 RPM         - 0.0727%
/* second startup threshold velocity */
#define STARTUP_ACCEL1_VELOCITY_THRESHOLD        599      // Q15(  0.01828) =  +99.91864 RPM         =  +99.99136 RPM         - 0.0727%
/* threshold velocity for damping */
#define STARTUP_DAMPING_THRESHOLD             240      // Q15(  0.00732) =  +40.03418 RPM         =  +39.99654 RPM         + 0.0941%
#define Q15_THETADELTA (Q15(THETADELTA/180.0))

/* open loop startup current ramp from initial startup current to startup current */
/* motor current from end of current rampup phase to end of startup */
#define MCAF_STARTUP_CURRENT                  253      // Q15(  0.00772) = +340.40112 mA          = +340.00000 mA          + 0.1180%
/* motor current at beginning of startup */
#define MCAF_STARTUP_CURRENT_INITIAL            0      // Q15(  0.00000) =   +0.00000 A           =   +0.00000 A           + 0.0000%
/* maximum current amplitude used for active damping */
#define STARTUP_DAMPING_IQMAX                1264      // Q15(  0.03857) =   +1.70066 A           =   +1.70000 A           + 0.0388%
/* binary point for active damping gain */
#define STARTUP_DAMPING_SHIFT                   8
/* active damping gain */
#define STARTUP_DAMPING_GAIN                   35      // Q8(  0.13672)  =  +10.53053 mA/(rad/s)  =  +10.57903 mA/(rad/s)  - 0.4585%

//value of theta_error at transition
#define THETADELTA 10           


#define STARTUP_DELTA_T_FACTOR               2388
#define STARTUP_DELTA_T_FACTOR_ACCELERATION          1
/* first startup acceleration rate */
#define STARTUP_ACCELERATION0                 136      // Q15(  0.00415) = +724.99879 mrad/s^2    = +725.71541 mrad/s^2    - 0.0987%
/* second startup acceleration rate */
#define STARTUP_ACCELERATION1                 681      // Q15(  0.02078) =   +3.63032 rad/s^2     =   +3.62858 rad/s^2     + 0.0482%

/* increase in current per control cycle, during current rampup */
#define STARTUP_TORQUE_RAMPUP_RATE              1      // Q15(  0.00003) =   +1.34546 mA          =   +1.56500 mA          -14.0279%

/* Current rampdown time constant = 0.15749 s */
/* current rampdown decay rate (=1/time constant) */
#define MCAF_RAMPDOWN_DECAY_RATE             5326      // Q24(  0.00032) =   +6.34909 1/s         =   +6.34961 1/s         - 0.0082%
#define MCAF_RAMPDOWN_DECAY_RATE_Q             24
#define MCAF_RAMPDOWN_DECAY_SHIFT (MCAF_RAMPDOWN_DECAY_RATE_Q - 16)

/* current rampdown end threshold */
#define MCAF_RAMPDOWN_END_CURRENT              13      // Q15(  0.00040) =  +17.49097 mA          =  +17.00000 mA          + 2.8880%

/* align angle shift after current rampup */
#define STARTUP_RAMPUP_ANGLE                -5461      // Q15( -0.16666) = -523.56682 mrad        = -523.59878 mrad        - 0.0061%
/* align angle shift after current rampup */
#define STARTUP_ALIGN_ANGLE_DELTA            5461      // Q15(  0.16666) = +523.56682 mrad        = +523.59878 mrad        - 0.0061%
/* hold time between current rampup and acceleration */
#define STARTUP_ALIGN_TIME                      0      // Q0(  0.00000)  =   +0.00000 s           =   +0.00000 s           + 0.0000%
/* hold time between velocity rampup and current rampdown */
#define STARTUP_HOLD_TIME                       0      // Q0(  0.00000)  =   +0.00000 s           =   +0.00000 s           + 0.0000%
// PWM loops necessary for transitioning from open loop to closed loop
#define TRANSITION_STEPS   IRP_PERCALC/4

/* convergence rate (electrical frequency) for forcing angle error towards zero, during transition to closed-loop */
#define STARTUP_THETA_ERROR_CONVERGE_RATE       2330      // Q24(  0.00014) =  +17.45203 rad/s       =  +17.45329 rad/s       - 0.0072%
#define STARTUP_THETA_ERROR_CONVERGE_RATE_Q         24


#ifdef  __cplusplus
}
#endif

#endif // __STARTUP_PARAMS_H
