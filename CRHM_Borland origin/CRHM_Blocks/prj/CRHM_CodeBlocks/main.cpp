// 10/12/12
//---------------------------------------------------------------------------

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include "boost/shared_ptr.hpp"
#include "GlobalDll.h"
#include "ClassCRHM.h"
#include "ClassModule.h"
#include "NewModules.h"
#include "MacroUnit.h"
#include "Common.h"

//---------------------------------------------------------------------------

using namespace std;
/*
void puts(const char *S){
  cout << S << endl;
}*/

string Version = "Version: 4.7_16";

  class TSeries{
    public:
    double *XValues;
    float *YValues;
    int Tag;
    int MaxCnt;
    int Used;
    string Title;
    TSeries(int Cnt){ MaxCnt = Cnt; XValues = new double[MaxCnt]; YValues = new float[MaxCnt]; Used = 0;};
    ~TSeries(){delete[] XValues; delete[] YValues;};
    void AddXY(double X, float Y) {XValues[Used] = X; YValues[Used++] = Y;};
    int Count(void) {return Used;};
    double XValue(int nn) {return XValues[nn];};
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

  CRHM::TFun  FindObservationType(string Kind);

  string OpenNamePrj;
  string OpenNameState;
  string OpenNamePar;
  string OpenNameObs;
  string OpenNameReport;

  string ProjectDirectory;
  string ApplicationDir;

  TStringList *ListBox1;
  TStringList *ListBox2;
  TStringList *ListBox3;
  TStringList *ListBox4;

  TStringList *LoopList;

  TStringList *ObsFilesList;
  TStringList *ProjectList;

  bool OpenStateFlag;

  double ProjectFileDate;
  double Dt0; // used to calculate project load time

  int _matherr (struct _exception *a){
    char Error[][10] = {"NONE", "DOMAIN","SING","OVERFLOW","UNDERFLOW","TLOSS"};
    CRHMException Except((string(Error[a->type]) + " error in function '" + a->name + "' "), TERMINATE);
    throw Except;
  }

using namespace std;
using namespace CRHM;

extern double xLimit;
extern long lLimit;

bool ReportAll = true;
Administer AdminMacro("03/24/06", "Macro");

double Picker1; // replaces graphic controls
double Picker2;

Global global;

string Sstrings[] = {"", "_WtoMJ", "_MJtoW", "_Avg", "_Min", "_Max", "_Sum", "_Pos", "_Tot", "_Tot/Freq", "_First", "_Last"};

extern string AKAstrings[];

CRHM::TFun Funct = CRHM::FOBS;

int InitModCnt = 0;
int InitMacroCnt = 0;

ClassPar *StatePar = NULL; // used to handle basin StateVars_to_Handle

//---------------------------------------------------------------------------

void  LogMessageX(const char *S)
{
  puts(S);
}
//---------------------------------------------------------------------------

int  IndexOf(TStringList *Box, const string S){
  for(int ii = 0; ii < Box->Count; ++ii){
    if(Box->Strings[ii] == S)
    return ii;
  }
  return -1;
}
//---------------------------------------------------------------------------

void  ResetLoopList(void){ // writes to "CRHM_loop_output" and cleans up

  if(LoopList == NULL)
    return;

  ClassPar *thisPar = ParFind("basin RUN_ID");

  long ID = 0;

  if(!thisPar){
    MapPar::iterator itPar;

    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
      thisPar = (*itPar).second;
      if(thisPar->param == "RUN_ID" && thisPar->ivalues[0] > 0) {
        ID = thisPar->ivalues[0];
        break;
      }
    }
  }
  else
    ID = thisPar->ivalues[0];

  string FileName = "CRHM_loop_output";
  if(ID > 0)
    FileName += string("_"); //??? + ID;

  LoopList->SaveToFile(ProjectDirectory + "\\" + FileName + ".txt");

  delete LoopList;
  LoopList = NULL;
}
//---------------------------------------------------------------------------

