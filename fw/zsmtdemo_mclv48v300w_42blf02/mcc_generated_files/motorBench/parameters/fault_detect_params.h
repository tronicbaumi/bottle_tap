/* This is an autogenerated file from a template. Do not edit this file as it will be overwritten.*/
/**
 *
 * fault_detect_params.h
 *
 * Fault detection parameters
 *
 * Component: supervisory
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
#ifndef __FAULT_DETECT_PARAMS_H
#define __FAULT_DETECT_PARAMS_H

#ifdef  __cplusplus
extern "C" {
#endif

/* overcurrent threshold (109.2% of rated allowable current) */
#define THRESHOLD_OVERCURRENT_STALL_DETECT       2760      // Q15(  0.08423) =   +3.71347 A           =   +3.71359 A           - 0.0034%

/*
 * natural_freq_current:           1.218 kHz
 * current loop natural frequency

 * natural_freq_velocity:          9.409  Hz
 * velocity loop natural frequency
 */

/* decimation factor for 2 stage filter LPF */
#define DECIMATION_FACTOR                     100      // Q0(100.00000)  = +100.00000             = +100.00000             + 0.0000%
/* 
 * Coefficient a1 for 2 stage implementation of LPF. Equation used for calculation:
 * f3db*Ts*2*pi. f3db for 1st stage is 10hz
 */
#define DECIMATION_FILTER_LPF1_VARIANCE_DETECT_COEFFA1        103      // Q15(  0.00314) =  +10.00547 Hz          =  +10.00000 Hz          + 0.0547%
/* 
 * Coefficient a1 for 2 stage implementation of LPF. Equation used for calculation:
 * f3db*Ts*2*pi. f3db for second stage is 1/10th of the natural frequency, Ts is 1/200hz
 */
#define DECIMATION_FILTER_LPF2_VARIANCE_DETECT_COEFFA1        969      // Q15(  0.02957) = +941.29114 mHz         = +940.93116 mHz         + 0.0383%
/* 
 * LPF filter coefficient for over current detect. Equation used for calculation:
 * f3db*Ts*2*pi f3d is equal to natural frequency
 */
#define FILTER_LPF_OVERCURRENT_DETECT          97      // Q15(  0.00296) =   +9.42263 Hz          =   +9.40931 Hz          + 0.1415%
/* 
 * LPF filter coefficient for negative Ed detect. Equation used for calculation:
 * f3db*Ts*2*pi f3d is equal to natural frequency
 */
#define FILTER_LPF_NEGATIVE_ED_DETECT          97      // Q15(  0.00296) =   +9.42263 Hz          =   +9.40931 Hz          + 0.1415%
/* 
 * HPF filter coefficient for 16bit implementation of HPF.
 * f3db is 2x natural frequency.
 */
#define FILTER_HPF_VARIANCE_DETECT            387      // Q16(  0.00591) =  +18.79668 Hz          =  +18.81862 Hz          - 0.1166%
/* 
 * Timer threshold to trigger low speed detect.
 * It is set to 3 times (1/natural frequency of velocity loop)
 */
#define ACTIVE_TIMER_THRESHOLD_LOW_SPEED_DETECT       6377      // Q0(6377.00000) = +318.85000 ms          = +318.83310 ms          + 0.0053%
/* 
 * Inactive timer threshold for low speed detect.
 * It is set to (2.0/natural frequency of velocity loop),
 * in units of the ADC ISR period.
 */
#define INACTIVE_TIMER_THRESHOLD_LOW_SPEED_DETECT       6377      // Q0(6377.00000) = +318.85000 ms          = +318.83310 ms          + 0.0053%
/* 
 * Overcurrent detector. Normally if the saturation limit was exceeded,
 * then we have a fault in the controllers.
 * then the error should immediately trigger
 * Timer threshold to trigger over currents detect.
 * It is set to 2 times (1/natural frequency of current loop)
 */
#define TIMER_COUNTS_OVERCURRENT_DETECT         33      // Q0( 33.00000)  =   +1.65000 ms          =   +1.64264 ms          + 0.4482%
/* 
 * Timer threshold to trigger negative Ed stall detect.
 * It is set to 5 times (1/natural frequency of velocity loop)
 */
