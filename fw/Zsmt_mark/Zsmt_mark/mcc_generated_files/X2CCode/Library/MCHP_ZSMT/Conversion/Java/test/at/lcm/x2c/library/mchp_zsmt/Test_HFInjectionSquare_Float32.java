/*
 * Copyright (c) {YEAR}, {ORGANIZATION_NAME}, {ORGANIZATION_WEB}
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the "{ORGANIZATION_NAME}" nor
 *     the names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "{ORGANIZATION_NAME}" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2108 $
 * $LastChangedDate:: 2020-12-07 19:09:57 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                                                       */
/* Description: */
/* USERCODE-END:Description                                                                                                                         */

package at.lcm.x2c.library.mchp_zsmt;

import java.util.HashMap;
import java.util.Map;

import at.lcm.bu21.general.dtypes.TData;
import at.lcm.bu21.general.dtypes.TNumeric;
import at.lcm.bu21.general.dtypes.TString;
import at.lcm.communication.hardware.Serial;
import at.lcm.x2c.blocktest.ConversionOnTargetTest;
import at.lcm.x2c.blocktest.ConversionTest;
import at.lcm.x2c.blocktest.InportTest;
import at.lcm.x2c.blocktest.ParameterTest;
import at.lcm.x2c.blocktest.TestSuite;
import at.lcm.x2c.communication.protocol.Protocol;
import at.lcm.x2c.communication.protocol.ProtocolFactory;

public class Test_HFInjectionSquare_Float32 {

