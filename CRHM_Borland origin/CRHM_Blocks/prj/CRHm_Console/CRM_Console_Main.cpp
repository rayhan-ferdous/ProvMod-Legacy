// 01/27/11
//---------------------------------------------------------------------------

#include <vcl.h>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream.h>                                          F
#include <StrUtils.hpp>
#include "boost/shared_ptr.hpp"
#include "ClassCRHM.h"
#include "ClassModule.h"
#include "NewModules.h"
#include "MacroUnit.h"
#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused

using namespace std;

String Version = "Version: Borland 1.00, 01/27/11";

  class TSeries{
    public:
    TDateTime *XValues;
    float *YValues;
    int Tag;
    int MaxCnt;
    int Used;
    String Title;
    TSeries(int Cnt){ MaxCnt = Cnt; XValues = new TDateTime[MaxCnt]; YValues = new float[MaxCnt]; Used = 0;};
    ~TSeries(){delete[] XValues; delete[] YValues;};
    void AddXY(TDateTime X, float Y) {XValues[Used] = X; YValues[Used++] = Y;};
    int Count(void) {return Used;};
    TDateTime XValue(int nn) {return XValues[nn];};
    float YValue(int nn) {return YValues[nn];};
  };

  TSeries **cdSeries;
  long SeriesCnt;

  class Classinfo; // used to process basin parameters

  typedef boost::shared_ptr<Classinfo> Pinfo;
  typedef pair<string, Pinfo>  Pairinfo;
  typedef multimap<string, Pinfo>  paras;

  typedef pair<string, ClassPar*>  PairPar;
  typedef multimap<string, ClassPar*>  GrpParas;

  class Classinfo {
    public:
    Classinfo() : thisPar(NULL), rootinfo(NULL), matched(false), cnt(0) {};
    Classinfo(ClassPar *thisPar) : thisPar(thisPar), rootinfo(NULL), matched(false), cnt(0) {};
    ClassPar *thisPar;
    Classinfo *rootinfo;
    long cnt;
    bool matched;
  };

  ClassVar *VarFind(string name);
  ClassPar *ParFind(string name);

  CRHM::TFun  FindObservationType(String Kind);

  String OpenNamePrj;
  String OpenNameState;
  String OpenNamePar;
  String OpenNameObs;
  String OpenNameReport;

  String ProjectDirectory;
  String ApplicationDir;

  TStringList *ListBox1;
  TStringList *ListBox2;
  TStringList *ListBox3;
  TStringList *ListBox4;

  TStringList *ObsFilesList;
  TStringList *ProjectList;

  bool OpenStateFlag;

  TDateTime ProjectFileDate;
  TDateTime Dt0; // used to calculate project load time

int _matherr (struct _exception *a){
  char Error[][10] = {"NONE", "DOMAIN","SING","OVERFLOW","UNDERFLOW","TLOSS"};
  CRHMException Except((String(Error[a->type]) + " error in function '" + a->name + "' ").c_str(), TERMINATE);
  throw Except;
}

using namespace std;
using namespace CRHM;

extern double xLimit;
extern long lLimit;

bool ReportAll = false;
Administer AdminMacro("03/24/06", "Macro");

Global global;

TDate Picker1; // replaces graphic controls
TDate Picker2;

String Sstrings[] = {"", "_WtoMJ", "_MJtoW", "_Avg", "_Min", "_Max", "_Sum", "_Pos", "_Tot", "_Tot/Freq", "_First", "_Last"};

extern string AKAstrings[];

CRHM::TFun Funct = CRHM::FOBS;

int InitModCnt = 0;
int InitMacroCnt = 0;
//---------------------------------------------------------------------------

void __fastcall LogMessageX(const char *S)
{
  puts(S);
}
//---------------------------------------------------------------------------

int __fastcall IndexOf(TStringList *Box, const AnsiString S){
  for(int ii = 0; ii < Box->Count; ++ii){
    if(Box->Strings[ii] == S)
    return ii;
  }
  return -1;
}
//---------------------------------------------------------------------------

void __fastcall ReadStateFile(bool & GoodRun)
{
  MapPar::iterator itVar;
  ClassVar *thisVar;

  ifstream DataFile;
  char module[24], name[24], Descrip[80], Line[80];
  string S;
    DataFile.open(OpenNameState.c_str());
    if(!DataFile) {
      Application->MessageBox("cannot open file", "File Error", MB_OK);
      return;
    }

    DataFile.getline(Descrip, 80);
    DataFile.ignore(80, '#');
    DataFile.getline(Line, 80);

    DataFile.getline(Line, 80); // read "TIME:"
    Word D[3];
    DataFile >> D[0] >> D[1] >> D[2];
    double DT = EncodeDate(D[0], D[1], D[2]);

    DataFile.getline(Descrip, 80);
    DataFile.ignore(80, '#');
    DataFile.getline(Line, 80);

    DataFile.getline(Line, 80); // read "Dimension:"
    long filehru, filelay;
    DataFile >> filehru >> filelay;
    if(filehru != Global::nhru || filelay != Global::nlay ){
      Application->MessageBox("State File and Model #HRU's or #LAY's are not equal",
                              "File Error", MB_OK);
      GoodRun = false;
      return;
    }

    DataFile.ignore(80, '#');
    DataFile.getline(Line, 80);

    while(!DataFile.eof()) {
      DataFile >> module >> name;
      if(DataFile.fail()) break;

      DataFile.ignore();
      S = string(module) + ' ' + string(name);
      thisVar = ClassVarFind(S);

      if(!thisVar) thisVar = ClassVarFind("#" + S);  // could be local variable

      if(thisVar) {
        if(thisVar->lay == 0){
          for(int ii = 0; ii < thisVar->dim; ii++)
            if(thisVar->values != NULL)
              DataFile >> thisVar->values[ii];
            else if(thisVar->ivalues != NULL)
              DataFile >> thisVar->ivalues[ii];
        }
        else {
          for(int ll = 0; ll < thisVar->lay; ll++)
            for(int ii = 0; ii < thisVar->dim; ii++)
              if(thisVar->layvalues != NULL)
                DataFile >> thisVar->layvalues[ll][ii];
              else  if(thisVar->ivalues != NULL)
                DataFile >> thisVar->ilayvalues[ll][ii];
        }
        DataFile.ignore(80, '#');
        DataFile.getline(Line, 80);
      }
      else {
        Application->MessageBox((String("State File variable ") + S.c_str()).c_str(),
                                "Unknown variable", MB_OK);
        DataFile.ignore(80, '#');
        DataFile.getline(Line, 80);
      }
    }
}
//---------------------------------------------------------------------------

String __fastcall ExtractHruLay(String S, long &Hru, long &Lay){

  long jj = S.LastDelimiter("(");
  long jj1 = S.LastDelimiter(",");
  long jj2 = S.LastDelimiter(")");

  Lay = 0;
  if(jj1 != 0)
    Lay = (S.SubString(jj1+1, jj2-jj1-1)).ToInt();
  else
    jj1 = jj2;

  Hru = (S.SubString(jj+1, jj1-jj-1)).ToInt();

  return S.SubString(1, jj-1);
}
//---------------------------------------------------------------------------

void __fastcall FormCreate(void){

  Global::BuildFlag = CRHM::BUILD;

  Global::maxhru = 1;
  Global::maxlay = 1;
  Global::maxobs = 1;

  Global::Freq = 48;
  Global::Interval = 1.0/Global::Freq;

  cdSeries = NULL;

  TDateTime Dt = TDateTime::CurrentDate();
  OpenStateFlag = false;

  Global::nhru = Global::maxhru;
  Global::nobs = Global::maxobs;
  Global::nlay = Global::maxlay;

  ObsFilesList = new TStringList;

  ProjectList = new TStringList;

  Global::AllModulesList = new TStringList;
  Global::AllModulesList->CaseSensitive = true;

  Global::OurModulesList = new TStringList;
  Global::OurModulesList->Sorted = false;

  Global::MacroModulesList = new TStringList;
  Global::MacroModulesList->Sorted = false; // Global::ModelModulesList is not sorted
  Global::MacroModulesList->QuoteChar = '\'';

  Global::AllModelsList = new TStringList;
  Global::AllModelsList->Sorted = true;

  Global::ModelModulesList = new TStringList;
  Global::ModelModulesList->Sorted = false;

  Global::OurHelpList = NULL;   // DLL help files
  Global::PendingDLLModuleList = new TStringList; // current DLL modules

  Global::ReportList = NULL; //

  Global::DeclRootList = new TStringList;

  ListBox1 = new TStringList;
  ListBox2 = new TStringList;
  ListBox3 = new TStringList;
  ListBox4 = new TStringList;

  MoveModulesToGlobal();
  ((ClassModule*) Global::PendingDLLModuleList->Objects[0])->OurAdmin->Accept(mrYesToAll);
  ++InitModCnt;
}
//---------------------------------------------------------------------------

