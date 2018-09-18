// 10/10/12
//---------------------------------------------------------------------------

#include "Common.h"
#include <time.h>
#include <math.h>
#include <algorithm>
#include <string>
#include <limits>
#include <unistd.h>
#include "GlobalDll.h"
#include <windef.h>

using namespace std;

long Decade_Offsets[][4] = { // Year, abs(value), calc wrt to this year, offset.
  {80, -3652,  29219,     2}, // 1900 moved to 1980
  {60,  3654,  21915,  3654}, // 1910 moved to 1970
  {60,  3654,  21915,  7306}, // 1920 moved to 1980
  {40,  10959, 14610, 10959}, // 1930 moved to 1970
  {40,  10959, 14610, 14611}, // 1940 moved to 1980
  {20,  18264,  7305, 18264}, // 1950 moved to 1970
  {20,  18264,  7305, 21916}, // 1960 moved to 1980
  { 0,  25569,     0, 25569}, // 1970 not moved
  { 0,  29221,     0}, // 1980 (not used)
};

double xLimit = numeric_limits<float>::max();
long lLimit = numeric_limits<long>::max();

double Calculate_TdateTime_Offset(void){

tm timeinfo;

    timeinfo.tm_sec = 0;
    timeinfo.tm_min = 0;
    timeinfo.tm_hour = 0;
    timeinfo.tm_mday = 1;
    timeinfo.tm_mon = 0;
    timeinfo.tm_year = 70;

    time_t Current = mktime(&timeinfo); // determine ???

    return double(Current)/86400.0;
}

long julian(int Year, int Month, int Day, int hour, int min){

    tm timeinfo;

    long indx = (Year - 1900)/10;
    if(indx > 7)indx = 7;

    timeinfo.tm_sec = 0;
    timeinfo.tm_min = min;
    timeinfo.tm_hour = hour;
    timeinfo.tm_mday = Day;
    timeinfo.tm_mon = Month- 1;
    timeinfo.tm_year = Year + Decade_Offsets[indx][0] - 1900;

    time_t Current = mktime(&timeinfo); // updates timeinfo

    return timeinfo.tm_yday + 1; //
}

long julian(double Dttime){

  long indx = 7;
  if(Dttime < 25569)
    for(indx = 6; indx >= 0; --indx){
      if(!(Dttime < Decade_Offsets[indx][3]))
         break;
    }

  long Fix = (Dttime - Decade_Offsets[indx][1])*86400.0;
  time_t rawtime = (time_t) Fix;

  tm *timeinfo = gmtime(&rawtime);

  return timeinfo->tm_yday + 1; //
}

double EncodeDateTime(int Year, int Month, int Day, int hour, int min){

    tm timeinfo;

    long indx = (Year - 1900)/10;
    if(indx > 7)indx = 7;

    timeinfo.tm_sec = 0;
    timeinfo.tm_min = min;
    timeinfo.tm_hour = hour;
    timeinfo.tm_mday = Day;
    timeinfo.tm_mon = Month - 1;

    timeinfo.tm_isdst = 0;

    timeinfo.tm_year = Year + Decade_Offsets[indx][0] - 1900;

    time_t Current = mktime(&timeinfo);

    return double(Current)/86400.0 + Decade_Offsets[indx][1] - Global::TdateTime_Offset; // correction from
}

void DecodeDateTime(double Dttime, int &Year, int &Month, int &Day, int &Hour, int &Min){

  long indx = 7;
  if(Dttime < 25569)
    for(indx = 6; indx >= 0; --indx){
      if(!(Dttime < Decade_Offsets[indx][3]))
         break;
    }

  long Fix = (Dttime - Decade_Offsets[indx][1])*86400.0;
  time_t rawtime = (time_t) Fix;

  tm *timeinfo = gmtime(&rawtime);

  Year =  timeinfo->tm_year - Decade_Offsets[indx][0] + 1900;
  Month = timeinfo->tm_mon + 1;
  Day =   timeinfo->tm_mday;
  Hour =  timeinfo->tm_hour;
  Min =   timeinfo->tm_min;
}

double DateTimeDt(void){
  time_t Currently;

  time(&Currently);

  return double(Currently)/86400.0 + Decade_Offsets[7][1] - Global::TdateTime_Offset; //  TdateTime_Offset less local time offset
}

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

//---------------------------------------------------------------------------
// float sqr(float X){ return X * X;}

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