void  ReadStateFile(bool & GoodRun)
{
  MapPar::iterator itVar;
  ClassVar *thisVar;

//  ifstream DataFile;
  char module[24], name[24], Descrip[80], Line[80];
  string S;
  ifstream DataFile(OpenNameState.c_str());
    if(!DataFile) {
      Message("cannot open file", "File Error");
      return;
    }

    DataFile.getline(Descrip, 80);
    DataFile.ignore(80, '#');
    DataFile.getline(Line, 80);

    DataFile.getline(Line, 80); // read "TIME:"
    int D[3];
    DataFile >> D[0] >> D[1] >> D[2];
    double DT = EncodeDateTime(D[0], D[1], D[2], 0, 0); // ????

    DataFile.getline(Descrip, 80);
    DataFile.ignore(80, '#');
    DataFile.getline(Line, 80);

    DataFile.getline(Line, 80); // read "Dimension:"
    long filehru, filelay;
    DataFile >> filehru >> filelay;
    if(filehru != Global::nhru || filelay != Global::nlay ){
      Message("State File and Model #HRU's or #LAY's are not equal", "File Error");
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
        Message((string("State File variable ") + S.c_str()).c_str(), "Unknown variable");
        DataFile.ignore(80, '#');
        DataFile.getline(Line, 80);
      }
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// On main runup, determines state variables to be saved from parameter "basin StateVars_to_Updatefills"VarPar" and
//  flags modules required to be run in Global::RunUpBitSet.
//
// On module, uses Global::ModuleBitSet to determine state variables to be saved from modules being executed.

void  ControlSaveState(bool MainLoop, ClassPar * VarPar, BitSet &Bit)
{
  TStringList *StateList;
  MapVar::iterator itVar;
  ClassVar * thisVar;
  StateList = new TStringList;
  string S;
  bool Needed;

  Global::RunUpBitSet.reset();

  bool Wild = false;
  if(VarPar && !VarPar->Strings->Strings[0].empty()) // first parameter determines the type
    Wild = VarPar->Strings->Strings[0].find("@") == string::npos;

  if( MainLoop)
    StateList->Add("Starting main run-up loop");
  else
    StateList->Add("starting module run-ahead to determine future variables");

  StateList->Add("######");

  StateList->Add("Time:");
  S = FormatString(Global::DTnow, "yyyy m d");
  StateList->Add(S);
  StateList->Add("######");

  StateList->Add("DTindx:");
  StateList->Add(DttoStr(Global::DTindx));
  StateList->Add("######");

  StateList->Add("CurrentModuleRun:");
  StateList->Add(DttoStr(Global::CurrentModuleRun));
  StateList->Add("######");

  StateList->Add("Dimension:");
  StateList->Add(longtoStr(Global::nhru) + " " + longtoStr(Global::nlay));
  StateList->Add("######");

  for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
    thisVar = (*itVar).second;
    Needed = false;

    if(thisVar->varType < CRHM::Read && thisVar->StatVar){ // Is state variable!

      if(!thisVar->InGroup || Global::ModuleBitSet[thisVar->InGroup-1])  // All variables in simple projects and module requested group projects
         Needed = true;
      else if(MainLoop){
        string namebasic = thisVar->name;
        if(VarPar->Strings->IndexOf(namebasic) > -1)
          Needed = true;
        else if(Wild){ // if Wild reduce parameter to root
          string::size_type Idx = namebasic.find("@");
          if(Idx != string::npos){
            namebasic = namebasic.substr(1, Idx-1);
            if(VarPar->Strings->IndexOf(namebasic) > -1)
              Needed = true;
          }
        } // wild!
        Global::RunUpBitSet[thisVar->InGroup-1] = true;
      } // MainLoop!
    } // state variable!

    if(Needed){
      S = thisVar->module + " " + thisVar->name;
      StateList->Add(S);
      S = "";
      if(thisVar->lay == 0)
        for(int ii = 0; ii < thisVar->dim; ii++) {
          if(thisVar->values != NULL)
            S = S + FloatToStrF(thisVar->values[ii], ffGeneral, 7, 0) + " ";
          else if(thisVar->ivalues != NULL)
            S = S + FloatToStrF(thisVar->ivalues[ii], ffGeneral, 7, 0) + " ";
          else
            S = S + "-0 ";

          if(ii%10 == 9) {
            StateList->Add(S);
            S = "";
          }
        }
      else
        for(int ll = 0; ll < thisVar->lay; ll++) {
          for(int ii = 0; ii < thisVar->dim; ii++) {
            if(thisVar->layvalues != NULL)
              S = S + FloatToStrF(thisVar->layvalues[ll][ii], ffGeneral, 4, 0) + " ";
            else if(thisVar->ivalues != NULL)
              S = S + FloatToStrF(thisVar->ilayvalues[ll][ii], ffGeneral, 4, 0) + " ";
            else
              S = S + "-0 ";

            if(ii%10 == 9) {
              StateList->Add(S);
              S = "";
            }
          }
          if(!S.empty()) StateList->Add(S);
          S = "";
        }
      if(!S.empty()) StateList->Add(S);
      StateList->Add("######");
    }
  }

  if(MainLoop)
    StateList->SaveToFile(ProjectDirectory + "\\" + "ControlStateFile.tmp1");
  else
    StateList->SaveToFile(ProjectDirectory + "\\" + "ControlStateFile.tmp2");

  delete StateList;
}
//---------------------------------------------------------------------------