bool __fastcall OpenObsFile(String FileName)
{
  ClassData  * FileData;

    if(ObsFilesList->IndexOf(FileName.c_str()) != -1)
         return false;  // already open

    if(ObsFilesList->Count == 0) {
      Global::DTstart = 0; // used to flag first data file
      Global::DTend = 0; // used to flag first data file
    }

    FileData = new ClassData(FileName.c_str());

    if(FileData->Success) {

      if(ObsFilesList->Count == 0) {
        if(FileData->Times != NULL) { // handle sparse data
          Application->MessageBox("Sparse file cannot be first to be opened", "File order Error", MB_OK);
          delete FileData;
          return false;
        }

        Global::Interval = FileData->Interval;
        Global::Freq = FileData->Freq;

        Global::IndxMin = FileData->IndxMin;
        Global::IndxMax = FileData->IndxMax;

      }

      FileData->ModN = Global::Freq / FileData->Freq;

      MapVar::iterator itVar;
      ClassVar * thisVar;

// always starts with this display// remove entries that are in observation ListBox1
      for(int ii = 0; ii < ListBox1->Count; ii++) {
        thisVar =  (ClassVar *) ListBox1->Objects[ii];
        if(thisVar && thisVar->varType >= CRHM::Read) {
          ListBox1->Delete(ii);
          ii = 0;
        }
      }

// remove entries that are in observation ListBox3
      for(int ii = 0; ii < ListBox3->Count; ii++) {
        thisVar =  (ClassVar *) ListBox3->Objects[ii];
        if(thisVar && thisVar->varType >= CRHM::Read) {
          ListBox3->Delete(ii);
          ii = 0;
        }
      }

      ListBox2->Clear();

      for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
        thisVar = (*itVar).second;
        if(thisVar && thisVar->varType >= CRHM::Read)
          if(IndexOf(ListBox2, thisVar->name.c_str()) == -1)
            ListBox2->AddObject(thisVar->name.c_str(), (TObject*) thisVar);
      }

      ObsFilesList->AddObject(OpenNameObs.c_str() , (TObject *) FileData);

      return true;
    }
    else {
      if(ObsFilesList->Count == 0) {
        Global::DTstart = 0; // used to flag first data file
        Global::DTend = 0; // used to flag first data file
      }

      delete FileData;
      return false;
    }
}
//---------------------------------------------------------------------------

void __fastcall ObsCloseClick(void){

  ListBox2->Clear();


  for(int ii = 0; ii < ObsFilesList->Count; ii++) {
    ClassData * FileData = (ClassData *) ObsFilesList->Objects[ii];
    delete FileData;   // delete ClassData instance
  }
  ObsFilesList->Clear();  // clear list

  Global::nobs = 1;  // reset to 1

}
//---------------------------------------------------------------------------

void __fastcall AddObsPlot(ClassVar *thisVar,
                             TSeries *cdSeries, String S, CRHM::TFun Funct)
{
  float **Data = thisVar->FileData->Data;
  double xx;
  double DTstartR = Picker1;
  double DTendR   = Picker2;
  if(DTstartR >= DTendR) return;

  double MyInterval = thisVar->FileData->Interval;
  long DTmin  = INT((DTstartR-Global::DTstart)* thisVar->FileData->Freq)*thisVar->FileData->ModN;
  long DTmax  = INT((DTendR-Global::DTstart)* thisVar->FileData->Freq)*thisVar->FileData->ModN;

  long jj = S.LastDelimiter("(");
  long jj2 = S.LastDelimiter(")");

  long  Indx = (S.SubString(jj+1, jj2-jj-1)).ToInt()-1;

  long IndxMin = thisVar->FileData->IndxMin;
  long IndxMax = thisVar->FileData->IndxMax;

  if(thisVar->FileData->Times != NULL) { // display sparse data
    if(Global::Freq == 1)
      --DTendR;

    for(long ii = 0; ii < thisVar->FileData->Lines; ++ii) {
      if(thisVar->FileData->Times[ii] < DTstartR) continue;
      if(thisVar->FileData->Times[ii] > DTendR) continue;

      xx = Data[thisVar->offset+Indx][ii];
      cdSeries->AddXY(thisVar->FileData->Times[ii], xx);
    }
  }

  else if(Funct == CRHM::FOBS || Funct == CRHM::W_MJ || Funct == CRHM::MJ_W){ // display simple observations
    float Mult;
    if(Funct == CRHM::FOBS) Mult = 1.0;
    else if(Funct == CRHM::W_MJ)
      Mult = thisVar->FileData->Interval*86400/1.0E6;
    else if(Funct == CRHM::MJ_W)
      Mult = 1.0E6/86400/thisVar->FileData->Interval;

    for (Global::DTindx = DTmin; Global::DTindx < DTmax; Global::DTindx++) {
      Global::DTnow = Global::DTstart + Global::Interval*Global::DTindx + Global::Interval;

      if(MyInterval >= 1) --Global::DTnow;

      if(Global::DTindx/thisVar->FileData->ModN >= IndxMin
           && Global::DTindx/thisVar->FileData->ModN <= IndxMax
           && (thisVar->FileData->ModN == 1 // handles root data
             || Global::DTindx%thisVar->FileData->ModN == thisVar->FileData->ModN -1)) { // handles shrink data
        xx = Data[thisVar->offset+Indx][(Global::DTindx/thisVar->FileData->ModN - IndxMin)]* Mult;
        cdSeries->AddXY(Global::DTnow, xx);
      }
    }
  }
  else { // display observations functions
// N.B. object FileData copied. If Obs function - Obs deletes else if VarObsFunct ListBox4 deletes.
    ClassVar *newVar = new ClassVar(*thisVar);
    cdSeries->Tag = (int) newVar;
    newVar->name = S.c_str();

    switch (Funct) {
      case CRHM::AVG:
          newVar->FunctVar = thisVar;
          newVar->UserFunct = &ClassVar::Avg;
          newVar->FunKind = CRHM::AVG;
          break;
      case CRHM::MIN:
          newVar->FunctVar = thisVar;
          newVar->UserFunct = &ClassVar::Min;
          newVar->FunKind = CRHM::MIN;
          break;
      case CRHM::MAX:
          newVar->FunctVar = thisVar;
          newVar->UserFunct = &ClassVar::Max;
          newVar->FunKind = CRHM::MAX;
          break;
      case CRHM::DTOT:
          newVar->FunctVar = thisVar;
          newVar->UserFunct = &ClassVar::Dtot;
          newVar->FunKind = CRHM::DTOT;
          break;
      case CRHM::POS:
          newVar->FunctVar = thisVar;
          newVar->UserFunct = &ClassVar::Pos;
          newVar->FunKind = CRHM::POS;
          break;
      case CRHM::TOT:
          newVar->FunctVar = thisVar;
          newVar->UserFunct = &ClassVar::Tot;
          newVar->FunKind = CRHM::TOT;
          newVar->values[Indx] = 0.0;
          break;
      case CRHM::TOT_INT:
          newVar->FunctVar = thisVar;
          newVar->UserFunct = &ClassVar::Tot_Ints;
          newVar->FunKind = CRHM::MIN;
          newVar->values[Indx] = 0.0;
          break;
      case CRHM::FIRST:
          newVar->FunctVar = thisVar;
          newVar->UserFunct = &ClassVar::First;
          newVar->FunKind = CRHM::TOT_INT;
          break;
      case CRHM::LAST:
          newVar->FunctVar = thisVar;
          newVar->UserFunct = &ClassVar::Last;
          newVar->FunKind = CRHM::LAST;
          break;
    } // switch

    long *HRU_OBS = new long[newVar->dim];
    for(long ii = 0; ii < newVar->dim; ++ii)
      HRU_OBS[ii] = ii+1;

    for (Global::DTindx = DTmin; Global::DTindx < DTmax; Global::DTindx+=Global::Freq) {
      Global::DTnow = Global::DTstart + Global::Interval*Global::DTindx + Global::Interval;

      if(Global::DTindx/thisVar->FileData->ModN >= IndxMin
           && Global::DTindx/thisVar->FileData->ModN <= IndxMax) {

        if(Global::Interval >= 1) --Global::DTnow;

        if(Global::DTindx%Global::Freq == 0) {
          (newVar->*(newVar->UserFunct))(HRU_OBS);
          xx = newVar->values[Indx];
          cdSeries->AddXY(Global::DTnow, xx);
        }
      }
    } // for
  delete[] HRU_OBS;
  } // else
}
//---------------------------------------------------------------------------

void __fastcall ObsFileClose(void)
{
  MapVar::iterator itVar;
  ClassVar * thisVar;

  String S;  // Fix ???

  int Pos  = ObsFilesList->IndexOf(S);

  if(Pos == 0 && ObsFilesList->Count > 1) {
    ObsCloseClick();
    return;
  }

  int Reply = Application->MessageBox(S.c_str(), "Close Observation File", IDOK);

  if(Reply == IDOK) {


      Global::nobs = 1;  // reset to 1
    }

    ListBox2->Clear();

    ClassData * FileData = (ClassData *) ObsFilesList->Objects[Pos];
    delete FileData;   // delete ClassData instance
    ObsFilesList->Delete(Pos);  // delete entry in list

    for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
      thisVar = (*itVar).second;
      if(thisVar->varType >= CRHM::Read)
	if(IndexOf(ListBox2, (*itVar).second->name.c_str()) == -1)
          ListBox2->AddObject((*itVar).second->name.c_str(),
            (TObject*) (*itVar).second);
    }

    for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
      thisVar = (*itVar).second;
      if(thisVar->varType < CRHM::Read && thisVar->visibility == CRHM::VARIABLE)
	if(IndexOf(ListBox1, (*itVar).second->name.c_str()) == -1)
	  ListBox1->AddObject((*itVar).second->name.c_str(),
	    (TObject*) (*itVar).second);
    }
}
//---------------------------------------------------------------------------