/*---------------------------------------------------------------------------
float DepthofSnow(float SWE)
{
// 3/5/98   Calculates Snow Depth(m) from SWE(mm)
  float Snow_Depth;

  if (SWE > 2.05) {
    if(SWE <= 145.45) // SWE 145.45 mm equivalent to 60 cm
      Snow_Depth = (SWE -2.05)/2.39;
    else
      Snow_Depth = (SWE +128.06)/4.5608;
  }
  else
    Snow_Depth = 0;

  return Snow_Depth/100.0;
} // DepthofSnow
*/
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

string trim(string& str){

  trimleft(str);
  trimright(str);

  return str;
}

string trimleft(string& str) {

  string::size_type pos = str.find_first_not_of(" \t");

  if(pos != string::npos)
    if(pos > 0)
    str.erase(0, pos);

  return str;
}

string trimright(string& str) //
{
  if(!str.empty()){

    string::size_type pos = str.find_last_not_of(" \t");

    if(pos != string::npos)
      if(pos < str.length()-1)
        str.erase(++pos);
  }

  return str;
}

string ExtractFileExt(string s){
  string::size_type Idx = s.rfind(".");
  if(Idx != string::npos)
    return s.substr(Idx);
  else
    return "";
}

string FloatToStrF(float X, TFloatFormat Format, int Prec, int Digits){
  ostringstream temp;
  if(Format == ffFixed){
    temp.precision(Prec);
    temp.width(Digits);
    temp << X;
  }
  else{ // assume ffGeneral
    temp.precision(Prec);
    temp.width(Digits);
    temp << X;
  }
    return temp.str();
}

string FloatToStrF(double X, TFloatFormat Format, int Prec, int Digits){
  ostringstream temp;
  if(Format == ffFixed){
    temp.precision(Prec);
    temp.width(Digits);
    temp << X;
  }
  else{ // assume ffGeneral
    temp.precision(Prec);
    temp.width(Digits);
    temp << X;
  }
    return temp.str();
}

string FloatToStrF(long L, TFloatFormat Format, int Prec, int Digits){
  ostringstream temp;
  if(Format == ffFixed){
    temp.precision(Prec);
    temp.width(Digits);
    temp << L;
  }
  else{ // assume ffGeneral
    temp.precision(Prec);
    temp.width(Digits);
    temp << L;
  }
    return temp.str();
}

string FormatString(double DT, string){
  ostringstream temp;
  temp.width(2);
  int Y, M, D, H, Min;

  DecodeDateTime(DT, Y, M, D, H, Min);
  temp << Y << " " << M << " " << D;

  return temp.str();
};

string FormatDateTime(string s1, double DT){
  ostringstream temp;
  temp.width(2);
  int Y, M, D, H, Min;

  DecodeDateTime(DT, Y, M, D, H, Min);
  temp << Y << " " << M << " " << D << H << " " << Min;

  return temp.str();
};

double StrToDate(string date){
  int Month = Strtolong(date.substr(0, 2));
  int Day = Strtolong(date.substr(3, 2));
  int Year = Strtolong(date.substr(6, 4));

  return EncodeDateTime(Year, Month, Day, 0, 0);
}

double StrToTime(string time){

  int hour = Strtolong(time.substr(0, 2));
  int min = Strtolong(time.substr(3, 2));

  return EncodeDateTime(0, 0, 1, hour, min);
}

string lowercase(string &s){

  transform(s.begin(), s.end(), s.begin(), (int(*)(int)) tolower);
  return s;
}

string::size_type LastDelimiter(string s1, string s2){
  return s1.find_last_of(s2);                              ;
}

string inttoStr(int I){
  ostringstream temp;
  temp << I;
  return temp.str();
}

string DttoStr(double D){
  ostringstream temp;
  temp << D;
  return temp.str();
}

string longtoStr(long L){
  ostringstream temp;
  temp << L;
  return temp.str();
}

long Strtolong(string s){

  istringstream instr;
  instr.str(s);

  long I;
  instr >> I;
  return I;
}

double StrtoDt(string s){

  istringstream instr;
  instr.str(s);

  double D;
  instr >> D;
  return D;
}

int Strtoint(char *ch){
  ifstream S(ch);
  int I;
  S >> I;
  return I;
}

bool IsDelimiter(string s1){

  return s1.find_first_of("/") != string::npos;
}

