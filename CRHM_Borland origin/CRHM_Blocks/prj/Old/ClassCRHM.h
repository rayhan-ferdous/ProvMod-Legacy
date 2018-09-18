// 06/28/12
//---------------------------------------------------------------------------
#ifndef ClassCRHMH
#define ClassCRHMH
//---------------------------------------------------------------------------

using namespace std;

#include "Common.h"
#include "GlobalCommon.h"
#include <string>
#include <iostream>
#include <map>
#include <typeinfo>

enum types { DELIMITER = 1, NUMBER};

class Classmacro;
class parser;
class ClassModule;

  class __declspec(dllexport) ClassData {
    public:
    string DataFileName;
    string Description;
    float **Data;
    double *Times; // holds sparse times
    double Dt1;
    double Dt2;
    double Interval; // days
    long Lines;
    long Freq;
    long IndxMin;   // range of data available
    long IndxMax;   // range of data available
    long ModN;      // divisor for data less frequent than basic interval
    long HdrLen;    // length of file header
    long Position;  // current line in file
    long DataCnt;
    long FilterCnt;  // filter count

    Classmacro *myMacro;
    bool Simulation;
    long ForceInterval;
    bool GoodInterval;
    bool GoodDay;
    bool RunUsed;
    bool Success;
    long TimeIndx; // sparse file ??
    bool FirstFile;
    float TimeShiftFilter; // used by Time shift filter

    ClassData(string DataFileName) : DataFileName(DataFileName), Data(NULL), myMacro(NULL),
                                       DataCnt(0), FilterCnt(0), Simulation(false), FirstFile(false),
                                       ForceInterval(0), ModN(0), Times(NULL), TimeShiftFilter(0.0) {
      Success = DataReadFile();
    }

    ClassData() : DataFileName(""), Data(NULL), myMacro(NULL),
                                       DataCnt(0), FilterCnt(0), Simulation(false),  FirstFile(false),
                                       ForceInterval(0), ModN(0), Times(NULL), TimeShiftFilter(0.0) {};

    bool DataReadFile(void);
    long Veto_Freq(long Freq);
    virtual __fastcall ~ClassData();
    double ClassData::Encode24(int D[]);
};

class __declspec(dllexport) ClassVar {

    typedef void (ClassVar:: *SomeFunct) (void);
    typedef void (ClassVar:: *AccFunct) (ClassModule *);

    public:

    string module;
    string root;
    string name;
    string help;
    string units;
    string DLLName; // use to differentiate DLLs and Macros from normal modules, i.e. CRHM

    CRHM::TVar varType;
    
    long dim;
    long dimMax; // used by observations
    long lay;
    long query;
    long variation_set;
    CRHM::TDim dimen;

    CRHM::TVISIBLE visibility;
    bool optional;
    bool PointPlot;
    long TchrtOpt;
    long Tag;
    bool StatVar;
    long InGroup;
    bool nfreq;
    CRHM::TFun FunKind;

    float * values;
    long  * ivalues;

    float ** layvalues;
    long **ilayvalues;

    long offset; // observation offset in ClassData FileData/Data
    long cnt;    // observation dimension

    ClassData  *FileData;

    long HRU_OBS_indexed; // used to access the HRU_OBS[HRU_OBS_indexed][HRU] table
    ClassVar *FunctVar;
    SomeFunct UserFunct;  // typedef void (ClassVar:: *SomeFunct) (void)
    AccFunct CustomFunct; // typedef void (ClassVar:: *AccFunct) (ClassModule *)

    ClassVar(string module = "none", string name = "none")
			 : module(module), name(name), help(""), DLLName(""), root(""), varType(CRHM::none), dim(0), dimMax(0), lay(0), variation_set(0), nfreq(false), query(0),
               optional(false), StatVar(false), InGroup(0), visibility(CRHM::USUAL), FunKind(CRHM::FOBS),
               values(NULL), ivalues(NULL), layvalues(NULL), ilayvalues(NULL),
               offset(0), cnt(0), FileData(NULL), HRU_OBS_indexed(0), UserFunct(NULL), FunctVar(NULL), CustomFunct(NULL), PointPlot(false), TchrtOpt(0) {};

    ClassVar(string module, string name, CRHM::TDim dimen,
			   string help, string units, CRHM::TVar varType, bool PointPlot = false, int Grpdim = 0, int defdim = 0);