void  ControlReadState(bool MainLoop, ClassPar * VarPar){

  MapPar::iterator itVar;
  ClassVar *thisVar;

  string Sy;
  string Sx;
  bool first = true;
  bool Wild = false;

  if(VarPar && !VarPar->Strings->Strings[0].empty()) // first parameter determines the type
    Wild = VarPar->Strings->Strings[0].find("@") == string::npos;

  ifstream DataFile;

  char module[80], name[80];
  string S, Descrip, Line;
    if(MainLoop)
      DataFile.open((ProjectDirectory + "\\" + "ControlStateFile.tmp1").c_str());
    else
      DataFile.open((ProjectDirectory + "\\" + "ControlStateFile.tmp2").c_str());

    if(!DataFile) {
    Message("cannot open file", "File Error");
    return;
    }

   getline(DataFile, Descrip);
    DataFile.ignore(180, '#');
    getline(DataFile, Line);

    getline(DataFile, Line); // read "TIME:"
    int D[3];
    DataFile >> D[0] >> D[1] >> D[2];

    DataFile.ignore(180, '#'); // not working?
    getline(DataFile, Line); // reads "#####"
    getline(DataFile, Line); // read "DTindx:"
    DataFile >> Global::DTindx;

    DataFile.ignore(180, '#'); // not working?
    getline(DataFile, Line); // reads "#####"
    getline(DataFile, Line); // read "CurrentModuleRun:"
    DataFile >> Global::CurrentModuleRun;

    getline(DataFile, Descrip);
    DataFile.ignore(180, '#');
    getline(DataFile, Line);

    getline(DataFile, Line); // read "Dimension:"
    long filehru, filelay;
    DataFile >> filehru >> filelay;

    DataFile.ignore(180, '#');
    getline(DataFile, Line);

    while(!DataFile.eof()) {
      DataFile >> module >> name;
      if(DataFile.fail()) break;

      DataFile.ignore();

      long exist = Global::OurModulesList->IndexOf(module);
      ClassModule*  mod;
      if(exist > -1)
        mod = (ClassModule*) Global::OurModulesList->Objects[exist];
      else {
        Message((string("State File module ") + module), "Unknown module");
        DataFile.ignore(180, '#');
        getline(DataFile, Line);
        continue;
      }

      S = string(module) + ' ' + string(name);
      thisVar = ClassVarFind(S);

      if(!thisVar)
        thisVar = ClassVarFind("#" + S);  // could be local variable

      if(!thisVar && mod->isGroup){
        string::size_type idx = S.find('@');
        if(idx == string::npos){
      string A;
      GroupEnding(A, mod->GroupCnt);
          S += A;
          thisVar = ClassVarFind(S);
        }
      }

      string namebasic = name;
      if(Wild){ // if Wild reduce parameter to root
        string::size_type Idx = namebasic.find("@");
        if(Idx != string::npos)
          namebasic = namebasic.substr(1, Idx-1);
      }

      if(thisVar) {

        if(VarPar && VarPar->Strings->IndexOf(namebasic) > -1){
          if(LoopList == NULL){
            LoopList = new TStringList;
            Sx = DttoStr(Global::DTnow);
            LoopList->Add(Sx);
          }
          if(first){
            Sx = "loop " + inttoStr(Global::LoopCnt - Global::LoopCntDown + 1) + "\t" + name;
            first = false;
          }
          else
            Sx += ("\t" + string(name));

// write data

          Sy ="";
          if(thisVar->lay == 0){
            for(int ii = 0; ii < thisVar->dim; ii++)
              if(thisVar->values != NULL){
                Sy += FloatToStrF(thisVar->values[ii], ffGeneral, 4, 0) + " ";
              }
              else if(thisVar->ivalues != NULL){
                Sy += FloatToStrF(thisVar->ivalues[ii], ffFixed, 0, 0) + " ";
              }
          }
          else {
            for(int ll = 0; ll < thisVar->lay; ll++)
              for(int ii = 0; ii < thisVar->dim; ii++)
                if(thisVar->layvalues != NULL){
                  Sy += FloatToStrF(thisVar->layvalues[ll][ii], ffGeneral, 4, 0) + " ";
                }
                else  if(thisVar->ivalues != NULL){
                  Sy += FloatToStrF(thisVar->ilayvalues[ll][ii], ffGeneral, 0, 0) + " ";
                }
          }

          Sx = Sx + "\t" + Sy;
        }
        else {
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
        }

        DataFile.ignore(180, '#');
        getline(DataFile, Line);
      }
      else {
        Message((string("State File variable ") + S), "Unknown variable");
        DataFile.ignore(180, '#');
        getline(DataFile, Line);
      }

    } // while

    if(MainLoop){
      bool Wild2 = false;
      ClassPar * TraceVarPar = ParFind("basin TraceVars");

      if(TraceVarPar && !TraceVarPar->Strings->Strings[0].empty()) // first parameter determines the type
        Wild2 = TraceVarPar->Strings->Strings[0].find("@") == string::npos;

      for(int ii = 0; ii < TraceVarPar->Strings->Count; ++ii){
        string Trimmed = trim(TraceVarPar->Strings->Strings[ii]);
        if(!Trimmed.empty()){
          int jj = ListBox1->IndexOf(Trimmed);
          if(jj > -1){
            for(int ii = 0; ii < Global::OurModulesList->Count; ii++) {
                ClassVar * thisVar = VarFind(string(Global::OurModulesList->Strings[ii]) + ' ' + TraceVarPar->Strings->Strings[0]);
                if(thisVar)
                  break;
            } // for

            thisVar = (ClassVar*) ListBox1->Objects[jj];
            if(thisVar){
              Sx += ("\t" + string(Trimmed));
              Sy ="";
              if(thisVar->lay == 0){
                for(int ii = 0; ii < thisVar->dim; ii++)
                  if(thisVar->values != NULL){
                    Sy += FloatToStrF(thisVar->values[ii], ffGeneral, 4, 0) + " ";
                  }
                  else if(thisVar->ivalues != NULL){
                    Sy += FloatToStrF(thisVar->ivalues[ii], ffFixed, 0, 0) + " ";
                  }
              }
              else {
                for(int ll = 0; ll < thisVar->lay; ll++)
                  for(int ii = 0; ii < thisVar->dim; ii++)
                    if(thisVar->layvalues != NULL){
                      Sy += FloatToStrF(thisVar->layvalues[ll][ii], ffGeneral, 4, 0) + " ";
                    }
                    else  if(thisVar->ivalues != NULL){
                      Sy += FloatToStrF(thisVar->ilayvalues[ll][ii], ffGeneral, 0, 0) + " ";
                    }
              }

              Sx = Sx + "\t" + Sy;
            }
          } // if
        }
      }
    }

    if(!Sx.empty())
      LoopList->Add(Sx);
}
//---------------------------------------------------------------------------

string  ExtractHruLay(string S, long &Hru, long &Lay){

  long jj = S.find("(");
  long jj1 = S.find(",");
  long jj2 = S.find(")");

  Lay = 0;
  if(jj1 > -1)
    Lay = Strtolong(S.substr(jj1+1, jj2-jj1-1));
  else
    jj1 = jj2;

  Hru = Strtolong((S.substr(jj+1, jj1-jj-1)));

  return S.substr(1, jj-1);
}
//---------------------------------------------------------------------------

void  FormCreate(void){

  Global::BuildFlag = CRHM::BUILD;

  Global::maxhru = 1;
  Global::maxlay = 1;
  Global::maxobs = 1;

  Global::Freq = 48;
  Global::Interval = 1.0/Global::Freq;

  cdSeries = NULL;

  double Dt = time(NULL);
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
  ((ClassModule*) Global::PendingDLLModuleList->Objects[0])->OurAdmin->Accept(mbYesToAll);
  ++InitModCnt;
}
//---------------------------------------------------------------------------

