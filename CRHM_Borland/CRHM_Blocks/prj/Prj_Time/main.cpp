// 082812
#include <iostream>
#include <time.h>


double TdateTime_Offset;

double EncodeDateTime(int Year, int Month, int Day, int hour, int min);
long julian(int Year, int Month, int Day, int hour, int min);
long julian(double rawtime);

void DecodeDateTime(double rawtime, int &Year, int &Month, int &Day, int &hour, int &min);
double Calculate_TdateTime_Offset(void);



double Calculate_TdateTime_Offset(void){

tm timeinfo;

    timeinfo.tm_sec = 0;
    timeinfo.tm_min = 0;
    timeinfo.tm_hour = 0;
    timeinfo.tm_mday = 1;
    timeinfo.tm_mon = 0;
    timeinfo.tm_year = 70;

    time_t Current = mktime(&timeinfo); // determine ???

    return (25569.0 - double(Current)/86400.0);
}

long julian(int Year, int Month, int Day, int hour, int min){

tm timeinfo;

    timeinfo.tm_sec = 0;
    timeinfo.tm_min = min;
    timeinfo.tm_hour = hour;
    timeinfo.tm_mday = Day;
    timeinfo.tm_mon = Month - 1;
    timeinfo.tm_year = Year - 1900;

    time_t Current = mktime(&timeinfo); // updates timeinfo

    return timeinfo.tm_yday + 1; //
}

double EncodeDateTime(int Year, int Month, int Day, int hour, int min){

tm timeinfo;

    timeinfo.tm_sec = 0;
    timeinfo.tm_min = min;
    timeinfo.tm_hour = hour;
    timeinfo.tm_mday = Day;
    timeinfo.tm_mon = Month - 1;
    timeinfo.tm_year = Year - 1900;

    time_t Current = mktime(&timeinfo);

    return double(Current)/86400.0 + TdateTime_Offset; // correction from
}

void DecodeDateTime(double Dttime, int &Year, int &Month, int &Day, int &Hour, int &Min){

  long Fix = (Dttime - TdateTime_Offset)*86400.0;
  time_t rawtime = (time_t) Fix;

  tm *timeinfo = gmtime(&rawtime);

  Year =  timeinfo->tm_year + 1900;
  Month = timeinfo->tm_mon + 1;
  Day =   timeinfo->tm_mday;
  Hour =  timeinfo->tm_hour;
  Min =   timeinfo->tm_min;
}
long julian(double Dttime){

  long Fix = (Dttime - TdateTime_Offset)*86400.0;
  time_t rawtime = (time_t) Fix;

  tm *timeinfo = gmtime(&rawtime);

//  time_t Current = mktime(timeinfo); // updates timeinfo

  return timeinfo->tm_yday + 1; //
}

double DateTimeDt(void){
  time_t Currently;

  time(&Currently);

  return double(Currently)/86400.0 + 25569.0; //  TdateTime_Offset less local time offset

}

using namespace std;

int main()
{
  double Dttime = 0;
  time_t Currently;


  TdateTime_Offset = Calculate_TdateTime_Offset();

  int Year = 2012, Month = 8, Day = 27, Hour = 0, Min = 0;

    Dttime = EncodeDateTime(Year, Month, Day, Hour, Min);

    long Julian = julian(Year, Month, Day, Hour, Min);

    long Julian2 = julian(Dttime);

    cout << "Julian dates " << Julian << ", " << Julian2 << endl;

    cout << Year << ", " << Month << ", " << Day << ", " << Hour << ", " << Min << endl;

    DecodeDateTime(Dttime, Year, Month, Day, Hour, Min);

    cout << Year << ", " << Month << ", " << Day << ", " << Hour << ", " << Min << endl;

    time(&Currently);

    Dttime = double(Currently)/86400.0 + 25569.0; //  TdateTime_Offset less local time offset

    DecodeDateTime(Dttime, Year, Month, Day, Hour, Min);

    cout << Year << ", " << Month << ", " << Day << ", " << Hour << ", " << Min << endl;

    Dttime = DateTimeDt(); //  TdateTime_Offset less local time offset

    DecodeDateTime(Dttime, Year, Month, Day, Hour, Min);

    cout << Year << ", " << Month << ", " << Day << ", " << Hour << ", " << Min << endl;

    return 0;
}
