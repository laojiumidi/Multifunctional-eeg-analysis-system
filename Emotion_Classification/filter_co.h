#include <math.h>
const int NL = 119;
double NUM[119] = {
  8.680669726594e-46,                 0,-5.121595138691e-44,                 0,
   1.48526259022e-42,                 0,-2.821998921419e-41,                 0,
  3.950798489986e-40,                 0,-4.345878338985e-39,                 0,
  3.911290505086e-38,                 0,-2.961405668137e-37,                 0,
  1.924913684289e-36,                 0,-1.090784421097e-35,                 0,
  5.453922105485e-35,                 0,-2.429474392443e-34,                 0,
  9.717897569773e-34,                 0,-3.513393736764e-33,                 0,
  1.154400799223e-32,                 0,-3.463202397668e-32,                 0,
  9.523806593586e-32,                 0,-2.40896284426e-31,                 0,
  5.620913303273e-31,                 0,-1.212933923338e-30,                 0,
  2.425867846676e-30,                 0,-4.505183143826e-30,                 0,
    7.7816799757e-30,                 0,-1.251835474352e-29,                 0,
  1.877753211528e-29,                 0,-2.628854496139e-29,                 0,
  3.437732802643e-29,                 0,-4.201673425453e-29,                 0,
  4.801912486231e-29,                 0,-5.133078864592e-29,                 0,
  5.133078864592e-29,                 0,-4.801912486231e-29,                 0,
  4.201673425453e-29,                 0,-3.437732802643e-29,                 0,
  2.628854496139e-29,                 0,-1.877753211528e-29,                 0,
  1.251835474352e-29,                 0, -7.7816799757e-30,                 0,
  4.505183143826e-30,                 0,-2.425867846676e-30,                 0,
  1.212933923338e-30,                 0,-5.620913303273e-31,                 0,
   2.40896284426e-31,                 0,-9.523806593586e-32,                 0,
  3.463202397668e-32,                 0,-1.154400799223e-32,                 0,
  3.513393736764e-33,                 0,-9.717897569773e-34,                 0,
  2.429474392443e-34,                 0,-5.453922105485e-35,                 0,
  1.090784421097e-35,                 0,-1.924913684289e-36,                 0,
  2.961405668137e-37,                 0,-3.911290505086e-38,                 0,
  4.345878338985e-39,                 0,-3.950798489986e-40,                 0,
  2.821998921419e-41,                 0,-1.48526259022e-42,                 0,
  5.121595138691e-44,                 0,-8.680669726594e-46
};
const int DL = 119;
double DEN[119] = {
                   1,   -102.4319561038,    5203.157814349,   -174743.9027293,
      4364768.642705,   -86485019.30376,     1415913618.75,   -19699249831.79,
      237738920535.4,    -2528093402990,2.398212671975e+13,-2.049805456678e+14,
  1.591604750298e+15,-1.130431681562e+16,7.387186296419e+16,-4.463975844613e+17,
  2.505343980598e+18,-1.310915853479e+19,6.416646847379e+19,-2.946914713778e+20,
  1.273252959322e+21,-5.187912183275e+21,1.997755489105e+22,-7.284776279424e+22,
  2.519934173027e+23,-8.282626396645e+23,2.590594319557e+24,-7.721046990644e+24,
  2.195551074383e+25,-5.96353235567e+25,1.548886728412e+26,-3.850525713344e+26,
  9.170668904863e+26,-2.094256199481e+27,4.589305003305e+27,-9.657580290821e+27,
  1.952933165504e+28,-3.79731391638e+28,7.103766410497e+28,-1.279259885893e+29,
  2.218731810194e+29,-3.707907543787e+29,5.973354557165e+29,-9.27996246223e+29,
  1.390825429966e+30,-2.011615015207e+30,2.808654718908e+30,-3.786666435523e+30,
  4.930988705102e+30,-6.203428498802e+30,7.541241051846e+30,-8.860328618339e+30,
  1.006296682101e+31,-1.10493188153e+31,1.173095330131e+31,-1.204386163098e+31,
  1.195833077432e+31,-1.148357054405e+31,1.066610220245e+31,-9.582293924763e+30,
  8.326691001388e+30,-6.998591287643e+30,5.689469583059e+30,-4.473375194295e+30,
  3.401514441788e+30,-2.501182224707e+30,1.778313520213e+30,-1.222380747421e+30,
  8.122244785825e+29,-5.216078110007e+29,3.236891340133e+29,-1.940599893605e+29,
  1.123739013459e+29,-6.283530427575e+28,3.391775524449e+28,-1.766853276199e+28,
   8.87926046868e+27,-4.303247947774e+27,2.010417613378e+27,-9.050228942851e+26,
  3.923867910584e+26,-1.637695048756e+26,6.576289853673e+25,-2.539249796614e+25,
  9.421810344872e+24,-3.357180502371e+24,1.147917716689e+24, -3.7635904727e+23,
  1.182177303943e+23,-3.554311759416e+22,1.021864083097e+22,-2.806289238873e+21,
   7.35311921403e+20,-1.835971261527e+20,4.362370905117e+19,-9.849076428025e+18,
  2.109493382955e+18,-4.278543857749e+17,8.201568946671e+16,-1.482655909266e+16,
  2.521642655074e+15,-4.024067113126e+14,6.007385676422e+13,    -8361435884597,
       1080917251241,   -129218874085.7,     14213444552.5,   -1430124567.979,
      130725719.8063,   -10766982.28453,     791123.910107,   -51221.63782968,
       2876.84654325,   -137.3137462903,    5.415580237389,  -0.1694393595833,
   0.003942993562801,-6.06680538537e-05,4.629235680874e-07
};