void __fastcall FormDestroy(void)
{

  for(int ii = 0; ii < ObsFilesList->Count; ++ii) {
    ClassData * FileData = (ClassData *) ObsFilesList->Objects[ii];
    delete FileData;   // delete ClassData instance
  }

  delete ObsFilesList;

  ModVarRemove(Global::MapVars);
  Global::SharedMapPars.clear();

  delete ProjectList;

  delete ListBox1;
  delete ListBox2;
  delete ListBox3;
  delete ListBox4;

  delete Global::OurModulesList;

  delete Global::ModelModulesList;

  delete Global::DeclRootList;

  delete Global::PendingDLLModuleList;
}
//---------------------------------------------------------------------------

void __fastcall FreeChart1(void)
{
  if(SeriesCnt > 0) {
    for (int ii = 0; ii < SeriesCnt; ii ++) {

      ClassVar* thisVar =  (ClassVar *) cdSeries[ii]->Tag;
      if(thisVar->FunKind > CRHM::FOBS && !thisVar->values && !thisVar->ivalues)
        delete thisVar;

    }
  }
}
//---------------------------------------------------------------------------

void __fastcall ClearModules(bool All){

  ModVarRemove(Global::MapVars);

  Global::SharedMapPars.clear();
  Global::MapParsPrj.clear();

  if(All)
    for(int ii = 0; ii < Global::OurModulesList->Count; ii++)
      ((ClassModule*) (Global::OurModulesList->Objects[ii]))->reset();

  Global::OurModulesList->Clear();

  if(All){
    AdminMacro.MacroClear();

    Global::MacroModulesList->Clear();
  }

  ListBox1->Clear();
  ListBox3->Clear();

  for (int ii = 0; ii < SeriesCnt; ++ii)
    delete cdSeries[ii];
  delete [] cdSeries;

  Global::BuildFlag = CRHM::BUILD;

  Global::MapAKA.clear(); // remove all AKA

  OpenNamePrj = "";
}
//---------------------------------------------------------------------------

void __fastcall UpdateDim(CRHM::TDim Dim, long dim){

  switch(Dim) {
    case CRHM::NHRU :
      Global::nhru = dim;
      Global::maxhru = dim;
      break;
    case CRHM::NOBS :
      Global::nobs = dim;
      Global::maxobs = dim;
      break;
    case CRHM::NLAY :
      Global::nlay = dim;
      Global::maxlay = dim;
      break;
  }
}
//---------------------------------------------------------------------------

void __fastcall RemoveBasinParams(void){ // pseudo shared parameters

  Global::Mapgetvar.clear();
  Global::Mapputvar.clear();
  Global::Mapreadvar.clear();
  Global::Mapdeclvar.clear();
  Global::Mapdeclstat.clear();
  Global::Mapdeclpar.clear();
  Global::Mapdeclobs.clear();

  Global::DeclRootList->Clear(); // used by AKA to stop looping

  Global::BuildFlag = CRHM::BUILD; // default value

  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii)
    ((ClassModule*) Global::OurModulesList->Objects[ii])->decl();


  Global::BuildFlag = CRHM::DECL; // model loaded

  ClassPar *thisPar;
  MapPar::iterator itPar, itPar0;
  long count;
// restore original module parameters from pseudo Shared parameters if they do not already exist

  itPar = Global::SharedMapPars.begin();
  while (itPar !=  Global::SharedMapPars.end()) {
    thisPar = (*itPar).second;
    count = ClassParFindParBld(thisPar);
    Global::MapPars.erase("Shared " + thisPar->param);
    delete thisPar; // parameter no longer needed
    ++itPar;
  }
  Global::SharedMapPars.clear();
}
//---------------------------------------------------------------------------

void __fastcall SetBasinParams(ClassPar *basinPar){

// copy basin parameter to all module parameters

  ClassPar *thisPar;
  MapPar::iterator itPar;

  for(itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); ++itPar){
    thisPar = (*itPar).second;
    if(basinPar == thisPar) // skip itself
      continue;
    if(thisPar->param == basinPar->param && thisPar->dim == basinPar->dim)
      thisPar->Change(*basinPar);
  }
}
//---------------------------------------------------------------------------

void __fastcall WMMainUpdateDim(TMessage &Message){

  UpdateDim((CRHM::TDim) Message.WParam, (long) Message.LParam);
}
//---------------------------------------------------------------------------

  void __fastcall DoObsStatus(bool &First){

  if(First) {
    for(int ii = 0; ii < ObsFilesList->Count; ii++) {
      ClassData * FileData = (ClassData *) ObsFilesList->Objects[ii];
      FileData->TimeIndx = 0;
    }
    First = false;
  }

  for(int ii = 0; ii < ObsFilesList->Count; ii++) {
    ClassData * FileData = (ClassData *) ObsFilesList->Objects[ii];

    FileData->GoodInterval = true;

    if(ii == 0) {  // first observation file always good
      FileData->GoodDay = true;
      continue;
    }

    FileData->GoodInterval = true;

    if(FileData->Times != NULL) { // sparse data
        FileData->GoodDay = false;

      while (FileData->Times[FileData->TimeIndx] < Global::DTnow
        && FileData->TimeIndx < FileData->Lines-1)
        ++FileData->TimeIndx;

      if(FileData->Times[FileData->TimeIndx] != Global::DTnow)
        FileData->GoodInterval = false;
    }
    else { // normal observation file

      long Index = Global::DTindx/FileData->ModN;

      if(Index < FileData->IndxMin || Index > FileData->IndxMax){
        FileData->GoodInterval = false;
        FileData->GoodDay = false;
        continue;
      }

      if(Index%FileData->Freq == 0){ // beginning of day
        FileData->GoodDay = true;
        if(FileData->Freq <= 1) continue; // handle daily data
        Index+= FileData->Freq/FileData->ModN -1; // add day
        if(Index < FileData->IndxMin || Index > FileData->IndxMax){
          FileData->GoodDay = false;
          continue;
        }
        continue;
      }
      else {
        if(FileData->GoodDay)
          FileData->GoodInterval = true;
        else if(Index < FileData->IndxMin || Index > FileData->IndxMax)
// day at end of file missing data
          FileData->GoodInterval = false;
      }
    }
  } // for
}
//---------------------------------------------------------------------------

  String __fastcall HRUStoString(String S){ // handles observations too!

    long Hru, Lay;

    return S;

  }
//---------------------------------------------------------------------------

ClassVar *VarFind(string name){
  MapVar::iterator itVar;

  if((itVar = Global::MapVars.find(name)) == Global::MapVars.end())
    return NULL;
  else
    return ((*itVar).second);
}
//---------------------------------------------------------------------------

ClassPar *ParFind(string name){ // where name is concatenation of MODULE and NAME
  MapPar::iterator itPar;

  if((itPar = Global::MapPars.find(name)) == Global::MapPars.end()) {
    return NULL;
  }
  return ((*itPar).second);
}
//---------------------------------------------------------------------------

void __fastcall MacroLoad(void)
{
  Global::GroupCntTrk = 0;
  Global::StructCntTrk = 0;
  if(Global::MacroModulesList->Count > 0) {
    int Macro = 0;

    while (Macro < Global::MacroModulesList->Count) {

      string s(Global::MacroModulesList->Strings[Macro].c_str());
      string::size_type ppp = s.find_last_not_of(' ');
      if(s.empty() || ppp == string::npos || s[0] == '/'){
        ++Macro;
        continue;
      }
      string Desc;
      string::size_type pp = s.find_first_of(" /");
      if(pp != string::npos){
        Desc = s.substr(pp);
        s = s.substr(0, pp);
        pp = Desc.find_first_not_of(" /");
        Desc = Desc.substr(pp);
        Desc = '\'' + Desc + '\''; // Bld handles as block
      }
      else
        Desc = "'no description given'"; // Bld handles as block

      ClassMacro *Custom = new ClassMacro(s, Macro, "04/20/06", Desc);
      AdminMacro.AddModule(Custom);

      String S;

      while(S = Global::MacroModulesList->Strings[Macro].TrimLeft(), !(S.SubString(1,3) == "end" &&
            (S.Length() == 3 || S.IsDelimiter(" /", 4))) && Macro < Global::MacroModulesList->Count)

        ++Macro;

      ++Macro;
    }

    AdminMacro.LoadCRHM("Macro");
    AdminMacro.Accept(mrYesToAll);

    if(InitMacroCnt == 0){
      InitMacroCnt = 1;
      ++InitModCnt;
    }

    if(SeriesCnt > 0) {
      SeriesCnt = 0;
    }
  }
}
//---------------------------------------------------------------------------

bool __fastcall FileExistsSp(String FileName) {

  ifstream DataFile;

  DataFile.open(FileName.c_str());
  if(DataFile) {
    DataFile.close();
    return true;
  }
  else
    return false;
}
//---------------------------------------------------------------------------

