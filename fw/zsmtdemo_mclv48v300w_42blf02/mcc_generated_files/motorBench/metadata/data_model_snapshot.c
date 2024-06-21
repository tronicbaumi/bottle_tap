/*
 * data_model_snapshot.c
 * 
 * Snapshot of code generation data model.
 * This information is included in the executable file
 * and does not affect any memory content in the embedded device.
 */
 
__attribute__((section("diagnostics_cinfo, info"), keep)) char MCAF_data_model_snapshot[] =
  "{\"motor\": {\"Tfr\": 0.00281660696837,\"B\": 5.42276325807e-06,\"Lq\": 0.000219"
  "977741868,\"poleCount\": 8,\"rated_current\": 3.4,\"J\": 3.50991416435e-06,\"vel"
  "ocity\": {\"nominal\": 381.5987877,\"maximum\": 418.879020479,\"units\": \"rad\\"
  "/s\"},\"L\": 0.000209919905156,\"R\": 0.483123180811,\"current\": {\"maximum\": "
  "{\"continuous\": 3.4,\"peak\": 6.0},\"units\": \"A\"},\"Ld\": 0.000199862068443,"
  "\"Ke\": 0.02774726373,\"id\": \"42blf02\"},\"controller\": {\"encoder\": {\"trac"
  "king_loop\": {\"zeta\": 1.5}},\"foc\": {\"feedback\": {\"voltage_delay\": 0}},\""
  "pll\": {\"delay_match\": true,\"properties\": {\"reference\": false},\"keInverse"
  "Scaling\": 1.0},\"operation\": {\"min_deceleration_time\": null},\"dyn_current\""
  ": {\"maxgain\": 1.1},\"zsmt\": {\"errorLimit\": 0.99997,\"properties\": {\"indep"
  "endent\": true,\"reference\": false},\"duration\": {\"lockDelay\": 0.05},\"probe"
  "\": {\"accumGain\": 1.0}},\"fault_detect\": {\"recovery\": {\"attempts\": 3}}},"
  "\"metadata\": {\"MCC\": {\"architecture\": \"melody\",\"peripherals\": {\"instan"
  "ces\": [{\"name\": \"ADC1\",\"type\": \"adc\"},{\"name\": \"PWM\",\"type\": \"pw"
  "m_hs\"},{\"name\": \"QEI1\",\"type\": \"qei\"},{\"name\": \"TMR1\",\"type\": \"t"
  "imer\"},{\"name\": \"SCCP1\",\"type\": \"timer\"},{\"name\": \"UART1\",\"type\":"
  " \"uart\"},{\"name\": \"OPA1\",\"type\": \"opa\"},{\"name\": \"OPA2\",\"type\": "
  "\"opa\"},{\"name\": \"OPA3\",\"type\": \"opa\"}]},\"version\": \"5.7.1\",\"perip"
  "heral_library\": {\"name\": \"melody\",\"version\": \"NA\"}},\"data_model\": {\""
  "schema_version\": 5},\"motorBench\": {\"commit_id\": \"6062ee969f17e173cb8502638"
  "f1e3c8ee7bea3fb\",\"version\": \"2.45.0\"},\"MCAF\": {\"build\": {\"commit_id\":"
  " \"116330\",\"date_str\": \"2023 Feb 09\",\"hostname\": \"motor-control-mcaf-tag"
  "s-builder-r7-2frc37-1-0ws3m-smcgr-kthrw\",\"time\": 1675959683.33,\"time_iso\": "
  "\"2023-02-09T16:21:23.327489\",\"time_str\": \"2023 Feb 09 16:21\",\"type\": \"r"
  "elease\",\"username\": \"jenkins\",\"version\": \"R7\\/RC37\"},\"build_time\": 1"
  "675959683.33,\"build_time_iso\": \"2023-02-09T16:21:23.327489\",\"build_time_str"
  "\": \"2023 Feb 09 16:21\",\"commit_id\": \"116330\",\"version\": \"R7\\/RC37\"}}"
  ",\"scdata\": {\"setup\": {\"communications\": {\"baudrate\": 625000},\"analysis"
  "\": {\"spindown_time\": {\"units\": \"s\",\"value\": 1.0},\"max_motor_speed\": {"
  "\"units\": \"rad\\/s mechanical\",\"value\": 2094.4}},\"calibration\": {\"vdc\":"
  " {\"units\": \"V\",\"value\": 24.0},\"resistor\": {\"units\": \"ohms\",\"value\""
  ": 12.0}}}},\"autotune_result\": {\"current\": {\"Kp\": 1.48261918353,\"phase_mar"
  "gin\": 60.0,\"wc\": 7650.1148602,\"Ki\": 5288.95800685,\"pi_phase_lag\": 25.0},"
  "\"velocity\": {\"Kp\": 0.00120519684805,\"phase_margin\": 65.0,\"wc\": 12.850832"
  "2717,\"Ki\": 0.00273091393469,\"pi_phase_lag\": 10.0}},\"code_generation_tag_map"
  "\": {\"application\": \"sample\",\"diagnostics\": \"x2cscope\"},\"operating_rang"
  "e\": {\"velocity\": {\"units_qualifier\": \"mechanical\",\"units\": \"rad\\/s\","
  "\"minimum\": 130.89975}},\"build\": {\"hardware_spec\": \"mclv2:33ck256mp508_ext"
  "opamp_pim\",\"normfactor_associations\": [{\"context\": null,\"annotations\": [{"
  "\"typerefs\": [\"MCAF_U_CURRENT_ABC\",\"MCAF_U_CURRENT_ALPHABETA\",\"MCAF_U_CURR"
  "ENT_DQ\",\"MCAF_U_CURRENT\",\"MCAF_MOTOR_DATA.omegaCtrl.outMin\",\"MCAF_MOTOR_DA"
  "TA.omegaCtrl.outMax\"],\"unit\": \"I\",\"q\": 15},{\"typerefs\": [\"MCAF_MOTOR_D"
  "ATA.omegaCtrl.integrator\"],\"unit\": \"I\",\"q\": 15},{\"typerefs\": [\"MCAF_U_"
  "VOLTAGE_ABC\",\"MCAF_U_VOLTAGE_ALPHABETA\",\"MCAF_U_VOLTAGE_DQ\",\"MCAF_U_VOLTAG"
  "E\",\"MCAF_MOTOR_DATA.idCtrl.outMin\",\"MCAF_MOTOR_DATA.idCtrl.outMax\",\"MCAF_M"
  "OTOR_DATA.iqCtrl.outMin\",\"MCAF_MOTOR_DATA.iqCtrl.outMax\"],\"unit\": \"V\",\"q"
  "\": 15},{\"typerefs\": [\"MCAF_MOTOR_DATA.idCtrl.integrator\",\"MCAF_MOTOR_DATA."
  "iqCtrl.integrator\"],\"unit\": \"V\",\"q\": 31},{\"typerefs\": [\"MCAF_U_DUTYCYC"
  "LE_ABC\"],\"unit\": 1,\"q\": 15},{\"typerefs\": [\"MCAF_U_ANGLE_ELEC\"],\"unit\""
  ": \"theta_e\",\"q\": 15},{\"typerefs\": [\"MCAF_U_ANGLE_MECH\"],\"unit\": \"thet"
  "a_m\",\"q\": 15},{\"typerefs\": [\"MCAF_U_VELOCITY_MECH\"],\"unit\": \"omega_m\""
  ",\"q\": 15},{\"typerefs\": [\"MCAF_U_VELOCITY_ELEC\"],\"unit\": \"omega_e\",\"q"
  "\": 15},{\"typerefs\": [\"MCAF_U_VELOCITY_DTHETA_ELEC_DT\"],\"unit\": \"dtheta_e"
  "lec_dt\",\"q\": 15},{\"typerefs\": [\"MCAF_U_TEMPERATURE\"],\"unit\": \"Temperat"
  "ure\",\"q\": 15},{\"typerefs\": [\"MCAF_U_DIMENSIONLESS\",\"MCAF_U_DIMENSIONLESS"
  "_SINCOS\"],\"unit\": 1,\"q\": 15},{\"typerefs\": [\"MCAF_U_NORMALIZED_GAIN\"],\""
  "unit\": 1,\"q\": 14}]}]},\"drive\": {\"iout\": {\"measurement\": {\"compensation"
  "\": {\"channels\": [\"a\",\"b\"],\"values\": {\"a\": [1.0,0.0],\"b\": [0.0,1.0]}"
  ",\"offset\": {\"range\": 0.03125,\"samples\": 128,\"filterGain\": 0.25}}},\"time"
  "_constant\": 5.971e-07,\"fullscale\": 22.044,\"maximum\": {\"continuous\": 16.79"
  "},\"units\": \"A\"},\"estimator\": {\"type\": \"pll\",\"runtimeSelect\": false,"
  "\"atpll\": {\"tau1\": 0.0001,\"tau2\": 0.00219,\"kpfactor\": 1.9,\"kifactor\": 3"
  "0},\"omega1\": 732.0,\"tau\": 0.00219},\"flux_control\": {\"emag_tau\": 0.001638"
  ",\"idref_tau\": 0.006552},\"temperature\": {\"fullscale\": 327.68,\"units\": \"C"
  "\"},\"pwm\": {\"adc_sampling_delay\": 0,\"period\": 5e-05,\"duty_cycle\": {\"max"
  "imum\": 0.945,\"minimum\": 0.014},\"deadtime\": 5.9e-07},\"mcaf\": {\"adc\": {\""
  "triggerSettings\": {\"noTrigger\": \"NO_TRIGGER\",\"trigger1\": \"PWM1_TRIGGER1"
  "\",\"trigger2\": \"PWM1_TRIGGER2\"},\"channels\": {\"prefix\": \"MCAF_ADC_\",\"c"
  "ritical\": [\"PHASEA_CURRENT\",\"PHASEB_CURRENT\",\"PHASEC_CURRENT\",\"DCLINK_CU"
  "RRENT\",\"DCLINK_VOLTAGE\"],\"required\": {\"single_channel\": [\"DCLINK_CURRENT"
  "\",\"DCLINK_VOLTAGE\",\"POTENTIOMETER\"],\"dual_channel\": [\"PHASEA_CURRENT\","
  "\"PHASEB_CURRENT\",\"DCLINK_VOLTAGE\",\"POTENTIOMETER\"],\"triple_channel\": [\""
  "PHASEA_CURRENT\",\"PHASEB_CURRENT\",\"PHASEC_CURRENT\",\"DCLINK_VOLTAGE\",\"POTE"
  "NTIOMETER\"]},\"optional\": [\"PHASEA_VOLTAGE\",\"PHASEB_VOLTAGE\",\"PHASEC_VOLT"
  "AGE\",\"BRIDGE_TEMPERATURE\",\"ABSREF_VOLTAGE\"],\"fullList\": [{\"name\": \"PHA"
  "SEA_CURRENT\",\"c_fragment\": \"IphaseA\",\"description\": \"phase A current\"},"
  "{\"name\": \"PHASEB_CURRENT\",\"c_fragment\": \"IphaseB\",\"description\": \"pha"
  "se B current\"},{\"name\": \"PHASEC_CURRENT\",\"c_fragment\": \"IphaseC\",\"desc"
  "ription\": \"phase C current\"},{\"name\": \"PHASEA_VOLTAGE\",\"c_fragment\": \""
  "VphaseA\",\"description\": \"phase A voltage\"},{\"name\": \"PHASEB_VOLTAGE\",\""
  "c_fragment\": \"VphaseB\",\"description\": \"phase B voltage\"},{\"name\": \"PHA"
  "SEC_VOLTAGE\",\"c_fragment\": \"VphaseC\",\"description\": \"phase C voltage\"},"
  "{\"name\": \"DCLINK_CURRENT\",\"c_fragment\": \"Ibus\",\"description\": \"DC lin"
  "k current\"},{\"name\": \"DCLINK_VOLTAGE\",\"c_fragment\": \"Dclink\",\"descript"
  "ion\": \"DC link voltage\"},{\"name\": \"POTENTIOMETER\",\"c_fragment\": \"Poten"
  "tiometer\",\"description\": \"potentiometer voltage\"},{\"name\": \"BRIDGE_TEMPE"
  "RATURE\",\"c_fragment\": \"BridgeTemperature\",\"description\": \"bridge tempera"
  "ture voltage\"},{\"name\": \"ABSREF_VOLTAGE\",\"c_fragment\": \"AbsoluteReferenc"
  "eVoltage\",\"description\": \"absolute reference voltage\"}]}}},\"metadata\": {"
  "\"name\": \"MCLV-48V-300W Development Board\",\"id\": \"mclv-48v-300w\"},\"vdc\""
  ": {\"nominal\": 24.0,\"time_constant\": 2.87e-05,\"fullscale\": 75.9,\"maximum\""
  ": 48.0,\"units\": \"V\",\"minimum\": 12.0},\"configuration\": {\"metadata\": {\""
  "capability\": {\"adc\": {\"channel\": {\"ABSREF_VOLTAGE\": \"AN6\",\"PHASEB_VOLT"
  "AGE\": \"AN11\",\"PHASEB_CURRENT\": \"AN4\",\"PHASEA_VOLTAGE\": \"AN10\",\"PHASE"
  "C_CURRENT\": \"AN16\",\"POTENTIOMETER\": \"AN17\",\"BRIDGE_TEMPERATURE\": \"AN18"
  "\",\"DCLINK_VOLTAGE\": \"AN15\",\"PHASEA_CURRENT\": \"AN1\",\"PHASEC_VOLTAGE\": "
  "\"AN12\",\"DCLINK_CURRENT\": \"AN0\"}},\"opamp\": \"internal\",\"buttonCount\": "
  "2.0,\"current_measure\": {\"a\": true,\"b\": true,\"c\": true,\"dc\": true}},\"s"
  "caling\": {\"temperature\": {\"bridge\": {\"offset\": 5000.0,\"gain\": 0.50354}}"
  "},\"peripherals\": {\"adc\": {\"core\": {\"names\": [\"Core0\",\"Core1\",\"Share"
  "dCore\"]}}},\"pim\": {\"algorithm\": {\"single_channel\": {\"supported\": true}}"
  ",\"device\": \"33ck256mp508\",\"displayName\": \"dsPIC33CK256MP508\",\"id\": \"3"
  "3ck256mp508_dim\",\"opamp\": \"internal\",\"peripherals\": {\"adc\": {\"core\": "
  "{\"names\": [\"Core0\",\"Core1\",\"SharedCore\"]}}}},\"device\": \"33ck256mp508"
  "\",\"board\": {\"id\": \"mclv-48v-300w\"}},\"peripherals\": {\"adc\": {\"request"
  "edDedCoreSamplingTimeData\": [{\"core\": \"Core0\",\"requestedSamplingTime_us\":"
  " 0.3},{\"core\": \"Core1\",\"requestedSamplingTime_us\": 0.3}],\"dataOutputForma"
  "t\": \"Fractional\",\"channelConfig\": [{\"channel\": \"AN1\",\"sign\": \"signed"
  "\",\"core\": \"Core1\",\"customName\": \"MCAF_ADC_PHASEA_CURRENT\",\"inverted\":"
  " true},{\"channel\": \"AN4\",\"sign\": \"signed\",\"core\": \"Shared\",\"customN"
  "ame\": \"MCAF_ADC_PHASEB_CURRENT\",\"inverted\": true},{\"channel\": \"AN16\",\""
  "sign\": \"signed\",\"core\": \"Shared\",\"customName\": \"MCAF_ADC_PHASEC_CURREN"
  "T\",\"inverted\": true},{\"channel\": \"AN0\",\"sign\": \"signed\",\"core\": \"C"
  "ore0\",\"customName\": \"MCAF_ADC_DCLINK_CURRENT\",\"inverted\": false},{\"chann"
  "el\": \"AN15\",\"sign\": \"signed\",\"core\": \"Shared\",\"customName\": \"MCAF_"
  "ADC_DCLINK_VOLTAGE\"},{\"channel\": \"AN6\",\"sign\": \"unsigned\",\"core\": \"S"
  "hared\",\"customName\": \"MCAF_ADC_ABSREF_VOLTAGE\"},{\"channel\": \"AN17\",\"si"
  "gn\": \"signed\",\"core\": \"Shared\",\"customName\": \"MCAF_ADC_POTENTIOMETER\""
  "},{\"channel\": \"AN18\",\"sign\": \"unsigned\",\"core\": \"Shared\",\"customNam"
  "e\": \"MCAF_ADC_BRIDGE_TEMPERATURE\"},{\"channel\": \"AN10\",\"sign\": \"unsigne"
  "d\",\"core\": \"Shared\",\"customName\": \"MCAF_ADC_PHASEA_VOLTAGE\"},{\"channel"
  "\": \"AN11\",\"sign\": \"unsigned\",\"core\": \"Shared\",\"customName\": \"MCAF_"
  "ADC_PHASEB_VOLTAGE\"},{\"channel\": \"AN12\",\"sign\": \"unsigned\",\"core\": \""
  "Shared\",\"customName\": \"MCAF_ADC_PHASEC_VOLTAGE\"}],\"customName\": \"MCC_ADC"
  "\",\"interruptDriven\": false,\"requestedSharedSamplingTime_us\": 0.3,\"resoluti"
  "on\": 12.0},\"timer\": [{\"requestedTimerPeriod_ms\": 1.0,\"customName\": \"MCC_"
  "TMR_TICK\",\"interruptDriven\": true},{\"clkSrc\": \"FCY\",\"customName\": \"MCC"
  "_TMR_PROFILE\",\"interruptDriven\": false,\"clkPrescaler\": 1.0,\"periodCount\":"
  " 65535.0}],\"oscillator\": {\"clockSource\": \"External Oscillator with PLL\",\""
  "requestedSystemFrequency_Hz\": 0.0,\"defaultValue\": \"max-frequency\",\"setMaxi"
  "mumSystemFrequency\": true,\"clockSourceFrequency\": 8000000.0},\"opamp\": [{\"c"
  "ustomName\": \"MCC_OPA_IDC\",\"enable\": true,\"instance\": 1.0},{\"customName\""
  ": \"MCC_OPA_IA\",\"enable\": true,\"instance\": 2.0},{\"customName\": \"MCC_OPA_"
  "IB\",\"enable\": true,\"instance\": 3.0}],\"qei\": [{\"noiseFilterEnable\": fals"
  "e,\"pinMapping\": [{\"pin\": \"RC4\",\"functionName\": \"A\",\"direction\": \"in"
  "put\"},{\"pin\": \"RC5\",\"functionName\": \"B\",\"direction\": \"input\"},{\"pi"
  "n\": \"RD2\",\"functionName\": \"INDX\",\"direction\": \"input\"}],\"qeiOperatio"
  "nMode\": \"Modulo Count mode\",\"indexPulseCaptureEnable\": false,\"homePulseCap"
  "tureEnable\": false,\"homePulsePolarity\": false,\"customName\": \"MCC_QEI\",\"i"
  "ndexPulsePolarity\": false}],\"wdt\": {\"wdtEnable\": true,\"requestedWdtPeriod_"
  "ms\": 1.0,\"wdtMode\": \"Non-Window mode\",\"wdtEnableType\": \"Software\"},\"pw"
  "m\": {\"synchronousUpdate\": true,\"duty_cycle\": {\"maximum\": 0.945,\"minimum"
  "\": 0.014},\"requestedDeadTime_us\": {\"defaultValue\": 0.59,\"maximum\": 6.0,\""
  "minimum\": 0.385},\"customName\": \"MCC_PWM\",\"generatorMapping\": [{\"name\": "
  "\"MOTOR1_PHASE_A\",\"generator\": 1.0},{\"name\": \"MOTOR1_PHASE_B\",\"generator"
  "\": 2.0},{\"name\": \"MOTOR1_PHASE_C\",\"generator\": 3.0}],\"interruptDriven\":"
  " false,\"faultInputPolarity\": \"Active-low\",\"frequency\": {\"defaultValue\": "
  "20000.0,\"maximum\": 50000.0,\"minimum\": 1000.0},\"faultInputSource\": \"Device"
  " pin, PCI20\",\"polarity\": {\"lower\": \"Active-high\",\"upper\": \"Active-high"
  "\"}},\"uart\": {\"baudRate\": 115200.0,\"pinMapping\": [{\"name\": \"TX\",\"pinS"
  "elected\": \"RD14\"},{\"name\": \"RX\",\"pinSelected\": \"RD13\"}],\"stopBits\":"
  " 1.0,\"parity\": \"None\",\"dataSize\": 8.0,\"customName\": \"MCC_UART\",\"inter"
  "ruptDriven\": false},\"gpio\": [{\"isWeakPullUp\": false,\"pinSelected\": \"RE12"
  "\",\"interruptOnChange\": \"none\",\"isWeakPullDown\": false,\"customName\": \"M"
  "CAF_LED1\",\"isAnalogPin\": false,\"direction\": \"output\",\"isOpenDrain\": fal"
  "se},{\"isWeakPullUp\": false,\"pinSelected\": \"RE13\",\"interruptOnChange\": \""
  "none\",\"isWeakPullDown\": false,\"customName\": \"MCAF_LED2\",\"isAnalogPin\": "
  "false,\"direction\": \"output\",\"isOpenDrain\": false},{\"isWeakPullUp\": false"
  ",\"pinSelected\": \"RE10\",\"interruptOnChange\": \"none\",\"isWeakPullDown\": f"
  "alse,\"customName\": \"MCAF_BUTTON1\",\"isAnalogPin\": false,\"direction\": \"in"
  "put\",\"isOpenDrain\": false},{\"isWeakPullUp\": false,\"pinSelected\": \"RE11\""
  ",\"interruptOnChange\": \"none\",\"isWeakPullDown\": false,\"customName\": \"MCA"
  "F_BUTTON2\",\"isAnalogPin\": false,\"direction\": \"input\",\"isOpenDrain\": fal"
  "se},{\"isWeakPullUp\": false,\"pinSelected\": \"RE8\",\"interruptOnChange\": \"n"
  "one\",\"isWeakPullDown\": false,\"customName\": \"MCAF_TESTPOINT1\",\"isAnalogPi"
  "n\": false,\"direction\": \"output\",\"isOpenDrain\": false}]},\"displayName\": "
  "\"MCLV-48V-300W\",\"name\": \"MCLV-48V-300W Inverter Board\",\"partNumber\": \"E"
  "V18H47A\",\"id\": \"mclv-48v-300w\",\"supportedPim\": [\"33ck256mp508_dim\",\"33"
  "ck64mc105_dim\"]},\"idc\": {\"maximum\": 2.9,\"units\": \"A\"},\"sampling_time\""
  ": {\"current\": 5e-05,\"velocity\": 0.001},\"processor\": {\"clock_frequency\": "
  "100000000.0,\"pim\": \"dsPIC33CK256MP508\",\"familyName\": \"dsPIC33CK256MP508\""
  ",\"device\": \"dsPIC33CK256MP508\"},\"vbus\": 24.0},\"config\": {\"ui\": {\"cont"
  "ent\": {\"current_measure-method\": \"triple_channel\",\"current_measure-single_"
  "channel-minimumTime\": 2.0,\"current_measure-single_channel-sampleDelay\": 0.0,"
  "\"current_measure-opamp-full_input_range\": true,\"estimator-type\": \"zsmt\",\""
  "estimator-active-pll\": true,\"estimator-active-qei\": false,\"estimator-active-"
  "atpll\": false,\"estimator-active-zsmt\": false,\"estimator-active-ideal\": fals"
  "e,\"operation-min_velocity_ratio\": 0.0494,\"operation-startup_velocity_ratio\":"
  " 0.0494,\"operation-max_velocity_ratio\": 0.1,\"operation-fullscale_base_ratio\""
  ": 1.5,\"operation-outer_loop_type\": \"voltage\",\"operation-saliency-threshold"
  "\": 1.25,\"operation-slewrate-accel\": 0.5,\"operation-slewrate-decel\": 1.0,\"o"
  "peration-dyn_current_type\": \"none\",\"operation-stopping-type\": \"minimal_imp"
  "act\",\"operation-stopping-closed_loop_parameters-speed\": 0.05,\"operation-stop"
  "ping-closed_loop_parameters-time\": 0.5,\"operation-coastdown-end_velocity\": 0."
  "05,\"operation-coastdown-time\": 1.2,\"fault_inject-get_tf-div0\": false,\"fault"
  "_inject-get_tf-missing_data\": false,\"fault_inject-get_tf-raise_value_error\": "
  "false,\"fault_inject-get_tf-raise_custom_error\": false,\"fault_inject-tf-tf_nul"
  "l\": false,\"fault_inject-tf-tf_jy\": false,\"fault_inject-tf-tf_jyex\": false,"
  "\"fault_inject-tf-div0\": false,\"fault_inject-tf-tau\": 0.0,\"flux_control-meth"
  "od\": \"none\",\"flux_control-eqn_based-ilimit-region_type\": \"quadratic\",\"fl"
  "ux_control-eqn_based-ilimit-id_limit\": 0.7,\"flux_control-eqn_based-ilimit-iq_l"
  "imit\": 0.95,\"flux_control-eqn_based-fluxweak_enable\": false,\"flux_control-eq"
  "n_based-fw-vdq_limit\": 0.95,\"flux_control-eqn_based-mtpa_enable\": false,\"dea"
  "dtimecomp-method\": \"none\",\"deadtimecomp-perphase-current_sign_band\": 0.02,"
  "\"deadtimecomp-perphase-forward_gain\": 0.0,\"deadtimecomp-perphase-feedback_gai"
  "n\": 0.0,\"fault_detect-margin_uv\": 2.0,\"fault_detect-margin_ov\": 2.0,\"fault"
  "_detect-stall_detect_enable\": false,\"startup-Istartup\": 0.75,\"startup-t_ramp"
  "up\": 25.0,\"startup-t_align\": 0.0,\"startup-min_total_accel_time\": 250.0,\"st"
  "artup-torque_scale_accel\": 0.15,\"startup-torque_scale_slow_accel\": 0.2,\"star"
  "tup-t_hold\": 0.0,\"startup-omega0\": 0.2,\"startup-theta_converge_rate\": 1.0,"
  "\"startup-method\": \"zsmt_dsat\",\"startup-damping-Imax\": 0.1,\"startup-dampin"
  "g-gainmax\": 40.0,\"startup-damping-omega_min\": 0.4,\"overmodulation-vd_limit\""
  ": 1.0,\"overmodulation-vq_limit\": 1.15,\"overmodulation-include_duty_clipping\""
  ": true,\"pll-tau\": 2.19,\"pll-omega1\": 116.5,\"pll-velocity_filter_threshold\""
  ": 1.0,\"encoder-lines\": 250.0,\"encoder-index_present\": false,\"encoder-tracki"
  "ng_loop-tau\": 1.5,\"encoder-qei_sync-method\": \"align\",\"encoder-qei_sync-ali"
  "gn-t_align\": 0.5,\"encoder-qei_sync-align-angle_shift\": 30.0,\"encoder-qei_syn"
  "c-align-angle_init\": -30.0,\"encoder-qei_sync-align_sweep-sweep_rate_pow\": 1.0"
  ",\"encoder-qei_sync-align_sweep-setup_angle\": 45.0,\"encoder-qei_sync-pullout-p"
  "ullout_slip\": 0.117,\"zsmt-excitation-kV\": 0.12,\"zsmt-excitation-kI\": 0.1,\""
  "zsmt-pll-zeta\": 1.5,\"zsmt-pll-tau\": 10.0,\"zsmt-pll-tau_lpf\": 0.0,\"zsmt-pll"
  "-execution_divider\": 2.0,\"zsmt-startup-align_delay\": 1.0,\"zsmt-startup-pll_l"
  "ock_time\": 1.0,\"zsmt-startup-speed_limit\": 0.015,\"zsmt-startup-current_limit"
  "\": 0.3,\"zsmt-startup-probe_duration\": 10.0,\"zsmt-startup-probe_slew_time\": "
  "1.5,\"zsmt-startup-probe_blanking_time\": 4.0,\"zsmt-hybrid-type\": \"minotaur\""
  ",\"zsmt-minotaur-voltage_limit-vd\": 0.45,\"zsmt-minotaur-voltage_limit-vq\": 0."
  "78,\"zsmt-minotaur-converge-angle\": 10.0,\"zsmt-minotaur-converge-duration\": 2"
  ".0,\"zsmt-minotaur-velocity_threshold-slow\": 0.15,\"zsmt-minotaur-velocity_thre"
  "shold-transition\": 0.2,\"zsmt-minotaur-velocity_threshold-fast\": 0.25,\"zsmt-a"
  "ngle_correction-current_gain\": 0.0,\"dyn_current1-peak_factor\": 1.0,\"dyn_curr"
  "ent1-horizon_factor\": 1.05,\"dyn_current1-tau\": 5.0,\"dyn_current1-nsamples\":"
  " 128.0,\"voltage_outerloop-tau_lpf\": 2.0,\"voltage_outerloop-Kp\": 0.1,\"voltag"
  "e_outerloop-tau\": 5.0,\"mcapi-isSquaredTau\": 1.0,\"mcapi-iqTau\": 1.0,\"mcapi-"
  "adcIsrUserFunctions_enable\": false,\"board_service-uiServiceTiming\": 1.0,\"boa"
  "rd_service-uiButtonDebounceTime\": 7.0,\"board_service-uiButtonLongPressTime\": "
  "2.5,\"test_harness-perturbation_asymmetric\": false,\"adc-vtempbridge\": false,"
  "\"adc-temp_bridge_params-threshold\": 50.0,\"adc-temp_bridge_params-tau_lpf\": 1"
  "0.0,\"adc-temp_bridge_params-slewrate\": 4.0,\"adc-vabsref\": false,\"adc-vphase"
  "a\": false,\"adc-vphaseb\": false,\"adc-vphasec\": false},\"version\": {\"schema"
  "\": 4.0,\"motorBench\": \"2.45.0\",\"MCAF\": \"R7\"},\"status\": {\"valid\": tru"
  "e}}}}";