void Message(const char *s1, const char *s2){

  cout << s1 << ", " << s2 << endl;
}

void Message(const string s1, const string s2){

  cout << s1 << ", " << s2 << endl;
}

  string TStringList::CommaText(void){
    ostringstream temp;

    for(unsigned int ii = 0; ii < array.size(); ++ii){
      if(ii)
         temp << ", ";
      temp << array.at(ii).get_Name();
    }
    temp << endl;
    return temp.str();

  }

  void TStringList::DelimitedText(string s){

    string in_quote;
    bool quoted = FALSE;
    long pos, here, last_quote, done_to = 0;
    Clear();
    trim(s);
    if(s.size() == 0)
      return;

    s.append(",");
    for(pos = 0; pos < s.size(); ++pos){
      here = s.find_first_of("' ,", pos);
      pos = here;
      switch(s[here]){
        case '\'':
          quoted = TRUE;
          last_quote = s.find('\'', ++pos);
          if(last_quote  > here+1) // not empty
            in_quote = s.substr(here+1, last_quote-here-1);
          else
            return;
          pos = last_quote;
          break;
        case ',':
        case ' ':
          if(quoted)
            Add(in_quote);
          else{
            if( pos > done_to )
              Add(s.substr(done_to, pos-done_to));
            else
              return;
          }

          done_to = s.find_first_not_of(" ", here+1);

          if(done_to > -1)
             pos = done_to - 1;
          else
             pos = here;

          in_quote = "";
          quoted = FALSE;
      } // switch
    } // for
  }

  void TStringList::CommaText(string s){ //used to read "AnnandaleX, calcsunX, calcsun_QsiD, ...
    string in_quote;
    string::size_type pos, here, last_quote, done_to = 0;
    array.clear();
    trim(s);
    s.append(",");
    for(pos = 0; pos < s.size(); ++pos){
      here = s.find_first_of("' ,", pos);
      switch(s[here]){
        case '\'':
          last_quote = s.find("'", pos);
          in_quote = s.substr(here+1, last_quote-1);
          pos = last_quote+1;
          break;
        case ',':
        case ' ':
          in_quote.append(s.substr(done_to, here-done_to));
          Add(in_quote);
          done_to = s.find_first_not_of(" ", here+1);

          if(done_to == string::npos)
            pos = s.size();
          else{
            pos = done_to;
            in_quote = "";
          }
      } // switch
    } // for
  }

  void TStringList::SaveToFile(string FileName){
    ofstream file;
    file.open(FileName.c_str());

    for(unsigned int ii = 0; ii < array.size(); ++ii)
      file << array.at(ii).get_Name() << endl;

    file.close();
  };

string &TStringList::operator[](int ii) {
  return array[ii].Name;
  }

void TStringList::AddObject(string s, TObject* thing){

  array.push_back(StringandObject(s, thing));
  Count = array.size();
}

int TStringList::IndexOf(string s){

  for(unsigned int ii = 0; ii < array.size(); ++ii)
    if(array.at(ii).get_Name() == s)
      return ii;

  return -1;
}

void TStringList::Add(string s){

  array.push_back(StringandObject(s, 0));
  Count = array.size();
}

void TStringList::Clear(){
  array.clear();
  Count = 0;
}

void TStringList::Assign(TStringList *Src){
  Clear();
  for(unsigned int ii = 0; ii < Src->array.size(); ++ii)
    AddObject(Src->array.at(ii).get_Name(), Src->array[ii].Object);
}

void TStringList::Delete(int Index){
  vector<StringandObject>::iterator pos;
  int cnt = -1;
    for(pos = array.begin(); pos < array.end(); ++pos)
      if(Index == ++cnt){
        array.erase(pos);
        Count = array.size();
        return;
      }
  ;
}

string &TStrings::operator[](int ii) {
  return StringList->array[ii].Name;
}

TObject* &TObjects::operator[](int ii) {
  return StringList->array[ii].Object;
}

  TStringList::TStringList(const TStringList &p){ // copy constructor

    Sorted = p.Sorted;
    CaseSensitive = p.CaseSensitive;

    array.reserve(64);
    Strings.Init(this);
    Objects.Init(this);
    Count = 0;
  }

TStringList & TStringList::operator=(const TStringList & p) {

  if (this == &p) return *this;

}

string GetCurrentPath(void){

  char buffer[_MAX_PATH];

  getcwd(buffer, _MAX_PATH);

  return buffer;
}