bool __fastcall FindFileName(String &FileName) {

String FilePart;

ApplicationDir = ExtractFilePath(AnsiReplaceStr(Application->ExeName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
ProjectDirectory = ExtractFilePath(AnsiReplaceStr(OpenNamePrj, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples

  if(FileExistsSp(FileName)) // file path directory
    return true;

  int Pos = FileName.LastDelimiter("\\/" );
  if(Pos){
    FilePart = FileName.SubString(Pos+1, FileName.Length());

    if(FileExistsSp(FilePart)){ // current directory
      FileName = FilePart;
      return true;
    }
  }
  else
    FilePart = FileName;

// original file may now be in project directory
  String NewFileName = ProjectDirectory + FilePart;
  if(FileExistsSp(NewFileName)){
    FileName = NewFileName;
    return true;
  }

// original file may now be in Application directory
  NewFileName = ApplicationDir + FilePart;
  if(FileExistsSp(NewFileName)){
    FileName = NewFileName;
    return true;
  }

  return false;
}
//---------------------------------------------------------------------------

void __fastcall ListBoxMacroClear(void){ // used by Macro

  ClassVar * thisVar;

  if(SeriesCnt <= 0)
    ListBox3->Clear();
  else{
    int indx;
    for(int jj = 0; jj < SeriesCnt;)
      if(indx = ListBox3->IndexOf(cdSeries[jj]->Title), indx > -1) {
        thisVar =  (ClassVar *) ListBox3->Objects[indx];
        if(thisVar->DLLName == "Macro"){ // delete only macros

          for(int kk = jj+1; kk < SeriesCnt; ++kk)
            cdSeries[kk-1] = cdSeries[kk];

          ListBox3->Delete(indx);
          SeriesCnt--; // no need to increment
        }
        else
          ++jj; // increment
      }
  }

  for(int ii = 0; ii < ListBox1->Count; ii++) {
    thisVar =  (ClassVar *) ListBox1->Objects[ii];
    if(thisVar != NULL && thisVar->DLLName == "Macro") {
      ListBox1->Delete(ii);
      ii = 0;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall StateFileClose(void)
{
  OpenNameState = "";
  OpenStateFlag = false;
}
//---------------------------------------------------------------------------

String __fastcall DeclObsName(ClassVar *thisVar){

  String Newname = thisVar->name.c_str();
  int jj = Global::OurModulesList->IndexOf(thisVar->module.c_str()); // find module
  if(jj > -1 && Newname.Pos("#") > 0){ // -1 for "obs" and "#" for declared "obs"
    ClassModule* thisModule = (ClassModule*) Global::OurModulesList->Objects[jj];
    if(thisModule->isGroup){ // if group add suffix
      String AA("@@");
      AA[2] += thisModule->GroupCnt;
      Newname += AA;
    }
  }
  return Newname;
}
//---------------------------------------------------------------------------

bool __fastcall isSimple(string module){ // determines if Simple or Group/Struct module

  int jj = Global::AllModulesList->IndexOf(module.c_str());
  ClassModule* thisModule = (ClassModule*) Global::AllModulesList->Objects[jj];
  if(!(thisModule->isGroup || thisModule->isStruct))
    return true;
  else
    return false;
}
//---------------------------------------------------------------------------

bool Variation_Decide(int Variation_set, long Variation){

// Variation = module variation
// Variation_set = variable variation

  VandP V; V.Set(Variation);

  long variations = V.GetV(); // & 2047;

  if((Variation_set & 2048) != 0 && variations == 0 || // handles VARIATION_0
    (Variation_set == 0) ||                               // handles VARIATION_ORG
    (variations & Variation_set) != 0)                 // handles #1, #2, #4 etc.
    return true;
  else
    return false;
}
//---------------------------------------------------------------------------

//void __fastcall WMMainUpdateStatus(TMessage &Message){

// dummy
//}
//---------------------------------------------------------------------------

void __fastcall Label4Click(void){

  ClassVar *thisVar;
  MapVar::iterator itVar;
  String Newname;

  ListBox1->Clear();

  ListBox1->Sorted = true;

  for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
    thisVar = (*itVar).second;
    if(thisVar->varType < CRHM::Read && thisVar->visibility == CRHM::USUAL && thisVar->dimen != CRHM::NREB){
      Newname = DeclObsName(thisVar);
      if(IndexOf(ListBox1, Newname) == -1)
        ListBox1->AddObject(Newname, (TObject*) thisVar);
    }
  }
}
//---------------------------------------------------------------------------

CRHM::TFun  FindObservationType(String Kind){

  if(Kind == "_obs") Kind = "";
  for(int ii = CRHM::FOBS; ii <= CRHM::LAST; ii++)
    if(Kind == Sstrings[ii]) return (CRHM::TFun)ii;
  return (CRHM::TFun) 0;
}
//---------------------------------------------------------------------------

void __fastcall SqueezeParams(void) {

  paras MapInfo; // holds all parameters - used for processing
  ClassPar *thisPar, *thisPar2;

  Global::MapParsPrj.clear();
  Global::MapParsPrj = Global::MapPars; // non squeezed for checking

// make multimap: keyed by parameter name holding pointer to parameter
  MapPar::iterator itPar; // iterator for Global::MapPars
  itPar = Global::MapPars.begin();
  while (itPar !=  Global::MapPars.end()) {
    thisPar = (*itPar).second;
    string S = ((*itPar).second)->param;
    Pairinfo Item = Pairinfo(S, Pinfo(new Classinfo(thisPar)));
    MapInfo.insert(Item);
    ++itPar;
  } // while

  paras::iterator itPar2, itPar3, itPar4;
  itPar2 = MapInfo.begin();
  pair<paras::iterator, paras::iterator> range;
  GrpParas Matched; // working matched parametrs multimap
  string Key; // key for eventual basin parameters
  MapPar MapParsNew; // holds final processed parameters

// process multimap by parameter name
  while (itPar2 !=  MapInfo.end()) {
    string S = (*itPar2).first;
    long thiscnt = MapInfo.count(S.c_str()); // # of occurrences of string S

// if duplicate parameter name from other module
    if(thiscnt > 1) {
      range = MapInfo.equal_range(S.c_str());
      long greatestCnt = 0;
      bool first = true;

      ClassPar *SharedPar = NULL; // set if Simple actual Basin parameter

// proceed through duplicate list
      for(itPar3 = range.first; itPar3 != range.second; itPar3++) {
        Classinfo *info3 = ((*itPar3).second).get();

        if(info3->rootinfo == NULL)
          info3->rootinfo = info3;

        thisPar = info3->thisPar;

        range.first++;

        if(info3->matched) // handled by earlier pass
          continue;

        PairPar Item = PairPar(thisPar->module, thisPar);
        Matched.insert(Item);

// compare with following duplicate entries
        for(itPar4 = range.first; itPar4 != range.second; itPar4++) {
          Classinfo *info4 = ((*itPar4).second).get();

          if(info4->matched) // skip if already matched
            continue;

          thisPar2 = info4->thisPar;

// check for duplicate values
          bool match = thisPar->Same(*thisPar2);

// if same values indicate could be merged
          if(match) {
            PairPar Item = PairPar(thisPar->module, thisPar2);
            Matched.insert(Item);
            info4->matched = true;
            if(++info3->rootinfo->cnt > greatestCnt){
              greatestCnt = info3->rootinfo->cnt;
              Key = info3->rootinfo->thisPar->module;
            } // update Key
          } // if(match)

        } // for(compare successively with first in range
      } // for(range of S)

      GrpParas::iterator itPar5;
      if(Matched.count(Key) > 1){
        pair<GrpParas::iterator, GrpParas::iterator> range2;
        range2 = Matched.equal_range(Key);
          bool first = true;
          for(itPar5 = range2.first; itPar5 != range2.second; itPar5++) {
            thisPar = (*itPar5).second;
// save module as shared parameters in MapPars and SharedMapPars
            if(first){
              thisPar->module = "Shared";
              PairPar Item = PairPar("Shared " + thisPar->param, thisPar);
              MapParsNew.insert(Item);
              Global::SharedMapPars.insert(Item);
              first = false;
            } // first
            else  // remove module parameters so as basin parameters visible
              delete thisPar;
            (*itPar5).second = NULL; // Indicate has been handled
        } // for(range of S)
      } // if(greatestCnt > 0)

      for(itPar5 = Matched.begin(); itPar5 != Matched.end(); itPar5++) {
        thisPar = (*itPar5).second;
        if(!thisPar) // already handled
          continue;
        PairPar Item = PairPar(thisPar->module + ' ' + thisPar->param, thisPar);
        MapParsNew.insert(Item);
      }
      Matched.clear();
    } // if(thiscnt > 1)
    else{
      Classinfo *info = ((*itPar2).second).get();
      thisPar = info->thisPar;
      PairPar Item = PairPar(thisPar->module + ' ' + thisPar->param, thisPar);
      MapParsNew.insert(Item);
    }
    MapInfo.erase(S.c_str());
    itPar2 = MapInfo.begin();
  } // while

  Global::MapPars.clear();
  Global::MapPars = MapParsNew;
}
//---------------------------------------------------------------------------

void __fastcall RprtHeader(TStringList *LogList, int LocalCnt){

  String Sx, Sy;

  ClassPar *thisPar;
  thisPar = ParFind("basin RUN_ID");

  long ID = 0;

  if(!thisPar){
    MapPar::iterator itPar;

    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
      thisPar = (*itPar).second;
      if(thisPar->param == "RUN_ID") {
        ID = thisPar->ivalues[0];
        break;
      }
    }
  }
  else
    ID = thisPar->ivalues[0];

  OpenNameReport = ProjectDirectory + "CRHM_output";
  if(ID >= 0){
    if(ID > 0)
      OpenNameReport += String("_") + ID;
    OpenNameReport += ".txt";
  }
  else if(ID < 0){
    ID = -ID;
    OpenNameReport = OpenNamePrj.SubString(1, OpenNamePrj.Length() -4) + String("_") + ID +".obs";
  }

  LogList->Add("Future File Description");

  for(int vv = 0; vv < LocalCnt; ++vv) {
    ClassVar *thisVar =  (ClassVar *) cdSeries[vv]->Tag;
    Sx = cdSeries[vv]->Title;
    Sx += String(" 1 ");
    Sx += thisVar->units.c_str();
    LogList->Add(Sx);
  }

  Sx = "##### time";
  for(int vv = 0; vv < LocalCnt; ++vv) {
    String S = cdSeries[vv]->Title;
    Sx += "\t" + S;
  }
  LogList->Add(Sx);
}

void __fastcall LastRprt(void)
{
  TStringList *LogList = new TStringList;

  RprtHeader(LogList, SeriesCnt);

  String Sx, Sy;

  int nn = cdSeries[0]->Count();

  Sx = FloatToStrF(cdSeries[0]->XValue(nn-1), ffGeneral, 10, 0);

  for (int vv = 0; vv < SeriesCnt; ++vv) {
    ClassVar *thisVar =  (ClassVar *) cdSeries[vv]->Tag;
    int prec = 6;
    if(thisVar->varType == CRHM::Int || thisVar->varType == CRHM::ReadI)
      prec = 4;

    Sy = FloatToStrF(cdSeries[vv]->YValue(nn-1), ffGeneral, prec, 0);

    Sx = Sx + "\t" + Sy;
  }

  LogList->Add(Sx);

  LogList->SaveToFile(OpenNameReport);
  LogList->Clear();
}
//---------------------------------------------------------------------------

void __fastcall AllRprt(void)
{
  TStringList *LogList = new TStringList;

  RprtHeader(LogList, SeriesCnt);

  String Sx, Sy;

  for(int nn = 0; nn < cdSeries[0]->Count(); ++nn){

    Sx = FloatToStrF(cdSeries[0]->XValue(nn), ffGeneral, 10, 0);

    for (int vv = 0; vv < SeriesCnt; ++vv) {
      if(cdSeries[0]->Count() == cdSeries[vv]->Count()){ // has to equal first series length
        ClassVar *thisVar =  (ClassVar *) cdSeries[vv]->Tag;
        int prec = 6;
        if(thisVar->varType == CRHM::Int || thisVar->varType == CRHM::ReadI)
          prec = 4;

        Sy = FloatToStrF(cdSeries[vv]->YValue(nn), ffGeneral, prec, 0);
        Sx = Sx + "\t" + Sy;
      }
    }

    LogList->Add(Sx);
  }

  LogList->SaveToFile(OpenNameReport);

  LogList->Clear();
}
//---------------------------------------------------------------------------

void __fastcall LastRprtObs(void)
{
  bool Daily = false;

  int SeriesCnt = ListBox4->Count;
  if(SeriesCnt <= 0) return;

  TSeries *cdS = (TSeries *) ListBox4->Objects[0];
  ClassVar *thisVar =  (ClassVar *) cdS->Tag;

  cdSeries = new TSeries*[SeriesCnt];

// can only do interval or daily at one time
  int Acnt = 0;
  for (int ii = 0; ii < SeriesCnt ; ++ii){
    cdSeries[Acnt] = (TSeries *) ListBox4->Objects[ii];
    ClassVar *thisVar =  (ClassVar *) cdSeries[Acnt]->Tag;
    if(ii == 0){
      if(thisVar->FunKind > MJ_W)
        Daily = true;
      ++Acnt;
    }
    else
      if(thisVar->FunKind > MJ_W && Daily || thisVar->FunKind <= MJ_W && !Daily)
        ++Acnt;
  }

  SeriesCnt = Acnt;
  TStringList *LogList = new TStringList;

  RprtHeader(LogList, SeriesCnt);

  String Sx, Sy;
  int nn = cdSeries[0]->Count();

  Sx = FloatToStrF(cdSeries[0]->XValue(nn-1), ffGeneral, 10, 0);

  for (int vv = 0; vv < SeriesCnt; ++vv) {
    ClassVar *thisVar =  (ClassVar *) cdSeries[vv]->Tag;
    int prec = 6;
    if(thisVar->varType == CRHM::Int || thisVar->varType == CRHM::ReadI)
      prec = 4;

    Sy = FloatToStrF(cdSeries[vv]->YValue(nn-1), ffGeneral, prec, 0);

    Sx = Sx + "\t" + Sy;
  }

  LogList->Add(Sx);

  delete [] cdSeries;
  cdSeries = NULL;

  LogList->SaveToFile(OpenNameReport);
  LogList->Clear();
}
//---------------------------------------------------------------------------

void __fastcall AllRprtObs(void){

  bool Daily = false;

  int SeriesCnt = ListBox4->Count;
  if(SeriesCnt <= 0) return;

  TSeries *cdS = (TSeries *) ListBox4->Objects[0];
  ClassVar *thisVar =  (ClassVar *) cdS->Tag;

  cdSeries = new TSeries*[SeriesCnt];

// can only do interval or daily at one time
  int Acnt = 0;
  for (int ii = 0; ii < SeriesCnt ; ++ii){
    cdSeries[Acnt] = (TSeries *) ListBox4->Objects[ii];
    ClassVar *thisVar =  (ClassVar *) cdSeries[Acnt]->Tag;
    if(ii == 0){
      if(thisVar->FunKind > MJ_W)
        Daily = true;
      ++Acnt;
    }
    else
      if(thisVar->FunKind > MJ_W && Daily || thisVar->FunKind <= MJ_W && !Daily)
        ++Acnt;
  }
  
  SeriesCnt = Acnt;

  TStringList *LogList = new TStringList;

  RprtHeader(LogList, SeriesCnt);

  String Sx, Sy;

  for(int nn = 0; nn < cdSeries[0]->Count(); ++nn){

    Sx = FloatToStrF(cdSeries[0]->XValue(nn), ffGeneral, 10, 0);

    for (int vv = 0; vv < SeriesCnt; ++vv) {
      ClassVar *thisVar =  (ClassVar *) cdSeries[vv]->Tag;
      int prec = 6;
      if(thisVar->varType == CRHM::Int || thisVar->varType == CRHM::ReadI)
        prec = 4;

      Sy = FloatToStrF(cdSeries[vv]->YValue(nn), ffGeneral, prec, 0);
      Sx = Sx + "\t" + Sy;
    }

    LogList->Add(Sx);
  }

  delete [] cdSeries;
  cdSeries = NULL;

  LogList->SaveToFile(OpenNameReport);
  LogList->Clear();
}
//---------------------------------------------------------------------------
void __fastcall RunClick(void){

  ClassVar *thisVar;
  float **mmsData;
  long **mmsDataL;
  bool GoodRun = true;

  if(Global::IndxMin != 0){
    if(Application->MessageBox("", "First observation day - not an entire day", MB_OK)) return;
    return;  // do not run
  }

  if(ListBox3->Count == 0){
    if(Application->MessageBox("", "No model output selected", MB_OK)) return;
    return;  // nothing selected
  }

  String Message = "Project file: " + OpenNamePrj;
  LogMessageX(Message.c_str());
  LogMessageX(" ");

  for(int ii = 0; ii < ObsFilesList->Count; ii++){
    Message = "Observation file: " + ObsFilesList->Strings[ii];
    LogMessageX(Message.c_str());
  }
  LogMessageX(" ");

  if(OpenStateFlag){
    Message = "State file: " + OpenNameState;
    LogMessageX(Message.c_str());
    LogMessageX(" ");
  }

  TDateTime Dt = TDateTime::CurrentDateTime();
  Message = "Time of model run: " + Dt.DateString() +  FormatDateTime(" hh:mm", Dt)
    + ". Program  " + "add revision";

  String S = String("Module List \"") ;
  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){
    ClassModule* thisModule = (ClassModule*) Global::OurModulesList->Objects[ii];
    S += Global::OurModulesList->Strings[ii];
    if(thisModule->variation != 0){
      String AA("#0");
      AA[2] += log(thisModule->variation)/log(2) + 1;
      S += AA;
    }
    if(ii == Global::OurModulesList->Count-1)
      S += ".\"";
    else
      S += ", ";
  }

  LogDebug(S.c_str());
  LogMessageX(" ");

  if(!Global::MapAKA.empty()) {
    Mapstr2::iterator it;
    LogMessageX("Linkage modifications (AKAs)");
    for (it = Global::MapAKA.begin(); it !=  Global::MapAKA.end(); ++it) {

      Message = String((*it).first.c_str()) + " " + String((*it).second.c_str());
      LogMessageX(Message.c_str());
    }
    LogMessageX(" ");
  }

  Global::DeclRootList->Clear(); // used by AKA to stop looping

// clears storage for observation read and function lists
  ((ClassModule*) Global::OurModulesList->Objects[0])->InitReadObs();

  double DTstartR = Picker1;
  double DTendR   = Picker2;

  ClassPar *thisPar;

  double P;
  thisPar = ParFind("basin RUN_START");
  if(thisPar){
    if(thisPar->ivalues[0] > 0)
      P = thisPar->ivalues[0];
  }
  else{
    MapPar::iterator itPar;

    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
      thisPar = (*itPar).second;
      if(thisPar->param == "RUN_START" && thisPar->ivalues[0] > 0) {
        P = thisPar->ivalues[0];
        break;
      }
    }
  }

  thisPar = ParFind("basin RUN_END");
  if(thisPar){
    if(thisPar->ivalues[0] > 0)
      P = thisPar->ivalues[0];
  }
  else{
    MapPar::iterator itPar;

    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
      thisPar = (*itPar).second;
      if(thisPar->param == "RUN_END" && thisPar->ivalues[0] > 0) {
        P = thisPar->ivalues[0];
        break;
      }
    }
  }

  Global::DTmin  = INT((DTstartR-Global::DTstart)* Global::Freq);
  Global::DTindx = Global::DTmin;
  Global::DTnow = Global::DTstart + Global::Interval*(Global::DTindx+1);

  int Modii;
  Global::MapVarsGet.clear();
  Global::MapVarsPut.clear();
  Global::MapObsGet.clear();

  try{
    for(Modii = 0; Modii < Global::OurModulesList->Count; Modii++)
      ((ClassModule*) (Global::OurModulesList->Objects[Modii]))->initbase();
  }
  catch (CRHMException Except){ // serious error - program had to stop immediately

    Application->MessageBox(Except.Message.c_str(),
      (String("Initialisation of module - ") + ((ClassModule*) Global::OurModulesList->Objects[Modii])->Name.c_str()).c_str(),
      MB_OK);
    GoodRun = false;
  }

  catch (Sysutils::Exception &E){
    ShowMessage(E.Message + " in Initialisation of " + ((ClassModule*) Global::OurModulesList->Objects[Modii])->Name.c_str());
    GoodRun = false;
  }

  if(!GoodRun){ // initialisation
    GoodRun = false;
  }
  else if(DTstartR >= DTendR) {
    Application->MessageBox("Start Time >= EndTime",
                              "Time Error", MB_OK);
    GoodRun = false;
  }

  if(!OpenStateFlag){
    thisPar = ParFind("basin INIT_STATE");
    if(thisPar && thisPar->Strings->Count && !thisPar->Strings->Strings[0].IsEmpty()){
      OpenNameState = thisPar->Strings->Strings[0].c_str();
      OpenStateFlag = true;
    }
    else{
      MapPar::iterator itPar;

      for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
        thisPar = (*itPar).second;
        if(thisPar->param == "INIT_STATE" && thisPar->Strings->Count && !thisPar->Strings->Strings[0].IsEmpty()) {
          OpenNameState = thisPar->Strings->Strings[0].c_str();
          OpenStateFlag = true;
          break;
        }
      }
    }
  }

  if(OpenStateFlag)
    ReadStateFile(GoodRun);

  if(!GoodRun) { //cleanup memory before returning

// deletes storage for observation read list
    ((ClassModule*) Global::OurModulesList->Objects[0])->InitReadObs();

// deletes module allocated storage
    for(int ii = 0; ii < Modii; ii++)
      ((ClassModule*) (Global::OurModulesList->Objects[ii]))->finish(false);

    Global::BuildFlag = CRHM::DECL;
    return;
  }

  Global::BuildFlag = CRHM::RUN;
  Global::DTmax  = INT((DTendR-Global::DTstart)* Global::Freq);

  SeriesCnt = ListBox3->Count;

  int Cnt = Global::DTmax - Global::DTmin;
  cdSeries = new TSeries*[SeriesCnt];

  for (int ii = 0; ii < SeriesCnt; ++ii)
    cdSeries[ii] = new TSeries(Cnt);

  mmsData = new float*[SeriesCnt];
  mmsDataL = new long*[SeriesCnt];

  for (int ii = 0; ii < ListBox3->Count; ii ++) {

    thisVar = (ClassVar *) (ListBox3->Objects[ii]);

    cdSeries[ii]->Tag = (int) thisVar;

    String S = ListBox3->Strings[ii];
    cdSeries[ii]->Title = S;

    long lay, dim;

    ExtractHruLay(S, dim, lay);

    if(thisVar->varType == CRHM::Float) {
      mmsDataL[ii] = NULL;
      if(thisVar->lay == 0){
        mmsData[ii]  = thisVar->values+(dim-1);
      }
      else {
        mmsData[ii]  = (thisVar->layvalues[lay-1])+(dim-1);
      }
    }
    else if(thisVar->varType == CRHM::Int) {
      mmsData[ii]  = NULL;
      if(thisVar->lay == 0){
        mmsDataL[ii] = thisVar->ivalues+(dim-1);
      }
      else {
        mmsDataL[ii] = (thisVar->ilayvalues[lay-1])+(dim-1);
      }
    }
  }

  bool First = true;

  LogMessageX(" ");
  S = String("timestep ") + Global::Interval*24 + " hr.";
  LogDebug(S.c_str());

  LogDebugT("\"start of run\".");
  LogMessageX(" ");

  try{
    for (Global::DTindx = Global::DTmin; Global::DTindx < Global::DTmax; Global::DTindx++) {

      if(Global::Freq == 1)
          Global::DTnow = Global::DTstart + Global::Interval*(Global::DTindx);
      else
          Global::DTnow = Global::DTstart + Global::Interval*(Global::DTindx+1);

// determine which obervation files have good data
      DoObsStatus(First);
// reads observations for current interval
//      ((ClassModule*) Global::OurModulesList->Objects[0])->ReadObs();
      bool Reset = true;
      for(Modii = 0; Modii < Global::OurModulesList->Count; Modii++){
        ClassModule *p = (ClassModule*) Global::OurModulesList->Objects[Modii];
        if((p->HRU_OBS)){
          p->ReadObs(Reset);
          Reset = false;
        }

        p->run();
      }

      double xx;
      for (int ii = 0; ii < SeriesCnt; ii++) {
        if(mmsData[ii] != NULL) {
          xx = *mmsData[ii];
          if(xx < xLimit)
            cdSeries[ii]->AddXY(Global::DTnow, xx);
        }
        else {
          xx = (*mmsDataL[ii]);
          if(xx < lLimit)
            cdSeries[ii]->AddXY(Global::DTnow, xx);
        }

      }

    } // end for

    Global::BuildFlag = CRHM::DECL;
  }

  catch (Sysutils::Exception &E){
    String S = E.Message + " at " +
      Global::DTnow.FormatString("yyyy'/'m'/'d hh':'nn") + " in '" + Global::OurModulesList->Strings[Modii] + "'";
    ShowMessage(S.c_str());
    LogError(S + " (" + FloatToStrF(Global::DTnow, ffGeneral	, 10, 0) + ")", ERR);
    GoodRun = false;
  }

  catch (CRHMException Except){
    String S = Except.Message.c_str() + String("at ") +
      Global::DTnow.FormatString("yyyy'/'m'/'d hh':'nn") + " in '" + Global::OurModulesList->Strings[Modii] + "'";
    ShowMessage(S.c_str());
    LogError(S + " (" + FloatToStrF(Global::DTnow, ffGeneral	, 10, 0) + ")", ERR);
    GoodRun = false;
  }

  delete[] mmsData;
  delete[] mmsDataL;

// deletes storage for observation read list
  ((ClassModule*) Global::OurModulesList->Objects[0])->InitReadObs();

// deletes module allocated storage
    for(int ii = 0; ii < Global::OurModulesList->Count; ii++)
      ((ClassModule*) (Global::OurModulesList->Objects[ii]))->finish(true);

  if(GoodRun) {
    LogDebugT("\"end of run\".");
    if(ReportAll)
      AllRprt();
    else
      LastRprt();
  }
}
//---------------------------------------------------------------------------

void __fastcall InitModules(void) {

  ClassVar *thisVar;

  Global::BuildFlag = CRHM::DECL;

// executes the DECL portion of the declvar/declparam etc. routines
  for(int ii = 0; ii < Global::OurModulesList->Count; ii++){
    ((ClassModule*) Global::OurModulesList->Objects[ii])->nhru = Global::nhru;
    ((ClassModule*) Global::OurModulesList->Objects[ii])->decl();
  }
  Label4Click();
}
//---------------------------------------------------------------------------

void __fastcall DoPrjOpen(void) {

  MapPar::iterator itPar;
  ClassPar *thisPar;
  ClassVar *thisVar;
  ifstream DataFile;
  long Variation;

  char module[80], param[80], Descrip[80], Line[80], name[80];
  string S, s;
  String SS;

  String Default = GetCurrentDir();

  int iFileHandle = FileOpen(OpenNamePrj, fmOpenRead);
  if(iFileHandle > -1){ // not file error
    int T = FileGetDate(iFileHandle);
    ProjectFileDate = FileDateToDateTime(T);
    FileClose(iFileHandle);
  }

  DataFile.open(OpenNamePrj.c_str());
  if(!DataFile) {
    Application->MessageBox("cannot open file", "File Error", MB_OK);
    return;
  }

  Dt0 = TDateTime::CurrentDateTime(); // used to calculate project load time

  bool Prj = (OpenNamePrj.LowerCase()).Pos(".prj");

  DataFile.getline(Descrip, 80);
  DataFile.ignore(80, '#');
  DataFile.getline(Line, 80);

  Global::MacroModulesList->Clear();

  try{

    do {
      DataFile >> S;
      if(DataFile.eof()) break;

      DataFile.ignore(80, '#');
      DataFile.getline(Line, 80);

      if(S == "AKAs:") {
        string module, type, name, alias, source;

        while(!DataFile.eof()) {
          DataFile >> type ;
          if(type[1] == '#') break;
          DataFile >> module >> name >> alias;

          TAKA Type = AKAtype(type);

          if(Type == VARG || Type == OBSR || Type == OBSF) {
            DataFile >> source;
            alias += ' ' + source;
          }

          if(Type != AKAERROR) {
            Pairstr2 Item = Pairstr2(type + " " + module + " " + name, alias);
            Global::MapAKA.insert(Item);
          }

          if(DataFile.eof()) return; // final exit

        }
      }
      else if(S == "Macros:") {
        getline(DataFile, S);

        while (S[1] != '#') {
          Global::MacroModulesList->Add((S.substr(1, S.length()-2)).c_str());
          getline(DataFile, S);
        }
        MacroLoad();
      }
      else if(S == "Observations:") {
        getline(DataFile, S);
        while(S[1] != '#'){
          SS = S.c_str();
          if(FindFileName(SS)){
            OpenNameObs = SS.c_str();

            if(!OpenObsFile(SS)) ;   // was return
          }
          else{
            Application->MessageBox(SS.c_str(), "Cannot find observation file", MB_OK);
          }
          getline(DataFile, S);
        }
      }
      else if(S == "Dates:") {
        int D[3];
        TDateTime DT;

        for (int ii = 0; ii < 3; ii++)
          DataFile >> D[ii];

        DT = EncodeDate((Word)D[0], (Word)D[1], (Word)D[2]);
          Picker1 = DT;

        int c;
        while((c = DataFile.peek(), c==32)) {
          DataFile.get();
          c = DataFile.peek();
        }

        if(isdigit(c) && ObsFilesList->Count == 0) {
            DataFile >> Global::Freq;
            Global::Interval = 1.0/Global::Freq;
        }
        else
            DataFile.ignore(256, '\n');

        for (int ii = 0; ii < 3; ii++)
          DataFile >> D[ii];

        DT = EncodeDate((Word)D[0], (Word)D[1], (Word)D[2]);
        Picker2 = DT;

       DataFile >> S;
      }
      else if(S == "Modules:") {
        Global::OurModulesList->Clear();

        for(;;) {
          getline(DataFile, S);
          if(S[1] == '#') break;

          bool InGrp = false;
          string::size_type idx = S.find('+');
          if(idx != string::npos){
            S = S.substr(idx+1);
            InGrp = true;
          }
          idx = S.find(' ');
          s = S.substr(0, idx);

          idx = S.find('#');
          if(idx != string::npos){
            Variation = pow(2, S[idx+1] - char('1'));
            s = S.substr(0, idx);
          }
          else
            Variation = 0;

          if(!InGrp)
            Global::OurModulesList->AddObject(s.c_str(), (TObject*) Variation);

          S = S.substr(idx+1);
          idx = S.rfind(' ');
          S = S.substr(0, idx);

          transform(S.begin(), S.end(), S.begin(), ::toupper);
          idx = S.rfind(".DLL");
        }



        for(int ii = Global::OurModulesList->Count-1; ii >= 0; --ii) {
          String Name = Global::OurModulesList->Strings[ii];
          int jj = Global::AllModulesList->IndexOf(Name);
          if(jj < 0) {
            CRHMException Except("Unknown Module: " + string(Name.c_str()), ERR);
            Application->MessageBox(Except.Message.c_str(),
                               "Unknown Module: incorrect CRHM version or DLL not loaded", MB_OK);
            LogError(Except);
            Global::OurModulesList->Delete(ii);

            DataFile.seekg(0, ios_base::end);  // cause break out
          }
          else{
            Variation = ((long) Global::OurModulesList->Objects[ii]);
            ((ClassModule*) Global::AllModulesList->Objects[jj])->variation = Variation;
            Global::OurModulesList->Objects[ii] = Global::AllModulesList->Objects[jj];
          }
        }

        InitModules();
      }
      else if(S == "Dimensions:") {
        DataFile >> S;
        long dim;
        while(S[1] != '#'){
          DataFile >> dim;

          if(S == "nhru") {
              Global::nhru = dim;
              Global::maxhru = dim;
          }
          else if(S == "nobs") {
              Global::nobs = dim;
              Global::maxobs = dim;
          }
          else if(S == "nlay") {
              Global::nlay = dim;
              Global::maxlay = dim;
          }
          DataFile >> S;
        }
      }
      else if(S == "Parameters:") {

        int c;
        long Cols;
        bool TooFewHRUs = false;
        string ss;

        while(!DataFile.eof()) {
          DataFile >> module;
          if(module[1] == '#') break;
          DataFile  >> param;
          if(DataFile.eof()) return; // final exit

          DataFile.ignore(80, '\n'); // need for character input, why?
          S = "";

          do { // determine # columns
            getline(DataFile, ss);
            S += ss + ' ';
            while(c = DataFile.peek(), iscntrl(c) || isspace(c))
              DataFile.get();

          } while(c = DataFile.peek(), !isalpha(c) && c != '#');

          string::iterator pos; // first handle single quotes
          bool inField = false;

          for(pos = S.begin(); pos != S.end(); ++pos){
            if(*pos == '\'')
              inField = !inField;
            if(inField && *pos == ' ')
              *pos = '_';
          }

          istringstream instr; // count columns
          instr.clear();
          instr.str(S);
          Cols = 0;
          for (;;) {
            instr >> s;
            if(instr.fail()) break;
              ++Cols; // # of HRU's in Basin
          }

          if(String(module) == "Shared" || String(module) == "basin") {
// write Shared parameters to module parameters
// all parameter values are set to basin values.  If re-defined in a module will be changed.
            MapPar::iterator itPar;
            for(itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); ++itPar){
              thisPar = (*itPar).second;
              if(thisPar->param == string(param) && (thisPar->dim == Cols)) // find module parameter for template thisPar->varType == CRHM::Int || thisPar->varType == CRHM::Float ||
                break;
              else { // Added to handle 2D parameters
                if(thisPar->param == string(param) && (thisPar->dim == Cols/thisPar->dim))
                  break;
                else
                  thisPar = NULL;
              }
            }
          }
          else
            thisPar = ClassParFind(module, param); // find module parameter for template

          if(thisPar) {
            ClassPar *newPar = new ClassPar(*thisPar);
            newPar->module = module; // set module name
            if(thisPar->varType == CRHM::Txt) {
              newPar->Strings->DelimitedText = S.c_str();
            }
            else {
              istringstream instr; // count columns
              instr.clear();
              instr.str(S);
              for(int jj = 0; jj<thisPar->lay; jj++) {
                for(int ii = 0; ii < newPar->dim; ii++) {

                  if(newPar->varType == CRHM::Float)
                    instr >> newPar->layvalues[jj][ii];
                  else if(newPar->varType == CRHM::Int) {
                    float x;
                    instr >> x;
                    newPar->ilayvalues[jj][ii] = x;
                  }
                }

                if(newPar->dim > Cols) {
                  if(!TooFewHRUs) {
                    Application->MessageBox("Too few HRUs defined in the Project file",
                                   "parameters not complete", MB_OK);
                    TooFewHRUs = true;
                  }

                  for(int ii = Cols; ii < newPar->dim; ii++)
                    if(newPar->varType == CRHM::Float)
                      newPar->layvalues[jj][ii] = newPar->layvalues[jj][ii-1];
                    else
                      newPar->ilayvalues[jj][ii] = newPar->ilayvalues[jj][ii-1];
                }
              }
            }
            if(String(module) == "Shared" || String(module) == "basin") {// Shared parameters first - initially over-write all others
              SetBasinParams(newPar); // copy template parameter to basin module
              delete newPar;
            }
            else
              ClassParSet(newPar);  // can delete newPar!
          }
          else {
              CRHMException Except("Unknown Module Parameter: " + string(module) + " -> "+ string(param) +
                " in " + string(OpenNamePrj.c_str()), ERR);
              Application->MessageBox(Except.Message.c_str(),
                                 "Unknown Parameter in project file", MB_OK);
              LogError(Except);

              while(c = DataFile.peek(), !isalpha(c) && c != '#')
                DataFile.ignore(256, '\n');
          }
          long cnt = Global::MapPars.size();
          DataFile.clear();
        } // while
        SqueezeParams();  // converts identical parameters to basin parameters
      }
      else if(S == "Display_Variable:") {
        while(!DataFile.eof()) {
          DataFile >> module;
          if(module[1] == '#') break;
          DataFile  >> name;
          if(DataFile.eof()) return; // final exit

          S = string(module) + ' ' +  string(name);
          long Index;
          string comma;
          thisVar = ClassVarFind(S);
          if(thisVar) {

            for( ; ; ) {
              DataFile >> Index;
              if(DataFile.fail()) break;

              if(Index < 0) {
                Index = labs(Index);
                thisVar->TchrtOpt = 1;
              }
              if(DataFile.peek() != ',')
                SS = String(thisVar->name.c_str()) + "(" + String(Index) + ")";
              else {
                DataFile >> comma;
                SS = String(thisVar->name.c_str()) + "(" + String(Index) + comma.c_str() + ")";
              }

              if(IndexOf(ListBox3, SS) == -1 && Index <= thisVar->dim)
                ListBox3->AddObject(SS, (TObject*) thisVar);
            } // for
          }
          else {
              CRHMException Except("Unknown Variable " + S +
                     " in " + string(OpenNamePrj.c_str()), ERR);
              Application->MessageBox(Except.Message.c_str(),
                                 "Unknown Variable in project file", MB_OK);
              LogError(Except);

              DataFile.ignore(256, '\n');
          }
          DataFile.clear();
        } // while
      }
      else if(S == "Display_Observation:") {

        while(!DataFile.eof()) {
          DataFile >> module;
          if(module[1] == '#') break;
          DataFile  >> name;
          if(DataFile.eof()) return; // final exit

          string Kind;
          long Index;

          S = string(module) + ' ' +  string(name);
          thisVar = ClassVarFind(S);

          if(thisVar && thisVar->FileData != NULL) {

            for(int ii = 0; ii < 100; ii++) {
              DataFile >> Index >> Kind;
              if(DataFile.fail()) break;

              if(Kind == "_obs") Kind = "";
              SS = String(thisVar->name.c_str()) + "(" + String(labs(Index)) +
                                                    ")" + Kind.c_str();
              if(IndexOf(ListBox4, SS) == -1) {

                TSeries *cdSeries;
                if(thisVar->FileData->Times == NULL){
//                  cdSeries = new TSeries(Global::DTmax - Global::DTmin);
                  double Dif = Picker2 - Picker1;
                  cdSeries = new TSeries(INT((Dif * thisVar->FileData->Freq))*thisVar->FileData->ModN);
                }
                cdSeries->Tag = (int) thisVar;

                cdSeries->Title = SS;

                ListBox4->AddObject(SS, (TObject *) cdSeries);
                AddObsPlot((ClassVar *) thisVar, cdSeries, SS,
                FindObservationType(Kind.c_str()));
              }
            }
          }
          else {
              CRHMException Except("Unknown Variable " + S +
                     " in " + string(OpenNamePrj.c_str()), ERR);
              Application->MessageBox(Except.Message.c_str(),
                                 "Unknown Variable in project file", MB_OK);
              LogError(Except);

              DataFile.ignore(256, '\n');
          }
          DataFile.clear();
        }
      }
      else if(S == "Initial_State") {
        getline(DataFile, S);
        if(S[1] != '#') {
          SS = S.c_str();
          if(FindFileName(SS)){
            OpenNameState = SS;
            OpenStateFlag = true;

          }
          else
            OpenNameState = "";

          DataFile.ignore(80, '#');
          DataFile >> S;
        }
      }
      else if(S == "Final_State") {
        getline(DataFile, S);
	      if(S[1] != '#') {
          DataFile >> S;
        }
      }
      else if(S == "Log_All") {
        ReportAll = true;
      }
      else if(S == "TChart:") {

        while(!DataFile.eof()){
          getline(DataFile, S);
          if(DataFile.eof()) break;
          if(S[1] == '#') break;
        }
      }
    }while(!DataFile.eof());
  }

  catch (CRHMException Except) {
    Application->MessageBox(Except.Message.c_str(), "Loading project Error", MB_OK);
    DataFile.close();
    return;
  }

  DataFile.close();
}
//---------------------------------------------------------------------------

