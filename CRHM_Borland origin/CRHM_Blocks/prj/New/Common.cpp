// 01/20/12
//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include <math>
#include <algorithm>
#include <limits>

//---------------------------------------------------------------------------

#pragma package(smart_init)

using namespace std;

double xLimit = numeric_limits<float>::max();
long lLimit = numeric_limits<long>::max();

void GroupEnding(string &AA, int Cnt){
  int alphas = Cnt/26;
  int letter = Cnt%26;
  if(!letter){ // 26th letter is 'Z' not "@@"
    letter = 26;
    alphas = 0;
  }
  AA = "@@";
  AA[1] += letter;
  if(alphas > 0){
    string B = "@";
    B[0] += alphas;
    AA.insert(1, B);
  }
}

void GroupEnding(String &AA, int Cnt){
  int alphas = Cnt/26;
  int letter = Cnt%26;
  if(!letter){ // 26th letter is 'Z' not "@@"
    letter = 26;
    alphas = 0;
  }
  AA = "@@";
  AA[2] += letter;
  if(alphas > 0){
    String B = "@";
    B[1] += alphas;
    AA.Insert(B, 2);
  }
}

//---------------------------------------------------------------------------
float sqr(float X){ return X * X;}

//---------------------------------------------------------------------------
double estar(float t) /* Saturation vapour pressure kPa*/
{
  if (t > 0.0)
     return 0.611 * exp(17.27*t / (t + 237.3));
  else
     return 0.611 * exp(21.88*t / (t + 265.5));
}

// Saturation humidity (kg/kg) Over ice and water
float Qs(float P, float tc) { // P (KPa)

  float es; // Vapour pressure (Pa)

  if (tc >= 0)
    es = 0.611213*exp(17.5043*tc/(241.3+tc));
  else
    es = 0.611213*exp(22.4422*tc/(272.186+tc));

  return(0.622*es/P);
}

// Saturation humidity (kg/kg) Over water
float Qswater(float P, float tc) { // P (KPa)

  float es; // Vapour pressure (KPa)

  es = 0.611213*exp(17.5043*tc/(241.3+tc));

  return(0.622*es/P);
}

//---------------------------------------------------------------------------
float DepthofSnow(float SWE)
{
/* 3/5/98
   Calculates Snow Depth(m) from SWE(mm) */
  float Snow_Depth;

  if (SWE > 2.05) {
    if(SWE <= 145.45) /* SWE 145.45 mm equivalent to 60 cm*/
      Snow_Depth = (SWE -2.05)/2.39;
    else
      Snow_Depth = (SWE +128.06)/4.5608;
  }
  else
    Snow_Depth = 0;

  return Snow_Depth/100.0;
} /* DepthofSnow*/

//---------------------------------------------------------------------------
float K(float Ky, float LogStDev) {

  return (exp(LogStDev*Ky-(sqr(LogStDev)/2))-1)/(sqrt(exp(sqr(LogStDev))-1));
}

const float a1          =   0.4361836;   //constants of approximation
const float a2          =  -0.1201676;
const float a3          =   0.937298;
const float little_p    =   0.33267;

/*
const float a1          =   0.31938;     //constants of approximation
const float a2          =  -0.35656;
const float a3          =   1.78147;
const float a4          =  -1.82125;
const float a5          =   1.33027;
const float little_p    =   0.23164; */

//---------------------------------------------------------------------------
float KyValue(float probability, float guess) {
// finds location of probability, using polynomial approx to normal dist
//   from "Handbook of Mathematical Functions" by Abramowitz and Stegun}

float Ky, TempP, t;
bool  done       = false;
float direction  = -1;       // increasing
float tolerance  = 0.0001;
float dKy        = 0.1;      // increment
long  iterations = 0;

  Ky         = guess;        // start value

  while (!done) {
     iterations++;
     t = 1 /(1+little_p * Ky);
     TempP = (exp(-Ky*Ky/2)/sqrt(2*M_PI)) * (a1*t + a2*t*t + a3*t*t*t);

     if (fabs(TempP - probability) <= tolerance)
       done = true;
     else  {
       if (TempP > (probability+tolerance))
         if (direction == -1) {
           dKy = dKy / 2;
           direction = 1;
         }
         else {
           dKy = dKy / 2;
           direction = -1;
         }

         Ky = Ky + dKy * direction;
       }
  } // while

  return Ky;
}

//---------------------------------------------------------------------------
float SWE_prob(float SWEmean, float SWE, float CV) {

  if(SWE <= 0.01) return 0.0; // handle log(0) error
  if(SWE >= SWEmean) return 1.0; // 

  float K = -SWE/(SWEmean*CV);

  float Sy = sqrt(log(1.0 + CV*CV));

  float Ky = log(1.0 + K*CV)/Sy + Sy/2.0;

  float t = 1 /(1+little_p * Ky);

  float P = (exp(-Ky*Ky/2)/sqrt(2*M_PI)) * (a1*t + a2*t*t + a3*t*t*t);

  if(P > 1.0 || P < 0.001) // handle discontinuity
    P = 1.0;

  return P;
}

//---------------------------------------------------------------------------
snowcover::snowcover(float SWEmean, float cv){

float x, sca;

  const long N = 150;
  data = new float[N];
  
  for(int ii = 0; ii < N; ii++) {
    x = SWEmean*2.0*(ii+1)/N;
    float K = (x - SWEmean)/(SWEmean*cv);

    float Sy = sqrt(log(cv*cv+1.0));

    float Ky = (log(K*sqrt(exp(Sy*Sy)-1.0)+1.0) + Sy*Sy/2.0)/Sy;
    
    float t = 1 /(1+little_p * Ky);

    float P = (exp(-Ky*Ky/2)/sqrt(2*M_PI)) * (a1*t + a2*pow(t,2) + a3*pow(t,3));

    data[ii] = P;
  }
}

//---------------------------------------------------------------------------
snowcover::~snowcover() {
  delete[] data;
}

//---------------------------------------------------------------------------
float snowcover::lookup(float melt) {
  return 0;
}

//---------------------------------------------------------------------------
bool EqualUpper(string s1, string s2) {
  transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
  transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
  return (bool) (s1 == s2);
}

//---------------------------------------------------------------------------
float SVDens(float Temp) /* outputs sat. vapor density, kg/m^3 */
    {return 1.324*exp(22.452*Temp/(Temp+273.15))/(Temp+273.15);
}

//---------------------------------------------------------------------------
float Ice_Bulb(float Tc, float RH, float Pa) // returns ice bulb temperature, Pa (kPa), RH(%).
{
    float Tk = Tc + CRHM_constants::Tm;

    float D = 0.0000206*pow(Tk/CRHM_constants::Tm, 1.75);

    float RHO = Pa*1000.0/(CRHM_constants::Rgas*Tk);

    float qt = CRHM_constants::em/(Pa*1000.0)*611.213*exp(22.4422*Tc/(CRHM_constants::Tm + Tc));

    float lamda = 0.000063*Tk + 0.00673;

    float L;
    if(Tc > 0.0)
      L = CRHM_constants::Lv;
    else
      L = CRHM_constants::Ls;

    float delta = CRHM_constants::em*L*qt/(CRHM_constants::Rgas*sqr(Tk));

    return Tc - L*(1.0 - RH/100.0)*qt/(CRHM_constants::Cp + L*delta) *(RHO*CRHM_constants::Cp*D/lamda);
}