    ClassVar(string module, string name, long dim,
			   string help, string units, CRHM::TVar varType, bool PointPlot = false);

    ClassVar(string module, string name, long cnt, long offset, ClassData * FileData)
			 : module(module), name(name), help(""), DLLName(""), root(""), varType(CRHM::Read), dim(cnt), dimMax(0), lay(0), variation_set(0), nfreq(false),
               optional(false), StatVar(false), InGroup(0), visibility(CRHM::USUAL), FunKind(CRHM::FOBS),
               offset(offset), cnt(cnt), FileData(FileData), HRU_OBS_indexed(0), UserFunct(NULL), FunctVar(NULL), CustomFunct(NULL), dimen(CRHM::NOBS),
               values(NULL), ivalues(NULL), layvalues(NULL), ilayvalues(NULL), PointPlot(false), TchrtOpt(0) {};

    virtual __fastcall ~ClassVar(){ReleaseM();} // releases everything

    ClassVar(const ClassVar & Cl);
    ClassVar & operator=(const ClassVar & Cl);

    float &operator[](int ii) {return values[ii];}

    virtual void ReleaseM(bool Keep = false);

    virtual void ReadVar(void);

    virtual void WriteVar(void);

    virtual string UserName(void){return module + ' ' + name;};

    virtual void Avg(void);

    virtual void Min(void);

    virtual void Max(void);

    virtual void Dtot(void);

    virtual void Tot(void);

    virtual void Tot_Ints(void);

    virtual void First(void);

    virtual void Last(void);

    virtual void Pos(void);

    virtual void Intvl(void);

    virtual void do_t(ClassModule *thisModule);

    virtual void do_t_day(ClassModule *thisModule);

    virtual void do_rh_day(ClassModule *thisModule);

    virtual void do_ea_day(ClassModule *thisModule);

    virtual void do_p(ClassModule *thisModule);

    long GetUnit(void);

    virtual void review_HRU_OBS(void);
};

class __declspec(dllexport) ClassPar {
    public:
    string module;
    string param;
    string basemodule;
    string help;
    string units;

    CRHM::TVar varType;
    CRHM::TDim dimen;

    long dim;
    long lay;
    long variation_set;

    float *values;
    long *ivalues;

    float ** layvalues;
    long **ilayvalues;

    string valstr;
    float minVal;
    float maxVal;

    TStringList * Strings;

    CRHM::TVISIBLE visibility;

// backup storage

    float ** layvaluesBkup;
    long **ilayvaluesBkup;

    ClassPar *Identical;

    TStringList * StringsBkup;

    ClassPar(string module = "none", string param = "none")
			 : module(module), param(param), dim(0), visibility(CRHM::USUAL), variation_set(0), varType(CRHM::none),
               values(NULL), ivalues(NULL), layvalues(NULL), ilayvalues(NULL), Identical(NULL) {};

    ClassPar(string module, string param, CRHM::TDim dimen,  // strings
                     string CommaText, string help, CRHM::TVar varType, int Grpdim);

    ClassPar(string module, string param, CRHM::TDim dimen,  // integer and float
         string valstr, float minVal, float maxVal,
                     string help, string units, CRHM::TVar varType, int defdim = 0, int GrpN = 0);

    ClassPar(ClassPar &p);  // copy constructor

    float &operator[](int ii) {return values[ii];}

    virtual __fastcall ~ClassPar();
    
    bool Same(ClassPar &p);  // compares parameter data

    void Change(ClassPar &p);  // changes this values to p

    virtual string UserName(void){return module + ' ' + param;};

    friend class ::parser;

    void ExpandShrink(long new_dim);

    void BackUp (void);

    void Restore (void);

    long GetUnit(void);

};

class __declspec(dllexport) Classfilter {
  public:
  Classfilter(ClassData *MyObs, String ToVar, String args, String argtypes);
                                  
  virtual ~Classfilter();

  ClassData *MyObs;

  String ToVar;
  String argtypes;
  String args;
  
  long Vs;
  long Cs;
  bool Error;
  long ObsCnt;
  long TotalCnt; // when created;
  bool FirstTime;

  long *DataIndx;    // Vs offsets
  long *DataObsCnt;  // maximum number of observations
  float ***Data;     // Data[Vs selection][Obs][line]
  double *Constants; // constant data

  ClassVar *thisVar; // last one accessed
  
