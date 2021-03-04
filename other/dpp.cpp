#include<iostream>
#include<vector>
#include<map>
#include <algorithm>
#include <math.h>
#include <cmath>
using namespace std;
 
template<class ForwardIterator>
inline size_t argmax(ForwardIterator first, ForwardIterator last)
{
    return std::distance(first, std::max_element(first, last));
}

 
int main() {
    int max_length = 10;
    float epsilon = 1e-10;
     
    std::map<uint64_t, std::vector<double> > spu_vec_map;
    spu_vec_map[0] = {1.14967254e-01, 1.14621206e-01, 5.16453310e-01, -2.51835797e-01, 5.29705324e-01, -1.90919467e-01, -1.83791552e-01, -5.41000842e-01};
    spu_vec_map[1] = {-3.30887501e-01, 9.08395783e-02, 1.71370360e-01, 1.79932836e-01, 3.83492819e-01, 1.63427087e-01, 7.04650137e-01, 3.87570684e-01};
    spu_vec_map[2] = {4.27075155e-01, -1.94580429e-01, -6.86003464e-01, 3.80628312e-01, -9.81531884e-02, -3.21680597e-02, -2.22766052e-01, -3.22448535e-01};
    spu_vec_map[3] = {-1.99999448e-02, -4.58979053e-01, -2.86971932e-01, 3.74589158e-02, -3.83593611e-03, 3.25451861e-01, -2.61912856e-01, 7.28457410e-01};
    spu_vec_map[4] = {3.22137176e-01, 1.75535435e-01, -7.43898657e-02, -5.03963908e-01, -7.29232816e-02, -7.72623415e-01, 5.83160496e-02, 1.53613096e-02};
    spu_vec_map[5] = {-3.56868128e-02, -4.04049156e-01, 2.48731808e-01, 5.47711255e-01, 4.70758889e-01, -4.78732347e-01, -1.22124776e-02, -1.50558507e-01};
    spu_vec_map[6] = {6.45564775e-02, 7.43024648e-02, 2.67613483e-01, 3.68613917e-01, -2.66354848e-01, 7.42423809e-01, -1.35750699e-01, 3.77163279e-01};
    spu_vec_map[7] = {-3.57936967e-01, -6.05330715e-02, 3.73389737e-01, 3.51035023e-01, -5.39791956e-01, -4.04174961e-01, 3.71000687e-01, -1.14878752e-01};
    spu_vec_map[8] = {3.83490733e-01, -3.40026714e-01, -4.52393574e-01, 1.67672984e-01, -4.65757761e-02, -2.11144293e-02, 6.71756544e-01, -2.25101177e-01};
    spu_vec_map[9] = {-1.83120376e-01, -4.22919649e-01, 3.07247888e-02, 7.09180548e-01, -4.86262320e-01, 1.63168357e-01, -1.36357232e-01, 4.53495858e-02};
    spu_vec_map[10] = {5.02270895e-01, -1.43422792e-01, -5.00928292e-01, -8.62058899e-02, -4.79337581e-01, -3.71671269e-01, -5.23668193e-02, -3.13284070e-01};
    spu_vec_map[11] = {6.32358009e-02, -3.66898183e-01, -5.56192578e-01, -3.63110860e-01, -3.44701468e-01, 1.66946260e-01, 3.38475788e-01, 3.98661838e-01};
    spu_vec_map[12] = {-3.03661656e-01, -2.13119003e-01, -1.76093966e-01, -6.88089927e-02, -1.18314008e-01, 6.80773762e-01, 2.74947940e-01, 5.23047453e-01};
    spu_vec_map[13] = {-1.37582837e-02, -3.40740061e-01, 3.51047842e-01, 9.77634790e-02, -3.28775410e-02, 4.31380153e-01, -2.94919141e-01, -6.90483574e-01};
    spu_vec_map[14] = {2.53956178e-01, 1.68433022e-01, 4.25694121e-01, -2.31550197e-01, 3.78184860e-01, 1.02188436e-01, 4.36308917e-01, 5.73126393e-01};
    spu_vec_map[15] = {-2.28541788e-01, 1.23053933e-01, -2.50122903e-01, -3.82300801e-01, -3.72683346e-01, -7.48873962e-02, 5.83585839e-01, -4.88710120e-01};
    spu_vec_map[16] = {6.60183080e-01, 6.76383032e-01, -1.93980823e-01, 1.68701282e-03, 2.00327894e-01, 1.09706235e-01, -9.10528201e-03, 1.29550218e-01};
    spu_vec_map[17] = {-6.19508501e-01, 2.65814781e-01, 7.49391889e-02, 2.20708707e-01, 4.79259905e-01, 1.34614443e-01, 2.99530191e-01, -3.92038345e-01};
    spu_vec_map[18] = {4.17696872e-01, -7.14046807e-01, -4.48089952e-01, -7.56562875e-02, -2.54698451e-01, 1.61537794e-01, 7.90262629e-02, -1.09302745e-01};
    spu_vec_map[19] = {-5.89074920e-02, -6.64386788e-01, 9.03536158e-02, 1.85099505e-01, -4.12335402e-01, -5.18420195e-01, -2.32412308e-01, 1.41063950e-01};
    spu_vec_map[20] = {1.01494476e-01, -3.22943734e-01, -9.60223428e-02, -1.99795184e-01, -4.37465103e-01, 4.36270081e-01, 5.54481682e-01, -3.83549962e-01};
    spu_vec_map[21] = {1.96987739e-02, 7.14764973e-01, -1.31064367e-01, -3.03906091e-01, 4.08118700e-01, -1.27902192e-01, 5.52139948e-02, 4.39565447e-01};
    spu_vec_map[22] = {3.65590690e-01, -4.50365973e-01, -1.39544903e-01, 2.23580970e-01, 1.40910519e-02, 5.62132649e-02, -4.14678961e-01, -6.47097812e-01};
    spu_vec_map[23] = {3.10248929e-01, 4.17526191e-01, -4.31979553e-01, -2.82112684e-01, 2.01936858e-01, 2.27941582e-03, 5.02775051e-01, -4.11894573e-01};
    spu_vec_map[24] = {1.26233103e-01, -3.71153935e-01, -9.67460543e-02, 4.36758982e-01, -2.70153167e-01, 6.07800261e-02, 3.39645390e-01, 6.73910837e-01};
    spu_vec_map[25] = {-4.10210595e-01, 2.05629296e-01, -1.18169680e-01, 1.40251564e-01, 2.51012756e-01, 5.38252567e-01, 5.51620015e-01, -3.14326925e-01};
    spu_vec_map[26] = {2.93483811e-01, 3.05797487e-01, -5.36990239e-01, -6.02291237e-01, -2.60509725e-01, 1.10856189e-01, 1.74515709e-01, -2.42139949e-01};
    spu_vec_map[27] = {5.12791999e-01, -5.86178478e-01, 4.65613409e-01, 1.60740994e-01, -1.86971999e-03, 1.49969062e-01, 2.18949461e-01, 2.83500551e-01};
    spu_vec_map[28] = {-4.30274228e-01, 3.13554374e-02, 5.54819510e-01, -2.66487567e-01, 4.87600364e-01, -3.83215116e-01, 1.44049877e-01, 1.72285538e-01};
    spu_vec_map[29] = {2.81495106e-02, 3.11135212e-01, -4.95650363e-01, 5.07584496e-01, 4.54921009e-01, 1.14833140e-02, -3.54471971e-01, -2.57596221e-01};
    spu_vec_map[30] = {-7.54147114e-01, 5.26272366e-01, -4.50116886e-03, 8.71485126e-02, -2.86330037e-01, 2.04273628e-01, -1.35613924e-01, -6.76805895e-02};
    spu_vec_map[31] = {1.21940976e-01, -4.55413854e-01, -5.48940486e-01, 2.12702882e-01, -3.36603729e-01, -5.33788807e-01, 7.95517931e-02, -1.63062557e-01};
    spu_vec_map[32] = {1.68408067e-01, 3.69668400e-01, 1.32685673e-01, 2.76513226e-01, -4.00478007e-01, -8.94072816e-02, -5.27364556e-01, 5.42613374e-01};
    spu_vec_map[33] = {-8.16181874e-02, 2.68733526e-01, -8.56505779e-02, -1.51300911e-01, -5.58399993e-01, -6.31928440e-01, -3.75109580e-01, 1.97589154e-01};
    spu_vec_map[34] = {-4.49436298e-01, 2.10306089e-01, -1.17979968e-01, -6.43037835e-01, 1.94628108e-01, -1.10682679e-01, -6.57588108e-02, 5.21446503e-01};
    spu_vec_map[35] = {3.57014714e-01, 3.17408942e-02, -7.49679056e-01, -4.21411429e-01, 2.70077162e-01, -1.87118061e-03, 1.83128211e-01, -1.59516813e-01};
    spu_vec_map[36] = {3.70443737e-01, -2.89043216e-01, 6.14537565e-02, 3.58143247e-01, 3.67751545e-02, 1.66568977e-01, -1.43885485e-01, 7.72904676e-01};
    spu_vec_map[37] = {4.49642384e-01, 4.47746607e-01, -1.99282391e-01, -2.71469044e-01, 5.77083190e-01, 2.57775603e-01, -1.77176970e-01, 2.30371094e-01};
    spu_vec_map[38] = {-2.42677509e-01, -3.91693562e-01, -6.72466319e-02, -4.01091267e-01, 3.40077959e-02, -5.95735475e-01, 3.47730633e-01, -3.81200193e-01};
    spu_vec_map[39] = {6.38660170e-01, 2.27404040e-01, 4.71705501e-01, -1.85892581e-01, -4.42688898e-01, -1.09847224e-01, -7.58096685e-03, 2.74301138e-01};
    spu_vec_map[40] = {5.07609326e-01, 4.74528019e-01, -4.33612234e-01, 1.40023450e-01, -3.02799654e-01, -4.15901740e-01, -2.09069649e-01, -3.40263158e-02};
    spu_vec_map[41] = {-2.93512755e-01, -3.38303859e-01, 5.30242501e-01, 2.06896996e-01, 1.46113967e-01, 6.02170319e-01, -2.28259793e-01, -1.98434795e-01};
    spu_vec_map[42] = {2.87484067e-01, 1.99332858e-02, 2.57669196e-01, 6.33725278e-01, -4.14433935e-01, -1.28094785e-01, 4.30857188e-01, -2.74140029e-01};
    spu_vec_map[43] = {-4.73131988e-01, 4.11398094e-01, 2.89498390e-01, -2.00330719e-01, -1.19751014e-01, -6.79882944e-02, 2.98532568e-01, 6.12267594e-01};
    spu_vec_map[44] = {-7.65911220e-02, -1.92345699e-01, 1.27252172e-02, 4.07647748e-01, -4.44873201e-01, 6.26496345e-01, 3.83561080e-01, -2.30801597e-01};
    spu_vec_map[45] = {2.44369557e-01, 1.13657664e-02, -1.08586849e-01, 4.06193592e-01, 5.62900891e-01, 6.61947718e-01, -6.76053087e-02, 6.13785665e-02};
    spu_vec_map[46] = {4.60270401e-01, -3.18014349e-01, -3.27249618e-01, 5.77359637e-02, 1.27833271e-01, -3.45088098e-01, -6.20545578e-01, -2.36829735e-01};
    spu_vec_map[47] = {7.70733994e-01, -1.58966400e-01, -2.64187383e-01, 1.02926963e-03, -3.59593129e-01, 3.73259634e-01, 2.05603240e-01, 3.10708823e-04};
    spu_vec_map[48] = {-4.95399800e-02, 1.66767697e-01, -1.41915166e-01, -4.74493775e-02, 5.34323237e-01, -3.92941443e-01, -5.77038756e-01, -4.17690008e-01};
    spu_vec_map[49] = {4.19692668e-01, -2.51449933e-02, -4.40866270e-01, -4.08620935e-01, -4.13292689e-01, 2.78586312e-02, -2.95363222e-02, 5.37989139e-01};
    spu_vec_map[50] = {-1.01355927e-01, -3.85580674e-02, 1.69712111e-01, -5.07361142e-02, 1.28021442e-01, 1.33374919e-01, 6.70112546e-01, 6.88211243e-01};
    spu_vec_map[51] = {-4.93616108e-01, -7.16929651e-01, 2.50931325e-01, -1.60934141e-01, -3.14702086e-01, 1.08708809e-01, -3.52392728e-02, 2.03449924e-01};
    spu_vec_map[52] = {-1.22554966e-02, 1.18104328e-01, -7.79457440e-01, -3.95918536e-02, -1.33470391e-01, -2.06471476e-01, -2.24072424e-01, 5.15874488e-01};
    spu_vec_map[53] = {-2.84741938e-01, -4.08827704e-01, -5.21924523e-01, 3.21151870e-01, 3.80019589e-01, -4.45654642e-01, 1.44980375e-01, 1.10435267e-01};
    spu_vec_map[54] = {9.45382627e-02, -1.44116238e-01, -4.66227643e-01, -5.24315460e-01, 1.78028785e-01, 4.71418453e-02, -3.48033168e-01, -5.68308386e-01};
    spu_vec_map[55] = {5.64824404e-01, 1.54556246e-01, -3.03787695e-01, 2.25079892e-01, 4.22027594e-01, -3.47259012e-01, -1.30686739e-01, -4.45379278e-01};
    spu_vec_map[56] = {-2.74746600e-01, 5.37415652e-01, 3.63579613e-01, -1.81964348e-01, 1.66993402e-01, -4.64441570e-01, 3.01817803e-01, -3.68389480e-01};
    spu_vec_map[57] = {2.16073696e-01, -5.76417344e-01, -2.74775657e-01, 4.13985123e-01, 3.45105667e-01, 9.84366762e-03, 4.86036782e-01, -1.36906124e-01};
    spu_vec_map[58] = {1.46029921e-01, 6.48433293e-01, -1.10240380e-01, -6.05722019e-01, -2.37753221e-02, 1.59225347e-01, -3.29727487e-01, 2.10995802e-01};
    spu_vec_map[59] = {2.37830247e-01, -6.79900825e-01, 3.30675802e-01, -1.78970412e-01, 3.88443580e-01, 2.75477078e-01, 1.17885241e-01, -3.14836119e-01};
    spu_vec_map[60] = {-2.89808577e-01, -4.55684562e-01, 1.20394507e-01, -1.35955276e-01, -7.69196583e-01, 2.06534827e-01, -1.45613736e-01, -1.40927342e-01};
    spu_vec_map[61] = {2.52130347e-01, 1.96138186e-01, 4.20584186e-01, 7.25124577e-02, -5.67382808e-01, 5.38450709e-01, -2.77934581e-01, 1.63434816e-01};
    spu_vec_map[62] = {-1.36583849e-01, 1.52930355e-01, 4.45987266e-01, -6.46160078e-01, -2.03612489e-01, -3.33714705e-01, -3.51444436e-01, 2.55329061e-01};
    spu_vec_map[63] = {4.25315295e-01, 5.20179766e-01, 2.76736947e-01, 2.22260054e-01, 4.49139277e-01, -2.84299758e-01, 1.83763381e-01, -3.25907376e-01};
    spu_vec_map[64] = {-1.28060579e-01, -2.06769499e-01, -5.16625863e-01, 1.06270061e-01, -3.58306035e-01, 5.88834355e-01, -4.13081047e-01, -1.30023806e-01};
    spu_vec_map[65] = {4.45909839e-01, -4.59731903e-01, 9.67699035e-02, 3.31030590e-01, 1.98736718e-01, -2.21199137e-02, 5.34081103e-01, 3.81624329e-01};
    spu_vec_map[66] = {-3.86906259e-01, 3.48966801e-01, -5.25769686e-02, 5.04465518e-02, -3.50182112e-01, 2.54420147e-02, 7.19790344e-01, -2.86083169e-01};
    spu_vec_map[67] = {4.26426210e-01, -4.65257123e-01, -2.74995051e-01, 1.64569785e-01, -5.71769398e-01, -2.17994107e-01, -2.08197636e-01, -2.84961530e-01};
    spu_vec_map[68] = {2.01849366e-01, -1.07294551e-03, -6.75908212e-01, -2.55419454e-01, -3.87578515e-02, -5.96025314e-01, -2.60604003e-01, 1.11811808e-01};
    spu_vec_map[69] = {3.63621888e-02, 4.29335775e-01, 9.65527752e-02, 2.37383953e-02, -9.37457713e-02, 6.68121745e-01, -5.74192912e-01, 1.39964987e-01};
    spu_vec_map[70] = {1.69590147e-01, -4.25196988e-01, 1.03696085e-02, 6.31965597e-02, -1.30614770e-01, 2.13966421e-01, -2.01518023e-01, 8.26374012e-01};
    spu_vec_map[71] = {5.90512344e-01, 4.97876750e-02, -3.97595666e-02, -1.29396670e-02, 4.11044364e-03, -5.25986423e-01, 6.03719931e-01, -7.68877907e-02};
    spu_vec_map[72] = {4.53757395e-01, -5.34804594e-02, -2.59841669e-01, -3.78625571e-01, 9.62973679e-02, -4.99168470e-01, -5.62798585e-01, 7.20031877e-02};
    spu_vec_map[73] = {-1.03218351e-02, -2.61478349e-01, 3.63762946e-01, 2.56727657e-01, 8.60061472e-02, -2.87931754e-01, 6.76816388e-01, -4.30009054e-01};
    spu_vec_map[74] = {-3.51548434e-01, -4.94099015e-01, 1.57799959e-01, 5.14717946e-01, -3.27851059e-01, -4.18040876e-01, -1.24027012e-01, -2.11700920e-01};
    spu_vec_map[75] = {6.70719966e-02, -8.96746172e-02, -2.55950412e-01, 1.58064104e-01, 5.27779952e-02, 4.93006080e-02, 9.37694226e-01, 1.11706796e-01};
    spu_vec_map[76] = {1.21699937e-01, -4.29389712e-01, -1.57693799e-01, 4.56367282e-01, -7.46626356e-01, 9.13355067e-03, -3.26128492e-02, -9.52745236e-02};
    spu_vec_map[77] = {3.27983058e-01, -3.01625405e-02, -6.66448592e-01, 3.31331743e-01, -2.44729300e-01, -1.09729769e-02, -3.71798240e-01, -3.73277532e-01};
    spu_vec_map[78] = {-4.26340311e-01, -2.44498721e-01, -4.81788655e-01, 3.60465754e-01, 8.58904825e-02, 4.49928077e-01, 3.87127869e-01, -1.91619443e-01};
    spu_vec_map[79] = {-2.54375628e-01, -2.15464268e-01, -6.04532288e-01, -1.36655626e-01, -3.15424560e-01, -3.63302333e-01, 3.40427307e-01, 3.96688987e-01};
    spu_vec_map[80] = {-1.84581042e-01, 5.25742325e-01, 3.17024292e-01, 8.60295459e-02, -3.63288664e-01, 2.42799852e-01, 1.18755370e-01, 6.13666117e-01};
    spu_vec_map[81] = {4.99819533e-01, -2.57074148e-02, 5.77493335e-01, -1.36324144e-01, 2.63301817e-01, -3.34079113e-03, 5.46542591e-01, 1.71431989e-01};
    spu_vec_map[82] = {1.90653491e-01, 1.72936956e-01, 4.34944504e-01, 6.34700775e-01, -1.35634805e-01, -3.01941086e-01, -2.31722563e-01, 4.22447267e-01};
    spu_vec_map[83] = {-6.11293017e-01, -1.66360754e-01, 3.54050546e-01, -1.43676985e-01, -2.41269582e-01, -3.15670288e-01, -4.30818630e-01, -3.30434029e-01};
    spu_vec_map[84] = {2.69011295e-02, -1.54437697e-01, 2.30675493e-01, -2.40995772e-01, 3.96567339e-02, -5.65722750e-01, -3.46260962e-01, 6.50095102e-01};
    spu_vec_map[85] = {4.66373995e-01, -4.00659691e-02, 6.63016374e-01, 4.27621491e-01, 9.50166072e-02, 6.28467726e-02, -3.67345093e-01, -1.02561560e-01};
    spu_vec_map[86] = {4.31745885e-01, -2.20846111e-01, 4.72588834e-01, 5.75197756e-01, -1.44337432e-01, -4.27538764e-01, -7.72325206e-02, 3.22842227e-02};
    spu_vec_map[87] = {-4.19046018e-01, -3.94122529e-01, 3.52628147e-01, 4.81844456e-01, 2.79282969e-01, -1.26707444e-01, 3.03359837e-01, 3.55620912e-01};
    spu_vec_map[88] = {8.02910647e-02, -6.46747934e-02, 5.76284561e-02, -2.15141224e-01, 2.50183569e-01, -9.19182056e-01, -1.59628381e-01, 8.24320357e-02};
    spu_vec_map[89] = {-6.23491627e-01, 3.08610598e-01, -6.41945587e-01, 7.79943286e-02, -1.94282906e-01, -1.53037428e-01, -1.66385360e-01, -9.48158600e-02};
    spu_vec_map[90] = {1.71842280e-01, 3.39069790e-01, -2.53694165e-01, 4.60134330e-01, -2.90002282e-03, -8.85532900e-02, 5.79965886e-01, 4.84981499e-01};
    spu_vec_map[91] = {3.50282832e-01, 2.27761661e-01, -2.58793378e-01, 1.70935006e-01, 6.20057991e-01, 5.63294943e-01, 5.63112329e-02, -1.55851577e-01};
    spu_vec_map[92] = {6.23395448e-01, 2.88517008e-01, 5.22364403e-01, -3.07262007e-01, -1.31585266e-01, 3.32345362e-01, -1.81377831e-01, 1.39821592e-02};
    spu_vec_map[93] = {4.93142019e-01, 4.27616459e-02, 2.20090933e-01, 6.32315705e-01, 1.29862828e-01, -2.06981818e-01, -4.78576174e-01, 1.34082958e-01};
    spu_vec_map[94] = {-6.51658127e-01, 2.55047248e-01, 3.37868443e-01, -1.66906970e-01, 2.67169920e-01, -4.95935304e-01, -8.81324445e-02, 2.07799533e-01};
    spu_vec_map[95] = {-2.73669879e-01, 3.23919550e-01, 3.11339951e-01, -3.13442198e-02, 2.74227824e-01, 3.08558702e-01, 2.52926283e-02, 7.42439768e-01};
    spu_vec_map[96] = {-3.54599495e-01, 6.26123717e-01, -5.92650136e-01, -3.77240776e-02, 9.21556201e-02, -2.29758237e-01, 2.15332003e-01, 1.48059524e-01};
    spu_vec_map[97] = {-6.55058409e-02, 3.22937013e-01, -1.85597447e-02, 5.91112560e-01, -2.52016867e-01, -4.02549629e-01, 5.62043828e-01, 1.44975173e-02};
    spu_vec_map[98] = {-3.14661216e-01, 5.50743624e-01, 6.67227069e-02, -4.49715165e-01, 2.15969049e-01, -2.81443670e-02, 1.17535034e-01, -5.74216780e-01};
    spu_vec_map[99] = {-4.48653784e-01, 6.18719932e-02, 4.50325091e-01, -2.91836759e-01, -4.77307989e-01, 3.33225143e-01, 2.54411403e-01, -3.21454791e-01};
     
    std::vector<uint64_t> spuid_list;
    spuid_list.push_back(0);
    spuid_list.push_back(1);
    spuid_list.push_back(2);
    spuid_list.push_back(3);
    spuid_list.push_back(4);
    spuid_list.push_back(5);
    spuid_list.push_back(6);
    spuid_list.push_back(7);
    spuid_list.push_back(8);
    spuid_list.push_back(9);
    spuid_list.push_back(10);
    spuid_list.push_back(11);
    spuid_list.push_back(12);
    spuid_list.push_back(13);
    spuid_list.push_back(14);
    spuid_list.push_back(15);
    spuid_list.push_back(16);
    spuid_list.push_back(17);
    spuid_list.push_back(18);
    spuid_list.push_back(19);
    spuid_list.push_back(20);
    spuid_list.push_back(21);
    spuid_list.push_back(22);
    spuid_list.push_back(23);
    spuid_list.push_back(24);
    spuid_list.push_back(25);
    spuid_list.push_back(26);
    spuid_list.push_back(27);
    spuid_list.push_back(28);
    spuid_list.push_back(29);
    spuid_list.push_back(30);
    spuid_list.push_back(31);
    spuid_list.push_back(32);
    spuid_list.push_back(33);
    spuid_list.push_back(34);
    spuid_list.push_back(35);
    spuid_list.push_back(36);
    spuid_list.push_back(37);
    spuid_list.push_back(38);
    spuid_list.push_back(39);
    spuid_list.push_back(40);
    spuid_list.push_back(41);
    spuid_list.push_back(42);
    spuid_list.push_back(43);
    spuid_list.push_back(44);
    spuid_list.push_back(45);
    spuid_list.push_back(46);
    spuid_list.push_back(47);
    spuid_list.push_back(48);
    spuid_list.push_back(49);
    spuid_list.push_back(50);
    spuid_list.push_back(51);
    spuid_list.push_back(52);
    spuid_list.push_back(53);
    spuid_list.push_back(54);
    spuid_list.push_back(55);
    spuid_list.push_back(56);
    spuid_list.push_back(57);
    spuid_list.push_back(58);
    spuid_list.push_back(59);
    spuid_list.push_back(60);
    spuid_list.push_back(61);
    spuid_list.push_back(62);
    spuid_list.push_back(63);
    spuid_list.push_back(64);
    spuid_list.push_back(65);
    spuid_list.push_back(66);
    spuid_list.push_back(67);
    spuid_list.push_back(68);
    spuid_list.push_back(69);
    spuid_list.push_back(70);
    spuid_list.push_back(71);
    spuid_list.push_back(72);
    spuid_list.push_back(73);
    spuid_list.push_back(74);
    spuid_list.push_back(75);
    spuid_list.push_back(76);
    spuid_list.push_back(77);
    spuid_list.push_back(78);
    spuid_list.push_back(79);
    spuid_list.push_back(80);
    spuid_list.push_back(81);
    spuid_list.push_back(82);
    spuid_list.push_back(83);
    spuid_list.push_back(84);
    spuid_list.push_back(85);
    spuid_list.push_back(86);
    spuid_list.push_back(87);
    spuid_list.push_back(88);
    spuid_list.push_back(89);
    spuid_list.push_back(90);
    spuid_list.push_back(91);
    spuid_list.push_back(92);
    spuid_list.push_back(93);
    spuid_list.push_back(94);
    spuid_list.push_back(95);
    spuid_list.push_back(96);
    spuid_list.push_back(97);
    spuid_list.push_back(98);
    spuid_list.push_back(99);
     
    std::vector<double> scores;
    scores.push_back(1.21255397);
    scores.push_back(1.22609362);
    scores.push_back(1.21871747);
    scores.push_back(1.2325447);
    scores.push_back(1.22156332);
    scores.push_back(1.22951557);
    scores.push_back(1.21638655);
    scores.push_back(1.2054794);
    scores.push_back(1.21152725);
    scores.push_back(1.2210957);
    scores.push_back(1.23908162);
    scores.push_back(1.19762098);
    scores.push_back(1.21648203);
    scores.push_back(1.20829433);
    scores.push_back(1.22558482);
    scores.push_back(1.24316774);
    scores.push_back(1.22450405);
    scores.push_back(1.21383702);
    scores.push_back(1.23525815);
    scores.push_back(1.20365703);
    scores.push_back(1.22123706);
    scores.push_back(1.22951099);
    scores.push_back(1.24014716);
    scores.push_back(1.23109052);
    scores.push_back(1.19345168);
    scores.push_back(1.23609924);
    scores.push_back(1.21636328);
    scores.push_back(1.21875672);
    scores.push_back(1.20676471);
    scores.push_back(1.22833378);
    scores.push_back(1.21125123);
    scores.push_back(1.25619617);
    scores.push_back(1.21093479);
    scores.push_back(1.22903107);
    scores.push_back(1.21785069);
    scores.push_back(1.2603395);
    scores.push_back(1.21243735);
    scores.push_back(1.21998974);
    scores.push_back(1.22251204);
    scores.push_back(1.21575657);
    scores.push_back(1.22471857);
    scores.push_back(1.25411506);
    scores.push_back(1.21614249);
    scores.push_back(1.20470443);
    scores.push_back(1.22647332);
    scores.push_back(1.22525328);
    scores.push_back(1.22691928);
    scores.push_back(1.21612568);
    scores.push_back(1.23449235);
    scores.push_back(1.23511853);
    scores.push_back(1.2300547);
    scores.push_back(1.21145251);
    scores.push_back(1.20698632);
    scores.push_back(1.23073077);
    scores.push_back(1.22754975);
    scores.push_back(1.24880083);
    scores.push_back(1.21758812);
    scores.push_back(1.23293472);
    scores.push_back(1.23491066);
    scores.push_back(1.2209861);
    scores.push_back(1.22624414);
    scores.push_back(1.22684678);
    scores.push_back(1.22974801);
    scores.push_back(1.21888663);
    scores.push_back(1.22240652);
    scores.push_back(1.23628154);
    scores.push_back(1.21776304);
    scores.push_back(1.21071465);
    scores.push_back(1.23864353);
    scores.push_back(1.23617567);
    scores.push_back(1.21412048);
    scores.push_back(1.22768679);
    scores.push_back(1.2159178);
    scores.push_back(1.22821296);
    scores.push_back(1.22361117);
    scores.push_back(1.22109566);
    scores.push_back(1.22363061);
    scores.push_back(1.21802644);
    scores.push_back(1.21849092);
    scores.push_back(1.23465524);
    scores.push_back(1.21512152);
    scores.push_back(1.20121499);
    scores.push_back(1.22833381);
    scores.push_back(1.21670787);
    scores.push_back(1.23417894);
    scores.push_back(1.21761625);
    scores.push_back(1.2265847);
    scores.push_back(1.22444736);
    scores.push_back(1.21549473);
    scores.push_back(1.24550117);
    scores.push_back(1.23711643);
    scores.push_back(1.21039298);
    scores.push_back(1.20379617);
    scores.push_back(1.22811546);
    scores.push_back(1.24517936);
    scores.push_back(1.20845599);
    scores.push_back(1.22644237);
    scores.push_back(1.22845685);
    scores.push_back(1.22094148);
    scores.push_back(1.2221472);
     
    //get feature_vectors
    int num_spuid = spuid_list.size();
    int vec_size = 8;
    vector<vector<double> >feature_vectors;
    for(int32_t i = 0; i < num_spuid ; i++){
        feature_vectors.push_back(spu_vec_map[spuid_list[i]]);
    }
     
    //get similarities
    //similarities = np.dot(feature_vectors, feature_vectors.T)
    double similarities[num_spuid][num_spuid];
    for(int m=0;m<num_spuid;m++){
        for(int s=0;s<num_spuid;s++){
            similarities[m][s]=0;//变量使用前记得初始化,否则结果具有不确定性
            for(int n=0;n<vec_size;n++){
                similarities[m][s]+=feature_vectors[m][n]*feature_vectors[s][n];
            }
        }
    }
     
    //get kernel_matrix
    vector<vector<double> > kernel_matrix; //double kernel_matrix[num_spuid][num_spuid];
    for(int m=0;m<num_spuid;m++){
        vector<double> cur;
        for(int s=0;s<num_spuid;s++){
            cur.push_back(similarities[m][s]*scores[m]*scores[s]); //kernel_matrix[m][s] = similarities[m][s]*scores[m]*scores[s];
        }
        kernel_matrix.push_back(cur);
    }
 
    // get cis
    double cis[max_length][num_spuid];//cis = np.zeros((max_length, item_size))
    for(int m=0;m<max_length;m++){
        for(int n=0;n<num_spuid;n++){
            cis[m][n] = 0;
        }
    }
     
    // get di2s
    std::vector<double> di2s; //di2s = np.copy(np.diag(kernel_matrix))
    for(int m=0;m<num_spuid;m++){
        di2s.push_back(kernel_matrix[m][m]);
    }
 
    // get selected_items
    std::vector<double> selected_items;
    int selected_item = argmax(di2s.begin(), di2s.end());
    selected_items.push_back(selected_item);
 
    double eis[num_spuid];//eis = (elements - np.dot(ci_optimal, cis[:k, :])) / di_optimal
    while( selected_items.size() < max_length){
        int k = selected_items.size()-1;
 
        //ci_optimal
        std::vector<double> ci_optimal; //ci_optimal = cis[:k, selected_item]
        for(int m=0;m<k;m++){
            ci_optimal.push_back(cis[m][selected_item]);
        }
         
        //di_optimal
        double di_optimal = sqrt(di2s[selected_item]);
         
        //elements
        std::vector<double> elements;
        for(int m=0;m<num_spuid;m++){
             elements.push_back(kernel_matrix[selected_item][m]);
        }
         
        //eis
        for(int m=0;m<num_spuid;m++){
            double rt = 0;
            for(int n=0;n<k;n++){
                rt = rt +  ci_optimal[n]*cis[n][m];
            }
            eis[m] = (elements[m] - rt)/di_optimal;
        }
         
        //update cis
        for(int n=0;n<num_spuid;n++){
            cis[k][n] = eis[n]; //cis[k, :] = eis
        }
        //update di2s    //di2s -= np.square(eis)
        for(int n=0;n<num_spuid;n++){
            di2s[n] -= eis[n]*eis[n];
        }
        // update selected_items
        selected_item = argmax(di2s.begin(), di2s.end());
        if (di2s[selected_item] < epsilon)
        {
            break;
        }
        selected_items.push_back(selected_item);
    }
     
    cout << '[';
    for(int m=0;m<selected_items.size();m++){
        cout << selected_items[m] << ", ";
    }
    cout <<  ']';
}