bool  OpenObsFile(string FileName)
{
  ClassData  * FileData;

//    if(ObsFilesList->IndexOf(FileName.c_str()) != -1)
//         return false;  // already open

    if(ObsFilesList->Count == 0) {
      Global::DTstart = 0; // used to flag first data file
      Global::DTend = 0; // used to flag first data file
    }

    FileData = new ClassData(FileName);

    if(FileData->Success) {

      if(ObsFilesList->Count == 0) {
        if(FileData->Times != NULL) { // handle sparse data
          Message("Sparse file cannot be first to be opened", "File order Error");
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
          if(IndexOf(ListBox2, thisVar->name) == -1)
            ListBox2->AddObject(thisVar->name, (TObject*) thisVar);
      }

      ObsFilesList->AddObject(OpenNameObs , (TObject *) FileData);

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

void  ObsCloseClick(void){

  ListBox2->Clear();


  for(int ii = 0; ii < ObsFilesList->Count; ii++) {
    ClassData * FileData = (ClassData *) ObsFilesList->Objects[ii];
    delete FileData;   // delete ClassData instance
  }
  ObsFilesList->Clear();  // clear list

  Global::nobs = 1;  // reset to 1

}
//---------------------------------------------------------------------------

void  ObsFileClose(void)
{
  MapVar::iterator itVar;
  ClassVar * thisVar;

  string S;  // Fix ???

  int Pos  = ObsFilesList->IndexOf(S);

  if(Pos == 0 && ObsFilesList->Count > 1) {
    ObsCloseClick();
    return;
  }

    ListBox2->Clear();

    ClassData * FileData = (ClassData *) ObsFilesList->Objects[Pos];
    delete FileData;   // delete ClassData instance
    ObsFilesList->Delete(Pos);  // delete entry in list

    for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
      thisVar = (*itVar).second;
      if(thisVar->varType >= CRHM::Read)
	if(IndexOf(ListBox2, (*itVar).second->name) == -1)
          ListBox2->AddObject((*itVar).second->name,
            (TObject*) (*itVar).second);
    }

    for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
      thisVar = (*itVar).second;
      if(thisVar->varType < CRHM::Read && thisVar->visibility == CRHM::VARIABLE)
	if(IndexOf(ListBox1, (*itVar).second->name) == -1)
	  ListBox1->AddObject((*itVar).second->name, (TObject*) (*itVar).second);
    }
}
//---------------------------------------------------------------------------

void  FormDestroy(void)
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

void  FreeChart1(void)
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

void  ClearModules(bool All){

  ModVarRemove(Global::MapVars);

  Global::SharedMapPars.clear();

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

void  UpdateDim(CRHM::TDim Dim, long dim){

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

void  RemoveBasinParams(void){ // pseudo shared parameters

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

void  SetBasinParams(ClassPar *basinPar){

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

  void  DoObsStatus(bool &First){

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

  string  HRUStoString(string S){ // handles observations too!

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

void MacroLoad(void)
{
  Global::GroupCntTrk = 0;
  Global::StructCntTrk = 0;
  int Macro = 0;

  if(Global::MacroModulesList->Count > 0) {

    while (Global::MacroModulesList->Count-1 > Macro) {

      string s = Global::MacroModulesList->Strings[Macro];
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

      string S, SS;

      while(S = trim(Global::MacroModulesList->Strings[Macro]), SS = S.substr(0,3),
              !(SS == "end" &&
              (S.length() == 3 || S.find_first_of(" /") != string::npos)) &&
              Global::MacroModulesList->Count > Macro
            )

        ++Macro;

      ++Macro;
    }

    AdminMacro.LoadCRHM("Macro");
    AdminMacro.Accept(mbYesToAll);

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

bool  FileExistsSp(string FileName) {

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

bool  FindFileName(string &FileName) {

string FilePart;

//ApplicationDir = ExtractFilePath(AnsiReplaceStr(Application->ExeName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
//ProjectDirectory = ExtractFilePath(AnsiReplaceStr(OpenNamePrj, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples

  if(FileExistsSp(FileName)) // file path directory
    return true;

  string::size_type Pos = FileName.find_last_of("\\/" );
  if(Pos){
    FilePart = FileName.substr(Pos+1, FileName.length());

    if(FileExistsSp(FilePart)){ // current directory
      FileName = FilePart;
      return true;
    }
  }
  else
    FilePart = FileName;

// original file may now be in project directory
  string NewFileName = ProjectDirectory + FilePart;
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

void  ListBoxMacroClear(void){ // used by Macro

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
void  StateFileClose(void)
{
  OpenNameState = "";
  OpenStateFlag = false;
}
//---------------------------------------------------------------------------

string  DeclObsName(ClassVar *thisVar){

  string Newname = thisVar->name;
  int jj = Global::OurModulesList->IndexOf(thisVar->module); // find module
  if(jj > -1 && Newname.rfind("#") != string::npos){ // -1 for "obs" and "#" for declared "obs"
    ClassModule* thisModule = (ClassModule*) Global::OurModulesList->Objects[jj];
    if(thisModule->isGroup){ // if group add suffix
      string AA("@@");
      AA[1] += thisModule->GroupCnt;
      Newname += AA;
    }
  }
  return Newname;
}
//---------------------------------------------------------------------------

bool  isSimple(string module){ // determines if Simple or Group/Struct module

  int jj = Global::AllModulesList->IndexOf(module);
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

void  Label4Click(void){

  ClassVar *thisVar;
  MapVar::iterator itVar;
  string Newname;

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

CRHM::TFun  FindObservationType(string Kind){

  if(Kind == "_obs") Kind = "";
  for(int ii = CRHM::FOBS; ii <= CRHM::LAST; ii++)
    if(Kind == Sstrings[ii]) return (CRHM::TFun)ii;
  return (CRHM::TFun) 0;
}
//---------------------------------------------------------------------------

void  SqueezeParams(void) {

  paras MapInfo; // holds all parameters - used for processing
  ClassPar *thisPar, *thisPar2;

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
    long thiscnt = MapInfo.count(S); // # of occurrences of string S

// if duplicate parameter name from other module
    if(thiscnt > 1) {
      range = MapInfo.equal_range(S);
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
    MapInfo.erase(S);
    itPar2 = MapInfo.begin();
  } // while

  Global::MapPars.clear();
  Global::MapPars = MapParsNew;
}
//---------------------------------------------------------------------------

void  RprtHeader(TStringList *LogList, int LocalCnt){

  string Sx, Sy;

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

  OpenNameReport = ProjectDirectory + "\\CRHM_output";
  if(ID >= 0){
    if(ID > 0){
      OpenNameReport += "_";
      OpenNameReport += inttoStr(ID);
    }
    OpenNameReport += ".obs";
  }
  else if(ID < 0){
    ID = -ID;
    OpenNameReport = OpenNamePrj.substr(0, OpenNamePrj.length() -4) + "_" + longtoStr(ID) + ".obs";
  }

  LogList->Add("Future File Description");

  for(int vv = 0; vv < LocalCnt; ++vv) {
    ClassVar *thisVar =  (ClassVar *) cdSeries[vv]->Tag;
    Sx = cdSeries[vv]->Title;
    Sx += string(" 1 ");
    Sx += thisVar->units;
    LogList->Add(Sx);
  }

  Sx = "##### time";
  for(int vv = 0; vv < LocalCnt; ++vv) {
    string S = cdSeries[vv]->Title;
    Sx += "\t" + S;
  }
  LogList->Add(Sx);
}

void  LastRprt(void)
{
  TStringList *LogList = new TStringList;

  RprtHeader(LogList, SeriesCnt);

  string Sx, Sy;

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

void  AllRprt(void)
{
  TStringList *LogList = new TStringList;

  RprtHeader(LogList, SeriesCnt);

  string Sx, Sy;

  for(int nn = 0; nn < cdSeries[0]->Count(); ++nn){

    Sx = FloatToStrF(cdSeries[0]->XValue(nn), ffGeneral, 10, 0);

    for (int vv = 0; vv < SeriesCnt; ++vv) {
      if(cdSeries[0]->Count() == cdSeries[vv]->Count()){ // has to equal first series length
        ClassVar *thisVar =  (ClassVar *) cdSeries[vv]->Tag;
        int prec = 7;
        if(thisVar->varType == CRHM::Int || thisVar->varType == CRHM::ReadI)
          prec = 7;

        Sy = FloatToStrF(cdSeries[vv]->YValue(nn), ffGeneral, prec, 10);
        Sx = Sx + "\t" + Sy;
      }
    }

    LogList->Add(Sx);
  }

  LogList->SaveToFile(OpenNameReport);

  LogList->Clear();
}
//---------------------------------------------------------------------------

void  LastRprtObs(void)
{
  bool Daily = false;

  int SeriesCnt = ListBox4->Count;
  if(SeriesCnt <= 0) return;

//  TSeries *cdS = (TSeries *) ListBox4->Objects[0];
//  ClassVar *thisVar =  (ClassVar *) cdS->Tag;

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

  string Sx, Sy;
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

void  AllRprtObs(void){

  bool Daily = false;

  int SeriesCnt = ListBox4->Count;
  if(SeriesCnt <= 0) return;

//  TSeries *cdS = (TSeries *) ListBox4->Objects[0];
//  ClassVar *thisVar =  (ClassVar *) cdS->Tag;

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

  string Sx, Sy;

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
void  RunClick(void){

  ClassVar *thisVar;
  float **mmsData;
  long **mmsDataL;
  bool GoodRun = true;

  if(Global::IndxMin != 0){
    Message("", "First observation day - not an entire day");
    return;  // do not run
  }

  if(ListBox3->Count == 0){
    Message("", "No model output selected");
    return;  // nothing selected
  }

  string Message = "Project file: " + OpenNamePrj;
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

  double Dt = DateTimeDt();
  Message = string("Time of model run: ") + DttoStr(Dt) + " " +  FormatString(Dt, "yy mm dd ") + ". Program " + Version;
  LogMessageX(Message.c_str());

  string S = string("Module List \"") ;
  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){
    ClassModule* thisModule = (ClassModule*) Global::OurModulesList->Objects[ii];
    S += Global::OurModulesList->Strings[ii];
    if(thisModule->variation != 0){
      string AA("#0");
      AA[1] += log(thisModule->variation)/log(2) + 1;
      S += AA;
    }

    if(ii == Global::OurModulesList->Count-1)
      S += ".\"";
    else
      S += ", ";
  }

  if(!Global::MapAKA.empty()) {
    Mapstr2::iterator it;
    LogMessageX("Linkage modifications (AKAs)");
    for (it = Global::MapAKA.begin(); it !=  Global::MapAKA.end(); ++it) {

      Message = string((*it).first.c_str()) + " " + string((*it).second.c_str());
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

  Global::DTmin  = (int) ((DTstartR-Global::DTstart)* Global::Freq);
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

    LogMessageX(Except.Message.c_str()); // , "Initialisation of module - "); // + string((ClassModule*) Global::OurModulesList->Objects[Modii])->Name)
    GoodRun = false;
  }

  catch (exception &E){
//    ShowMessage(E.Message + " in Initialisation of " + ((ClassModule*) Global::OurModulesList->Objects[Modii])->Name);
    LogMessageX(E.what());
    GoodRun = false;
  }

  catch(...){
    LogMessageX("Unknown error");
    GoodRun = false;
}

  if(DTstartR >= DTendR) {
    LogMessageX("Start Time >= EndTime");
    GoodRun = false;
  }

  ClassData * FileData = (ClassData *) ObsFilesList->Objects[0];

  if(DTstartR < FileData->Dt1) {
    LogMessageX("Start Time before first Observation");
    GoodRun = false;
  }

  if(DTendR > FileData->Dt2) {
    LogMessageX("End Time after last Observation");
    GoodRun = false;
  }

  if(GoodRun) {
    if(!OpenStateFlag){
      thisPar = ParFind("basin INIT_STATE");
      if(thisPar && thisPar->Strings->Count && !thisPar->Strings->Strings[0].empty()){
        OpenNameState = thisPar->Strings->Strings[0];
        OpenStateFlag = true;
      }
      else{
        MapPar::iterator itPar;

        for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
          thisPar = (*itPar).second;
          if(thisPar->param == "INIT_STATE" && thisPar->Strings->Count && !thisPar->Strings->Strings[0].empty()) {
            OpenNameState = thisPar->Strings->Strings[0];
            OpenStateFlag = true;
            break;
          }
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
  Global::DTmax  = (int) ((DTendR-Global::DTstart)* Global::Freq);

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

    string S = ListBox3->Strings[ii];
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
  S = string("timestep ") + DttoStr(Global::Interval*24) + " hr.";
  LogDebug(S.c_str());

  LogDebugT("\"start of run\".");
  LogMessageX(" ");

  Global::CRHMControlSaveCnt = 0; // set by module
  Global::CRHMStatus = 0; // module status; module control = 1 , main control = 2 and Finished = 4. Both inhibit output.
  Global::LoopCntDown = -1;
  StatePar = NULL;
  Global::ModuleBitSet.reset();

  try{
    for (Global::DTindx = Global::DTmin; Global::DTindx < Global::DTmax; Global::DTindx++) {

      if(Global::Freq == 1)
          Global::DTnow = Global::DTstart + Global::Interval*(Global::DTindx);
      else
          Global::DTnow = Global::DTstart + Global::Interval*(Global::DTindx+1);

      if((double) Global::RapidAdvanceTo > 0.0 && !(Global::CRHMStatus & 4)){
        if(Global::DTnow < Global::RapidAdvanceTo)
          Global::CRHMStatus |= 2; // set module control and inhibit display

        else if(Global::DTnow == Global::RapidAdvanceTo+Global::Interval && !Global::LoopCnt){ // reached RapidAdvanceTo and NO looping.
            Global::CRHMStatus &=125; // clear status == 2 (main control) and resume display
            LogMessage("Terminate fast loop aheadMain", DD);
        }
        else if(Global::DTnow == Global::RapidAdvanceTo && Global::LoopCnt){ // reached RapidAdvanceTo with looping.
          if(Global::LoopCntDown == -1){ // first time
            Global::LoopCntDown = Global::LoopCnt;
            StatePar = ParFind("basin StateVars_to_Update");
            ControlSaveState(true, StatePar, Global::RunUpBitSet); // save this position
            LogMessage("Initialise LoopTo Main", DD);
          }
        }
        else if(Global::DTnow == Global::LoopTo && Global::LoopCnt){ // reached LoopTo position
            ControlReadState(true, StatePar); // return to earlier position
            --Global::LoopCntDown; // after above ReadState
            LogMessage("Reached loop Main", DD);
            if(Global::LoopCntDown <= 0){
              ResetLoopList();
              Global::CRHMStatus &=125; // remove status == 2 (inhibit display)
              Global::CRHMStatus |= 4; // flag done
              Global::LoopCntDown = -1;
              LogMessage("Terminate LoopTo Main", DD);
              continue;
            }
        }
      } // end of RapidAdvanceTo logic

// determine which obervation files have good data
      DoObsStatus(First);
// reads observations for current interval

      bool Reset = true;
      for(Global::CurrentModuleRun = 0; Global::CurrentModuleRun < Global::OurModulesList->Count; Global::CurrentModuleRun++){
        long Last = Global::CRHMControlSaveCnt;

        ClassModule *p = (ClassModule*) Global::OurModulesList->Objects[Global::CurrentModuleRun];
// Simple project for module obs. For group always when !CRHMStatus otherwise only selected groups

        if(!p->isGroup || !Global::CRHMStatus || (Global::CRHMStatus & 1 && Global::ModuleBitSet[Global::CurrentModuleRun])){
          p->ReadObs(Reset);
          Reset = false;

          p->run();
        }

// module flag loop

        if(Last != Global::CRHMControlSaveCnt) // means last module/group
          Global::ModuleBitSet.set(Global::CurrentModuleRun);

      } // end for

// module loop control

      if(Global::CRHMControlSaveCnt && !(Global::CRHMStatus & 1)){ // Set module mode. Save current position.
          ControlSaveState(false, StatePar, Global::ModuleBitSet);
          Global::CRHMStatus |= 1; // set module control bit and inhibit display.
          LogMessage("Start save Main", DD);
      }

// module loop control reset
      bool DoOutput = true;
      if((Global::CRHMStatus & 1) && (!Global::CRHMControlSaveCnt || Global::DTindx >= Global::DTmax-1)){ // handles daily + last day of run
        ControlReadState(false, NULL); // restore all
        Global::CRHMStatus &= 126; // reset module mode.
        Global::CRHMControlSaveCnt = 0; // required for Global::DTindx >= Global::DTmax-1 condition
        LogMessage("End save Main", DD);
        LogDebug(" ");

        if(Global::Freq == 1){
            Global::DTnow = Global::DTstart + Global::Interval*(Global::DTindx);
            Global::DTindx -=1;
        }
        else{
            Global::DTnow = Global::DTstart + Global::Interval*(Global::DTindx+1);
            Global::DTindx -=1;
        }

        DoOutput = false;
      }

      if(!(Global::CRHMStatus & 3) && !(Global::CRHMControlSaveCnt) && DoOutput){ // display if not module or main controlled. why?

        double xx;
        for (int ii = 0; ii < SeriesCnt; ii++) {
          if(mmsData[ii] != NULL) {
            xx = *mmsData[ii];
            if(xx < xLimit)
              cdSeries[ii]->AddXY(Global::DTnow, xx);
            else
              cdSeries[ii]->AddXY(Global::DTnow, -9999);
          }
          else {
            xx = (*mmsDataL[ii]);
            if(xx < lLimit)
              cdSeries[ii]->AddXY(Global::DTnow, xx);
            else
              cdSeries[ii]->AddXY(Global::DTnow, -9999);
          }

        }
      }

    } // end for

    Global::BuildFlag = CRHM::DECL;
  }

  catch (exception &E){
//    string S = E.Message + " at " + FormatString(Global::DTnow, "yyyy'/'m'/'d hh':'nn") + " in '" + Global::OurModulesList->Strings[Modii] + "'";
//    ShowMessage(S);
    LogError(S + " (" + FloatToStrF(Global::DTnow, ffGeneral	, 10, 0) + ")", ERR);
    GoodRun = false;
  }
/*
  catch (CRHMException Except){
    string S = Except.Message + string("at ") +
      FormatString(Global::DTnow, "yyyy'/'m'/'d hh':'nn") + " in '" + Global::OurModulesList->Strings[Modii] + "'";
    Message(S.c_str(), string("").c_str();
    LogError(S + " (" + FloatToStrF(Global::DTnow, ffGeneral	, 10, 0) + ")", ERR);
    GoodRun = false;
  }*/

  Dt = DateTimeDt();
  Message = string("End of model run: ") + DttoStr(Dt) +  " " +  FormatString(Dt, "yy mm dd ") + ". Program " + Version;
  LogMessageX(Message.c_str());

  delete[] mmsData;
  delete[] mmsDataL;

// deletes storage for observation read list
  ((ClassModule*) Global::OurModulesList->Objects[0])->InitReadObs();

// deletes module allocated storage
    for(int ii = 0; ii < Global::OurModulesList->Count; ii++)
      ((ClassModule*) (Global::OurModulesList->Objects[ii]))->finish(true);

  if(GoodRun) {
//    LogDebugT("\"end of run\".");
    if(ReportAll)
      AllRprt();
    else
      LastRprt();
  }
}
//---------------------------------------------------------------------------

void  InitModules(void) {

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

void  DoPrjOpen(void) {

  MapPar::iterator itPar;
  ClassPar *thisPar;
  ClassVar *thisVar;
  ifstream DataFile;
  long Variation;

  char module[80], param[80], Descrip[80], Line[80], name[80];
  string S, s;
  string SS;

//  string Default = GetCurrentDir();
/*
  int iFileHandle = FileOpen(OpenNamePrj, fmOpenRead);
  if(iFileHandle > -1){ // not file error
    int T = FileGetDate(iFileHandle);
    ProjectFileDate = FileDateToDateTime(T);
    FileClose(iFileHandle);
  }*/

  DataFile.open(OpenNamePrj.c_str());
  if(!DataFile) {
    Message("cannot open file", "File Error");
    return;
  }

  ProjectDirectory = GetCurrentPath();

  Dt0 = time(NULL); // used to calculate project load time

  bool Prj = lowercase(OpenNamePrj).find(".prj") != string::npos;

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

        while (S[0] != '#') {
          string sub = S.substr(1, S.length()-2);
          Global::MacroModulesList->Add(sub);
          getline(DataFile, S);
        }
        MacroLoad();
      }
      else if(S == "Observations:") {
        getline(DataFile, S);
        while(S[0] != '#'){
          SS = S;
          if(FindFileName(SS)){
            OpenNameObs = SS;

            if(!OpenObsFile(SS)) ;   // was return
          }
          else{
            Message(SS.c_str(), "Cannot find observation file");
          }
          getline(DataFile, S);
        }
      }
      else if(S == "Dates:") {
        int D[3];
        double DT;

        for (int ii = 0; ii < 3; ii++)
          DataFile >> D[ii];

        DT = EncodeDateTime((int)D[0], (int)D[1], (int)D[2], 0, 0); // check
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

        DT = EncodeDateTime((int)D[0], (int)D[1], (int)D[2], 0, 0);
        Picker2 = DT;

       DataFile >> S;
      }
      else if(S == "Modules:") {
        Global::OurModulesList->Clear();

        for(;;) {
          getline(DataFile, S);
          if(S[0] == '#') break;

          bool InGrp = false;
          long idx = S.find('+');
          if(idx != -1){
            S = S.substr(idx+1);
            InGrp = true;
          }
          idx = S.find(' ');
          s = S.substr(0, idx);

          idx = S.find('#');
          if(idx != -1){
            Variation = pow(2, S[idx+1] - char('1'));
            s = S.substr(0, idx);
          }
          else
            Variation = 0;

          if(!InGrp)
            Global::OurModulesList->AddObject(s, (TObject*) Variation);

          idx = S.find(' ');
          S = S.substr(idx+1);
          idx = S.rfind(' ');
          S = S.substr(0, idx);

          transform(S.begin(), S.end(), S.begin(), ::toupper);
          idx = S.rfind(".DLL");
        }

        for(int ii = Global::OurModulesList->Count-1; ii >= 0; --ii) {
          string Name = Global::OurModulesList->Strings[ii];
          int jj = Global::AllModulesList->IndexOf(Name);
          if(jj < 0) {
            CRHMException Except("Unknown Module: " + string(Name.c_str()), ERR);
            Message(Except.Message.c_str(),
                               "Unknown Module: incorrect CRHM version or DLL not loaded");
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
        while(S[0] != '#'){
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
            if(instr.fail())
              break;
              ++Cols; // # of HRU's in Basin
          }

          if(string(module) == "Shared" || string(module) == "basin") {
// write Shared parameters to module parameters
// all parameter values are set to basin values.  If re-defined in a module will be changed.
            MapPar::iterator itPar;
            for(itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); ++itPar){
              thisPar = (*itPar).second;
              if(thisPar->param == string(param) && (thisPar->varType == CRHM::Txt)) // find module parameter for template thisPar->varType == CRHM::Int || thisPar->varType == CRHM::Float ||
                break;
              else if(thisPar->param == string(param) && (thisPar->dim == Cols)) // find module parameter for template thisPar->varType == CRHM::Int || thisPar->varType == CRHM::Float ||
                break;
              else if(thisPar->param == string(param) && (thisPar->dim == Cols/thisPar->dim))
                break;
              else
                thisPar = NULL;
            }
          }
          else
            thisPar = ClassParFind(module, param); // find module parameter for template

          if(thisPar) {
            ClassPar *newPar = new ClassPar(*thisPar);
            newPar->module = string(module); // set module name
            if(thisPar->varType == CRHM::Txt) {
              newPar->Strings->DelimitedText(S);
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
                    Message("Too few HRUs defined in the Project file", "parameters not complete");
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
            if(string(module) == "Shared" || string(module) == "basin") {// Shared parameters first - initially over-write all others
              SetBasinParams(newPar); // copy template parameter to basin module
              delete newPar;
            }
            else
              ClassParSet(newPar);  // can delete newPar!
          }
          else {
              CRHMException Except(string("Unknown Module Parameter: ") + module + " -> "+ param + " in " + OpenNamePrj, ERR);
              Message(Except.Message, "Unknown Parameter in project file");
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
                SS = thisVar->name + "(" + longtoStr(Index) + ")";
              else {
                DataFile >> comma;
                SS = thisVar->name + "(" + longtoStr(Index) + comma + ")";
              }

              if(IndexOf(ListBox3, SS) == -1 && Index <= thisVar->dim)
                ListBox3->AddObject(SS, (TObject*) thisVar);
            } // for
          }
          else {
              CRHMException Except("Unknown Variable " + S +
                     " in " + string(OpenNamePrj.c_str()), ERR);
              Message(Except.Message.c_str(),
                                 "Unknown Variable in project file");
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
              SS = thisVar->name + "(" + longtoStr(labs(Index)) + ")" + Kind;
              if(IndexOf(ListBox4, SS) == -1) {

                TSeries *cdSeries;
                if(thisVar->FileData->Times == NULL){
//                  cdSeries = new TSeries(Global::DTmax - Global::DTmin);
                  double Dif = Picker2 - Picker1;
                  cdSeries = new TSeries(((int)(Dif * thisVar->FileData->Freq))*thisVar->FileData->ModN);
                }
                cdSeries->Tag = (int) thisVar;

                cdSeries->Title = SS;

                ListBox4->AddObject(SS, (TObject *) cdSeries);
//                AddObsPlot((ClassVar *) thisVar, cdSeries, SS,
//                FindObservationType(Kind.c_str()));
              }
            }
          }
          else {
              CRHMException Except("Unknown Variable " + S +
                     " in " + string(OpenNamePrj.c_str()), ERR);
              Message(Except.Message.c_str(),
                                 "Unknown Variable in project file");
              LogError(Except);

              DataFile.ignore(256, '\n');
          }
          DataFile.clear();
        }
      }
      else if(S == "Initial_State") {
        getline(DataFile, S);
        if(S[0] != '#') {
          SS = S;
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
	      if(S[0] != '#') {
          DataFile >> S;
        }
      }
      else if(S == "Log_Last") {
        ReportAll = false;
      }
      else if(S == "Log_All") {
        ReportAll = true;
      }
      else if(S == "Auto_Run") {
        ;
      }
      else if(S == "Auto_Exit") {
        ;
      }
      else if(S == "TChart:") {

        while(!DataFile.eof()){
          getline(DataFile, S);
          if(DataFile.eof()) break;
          if(S[0] == '#') break;
        }
      }
    }while(!DataFile.eof());
  }

  catch (CRHMException Except) {
    Message(Except.Message.c_str(), "Loading project Error");
    DataFile.close();
    return;
  }

  DataFile.close();
}
//---------------------------------------------------------------------------

void  PrjCloseClick(void){

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

void  ClearModulesClick(void){

  ClearModules(true);
}
//---------------------------------------------------------------------------

int main(int argc, char *argv[]){

using namespace std;
using namespace CRHM;

  Global global;

  FormCreate();

  Global::OldModuleName = new TStringList;
  Global::NewModuleName = new TStringList;
  Global::OldModuleName->CommaText("AnnandaleX, calcsunX, calcsun_QsiD, Slope_QsiX, ebsmX, long,   longVtX, route,    smbal, Trees");
  Global::NewModuleName->CommaText("Annandale,  calcsun,  calcsun,      Slope_Qsi,  ebsm,  longVt, longVt,  Netroute, Soil,  Canopy");

  Global::TdateTime_Offset = Calculate_TdateTime_Offset();

  for(int pp = 0; pp < argc-1; ++pp) {
    string FileS = argv[pp+1];
    if(FileExistsSp(FileS)) {
      string Ext = ExtractFileExt(FileS);
      Ext = lowercase(Ext);
      if(Ext == ".prj") {
        OpenNamePrj = FileS;
        DoPrjOpen();
        if(!ListBox3->Count && ListBox4->Count){ // allows output of daily observations
          if(ReportAll)
            AllRprtObs();
          else
            LastRprtObs();
        }
        else{
          RunClick();
        }
      }
      else if(Ext == ".obs") {
        OpenNameObs = FileS;
        OpenObsFile(FileS);
      }
      else if(Ext == ".par") {
        ifstream DataFile;
        int c, Cols;
        string ss;

        bool TooFewHRUs = false;
        string module, param, Descrip, Line, S, s;
        ClassPar *thisPar;

        OpenNamePar = FileS;

        DataFile.open(OpenNamePar.c_str());
        if(!DataFile) {
          Message("cannot open file", "File Error");
          return -1;
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
          if(DataFile.eof()) return 0; // final exit

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
              newPar->Strings->DelimitedText(S);
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
                    Message("Too few HRUs defined in the Project file", "parameters not complete");
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
              Message(Except.Message, "Unknown Parameter in project file");
              LogError(Except);

next:         DataFile.ignore(256, '\n');
              c = DataFile.peek();
              if(!isalpha(c) && c != '#') goto next;
          }
        } // while

        DataFile.close();

        SqueezeParams();  // converts identical parameters to basin parameters
      } // for param
      else
          Message(string(FileS + " - file extension not 'prj', 'obs' or 'par'"), "Problem with File extension");
    }
    else
        Message(string(FileS + " - file does not exist").c_str(), "Problem with File");
  } // runstring loop

  return 0;
}