  virtual void readargs();
  virtual void error(String Mess);
  void fixup(void);
  virtual void doFunc(long Obs, long Line){Data [0] [Obs] [Line] = 0.0;}
  virtual void doFunctions(long Line);
};

class __declspec(dllexport) ClassFtoC : Classfilter {
  public:
  ClassFtoC(ClassData *MyObs, String ToVar, String args, String argtypes = "V");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassCtoK : Classfilter {
  public:
  ClassCtoK(ClassData *MyObs, String ToVar, String args, String argtypes = "V");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassKtoC : Classfilter {
  public:
  ClassKtoC(ClassData *MyObs, String ToVar, String args, String argtypes = "V");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassTimeshift : Classfilter {
  public:
  ClassTimeshift(ClassData *MyObs, String ToVar, String args, String argtypes = "C");
};

class __declspec(dllexport) ClassRH_WtoI : Classfilter {
  public:
  ClassRH_WtoI(ClassData *MyObs, String ToVar, String args, String argtypes = "VV");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classea : Classfilter {
  public:
  Classea(ClassData *MyObs, String ToVar, String args, String argtypes = "VV");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classsine : Classfilter {
  public:
  long period;
  long phase;
  long delay;
  long duration;
  Classsine(ClassData *MyObs, String ToVar, String args, String argtypes = "CCCC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classpulse : Classfilter {
  public:
  long delay;
  long duration;
  Classpulse(ClassData *MyObs, String ToVar, String args, String argtypes = "CC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classexp : Classfilter {
  public:
  long delay;
  long duration;
  float A;
  float B;
  Classexp(ClassData *MyObs, String ToVar, String args, String argtypes = "CCCC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classexpv : Classfilter {
  public:
  float A;
  float B;
  Classexpv(ClassData *MyObs, String ToVar, String args, String argtypes = "VCC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classpoly : Classfilter {
  public:
  long delay;
  long duration;
  Classpoly(ClassData *MyObs, String ToVar, String args, String argtypes = "CCCCCCC");

  virtual void doFunc(long Obs, long Line);
  virtual String GetFilterName(void){return typeid(*this).name();}
};

class __declspec(dllexport) Classpolyv : Classfilter {
  public:
  Classpolyv(ClassData *MyObs, String ToVar, String args, String argtypes = "VCCCCC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classlog : Classfilter {
  public:
  long delay;
  long duration;
  float A;
  float B;
  Classlog(ClassData *MyObs, String ToVar, String args, String argtypes = "CCCC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classlogv : Classfilter {
  public:
  float A;
  float B;
  Classlogv(ClassData *MyObs, String ToVar, String args, String argtypes = "VCC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classpow : Classfilter {
  public:
  long delay;
  long duration;
  float A;
  float B;
  Classpow(ClassData *MyObs, String ToVar, String args, String argtypes = "CCCC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classpowv : Classfilter {
  public:
  float A;
  float B;
  Classpowv(ClassData *MyObs, String ToVar, String args, String argtypes = "VC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classtime : Classfilter {
  public:
  double start;
  int option;
  Classtime(ClassData *MyObs, String ToVar, String args, String argtypes = "C");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classjulian : Classfilter {
  public:
  int option;
  Classjulian(ClassData *MyObs, String ToVar, String args, String argtypes = "C");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classrandom : Classfilter {
  public:
  Classrandom(ClassData *MyObs, String ToVar, String args, String argtypes = "C");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classsquare : Classfilter {
  public:
  long period;
  long phase;
  long delay;
  long duration;
  Classsquare(ClassData *MyObs, String ToVar, String args, String argtypes = "CCCC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classramp : Classfilter {
  public:
  long period;
  long phase;
  long delay;
  long duration;
  Classramp(ClassData *MyObs, String ToVar, String args, String argtypes = "CCCC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classrefwind : Classfilter {
  public:
  float Const; // result log((Z2 - d)/Z)/log((Zm - d)/Z)

  Classrefwind(ClassData *MyObs, String ToVar, String args, String argtypes = "VCCC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classadd : Classfilter {
  public:

  Classadd(ClassData *MyObs, String ToVar, String args, String argtypes = "VC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classsub : Classfilter {
  public:

  Classsub(ClassData *MyObs, String ToVar, String args, String argtypes = "VC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classmul : Classfilter {
  public:

  Classmul(ClassData *MyObs, String ToVar, String args, String argtypes = "VC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classdiv : Classfilter {
  public:

  Classdiv(ClassData *MyObs, String ToVar, String args, String argtypes = "VC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassaddV : Classfilter {
  public:

  ClassaddV(ClassData *MyObs, String ToVar, String args, String argtypes = "VV");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClasssubV : Classfilter {
  public:

  ClasssubV(ClassData *MyObs, String ToVar, String args, String argtypes = "VV");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassmulV : Classfilter {
  public:

  ClassmulV(ClassData *MyObs, String ToVar, String args, String argtypes = "VV");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassdivV : Classfilter {
  public:

  ClassdivV(ClassData *MyObs, String ToVar, String args, String argtypes = "VV");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classconst : Classfilter {
  public:

  Classconst(ClassData *MyObs, String ToVar, String args, String argtypes = "C");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassSim : Classfilter {
  public:

  ClassSim(ClassData *MyObs, String ToVar, String args, String argtypes = "CCC");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassSmear : Classfilter {
  public:

  ClassSmear(ClassData *MyObs, String ToVar, String args, String argtypes = "VCC");

  bool Minus;

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassMissing : Classfilter {
  public:

  ClassMissing(ClassData *MyObs, String ToVar, String args, String argtypes = "VCC");
  ~ClassMissing();

  float *GoodData;
  
  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassMissingInter : Classfilter {
  public:

  ClassMissingInter(ClassData *MyObs, String ToVar, String args, String argtypes = "VCC");
  ~ClassMissingInter();

  bool FirstTime;
  float *GoodData;
  long *LastGoodData;
  
  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassMissing0 : Classfilter {
  public:

  ClassMissing0(ClassData *MyObs, String ToVar, String args, String argtypes = "VCC"):
            Classfilter(MyObs, ToVar, args, argtypes) {readargs();};

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassMissingC : Classfilter {
  public:

  ClassMissingC(ClassData *MyObs, String ToVar, String args, String argtypes = "VCCC"):
            Classfilter(MyObs, ToVar, args, argtypes) {readargs();};

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassMissingFlag : Classfilter {
  public:

  ClassMissingFlag(ClassData *MyObs, String ToVar, String args, String argtypes = "VCC"):
            Classfilter(MyObs, ToVar, args, argtypes) {readargs();};

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassMissingFlagAfter : Classfilter {
  public:

  ClassMissingFlagAfter(ClassData *MyObs, String ToVar, String args, String argtypes = "VCC"):
            Classfilter(MyObs, ToVar, args, argtypes) {readargs();};
  ~ClassMissingFlagAfter();

  long First;
  long Last;

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassMissingrepl : Classfilter {
  public:

  ClassMissingrepl(ClassData *MyObs, String ToVar, String args, String argtypes = "VCCV"):
            Classfilter(MyObs, ToVar, args, argtypes) {readargs();};

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassForce : Classfilter {
  public:

  ClassForce(ClassData *MyObs, String ToVar, String args, String argtypes = "C");

  virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classmacro {
  public:
  Classmacro(ClassData *File);
  ~Classmacro();

  ClassData *File;
  TStringList *FilterList;
  long Interpolation;
  void addfilter(String Line);
  void fixup(void);
  void execute(long Line);
};

class __declspec(dllexport) ClassModel {
public:
  String ModelName;
  String ModelModules;

  ClassModel(String ModelName, String ModelModules) :
           ModelName(ModelName), ModelModules(ModelModules) {};
};

__declspec(dllexport) void __fastcall LogError(CRHMException Except);
__declspec(dllexport) void __fastcall LogError(String S, TExcept Kind);

__declspec(dllexport) void __fastcall LogMessage(const char *S, float V, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessage(const char *S, long V, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessage(const char *S, TExtra Opt = BLANK);

__declspec(dllexport) void __fastcall LogMessage(long hh, const char *S, float V, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessage(long hh, const char *S, long V, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessage(long hh, const char *S, TExtra Opt = BLANK);

__declspec(dllexport) void __fastcall LogMessage(long hh, const char *S, float V1, float V2, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessage(long hh, const char *S, float V1, float V2, float V3, TExtra Opt = BLANK);

__declspec(dllexport) void __fastcall LogMessageA(long hh, const char *S, float V1, const float HRU_area, const float Basin_area, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessageA(long hh, const char *S, float V1, const float Basin_area, TExtra Opt = BLANK);

__declspec(dllexport) void __fastcall LogDebug(long h, char *Text, float v);
__declspec(dllexport) void __fastcall LogDebug(char *S);
__declspec(dllexport) void __fastcall LogDebugD(char *S);
__declspec(dllexport) void __fastcall LogDebugT(char *S);

__declspec(dllexport) void __fastcall Update_Main_Status(String S);

__declspec(dllexport) void __fastcall Update_Main_DIM(CRHM::TDim Dim, long dim);

__declspec(dllexport) void __fastcall Update_Main_Dirty(void);

__declspec(dllexport) long getdim(CRHM::TDim dimen);

__declspec(dllexport) long getstep(void);

__declspec(dllexport) bool laststep(void);

__declspec(dllexport) void setdim(CRHM::TDim dimen, long dim);

__declspec(dllexport) void setdim(string name, long dim);

__declspec(dllexport) void ModVarRemove(MapVar & MapVars);

__declspec(dllexport) long julian(char *when);

__declspec(dllexport) long julian(TDateTime DT);

__declspec(dllexport) long julian(TDateTime DT);

__declspec(dllexport) long MonthDaysCnt(TDateTime DT);

__declspec(dllexport) float Julian(char *when);

__declspec(dllexport) bool last_timestep(void);

__declspec(dllexport) void dattim(char *type, long *itime);

__declspec(dllexport) ClassVar *declread(string module, string name, long cnt, long offset,
               ClassData * FileData, string Comment);

__declspec(dllexport) long ClassParFindParBld(ClassPar *thisPar);

__declspec(dllexport) ClassVar *ClassVarFind(string name);

__declspec(dllexport) ClassPar *ClassParFindShared(string name); // where name is concatenation of MODULE and NAME

__declspec(dllexport) ClassPar *ClassParFind(string name); // where name is concatenation of MODULE and NAME

__declspec(dllexport) ClassPar *ClassParFindPar(string name); // where name is parameter

__declspec(dllexport) ClassPar *ClassParFind(string module, string param); // routine concatenates MODULE and NAME

__declspec(dllexport) ClassPar *ClassParFindRev(string module, string param);

__declspec(dllexport) void ClassParSet(ClassPar *p);

float sqr(float x);

class __declspec(dllexport) Tresult {
public:
  double k;
  char *aExp;

  Tresult(int size) : k(1.0){
                      aExp = new char[size];
                      ::memset( aExp, 0, sizeof(char)*size );
                    }
  ~Tresult() {delete[] aExp;}
};

class Unit_Info {
public:
  string Abbr;
  string Name;
  double k;
  string Expr;

  Unit_Info() :
    Abbr(""), Name(""), k(0.0), Expr("") {};

  Unit_Info(string Abbr_, string Name_, double k_, string Expr_) :
    Abbr(Abbr_), Name(Name_), k(k_), Expr(Expr_) {};
};

class Multiplier_Info {
public:
  char Abbr;
  string Name;
  double k;
  Multiplier_Info(char Abbr_, string Name_, double k_) :
    Abbr(Abbr_), Name(Name_), k(k_) {};
};

class __declspec(dllexport) Convert {
  static Unit_Info Infos[];
  static Multiplier_Info Multipliers[];

  int NumBasicUnits;
  int NumUnits;
  int NumMultipliers;

  public:
  Convert();

  bool ConvertUnit(double& dValue, string pszSrcUnit, string pszDstUnit );

  double quickPow( double k, int nPow );
  int LookupUnit( string pszIn );
  void DivUnit( Tresult& u1, const Tresult& u2 );
  void MulUnit( Tresult& u1, const Tresult& u2 );
  void MulUnitK( Tresult& u, double k );
  void PowUnit( Tresult& u, char nPow );
  void SetBasicUnit( Tresult& u, double k, int iBasicUnit );
  void ExpandUnitExpr( Tresult& u, double k, string pszExpr );

  string ParseDivUnitExpr( string pszIn, Tresult& u );
  string ParseMulUnitExpr( string pszIn, Tresult& u );
  string ParsePowUnitExpr( string pszIn, Tresult& u );
  string ParseUnitPhase1( string pszIn, Tresult& u );
  string ParseUnitPhase2( string pszIn, Tresult& u );

  void CheckUnitsString(string Name, string variable, string units);
  void CheckUnitsObs(string Comment, string units, string obs); // check original observation units

  bool CheckUnitsTable();
};
#endif
