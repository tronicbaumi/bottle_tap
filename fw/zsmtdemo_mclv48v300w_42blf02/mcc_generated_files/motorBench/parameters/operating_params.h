/* This is an autogenerated file from a template. Do not edit this file as it will be overwritten.*/
/**
 *
 * operating_params.h
 *
 * Operating parameters (speed ranges, slew rates, etc.)
 *
 * Component: miscellaneous
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
#ifndef __OPERATING_PARAMS_H
#define __OPERATING_PARAMS_H

#include "motor_params.h"
/* needed for motor's relative saliency */

#ifdef  __cplusplus
extern "C" {
#endif

/**** parameters for speed reference ***/

/* Maximum velocity command */
#define MCAF_VELOCITY_COMMAND_MAX            2185      // Q15(  0.06668) = +364.47784 RPM         = +364.40000 RPM         + 0.0214%
/* Minimum velocity command */
#define MCAF_VELOCITY_COMMAND_MIN            1079      // Q15(  0.03293) = +179.98700 RPM         = +180.01360 RPM         - 0.0148%
/* Nominal velocity (base speed): nominal no-load speed at nominal supply voltage with no flux weakening */
#define MCAF_VELOCITY_NOMINAL               21845      // Q15(  0.66666) =   +3.64394 kRPM        =   +3.64400 kRPM        - 0.0015%

/* --- Miscellaneous operating velocity parameters --- */

/*
 * velocity_fullscale:           572.398  rad/s
 *                                 5.466 kRPM
 * velocity_maximum:              38.160  rad/s
 *                               364.400  RPM
 * velocity_minimum:              18.851  rad/s
 *                               180.014  RPM
 * velocity_nominal:             381.599  rad/s
 *                                 3.644 kRPM
 * rho_xi_thresh:                0.111111  
 * ilimit                                 
 *   ipeak:                        3.400  A
 * run                                    
 *   slewrate_accel:              19.758 krad/s^2
 *                               188.670 kRPM/s
 *   slewrate_decel:             831.596  rad/s^2
 *                                 7.941 kRPM/s
 *   t_coastdown:                428.616 ms
 *   closedLoopStopping                   
 *     time:                     500.000 ms
 *     speed:                     19.080  rad/s
 *                               182.200  RPM
 */

/* Minimum time for achieving a closed-loop stop below the speed threshold */
#define MCAF_CLOSED_LOOP_STOPPING_TIME      10000      // Q0(10000.00000) = +500.00000 ms          = +500.00000 ms          + 0.0000%
/* Speed threshold for a closed-loop stop */
#define MCAF_CLOSED_LOOP_STOPPING_SPEED       1092      // Q15(  0.03333) =  +19.07528 rad/s       =  +19.07994 rad/s       - 0.0244%

#define VELOCITY_SLEWRATE_LIMIT1 32000
/* slew rate limit for velocity commands during acceleration */
#define VELOCITY_SLEWRATE_LIMIT_ACCEL        1131      // Q15(  0.03452) =  +19.75654 rad/s       =  +19.75753 rad/s       - 0.0050%
/* slew rate limit for velocity commands during deceleration */
#define VELOCITY_SLEWRATE_LIMIT_DECEL          48      // Q15(  0.00146) = +838.47390 mrad/s      = +831.59623 mrad/s      + 0.8270%
/* estimate of worst-case time needed to decelerate to a stop */
#define VELOCITY_COASTDOWN_TIME              8572      // Q0(8572.00000) = +428.60000 ms          = +428.61636 ms          - 0.0038%

#define RATED_MOTOR_IPEAK                          3.4 // (A)        rated allowable current of motor (peak amplitude)

/**** Motor saliency ****/

/*  Relative saliency threshold = (xi-1.0)/(xi+1.0)  */
#define MCAF_RELATIVE_SALIENCY_THRESHOLD       3641      // Q15(  0.11111) = +111.11450 m           = +111.11111 m           + 0.0031%

/**
 * This function returns whether the motor's saliency is significant
 *
 * @return true if the motor's saliency is significant as per set threshold
 */
inline static bool MCAF_IsMotorSaliencySignificant(void)
{
    return (MCAF_MOTOR_RELATIVE_SALIENCY > MCAF_RELATIVE_SALIENCY_THRESHOLD) ||
           (MCAF_MOTOR_RELATIVE_SALIENCY < -MCAF_RELATIVE_SALIENCY_THRESHOLD);
}
                            
#ifdef  __cplusplus
}
#endif

#endif // __OPERATING_PARAMS_H