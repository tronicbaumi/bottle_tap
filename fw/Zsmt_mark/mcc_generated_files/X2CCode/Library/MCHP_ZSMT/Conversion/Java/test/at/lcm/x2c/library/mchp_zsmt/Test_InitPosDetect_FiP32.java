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
import at.lcm.communication.hardware.Serial;
import at.lcm.x2c.blocktest.ConversionOnTargetTest;
import at.lcm.x2c.blocktest.ConversionTest;
import at.lcm.x2c.blocktest.InportTest;
import at.lcm.x2c.blocktest.TestSuite;
import at.lcm.x2c.communication.protocol.Protocol;
import at.lcm.x2c.communication.protocol.ProtocolFactory;

public class Test_InitPosDetect_FiP32 {

    public Test_InitPosDetect_FiP32(Protocol protocol) throws Exception {
        /* Inport test variables start here */
        final int IT_LENGTH = 185;
        final boolean IT_DOINIT = false;
        final double IT_SAMPLETIME = 1.000000e-04;
        /* Inports: */
        final double[] it_in_I_A = { 0, 0, 0, -0.063514317731861252847, -0.12581841489663903033,
                -0.1869353513944209122, -0.24688774773514757244, -0.30569779341088249014, -0.36338725510855557355,
                -0.41997748476621449276, -0.47548942747577482848, -0.5299436292351847877, -0.58336024455288038038,
                -0.51835512553679863323, -0.45461770617020541563, -0.39212326436312339162, -0.33084756014429506088,
                -0.27076682625912862346, -0.21185775895099548394, -0.15409750892230997255, -0.097463672471878440295,
                -0.041934282805086507684, 0.012512198486451780316, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0.032502559508040818059, 0.064371269191337468496, 0.095618490094878480501, 0.12625634220429263199,
                0.15629670914687587846, 0.18575124280094243434, 0.21463136781528519004, 0.24294828604050094922,
                0.27071298087389694675, 0.29793622151966608902, 0.26617906265373564301, 0.23502701407134637956,
                0.20446854582245543863, 0.17449234765209245546, 0.14508732481422481619, 0.11624259396538827449,
                0.087947479136559009172, 0.060191507781778647024, 0.032964406902073667416, 0.0062560992432260792429, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0.032502559508040998471, 0.064371269191337662785, 0.095618490094878841323,
                0.12625634220429282628, 0.15629670914687607275, 0.18575124280094260087, 0.21463136781528519004,
                0.24294828604050094922, 0.27071298087389727982, 0.29793622151966625555, 0.26617906265373580954,
                0.23502701407134674039, 0.20446854582245579945, 0.17449234765209264975, 0.14508732481422501048,
                0.11624259396538864919, 0.087947479136559203461, 0.060191507781778834374, 0.032964406902073854766,
                0.0062560992432260792429, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.065005119016081275296,
                0.12874253838267421535, 0.19123698018975582302, 0.25251268440858493092, 0.31259341829375103528,
                0.37150248560188375846, 0.42926273563056971394, 0.48589657208100078822, 0.54142596174779389351,
                0.59587244303933173395, 0.53235812530747084192, 0.47005402814269342526, 0.40893709164491087726,
                0.34898469530418341211, 0.29017464962844885523, 0.23248518793077654898, 0.17589495827311765752,
                0.12038301556355766875, 0.065928813804146960131, 0.012512198486451022242, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                -0.031757158865931001124, -0.062909207448319695577, -0.093467675697210456098, -0.12344387386757361968,
                -0.15284889670544088425, -0.18169362755427759248, -0.20998874238310744067, -0.23774471373788760853,
                -0.26497181461759239385, -0.29168012227643996814, -0.25917756276839881702, -0.22730885308510234699,
                -0.19606163218156094641, -0.16542378007214697533, -0.13538341312956392315, -0.10592887947549754768,
                -0.077048754461154417283, -0.048731836235939025859, -0.020967141402542542605, 0.0062560992432262691951,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.031757158865930446012, -0.062909207448319154343,
                -0.09346767569721006752, -0.12344387386757361968, -0.15284889670544088425, -0.18169362755427759248,
                -0.20998874238310705209, -0.23774471373788705342, -0.26497181461759200527, -0.29168012227643941303,
                -0.25917756276839765128, -0.22730885308510120901, -0.1960616321815603913, -0.16542378007214642022,
                -0.13538341312956336804, -0.10592887947549606276, -0.077048754461153473594, -0.04873183623593788788,
                -0.020967141402541973616, 0.006256099243226837317, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        final double[] it_in_I_B = { 0, 0, 0, 0.031103736276511161074, 0.061627007106807019099,
                0.091580645277381897418, 0.12097528141064868568, 0.14982134773777577852, 0.17812908180111053369,
                0.20590853008751056064, 0.23316955159386604235, 0.25992182132608454559, 0.28617483373277352587,
                0.25551817614066363316, 0.22542541694138587549, 0.19588618379097236244, 0.16689029513429451401,
                0.13842775669569243324, 0.11048875803415919572, 0.083063669161885775316, 0.056143037225006554858,
                0.029717583245398675879, 0.0037781989224120594677, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                -0.061313315184219341347, -0.12149883358277527301, -0.18057729988360232687, -0.23856907719695802372,
                -0.29549415407416212975, -0.35137215139722866031, -0.40622232914177580643, -0.46006359301553395591,
                -0.5129145009747496653, -0.5647932696207229597, -0.50258579706770067919, -0.44153925540710853292,
                -0.38163197906595913711, -0.32284270679942556059, -0.26515057414517134715, -0.20853510601850147599,
                -0.1529762094457021715, -0.098454166432990847246, -0.044949626968553861583, 0.0075563978448237398983,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.031103736276511344955, 0.061627007106807206449,
                0.091580645277382077829, 0.12097528141064868568, 0.14982134773777597281, 0.17812908180111089451,
                0.20590853008751056064, 0.23316955159386623664, 0.25992182132608454559, 0.28617483373277369241,
                0.25551817614066402173, 0.22542541694138606978, 0.19588618379097255673, 0.16689029513429487483,
                0.13842775669569279406, 0.11048875803415939001, 0.083063669161886150016, 0.056143037225006749147,
                0.029717583245398866698, 0.0037781989224122489862, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                -0.030656657592109670674, -0.060749416791387268744, -0.090288649941800608323, -0.11928453859847884533,
                -0.14774707703708073181, -0.17568607569861374729, -0.20311116457088757015, -0.23003179650776658938,
                -0.25645725048737483265, -0.28239663481036125781, -0.25129289853385028408, -0.22076962770355465504,
                -0.19081598953297956855, -0.16142135339971222519, -0.132575287072585285, -0.10426755300925073799,
                -0.076488104722851057993, -0.049227083216495562401, -0.022474813484276930792, 0.0037781989224124385048,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.062207472553023057671, 0.1232540142136144129, 0.18316129055476340626,
                0.24195056282129703829, 0.29964269547555083539, 0.35625816360222106738, 0.41181706017502150985,
                0.46633910318773247328, 0.51984364265216864709, 0.57234966746554671868, 0.51103635228132615609,
                0.45085083388277097383, 0.39177236758194361466, 0.33378059026858786229, 0.27685551339138414484,
                0.22097751606831803062, 0.16612733832377046816, 0.11228607445001236032, 0.059435166490796213778,
                0.0075563978448234554036, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.030656657592109670674,
                -0.060749416791387268744, -0.090288649941800608323, -0.11928453859847884533, -0.14774707703708073181,
                -0.17568607569861433015, -0.20311116457088757015, -0.23003179650776658938, -0.25645725048737427754,
                -0.28239663481036070269, -0.25129289853384861875, -0.22076962770355293419, -0.19081598953297843058,
                -0.16142135339971164232, -0.13257528707258472989, -0.1042675530092490449, -0.076488104722849406536,
                -0.049227083216494091356, -0.022474813484275792813, 0.0037781989224130066267, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0 };
        final double[] it_in_I_C = { 0, 0, 0, 0.035732504011812091238, 0.070698920917851570955, 0.1049156752444668772,
                0.13839883938433383825, 0.17116414114602740426, 0.20322697114173227106, 0.23460239001656613134,
                0.26530513552290951873, 0.29534962944306536459, 0.32474998436350044351, 0.28742919525212667908,
                0.25094411092069035529, 0.21527601787208047734, 0.1804066216506736986, 0.14631803745895918811,
                0.11299278098427918693, 0.080413759430983583476, 0.048564262753395155692, 0.017427955085091421938,
                -0.013011133639895054726, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.035732504011811896949,
                0.070698920917851570955, 0.1049156752444668772, 0.13839883938433383825, 0.17116414114602740426,
                0.20322697114173210453, 0.23460239001656613134, 0.26530513552290929669, 0.29534962944306536459,
                0.32474998436350044351, 0.28742919525212667908, 0.25094411092069018876, 0.21527601787208028306,
                0.18040662165067389289, 0.14631803745895918811, 0.11299278098427900652, 0.080413759430983583476,
                0.048564262753395155692, 0.017427955085091231119, -0.013011133639894865641, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, -0.074641578222747570481, -0.14761174688562084256, -0.21894793298284070948, -0.28868672542565348982,
                -0.35686389380908289937, -0.42351440675844287398, -0.48867244986503372006, -0.55237144322021092258,
                -0.61464405855681836233, -0.67552223600679139892, -0.60405722798316796585, -0.53412439417108859008,
                -0.465690885517857589, -0.39872455723812405548, -0.33319395371473692347, -0.26906829372332718986,
                -0.20631745597365985789, -0.14491196496097275004, -0.084822977120660614236, -0.026022267279790487621,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.037320789111373597891, -0.073805873442809685758,
                -0.10947396649141941105, -0.14434336271282635633, -0.17843194690454072804, -0.21175720337922071534,
                -0.24433622493251666574, -0.27618572161010490618, -0.30732202927840901463, -0.33776111800339531088,
                -0.30202861399158359434, -0.26706219708554407299, -0.23284544275892840592, -0.19936227861906108405,
                -0.16659697685736771233, -0.13453414686166320635, -0.10315872798682955425, -0.072455982480486375019,
                -0.042411488560329925479, -0.013011133639894485736, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                -0.037320789111374153002, -0.073805873442810421281, -0.10947396649141998004, -0.14434336271282635633,
                -0.17843194690454072804, -0.2117572033792212427, -0.24433622493251722085, -0.27618572161010546129,
                -0.30732202927840901463, -0.33776111800339531088, -0.3020286139915828727, -0.26706219708554357339,
                -0.23284544275892785081, -0.19936227861906108405, -0.16659697685736771233, -0.13453414686166320635,
                -0.10315872798682898526, -0.07245598248048580603, -0.042411488560329550779, -0.013011133639894485736,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.071465008023623433075, 0.14139784183570239251, 0.2098313504889322556,
                0.27679767876866728793, 0.34232828229205403137, 0.40645394228346420906, 0.46920478003313148552,
                0.53061027104581792724, 0.59069925888612961895, 0.6494999687269993327, 0.57485839050424958341,
                0.50188822184137749094, 0.43055203574415829015, 0.36081324330134556533, 0.29263607491791643334,
                0.22598556196855465461, 0.16082751886196378077, 0.097128525506787369292, 0.034855910170180193219,
                -0.026022267279792003769, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        final double[] it_in_Enable = { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        /* Mask parameters: */
        final double[] it_mp_U_pulse = { 4 };
        final double[] it_mp_T_pulse = { 10 };
        final double[] it_mp_T_pause = { 1 };
        final double[] it_mp_U_max = { 12 };
        final double[] it_mp_ts_fact = { 1 };
        /* Outports: */
        final double[] it_out_U_A = { 0, 0, -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483,
                -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483,
                -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483, 0.33333333333333331483,
                0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483,
                0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483,
                0.33333333333333331483, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483,
                0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483,
                0.33333333333333331483, 0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483,
                -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483,
                -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        final double[] it_out_U_B = { 0, 0, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.33333333333333331483,
                -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483,
                -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483,
                -0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483,
                0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483,
                0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.33333333333333331483, 0.33333333333333331483,
                0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483,
                0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483,
                -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483,
                -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483,
                -0.33333333333333331483, -0.33333333333333331483, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        final double[] it_out_U_C = { 0, 0, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483,
                -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483,
                -0.33333333333333331483, -0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483,
                0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483,
                0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741, -0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741, 0.16666666666666665741,
                0.16666666666666665741, 0.16666666666666665741, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.33333333333333331483,
                0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483,
                0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483, 0.33333333333333331483,
                0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483,
                -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483,
                -0.33333333333333331483, -0.33333333333333331483, -0.33333333333333331483, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0 };
        final double[] it_out_Ready = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 };
        final double[] it_out_phi0 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.30831483545060139884,
                0.30831483545060139884, 0.30831483545060139884 };
        /* Outport Tolerances: */
        final double it_tol_U_A = 1 * Math.pow(2, -31);
        final double it_tol_U_B = 1 * Math.pow(2, -31);
        final double it_tol_U_C = 1 * Math.pow(2, -31);
        final double it_tol_Ready = 0 * Math.pow(2, -0);
        final double it_tol_phi0 = 200000 * Math.pow(2, -31);
        /* Inport test variables end here */

        // /* Parameter test variables start here */
        // final int PT_LENGTH = 3;
        // final boolean PT_DOINIT = true;
        // final double PT_SAMPLETIME = 0.0;
        // /* Inport: I_A */
        // final double pt_in_I_A = 0;
        // /* Inport: I_B */
        // final double pt_in_I_B = 0;
        // /* Inport: I_C */
        // final double pt_in_I_C = 0;
        // /* Inport: Enable */
        // final double pt_in_Enable = 0;
        // /* Mask parameter: U_pulse */
        // final double[][] pt_mp_U_pulse = { { 0 }, { 0 }, { 0 } };
        // /* Mask parameter: T_pulse */
        // final double[][] pt_mp_T_pulse = { { 0 }, { 0 }, { 0 } };
        // /* Mask parameter: T_pause */
        // final double[][] pt_mp_T_pause = { { 0 }, { 0 }, { 0 } };
        // /* Mask parameter: U_max */
        // final double[][] pt_mp_U_max = { { 0 }, { 0 }, { 0 } };
        // /* Mask parameter: ts_fact */
        // final double[][] pt_mp_ts_fact = { { 0 }, { 0 }, { 0 } };
        // /* Outport: U_A */
        // final double[] pt_out_U_A = { 0, 0, 0 };
        // /* Outport: U_B */
        // final double[] pt_out_U_B = { 0, 0, 0 };
        // /* Outport: U_C */
        // final double[] pt_out_U_C = { 0, 0, 0 };
        // /* Outport: Ready */
        // final double[] pt_out_Ready = { 0, 0, 0 };
        // /* Outport: phi0 */
        // final double[] pt_out_phi0 = { 0, 0, 0 };
        // /* Outport tolerances: U_A */
        // final double pt_tol_U_A = Math.pow(2, -31);
        // /* Outport tolerances: U_B */
        // final double pt_tol_U_B = Math.pow(2, -31);
        // /* Outport tolerances: U_C */
        // final double pt_tol_U_C = Math.pow(2, -31);
        // /* Outport tolerances: Ready */
        // final double pt_tol_Ready = Math.pow(2, -0);
        // /* Outport tolerances: phi0 */
        // final double pt_tol_phi0 = Math.pow(2, -31);
        // /* Parameter test variables end here */

        /* Conversion test variables start here */
        final int CT_LENGTH = 7;
        final double CT_SAMPLETIME = 0.0001;
        /* Mask parameter: U_pulse */
        final double[][] ct_mp_U_pulse = { { 0 }, { 12.1 }, { -12.1 }, { 57.3 }, { -7.9 }, { 7.9 }, { 7.9 } };
        /* Mask parameter: T_pulse */
        final double[][] ct_mp_T_pulse = { { 1 }, { 1 }, { 2 }, { 4 }, { 32767 }, { 32768 }, { 32769 } };
        /* Mask parameter: T_pause */
        final double[][] ct_mp_T_pause = { { 0 }, { 1 }, { 2 }, { 4 }, { 32767 }, { 32768 }, { 32769 } };
        /* Mask parameter: U_max */
        final double[][] ct_mp_U_max = { { 57.3 }, { -57.3 }, { 57.3 }, { 12.1 }, { -8.4 }, { 7.9 }, { 4.8 } };
        /* Mask parameter: ts_fact */
        final double[][] ct_mp_ts_fact = { { 1 }, { 1 }, { 4 }, { 4 }, { 1 }, { 1 }, { 1 } };
        /* Implementation parameter: u_pulse */
        final double[][] ct_cp_u_pulse = { { 0 }, { 453482585 }, { -453482585 }, { 2147483647 }, { -2019657240 },
                { 2147483647 }, { 2147483647 } };
        /* Implementation parameter: t_pulse */
        final double[][] ct_cp_t_pulse = { { 1 }, { 1 }, { 2 }, { 4 }, { 32767 }, { 32767 }, { 32767 } };
        /* Implementation parameter: t_period */
        final double[][] ct_cp_t_period = { { 2 }, { 12 }, { 9 }, { 18 }, { 32767 }, { 32767 }, { 32767 } };
        /* Implementation Parameter tolerances: u_pulse */
        final double ct_tol_u_pulse = 0.0;
        /* Implementation Parameter tolerances: t_pulse */
        final double ct_tol_t_pulse = 0.0;
        /* Implementation Parameter tolerances: t_period */
        final double ct_tol_t_period = 0.0;
        /* Conversion test variables end here */

        /* Conversion-on-Target test variables start here */
        /* ! Uses test vectors of Conversion test ! */
        /* Implementation Parameter tolerances: u_pulse */
        final double cott_tol_u_pulse = 200;
        /* Implementation Parameter tolerances: t_pulse */
        final double cott_tol_t_pulse = 0;
        /* Implementation Parameter tolerances: t_period */
        final double cott_tol_t_period = 0;
        /* Conversion-on-Target test variables end here */

        try {
            TestSuite suite = new TestSuite(protocol, "mchp_zsmt", "InitPosDetect", "FiP32");

            /* INPORT TEST */
            InportTest it = new InportTest("mchp_zsmt", "InitPosDetect", "FiP32", protocol, IT_DOINIT);
            Map<String, TData> it_mp = new HashMap<String, TData>();
            it_mp.put("U_pulse", new TNumeric(it_mp_U_pulse));
            it_mp.put("T_pulse", new TNumeric(it_mp_T_pulse));
            it_mp.put("T_pause", new TNumeric(it_mp_T_pause));
            it_mp.put("U_max", new TNumeric(it_mp_U_max));
            it_mp.put("ts_fact", new TNumeric(it_mp_ts_fact));
            it.setMaskParameters(it_mp);
            Map<String,  Double> it_tol = new HashMap<String, Double>();
            it_tol.put("U_A", it_tol_U_A);
            it_tol.put("U_B", it_tol_U_B);
            it_tol.put("U_C", it_tol_U_C);
            it_tol.put("Ready", it_tol_Ready);
            it_tol.put("phi0", it_tol_phi0);
            it.setTolerances(it_tol);
            for (int i = 0; i < IT_LENGTH; i++) {
                Map<String,  TNumeric> it_in = new HashMap<String, TNumeric>();
                Map<String,  TNumeric> it_out = new HashMap<String, TNumeric>();
                it_in.put("I_A", new TNumeric(it_in_I_A[i]));
                it_in.put("I_B", new TNumeric(it_in_I_B[i]));
                it_in.put("I_C", new TNumeric(it_in_I_C[i]));
                it_in.put("Enable", new TNumeric(it_in_Enable[i]));
                it_out.put("U_A", new TNumeric(it_out_U_A[i]));
                it_out.put("U_B", new TNumeric(it_out_U_B[i]));
                it_out.put("U_C", new TNumeric(it_out_U_C[i]));
                it_out.put("Ready", new TNumeric(it_out_Ready[i]));
                it_out.put("phi0", new TNumeric(it_out_phi0[i]));
                it.addConfig(it_in, it_out);
            }
            it.setSampleTime(IT_SAMPLETIME);
            suite.add(it);

            // /* PARAMETER TEST */
            // ParameterTest pt = new ParameterTest("mchp_zsmt", "InitPosDetect", "FiP32", protocol, PT_DOINIT);
            // Map<String, TNumeric> pt_in = new HashMap<String, TNumeric>();
            // pt_in.put("I_A", new TNumeric(pt_in_I_A));
            // pt_in.put("I_B", new TNumeric(pt_in_I_B));
            // pt_in.put("I_C", new TNumeric(pt_in_I_C));
            // pt_in.put("Enable", new TNumeric(pt_in_Enable));
            // pt.setInports(pt_in);
            // Map<String, Double> pt_tol = new HashMap<String, Double>();
            // pt_tol.put("U_A", pt_tol_U_A);
            // pt_tol.put("U_B", pt_tol_U_B);
            // pt_tol.put("U_C", pt_tol_U_C);
            // pt_tol.put("Ready", pt_tol_Ready);
            // pt_tol.put("phi0", pt_tol_phi0);
            // pt.setTolerances(pt_tol);
            // for (int i = 0; i < PT_LENGTH; i++) {
            // Map<String, TData> pt_mp = new HashMap<String, TData>();
            // Map<String, TNumeric> pt_out = new HashMap<String, TNumeric>();
            // pt_mp.put("U_pulse", new TNumeric(pt_mp_U_pulse[i]));
            // pt_mp.put("T_pulse", new TNumeric(pt_mp_T_pulse[i]));
            // pt_mp.put("T_pause", new TNumeric(pt_mp_T_pause[i]));
            // pt_mp.put("U_max", new TNumeric(pt_mp_U_max[i]));
            // pt_mp.put("ts_fact", new TNumeric(pt_mp_ts_fact[i]));
            // pt_out.put("U_A", new TNumeric(pt_out_U_A[i]));
            // pt_out.put("U_B", new TNumeric(pt_out_U_B[i]));
            // pt_out.put("U_C", new TNumeric(pt_out_U_C[i]));
            // pt_out.put("Ready", new TNumeric(pt_out_Ready[i]));
            // pt_out.put("phi0", new TNumeric(pt_out_phi0[i]));
            // pt.addConfig(pt_mp, pt_out);
            // }
            // pt.setSampleTime(PT_SAMPLETIME);
            // suite.add(pt);

            /* CONVERSION TEST */
            ConversionTest ct = new ConversionTest("mchp_zsmt", "InitPosDetect", "FiP32");
            Map<String,  Double> ct_tol = new HashMap<String, Double>();
            ct_tol.put("u_pulse", ct_tol_u_pulse);
            ct_tol.put("t_pulse", ct_tol_t_pulse);
            ct_tol.put("t_period", ct_tol_t_period);
            ct.setTolerances(ct_tol);
            for (int i = 0; i < CT_LENGTH; i++) {
                Map<String, TData> ct_mp = new HashMap<String, TData>();
                Map<String, TNumeric> ct_cp = new HashMap<String, TNumeric>();
                ct_mp.put("U_pulse", new TNumeric(ct_mp_U_pulse[i]));
                ct_mp.put("T_pulse", new TNumeric(ct_mp_T_pulse[i]));
                ct_mp.put("T_pause", new TNumeric(ct_mp_T_pause[i]));
                ct_mp.put("U_max", new TNumeric(ct_mp_U_max[i]));
                ct_mp.put("ts_fact", new TNumeric(ct_mp_ts_fact[i]));
                ct_cp.put("u_pulse", new TNumeric(ct_cp_u_pulse[i]));
                ct_cp.put("t_pulse", new TNumeric(ct_cp_t_pulse[i]));
                ct_cp.put("t_period", new TNumeric(ct_cp_t_period[i]));
                ct.addConfig(ct_mp, ct_cp);
            }
            ct.setSampleTime(CT_SAMPLETIME);
            suite.add(ct);

            /* CONVERSION-ON-TARGET TEST */
            ConversionOnTargetTest cott = new ConversionOnTargetTest("mchp_zsmt", "InitPosDetect", "FiP32", protocol);
            Map<String,  Double> cott_tol = new HashMap<String, Double>();
            cott_tol.put("u_pulse", cott_tol_u_pulse);
            cott_tol.put("t_pulse", cott_tol_t_pulse);
            cott_tol.put("t_period", cott_tol_t_period);
            cott.setTolerances(cott_tol);
            for (int i = 0; i < CT_LENGTH; i++) {
                Map<String, TData> cott_mp = new HashMap<String, TData>();
                Map<String, TNumeric> cott_cp = new HashMap<String, TNumeric>();
                /* Uses test data of Conversion test */
                cott_mp.put("U_pulse", new TNumeric(ct_mp_U_pulse[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("T_pulse", new TNumeric(ct_mp_T_pulse[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("T_pause", new TNumeric(ct_mp_T_pause[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("U_max", new TNumeric(ct_mp_U_max[i]));
                /* Uses test data of Conversion test */
                cott_mp.put("ts_fact", new TNumeric(ct_mp_ts_fact[i]));
                /* Use test data of Conversion test */
                cott_cp.put("u_pulse", new TNumeric(ct_cp_u_pulse[i]));
                /* Use test data of Conversion test */
                cott_cp.put("t_pulse", new TNumeric(ct_cp_t_pulse[i]));
                /* Use test data of Conversion test */
                cott_cp.put("t_period", new TNumeric(ct_cp_t_period[i]));
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
        new Test_InitPosDetect_FiP32(protocol);
    }
}
