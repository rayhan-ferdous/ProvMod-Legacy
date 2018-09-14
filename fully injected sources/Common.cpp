#pragma hdrstop
#include "Common.h"
#include <math.hpp>
#include <algorithm>
#include <stdio.h>
#include <limits>
#pragma package(smart_init)
using namespace std;
double xLimit = numeric_limits<float>::max();
long lLimit = numeric_limits<long>::max();
void GroupEnding(string &AA, int Cnt)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidGroupEnding(string&AA,intCnt) @@@ Common.cpp_nocom>\n"); fclose(stdout);
    int alphas = Cnt/26;
    int letter = Cnt%26;
    if(!letter)  
    {
        letter = 26;
        alphas = 0;
    }
    AA = "@@";
    AA[1] += letter;
    if(alphas > 0)
    {
        string B = "@";
        B[0] += alphas;
        AA.insert(1, B);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidGroupEnding(string&AA,intCnt) @@@ Common.cpp_nocom>\n"); fclose(stdout);
}
void GroupEnding(String &AA, int Cnt)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidGroupEnding(String&AA,intCnt) @@@ Common.cpp_nocom>\n"); fclose(stdout);
    int alphas = Cnt/26;
    int letter = Cnt%26;
    if(!letter)  
    {
        letter = 26;
        alphas = 0;
    }
    AA = "@@";
    AA[2] += letter;
    if(alphas > 0)
    {
        String B = "@";
        B[1] += alphas;
        AA.Insert(B, 2);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidGroupEnding(String&AA,intCnt) @@@ Common.cpp_nocom>\n"); fclose(stdout);
}
float sqr(float X)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatsqr(floatX) @@@ Common.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</floatsqr(floatX) @@@ Common.cpp_nocom>\n"); fclose(stdout);return X * X;}
freopen("c:\\injection.log", "a", stdout); printf("</floatsqr(floatX) @@@ Common.cpp_nocom>\n"); fclose(stdout);
}
double estar(float t) /* Saturation vapour pressure kPa*/
{
freopen("c:\\injection.log", "a", stdout); printf("<doubleestar(floatt)/*SaturationvapourpressurekPa*/ @@@ Common.cpp_nocom>\n"); fclose(stdout);
    if (t > 0.0)
{freopen("c:\\injection.log", "a", stdout); printf("</doubleestar(floatt)/*SaturationvapourpressurekPa*/ @@@ Common.cpp_nocom>\n"); fclose(stdout);return 0.611 * exp(17.27*t / (t + 237.3));}
    else
{freopen("c:\\injection.log", "a", stdout); printf("</doubleestar(floatt)/*SaturationvapourpressurekPa*/ @@@ Common.cpp_nocom>\n"); fclose(stdout);return 0.611 * exp(21.88*t / (t + 265.5));}
freopen("c:\\injection.log", "a", stdout); printf("</doubleestar(floatt)/*SaturationvapourpressurekPa*/ @@@ Common.cpp_nocom>\n"); fclose(stdout);
}
float Qs(float P, float tc)   
{
freopen("c:\\injection.log", "a", stdout); printf("<floatQs(floatP,floattc) @@@ Common.cpp_nocom>\n"); fclose(stdout);
    float es; 
    if (tc >= 0)
        es = 0.611213*exp(17.5043*tc/(241.3+tc));
    else
        es = 0.611213*exp(22.4422*tc/(272.186+tc));
{freopen("c:\\injection.log", "a", stdout); printf("</floatQs(floatP,floattc) @@@ Common.cpp_nocom>\n"); fclose(stdout);return(0.622*es/P);}
freopen("c:\\injection.log", "a", stdout); printf("</floatQs(floatP,floattc) @@@ Common.cpp_nocom>\n"); fclose(stdout);
}
float Qswater(float P, float tc)   
{
freopen("c:\\injection.log", "a", stdout); printf("<floatQswater(floatP,floattc) @@@ Common.cpp_nocom>\n"); fclose(stdout);
    float es; 
    es = 0.611213*exp(17.5043*tc/(241.3+tc));
{freopen("c:\\injection.log", "a", stdout); printf("</floatQswater(floatP,floattc) @@@ Common.cpp_nocom>\n"); fclose(stdout);return(0.622*es/P);}
freopen("c:\\injection.log", "a", stdout); printf("</floatQswater(floatP,floattc) @@@ Common.cpp_nocom>\n"); fclose(stdout);
}
float DepthofSnow(float SWE)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatDepthofSnow(floatSWE) @@@ Common.cpp_nocom>\n"); fclose(stdout);
    /* 3/5/98
       Calculates Snow Depth(m) from SWE(mm) */
    float Snow_Depth;
    if (SWE > 2.05)
    {
        if(SWE <= 145.45) /* SWE 145.45 mm equivalent to 60 cm*/
            Snow_Depth = (SWE -2.05)/2.39;
        else
            Snow_Depth = (SWE +128.06)/4.5608;
    }
    else
        Snow_Depth = 0;
{freopen("c:\\injection.log", "a", stdout); printf("</floatDepthofSnow(floatSWE) @@@ Common.cpp_nocom>\n"); fclose(stdout);return Snow_Depth/100.0;}
} /* DepthofSnow*/
float K(float Ky, float LogStDev)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatK(floatKy,floatLogStDev) @@@ Common.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</floatK(floatKy,floatLogStDev) @@@ Common.cpp_nocom>\n"); fclose(stdout);return (exp(LogStDev*Ky-(sqr(LogStDev)/2))-1)/(sqrt(exp(sqr(LogStDev))-1));}
freopen("c:\\injection.log", "a", stdout); printf("</floatK(floatKy,floatLogStDev) @@@ Common.cpp_nocom>\n"); fclose(stdout);
}
const float a1          =   0.4361836;   
const float a2          =  -0.1201676;
const float a3          =   0.937298;
const float little_p    =   0.33267;
/*
const float a1          =   0.31938;     
const float a2          =  -0.35656;
const float a3          =   1.78147;
const float a4          =  -1.82125;
const float a5          =   1.33027;
const float little_p    =   0.23164; */
float KyValue(float probability, float guess)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatKyValue(floatprobability,floatguess) @@@ Common.cpp_nocom>\n"); fclose(stdout);
    float Ky, TempP, t;
    bool  done       = false;
    float direction  = -1;       
    float tolerance  = 0.0001;
    float dKy        = 0.1;      
    long  iterations = 0;
    Ky         = guess;        
    while (!done)
    {
        iterations++;
        t = 1 /(1+little_p * Ky);
        TempP = (exp(-Ky*Ky/2)/sqrt(2*M_PI)) * (a1*t + a2*t*t + a3*t*t*t);
        if (fabs(TempP - probability) <= tolerance)
            done = true;
        else
        {
            if (TempP > (probability+tolerance))
                if (direction == -1)
                {
                    dKy = dKy / 2;
                    direction = 1;
                }
                else
                {
                    dKy = dKy / 2;
                    direction = -1;
                }
            Ky = Ky + dKy * direction;
        }
    } 
{freopen("c:\\injection.log", "a", stdout); printf("</floatKyValue(floatprobability,floatguess) @@@ Common.cpp_nocom>\n"); fclose(stdout);return Ky;}
freopen("c:\\injection.log", "a", stdout); printf("</floatKyValue(floatprobability,floatguess) @@@ Common.cpp_nocom>\n"); fclose(stdout);
}
float SWE_prob(float SWEmean, float SWE, float CV)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatSWE_prob(floatSWEmean,floatSWE,floatCV) @@@ Common.cpp_nocom>\n"); fclose(stdout);
    if(SWE <= 0.01)
{freopen("c:\\injection.log", "a", stdout); printf("</floatSWE_prob(floatSWEmean,floatSWE,floatCV) @@@ Common.cpp_nocom>\n"); fclose(stdout);return 0.0;}
    if(SWE >= SWEmean)
{freopen("c:\\injection.log", "a", stdout); printf("</floatSWE_prob(floatSWEmean,floatSWE,floatCV) @@@ Common.cpp_nocom>\n"); fclose(stdout);return 1.0;}
    float K = -SWE/(SWEmean*CV);
    float Sy = sqrt(log(1.0 + CV*CV));
    float Ky = log(1.0 + K*CV)/Sy + Sy/2.0;
    float t = 1 /(1+little_p * Ky);
    float P = (exp(-Ky*Ky/2)/sqrt(2*M_PI)) * (a1*t + a2*t*t + a3*t*t*t);
    if(P > 1.0 || P < 0.001) 
        P = 1.0;
{freopen("c:\\injection.log", "a", stdout); printf("</floatSWE_prob(floatSWEmean,floatSWE,floatCV) @@@ Common.cpp_nocom>\n"); fclose(stdout);return P;}
freopen("c:\\injection.log", "a", stdout); printf("</floatSWE_prob(floatSWEmean,floatSWE,floatCV) @@@ Common.cpp_nocom>\n"); fclose(stdout);
}
snowcover::snowcover(float SWEmean, float cv)
{
freopen("c:\\injection.log", "a", stdout); printf("<snowcover::snowcover(floatSWEmean,floatcv) @@@ Common.cpp_nocom>\n"); fclose(stdout);
    float x, sca;
    const long N = 150;
    data = new float[N];
    for(int ii = 0; ii < N; ii++)
    {
        x = SWEmean*2.0*(ii+1)/N;
        float K = (x - SWEmean)/(SWEmean*cv);
        float Sy = sqrt(log(cv*cv+1.0));
        float Ky = (log(K*sqrt(exp(Sy*Sy)-1.0)+1.0) + Sy*Sy/2.0)/Sy;
        float t = 1 /(1+little_p * Ky);
        float P = (exp(-Ky*Ky/2)/sqrt(2*M_PI)) * (a1*t + a2*pow(t,2) + a3*pow(t,3));
        data[ii] = P;
    }
freopen("c:\\injection.log", "a", stdout); printf("</snowcover::snowcover(floatSWEmean,floatcv) @@@ Common.cpp_nocom>\n"); fclose(stdout);
}
snowcover::~snowcover()
{
freopen("c:\\injection.log", "a", stdout); printf("<snowcover::~snowcover() @@@ Common.cpp_nocom>\n"); fclose(stdout);
    delete[] data;
freopen("c:\\injection.log", "a", stdout); printf("</snowcover::~snowcover() @@@ Common.cpp_nocom>\n"); fclose(stdout);
}
float snowcover::lookup(float melt)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatsnowcover::lookup(floatmelt) @@@ Common.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</floatsnowcover::lookup(floatmelt) @@@ Common.cpp_nocom>\n"); fclose(stdout);return 0;}
freopen("c:\\injection.log", "a", stdout); printf("</floatsnowcover::lookup(floatmelt) @@@ Common.cpp_nocom>\n"); fclose(stdout);
}
bool EqualUpper(string s1, string s2)
{
freopen("c:\\injection.log", "a", stdout); printf("<boolEqualUpper(strings1,strings2) @@@ Common.cpp_nocom>\n"); fclose(stdout);
    transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
{freopen("c:\\injection.log", "a", stdout); printf("</boolEqualUpper(strings1,strings2) @@@ Common.cpp_nocom>\n"); fclose(stdout);return (bool) (s1 == s2);}
freopen("c:\\injection.log", "a", stdout); printf("</boolEqualUpper(strings1,strings2) @@@ Common.cpp_nocom>\n"); fclose(stdout);
}
float SVDens(float Temp) /* outputs sat. vapor density, kg/m^3 */
{
freopen("c:\\injection.log", "a", stdout); printf("<floatSVDens(floatTemp)/*outputssat.vapordensity,kg/m^3*/ @@@ Common.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</floatSVDens(floatTemp)/*outputssat.vapordensity,kg/m^3*/ @@@ Common.cpp_nocom>\n"); fclose(stdout);return 1.324*exp(22.452*Temp/(Temp+273.15))/(Temp+273.15);}
freopen("c:\\injection.log", "a", stdout); printf("</floatSVDens(floatTemp)/*outputssat.vapordensity,kg/m^3*/ @@@ Common.cpp_nocom>\n"); fclose(stdout);
}
float Ice_Bulb(float Tc, float RH, float Pa) 
{
freopen("c:\\injection.log", "a", stdout); printf("<floatIce_Bulb(floatTc,floatRH,floatPa) @@@ Common.cpp_nocom>\n"); fclose(stdout);
    float Tk = Tc + CRHM_constants::Tm;
    float D = 0.0000206*pow(Tk/CRHM_constants::Tm, 1.75);
    float RHO = Pa*1000.0/(CRHM_constants::Rgas*Tk);
    float qt = CRHM_constants::em/(Pa*1000.0)*611.213*exp(22.4422*Tc/(CRHM_constants::Tm + Tc));
    float lamda = 0.000076843*Tk + 0.003130762;
    float L;
    if(Tc > 0.0)
        L = CRHM_constants::Lv;
    else
        L = CRHM_constants::Ls;
    float delta = CRHM_constants::em*L*qt/(CRHM_constants::Rgas*sqr(Tk));
{freopen("c:\\injection.log", "a", stdout); printf("</floatIce_Bulb(floatTc,floatRH,floatPa) @@@ Common.cpp_nocom>\n"); fclose(stdout);return Tc - L*(1.0 - RH/100.0)*qt/(CRHM_constants::Cp + L*delta) *(RHO*CRHM_constants::Cp*D/lamda);}
freopen("c:\\injection.log", "a", stdout); printf("</floatIce_Bulb(floatTc,floatRH,floatPa) @@@ Common.cpp_nocom>\n"); fclose(stdout);
}