    public Test_HFInjectionSquare_Float32(Protocol protocol) throws Exception {
        /* Inport test variables start here */
        final int IT_LENGTH = 100;
        final boolean IT_DOINIT = false;
        final double IT_SAMPLETIME = 1.000000e-04;
        /* Inports: */
        final double[] it_in_I_D = { 0, 4.1666748913099427298, -4.1666995649150759817, 4.1667406865079961165,
                -4.166768899321461106, 4.1666772911420659753, -4.1667493485571105438, 4.1668378475233085467,
                -4.1662492361028524712, 4.1657852925651042142, -4.1658834689869514989, 4.1659980811059122985,
                -4.1642993010774027596, 4.1636877900617381698, -4.1638094122178461731, 4.1639474634187783053,
                -4.1612355240849101534, 4.1605521776223399755, -4.1606984512343370142, 4.160861145469290534,
                -4.1573294409795034099, 4.1565968787839491227, -4.1567698581015948278, 4.156959247264843782,
                -4.1527486707096370466, 4.1519674300191722338, -4.1521689886425798832, 4.1523869436695015622,
                -4.1475791284652814284, 4.1467433108917752804, -4.1469749199855483468, 4.1472229092154782037,
                -4.1418586943818427315, 4.1409610077780634185, -4.1412237483306508778, 4.1415028498539872004,
                -4.1355988115052815246, 4.1346322506715056377, -4.1349268842329900409, 4.1352378566818774885,
                -4.1287970857474229902, 4.1277554454660050354, -4.1280824876636659226, 4.1284258437592162849,
                -4.1214443897169639186, 4.1203223789816405542, -4.1206821611579282916, 4.1210582293663007292,
                -4.1135288341412188373, 4.1123220494928505175, -4.1127147667239052353, 4.1131237392841546452,
                -4.1050379650682495836, 4.1037428138636089514, -4.1041685612245153436, 4.1046105304175624084,
                -4.0959599456970572362, 4.0945735532463798378, -4.0950323527971637105, 4.0955073379320268145,
                -4.0862841503648379415, 4.0848042649539442195, -4.0852960856576387982, 4.085804052987680457,
                -4.0760014170974976366, 4.0744263193736180995, -4.0749510917164277757, 4.0754919690566087098,
                -4.0651041040987978548, 4.0634325240079833819, -4.0639901506790998553, 4.0645638380824307134,
                -4.0535860374048056087, 4.0518170801409132409, -4.0524074437941486337, 4.0530138213098778621,
                -4.0414424023958890331, 4.0395754837790542879, -4.0401984526393448505, 4.0408373859161983432,
                -4.0286696108296968788, 4.0267044018743094469, -4.0273598337564298077, 4.0280311780583302195,
                -4.0152651620481085715, 4.0132015420803988093, -4.013889287240678172, 4.0145928902958409878,
                -4.0012275089105848735, 3.9990655263802210584, -3.9997854295130039759, 4.0005211335081245494,
                -3.9865559339788712023, 3.9842957740230646735, -3.9850476756324977323, 3.9858153185826274978,
                -3.971250438399244409, 3.9688923962186177796, -3.9696761335362160672, 3.9704755502007542667 };
        final double[] it_in_I_Q = { 0, -0.0026179766523162285342, 0.00523584995139691773, -0.0078535165480867370758,
                -0.01882212118558087427, 0.022061234325801280798, -0.019444236594475021451, 0.016827743267555990425,
                -0.077339829694661271775, 0.087336402191898199199, -0.084720254109884610139, 0.082104774524986851025,
                -0.14683965030040649347, 0.15767843294049121994, -0.15506326995360616983, 0.15244892275731583564,
                -0.21520813266720348333, 0.22565435227954858122, -0.22304045223798932285, 0.22042752285074163066,
                -0.27984206025211588731, 0.28962381086759741988, -0.28701154220750579871, 0.28440041196531684609,
                -0.340742625296181878, 0.34991468350728316405, -0.34730446445169416148, 0.34469556334144313414,
                -0.39859149366514512458, 0.40727884262605679178, -0.4046711182110712679, 0.40206490050361309851,
                -0.45412082726796199061, 0.4624443841013625156, -0.45983961217298652269, 0.45723654249729567267,
                -0.50794574024084737651, 0.51600385153341254973, -0.5134024941067452108, 0.51080303925373038432,
                -0.56054143772239684029, 0.56840905233569727351, -0.56581157032463746948, 0.56321619443885950762,
                -0.61226140468837408903, 0.61999388502418961711, -0.61740073516688176447, 0.61480989705934185885,
                -0.66336298766572954211, 0.67100046050040473844, -0.66841209372321452875, 0.66582624553706870607,
                -0.71403051672441986142, 0.72160162112922754396, -0.71901848184116912144, 0.71643806857403025123,
                -0.76439386263419639711, 0.7719187049838274195, -0.76934123095504836076, 0.76676669050702905839,
                -0.81454266489696924847, 0.82203506678978688349, -0.81946368937831115531, 0.81689545290391085697,
                -0.86453702520242481366, 0.87200620619319335614, -0.86944135076158501896, 0.86687984317820565572,
                -0.91441546914221460973, 0.92186729651521415185, -0.91930938293331010414, 0.9167550234910839535,
                -0.96420084510151227164, 0.97163875805345678582, -0.96908820122135730379, 0.96654140407489130826,
                -1.0139046816819008434, 1.0213303727458276082, -1.0187875830974417735, 1.016248757844582018,
                -1.0635303989634223853, 1.0709443151982007691, -1.0684096991632299201, 1.0658792513322847828,
                -1.1130756697171912961, 1.120477380396961653, -1.1179513408107037975, 1.1154296722881587023,
                -1.1625341511412208284, 1.1699226167142191546, -1.1674055531718667833, 1.1648930625692188734,
                -1.2118967509867819565, 1.2192705191106782969, -1.2167628282671807405, 1.2142599112294132357,
                -1.2611525496493993792, 1.2685098974327890797, -1.2660119732518271274, 1.2635190227121473328 };
        final double[] it_in_n0 = { 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
                300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
                300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
                300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
                300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300 };
        final double[] it_in_phi0 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0 };
        final double[] it_in_Enable = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1 };
        /* Mask parameters: */
        final double[] it_mp_U_inj = { 2 };
        final double[] it_mp_Jp = { 1 };
        final double[] it_mp_I_inj = { 4.166667e-01 };
        final double[] it_mp_fo = { 40 };
        final double[] it_mp_p = { 1 };
        final double[] it_mp_n_max = { 1000 };
        final double[] it_mp_I_max = { 5 };
        final double[] it_mp_U_max = { 10 };
        final double[] it_mp_ts_fact = { 1 };
        final String it_mp_estimation = "less noise";
        final String it_mp_method = "tustin";
        /* Outports: */
        final double[] it_out_Ud = { 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2,
                2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2,
                2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2,
                2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2 };
        final double[] it_out_I_eps = { 0, 0, 0, 0, 0.0039268745449032721462, 0.0039268745449032721462,
                0.0039268745449032721462, 0.0039268745449032721462, 0.00016404275961001604095,
                0.00016404275961001604095, 0.00016404275961001604095, 0.00016404275961001604095,
                -0.018679487058521578036, -0.018679487058521578036, -0.018679487058521578036, -0.018679487058521578036,
                -0.02474895900896783435, -0.02474895900896783435, -0.02474895900896783435, -0.02474895900896783435,
                -0.0079228420233767443692, -0.0079228420233767443692, -0.0079228420233767443692,
                -0.0079228420233767443692, 0.011013051804952333351, 0.011013051804952333351, 0.011013051804952333351,
                0.011013051804952333351, 0.010502650651801767601, 0.010502650651801767601, 0.010502650651801767601,
                0.010502650651801767601, -0.0031271931566636407274, -0.0031271931566636407274,
                -0.0031271931566636407274, -0.0031271931566636407274, -0.0079195073111956795775,
                -0.0079195073111956795775, -0.0079195073111956795775, -0.0079195073111956795775,
                0.0024601294183072899835, 0.0024601294183072899835, 0.0024601294183072899835, 0.0024601294183072899835,
                0.01270330943278295821, 0.01270330943278295821, 0.01270330943278295821, 0.01270330943278295821,
                0.0094817760711604220925, 0.0094817760711604220925, 0.0094817760711604220925, 0.0094817760711604220925,
                -0.00096631235579160146276, -0.00096631235579160146276, -0.00096631235579160146276,
                -0.00096631235579160146276, -0.003842322522974728205, -0.003842322522974728205,
                -0.003842322522974728205, -0.003842322522974728205, 0.0033475817984291167395, 0.0033475817984291167395,
                0.0033475817984291167395, 0.0033475817984291167395, 0.0092668878355875311525, 0.0092668878355875311525,
                0.0092668878355875311525, 0.0092668878355875311525, 0.0058476645780861369328, 0.0058476645780861369328,
                0.0058476645780861369328, 0.0058476645780861369328, -0.0014066760382476367619,
                -0.0014066760382476367619, -0.0014066760382476367619, -0.0014066760382476367619,
                -0.002666623482416544122, -0.002666623482416544122, -0.002666623482416544122, -0.002666623482416544122,
                0.0025265491378489712826, 0.0025265491378489712826, 0.0025265491378489712826, 0.0025265491378489712826,
                0.0059898576047770907271, 0.0059898576047770907271, 0.0059898576047770907271, 0.0059898576047770907271,
                0.0030309863324006480756, 0.0030309863324006480756, 0.0030309863324006480756, 0.0030309863324006480756,
                -0.0017967269692840404094, -0.0017967269692840404094, -0.0017967269692840404094,
                -0.0017967269692840404094, -0.0020734130591985866499, -0.0020734130591985866499,
                -0.0020734130591985866499, -0.0020734130591985866499 };
        final double[] it_out_n = { 300, 300, 300, 300, 264.33781224925309061, 264.33781224925309061,
                264.33781224925309061, 264.33781224925309061, 294.98510168241307383, 294.98510168241307383,
                294.98510168241307383, 294.98510168241307383, 465.85238649706923297, 465.85238649706923297,
                465.85238649706923297, 465.85238649706923297, 537.62211750495998785, 537.62211750495998785,
                537.62211750495998785, 537.62211750495998785, 407.45617196863759091, 407.45617196863759091,
                407.45617196863759091, 407.45617196863759091, 243.74579130693368256, 243.74579130693368256,
                243.74579130693368256, 243.74579130693368256, 239.87027373118255014, 239.87027373118255014,
                239.87027373118255014, 239.87027373118255014, 355.2775297644695911, 355.2775297644695911,
                355.2775297644695911, 355.2775297644695911, 402.35587238616250261, 402.35587238616250261,
                402.35587238616250261, 402.35587238616250261, 316.04212914533025014, 316.04212914533025014,
                316.04212914533025014, 316.04212914533025014, 221.88039795193520831, 221.88039795193520831,
                221.88039795193520831, 221.88039795193520831, 240.73256035713950496, 240.73256035713950496,
                240.73256035713950496, 240.73256035713950496, 327.73539256857299051, 327.73539256857299051,
                327.73539256857299051, 327.73539256857299051, 355.07506826472621242, 355.07506826472621242,
                355.07506826472621242, 355.07506826472621242, 293.61033630200165589, 293.61033630200165589,
                293.61033630200165589, 293.61033630200165589, 237.34213397737474338, 237.34213397737474338,
                237.34213397737474338, 237.34213397737474338, 260.47127966766953477, 260.47127966766953477,
                260.47127966766953477, 260.47127966766953477, 321.2290025552139241, 321.2290025552139241,
                321.2290025552139241, 321.2290025552139241, 333.89019513387842153, 333.89019513387842153,
                333.89019513387842153, 333.89019513387842153, 289.118914469223796, 289.118914469223796,
                289.118914469223796, 289.118914469223796, 255.4732525575866191, 255.4732525575866191,
                255.4732525575866191, 255.4732525575866191, 276.96853701895338418, 276.96853701895338418,
                276.96853701895338418, 276.96853701895338418, 317.91765885162629957, 317.91765885162629957,
                317.91765885162629957, 317.91765885162629957, 321.78189483446328722, 321.78189483446328722,
                321.78189483446328722, 321.78189483446328722 };
        final double[] it_out_phi = { 0, 0, 0, 0, 0.0055362781935216764939, 0.0055362781935216764939,
                0.0055362781935216764939, 0.0055362781935216764939, 0.017250709909469398584, 0.017250709909469398584,
                0.017250709909469398584, 0.017250709909469398584, 0.033185652999071883762, 0.033185652999071883762,
                0.033185652999071883762, 0.033185652999071883762, 0.054202373864654797286, 0.054202373864654797286,
                0.054202373864654797286, 0.054202373864654797286, 0.073996047273171217107, 0.073996047273171217107,
                0.073996047273171217107, 0.073996047273171217107, 0.087634789298703108518, 0.087634789298703108518,
                0.087634789298703108518, 0.087634789298703108518, 0.097763620479248108941, 0.097763620479248108941,
                0.097763620479248108941, 0.097763620479248108941, 0.11022836692766173339, 0.11022836692766173339,
                0.11022836692766173339, 0.11022836692766173339, 0.1260962037963995197, 0.1260962037963995197,
                0.1260962037963995197, 0.1260962037963995197, 0.14114229635616570846, 0.14114229635616570846,
                0.14114229635616570846, 0.14114229635616570846, 0.15240851941836053296, 0.15240851941836053296,
                0.15240851941836053296, 0.15240851941836053296, 0.1620974625602220609, 0.1620974625602220609,
                0.1620974625602220609, 0.1620974625602220609, 0.17400342752497305332, 0.17400342752497305332,
                0.17400342752497305332, 0.17400342752497305332, 0.18830417637529409114, 0.18830417637529409114,
                0.18830417637529409114, 0.18830417637529409114, 0.20189021171847912339, 0.20189021171847912339,
                0.20189021171847912339, 0.20189021171847912339, 0.21301045425204606643, 0.21301045425204606643,
                0.21301045425204606643, 0.21301045425204606643, 0.2234366340064842249, 0.2234366340064842249,
                0.2234366340064842249, 0.2234366340064842249, 0.23561973622796769656, 0.23561973622796769656,
                0.23561973622796769656, 0.23561973622796769656, 0.2493405206192056689, 0.2493405206192056689,
                0.2493405206192056689, 0.2493405206192056689, 0.26238879289819649898, 0.26238879289819649898,
                0.26238879289819649898, 0.26238879289819649898, 0.27379470457242299775, 0.27379470457242299775,
                0.27379470457242299775, 0.27379470457242299775, 0.28494613933640872139, 0.28494613933640872139,
                0.28494613933640872139, 0.28494613933640872139, 0.29740540668753528974, 0.29740540668753528974,
                0.29740540668753528974, 0.29740540668753528974, 0.31080324280996785014, 0.31080324280996785014,
                0.31080324280996785014, 0.31080324280996785014 };
        /* Outport Tolerances: */
        final double it_tol_Ud = 1 * Math.pow(2, -31);
        final double it_tol_I_eps = 1 * Math.pow(2, -31);
        final double it_tol_n = 1 * Math.pow(2, -31);
        final double it_tol_phi = 0 * Math.pow(2, -31);
        /* Inport test variables end here */

        /* Parameter test variables start here */
        final int PT_LENGTH = 3;
        final boolean PT_DOINIT = true;
        final double PT_SAMPLETIME = 0.0;
        /* Inport: I_D */
        final double pt_in_I_D = 0;
        /* Inport: I_Q */
        final double pt_in_I_Q = 0;
        /* Inport: n0 */
        final double pt_in_n0 = 0;
        /* Inport: phi0 */
        final double pt_in_phi0 = 0;
        /* Inport: Enable */
        final double pt_in_Enable = 0;
        /* Mask parameter: U_inj */
        final double[][] pt_mp_U_inj = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: Jp */
        final double[][] pt_mp_Jp = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: I_inj */
        final double[][] pt_mp_I_inj = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: fo */
        final double[][] pt_mp_fo = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: p */
        final double[][] pt_mp_p = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: n_max */
        final double[][] pt_mp_n_max = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: I_max */
        final double[][] pt_mp_I_max = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: U_max */
        final double[][] pt_mp_U_max = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: ts_fact */
        final double[][] pt_mp_ts_fact = { { 0 }, { 0 }, { 0 } };
        /* Mask parameter: estimation */
        final String[] pt_mp_estimation = { "Test", "Test", "Test" };
        /* Mask parameter: method */
        final String[] pt_mp_method = { "Test", "Test", "Test" };
        /* Outport: Ud */
        final double[] pt_out_Ud = { 0, 0, 0 };
        /* Outport: I_eps */
        final double[] pt_out_I_eps = { 0, 0, 0 };
        /* Outport: n */
        final double[] pt_out_n = { 0, 0, 0 };
        /* Outport: phi */
        final double[] pt_out_phi = { 0, 0, 0 };
        /* Outport tolerances: Ud */
        final double pt_tol_Ud = Math.pow(2, -31);
        /* Outport tolerances: I_eps */
        final double pt_tol_I_eps = Math.pow(2, -31);
        /* Outport tolerances: n */
        final double pt_tol_n = Math.pow(2, -31);
        /* Outport tolerances: phi */
        final double pt_tol_phi = Math.pow(2, -31);
        /* Parameter test variables end here */

        /* Conversion test variables start here */
        final int CT_LENGTH = 3;
        final double CT_SAMPLETIME = 1.000000e-04;
        /* Mask parameter: */
        final double[][] ct_mp_U_inj = { { 2 }, { 3 }, { 4 } };
        final double[][] ct_mp_Jp = { { 0.10000000000000000555 }, { 1 }, { 1.1100000000000000977 } };
        final double[][] ct_mp_I_inj = { { 0.2999999999999999889 }, { 0.4000000000000000222 }, { 0.5 } };
        final double[][] ct_mp_fo = { { 20 }, { 30 }, { 40 } };
        final double[][] ct_mp_p = { { 1 }, { 2 }, { 3 } };
        final double[][] ct_mp_n_max = { { 1000 }, { 1000 }, { 1000 } };
        final double[][] ct_mp_I_max = { { 10 }, { 10 }, { 10 } };
        final double[][] ct_mp_U_max = { { 5 }, { 5 }, { 5 } };
        final double[][] ct_mp_ts_fact = { { 1 }, { 1 }, { 1 } };
        final String[] ct_mp_estimation = { "less noise", "less noise", "high dynamic range" };
        final String[] ct_mp_method = { "tustin", "tustin", "zoh" };
        /* Implementation parameter: */
        final double[][] ct_cp_uInjAmp = { { 2 }, { 3 }, { 4 } };
        final double[][] ct_cp_vGain = { { 750.00000000000011369 }, { 421.87500000000005684 }, { 300 } };
        final double[][] ct_cp_b0_torque = { { 157.9136704174297563 }, { 1998.5948912205947181 },
                { 2804.5467866135518307 } };
        final double[][] ct_cp_b1_torque = { { 9503.734795978096372 }, { 80520.861489601942594 },
                { 83692.028291632101173 } };
        final double[][] ct_cp_b0_speed = { { 0.0040000000000000000833 }, { 0.00040000000000000001917 },
                { 0.0003603603603603603117 } };
        final double[][] ct_cp_b1_speed = { { 0.0020000000000000000416 }, { 0.00020000000000000000958 }, { 0 } };
        final double[][] ct_cp_b0_angle = { { 4.188790204786390877e-05 }, { 8.377580409572781754e-05 },
                { 0.00012566370614359173986 } };
        final double[][] ct_cp_b1_angle = { { 2.0943951023931954385e-05 }, { 4.188790204786390877e-05 }, { 0 } };
        final double[][] ct_cp_rawSpeed = { { 0 }, { 0 }, { 1 } };
        /* Implementation Parameter tolerances: uInjAmp */
        final double ct_tol_uInjAmp = 0.0;
        /* Implementation Parameter tolerances: vGain */
        final double ct_tol_vGain = 0.0;
        /* Implementation Parameter tolerances: b0_torque */
        final double ct_tol_b0_torque = 0.0;
        /* Implementation Parameter tolerances: b1_torque */
        final double ct_tol_b1_torque = 0.0;
        /* Implementation Parameter tolerances: b0_speed */
        final double ct_tol_b0_speed = 0.0;
        /* Implementation Parameter tolerances: b1_speed */
        final double ct_tol_b1_speed = 0.0;
        /* Implementation Parameter tolerances: b0_angle */
        final double ct_tol_b0_angle = 0.0;
        /* Implementation Parameter tolerances: b1_angle */
        final double ct_tol_b1_angle = 0.0;
        /* Implementation Parameter tolerances: rawSpeed */
        final double ct_tol_rawSpeed = 0.0;
        /* Conversion test variables end here */

        /* Conversion-on-Target test variables start here */
        /* ! Uses test vectors of Conversion test ! */
        /* Implementation Parameter tolerances: uInjAmp */
        final double cott_tol_uInjAmp = 0.0;
        /* Implementation Parameter tolerances: vGain */
        final double cott_tol_vGain = 0.0001;
        /* Implementation Parameter tolerances: b0_torque */
        final double cott_tol_b0_torque = 0.001;
        /* Implementation Parameter tolerances: b1_torque */
        final double cott_tol_b1_torque = 0.01;
        /* Implementation Parameter tolerances: b0_speed */
        final double cott_tol_b0_speed = 0.000000001;
        /* Implementation Parameter tolerances: b1_speed */
        final double cott_tol_b1_speed = 0.000000001;
        /* Implementation Parameter tolerances: b0_angle */
        final double cott_tol_b0_angle = 0.00000000001;
        /* Implementation Parameter tolerances: b1_angle */
        final double cott_tol_b1_angle = 0.000000000001;
        /* Implementation Parameter tolerances: rawSpeed */
        final double cott_tol_rawSpeed = 0.0;
        /* Conversion-on-Target test variables end here */

        try {
            TestSuite suite = new TestSuite(protocol, "mchp_zsmt", "HFInjectionSquare", "Float32");

            /* INPORT TEST */
            InportTest it = new InportTest("mchp_zsmt", "HFInjectionSquare", "Float32", protocol, IT_DOINIT);
            Map<String, TData> it_mp = new HashMap<String, TData>();
            it_mp.put("U_inj", new TNumeric(it_mp_U_inj));
            it_mp.put("Jp", new TNumeric(it_mp_Jp));
            it_mp.put("I_inj", new TNumeric(it_mp_I_inj));
            it_mp.put("fo", new TNumeric(it_mp_fo));
            it_mp.put("p", new TNumeric(it_mp_p));
            it_mp.put("n_max", new TNumeric(it_mp_n_max));
            it_mp.put("I_max", new TNumeric(it_mp_I_max));
            it_mp.put("U_max", new TNumeric(it_mp_U_max));
            it_mp.put("ts_fact", new TNumeric(it_mp_ts_fact));
            it_mp.put("estimation", new TString(it_mp_estimation));
            it_mp.put("method", new TString(it_mp_method));
            it.setMaskParameters(it_mp);
            Map<String,  Double> it_tol = new HashMap<String, Double>();
            it_tol.put("Ud", it_tol_Ud);
            it_tol.put("I_eps", it_tol_I_eps);
            it_tol.put("n", it_tol_n);
            it_tol.put("phi", it_tol_phi);
            it.setTolerances(it_tol);
            for (int i = 0; i < IT_LENGTH; i++) {
                Map<String,  TNumeric> it_in = new HashMap<String, TNumeric>();
                Map<String,  TNumeric> it_out = new HashMap<String, TNumeric>();
                it_in.put("I_D", new TNumeric(it_in_I_D[i]));
                it_in.put("I_Q", new TNumeric(it_in_I_Q[i]));
                it_in.put("n0", new TNumeric(it_in_n0[i]));
                it_in.put("phi0", new TNumeric(it_in_phi0[i]));
                it_in.put("Enable", new TNumeric(it_in_Enable[i]));
                it_out.put("Ud", new TNumeric(it_out_Ud[i]));
                it_out.put("I_eps", new TNumeric(it_out_I_eps[i]));
                it_out.put("n", new TNumeric(it_out_n[i]));
                it_out.put("phi", new TNumeric(it_out_phi[i]));
                it.addConfig(it_in, it_out);
            }
            it.setSampleTime(IT_SAMPLETIME);
            // suite.add(it);

            /* PARAMETER TEST */
            ParameterTest pt = new ParameterTest("mchp_zsmt", "HFInjectionSquare", "Float32", protocol, PT_DOINIT);
            Map<String, TNumeric> pt_in = new HashMap<String, TNumeric>();
            pt_in.put("I_D", new TNumeric(pt_in_I_D));
            pt_in.put("I_Q", new TNumeric(pt_in_I_Q));
            pt_in.put("n0", new TNumeric(pt_in_n0));
            pt_in.put("phi0", new TNumeric(pt_in_phi0));
            pt_in.put("Enable", new TNumeric(pt_in_Enable));
            pt.setInports(pt_in);
            Map<String,  Double> pt_tol = new HashMap<String, Double>();
            pt_tol.put("Ud", pt_tol_Ud);
            pt_tol.put("I_eps", pt_tol_I_eps);
            pt_tol.put("n", pt_tol_n);
            pt_tol.put("phi", pt_tol_phi);
            pt.setTolerances(pt_tol);
            for (int i = 0; i < PT_LENGTH; i++) {
                Map<String,  TData> pt_mp = new HashMap<String, TData>();
                Map<String,  TNumeric> pt_out = new HashMap<String, TNumeric>();
                pt_mp.put("U_inj", new TNumeric(pt_mp_U_inj[i]));
                pt_mp.put("Jp", new TNumeric(pt_mp_Jp[i]));
                pt_mp.put("I_inj", new TNumeric(pt_mp_I_inj[i]));
                pt_mp.put("fo", new TNumeric(pt_mp_fo[i]));
                pt_mp.put("p", new TNumeric(pt_mp_p[i]));
                pt_mp.put("n_max", new TNumeric(pt_mp_n_max[i]));
                pt_mp.put("I_max", new TNumeric(pt_mp_I_max[i]));
                pt_mp.put("U_max", new TNumeric(pt_mp_U_max[i]));
                pt_mp.put("ts_fact", new TNumeric(pt_mp_ts_fact[i]));
                pt_mp.put("estimation", new TString(pt_mp_estimation[i]));
                pt_mp.put("method", new TString(pt_mp_method[i]));
                pt_out.put("Ud", new TNumeric(pt_out_Ud[i]));
                pt_out.put("I_eps", new TNumeric(pt_out_I_eps[i]));
                pt_out.put("n", new TNumeric(pt_out_n[i]));
                pt_out.put("phi", new TNumeric(pt_out_phi[i]));
                pt.addConfig(pt_mp, pt_out);
            }
            pt.setSampleTime(PT_SAMPLETIME);
            // suite.add(pt);

            /* CONVERSION TEST */
            ConversionTest ct = new ConversionTest("mchp_zsmt", "HFInjectionSquare", "Float32");
            Map<String,  Double> ct_tol = new HashMap<String, Double>();
            ct_tol.put("uInjAmp", ct_tol_uInjAmp);
            ct_tol.put("vGain", ct_tol_vGain);
            ct_tol.put("b0_torque", ct_tol_b0_torque);
            ct_tol.put("b1_torque", ct_tol_b1_torque);
            ct_tol.put("b0_speed", ct_tol_b0_speed);
            ct_tol.put("b1_speed", ct_tol_b1_speed);
            ct_tol.put("b0_angle", ct_tol_b0_angle);
            ct_tol.put("b1_angle", ct_tol_b1_angle);
            ct_tol.put("rawSpeed", ct_tol_rawSpeed);
            ct.setTolerances(ct_tol);
            for (int i = 0; i < CT_LENGTH; i++) {
                Map<String, TData> ct_mp = new HashMap<String, TData>();
                Map<String, TNumeric> ct_cp = new HashMap<String, TNumeric>();
                ct_mp.put("U_inj", new TNumeric(ct_mp_U_inj[i]));
                ct_mp.put("Jp", new TNumeric(ct_mp_Jp[i]));
                ct_mp.put("I_inj", new TNumeric(ct_mp_I_inj[i]));
                ct_mp.put("fo", new TNumeric(ct_mp_fo[i]));
                ct_mp.put("p", new TNumeric(ct_mp_p[i]));
                ct_mp.put("n_max", new TNumeric(ct_mp_n_max[i]));
                ct_mp.put("I_max", new TNumeric(ct_mp_I_max[i]));
                ct_mp.put("U_max", new TNumeric(ct_mp_U_max[i]));
                ct_mp.put("ts_fact", new TNumeric(ct_mp_ts_fact[i]));
                ct_mp.put("estimation", new TString(ct_mp_estimation[i]));
                ct_mp.put("method", new TString(ct_mp_method[i]));
                ct_cp.put("uInjAmp", new TNumeric(ct_cp_uInjAmp[i]));
                ct_cp.put("vGain", new TNumeric(ct_cp_vGain[i]));
                ct_cp.put("b0_torque", new TNumeric(ct_cp_b0_torque[i]));
                ct_cp.put("b1_torque", new TNumeric(ct_cp_b1_torque[i]));
                ct_cp.put("b0_speed", new TNumeric(ct_cp_b0_speed[i]));
                ct_cp.put("b1_speed", new TNumeric(ct_cp_b1_speed[i]));
                ct_cp.put("b0_angle", new TNumeric(ct_cp_b0_angle[i]));
                ct_cp.put("b1_angle", new TNumeric(ct_cp_b1_angle[i]));
                ct_cp.put("rawSpeed", new TNumeric(ct_cp_rawSpeed[i]));
                ct.addConfig(ct_mp, ct_cp);
            }
            ct.setSampleTime(CT_SAMPLETIME);
            suite.add(ct);

            /* CONVERSION-ON-TARGET TEST */
            ConversionOnTargetTest cott = new ConversionOnTargetTest("mchp_zsmt", "HFInjectionSquare", "Float32", protocol);
            Map<String,  Double> cott_tol = new HashMap<String, Double>();
            cott_tol.put("uInjAmp", cott_tol_uInjAmp);
            cott_tol.put("vGain", cott_tol_vGain);
            cott_tol.put("b0_torque", cott_tol_b0_torque);
            cott_tol.put("b1_torque", cott_tol_b1_torque);
            cott_tol.put("b0_speed", cott_tol_b0_speed);
            cott_tol.put("b1_speed", cott_tol_b1_speed);
            cott_tol.put("b0_angle", cott_tol_b0_angle);
            cott_tol.put("b1_angle", cott_tol_b1_angle);
            cott_tol.put("rawSpeed", cott_tol_rawSpeed);
            cott.setTolerances(cott_tol);
            for (int i = 0; i < CT_LENGTH; i++) {
                Map<String, TData> cott_mp = new HashMap<String, TData>();
                Map<String, TNumeric> cott_cp = new HashMap<String, TNumeric>();
                /* Uses test data of Conversion test */
                cott_mp.put("U_inj", new TNumeric(ct_mp_U_inj[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("Jp", new TNumeric(ct_mp_Jp[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("I_inj", new TNumeric(ct_mp_I_inj[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("fo", new TNumeric(ct_mp_fo[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("p", new TNumeric(ct_mp_p[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("n_max", new TNumeric(ct_mp_n_max[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("I_max", new TNumeric(ct_mp_I_max[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("U_max", new TNumeric(ct_mp_U_max[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("ts_fact", new TNumeric(ct_mp_ts_fact[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("estimation", new TString(ct_mp_estimation[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("method", new TString(ct_mp_method[i]));
                /* Use test data of Conversion test */
                cott_cp.put("uInjAmp", new TNumeric(ct_cp_uInjAmp[i]));
                /* Use test data of Conversion test */
                cott_cp.put("vGain", new TNumeric(ct_cp_vGain[i]));
                /* Use test data of Conversion test */
                cott_cp.put("b0_torque", new TNumeric(ct_cp_b0_torque[i]));
                /* Use test data of Conversion test */
                cott_cp.put("b1_torque", new TNumeric(ct_cp_b1_torque[i]));
                /* Use test data of Conversion test */
                cott_cp.put("b0_speed", new TNumeric(ct_cp_b0_speed[i]));
                /* Use test data of Conversion test */
                cott_cp.put("b1_speed", new TNumeric(ct_cp_b1_speed[i]));
                /* Use test data of Conversion test */
                cott_cp.put("b0_angle", new TNumeric(ct_cp_b0_angle[i]));
                /* Use test data of Conversion test */
                cott_cp.put("b1_angle", new TNumeric(ct_cp_b1_angle[i]));
                /* Use test data of Conversion test */
                cott_cp.put("rawSpeed", new TNumeric(ct_cp_rawSpeed[i]));
                cott.addConfig(cott_mp, cott_cp);
            }
            /* Use sample time of Conversion test */
            cott.setSampleTime(CT_SAMPLETIME);
            suite.add(cott);

            suite.test();
            suite.report();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws Exception {
        final String port;
        if (args.length == 0) {
            port = "COM17";
        } else {
            port = args[0];
        }
        Protocol protocol = ProtocolFactory.getLNet(new Serial(115200, Serial.Databits.BITS_8, Serial.Parity.NONE, Serial.Stopbits.STOPBITS_1, port), 1);
        new Test_HFInjectionSquare_Float32(protocol);
    }
}