#define ACTIVE_TIMER_THRESHOLD_NEGATIVE_ED_DETECT      10628      // Q0(10628.00000) = +531.40000 ms          = +531.38850 ms          + 0.0022%
/* 
 * Timer threshold to trigger negative Ed stall detect.
 * It is set to 5 times (1/natural frequency of velocity loop)
 */
#define INACTIVE_TIMER_THRESHOLD_NEGATIVE_ED_DETECT      10628      // Q0(10628.00000) = +531.40000 ms          = +531.38850 ms          + 0.0022%
/* 
 * Timer threshold to trigger stall detect based on torque angle.
 * It is set to 3 times (1/natural frequency of velocity loop)
 */
#define ACTIVE_TIMER_THRESHOLD_TORQUE_ANGLE_DETECT       6377      // Q0(6377.00000) = +318.85000 ms          = +318.83310 ms          + 0.0053%
/* 
 * Inactive Timer threshold for stall detect based on torque angle.
 * It is set to 3 times (1/natural frequency of velocity loop)
 */
#define INACTIVE_TIMER_THRESHOLD_TORQUE_ANGLE_DETECT       6377      // Q0(6377.00000) = +318.85000 ms          = +318.83310 ms          + 0.0053%
/* 
 * Timer threshold to trigger stall detect based on variance in Ed and Eq.
 * It is set to (1/natural frequency of velocity loop)
 */
#define TIMER_COUNTS_VARIANCE_DETECT           21      // Q0( 21.00000)  = +105.00000 ms          = +106.27770 ms          - 1.2022%

/* Threshold for under speed detect as a fixed fraction of minimum velocity */
#define THRESHOLD_UNDERSPEED_STALL_DETECT  ((int16_t)(0.333*MCAF_VELOCITY_COMMAND_MIN))
/* Ed detect threshold */
#define THRESHOLD_ED_STALL_DETECT               4      // Q15(  0.00012) =   +9.26514 mV          =  +10.00000 mV          - 7.3486%

/*
 * max error from modified polynomial approximation 0.045475
 * limited normalized frequency omega_c1 = 0.1
 * max error above omega_c1 = 0.018502
 */
/* torque angle threshold polynomial, constant term */
#define STALL_DETECT_TORQUE_ANGLE_COEFF0       6969      // Q15(  0.21268) = +212.67700 m           = +212.68667 m           - 0.0045%
/* torque angle threshold polynomial, linear term */
#define STALL_DETECT_TORQUE_ANGLE_COEFF1      22773      // Q15(  0.69498) = +694.97681 m           = +694.97778 m           - 0.0001%
/* torque angle threshold polynomial, quadratic term */
#define STALL_DETECT_TORQUE_ANGLE_COEFF2       2698      // Q15(  0.08234) =  +82.33643 m           =  +82.33555 m           + 0.0011%
#define STALL_DETECT_TORQUE_ANGLE_K         11732      // Q15(  0.35803) = +358.03223 m           = +358.04460 m           - 0.0035%
/* Maximum velocity for torque angle stall detection (we inhibit at faster speeds) */
#define STALL_DETECT_TORQUE_ANGLE_VELOCITY_THRESHOLD       8738      // Q15(  0.26666) = +152.63719 rad/s       = +152.63952 rad/s       - 0.0015%

/* overvoltage fault threshold */
#define VDC_OVERVOLTAGE_THRESHOLD           21586      // Q15(  0.65875) =  +49.99931 V           =  +50.00000 V           - 0.0014%
/* undervoltage fault threshold */
#define VDC_UNDERVOLTAGE_THRESHOLD           4317      // Q15(  0.13174) =   +9.99940 V           =  +10.00000 V           - 0.0060%
/* overtemperature fault threshold */
#define MCAF_OVERTEMPERATURE_THRESHOLD       5000      // Q15(  0.15259) =  +50.00000 C           =  +50.00000 C           + 0.0000%

#ifdef  __cplusplus
}
#endif

#endif // __FAULT_DETECT_PARAMS_H