void __fastcall PrjCloseClick(void){

  ObsCloseClick();       // remove any observations

  FreeChart1();          // remove series and clear ListBox4

  StateFileClose();

  ClearModules(true);   // remove any modules

  if(InitMacroCnt && InitModCnt){
    --InitModCnt;
    InitMacroCnt = 0;
  }
  AdminMacro.MacroClear();

  Global::OurModulesList->Clear();

  Global::MacroModulesList->Clear();

  Global::DeclRootList->Clear();

  Global::MapVars.clear();
  Global::MapVarsGet.clear();
  Global::MapVarsPut.clear();
  Global::MapObsGet.clear();
  Global::MapPars.clear();

  Global::MapAKA.clear();
}
//---------------------------------------------------------------------------

void __fastcall ClearModulesClick(void){

  ClearModules(true);
}
//---------------------------------------------------------------------------

void __fastcall FormActivate(void) {

  for(int pp = 0; pp < ParamCount(); ++pp) {
    String FileS = ParamStr(pp+1);
    if(FileExistsSp(FileS)) {
      if(LowerCase(ExtractFileExt(FileS)) == ".prj") {

        OpenNamePrj = FileS;

        DoPrjOpen();
      }
      else if(LowerCase(ExtractFileExt(FileS)) == ".obs") {
        TDateTime Dt = TDateTime::CurrentDateTime();

        OpenNameObs = FileS;
        OpenObsFile(FileS);

        int iFileHandle  = FileOpen(FileS, fmOpenRead);
        int T = FileGetDate(iFileHandle);
        ProjectFileDate = FileDateToDateTime(T);
        char Buf[121];
        FileRead(iFileHandle, Buf, 120);
        String C(Buf);
        int n = C.Pos("\r");
        C.SetLength(n-1);
        FileClose(iFileHandle);
      }
      else if(LowerCase(ExtractFileExt(FileS)) == ".par") {
        ifstream DataFile;
        int c, Cols;
        string ss;

        bool TooFewHRUs = false;
        string module, param, Descrip, Line, S, s;
        ClassPar *thisPar;

        OpenNamePar = FileS;
        String path = ExtractFilePath(AnsiReplaceStr(OpenNamePar, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
        if(path.IsEmpty()){
          path = GetCurrentDir();
          FileS = path + "\\" + FileS;
        }
        DataFile.open(OpenNamePar.c_str());
        if(!DataFile) {
          Application->MessageBox("cannot open file", "File Error", MB_OK);
          return;
        }

        getline(DataFile, Descrip);
        DataFile.ignore(80, '#');
        getline(DataFile, Line);

        RemoveBasinParams(); // change basin parameters to module parameters

        while(!DataFile.eof()) {
          DataFile.clear();

          DataFile >> module;
          if(module[1] == '#') break;
          DataFile  >> param;
          if(DataFile.eof()) return; // final exit

          DataFile.ignore(80, '\n'); // need for character input, why?
          S = "";

          do {
            getline(DataFile, ss);
            S += ss + ' ';
            while(c = DataFile.peek(), iscntrl(c) || isspace(c))
              DataFile.get();

          } while(c = DataFile.peek(), !isalpha(c) && c != '#' && !DataFile.eof());

          string::iterator pos; // first handle single quotes
          bool inField = false;

          for(pos = S.begin(); pos != S.end(); ++pos){
            if(*pos == '\'')
              inField = !inField;
            if(inField && *pos == ' ')
              *pos = '_';
          }

          istringstream instr; // count columns
          instr.clear();
          instr.str(S);
          Cols = 0;
          for (;;) {
            instr >> s;
          if(instr.fail()) break;
            ++Cols; // # of HRU's in Basin
          }

          if(module == "Shared") {
// write basin parameters to module parameters
// all parameter values are set to basin values.  If re-defined in a module will be changed.
            MapPar::iterator itPar;
            for(itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); ++itPar){
              thisPar = (*itPar).second;
              if(thisPar->param == string(param) && (thisPar->dim == Cols)) // find module parameter for template thisPar->varType == CRHM::Int || thisPar->varType == CRHM::Float ||
                break;
              else
                thisPar = NULL;
            }
          }
          else
            thisPar = ClassParFind(module, param); // find module parameter for template

          if(thisPar) {
            ClassPar *newPar = new ClassPar(*thisPar);
            newPar->module = module; // set module name
            if(thisPar->varType == CRHM::Txt) {
              newPar->Strings->DelimitedText = S.c_str();
            }
            else {
              istringstream instr; // count columns
              instr.clear();
              instr.str(S);
              for(int jj = 0; jj<thisPar->lay; jj++) {
                for(int ii = 0; ii < newPar->dim; ii++) {

                  if(newPar->varType == CRHM::Float)
                    instr >> newPar->layvalues[jj][ii];
                  else if(newPar->varType == CRHM::Int) {
                    float x;
                    instr >> x;
                    newPar->ilayvalues[jj][ii] = x;
                  }
                }

                if(newPar->dim > Cols) {
                  if(!TooFewHRUs) {
                    Application->MessageBox("Too few HRUs defined in the Project file",
                                   "parameters not complete", MB_OK);
                    TooFewHRUs = true;
                  }

                  for(int ii = Cols; ii < newPar->dim; ii++)
                    if(newPar->varType == CRHM::Float)
                      newPar->layvalues[jj][ii] = newPar->layvalues[jj][ii-1];
                    else
                      newPar->ilayvalues[jj][ii] = newPar->ilayvalues[jj][ii-1];
                }
              }
            }

            if(module == "Shared") {
              SetBasinParams(newPar); // copy template parameter to basin module
              delete newPar;
            }
            else
              ClassParSet(newPar);  // can delete newPar!
          }
          else {
              CRHMException Except("Unknown Module Parameter: " + string(module) + " -> "+ string(param) +
                " in " + string(OpenNamePrj.c_str()), ERR);
              Application->MessageBox(Except.Message.c_str(),
                                 "Unknown Parameter in project file", MB_OK);
              LogError(Except);

next:         DataFile.ignore(256, '\n');
              c = DataFile.peek();
              if(!isalpha(c) && c != '#') goto next;
          }
        } // while

        DataFile.close();

        SqueezeParams();  // converts identical parameters to basin parameters
      }
      else
          Application->MessageBox(String(FileS + " - file extension not 'prj', 'obs' or 'par'").c_str(), "Problem with File extension", MB_OK);
    }
    else
        Application->MessageBox(String(FileS + " - file does not exist").c_str(), "Problem with File", MB_OK);
  }  // for param

  if(!ListBox3->Count && ListBox4->Count){ // allows output of daily observations
    if(ReportAll)
      AllRprtObs();
    else
      LastRprtObs();
  }
  else{
		puts(Version.c_str());
    puts("");
    
		TDateTime Dt1 = TDateTime::CurrentDateTime();
		String Message = "Start time: " + Dt1.DateString()
			+ FormatDateTime(" hh:mm:ss", Dt1);
		puts(Message.c_str());
    puts("");

		RunClick();

		Message = "Project load time: " + FormatDateTime(" hh:mm:ss", Dt1-Dt0);
		puts(Message.c_str());

		TDateTime Dt2 = TDateTime::CurrentDateTime();

		Message = "Run time: " + FormatDateTime(" hh:mm:ss", Dt2-Dt1);
		puts(Message.c_str());

		Message = "End time: " + Dt2.DateString()
			+ FormatDateTime(" hh:mm:ss", Dt2);
		puts(Message.c_str());
  }
}
//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
  FormCreate();

  FormActivate();
  PrjCloseClick();
  FormDestroy();

  return 0;
}
