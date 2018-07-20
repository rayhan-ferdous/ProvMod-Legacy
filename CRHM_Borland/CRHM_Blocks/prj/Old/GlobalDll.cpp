// 04/05/12
#include <vcl.h>
//---------------------------------------------------------------------------

#pragma hdrstop

#include "GlobalDll.h"
#include "GlobalCommon.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

using namespace std;

long Global::GroupCntTrk;
long Global::StructCntTrk;

long Global::Freq;     // set by first observation file.

long Global::DTindx;  // current index during model run and observation display.  Set in main.
long Global::DTmin;   // minimum index during model run and observation display.  Set in main.
long Global::DTmax;   // maximum index during model run and observation display.  Set in main.
long Global::IndxMin; // minimum index of the first file.
long Global::IndxMax; // maximum index of the first file.

long Global::maxobs;
long Global::maxlay;
long Global::maxhru;

long Global::nobs;
long Global::nlay;
long Global::nhru;

long Global::CRHMStatus;  // module status; module control = 1 , main control = 2 and Finished = 4. Both inhibit output.
long Global::CurrentModuleRun;  // currently executing module index
long Global::CRHMControlSaveCnt; // NewModules input

BitSet Global::RunUpBitSet; // determines modules executed during looping.
BitSet Global::ModuleBitSet; // determines modules executed during calculating ahead.

double Global::Interval; // set by first observation file.
double Global::DTstart;  // set by first observation file.  Integer.
double Global::DTend;    // set by first observation file.  Integer.

TDateTime Global::DTnow; // current time during model run and observation display.  Set in main.

TDateTime Global::RapidAdvanceTo; // Rapid advance to this date.
TDateTime Global::LoopTo; // Loop to this date.
long Global::LoopCnt;  // Loop this count
long Global::LoopCntDown;  // Loop this count

CRHM::TBuild Global::BuildFlag;

MapVar Global::MapVars;     // DECL
MapVar Global::MapVarsGet;  // INIT
MapVar Global::MapVarsPut;  // INIT
MapVar Global::MapObsGet;   // INIT
MapPar Global::MapPars;     // DECL
MapPar Global::SharedMapPars; // DECL

Mapstr Global::Mapgetvar;   // build
Mapstr Global::Mapputvar;   // build
Mapstr Global::Mapreadvar;  // build
Mapstr Global::Mapdeclvar;  // build
Mapstr Global::Mapdeclpar;  // build
Mapstr Global::Mapdeclobs;  // build
Mapstr Global::Mapdeclstat; // build
Mapstr2 Global::MapAKA;

TStringList *(Global::AllModulesList);
TStringList *(Global::OurModulesList);
TStringList *(Global::MacroModulesList);
TStringList *(Global::AllModelsList);
TStringList *(Global::ModelModulesList);
TStringList *(Global::OurHelpList);
TStringList *(Global::PendingDLLModuleList);
TStringList *(Global::ReportList);
TStringList *(Global::DeclRootList);
TStringList *(Global::OldModuleName);
TStringList *(Global::NewModuleName); 

HWND Global::crhmMain;
HWND Global::crhmLog;

float  *Global::lapse_rate; // used for array observations adjustments
float  *Global::ppt_adj; // used for array observations adjustments
float  *Global::hru_elev; // used for array observations adjustments
float  *Global::obs_elev; // used for array observations adjustments

float  *Global::Warming_t; // used for climate warming
float  *Global::Warming_p; // used for climate warming
long   *Global::RH_VP_flag; // used for climate warming
long   Global::RH_EA_flag; // used for climate warming

long   **Global::HRU_OBS; // used for array observations
float  **Global::obs_t; // used for array observations adjustments
float  **Global::obs_ea; // used for array observations adjustments
float  **Global::obs_rh; // used for array observations adjustments
float  **Global::obs_t_obs; // used for array observations adjustments



