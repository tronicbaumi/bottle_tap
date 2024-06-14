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
#define MCAF_VELOCITY_COMMAND_MAX           23980      // Q15(  0.73181) =   +4.00008 kRPM        =   +4.00000 kRPM        + 0.0020%
/* Minimum velocity command */
#define MCAF_VELOCITY_COMMAND_MIN             437      // Q15(  0.01334) =  +72.89557 RPM         =  +72.88000 RPM         + 0.0214%
/* Nominal velocity (base speed): nominal no-load speed at nominal supply voltage with no flux weakening */
#define MCAF_VELOCITY_NOMINAL               21845      // Q15(  0.66666) =   +3.64394 kRPM        =   +3.64400 kRPM        - 0.0015%

/* --- Miscellaneous operating velocity parameters --- */

/*
 * velocity_fullscale:           572.398  rad/s
 *                                 5.466 kRPM
 * velocity_maximum:             418.879  rad/s
 *                                 4.000 kRPM
 * velocity_minimum:               7.632  rad/s
 *                                72.880  RPM
 * velocity_nominal:             381.599  rad/s
 *                                 3.644 kRPM
 * rho_xi_thresh:                0.090909  
 * ilimit                                 
 *   ipeak:                        3.400  A
 * run                                    
 *   slewrate_accel:               9.879 krad/s^2
 *                                94.335 kRPM/s
 *   slewrate_decel:             814.263  rad/s^2
 *                                 7.776 kRPM/s
 *   t_coastdown:                714.361 ms
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
#define VELOCITY_SLEWRATE_LIMIT_ACCEL         566      // Q15(  0.01727) =   +9.88700 rad/s       =   +9.87876 rad/s       + 0.0834%
/* slew rate limit for velocity commands during deceleration */
#define VELOCITY_SLEWRATE_LIMIT_DECEL          47      // Q15(  0.00143) = +821.00569 mrad/s      = +814.26304 mrad/s      + 0.8281%
/* estimate of worst-case time needed to decelerate to a stop */
#define VELOCITY_COASTDOWN_TIME             14287      // Q0(14287.00000) = +714.35000 ms          = +714.36059 ms          - 0.0015%

#define RATED_MOTOR_IPEAK                          3.4 // (A)        rated allowable current of motor (peak amplitude)

/**** Motor saliency ****/

/*  Relative saliency threshold = (xi-1.0)/(xi+1.0)  */
#define MCAF_RELATIVE_SALIENCY_THRESHOLD       2979      // Q15(  0.09091) =  +90.91187 m           =  +90.90909 m           + 0.0031%

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