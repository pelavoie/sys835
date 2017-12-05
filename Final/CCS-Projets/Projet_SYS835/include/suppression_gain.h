/*
 * suppression_curves.h
 *
 *  Created on: Dec 2, 2017
 *      Author: Eric Lacerte and Philippe Lavoie
 *
 *  File containing all related to the Bessel Suppression Gain.
 *
 */

#ifndef __SUPPRESSION_CURVES_H__
#define __SUPPRESSION_CURVES_H__

#include "../include/utils.h"

/*************************************** Definitions *********************************************/
#define NUMBER_OF_SUPPRESSION_VALUES	50

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Pre-generated lookup tables for Bessel functions
 * - For each epsilon, it contains NUMBER_OF_GAIN_VALUE of values, corresponding to Bessel Function value.
 * - The Bessel Values goes from 0 to 1.0 and is generated with Matlab.
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#define SUPPRESSION_FILTER_EPS_1		{0.1826390438621584,0.2118375855163274,0.2262089277030256,0.238433472627147,0.2497042119593004,0.2604874144191136,0.2710282545674763,0.2814788746929111,0.2919450082624416,0.3025067209956157,0.3132289387364079,0.3241673257939213,0.3353718161935208,0.3468888616576657,0.3587629299583045,0.3710375381070972,0.3837559782382285,0.3969618249595119,0.4106992723890803,0.4250133231517357,0.4399498331588125,0.4555554011383807,0.4718770783271676,0.4889618600399901,0.5068559060552636,0.5256034203286013,0.5452451023028297,0.5658160624210405,0.587343074667641,0.6098410218041614,0.6333083794464801,0.6577215917033072,0.6830282271874745,0.7091388899980382,0.7359180243142471,0.7631740310492398,0.7906495547184565,0.8180134408667364,0.8448567318330389,0.8706961312916897,0.8949894924606363,0.9171687670595813,0.9366959345531272,0.9531457722884142,0.9663142390250213,0.9763390782862815,0.9837910760143731,0.9896331119515696,0.9948714540189696,1}
#define SUPPRESSION_FILTER_EPS_2		{0.1313840911850666,0.1535157335608507,0.1651736631229797,0.175453641283021,0.1852125900145895,0.1947909028117957,0.204373224255182,0.2140795990958423,0.22399862286961,0.2342022052091117,0.244753093512302,0.2557091054114143,0.267125698088041,0.2790576213967922,0.2915600237172852,0.3046892002075225,0.318503079932565,0.3330614948447467,0.3484262390216638,0.3646609008766026,0.3818304290472027,0.4000003715443746,0.4192357060811316,0.4395991569048448,0.4611488706053231,0.4839353023545869,0.5079971489543932,0.5333561628920573,0.5600107032045621,0.5879279401208345,0.617034752455662,0.6472075654785238,0.6782616994089206,0.7099412543072094,0.7419111426818912,0.773753547515871,0.8049717078287904,0.8350042975298159,0.8632534543276544,0.8891283825405529,0.9121041242413001,0.9317915275913962,0.9480099189371386,0.9608489553850097,0.9707007345104155,0.9782369201232833,0.9842993800917184,0.9896822912597454,0.9948716520824166,1}
#define SUPPRESSION_FILTER_EPS_3		{0.08575045225034626,0.10094378942096,0.1094463777559036,0.1171823336232341,0.1247151966229446,0.132276121675625,0.1399975734847793,0.1479723315396161,0.1562750349280909,0.1649718948771843,0.1741257733304292,0.1837991718481656,0.1940561762839842,0.204963832712497,0.216593183484096,0.2290200722578074,0.2423257602003677,0.2565973517384261,0.2719279931541809,0.2884167735521688,0.3061682210057399,0.3252912444023024,0.3458973224001252,0.3680976855069983,0.3919991789389289,0.4176984405855429,0.4452739953072538,0.4747758796834554,0.5062125099321547,0.5395347454774984,0.5746175495605669,0.6112403732254419,0.6490684242166029,0.6876382746822097,0.7263525965544469,0.7644897480083708,0.8012337962112018,0.8357285990050751,0.8671553065132911,0.894826375982039,0.9182823229621955,0.9373722506981091,0.9522978814322454,0.9636040461791121,0.972105041830663,0.9787445182212978,0.9844009088469406,0.9896881053444697,0.9948716588094939,1}
#define SUPPRESSION_FILTER_EPS_4		{0.05154312342447923,0.06109679946355609,0.06671970425010842,0.07196880198895304,0.07718859306714207,0.08252701697601453,0.08807508686085889,0.09390225353720594,0.100069499307901,0.1066354498300482,0.1136597963703491,0.1212055488246132,0.129340748556163,0.1381399311715152,0.1476854816335635,0.158068949821032,0.1693923492515257,0.1817694256151453,0.1953268445233513,0.2102052021866581,0.2265597021597672,0.2445602593406124,0.2643906825677687,0.2862464439962766,0.3103303653233274,0.3368453454163637,0.3659830469115815,0.3979073095671892,0.4327310760074408,0.4704859822893079,0.5110847388315588,0.5542783021486501,0.5996128216049647,0.6463952981894584,0.6936809537258851,0.7402975888075027,0.7849199575066605,0.82619795768202,0.8629262530350911,0.8942243050029655,0.9196831884440995,0.939437100913682,0.9541347758832336,0.9648118121836511,0.9726880932026718,0.978929791258109,0.9844302752739444,0.9896891949597776,0.994871659253057,1}
#define SUPPRESSION_FILTER_EPS_5		{0.02905780838562872,0.03465339998901916,0.03808205626418977,0.04134851071024083,0.04465148357760723,0.04808083620355474,0.05169598036016831,0.05554588447746941,0.05967667473783649,0.06413540169105331,0.06897238604163895,0.07424300974355301,0.08000932424033481,0.08634166275434381,0.09332036577508432,0.1010376921522412,0.1095999669029955,0.1191299987639621,0.1297697774909592,0.1416834249481637,0.155060315094654,0.170118182213548,0.1871058848609927,0.206305259236396,0.2280311482006072,0.2526281980267053,0.2804623541931632,0.3119041853591875,0.3473003537862218,0.3869290736291183,0.4309359422798843,0.4792492199036424,0.5314798949607221,0.5868227098653702,0.6439886445311364,0.701211696404025,0.7563723667983419,0.8072551529124806,0.8519057570070192,0.8889954369703166,0.9180720652078598,0.9396073121726153,0.9548257267860436,0.9653791469841494,0.9729684958154061,0.9790119221060812,0.9844410509021438,0.9896894699926863,0.9948716592978873,1}
#define SUPPRESSION_FILTER_EPS_6		{0.01562556168281497,0.01873188502127705,0.02069707760312443,0.02259945620944626,0.02454861018057426,0.02659665360693429,0.02878029521582825,0.03113168999589527,0.03368270669679217,0.03646720394527884,0.03952261807140833,0.04289134327486654,0.04662212646803278,0.0507716076341459,0.05540610425141725,0.06060373041425615,0.06645694457429194,0.07307562814984669,0.08059080618947372,0.08915912551851002,0.09896819691113007,0.1102428713647891,0.1232524317879776,0.1383184990385671,0.1558231086318152,0.1762158093102908,0.2000176218514105,0.2278180971934789,0.2602593732843065,0.2979980941710706,0.3416329569578666,0.3915844201898216,0.4479178411181693,0.5101184377214215,0.5768618619899674,0.6458741347030079,0.7140124053295245,0.7776713659136869,0.8334887731659952,0.879129962492344,0.9138195520864103,0.9383838495522839,0.9548193514634693,0.9656167049762707,0.973112619227846,0.9790533072428441,0.9844457257248403,0.9896895558690988,0.9948716593040342,1}
#define SUPPRESSION_FILTER_EPS_7		{0.008119777172797851,0.009777936878148227,0.01085444995444099,0.01190997740471769,0.01300292362851989,0.01416236457671597,0.01540988656786047,0.01676529233961779,0.0182489324996452,0.01988304479123225,0.02169278475213286,0.02370720992069491,0.02596035122438096,0.02849246457583471,0.0313515480852412,0.03459521861593491,0.03829306015005185,0.04252958412555818,0.04740797852483597,0.05305486810532424,0.05962636157764908,0.06731571811044465,0.07636301305467072,0.08706719370475034,0.09980083321506128,0.11502760291447,0.1333217827648942,0.1553876521693759,0.1820737578502198,0.2143720084165055,0.2533834516389907,0.3002215438261937,0.3558132516853277,0.4205600716621828,0.4938592138960746,0.5735892966213302,0.6558287876728178,0.7351842020966635,0.8059360939006059,0.8636796922743742,0.9066233423376828,0.9358110456125042,0.9542605240377771,0.9656445466428863,0.9731844387265299,0.9790759202008861,0.9844480209908544,0.9896895873801955,0.9948716593050972,1}
#define SUPPRESSION_FILTER_EPS_8		{0.004114552470504549,0.004974572003379716,0.005545110555228753,0.006110482037502485,0.006701017321984123,0.007332449072685119,0.008016975289253988,0.00876619016442964,0.009592328968933321,0.01050903355615466,0.01153198945413474,0.01267957535100612,0.01397360427198247,0.01544021985855994,0.01711101378511457,0.01902444374310544,0.02122765407658342,0.02377883420259364,0.02675029616727388,0.03023251623220554,0.03433947171616265,0.03921571983696693,0.04504581604747554,0.05206685738630599,0.06058515082667152,0.07099820353563355,0.08382329055860922,0.0997334883829317,0.1196006433427256,0.1445410054304815,0.1759508763787542,0.2155029762738546,0.265045611932871,0.3263084677055074,0.4002964842954655,0.4863232237984851,0.5809188664617381,0.6773484550513419,0.766731237448634,0.8409331065933352,0.8956744735223535,0.9316552542119683,0.9531488182138396,0.9655063034194517,0.9732112751198086,0.9790887425436197,0.9844492582219546,0.9896896005150143,0.9948716593053184,1}
#define SUPPRESSION_FILTER_EPS_9		{0.002045399301184754,0.002481864005835427,0.002776862784607175,0.003071852751762314,0.00338227611228487,0.003716445604722437,0.004081045908974859,0.004482612067174738,0.00492818181870095,0.005425721848655154,0.00598450514985607,0.006615514035932896,0.007331914823683918,0.008149645063236273,0.009088159403092818,0.01017139248780394,0.01142901684505166,0.01289810247212452,0.01462532630854649,0.01666993943864365,0.01910778579740475,0.02203679011644641,0.02558451155521417,0.02991861575039306,0.03526148074129515,0.04191065160689184,0.05026750850517367,0.06087725880608794,0.07448394901173369,0.09210383168765961,0.1151170818353654,0.1453668205867066,0.1852260893992679,0.2375324795748065,0.3051858755022613,0.3901008484915293,0.4913163330936255,0.602821337300415,0.7130757408314599,0.8084727984211524,0.8796402236670694,0.9254287247193193,0.9513836046579538,0.965206580352177,0.9732049184643495,0.9790958521860299,0.9844499733971388,0.9896896065873817,0.9948716593053718,1}
#define SUPPRESSION_FILTER_EPS_10		{0.001001438207884809,0.001219194000169726,0.001368822560767219,0.001519648535455279,0.001679412082454245,0.001852424400504319,0.002042263226779762,0.002252508024452341,0.002487076688527521,0.002750457823352509,0.003047926871331717,0.003385785048698549,0.003771647191680788,0.004214803618267472,0.004726685837861297,0.0053214751579876,0.006016907556087092,0.006835349407470826,0.007805249873901349,0.008963121834684198,0.01035627176503068,0.0120466017210303,0.01411596192452634,0.01667376887398412,0.01986796540858606,0.02390095211299357,0.02905295959087045,0.03571658260234348,0.04444797792291172,0.05604250551996894,0.07164471952522693,0.09290201096759611,0.1221600058263416,0.1626556743897755,0.2185479938237297,0.2943794824203778,0.3932416712856007,0.5131094600153473,0.642889292355901,0.7633648200979516,0.8565853758424822,0.9163421999249817,0.9487651060598336,0.964722932424663,0.9731693400004473,0.9790992242659626,0.9844504076804198,0.9896896096461359,0.9948716593053866,1}
#define SUPPRESSION_FILTER_EPS_11		{0.0004841845977635518,0.0005913170543193006,0.0006660401652882095,0.0007419072880661822,0.0008227490334842097,0.000910768016226738,0.00100784360326998,0.001115893301730909,0.001237044450690924,0.001373758618969998,0.001528952217858458,0.001706133473851643,0.001909570280518662,0.002144503780434964,0.002417425990597011,0.002736445977306901,0.003111778609464912,0.003556404127674743,0.004086967935563218,0.004725021793282607,0.005498755789485203,0.006445444445390552,0.007614945264568592,0.009074768920471602,0.01091752830735001,0.01327203739290465,0.01632008393043754,0.02032212902638296,0.02565718638423861,0.03288533299270455,0.04284618415539217,0.05681325461305643,0.07672997792254556,0.1055467632585204,0.1476209414298223,0.2089286142095531,0.296284621495569,0.4139304626007612,0.5564231041329124,0.7027503786103289,0.8239274368328582,0.9032113137735635,0.9449697503933026,0.9640070118705708,0.9731036184512079,0.9790998232209646,0.9844506788806076,0.9896896113019135,0.994871659305391,1}
#define SUPPRESSION_FILTER_EPS_12		{0.000231601663488633,0.0002836895432175841,0.0003205217234644559,0.0003581666157255017,0.0003984998289109612,0.0004426327148702705,0.0004915374529815717,0.0005462229935884109,0.0006078217373019542,0.0006776552199921787,0.0007573000595471534,0.0008486644930142302,0.0009540834512614321,0.00107644071009594,0.00121932894262668,0.001387262393034542,0.00158596285099814,0.001822748544239032,0.002107069007456762,0.002451249393446831,0.002871539065094947,0.003389608209068848,0.004034713570005334,0.004846878678718071,0.005881636798071506,0.007217221309859533,0.008965655455017428,0.01129016384947679,0.01443301019890818,0.01876080452537986,0.02483945193881784,0.03355968258210848,0.04634814331999879,0.06551748445306974,0.09481639522467042,0.1401647465304851,0.2101568103371173,0.3146645441440767,0.4579075073811084,0.6250855142257845,0.7785796176450708,0.884334015555542,0.9395024745212937,0.9629790922200291,0.9730028308391756,0.9790980647361744,0.9844508483464823,0.9896896122545159,0.9948716593053925,1}
#define SUPPRESSION_FILTER_EPS_13		{0.0001097499454130748,0.0001348162946645875,0.0001527680836060283,0.0001712293703884478,0.0001911100710510209,0.0002129649327983045,0.000237290334529604,0.0002646092477059233,0.0002955146294313065,0.0003307036942317733,0.0003710133739263178,0.0004174622242660292,0.0004713030710237966,0.0005340911980772059,0.000607774298522128,0.0006948127548510223,0.0007983423918425008,0.0009223972358864151,0.001072217977850289,0.00125468433853991,0.001478928944734862,0.00175722091311594,0.002106256336269242,0.00254907270793886,0.003117936818796402,0.003858779754494075,0.004838139275375593,0.006154250687527595,0.007955150845560404,0.01046890184893126,0.01405521758314486,0.01929563551965945,0.02715410141711138,0.03926640769880942,0.05845909514019397,0.08963705546413801,0.1410730116681043,0.2252939993582586,0.3557933278178995,0.5319120891388253,0.7175269319356764,0.8573782051904447,0.9316228167099977,0.961516425450924,0.97285783769919,0.9790940169129368,0.9844509495031415,0.9896896128315981,0.994871659305393,1}
#define SUPPRESSION_FILTER_EPS_14		{5.157627148159326e-005,6.352976973962745e-005,7.219294074554139e-005,8.115356429520693e-005,9.084947707786477e-005,0.0001015549726952321,0.0001135206176888855,0.0001270139875339511,0.0001423412309325338,0.0001598647662433524,0.0001800220798276787,0.0002033482879333338,0.0002305047547822149,0.0002623164201331991,0.0002998213339481488,0.0003443372634939283,0.0003975523223612604,0.0004616497234144264,0.0005394815605955201,0.0006348139312907499,0.0007526772992527297,0.0008998744186669688,0.001085727926294341,0.001323198763533024,0.001630588973296841,0.002034183684113219,0.00257243475991394,0.003302733091873521,0.004312634129237903,0.005738943881001395,0.0078010582112427,0.01086086675384563,0.01553349409906614,0.02289751110472899,0.03490184022440868,0.05515433649520604,0.09038027080382983,0.1526469662480003,0.2604221336150141,0.4291959160330362,0.6390798885740225,0.8193770721333277,0.9202407532908158,0.9594339428930049,0.9726542202705246,0.9790874794081689,0.9844510009366358,0.9896896131967287,0.9948716593053932,1}
#define SUPPRESSION_FILTER_EPS_15		{0.2280558128776632,0.2626915457034704,0.278537816818187,0.2914790921223643,0.3030155304115615,0.3137302638438529,0.3239257913779015,0.3337856341792743,0.3434333297112592,0.352958725107455,0.3624313420448175,0.3719078485063554,0.3814365564028805,0.3910602989312639,0.4008183715380334,0.4107479061157908,0.4208848895113659,0.431264952432207,0.4419240068082846,0.452898781142179,0.4642272855114263,0.4759492259192582,0.4881063788915544,0.500742929873732,0.5139057718636907,0.5276447527809326,0.5420128502515269,0.5570662395300509,0.5728642025772094,0.5894688017229635,0.6069442069748752,0.6253555179923321,0.6447668549341053,0.6652384003871257,0.6868219500119779,0.7095543654288482,0.7334481164773291,0.7584778617886331,0.7845617899265389,0.811536345046087,0.8391232622686117,0.8668891175007618,0.8942010153850679,0.9201897949809933,0.943748093547372,0.9636207253578718,0.9786943625049468,0.9886397404223037,0.9948507636572234,1}

/*************************************** Prototypes **********************************************/
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : GetSmoothedSuppressionValue
 *
 * 		arguments:
 * 			- f_lCurrentGain: The current calculated Gain
 * 			- f_lPreviousGain : The last applied Gain.
 * 		Description:
 * 			it "smooth" the current calculated gain to minimize brutal variations. (�q. 6 et 7)
 * 		returns:
 * 			- (float) Smoothed value of suppression to apply.
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
float GetSmoothedSuppressionValue(const float f_lCurrentGain, const float f_lPreviousGain);

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : ApplyGainOnChFrame
 *
 * 		arguments:
 * 			- f_ptFrame :  	A pointer to a Frame of data as float.
 * 			- f_lGain: 		The Gain to be apply.
 * 		Description:
 * 			Apply gain to the frame data.
 * 		returns:
 * 			- void
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void ApplyGainOnChFrame(const float f_lGain, tFRAME* f_ptFrame );

#endif/*__SUPPRESSION_CURVES_H__*/
