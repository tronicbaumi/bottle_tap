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

public class Test_InitPosDetect_Float32 {

    public Test_InitPosDetect_Float32(Protocol protocol) throws Exception {
        /* Inport test variables start here */
        final int IT_LENGTH = 185;
        final boolean IT_DOINIT = false;
        final double IT_SAMPLETIME = 1.000000e-04;
        /* Inports: */
        final double[] it_in_I_A = { 0, 0, 0, -19.054295319558377741, -37.745524468991710876, -56.080605418326271661,
                -74.066324320544268289, -91.70933802326474904, -109.01617653256667495, -125.99324542986434494,
                -142.64682824273245387, -158.98308877055544031, -175.00807336586410656, -155.50653766103960152,
                -136.3853118510616298, -117.63697930893701482, -99.254268043288519152, -81.230047877738584816,
                -63.557327685298645292, -46.229252676692993873, -29.239101741563530368, -12.580284841525951833,
                3.7536595459355339699, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9.7507678524122454178, 19.311380757401241937,
                28.685547028463542318, 37.876902661287793705, 46.889012744062760873, 55.725372840282730635,
                64.389410344585556345, 72.884485812150288098, 81.213894262169077365, 89.380866455899820266,
                79.853718796120688239, 70.508104221403911538, 61.340563746736634698, 52.34770429562773586,
                43.526197444267445746, 34.872778189616482791, 26.384243740967704639, 18.05745233453359333,
                9.8893220706221001137, 1.8768297729678238284, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9.7507678524123004848,
                19.31138075740129878, 28.685547028463652453, 37.876902661287850549, 46.889012744062817717,
                55.725372840282780373, 64.389410344585556345, 72.884485812150288098, 81.213894262169191052,
                89.38086645589987711, 79.853718796120745083, 70.508104221404025225, 61.34056374673674128,
                52.347704295627792703, 43.52619744426750259, 34.872778189616596478, 26.384243740967761482,
                18.057452334533650173, 9.8893220706221569571, 1.8768297729678238284, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                19.501535704824380701, 38.622761514802263605, 57.371094056926750682, 75.753805322575473724,
                93.778025488125308584, 111.45074568056512021, 128.77882068917091374, 145.76897162430023513,
                162.42778852433815473, 178.76173291179952685, 159.70743759224126279, 141.01620844280802203,
                122.68112749347325519, 104.69540859125503118, 87.052394888534664119, 69.745556379232965583,
                52.768487481935295591, 36.114904669067300347, 19.778644141244086541, 3.7536595459353065962, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, -9.5271476597793007812, -18.872762234495908729, -28.04030270916313583,
                -37.033162160272084407, -45.854669011632267939, -54.508088266283280632, -62.996622714932229314,
                -71.32341412136628378, -79.491544385277720153, -87.504036682931996438, -77.753268830519644439,
                -68.192655925530701211, -58.818489654468287142, -49.627134021644096151, -40.615023938869178721,
                -31.778663842649265803, -23.114626338346326406, -14.61955087078170834, -6.2901424207627627538,
                1.8768297729678806718, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -9.5271476597791338037, -18.872762234495745304,
                -28.040302709163022143, -37.033162160272084407, -45.854669011632267939, -54.508088266283280632,
                -62.996622714932115628, -71.32341412136611325, -79.491544385277606466, -87.504036682931825908,
                -77.753268830519303378, -68.19265592553036015, -58.818489654468116612, -49.627134021643925621,
                -40.615023938869008191, -31.778663842648818161, -23.114626338346042189, -14.61955087078136728,
                -6.2901424207625922236, 1.876829772968051202, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        final double[] it_in_I_B = { 0, 0, 0, 9.3311208829533480724, 18.488102132042104842, 27.474193583214567838,
                36.292584423194604426, 44.946404321332735776, 53.438724540333161883, 61.772559026253169634,
                69.950865478159812483, 77.976546397825359236, 85.85245011983205643, 76.655452842199096608,
                67.627625082415761426, 58.765855137291708843, 50.06708854028835276, 41.52832700870773408,
                33.146627410247759826, 24.919100748565732317, 16.842911167501966929, 8.9152749736196028607,
                1.1334596767236178039, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -18.393994555265802404, -36.449650074832582902,
                -54.173189965080695174, -71.570723159087407339, -88.648246222248644699, -105.41164541916859321,
                -121.8666987425327477, -138.019077904660179, -153.87435029242490714, -169.43798088621687725,
                -150.77573912031019177, -132.46177662213256099, -114.48959371978773447, -96.8528120398276684,
                -79.5451722435514057, -62.560531805550439799, -45.892862833710651671, -29.536249929897252287,
                -13.48488809056615878, 2.2669193534471219209, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9.3311208829534031395,
                18.488102132042161685, 27.474193583214624681, 36.292584423194604426, 44.94640432133279262,
                53.438724540333268465, 61.772559026253169634, 69.950865478159869326, 77.976546397825359236,
                85.852450119832113273, 76.655452842199210295, 67.62762508241581827, 58.765855137291765686,
                50.067088540288459342, 41.528327008707840662, 33.14662741024781667, 24.919100748565846004,
                16.842911167502023773, 8.9152749736196597041, 1.1334596767236746473, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                -9.1969972776329012021, -18.224825037416181317, -27.086594982540180609, -35.785361579543653932,
                -44.324123111124215768, -52.705822709584126073, -60.933349371266267269, -69.009538952329975814,
                -76.937175146212453569, -84.718990443108381783, -75.387869560155081672, -66.230888311066394181,
                -57.244796859893867236, -48.42640601991366367, -39.772586121775589163, -31.280265902775219899,
                -22.94643141685531873, -14.768124964948668776, -6.7424440452830793902, 1.1334596767237314907, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 18.662241765906916413, 36.97620426408432337, 54.948387166429021988,
                72.585168846389109376, 89.892808642665244179, 106.87744908066632377, 123.54511805250645295,
                139.90173095631973865, 155.95309279565060478, 171.70490023966399917, 153.31090568439785216,
                135.25525016483129548, 117.53171027458307663, 100.13417708057636446, 83.056654017415240787,
                66.293254820495405966, 49.838201497131137785, 33.685822335003706485, 17.830549947238864661,
                2.2669193534470366558, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -9.1969972776329012021, -18.224825037416181317,
                -27.086594982540180609, -35.785361579543653932, -44.324123111124215768, -52.705822709584296604,
                -60.933349371266267269, -69.009538952329975814, -76.937175146212283039, -84.718990443108211252,
                -75.387869560154584292, -66.23088831106588259, -57.244796859893533281, -48.426406019913493139,
                -39.772586121775418633, -31.280265902774715414, -22.94643141685482135, -14.768124964948228239,
                -6.7424440452827383297, 1.133459676723902021, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        final double[] it_in_I_C = { 0, 0, 0, 10.719751203543626872, 21.209676275355469954, 31.474702573340064049,
                41.519651815300150588, 51.349242343808221278, 60.968091342519684872, 70.380717004969838513,
                79.5915406568728514, 88.604888832919613151, 97.424995309050132164, 86.228758575637996842,
                75.283233276207113249, 64.582805361624139096, 54.121986495202108358, 43.895411237687753214,
                33.897834295283757911, 24.124127829295076708, 14.569278826018546624, 5.2283865255274264427,
                -3.9033400919685163899, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10.719751203543570028, 21.209676275355469954,
                31.474702573340064049, 41.519651815300150588, 51.349242343808221278, 60.968091342519628029,
                70.380717004969838513, 79.591540656872794557, 88.604888832919613151, 97.424995309050132164,
                86.228758575637996842, 75.283233276207056406, 64.582805361624082252, 54.121986495202165202,
                43.895411237687753214, 33.897834295283701067, 24.124127829295076708, 14.569278826018546624,
                5.2283865255273695993, -3.9033400919684595465, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -22.392473466824270645,
                -44.283524065686250992, -65.684379894852213511, -86.606017627696047612, -107.05916814272487159,
                -127.05432202753286219, -146.60173495951011091, -165.71143296606328477, -184.39321756704552513,
                -202.65667080203741079, -181.21716839495039153, -160.23731825132657036, -139.70726565535727559,
                -119.61736717143722331, -99.958186114421081925, -80.720488116998154737, -61.895236792097961143,
                -43.473589488291821681, -25.446893136198184493, -7.8066801839371464666, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                -11.196236733412078479, -22.141762032842905228, -32.842189947425822538, -43.303008813847910119,
                -53.529584071362215525, -63.527161013766210829, -73.300867479754998612, -82.855716483031471853,
                -92.196608783522705721, -101.32833540101859171, -90.608584197475082078, -80.118659125663228338,
                -69.853632827678524109, -59.808683585718327436, -49.979093057210313589, -40.360244058498963682,
                -30.947618396048866884, -21.73679474414591084, -12.72344656809897856, -3.9033400919683458596, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, -11.196236733412245457, -22.141762032843125496, -32.842189947425993068,
                -43.303008813847910119, -53.529584071362215525, -63.527161013766374253, -73.300867479755169143,
                -82.855716483031642383, -92.196608783522705721, -101.32833540101859171, -90.608584197474854705,
                -80.118659125663072018, -69.853632827678353578, -59.808683585718327436, -49.979093057210313589,
                -40.360244058498963682, -30.947618396048696354, -21.73679474414574031, -12.723446568098864873,
                -3.9033400919683458596, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21.439502407087029923, 42.41935255071071964,
                62.949405146679680456, 83.039303630600187489, 102.69848468761621518, 121.93618268503925606,
                140.76143400993944965, 159.18308131374536174, 177.20977766583888524, 194.84999061809980958,
                172.45751715127488524, 150.56646655241323174, 129.16561072324748238, 108.24397299040366249,
                87.790822475374937994, 67.795668590566393163, 48.248255658589130235, 29.138557652036212176,
                10.456773051054057078, -7.806680183937601214, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
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
        final double[] it_mp_U_max = { 1 };
        final double[] it_mp_ts_fact = { 1 };
        /* Outports: */
        final double[] it_out_U_A = { 0, 0, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0 };
        final double[] it_out_U_B = { 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0 };
        final double[] it_out_U_C = { 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0 };
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
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.96859962204435534616,
                0.96859962204435534616, 0.96859962204435534616 };
        /* Outport Tolerances: */
        final double it_tol_U_A = 1 * Math.pow(2, -31);
        final double it_tol_U_B = 1 * Math.pow(2, -31);
        final double it_tol_U_C = 1 * Math.pow(2, -31);
        final double it_tol_Ready = 0 * Math.pow(2, -0);
        final double it_tol_phi0 = 500 * Math.pow(2, -31);
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
        final double[][] ct_cp_u_pulse = { { 0 }, { 12.1 }, { -12.1 }, { 57.3 }, { -7.9 }, { 7.9 }, { 7.9 } };
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
        final double cott_tol_u_pulse = 0.000001;
        /* Implementation Parameter tolerances: t_pulse */
        final double cott_tol_t_pulse = 0;
        /* Implementation Parameter tolerances: t_period */
        final double cott_tol_t_period = 0;
        /* Conversion-on-Target test variables end here */

        try {
            TestSuite suite = new TestSuite(protocol, "mchp_zsmt", "InitPosDetect", "Float32");

            /* INPORT TEST */
            InportTest it = new InportTest("mchp_zsmt", "InitPosDetect", "Float32", protocol, IT_DOINIT);
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
            // ParameterTest pt = new ParameterTest("mchp_zsmt", "InitPosDetect", "Float32", protocol, PT_DOINIT);
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
            ConversionTest ct = new ConversionTest("mchp_zsmt", "InitPosDetect", "Float32");
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
            ConversionOnTargetTest cott = new ConversionOnTargetTest("mchp_zsmt", "InitPosDetect", "Float32", protocol);
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
        new Test_InitPosDetect_Float32(protocol);
    }
}
