/* This is an autogenerated file from a template. Do not edit this file as it will be overwritten.*/
/**
 *
 * zsmt_params.h
 *
 * Component: commutation
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
#ifndef __ZSMT_PARAMS_H
#define __ZSMT_PARAMS_H

#ifdef  __cplusplus
extern "C" {
#endif

/* 
 * Vexc:                           1.427  V
 * tau:                            5.000 ms
 * zeta:                           1.500  
 * executionDivider:               2.000  
 * elim:                         999.970 m
 * A:                            0.333330  
 * A1:                             8.164 mA
 * A2norm:                       511.984375  
 * A2:                            11.613  /A
 * A1A2:                         0.094806  
 * Ki:                           421.916 krad/s^2
 *                                 4.029 MRPM/s
 * Kp:                             6.329 krad/s
 *                                60.435 kRPM
 * dt:                            50.000 us
 * timestep:                     100.000 us
 * omega_lpf:                     20.000 krad/s
 *                               190.986 kRPM
 * alignTime:                      1.000 ms
 * angleLockDelay:                50.000 ms
 * angleProbeCurrent:              2.550  A
 * angleProbeTime:                10.000 ms
 * angleProbeAccumGain:                1  
 * angleProbeSlewTime:           196.075 us
 * angleProbeSlewRate:            13.005 kA/s
 * angleProbeBlankingTime:       522.868 us
 * correctionGainDc:               0.000  rad/A
 * pllLockTime:                    5.000 ms
 * pllLockSpeedLimit:              5.724  rad/s
 *                                54.660  RPM
 * pllLockCurrentLimit:            1.020  A
 * pllLockCurrentSquaredLimit:     1.040  A^2
 */

/* Excitation voltage amplitude */
#define ZSMT_EXCITATION_VOLTAGE_AMPLITUDE        616      // Q15(  0.01880) =   +1.42683 V           =   +1.42746 V           - 0.0437%
/* Proportional gain of PLL = 2*zeta/B/tau */
#define ZSMT_PLL_KP                         17784      // Q11(  8.68359) =   +6.32860 krad/s      =   +6.32874 krad/s      - 0.0021%
#define ZSMT_PLL_KP_Q                          11
/* Integral gain of PLL = 1/B/tau^2 */
#define ZSMT_PLL_KI                          3794      // Q16(  0.05789) = +421.91577 krad/s^2    = +421.91569 krad/s^2    + 0.0000%
/* PLL integrator time scaling factor */
#define ZSMT_PLL_DT                          2388      // Q16(  0.03644) =  +49.99724 us          =  +50.00000 us          - 0.0055%
/* Scaling gain for HFI error */
#define ZSMT_ERROR_GAIN                     32767      // Q6(511.98438)  = +511.98438             = +511.98438             + 0.0000%
/* Error limit for PLL */
#define ZSMT_ERROR_LIMIT                    32767      // Q15(  0.99997) = +999.96948 m           = +999.97000 m           - 0.0001%
#define ZSMT_PLL_EXECUTION_DIVIDER                   2 // ()         defines PLL execution rate based on main control update rate
/* Pole of input low-pass filter */
#define ZSMT_FILTER_GAIN                    65535      // Q16(  0.99998) =   +9.99985 krad/s      =  +20.00000 krad/s      -50.0008%
/* Align delay */
#define ZSMT_ALIGN_TIME                        20      // Q0( 20.00000)  =   +1.00000 ms          =   +1.00000 ms          + 0.0000%
/* Angle lock delay */
#define ZSMT_ANGLE_LOCK_DELAY                1000      // Q0(1000.00000) =  +50.00000 ms          =  +50.00000 ms          + 0.0000%
/* Angle probe duration */
#define ZSMT_ANGLE_PROBE_TIME                 200      // Q0(200.00000)  =  +10.00000 ms          =  +10.00000 ms          + 0.0000%
/* Angle probe accumulator gain */
#define ZSMT_ANGLE_PROBE_ACCUM_GAIN           328      // Q16(  0.00500) =   +1.00098             =   +1.00000             + 0.0977%
/* Angle probe blanking time */
#define ZSMT_ANGLE_PROBE_BLANKING_TIME         10      // Q0( 10.00000)  = +500.00000 us          = +522.86797 us          - 4.3736%
/* Angle probe slew rate */
#define ZSMT_ANGLE_PROBE_SLEW_RATE            483      // Q15(  0.01474) =  +12.99713 kA/s        =  +13.00520 kA/s        - 0.0620%
/* DC correction gain */
#define ZSMT_CORRECTION_GAIN_DC                 0      // Q14(  0.00000) =   +0.00000 rad/A       =   +0.00000 rad/A       + 0.0000%
/* Required PLL lock time */
#define ZSMT_PLL_LOCK_TIME                    100      // Q0(100.00000)  =   +5.00000 ms          =   +5.00000 ms          + 0.0000%
/* Maximum allowed speed for ZSMT startup */
#define ZSMT_PLL_LOCK_SPEED_LIMIT             328      // Q15(  0.01001) =   +5.72957 rad/s       =   +5.72398 rad/s       + 0.0977%
/* Maximum allowed squared current for ZSMT startup */
#define ZSMT_PLL_LOCK_CURRENT_SQUARED_LIMIT         18      // Q15(  0.00055) =   +1.06773 A^2         =   +1.04040 A^2         + 2.6273%

/**
 * Returns whether ZS/MT estimator operates in a standalone manner.
 * (whether it uses its own sine/cosine calculations and Park transforms)
 *
 * @return whether ZS/MT estimator operates in a standalone manner
 */
inline static bool ZSMT_IsStandaloneEstimator(void)
{
    return true;
}

#ifdef  __cplusplus
}
#endif

#endif // __ZSMT_PARAMS_H
