/**
 * $LastChangedRevision: 2108 $
 * $LastChangedDate:: 2020-12-07 19:09:57 +0100#$
 *
 * This file is part of X2C. http://x2c.lcm.at/
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
package at.lcm.x2c.library.mchp_zsmt;

import at.lcm.communication.hardware.Serial;
import at.lcm.x2c.communication.protocol.Protocol;
import at.lcm.x2c.communication.protocol.ProtocolFactory;

public class runTest_Float32 {

    /**
     * @param args
     */
    public static void main(String[] args) throws Exception {
        final String port;
        if (args.length == 0) {
            port = "COM1";
        } else {
            port = args[0];
        }
        final Protocol protocol = ProtocolFactory.getLNet(new Serial(115200, Serial.Databits.BITS_8,
                Serial.Parity.NONE, Serial.Stopbits.STOPBITS_1, port), 1);

        new Test_EstimatorSwitch_Float32(protocol);
        new Test_HFInjectionSquare_Float32(protocol);
        new Test_InitPosDetect_Float32(protocol);

    }

}