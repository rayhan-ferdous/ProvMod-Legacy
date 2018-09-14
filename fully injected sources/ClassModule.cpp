#include <vcl.h>
#pragma hdrstop
#include "ClassModule.h"
#include "MacroUnit.h"
#include "Common.h"
#pragma package(smart_init)
using namespace std;
TStringList *ReadListN = new TStringList;
TStringList *FunctListN = new TStringList;
__declspec(dllexport) string Fstrings[] = {"Observation", "VP_saturated", "W_to_MJ/Int", "MJ/Int_to_W", "Average", "Minimum", "Maximum", "Daily Sum", "Positive",
                                           "Total", "First", "Last", "Peak", "Count", "Count0", "Intvl"
                                          };
__declspec(dllexport) string AKAstrings[] = {"VARG", "OBSR", "VARD", "OBSD", "PARD", "OBSF"};
double ClassModule::Now(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<doubleClassModule::Now(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</doubleClassModule::Now(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return Global::DTnow;}
freopen("c:\\injection.log", "a", stdout); printf("</doubleClassModule::Now(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
String ClassModule::Var_name(ClassModule* thisModule, String S)
{
freopen("c:\\injection.log", "a", stdout); printf("<StringClassModule::Var_name(ClassModule*thisModule,StringS) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    if(thisModule->variation != 0)
    {
        String AA("#0");
        AA[2] += log(thisModule->variation)/log(2) + 1;
        S += AA;
    }
{freopen("c:\\injection.log", "a", stdout); printf("</StringClassModule::Var_name(ClassModule*thisModule,StringS) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return S;}
freopen("c:\\injection.log", "a", stdout); printf("</StringClassModule::Var_name(ClassModule*thisModule,StringS) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::initbase(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::initbase(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    Global::BuildFlag = CRHM::INIT;
    MapPar::iterator itPar;
    ClassPar *newPar;
    decl();  
    init();  
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::initbase(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
int ClassModule::declgrpvar(string variable, string queryvar, string help, string units, float **value, float ***layvalue, bool PointPlot)
{
freopen("c:\\injection.log", "a", stdout); printf("<intClassModule::declgrpvar(stringvariable,stringqueryvar,stringhelp,stringunits,float**value,float***layvalue,boolPointPlot) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *newVar;
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</intClassModule::declgrpvar(stringvariable,stringqueryvar,stringhelp,stringunits,float**value,float***layvalue,boolPointPlot) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    Convert convert;
    convert.CheckUnitsString(Name, variable, units);
    AKAhook(VARD, Name, variable, variable);
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        PairstrV Item2 = PairstrV(variable.c_str(), variation_set);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclvar.insert(Item);
        PeerVar = queryvar.c_str();
{freopen("c:\\injection.log", "a", stdout); printf("</intClassModule::declgrpvar(stringvariable,stringqueryvar,stringhelp,stringunits,float**value,float***layvalue,boolPointPlot) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
    }
    case CRHM::DECL:
    {
        if((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end())
        {
{freopen("c:\\injection.log", "a", stdout); printf("</intClassModule::declgrpvar(stringvariable,stringqueryvar,stringhelp,stringunits,float**value,float***layvalue,boolPointPlot) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
        }
        if(layvalue == NULL)
        {
            LogError(CRHMException("Layer Array not defined for " + Name + " " + variable, WARNING));
{freopen("c:\\injection.log", "a", stdout); printf("</intClassModule::declgrpvar(stringvariable,stringqueryvar,stringhelp,stringunits,float**value,float***layvalue,boolPointPlot) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return -1;}
        }
        if(!Global::GroupCntTrk)
        {
            LogError(CRHMException("No groups defined " + Name + " " + variable, WARNING));
{freopen("c:\\injection.log", "a", stdout); printf("</intClassModule::declgrpvar(stringvariable,stringqueryvar,stringhelp,stringunits,float**value,float***layvalue,boolPointPlot) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return -1;}
        }
        newVar = new ClassVar(Name, variable, CRHM::NREB, help, units, CRHM::Float, PointPlot, nhru);
        newVar->varType = CRHM::Float;
        newVar->variation_set = variation_set;
        newVar->InGroup = GroupCnt;
        newVar->DLLName = DLLName.c_str();
        newVar->root = ID.c_str();
        PairVar Item = PairVar(Name + " " + variable, newVar);
        Global::MapVars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</intClassModule::declgrpvar(stringvariable,stringqueryvar,stringhelp,stringunits,float**value,float***layvalue,boolPointPlot) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
    }
    case CRHM::INIT:
    {
        if((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end())
        {
            newVar = (*itVar).second;
            *value = newVar->values;
            for(int ii = 0; ii < nhru; ++ii)
                newVar->layvalues[ii] = NULL;
            if(!Global::GroupCntTrk) 
{freopen("c:\\injection.log", "a", stdout); printf("</intClassModule::declgrpvar(stringvariable,stringqueryvar,stringhelp,stringunits,float**value,float***layvalue,boolPointPlot) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
            long querycnt = 0;
            for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++)
            {
                ClassVar* foundVar = (*itVar).second;
                if(newVar != NULL)
                {
                    if(foundVar->FileData)
                        continue;
                    string S = foundVar->name;
                    string::size_type indx = S.find('@');
                    if(indx != string::npos)
                    {
                        string N = S.substr(indx+1);
                        S = S.erase(indx);
                        if(S == queryvar)
                        {
                            newVar->layvalues[querycnt] = foundVar->values;
                            newVar->values[querycnt] = foundVar->dim;
                            ++querycnt;
                        } 
                    } 
                } 
            } 
            *layvalue = newVar->layvalues; 
{freopen("c:\\injection.log", "a", stdout); printf("</intClassModule::declgrpvar(stringvariable,stringqueryvar,stringhelp,stringunits,float**value,float***layvalue,boolPointPlot) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return querycnt;}
        }
        else
        {
            CRHMException Except("variable not found: " + Name + ' ' + variable, TERMINATE);
            LogError(Except);
            throw Except;
        }
    }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</intClassModule::declgrpvar(stringvariable,stringqueryvar,stringhelp,stringunits,float**value,float***layvalue,boolPointPlot) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return -1;}
freopen("c:\\injection.log", "a", stdout); printf("</intClassModule::declgrpvar(stringvariable,stringqueryvar,stringhelp,stringunits,float**value,float***layvalue,boolPointPlot) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::decldiag(string variable, CRHM::TDim dimen, string help, string units, float **value, float ***layvalue, const int dim, bool PointPlot, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::decldiag(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim,boolPointPlot,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    declvar(variable, dimen, help, units, value, layvalue, dim, PointPlot, false, Local);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decldiag(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim,boolPointPlot,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::decldiag(string variable, CRHM::TDim dimen, string help, string units, long **value, long ***ilayvalue, const int dim, bool PointPlot, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::decldiag(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**value,long***ilayvalue,constintdim,boolPointPlot,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    declvar(variable, dimen, help, units, value, ilayvalue, dim, PointPlot, false, Local);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decldiag(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**value,long***ilayvalue,constintdim,boolPointPlot,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::declstatdiag(string variable, CRHM::TDim dimen, string help, string units, float **value, float ***layvalue, const int dim, bool PointPlot, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::declstatdiag(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim,boolPointPlot,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    declvar(variable, dimen, help, units, value, layvalue, dim, PointPlot, true, Local);
    if(Global::BuildFlag == CRHM::BUILD)
    {
        String s = String(Name.c_str()) + " " + variable.c_str();
        VandP VP;
        VP.PutV(variation_set);
        VP.PutP(Local);
        PairstrV Item2 = PairstrV(s, VP.both);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclstat.insert(Item);
    }
};
void ClassModule::declstatdiag(string variable, CRHM::TDim dimen, string help, string units, long **value, long ***ilayvalue, const int dim, bool PointPlot, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::declstatdiag(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**value,long***ilayvalue,constintdim,boolPointPlot,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    declvar(variable, dimen, help, units, value, ilayvalue, dim, PointPlot, true, Local);
    if(Global::BuildFlag == CRHM::BUILD)
    {
        String s = String(Name.c_str()) + " " + variable.c_str();
        VandP VP;
        VP.PutV(variation_set);
        VP.PutP(Local);
        PairstrV Item2 = PairstrV(s, VP.both);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclstat.insert(Item);
    }
};
void ClassModule::declstatvar(string variable, CRHM::TDim dimen, string help, string units, float **value, float ***layvalue, const int dim, bool PointPlot, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::declstatvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim,boolPointPlot,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    declvar(variable, dimen, help, units, value, layvalue, dim, PointPlot, true, Local);
    if(Global::BuildFlag == CRHM::BUILD)
    {
        String s = String(Name.c_str()) + " " + variable.c_str();
        VandP VP;
        VP.PutV(variation_set);
        VP.PutP(Local);
        PairstrV Item2 = PairstrV(s, VP.both);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclstat.insert(Item);
    }
};
void ClassModule::declstatvar(string variable, CRHM::TDim dimen, string help, string units, long **value, long ***ilayvalue, const int dim, bool PointPlot, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::declstatvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**value,long***ilayvalue,constintdim,boolPointPlot,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    declvar(variable, dimen, help, units, value, ilayvalue, dim, PointPlot, true, Local);
    if(Global::BuildFlag == CRHM::BUILD)
    {
        String s = String(Name.c_str()) + " " + variable.c_str();
        VandP VP;
        VP.PutV(variation_set);
        VP.PutP(Local);
        PairstrV Item2 = PairstrV(s, VP.both);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclstat.insert(Item);
    }
};
void ClassModule::declvar(string variable, CRHM::TDim dimen, string help, string units, float **value, float ***layvalue, const int dim, bool PointPlot, bool StatVar, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *newVar;
    string Orgvariable = variable;
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString(Name, variable, units);
    AKAhook(VARD, Name, variable, variable);
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        VandP VP;
        VP.PutV(variation_set);
        VP.PutP(Local);
        PairstrV Item2 = PairstrV(variable.c_str(), VP.both);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclvar.insert(Item);
        Global::DeclRootList->Add(String(ID.c_str()) + " " + Orgvariable.c_str()); 
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    case CRHM::DECL:
    {
        if((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end())
        {
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        if(dimen == CRHM::NLAY && layvalue == NULL)
        {
            LogError(CRHMException("Layer Array not defined for " + Name + " " + variable, WARNING));
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        newVar = new ClassVar(Name, variable, dimen, help, units, CRHM::Float, PointPlot, nhru, dim);
        newVar->varType = CRHM::Float;
        newVar->StatVar = StatVar;
        newVar->InGroup = GroupCnt;
        newVar->visibility = Local;
        newVar->variation_set = variation_set;
        newVar->DLLName = DLLName.c_str();
        newVar->root = ID.c_str();
        PairVar Item = PairVar(Name + " " + variable, newVar);
        Global::MapVars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    case CRHM::INIT:
    {
        if((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end())
        {
            newVar = (*itVar).second;
            if(newVar->layvalues != NULL)
            {
                if(dimen == CRHM::NFREQ && newVar->lay != Global::Freq)
                {
                    newVar->nfreq = true;
                    newVar->lay = Global::Freq;
                    newVar->ReleaseM(true);
                    newVar->layvalues = new float *[newVar->lay];
                    for(int ii = 0; ii < newVar->lay; ii++)
                        newVar->layvalues[ii] = new float[newVar->dim];
                }
                if((dimen == CRHM::NLAY  || dimen == CRHM::NDEFN) && newVar->lay != dim)
                {
                    long JJ = newVar->lay;
                }
            }
            if(layvalue) 
                *layvalue = newVar->layvalues;
            *value = newVar->values; 
            Global::DeclRootList->Add(String(ID.c_str()) + " " + Orgvariable.c_str()); 
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        else
        {
            CRHMException Except("variable not found: " + Name + ' ' + variable, TERMINATE);
            LogError(Except);
            throw Except;
        }
    }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::declvar(string variable, CRHM::TDim dimen, string help, string units, long **ivalue, long ***ilayvalue, const int dim, bool PointPlot, bool StatVar, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**ivalue,long***ilayvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *newVar;
    string Orgvariable = variable;
    if(Variation_Skip())
    {
        *ivalue = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**ivalue,long***ilayvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    variation_max = variation_max | variation_set;
    AKAhook(VARD, Name, variable, variable);
    Convert convert;
    convert.CheckUnitsString(Name, variable, units);
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        VandP VP;
        VP.PutV(variation_set);
        VP.PutP(Local);
        PairstrV Item2 = PairstrV(variable.c_str(), VP.both);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclvar.insert(Item);
        Global::DeclRootList->Add(String(ID.c_str()) + " " + Orgvariable.c_str()); 
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**ivalue,long***ilayvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    case CRHM::DECL:
    {
        if((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end())
        {
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**ivalue,long***ilayvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        if(dimen == CRHM::NLAY && ilayvalue == NULL)
        {
            LogError(CRHMException("Layer Array not defined for " + Name + " " + variable, WARNING));
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**ivalue,long***ilayvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        newVar = new ClassVar(Name, variable, dimen, help, units, CRHM::Int, PointPlot, nhru, dim);
        newVar->varType = CRHM::Int;
        newVar->StatVar = StatVar;
        newVar->InGroup = GroupCnt;
        newVar->visibility = Local;
        newVar->variation_set = variation_set;
        newVar->DLLName = DLLName.c_str();
        newVar->root = ID.c_str();
        PairVar Item = PairVar(Name + " " + variable, newVar);
        Global::MapVars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**ivalue,long***ilayvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    case CRHM::INIT:
    {
        if((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end())
        {
            newVar = (*itVar).second;
            if((dimen == CRHM::NLAY || dimen == CRHM::NFREQ) && ilayvalue != NULL)
            {
                if(newVar->nfreq && newVar->lay != Global::Freq)
                {
                    newVar->ReleaseM(true);
                    newVar->lay = Global::Freq;
                    newVar->nfreq = true;
                    newVar->ilayvalues = new long *[newVar->lay];
                    for(int ii = 0; ii < newVar->lay; ii++)
                        newVar->ilayvalues[ii] = new long[newVar->dim];
                }
            }
            if(ilayvalue) 
                *ilayvalue = newVar->ilayvalues;
            *ivalue = newVar->ivalues; 
            Global::DeclRootList->Add(String(ID.c_str()) + " " + Orgvariable.c_str()); 
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**ivalue,long***ilayvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        else
        {
            CRHMException Except("Variable not found: " + Name + ' ' + variable, TERMINATE);
            LogError(Except);
            throw Except;
        }
    }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declvar(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**ivalue,long***ilayvalue,constintdim,boolPointPlot,boolStatVar,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::decllocal(string variable, CRHM::TDim dimen, string help, string units, float **value, float ***layvalue, const int dim)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::decllocal(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *newVar;
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decllocal(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString(Name, variable, units);
    AKAhook(VARD, Name, variable, variable); 
    switch(Global::BuildFlag)
    {
    case CRHM::DECL:
    {
        if((itVar = Global::MapVars.find("#" + Name + " " + variable)) != Global::MapVars.end())
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decllocal(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        if((dimen == CRHM::NLAY || dimen == CRHM::NFREQ) && layvalue == NULL)
        {
            LogError(CRHMException("Layer Array not defined for " + Name + " " + variable, WARNING));
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decllocal(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        newVar = new ClassVar(Name, variable, dimen, help, units, CRHM::Float, false, nhru, dim);
        newVar->varType = CRHM::Float;
        newVar->InGroup = GroupCnt;
        newVar->visibility = CRHM::PRIVATE;
        newVar->variation_set = variation_set;
        newVar->DLLName = DLLName.c_str();
        newVar->root = ID.c_str();
        PairVar Item = PairVar("#" + Name + " " + variable, newVar);
        Global::MapVars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decllocal(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    case CRHM::INIT:
    {
        string S = "#" + Name + " " + variable;
        if((itVar = Global::MapVars.find(S)) != Global::MapVars.end())
        {
            newVar = (*itVar).second;
            if((dimen == CRHM::NLAY || dimen == CRHM::NFREQ) && layvalue != NULL)
            {
                if(newVar->nfreq && newVar->lay != Global::Freq)
                {
                    newVar->ReleaseM(true);
                    newVar->lay = Global::Freq;
                    newVar->nfreq = true;
                    newVar->layvalues = new float *[newVar->lay];
                    for(int ii = 0; ii < newVar->lay; ii++)
                        newVar->layvalues[ii] = new float[newVar->dim];
                }
                *layvalue = newVar->layvalues;
            }
            *value = newVar->values;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decllocal(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        else
        {
            CRHMException Except("variable not found: " + ' ' + S, TERMINATE);
            LogError(Except);
            throw Except;
        }
    }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decllocal(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,float**value,float***layvalue,constintdim) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::decllocal(string variable, CRHM::TDim dimen, string help, string units, long **value, long ***layvalue, const int dim)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::decllocal(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**value,long***layvalue,constintdim) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *newVar;
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decllocal(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**value,long***layvalue,constintdim) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString(Name, variable, units);
    AKAhook(VARD, Name, variable, variable); 
    switch(Global::BuildFlag)
    {
    case CRHM::DECL:
    {
        if((itVar = Global::MapVars.find("#" + Name + " " + variable)) != Global::MapVars.end())
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decllocal(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**value,long***layvalue,constintdim) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        if(dimen == CRHM::NLAY && layvalue == NULL)
        {
            LogError(CRHMException("Layer Array not defined for " + Name + " " + variable, WARNING));
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decllocal(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**value,long***layvalue,constintdim) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        newVar = new ClassVar(Name, variable, dimen, help, units, CRHM::Int, false, nhru, dim);
        newVar->varType = CRHM::Int;
        newVar->InGroup = GroupCnt;
        newVar->visibility = CRHM::PRIVATE;
        newVar->variation_set = variation_set;
        newVar->DLLName = DLLName.c_str();
        newVar->root = ID.c_str();
        PairVar Item = PairVar("#" + Name + " " + variable, newVar);
        Global::MapVars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decllocal(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**value,long***layvalue,constintdim) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    case CRHM::INIT:
    {
        string S = "#" + Name + " " + variable;
        if((itVar = Global::MapVars.find(S)) != Global::MapVars.end())
        {
            newVar = (*itVar).second;
            if((dimen == CRHM::NLAY || dimen == CRHM::NFREQ) && layvalue != NULL)
            {
                if(newVar->nfreq && newVar->lay != Global::Freq)
                {
                    newVar->ReleaseM(true);
                    newVar->lay = Global::Freq;
                    newVar->nfreq = true;
                    newVar->ilayvalues = new long *[newVar->lay];
                    for(int ii = 0; ii < newVar->lay; ii++)
                        newVar->ilayvalues[ii] = new long[newVar->dim];
                }
                *layvalue = newVar->ilayvalues;
            }
            *value = newVar->ivalues;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decllocal(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**value,long***layvalue,constintdim) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        else
        {
            CRHMException Except("variable not found: " + ' ' + S, TERMINATE);
            LogError(Except);
            throw Except;
        }
    }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decllocal(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,long**value,long***layvalue,constintdim) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
TStringList* ClassModule::decldiagparam(string param, CRHM::TDim dimen, string Texts, string help, TStringList *StringsList, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<TStringList*ClassModule::decldiagparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    TStringList* fix = declparam(param, dimen, Texts, help, StringsList, Local);
{freopen("c:\\injection.log", "a", stdout); printf("</TStringList*ClassModule::decldiagparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return fix;}
freopen("c:\\injection.log", "a", stdout); printf("</TStringList*ClassModule::decldiagparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
TStringList* ClassModule::decllocalparam(string param, CRHM::TDim dimen, string Texts, string help, TStringList *StringsList, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<TStringList*ClassModule::decllocalparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    TStringList* fix = declparam(param, dimen, Texts, help, StringsList, Local);
{freopen("c:\\injection.log", "a", stdout); printf("</TStringList*ClassModule::decllocalparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return fix;}
freopen("c:\\injection.log", "a", stdout); printf("</TStringList*ClassModule::decllocalparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
TStringList* ClassModule::declparam(string param, CRHM::TDim dimen, string Texts, string help, TStringList *StringsList, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<TStringList*ClassModule::declparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *newPar;
    if(Variation_Skip())
    {
{freopen("c:\\injection.log", "a", stdout); printf("</TStringList*ClassModule::declparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return (TStringList*) NULL;}
    }
    variation_max = variation_max | variation_set;
    AKAhook(PARD, Name, param, param);
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        VandP VP;
        VP.PutV(variation_set);
        VP.PutP(Local);
        PairstrV Item2 = PairstrV(param.c_str(), VP.both);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclpar.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</TStringList*ClassModule::declparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return (TStringList*) NULL;}
    }
    case CRHM::DECL:
    {
        if((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end())
        {
            if((*itPar).second->dim == this->nhru || dimen == CRHM::BASIN)
            {
                newPar = (*itPar).second;
{freopen("c:\\injection.log", "a", stdout); printf("</TStringList*ClassModule::declparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return newPar->Strings;}
            }
            else
            {
                (*itPar).second->ExpandShrink(this->nhru);
                newPar = (*itPar).second;
{freopen("c:\\injection.log", "a", stdout); printf("</TStringList*ClassModule::declparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return newPar->Strings;}
            }
        }
        if((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
        {
            newPar = (*itPar).second;
{freopen("c:\\injection.log", "a", stdout); printf("</TStringList*ClassModule::declparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return newPar->Strings;}
        }
        newPar = new ClassPar(string(Name.c_str()), string(param), dimen, Texts, help, CRHM::Txt, nhru);
        newPar->basemodule = this->NameRoot;
        newPar->variation_set = variation_set;
        newPar->visibility = Local;
        PairPar Item = PairPar(Name + " " + param, newPar);
        Global::MapPars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</TStringList*ClassModule::declparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return newPar->Strings;}
    }
    case CRHM::INIT:
    {
        if((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end())
        {
            newPar = (*itPar).second;
            StringsList = newPar->Strings;
{freopen("c:\\injection.log", "a", stdout); printf("</TStringList*ClassModule::declparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return StringsList;}
        }
        else if((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
        {
            newPar = (*itPar).second;
            StringsList = newPar->Strings;
{freopen("c:\\injection.log", "a", stdout); printf("</TStringList*ClassModule::declparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return StringsList;}
        }
        else
        {
            CRHMException Except("Parameter not found: " + Name + param, TERMINATE);
            LogError(Except);
            throw Except;
        }
    }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</TStringList*ClassModule::declparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return (TStringList*) NULL;}
freopen("c:\\injection.log", "a", stdout); printf("</TStringList*ClassModule::declparam(stringparam,CRHM::TDimdimen,stringTexts,stringhelp,TStringList*StringsList,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::decldiagparam(string param, CRHM::TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const float **value, const float ***layvalue, const int dim, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::decldiagparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constfloat**value,constfloat***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    declparam(param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decldiagparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constfloat**value,constfloat***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::decllocalparam(string param, CRHM::TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const float **value, const float ***layvalue, const int dim, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::decllocalparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constfloat**value,constfloat***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    declparam(param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decllocalparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constfloat**value,constfloat***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::declparam(string param, CRHM::TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const float **value, const float ***layvalue, const int dim, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constfloat**value,constfloat***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *newPar;
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constfloat**value,constfloat***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString(Name, param, units);
    AKAhook(PARD, Name, param, param);
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        VandP VP;
        VP.PutV(variation_set);
        VP.PutP(Local);
        PairstrV Item2 = PairstrV(param.c_str(), VP.both);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclpar.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constfloat**value,constfloat***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    case CRHM::DECL:
    {
        if(dim <= 0)   
        {
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constfloat**value,constfloat***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        if((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end())
        {
            if((*itPar).second->dim == this->nhru || dimen == CRHM::BASIN)
            {
                newPar = (*itPar).second;
                if(newPar->Inhibit_share == 2)
                {
                    newPar->basemodule = this->NameRoot;
                    newPar->variation_set = variation_set;
                    newPar->visibility = Local;
                    newPar->Inhibit_share = 1;
                    newPar->valstr = valstr;
                    newPar->minVal = atof(minstr.c_str());
                    newPar->maxVal = atof(maxstr.c_str());
                    newPar->help = help;
                }
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constfloat**value,constfloat***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
            }
            else
            {
                (*itPar).second->ExpandShrink(this->nhru);
                newPar = (*itPar).second;
                if(newPar->Inhibit_share == 2)
                {
                    newPar->Inhibit_share = 1;
                }
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constfloat**value,constfloat***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
            }
        }
        if((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
        {
            if((*itPar).second->dim == this->nhru || dimen == CRHM::BASIN)
            {
                newPar = (*itPar).second;
                if(newPar->Inhibit_share == 2)
                {
                    newPar->Inhibit_share = 1;
                }
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constfloat**value,constfloat***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
            }
        }
        if((dimen == CRHM::NLAY && layvalue == NULL) || (dimen == CRHM::NDEF && layvalue == NULL) || (dimen == CRHM::NDEFN && layvalue == NULL))
        {
            LogError(CRHMException("Layer Array not defined for " + Name + " " + param, WARNING));
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constfloat**value,constfloat***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        float minval = atof(minstr.c_str());
        float maxval = atof(maxstr.c_str());
        newPar = new ClassPar(string(Name.c_str()), string(param), dimen,
                              valstr, minval, maxval, help, units, CRHM::Float, dim, nhru);
        newPar->basemodule = this->NameRoot;
        newPar->variation_set = variation_set;
        newPar->visibility = Local;
        Myparser ob;
        ob.eval_exp(newPar);
        PairPar Item = PairPar(Name + " " + param, newPar);
        Global::MapPars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constfloat**value,constfloat***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    case CRHM::INIT:
    {
        if((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end())
        {
            newPar = (*itPar).second;
            *value = newPar->values;
        }
        else if((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
        {
            newPar = (*itPar).second;
            *value = newPar->values;
        }
        else if(newPar = ClassParFindPar(param))
        {
            *value = newPar->values;
        }
        else
        {
            CRHMException Except("Parameter not found: " + Name + " " + param, TERMINATE);
            LogError(Except);
            throw Except;
        }
        if((dimen == CRHM::NLAY && layvalue != NULL) || (dimen == CRHM::NDEF && layvalue != NULL) || (dimen == CRHM::NDEFN && layvalue != NULL))
            const_cast<float **> (*layvalue) = newPar->layvalues;
    } 
    } 
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constfloat**value,constfloat***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::decldiagparam(string param, CRHM::TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long **value, const long ***layvalue, const int dim, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::decldiagparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**value,constlong***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    declparam(param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decldiagparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**value,constlong***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::decllocalparam(string param, CRHM::TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long **value, const long ***layvalue, const int dim, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::decllocalparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**value,constlong***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    declparam(param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::decllocalparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**value,constlong***layvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::declparam(string param, CRHM::TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long **ivalue, const long ***ilayvalue, const int dim, CRHM::TVISIBLE Local)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**ivalue,constlong***ilayvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *newPar;
    if(Variation_Skip())
    {
        *ivalue = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**ivalue,constlong***ilayvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString(Name, param, units);
    AKAhook(PARD, Name, param, param);
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        VandP VP;
        VP.PutV(variation_set);
        VP.PutP(Local);
        PairstrV Item2 = PairstrV(param.c_str(), VP.both);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclpar.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**ivalue,constlong***ilayvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    case CRHM::DECL:
    {
        if(dim <= 0)   
        {
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**ivalue,constlong***ilayvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        *ivalue = &Dummy;
        if((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end())
        {
            if((*itPar).second->dim == this->nhru || dimen == CRHM::BASIN)
            {
                newPar = (*itPar).second;
                if(newPar->Inhibit_share == 2)
                {
                    newPar->basemodule = this->NameRoot;
                    newPar->variation_set = variation_set;
                    newPar->visibility = Local;
                    newPar->Inhibit_share = 1;
                    newPar->valstr = valstr;
                    newPar->minVal = atof(minstr.c_str());
                    newPar->maxVal = atof(maxstr.c_str());
                    newPar->help = help;
                }
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**ivalue,constlong***ilayvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
            }
            else
            {
                (*itPar).second->ExpandShrink(this->nhru);
                newPar = (*itPar).second;
                if(newPar->Inhibit_share == 2)
                {
                    assert(0);
                }
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**ivalue,constlong***ilayvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
            }
        }
        if((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
        {
            if((*itPar).second->dim == this->nhru || dimen == CRHM::BASIN)
            {
                newPar = (*itPar).second;
                if(newPar->Inhibit_share == 2)
                {
                    assert(0);
                }
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**ivalue,constlong***ilayvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
            }
        }
        if((dimen == CRHM::NLAY && ilayvalue == NULL) || (dimen == CRHM::NDEF && ilayvalue == NULL) || (dimen == CRHM::NDEFN && ilayvalue == NULL))
        {
            LogError(CRHMException("Layer Array not defined for " + Name + " " + param, WARNING));
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**ivalue,constlong***ilayvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        float minval = atof(minstr.c_str());
        float maxval = atof(maxstr.c_str());
        newPar = new ClassPar(string(Name.c_str()), string(param), dimen,
                              valstr, minval, maxval, help, units, CRHM::Int, dim, nhru);
        newPar->basemodule = this->NameRoot;
        newPar->variation_set = variation_set;
        newPar->visibility = Local;
        Myparser ob;
        ob.eval_exp(newPar);
        PairPar Item = PairPar(Name + " " + param, newPar);
        Global::MapPars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**ivalue,constlong***ilayvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    case CRHM::INIT:
    {
        if((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end())
        {
            newPar = (*itPar).second;
            *ivalue = newPar->ivalues;
            if((dimen == CRHM::NLAY && ilayvalue != NULL) || (dimen == CRHM::NDEF && ilayvalue != NULL) || (dimen == CRHM::NDEFN && ilayvalue != NULL))
                const_cast<long **> (*ilayvalue) = newPar->ilayvalues;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**ivalue,constlong***ilayvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        else if((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
        {
            newPar = (*itPar).second;
            *ivalue = newPar->ivalues;
            if((dimen == CRHM::NLAY && ilayvalue != NULL) || (dimen == CRHM::NDEF && ilayvalue != NULL) || (dimen == CRHM::NDEFN && ilayvalue != NULL))
                const_cast<long **> (*ilayvalue) = newPar->ilayvalues;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**ivalue,constlong***ilayvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        else if(newPar = ClassParFindPar(param))
        {
            *ivalue = newPar->ivalues;
            if((dimen == CRHM::NLAY && ilayvalue != NULL) || (dimen == CRHM::NDEF && ilayvalue != NULL) || (dimen == CRHM::NDEFN && ilayvalue != NULL))
                const_cast<long **> (*ilayvalue) = newPar->ilayvalues;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**ivalue,constlong***ilayvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        else
        {
            CRHMException Except("Parameter not found: " + Name + " " + param, TERMINATE);
            LogError(Except);
            throw Except;
        }
    } 
    } 
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declparam(stringparam,CRHM::TDimdimen,stringvalstr,stringminstr,stringmaxstr,stringhelp,stringunits,constlong**ivalue,constlong***ilayvalue,constintdim,CRHM::TVISIBLELocal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::FindWildVarFloat(string name, ClassVar* &newVar, bool OnceFlag)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::FindWildVarFloat(stringname,ClassVar*&newVar,boolOnceFlag) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    string spacename = " " + name;;
    string Var;
    MapVar::iterator itVar;
    for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++)
    {
        Var = (*itVar).first;
        if(Var[0] == '#') 
            continue;
        string::size_type indx = Var.rfind(spacename); 
        if(indx == string::npos)
        {
            continue; 
        }
        newVar = (*itVar).second;
        if(newVar->cnt > 0)  
            continue;
        if(spacename.substr(1) != newVar->name) 
            continue;
        Global::thisVar =  (TObject*) newVar;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::FindWildVarFloat(stringname,ClassVar*&newVar,boolOnceFlag) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return newVar->GetUnit();}
    } 
    if(OnceFlag == false)
    {
        OnceFlag = true;
        string::size_type indx = name.find('@');
        if(indx != string::npos)
        {
            spacename = name.substr(0, indx); 
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::FindWildVarFloat(stringname,ClassVar*&newVar,boolOnceFlag) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return FindWildVarFloat(spacename, newVar, true);}
        }
    }
    Global::thisVar = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::FindWildVarFloat(stringname,ClassVar*&newVar,boolOnceFlag) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return -1;}
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::FindWildVarFloat(stringname,ClassVar*&newVar,boolOnceFlag) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::FindWildParFloat(string name, ClassPar* &newPar, bool Trunc = false, bool Root = true)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::FindWildParFloat(stringname,ClassPar*&newPar,boolTrunc=false,boolRoot=true) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    string spacename;
    if(!Trunc)
        spacename = " " + name;
    else
    {
        string::size_type indx2 = name.find('@');
        if(indx2 == string::npos)
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::FindWildParFloat(stringname,ClassPar*&newPar,boolTrunc=false,boolRoot=true) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return -1;}
        else
            spacename = " " + name.substr(0, indx2); 
    }
    MapPar::iterator itPar;
    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++)
    {
        string Var = (*itPar).first;
        if(Var[0] == '#')
            continue;
        string::size_type indx = Var.rfind(spacename);
        newPar = (*itPar).second;
        if(indx == string::npos)
            continue; 
        string::size_type indx2 = newPar->param.find('@');
        if(!Root || indx2 == string::npos)
        {
            if(spacename.substr(1) != newPar->param) 
                continue;
        }
        else if(spacename.substr(1) != newPar->param.substr(0, indx2))
            continue; 
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::FindWildParFloat(stringname,ClassPar*&newPar,boolTrunc=false,boolRoot=true) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return newPar->GetUnit();}
    }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::FindWildParFloat(stringname,ClassPar*&newPar,boolTrunc=false,boolRoot=true) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return -1;}
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::FindWildParFloat(stringname,ClassPar*&newPar,boolTrunc=false,boolRoot=true) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::declgetvar(string source, string name, string units, const float **value, const float ***layvalue)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::declgetvar(stringsource,stringname,stringunits,constfloat**value,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *newVar;
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constfloat**value,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    variation_max = variation_max | variation_set;
    AKAhook(VARG, Name, name, name, source, ID);
    MapPar::iterator itPar;
    ClassPar *newPar;
    long GetUnit;
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        String s = String(source.c_str()) + " " + name.c_str();
        PairstrV Item2 = PairstrV(s, variation_set);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapgetvar.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constfloat**value,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
    }
    case CRHM::DECL:
    {
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constfloat**value,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
    }
    case CRHM::INIT:
    {
        string::size_type indx2 = name.find('@');
        if((itVar = Global::MapVars.find(source + " " + name)) != Global::MapVars.end())
        {
            newVar = (*itVar).second;
            *value = newVar->values;
            if(layvalue != NULL)
                const_cast<float **> (*layvalue) = newVar->layvalues;
            PairVar Item = PairVar(Name + " " + name, newVar);
            Global::MapVarsGet.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constfloat**value,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return newVar->GetUnit();}
        }
        else if(indx2 != string::npos &&  
                (itVar = Global::MapVars.find(source + " " + name.substr(0, indx2))) != Global::MapVars.end())
        {
            newVar = (*itVar).second;
            *value = newVar->values;
            if(layvalue != NULL)
                const_cast<float **> (*layvalue) = newVar->layvalues;
            PairVar Item = PairVar(Name + " " + name, newVar);
            Global::MapVarsGet.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constfloat**value,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return newVar->GetUnit();}
        }
        else if(source[0] == '*')
        {
            GetUnit = FindWildVarFloat(name, newVar); 
            if(GetUnit > -1)
            {
                *value = newVar->values;
                if(layvalue != NULL)
                    const_cast<float **> (*layvalue) = newVar->layvalues;
                PairVar Item = PairVar(Name + " " + name, newVar);
                Global::MapVarsGet.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constfloat**value,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return GetUnit;}
            }
        }
    } 
    } 
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constfloat**value,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constfloat**value,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::declgetvar(string source, string name, string units, const long **value, const long ***layvalue)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::declgetvar(stringsource,stringname,stringunits,constlong**value,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *newVar;
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constlong**value,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    variation_max = variation_max | variation_set;
    AKAhook(VARG, Name, name, name, source, ID);
    MapPar::iterator itPar;
    ClassPar *newPar;
    long GetUnit;
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        String s = String(source.c_str()) + " " + name.c_str();
        PairstrV Item2 = PairstrV(s, variation_set);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapgetvar.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constlong**value,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
    }
    case CRHM::DECL:
    {
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constlong**value,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
    }
    case CRHM::INIT:
    {
        if(name == "Not_Used") 
            name = "Not_Used_int";
        string::size_type indx2 = name.find('@');
        if((itVar = Global::MapVars.find(source + " " + name)) != Global::MapVars.end())
        {
            newVar = (*itVar).second;
            *value = newVar->ivalues;
            if(layvalue != NULL)
                const_cast<long **> (*layvalue) = newVar->ilayvalues;
            PairVar Item = PairVar(Name + " " + name, newVar);
            Global::MapVarsGet.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constlong**value,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return newVar->GetUnit();}
        }
        else if(indx2 != string::npos &&  
                (itVar = Global::MapVars.find(source + " " + name.substr(0, indx2))) != Global::MapVars.end())
        {
            newVar = (*itVar).second;
            *value = newVar->ivalues;
            if(layvalue != NULL)
                const_cast<long **> (*layvalue) = newVar->ilayvalues;
            PairVar Item = PairVar(Name + " " + name, newVar);
            Global::MapVarsGet.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constlong**value,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return newVar->GetUnit();}
        }
        else if(source[0] == '*')
        {
            GetUnit = FindWildVarFloat(name, newVar); 
            if(GetUnit > -1)
            {
                *value = newVar->ivalues;
                if(layvalue != NULL)
                    const_cast<long **> (*layvalue) = newVar->ilayvalues;
                PairVar Item = PairVar(Name + " " + name, newVar);
                Global::MapVarsGet.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constlong**value,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return GetUnit;}
            }
        }
    } 
    } 
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constlong**value,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetvar(stringsource,stringname,stringunits,constlong**value,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::declobs(string name, CRHM::TDim dimen, string help, string units, float **value)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::declobs(stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *newVar;
    ClassVar *thisVar;
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobs(stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString(Name, name, units);
    AKAhook(OBSD, Name, name, name);
    int cnt = getdim(dimen);
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        VandP VP;
        VP.PutV(variation_set);
        VP.PutP(CRHM::USUAL);
        PairstrV Item2 = PairstrV((name + "#").c_str(), VP.both);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclvar.insert(Item);
        Global::Mapdeclobs.insert(Item);
        Global::DeclRootList->Add(String(ID.c_str()) + " " + (name + "#").c_str()); 
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobs(stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    case CRHM::DECL:
    {
        if((itVar = Global::MapVars.find(Name + " " + name + "#")) != Global::MapVars.end())
        {
            thisVar = (*itVar).second;
            if(thisVar->dim < cnt)
            {
                thisVar->ReleaseM(); 
                thisVar->dim = cnt;
                if(thisVar->lay > 0)
                {
                    thisVar->layvalues = new float *[thisVar->lay];
                    for(int ii = 0; ii < thisVar->lay; ii++)
                        thisVar->layvalues[ii] = new float[cnt];
                }
                thisVar->values = new float[cnt];     
            }
            thisVar->dimen == dimen;
            thisVar->DLLName = DLLName.c_str();
            thisVar->root = ID.c_str();
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobs(stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
        }
        newVar = new ClassVar(Name, name + "#", cnt, 0, NULL);
        newVar->varType = CRHM::Float;
        newVar->help = help;
        newVar->units = units;
        newVar->DLLName = DLLName.c_str();
        newVar->root = ID.c_str();
        newVar->values = new float[cnt];
        newVar->variation_set = variation_set;
        PairVar Item = PairVar(Name + " " + name + "#", newVar);
        Global::MapVars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobs(stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    case CRHM::INIT:
    {
        if((itVar = Global::MapVars.find(Name + " " + name + "#")) != Global::MapVars.end())
        {
            Global::DeclRootList->Add(String(ID.c_str()) + " " + (name + "#").c_str()); 
            newVar = (*itVar).second;
            if(newVar->FileData)
            {
                *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobs(stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-(newVar->cnt-1));}
            }
            else
            {
                *value = newVar->values;
                newVar->cnt = cnt; 
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobs(stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(newVar->cnt-1);}
            }
        }
        else
        {
            CRHMException Except("Observation not found: " + Name + " " + name + "#", TERMINATE);
            LogError(Except);
            throw Except;
        }
    }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobs(stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobs(stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::getdimObs(string variable)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::getdimObs(stringvariable) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *newVar;
    if((itVar = Global::MapVars.find("obs " + variable)) != Global::MapVars.end())
    {
        newVar = (*itVar).second;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::getdimObs(stringvariable) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(newVar->cnt);}
    }
    else
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::getdimObs(stringvariable) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::getdimObs(stringvariable) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::declreadobs(string variable, CRHM::TDim dimen, string help, string units, const float **value, long HRU_index, bool optional, const float ***layvalue)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constfloat**value,longHRU_index,booloptional,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *newVar;
    PairVar Item;
    string declModule = "obs ";
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constfloat**value,longHRU_index,booloptional,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    variation_max = variation_max | variation_set;
    AKAhook(OBSR, Name, variable, variable, declModule, ID);
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        PairstrV Item2 = PairstrV(variable.c_str(), variation_set);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapreadvar.insert(Item);
        Global::Mapdeclvar.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constfloat**value,longHRU_index,booloptional,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    case CRHM::DECL:
    {
        if(dimen == CRHM::NFREQ && layvalue == NULL)
        {
            LogError(CRHMException("NFREQ Array not defined for " + Name + " " + variable, WARNING));
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constfloat**value,longHRU_index,booloptional,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
        }
        if((itVar = Global::MapVars.find(declModule + variable)) != Global::MapVars.end())
        {
            newVar = (*itVar).second;
            if(newVar->varType == CRHM::Read)   
            {
                Convert convert;
                convert.CheckUnitsObs(newVar->units, units, variable); 
                newVar->values = NULL; 
                newVar->varType = CRHM::ReadF;
                newVar->dimen = dimen;
                newVar->help = help;
                newVar->units = units;
                Item = PairVar(Name + " " + variable, newVar);
                Global::MapVars.insert(Item);
            }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constfloat**value,longHRU_index,booloptional,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(0);}
        }
        if(optional)
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constfloat**value,longHRU_index,booloptional,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
        newVar = new ClassVar("obs", variable, dimen, help, units, CRHM::Float);
        newVar->varType = CRHM::Float;
        Item = PairVar(declModule + variable, newVar);
        Global::MapVars.insert(Item);
        Item = PairVar(Name + " " + variable, newVar);
        Global::MapVars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constfloat**value,longHRU_index,booloptional,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    case CRHM::INIT:
    {
        newVar = NULL; 
        if((itVar = Global::MapVars.find(declModule + variable)) != Global::MapVars.end())  
        {
            newVar = (*itVar).second;
            if((newVar->varType == CRHM::ReadF  | newVar->varType == CRHM::Read) && newVar->values == NULL)
            {
                Convert convert;
                convert.CheckUnitsObs(newVar->units, units, variable); 
                newVar->varType = CRHM::ReadF;
                newVar->dimMax = Global::maxhru;
                newVar->values = new float[newVar->dimMax];
                newVar->help = help;
                newVar->units = units;
                Item = PairVar(Name + " " + variable, newVar);
                Global::MapVars.insert(Item);
            }
        }
        string::size_type indx; 
        if(itVar == Global::MapVars.end() || !newVar->cnt && newVar->DLLName.empty())  
        {
            string variable2;
            indx = variable.find('#');
            if(indx == string::npos)
                variable2 = variable + '#';
            else
                variable2 = variable.erase(indx);
            if(GroupCnt)  
            {
                if((itVar = Global::MapVars.find(Name + ' ' + variable2)) != Global::MapVars.end())
                    newVar = (*itVar).second;
            }
            else   
            {
                if((itVar = Global::MapVars.find(declModule + variable2)) != Global::MapVars.end())
                    newVar = (*itVar).second;
            }
        }
        if(newVar == NULL)
        {
            if(optional)
            {
                *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constfloat**value,longHRU_index,booloptional,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
            }
            CRHMException Except("Observation not found " + declModule + ": " + variable, TERMINATE);
            LogError(Except);
            throw Except;
        }
        if(!newVar->cnt && newVar->DLLName.empty() && indx == string::npos)   
        {
            if(optional)
            {
                *value = NULL;
                PairVar Item = PairVar(Name + " " + variable, newVar);
                Global::MapObsGet.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constfloat**value,longHRU_index,booloptional,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
            }
            else
            {
                CRHMException Except("Observation: '" + variable + "', not in Data file. Requested by '" + Name.c_str() + "'", TERMINATE);
                LogError(Except);
                throw Except;
            }
        }
        if(newVar->FileData)
        {
            if(dimen == CRHM::NHRU)
                newVar->dim = nhru;
            else
                newVar->dim = newVar->cnt;
            addtoreadlist(newVar);  
        }
        *value = newVar->values;
        PairVar Item = PairVar(Name + " " + variable, newVar);
        Global::MapObsGet.insert(Item);
        if(HRU_index > 0)
            newVar->HRU_OBS_indexed = HRU_index-1; 
        if(newVar->cnt > 0)
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constfloat**value,longHRU_index,booloptional,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(newVar->cnt-1);}
        else
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constfloat**value,longHRU_index,booloptional,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(newVar->dim-1);}
    }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constfloat**value,longHRU_index,booloptional,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constfloat**value,longHRU_index,booloptional,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::declreadobs(string variable, CRHM::TDim dimen, string help, string units, const long **value, long HRU_index, bool optional, const long ***layvalue)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constlong**value,longHRU_index,booloptional,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *newVar;
    PairVar Item;
    string declModule = "obs ";
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constlong**value,longHRU_index,booloptional,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    variation_max = variation_max | variation_set;
    AKAhook(OBSR, Name, variable, variable, declModule, ID);
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        PairstrV Item2 = PairstrV(variable.c_str(), variation_set);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapreadvar.insert(Item);
        Global::Mapdeclvar.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constlong**value,longHRU_index,booloptional,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    case CRHM::DECL:
    {
        if(dimen == CRHM::NFREQ && layvalue == NULL)
        {
            LogError(CRHMException("NFREQ Array not defined for " + Name + " " + variable, WARNING));
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constlong**value,longHRU_index,booloptional,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
        }
        if((itVar = Global::MapVars.find(declModule + variable)) != Global::MapVars.end())
        {
            newVar = (*itVar).second;
            if(newVar->varType == CRHM::Read || newVar->varType == CRHM::ReadI)
            {
                if(dimen == CRHM::NFREQ && (newVar->lay == 0 || nhru > newVar->dim))
                {
                    newVar->ReleaseM(true);
                    newVar->dim = nhru;
                    newVar->dimMax = newVar->dim;
                    newVar->lay = Global::Freq;
                    newVar->nfreq = true;
                    newVar->ilayvalues = new long *[newVar->lay];
                    for(int ii = 0; ii < newVar->lay; ++ii)
                        newVar->ilayvalues[ii] = new long[newVar->dimMax];
                }
                if(newVar->varType == CRHM::Read || newVar->varType == CRHM::ReadF && nhru > newVar->dimMax)
                {
                    if(newVar->ivalues != NULL)
                        delete[] newVar->ivalues;
                    else
                    {
                        Convert convert;
                        convert.CheckUnitsObs(newVar->units, units, variable); 
                    }
                    newVar->dimMax = max<long> (nhru, newVar->cnt);
                    newVar->ivalues = new long[newVar->dimMax];
                    newVar->varType = CRHM::ReadI;
                    newVar->help = help;
                    newVar->units = units;
                    Item = PairVar(Name + " " + variable, newVar);
                    Global::MapVars.insert(Item);
                }
                else
                {
                    Item = PairVar(Name + " " + variable, newVar);
                    Global::MapVars.insert(Item);
                }
            }
            else if(newVar->dimen != dimen && dimen == CRHM::NFREQ)  
            {
                newVar->ReleaseM(true);
                newVar->lay = Global::Freq;
                newVar->nfreq = true;
                newVar->ilayvalues = new long *[newVar->lay];
                for(int ii = 0; ii < newVar->lay; ii++)
                    newVar->ilayvalues[ii] = new long[newVar->dim];
            }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constlong**value,longHRU_index,booloptional,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
        }
        newVar = new ClassVar(declModule, variable, dimen, help, units, CRHM::Int);
        newVar->varType = CRHM::Int;
        Item = PairVar(declModule + variable, newVar);
        Global::MapVars.insert(Item);
        Item = PairVar(Name + " " + variable, newVar);
        Global::MapVars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constlong**value,longHRU_index,booloptional,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    case CRHM::INIT:
    {
        newVar = NULL; 
        if((itVar = Global::MapVars.find(declModule + variable)) != Global::MapVars.end())  
        {
            newVar = (*itVar).second;
            if(itVar == Global::MapVars.end() || !newVar->cnt && newVar->DLLName.empty())  
            {
                string variable2;
                string::size_type indx = variable.find('#');
                if(indx == string::npos)
                    variable2 = variable + '#';
                else
                    variable2 = variable.erase(indx);
                if(GroupCnt)  
                {
                    if((itVar = Global::MapVars.find(Name + ' ' + variable2)) != Global::MapVars.end())
                        newVar = (*itVar).second;
                }
                else   
                {
                    if((itVar = Global::MapVars.find(declModule + variable2)) != Global::MapVars.end())
                        newVar = (*itVar).second;
                }
            }
        }
        if(newVar == NULL)
        {
            CRHMException Except("Observation not found " + declModule + ": " + variable, TERMINATE);
            LogError(Except);
            throw Except;
        }
        if(!newVar->cnt && newVar->DLLName.empty())
        {
            if(optional)
            {
                *value = NULL;
                PairVar Item = PairVar(Name + " " + variable, newVar);
                Global::MapObsGet.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constlong**value,longHRU_index,booloptional,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
            }
            else
            {
                CRHMException Except("Observation: '" + variable + "', not in Data file. Requested by '" + Name.c_str() + "'", TERMINATE);
                LogError(Except);
                throw Except;
            }
        }
        newVar->No_ReadVar = 0;
        if(layvalue != NULL)
        {
            if(newVar->nfreq && newVar->lay != Global::Freq)
            {
                newVar->ReleaseM(true);
                newVar->lay = Global::Freq;
                newVar->nfreq = true;
                newVar->ilayvalues = new long *[newVar->lay];
                for(int ii = 0; ii < newVar->lay; ii++)
                    newVar->ilayvalues[ii] = new long[newVar->dim];
            }
            const_cast<long **> (*layvalue) = newVar->ilayvalues;
            newVar->UserFunct = &ClassVar::Intvl;
            newVar->FunKind = CRHM::INTVL;
            newVar->FunctVar = newVar;
            addtofunctlist(newVar);  
        }
        if(newVar->FileData)
        {
            newVar->dim = nhru;
            addtoreadlist(newVar);  
        }
        *value = newVar->ivalues;
        PairVar Item = PairVar(Name + " " + variable, newVar);
        Global::MapObsGet.insert(Item);
        if(HRU_index > 0)
            newVar->HRU_OBS_indexed = HRU_index-1; 
        if(newVar->cnt > 0)
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constlong**value,longHRU_index,booloptional,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(newVar->cnt-1);}
        else
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constlong**value,longHRU_index,booloptional,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(newVar->dim-1);}
    }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constlong**value,longHRU_index,booloptional,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declreadobs(stringvariable,CRHM::TDimdimen,stringhelp,stringunits,constlong**value,longHRU_index,booloptional,constlong***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::declobsfunc(string obs, string variable, float **value, CRHM::TFun typeFun, float ***layvalue, bool optional)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::declobsfunc(stringobs,stringvariable,float**value,CRHM::TFuntypeFun,float***layvalue,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *obsVar, *newVar;
    PairVar Item;
    string declModule = "obs ";
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,float**value,CRHM::TFuntypeFun,float***layvalue,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    variation_max = variation_max | variation_set;
    AKAhook(OBSF, Name, obs, obs, declModule, ID);
    AKAhook(VARD, Name, variable, variable);
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        pair<Mapstr::iterator, Mapstr::iterator> range = Global::Mapreadvar.equal_range(Name.c_str());
        String units;
        for(Mapstr::iterator itMap = range.first; itMap != range.second; ++itMap)
        {
            if(itMap->second.first == obs.c_str())
            {
                units = itMap->second.second;
                break;
            }
        }
        VandP VP;
        VP.PutV(variation_set);
        VP.PutP(CRHM::DIAGNOSTIC);
        PairstrV Item2 = PairstrV(obs.c_str(), VP.both);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapreadvar.insert(Item);
        Global::Mapdeclvar.insert(Item);
        Item2 = PairstrV(variable.c_str(), VP.both);
        Item =  PairstrI(Name.c_str(), Item2);
        Global::Mapdeclvar.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,float**value,CRHM::TFuntypeFun,float***layvalue,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    case CRHM::DECL:
    {
        if((itVar = Global::MapVars.find(declModule + obs)) == Global::MapVars.end())
        {
            LogError(CRHMException("function obs variable not declared: " + Name +  " " + obs, WARNING));
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,float**value,CRHM::TFuntypeFun,float***layvalue,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
        }
        obsVar = (*itVar).second;
        if((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end())
        {
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,float**value,CRHM::TFuntypeFun,float***layvalue,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
        }
        newVar = new ClassVar(Name, variable, nhru,
                              obsVar->help + " <" + Fstrings[typeFun] + "> ",
                              obsVar->units, CRHM::Float);
        newVar->dimMax = nhru; 
        newVar->varType = CRHM::Float;
        newVar->visibility = CRHM::DIAGNOSTIC;
        newVar->variation_set = variation_set;
        newVar->DLLName = DLLName.c_str();
        newVar->root = ID.c_str();
        PairVar Item = PairVar(Name + " " + variable, newVar);
        Global::MapVars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,float**value,CRHM::TFuntypeFun,float***layvalue,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(0);}
    }
    case CRHM::INIT:
    {
        itVar = Global::MapVars.find(Name + " " + variable);
        newVar = (*itVar).second;
        if((itVar = Global::MapVars.find(declModule + obs)) != Global::MapVars.end())
        {
            obsVar = (*itVar).second;
            if(!newVar)  
            {
                newVar = new ClassVar(Name, variable, nhru,
                                      obsVar->help + " <" + Fstrings[typeFun] + "> ",
                                      obsVar->units, CRHM::Float);
                newVar->dimMax = nhru;
                newVar->varType = CRHM::Float;
                newVar->visibility = CRHM::DIAGNOSTIC;
                newVar->variation_set = variation_set;
                newVar->DLLName = DLLName.c_str();
                newVar->root = ID.c_str();
                PairVar Item = PairVar(Name + " " + variable, newVar);
                Global::MapVars.insert(Item);
            }
            if(obsVar->FileData == NULL)
            {
                if(optional)
                {
                    *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,float**value,CRHM::TFuntypeFun,float***layvalue,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
                }
                else
                {
                    CRHMException Except("Function observation: '" + variable + "', cannot be generated from the declared observation, '" + obs.c_str()+ "'. Requested by '" + Name.c_str() + "'", TERMINATE);
                    LogError(Except);
                    throw Except;
                }
            }
            if(obsVar->FileData->Times != NULL)
            {
                CRHMException Except("Function observation: '" + variable + "', uses a 'sparse' Data file. Requested by '" + Name.c_str() + "'", TERMINATE);
                LogError(Except);
                throw Except;
            }
            if(typeFun == CRHM::INTVL)
            {
                newVar->ReleaseM(false); 
                newVar->dim = max<long>(nhru, newVar->dim);
                newVar->dimMax = max<long>(newVar->dim, newVar->dimMax);
                newVar->lay = Global::Freq;
                newVar->layvalues = new float *[newVar->lay];
                *layvalue = newVar->layvalues;
                for(int ii = 0; ii < newVar->lay; ++ii)
                    newVar->layvalues[ii] = new float[newVar->dimMax];
                newVar->values = newVar->layvalues[0]; 
                newVar->FileData = obsVar->FileData;
            }
            else if(nhru > newVar->dim)  
            {
                delete[] newVar->values;
                newVar->dimMax = nhru;
                newVar->values = new float[newVar->dimMax];
                newVar->dim = newVar->dimMax;
            }
            if(GroupCnt)
                newVar->CustomFunct = NULL; 
            switch(typeFun)
            {
            case CRHM::FOBS:
                newVar->FunctVar = obsVar;
                newVar->FunKind = CRHM::FOBS;
                newVar->FileData = obsVar->FileData;
                if(GroupCnt)
                    newVar->No_ReadVar = 1;  
                break;
            case CRHM::AVG:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::Avg;
                newVar->FunKind = CRHM::AVG;
                break;
            case CRHM::MIN:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::Min;
                newVar->FunKind = CRHM::MIN;
                break;
            case CRHM::MAX:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::Max;
                newVar->FunKind = CRHM::MAX;
                break;
            case CRHM::DTOT:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::Dtot;
                newVar->FunKind = CRHM::DTOT;
                break;
            case CRHM::TOT:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::Tot;
                newVar->FunKind = CRHM::TOT;
                break;
            case CRHM::FIRST:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::First;
                newVar->FunKind = CRHM::FIRST;
                break;
            case CRHM::LAST:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::Last;
                newVar->FunKind = CRHM::LAST;
                break;
            case CRHM::POS:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::Pos;
                newVar->FunKind = CRHM::POS;
                break;
            case CRHM::INTVL:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::Intvl;
                newVar->FunKind = CRHM::INTVL;
                newVar->offset = newVar->FunctVar->offset;
                *layvalue = newVar->layvalues;
                break;
            }
            *value = newVar->values;
            newVar->HRU_OBS_indexed = obsVar->HRU_OBS_indexed;
            if(newVar->FunKind == CRHM::FOBS)
                addtoreadlist(newVar);
            else if(Global::RH_EA_obs == -1  && obs == "rh" || Global::RH_EA_obs == -1  && obs == "ea" || Global::OBS_AS_IS || !(obs == "ea" || obs == "rh"))
                addtofunctlist(newVar);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,float**value,CRHM::TFuntypeFun,float***layvalue,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(obsVar->cnt-1);}
        }
        else
        {
            if(!optional)
            {
                CRHMException Except("Observation not found obs: " + obs, TERMINATE);
                LogError(Except);
                throw Except;
            }
            else
                *value = NULL;
        }
    }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,float**value,CRHM::TFuntypeFun,float***layvalue,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,float**value,CRHM::TFuntypeFun,float***layvalue,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::declobsfunc(string obs, string variable, long **value, CRHM::TFun typeFun, bool optional)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::declobsfunc(stringobs,stringvariable,long**value,CRHM::TFuntypeFun,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *obsVar, *newVar;
    PairVar Item;
    string declModule = "obs ";
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,long**value,CRHM::TFuntypeFun,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    variation_max = variation_max | variation_set;
    AKAhook(OBSF, Name, obs, obs, declModule, ID);
    AKAhook(VARD, Name, variable, variable);
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        pair<Mapstr::iterator, Mapstr::iterator> range = Global::Mapreadvar.equal_range(Name.c_str());
        String units;
        for(Mapstr::iterator itMap = range.first; itMap != range.second; ++itMap)
        {
            if(itMap->second.first == obs.c_str())
            {
                units = itMap->second.second;
                break;
            }
        }
        VandP VP;
        VP.PutV(variation_set);
        VP.PutP(CRHM::DIAGNOSTIC);
        PairstrV Item2 = PairstrV(obs.c_str(), VP.both);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapreadvar.insert(Item);
        Global::Mapdeclvar.insert(Item);
        Item2 = PairstrV(variable.c_str(), VP.both);
        Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclvar.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,long**value,CRHM::TFuntypeFun,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    case CRHM::DECL:
    {
        if((itVar = Global::MapVars.find(declModule + obs)) == Global::MapVars.end())
        {
            LogError(CRHMException("function obs variable not declared: " + Name + " " + obs, WARNING));
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,long**value,CRHM::TFuntypeFun,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
        }
        obsVar = (*itVar).second;
        if((itVar = Global::MapVars.find(Name + " " +  variable)) != Global::MapVars.end())
        {
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,long**value,CRHM::TFuntypeFun,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
        }
        if(!obsVar->ivalues)
        {
            obsVar->ivalues = new long[obsVar->dim]; 
            obsVar->varType = CRHM::ReadI;
        }
        newVar = new ClassVar(Name, variable, obsVar->dim,
                              obsVar->help + " <" + Fstrings[typeFun] + "> ",
                              obsVar->units, CRHM::Float);
        newVar->varType = CRHM::Float;
        newVar->visibility = CRHM::DIAGNOSTIC;
        newVar->variation_set = variation_set;
        newVar->DLLName = DLLName.c_str();
        newVar->root = ID.c_str();
        PairVar Item = PairVar(Name + " " + variable, newVar);
        Global::MapVars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,long**value,CRHM::TFuntypeFun,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    case CRHM::INIT:
    {
        itVar = Global::MapVars.find(Name + " " + variable);
        newVar = (*itVar).second;
        if((itVar = Global::MapVars.find(declModule + obs)) != Global::MapVars.end())
        {
            obsVar = (*itVar).second;
            if(obsVar->FileData == NULL)
            {
                if(optional)
                {
                    LogError(CRHMException("Function observation: '" + variable + "', cannot be generated from the declared observation, '" + obs.c_str()+ "'. Requested by '" + Name.c_str() + "' (optional).", WARNING));
                    *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,long**value,CRHM::TFuntypeFun,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
                }
                else
                {
                    CRHMException Except("Function observation: '" + variable + "', cannot be generated from the declared observation, '" + obs.c_str()+ "'. Requested by '" + Name.c_str() + "'", TERMINATE);
                    LogError(Except);
                    throw Except;
                }
            }
            if(obsVar->FileData->Times != NULL)
            {
                CRHMException Except("Function observation: '" + variable + "', uses a 'sparse' Data file. Requested by '" + Name.c_str() + "'", TERMINATE);
                LogError(Except);
                throw Except;
            }
            if(obsVar->dim != newVar->dim)  
            {
                delete[] newVar->ivalues;
                newVar->ivalues = new long[obsVar->dim];
                newVar->dim = obsVar->dim;
            }
            switch(typeFun)
            {
            case CRHM::AVG:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::Avg;
                newVar->FunKind = CRHM::AVG;
                break;
            case CRHM::MIN:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::Min;
                newVar->FunKind = CRHM::MIN;
                break;
            case CRHM::MAX:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::Max;
                newVar->FunKind = CRHM::MAX;
                break;
            case CRHM::DTOT:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::Dtot;
                newVar->FunKind = CRHM::DTOT;
                break;
            case CRHM::TOT:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::Tot;
                newVar->FunKind = CRHM::TOT;
                break;
            case CRHM::FIRST:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::First;
                newVar->FunKind = CRHM::FIRST;
                break;
            case CRHM::LAST:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::Last;
                newVar->FunKind = CRHM::LAST;
                break;
            case CRHM::POS:
                newVar->FunctVar = obsVar;
                newVar->UserFunct = &ClassVar::Pos;
                newVar->FunKind = CRHM::POS;
                break;
            }
            *value = newVar->ivalues;
            newVar->No_ReadVar = 0;
            newVar->HRU_OBS_indexed = obsVar->HRU_OBS_indexed;
            addtofunctlist(newVar);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,long**value,CRHM::TFuntypeFun,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return (obsVar->cnt-1);}
        }
        else
        {
            CRHMException Except("Variable not found obs: " + obs, TERMINATE);
            LogError(Except);
            throw Except;
        }
    }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,long**value,CRHM::TFuntypeFun,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declobsfunc(stringobs,stringvariable,long**value,CRHM::TFuntypeFun,booloptional) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::declputvar(string source, string name, string units, float **value, float ***layvalue)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::declputvar(stringsource,stringname,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *newVar;
    long GetUnit;
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputvar(stringsource,stringname,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    variation_max = variation_max | variation_set;
    AKAhook(VARG, Name, name, name, source, ID);
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        String s = String(source.c_str()) + " " + name.c_str();
        PairstrV Item2 = PairstrV(s, variation_set);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapputvar.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputvar(stringsource,stringname,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
    }
    case CRHM::DECL:
    {
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputvar(stringsource,stringname,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
    }
    case CRHM::INIT:
    {
        if((itVar = Global::MapVars.find(source + " " + name)) != Global::MapVars.end())
        {
            newVar = (*itVar).second;
            *value = newVar->values;
            if(layvalue != NULL)
                const_cast<float **> (*layvalue) = newVar->layvalues;
            PairVar Item = PairVar(Name + " " + name, newVar);
            Global::MapVarsPut.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputvar(stringsource,stringname,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return newVar->GetUnit();}
        }
        else if(source[0] == '*')
        {
            GetUnit = FindWildVarFloat(name, newVar); 
            if(GetUnit > -1)
            {
                *value = newVar->values;
                if(layvalue != NULL)
                    const_cast<float **> (*layvalue) = newVar->layvalues;
                PairVar Item = PairVar(Name + " " + name, newVar);
                Global::MapVarsPut.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputvar(stringsource,stringname,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return GetUnit;}
            }
            CRHMException Except("Wild variable not found: " + source + ' ' + name, TERMINATE);
            LogError(Except);
            throw Except;
        }
        else
        {
            CRHMException Except("Variable not found: " + source + ' ' + name, TERMINATE);
            LogError(Except);
            throw Except;
        }
    }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputvar(stringsource,stringname,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputvar(stringsource,stringname,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::declputvar(string source, string name, string units, long **value, long ***layvalue)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::declputvar(stringsource,stringname,stringunits,long**value,long***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *newVar;
    long GetUnit;
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputvar(stringsource,stringname,stringunits,long**value,long***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    variation_max = variation_max | variation_set;
    AKAhook(VARG, Name, name, name, source, ID);
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        String s = String(source.c_str()) + " " + name.c_str();
        PairstrV Item2 = PairstrV(s, variation_set);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapputvar.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputvar(stringsource,stringname,stringunits,long**value,long***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
    }
    case CRHM::DECL:
    {
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputvar(stringsource,stringname,stringunits,long**value,long***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
    }
    case CRHM::INIT:
    {
        if(name == "Not_Used") 
            name = "Not_Used_int";
        if((itVar = Global::MapVars.find(source + " " + name)) != Global::MapVars.end())
        {
            newVar = (*itVar).second;
            *value = newVar->ivalues;
            if(layvalue != NULL)
                const_cast<long **> (*layvalue) = newVar->ilayvalues;
            PairVar Item = PairVar(Name + " " + name, newVar);
            Global::MapVarsPut.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputvar(stringsource,stringname,stringunits,long**value,long***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return newVar->GetUnit();}
        }
        else if(source[0] == '*')
        {
            GetUnit = FindWildVarFloat(name, newVar); 
            if(GetUnit > -1)
            {
                *value = newVar->ivalues;
                if(layvalue != NULL)
                    const_cast<long **> (*layvalue) = newVar->ilayvalues;
                PairVar Item = PairVar(Name + " " + name, newVar);
                Global::MapVarsPut.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputvar(stringsource,stringname,stringunits,long**value,long***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return GetUnit;}
            }
            CRHMException Except("Wild variable not found: " + source + ' ' + name, TERMINATE);
            LogError(Except);
            throw Except;
        }
        else
        {
            CRHMException Except("Variable not found: " + source + ' ' + name, TERMINATE);
            LogError(Except);
            throw Except;
        }
    }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputvar(stringsource,stringname,stringunits,long**value,long***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return(-1);}
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputvar(stringsource,stringname,stringunits,long**value,long***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::AKAhook(TAKA type, string module, string OrgName, string & NewName)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::AKAhook(TAKAtype,stringmodule,stringOrgName,string&NewName) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    Mapstr2::iterator it; 
    string ID = AKAstrings[type] + ' ' + module + ' ' + OrgName;
    bool Added = false;
    bool Explicit = false;
    if((it = Global::MapAKA.find(ID)) != Global::MapAKA.end())
    {
        NewName = (*it).second;
        NewName = NewName.substr(0, NewName.find(' '));
        Explicit = true;
    }
    else
    {
        if(type == OBSD)
        {
            string::size_type idx = ID.size();
            if(ID[idx-1] == '#')
                ID.erase(idx, 1);
            else
            {
                ID.insert(idx, "#");
                Added = true;
            }
            if((it = Global::MapAKA.find(ID)) != Global::MapAKA.end())
            {
                NewName = (*it).second;
                NewName = NewName.substr(0, NewName.find(' '));
                if(Added)
                    NewName = NewName.substr(0, NewName.size()-1);
                Explicit = true;
            }
            else
                Added = false;
        }
        else if(GroupCnt && type == VARD)
        {
            string A;
            GroupEnding(A, GroupCnt);
            NewName.append(A);
            ID = AKAstrings[type] + ' ' + module + ' ' + NewName;
            if((it = Global::MapAKA.find(ID)) != Global::MapAKA.end())
            {
                NewName = (*it).second;
                NewName = NewName.substr(0, NewName.find(' '));
                Explicit = true;
            }
        }
        else if(StructCnt && type == VARD)
        {
            string A("@`");
            A[1] += StructCnt;
            NewName.append(A);
        }
    }
    if(Global::ReportList && Explicit)
    {
        string ID = AKAstrings[type] + ' ' + module + ' ' + OrgName;
        if(Added)
            NewName.insert(NewName.size(), "#");
        if(Explicit)
            NewName.insert(NewName.size(), " **** explicit");
        Global::ReportList->Add((ID + " ---> " + NewName).c_str());
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::AKAhook(TAKAtype,stringmodule,stringOrgName,string&NewName) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::AKAhook(TAKA type, string module, string OrgName, string & NewName, string & source, string base)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::AKAhook(TAKAtype,stringmodule,stringOrgName,string&NewName,string&source,stringbase) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    Mapstr2::iterator it; 
    enum {None, Implicit, Explicit, IgnoreObs, IgnoreVar, IgnoreObsFunct} Outcome;
    Outcome = None;
    TAKA typeL = type; 
    if(type == OBSF)
        type = OBSR;
    string Try;
    string ID = AKAstrings[type] + ' ' + module + ' ' + OrgName;
    if((it = Global::MapAKA.find(ID)) != Global::MapAKA.end())   
    {
        Try = (*it).second;
        Try = Try.substr(0, Try.find(' '));
        if(Global::DeclRootList->IndexOf(String(base.c_str()) + " " + Try.c_str()) > -1)  
        {
            if(typeL == OBSF)
                Outcome = IgnoreObsFunct;
            else
                Outcome = IgnoreObs;
        }
        else if(GroupCnt && type == VARG)
        {
            string A;
            GroupEnding(A, GroupCnt);
            NewName.append(A);
            ID = AKAstrings[type] + ' ' + module + ' ' + NewName;
            if((it = Global::MapAKA.find(ID)) != Global::MapAKA.end())   
            {
                Try = (*it).second;
                Try = Try.substr(0, Try.find(' '));
                NewName = (*it).second;
                NewName = NewName.substr(0, NewName.find(' '));
                Outcome = Implicit;
            }
        }
        else if(typeL == OBSF && Try[Try.size()-1] == '#')  
        {
            Outcome = IgnoreObsFunct;
        }
        else if(type == OBSR)  
        {
            if(Try[Try.size()-1] == '#')
            {
                if(Global::DeclRootList->IndexOf(String(base.c_str()) + " " + Try.c_str()) > -1)
                {
                    Outcome = IgnoreObs;
                }
            }
            NewName = (*it).second;
            NewName = NewName.substr(0, NewName.find(' '));
            source = (*it).second;
            source = source.substr(source.find(' ')+1) + ' ';
            Outcome = Explicit;
        }
        else if(type == VARG)  
        {
            NewName = (*it).second;
            NewName = NewName.substr(0, NewName.find(' '));
            source = (*it).second;
            source = source.substr(source.find(' ')+1);
            Outcome = Explicit;
        }
    } 
    else
    {
        if(GroupCnt && typeL == OBSR)  
        {
            if((Global::MapVars.find("obs " + OrgName)) != Global::MapVars.end())  
            {
                NewName = OrgName;
                source = "obs ";
                Try = NewName;
                Outcome = Implicit;
            }
            else
            {
                string mod_var = ID.substr(ID.find(' ')+1) + '#';
                if((Global::MapVars.find(mod_var)) != Global::MapVars.end())
                {
                    NewName = OrgName + '#';
                    source = module + ' ';
                    Try = NewName;
                    Outcome = Implicit;
                }
            }
        }
        else if((GroupCnt || StructCnt) && type == VARG)
        {
            string A;
            if(GroupCnt)
            {
                GroupEnding(A, GroupCnt);
            }
            if(StructCnt)
            {
                GroupEnding(A, StructCnt);
            }
            NewName.append(A);
            ID = AKAstrings[type] + ' ' + module + ' ' + NewName;
            if((it = Global::MapAKA.find(ID)) != Global::MapAKA.end())
            {
                Try = (*it).second;
                Try = Try.substr(0, Try.find('@'));
                if(Global::DeclRootList->IndexOf(String(base.c_str()) + " " + Try.c_str()) > -1)
                {
                    Outcome = IgnoreVar;
                }
                else
                {
                    NewName = (*it).second;
                    NewName = NewName.substr(0, NewName.find(' '));
                    Outcome = Implicit;
                }
            }
        }
    }
    ID = AKAstrings[typeL] + " (" + base + ") "  + module + " -> " + OrgName + ' ';
    switch (Outcome)
    {
    case IgnoreObs:
        LogMessage(string(ID + " *** AKA warning, not changed to *** " + source + "->" + Try).c_str());
        break;
    case IgnoreObsFunct:
        LogMessage(string(ID + "*** AKA warning, not changed to *** " + source + "->" + Try).c_str());
        break;
    case IgnoreVar: 
        LogMessage(string(ID + "*** AKA warning, not changed to *** " + source + "->" + Try).c_str());
        break;
    } 
    if(Global::ReportList && Outcome != None)
    {
        string reason = "";
        switch (Outcome)
        {
        case Explicit:
            source = (ID + " changed to " + source + "-> " + Try).c_str();
            reason =  " *** Explicit *** ";
            break;
        case Implicit:
            source = (ID + " changed to " + source + "-> " + Try).c_str();
            reason = " *** Implicit *** ";
            break;
        case IgnoreObs:
            source = (ID + " AKA warning, not changed to " + source + "-> " + Try).c_str();
            reason = " *** source module AKA observation redirection would loop output to input";
            break;
        case IgnoreObsFunct:
            source = (ID + " AKA warning, not changed to " + source + "-> " + Try).c_str();
            reason = " *** daily function cannot be a declared observation";
            break;
        case IgnoreVar: 
            source = (ID + " AKA warning, not changed to " + source + "-> " + Try).c_str();
            reason = " *** source module AKA variable redirection would loop output to input";
            break;
        } 
        Global::ReportList->Add((source + reason).c_str());
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::AKAhook(TAKAtype,stringmodule,stringOrgName,string&NewName,string&source,stringbase) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::InitReadObs(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::InitReadObs(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    ReadListN->Clear();
    FunctListN->Clear();
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::InitReadObs(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::ReadObs(bool Reset)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::ReadObs(boolReset) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    static long p;
    static long pN;
    static long LastGroup; 
    if(Reset)
    {
        p = 0;
        pN = 0;
        LastGroup = -1;
    }
    if(Global::DTindx%Global::Freq == 0)   
    {
        while (pN != FunctListN->Count && FunctListN->Strings[pN] == Name.c_str())
        {
            ClassVar *P = (ClassVar*) FunctListN->Objects[pN];
            P->dim = nhru; 
            if(P->FunctVar->FileData->GoodDay)
                (P->*(P->UserFunct))();
            if(P->CustomFunct) 
                (P->*(P->CustomFunct))(this); 
            ++pN;
        }
    }
    while (p < ReadListN->Count && ((ReadListN->Strings[p] == Name.c_str()) || GroupCnt == 0))   
    {
        ClassVar *P = (ClassVar*) ReadListN->Objects[p];
        P->dim = nhru; 
        if(P->module == "obs" || (GroupCnt && !P->No_ReadVar))
            P->ReadVar();
        if(P->CustomFunct) 
            (P->*(P->CustomFunct))(this); 
        ++p;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::ReadObs(boolReset) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
bool ClassModule::ReadAheadObs(long inc)
{
freopen("c:\\injection.log", "a", stdout); printf("<boolClassModule::ReadAheadObs(longinc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    if(Global::DTindx + inc >= Global::DTmax || Global::DTindx + inc < Global::DTmin)
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::ReadAheadObs(longinc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return false;}
    long CurrentDTindx = Global::DTindx;
    TDateTime CurrentDTnow = Global::DTnow;
    Global::DTindx += inc;
    Global::DTnow = Global::DTstart + Global::Interval*(Global::DTindx+1);
    long p = 0;
    while (p < ReadListN->Count)
    {
        ClassVar *P = (ClassVar*)ReadListN->Objects[p];
        if(P->FileData->GoodInterval)
            P->ReadVar();
        ++p;
    }
    if(Global::DTindx%Global::Freq == 0)
    {
        p = 0;
        while (p < FunctListN->Count && FunctListN->Strings[p] == Name.c_str())
        {
            ClassVar *P = (ClassVar*) FunctListN->Objects[p];
            if(P->FunctVar->FileData->GoodDay)
                (P->*(P->UserFunct))();
            ++p;
        }
    }
    Global::DTindx = CurrentDTindx;
    Global::DTnow = CurrentDTnow;
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::ReadAheadObs(longinc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return true;}
freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::ReadAheadObs(longinc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
bool ClassModule::ReadAheadObsMacro(long inc)
{
freopen("c:\\injection.log", "a", stdout); printf("<boolClassModule::ReadAheadObsMacro(longinc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    if(Global::DTindx + inc >= Global::DTmax || Global::DTindx + inc < Global::DTmin)
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::ReadAheadObsMacro(longinc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return false;}
    long CurrentDTindx = Global::DTindx;
    long **Save_HRU_obs =  Global::HRU_OBS;
    Global::DTindx += inc;
    Global::DTnow = Global::DTstart + Global::Interval*(Global::DTindx+1);
    long p = 0;
    while (p < ReadListN->Count)
    {
        ClassVar *P = (ClassVar*)ReadListN->Objects[p];
        if(P->FileData->GoodInterval)
            P->ReadVar();
        ++p;
    }
    if(Global::DTindx%Global::Freq == 0)
    {
        p = 0;
        while (p < FunctListN->Count)
        {
            ClassVar *P = (ClassVar*) FunctListN->Objects[p];
            if(P->FunctVar->FileData->GoodDay)
                (P->*(P->UserFunct))();
            ++p;
        }
    }
    Global::DTindx = CurrentDTindx; 
    Global::HRU_OBS = Save_HRU_obs; 
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::ReadAheadObsMacro(longinc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return true;}
freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::ReadAheadObsMacro(longinc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
bool ClassModule::WriteAheadObsMacro(long inc)
{
freopen("c:\\injection.log", "a", stdout); printf("<boolClassModule::WriteAheadObsMacro(longinc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    if(Global::DTindx + inc >= Global::DTmax || Global::DTindx + inc < Global::DTmin)
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::WriteAheadObsMacro(longinc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return false;}
    long CurrentDTindx = Global::DTindx;
    Global::DTindx += inc;
    long p = 0;
    while (p < ReadListN->Count)
    {
        ClassVar *P = (ClassVar*)ReadListN->Objects[p];
        if(P->FileData->GoodInterval)
            P->WriteVar();
        ++p;
    }
    Global::DTindx = CurrentDTindx; 
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::WriteAheadObsMacro(longinc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return true;}
freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::WriteAheadObsMacro(longinc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::DelReadObs(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::DelReadObs(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    ReadListN->Clear();
    FunctListN->Clear();
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::DelReadObs(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
bool ClassModule::AnyOne(float *Data, int Cnt, float Val)
{
freopen("c:\\injection.log", "a", stdout); printf("<boolClassModule::AnyOne(float*Data,intCnt,floatVal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    if(Data == NULL) 
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::AnyOne(float*Data,intCnt,floatVal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return false;}
    for(int ii = 0; ii < Cnt; ++ii)
        if(Data[ii] != Val)
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::AnyOne(float*Data,intCnt,floatVal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return true;}
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::AnyOne(float*Data,intCnt,floatVal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return false;}
freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::AnyOne(float*Data,intCnt,floatVal) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
bool ClassModule::UsingObservations(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<boolClassModule::UsingObservations(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    if(ReadListN->Count || FunctListN->Count)
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::UsingObservations(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return true;}
    else
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::UsingObservations(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return false;}
freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::UsingObservations(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::addtoreadlist(ClassVar *newVar)   
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::addtoreadlist(ClassVar*newVar) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    long p = 0;
    ClassVar *P;
    string::size_type indx;
    while (p < ReadListN->Count && GroupCnt == 0)   
    {
        P = (ClassVar*)ReadListN->Objects[p];
        if(newVar == P)
        {
            if(this->Name == this->NameRoot) 
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::addtoreadlist(ClassVar*newVar) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        p++;
    }
    if(((Global::DTmax - Global::DTmin)/Global::Freq + newVar->FileData->Dt1 > newVar->FileData->Dt2) && !newVar->FileData->Times)
    {
        CRHMException TExcept((String("Observation file '") + String(newVar->FileData->DataFileName.c_str()) + "' shorter than model run!").c_str(), WARNING);
        LogError(TExcept);
    }
    if(GroupCnt) 
        ReadListN->AddObject(Name.c_str(), (TObject*) newVar); 
    else
        ReadListN->AddObject(newVar->module.c_str(), (TObject*) newVar); 
    newVar->CustomFunct = NULL; 
    if(!Global::OBS_AS_IS)
    {
        string::size_type idx = newVar->name.find('@');
        string root_var;
        if(idx != string::npos)
            root_var = newVar->name.substr(0, idx);
        if(newVar->name == "t_max" || newVar->name == "t_min")
        {
            if(AnyOne(Global::Warming_t, nhru, 0.0))
            {
                newVar->CustomFunct = &ClassVar::do_t_Clim;
                newVar->CustomFunctName = "do_t_Clim";
            }
            else
            {
                newVar->CustomFunct = &ClassVar::do_t;
                newVar->CustomFunctName = "do_t";
            }
        }
        else if(!GroupCnt && newVar->name == "p" || GroupCnt && root_var == "p")
        {
            if(AnyOne(Global::Warming_p, nhru, 1.0))
            {
                newVar->CustomFunct = &ClassVar::do_p_Clim;
                newVar->CustomFunctName = "do_p_Clim";
            }
            else
            {
                newVar->CustomFunct = &ClassVar::do_p;
                newVar->CustomFunctName = "do_p";
            }
        }
    } 
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::addtoreadlist(ClassVar*newVar) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::addtofunctlist(ClassVar *newVar)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::addtofunctlist(ClassVar*newVar) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    long p = 0;
    ClassVar *P;
    string::size_type indx;
    while (p < FunctListN->Count)
    {
        P = (ClassVar*)FunctListN->Objects[p];
        if(newVar == P)
        {
            if(this->Name == this->NameRoot && GroupCnt == 0) 
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::addtofunctlist(ClassVar*newVar) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        p++;
    }
    FunctListN->AddObject(Name.c_str(), (TObject*) newVar);
    if(NameRoot == "obs" || Name == "obs")  
    {
        string RootName = newVar->name;
        if(indx = RootName.find("@"), indx != std::string::npos)
            RootName = newVar->name.substr(0, indx);
        if(!Global::OBS_AS_IS)
        {
            if(RootName == "Tday")
            {
                if(AnyOne(Global::Warming_t, nhru, 0.0))
                {
                    newVar->CustomFunct = &ClassVar::do_t_day_Clim;
                    newVar->CustomFunctName = "do_t_day_Clim";
                }
                else
                {
                    newVar->CustomFunct = &ClassVar::do_t_day;
                    newVar->CustomFunctName = "do_t_day";
                }
            }
            else if(RootName == "RHday")
            {
                if(AnyOne(Global::Warming_t, nhru, 0.0))
                {
                    newVar->CustomFunct = &ClassVar::do_rh_day_Clim;
                    newVar->CustomFunctName = "do_rh_day_Clim";
                }
                else
                {
                    newVar->CustomFunct = &ClassVar::do_rh_day;
                    newVar->CustomFunctName = "do_rh_day";
                }
            }
            else if(RootName == "EAday")
            {
                if(AnyOne(Global::Warming_t, nhru, 0.0))
                {
                    newVar->CustomFunct = &ClassVar::do_ea_day;
                    newVar->CustomFunctName = "do_ea_day";
                }
            }
            else if(RootName == "t_min" || newVar->name == "t_max")
            {
                if(AnyOne(Global::Warming_t, nhru, 0.0))
                {
                    newVar->CustomFunct = &ClassVar::do_t_Clim;
                    newVar->CustomFunctName = "do_t_Clim";
                }
                else
                {
                    newVar->CustomFunct = &ClassVar::do_t;
                    newVar->CustomFunctName = "do_t";
                }
            }
            else if(RootName.substr(0, 4) == "pptD")
            {
                if(AnyOne(Global::Warming_p, nhru, 1.0))
                {
                    newVar->CustomFunct = &ClassVar::do_ppt_Clim;
                    newVar->CustomFunctName = "do_ppt_Clim";
                }
                else
                {
                    newVar->CustomFunct = &ClassVar::do_ppt;
                    newVar->CustomFunctName = "do_ppt";
                }
            }
        } 
        else
            newVar->CustomFunct = NULL;
    } 
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::addtofunctlist(ClassVar*newVar) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
Administer::Administer(String Version, String _HelpFile) : Version(Version), HelpFile(_HelpFile)
{
freopen("c:\\injection.log", "a", stdout); printf("<Administer::Administer(StringVersion,String_HelpFile):Version(Version),HelpFile(_HelpFile) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    DLLModuleList = new TStringList;
    DLLModelList = new TStringList;
    DLLModelModuleList = new TStringList;
    if(Global::PendingDLLModuleList != NULL)
        Global::PendingDLLModuleList->Clear(); 
freopen("c:\\injection.log", "a", stdout); printf("</Administer::Administer(StringVersion,String_HelpFile):Version(Version),HelpFile(_HelpFile) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
Administer::~Administer()
{
freopen("c:\\injection.log", "a", stdout); printf("<Administer::~Administer() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < DLLModuleList->Count; ++ii)
        delete ((ClassModule*) DLLModuleList->Objects[ii]); 
    delete DLLModuleList;
    delete DLLModelList;
    delete DLLModelModuleList;
freopen("c:\\injection.log", "a", stdout); printf("</Administer::~Administer() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void Administer::MacroClear()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidAdminister::MacroClear() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < DLLModuleList->Count; ++ii)
    {
        int jj = Global::AllModulesList->IndexOf(DLLModuleList->Strings[ii]);
        if(jj > -1)
            Global::AllModulesList->Delete(jj);
        ClassModule* thisModule = (ClassModule*) DLLModuleList->Objects[ii];
        delete thisModule;
    }
    if (Global::OurHelpList)
    {
        int indx = Global::OurHelpList->IndexOf(HelpFile);
        if (indx > -1) 
            Global::OurHelpList->Delete(indx);
    }
    DLLModuleList->Clear();
    DLLModelList->Clear();
    DLLModelModuleList->Clear();
freopen("c:\\injection.log", "a", stdout); printf("</voidAdminister::MacroClear() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void Administer::MacroUpdate()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidAdminister::MacroUpdate() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < DLLModuleList->Count; ++ii)
    {
        int jj = Global::OurModulesList->IndexOf(DLLModuleList->Strings[ii]);
        if(jj > -1) 
            Global::OurModulesList->Objects[jj] = DLLModuleList->Objects[ii];
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidAdminister::MacroUpdate() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void Administer::AddModule(ClassModule *Module)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidAdminister::AddModule(ClassModule*Module) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    Module->OurAdmin = this;
    DLLModuleList->AddObject((Module)->Name.c_str(), (TObject*) Module);
    Global::PendingDLLModuleList->AddObject((Module)->Name.c_str(), (TObject*) Module);
freopen("c:\\injection.log", "a", stdout); printf("</voidAdminister::AddModule(ClassModule*Module) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void Administer::AddModel(String ModelName, String ModelModules)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidAdminister::AddModel(StringModelName,StringModelModules) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    DLLModelModuleList->Add(ModelModules);
    DLLModelList->AddObject(ModelName, (TObject*) (DLLModelModuleList->Count-1));
freopen("c:\\injection.log", "a", stdout); printf("</voidAdminister::AddModel(StringModelName,StringModelModules) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void Administer::LoadCRHM(String DllName)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidAdminister::LoadCRHM(StringDllName) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    DLLName = DllName;
freopen("c:\\injection.log", "a", stdout); printf("</voidAdminister::LoadCRHM(StringDllName) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void Administer::Accept(int Result)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidAdminister::Accept(intResult) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    String Exists;
    TMsgDlgType MsgDlgType;
    ClassModule* thisModule;
    for(int ii = 0; ii < DLLModuleList->Count; ++ii)   
    {
        if(Global::PendingDLLModuleList->Count > 0  
                && Global::PendingDLLModuleList->IndexOf(DLLModuleList->Strings[ii]) == -1)
            continue;
        int jj = Global::AllModulesList->IndexOf(DLLModuleList->Strings[ii]);
        if(jj != -1)
        {
            Exists = "Over-write existing module \"";
            MsgDlgType = mtWarning;
        }
        else
        {
            Exists = "Load Module \"";
            MsgDlgType = mtInformation;
        }
        if(Global::AllModulesList->IndexOf(DLLModuleList->Strings[ii]) == -1 
                && Global::OurModulesList->IndexOf(DLLModuleList->Strings[ii]) != -1)
            Result = mrYes;
        else if(Result != mrYesToAll && Result != mrNoToAll)  
        {
            Result = MessageDlg(Exists + DLLModuleList->Strings[ii] + "\" ?",
                                MsgDlgType,
                                TMsgDlgButtons() << mbYes << mbNo << mbYesToAll << mbNoToAll, 0);
        }
        switch(Result)
        {
        case mrYes :
        case mrYesToAll :
            if(jj != -1)
            {
                LogError(CRHMException((DLLModuleList->Strings[ii] + " module being replaced").c_str(), WARNING));
                Global::AllModulesList->Delete(jj);
            }
            thisModule = (ClassModule*) DLLModuleList->Objects[ii];
            thisModule->DLLName = DLLName;
            if(thisModule->DLLName != "Macro")
                thisModule->ID = typeid(*thisModule).name();
            Global::AllModulesList->AddObject(DLLModuleList->Strings[ii],
                                              (TObject*) DLLModuleList->Objects[ii]);
            break;
        case mrNo :
        case mrNoToAll :
            continue;
        }
    }
    for(int ii = 0; ii < DLLModelList->Count; ++ii)
    {
        Global::AllModelsList->AddObject(DLLModelList->Strings[ii], (TObject*) ii);
        Global::ModelModulesList->AddObject(DLLModelModuleList->Strings[ii], (TObject*) this);
    }
    if(Global::OurHelpList)
        if(Global::OurHelpList->IndexOf(HelpFile) < 0)  
            Global::OurHelpList->AddObject(HelpFile, (TObject*) 1);
        else
            Global::OurHelpList->AddObject(HelpFile, (TObject*) 0);
    Global::PendingDLLModuleList->Clear(); 
freopen("c:\\injection.log", "a", stdout); printf("</voidAdminister::Accept(intResult) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
Myparser::Myparser() 
{
freopen("c:\\injection.log", "a", stdout); printf("<Myparser::Myparser() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    exp_ptr = NULL;
freopen("c:\\injection.log", "a", stdout); printf("</Myparser::Myparser() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void Myparser::eval_exp(ClassPar *Par)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidMyparser::eval_exp(ClassPar*Par) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    LocalPar = Par;
    float result, Last;
    int stop;
    bool OpenBrkt;
    exp_ptr = Par->valstr.c_str();
    row = 0;
    col = 0;
    rowrepeat = 1;
    Bang = 0;
next:
    repeat = 1;
    repeatset = false;
    OpenBrkt = false;
    get_token();
    if(*token == '[')
        result = 0.0;
    else if(*token)
    {
        eval_exp2(result);
        if(result > Par->maxVal)
            result = Par->maxVal;
        if(result < Par->minVal)
            result = Par->minVal;
        Last = result;
    }
    else
        result = 0.0;
    bool end = !*exp_ptr;
    switch(*token)
    {
    case '\0' :
        if(col >= Par->dim)
            break;
        if(Par->varType == CRHM::Float)
            Par->layvalues[row][col++] = result;
        else if (Par->varType == CRHM::Int)
            Par->ilayvalues[row][col++] = result;
        for(int ll = row; ll < Par->lay; ++ll)
        {
            if(Bang)  
            {
                for(int ii = col-1; ii < Par->dim; ++ii)
                {
                    if(Par->varType == CRHM::Float)
                        Par->layvalues[ll][ii] = Last;
                    else if (Par->varType == CRHM::Int)
                        Par->ilayvalues[ll][ii] = Last;
                    Last += 1;
                }
            }
            else
            {
                for(int ii = col; ii < Par->dim; ++ii)
                    if(Par->varType == CRHM::Float)
                        Par->layvalues[ll][ii] = 0.0;
                    else if (Par->varType == CRHM::Int)
                        Par->ilayvalues[ll][ii] = 0.0;
            }
            col = 0;;
        }
        break;
    case '[' :
        rowrepeat = repeat;
        repeat = 1;
        repeatset = false;
        OpenBrkt = true;
        goto next;
    case ']' :
        OpenBrkt = false;
        while(isspace(*exp_ptr))
            ++exp_ptr; 
        if(*exp_ptr == ',')
            ++exp_ptr; 
        stop = col + repeat;
        if(stop > Par->dim)
            stop = Par->dim;
        for(int ii = col; ii < stop; ++ii)
            if(Par->varType == CRHM::Float)
                Par->layvalues[row][col++] = result;
            else if(Par->varType == CRHM::Int)
                Par->ilayvalues[row][col++] = result;
        for(int ii = col; ii < Par->dim; ++ii)
        {
            Last += Bang;
            if(Par->varType == CRHM::Float)
                Par->layvalues[row][ii] = Last;
            else if(Par->varType == CRHM::Int)
                Par->ilayvalues[row][ii] = Last;
        }
        Bang = 0;
        row++;
        col = 0;
        if(rowrepeat > 1 || end)
        {
            stop = row + rowrepeat-1;
            if(stop > Par->lay || end)
                stop = Par->lay;
            for(int ll = row; ll < stop; ++ll)
            {
                for(int ii = col; ii < Par->dim; ++ii)
                    if(Par->varType == CRHM::Float)
                        Par->layvalues[ll][ii] = Par->layvalues[ll-1][ii];
                    else if(Par->varType == CRHM::Int)
                        Par->ilayvalues[ll][ii] = Par->ilayvalues[ll-1][ii];
            }
            row = stop;
            rowrepeat = 1;
        }
        if(row >= Par->lay)
            break;
        goto next;
    case ',' :
        stop = col + repeat;
        if(stop > Par->dim)
            stop = Par->dim;
        for(int ii = col; ii < stop; ++ii)
            if(Par->varType == CRHM::Float)
                Par->layvalues[row][col++] = result;
            else if(Par->varType == CRHM::Int)
                Par->ilayvalues[row][col++] = result;
        if(col >= Par->dim)
            if(!OpenBrkt && (row+1 < Par->lay))
            {
                col = 0;
                ++row;
            }
        goto next;
    default :
        serror(0); 
        break;
    } 
freopen("c:\\injection.log", "a", stdout); printf("</voidMyparser::eval_exp(ClassPar*Par) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void Myparser::eval_exp2(float &result)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidMyparser::eval_exp2(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    register char op;
    float temp;
    eval_exp3(result);
    while((op = *token) == '+' || op == '-')
    {
        get_token();
        eval_exp3(temp);
        switch(op)
        {
        case '-':
            result = result - temp;
            break;
        case '+':
            result = result + temp;
            break;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidMyparser::eval_exp2(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void Myparser::eval_exp3(float &result)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidMyparser::eval_exp3(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    register char op;
    float temp;
    eval_exp4(result);
    while((op = *token) == '*' || op == '/' || op == '%')
    {
        get_token();
        if(op == '*' && !repeatset)
        {
            repeat = result;
            repeatset = true;
            if(*token == '[')
{freopen("c:\\injection.log", "a", stdout); printf("</voidMyparser::eval_exp3(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
            eval_exp4(result);
{freopen("c:\\injection.log", "a", stdout); printf("</voidMyparser::eval_exp3(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        eval_exp4(temp);
        switch(op)
        {
        case '*':
            result = result * temp;
            break;
        case '/':
            result = result / temp;
            break;
        case '%':
            result = (int) result % (int) temp;
            break;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidMyparser::eval_exp3(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void Myparser::eval_exp4(float &result)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidMyparser::eval_exp4(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    float temp, ex;
    register int t;
    eval_exp5(result);
    if(*token== '^')
    {
        get_token();
        eval_exp4(temp);
        if(temp==0.0)
        {
            result = 1.0;
{freopen("c:\\injection.log", "a", stdout); printf("</voidMyparser::eval_exp4(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
        }
        result = pow(result, temp);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidMyparser::eval_exp4(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void Myparser::eval_exp5(float &result)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidMyparser::eval_exp5(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    register char  op;
    op = 0;
    if((tok_type == DELIMITER) && *token=='+' || *token == '-')
    {
        op = *token;
        get_token();
    }
    eval_exp6(result);
    if(op=='-')
        result = -result;
freopen("c:\\injection.log", "a", stdout); printf("</voidMyparser::eval_exp5(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void Myparser::eval_exp6(float &result)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidMyparser::eval_exp6(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    if((*token == '('))
    {
        repeatset = true;
        get_token();
        eval_exp2(result);
        if(*token != ')')
            serror(1);
        get_token();
    }
    else
        atom(result);
freopen("c:\\injection.log", "a", stdout); printf("</voidMyparser::eval_exp6(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void Myparser::atom(float &result)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidMyparser::atom(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    switch(tok_type)
    {
    case NUMBER:
        result = atof(token);
        get_token();
{freopen("c:\\injection.log", "a", stdout); printf("</voidMyparser::atom(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    default:
        serror(0);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidMyparser::atom(float&result) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void Myparser::serror(int error)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidMyparser::serror(interror) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    static char *e[]=
    {
        "Syntax Error",
        "Unbalanced Parentheses",
        "No expression Present"
    };
    LogError(CRHMException(string(e[error]) + " in module '" +
                           LocalPar->module + "' parameter '" + LocalPar->param + "'", WARNING));
    for(int ll = row; ll < LocalPar->lay; ++ll)   
    {
        for(int ii = col; ii < LocalPar->dim; ++ii)
            if(LocalPar->varType == CRHM::Float)
                LocalPar->layvalues[ll][ii] = 0.0;
            else if(LocalPar->varType == CRHM::Int)
                LocalPar->ilayvalues[ll][ii] = 0;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidMyparser::serror(interror) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void Myparser::get_token()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidMyparser::get_token() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    register char *temp;
    tok_type = 0;
    temp = token;
    *temp = '\0';
    if(!*exp_ptr)
{freopen("c:\\injection.log", "a", stdout); printf("</voidMyparser::get_token() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    while(isspace(*exp_ptr))
        ++exp_ptr; 
    if(*exp_ptr == '!')  
    {
        Bang = 1;
        ++exp_ptr;
    }
    if((*exp_ptr) && strchr("+-*/%^=(),[]!", *exp_ptr))   
    {
        tok_type = DELIMITER;
        *temp++ = *exp_ptr++;
    }
    else if(isalpha(*exp_ptr))
    {
        while(!isdelim(*exp_ptr))
            *temp++ = *exp_ptr++;
        tok_type = CRHM::VARIABLE;
    }
    else if(isdigit(*exp_ptr))
    {
        while((*exp_ptr) && strchr("0123456789.",*exp_ptr))
            *temp++ = *exp_ptr++;
        if((*exp_ptr) && strchr("eE", *exp_ptr))
        {
            *temp++ = *exp_ptr++;
            while((*exp_ptr) && strchr("+- ", *exp_ptr))
                *temp++ = *exp_ptr++;
            while(!isdelim(*exp_ptr))
                *temp++ = *exp_ptr++;
        }
        tok_type = NUMBER;
    }
    *temp = '\0';
freopen("c:\\injection.log", "a", stdout); printf("</voidMyparser::get_token() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
int Myparser::isdelim(char c)
{
freopen("c:\\injection.log", "a", stdout); printf("<intMyparser::isdelim(charc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    if((*exp_ptr) && strchr(" +-/*%^=(),[]", c) || c==9 || c=='\r' || c==0)  
{freopen("c:\\injection.log", "a", stdout); printf("</intMyparser::isdelim(charc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 1;}
{freopen("c:\\injection.log", "a", stdout); printf("</intMyparser::isdelim(charc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
freopen("c:\\injection.log", "a", stdout); printf("</intMyparser::isdelim(charc) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
ClassClark::ClassClark(const float* inVar, float* outVar, const float* kstorage, const float* lag, const long nhru, const float setlag) : inVar(inVar), outVar(outVar), kstorage(kstorage), nhru(nhru)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassClark::ClassClark(constfloat*inVar,float*outVar,constfloat*kstorage,constfloat*lag,constlongnhru,constfloatsetlag):inVar(inVar),outVar(outVar),kstorage(kstorage),nhru(nhru) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    LastIn = new float[nhru];
    LastOut = new float[nhru];
    c01 = new float[nhru];
    c2 = new float[nhru];
    NO_lag_release = new float[nhru];
    ilag = new long[nhru];
    maxlag = new long[nhru];
    ulag = new long[nhru];
    for(long hh = 0; hh < nhru; hh++)
    {
        c01[hh] = Global::Interval*0.5/(kstorage[hh] + Global::Interval*0.5);  
        c2[hh] = (kstorage[hh] - Global::Interval*0.5)/(kstorage[hh] + Global::Interval*0.5); 
        ilag[hh] = max<float> (lag[hh], 0.0)/24.0*Global::Freq + 1.1; 
        if(setlag == -1 || ilag[hh] > setlag)
            maxlag[hh] = ilag[hh] + 1; 
        else
            maxlag[hh] = setlag + 1; 
        ulag[hh] = 0;
        LastIn[hh] = 0.0; 
        LastOut[hh] = 0.0; 
        NO_lag_release[hh] = 0.0; 
    }
    LagArray = new float*[nhru];   
    for(long hh = 0; hh < nhru; hh++)
    {
        LagArray[hh] = new float[maxlag[hh]];
        for(long jj = 0; jj < maxlag[hh]; jj++)
            LagArray[hh][jj] = 0.0;
    }
freopen("c:\\injection.log", "a", stdout); printf("</ClassClark::ClassClark(constfloat*inVar,float*outVar,constfloat*kstorage,constfloat*lag,constlongnhru,constfloatsetlag):inVar(inVar),outVar(outVar),kstorage(kstorage),nhru(nhru) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
ClassClark::~ClassClark()
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassClark::~ClassClark() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    delete[] LastIn;
    delete[] LastOut;
    delete[] c01;
    delete[] c2;
    delete[] NO_lag_release;
    delete[] ilag;
    delete[] maxlag;
    delete[] ulag;
    for(long hh = 0; hh < nhru; hh++)
        delete[] LagArray[hh];
    delete[] LagArray;
freopen("c:\\injection.log", "a", stdout); printf("</ClassClark::~ClassClark() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
float ClassClark::ChangeStorage(const float* kstorage, const long hh)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatClassClark::ChangeStorage(constfloat*kstorage,constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    float Last_c01 = c01[hh];
    float Last_c2 = c2[hh];
    if(c2[hh] >= 1.0) 
{freopen("c:\\injection.log", "a", stdout); printf("</floatClassClark::ChangeStorage(constfloat*kstorage,constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0.0;}
    float Sstorage = (1.0/(1.0 - c2[hh]))*(c01[hh]*LastIn[hh] + c2[hh]*outVar[hh]);
    c01[hh] = Global::Interval*0.5/(kstorage[hh] + Global::Interval*0.5);  
    c2[hh] = (kstorage[hh] - Global::Interval*0.5)/(kstorage[hh] + Global::Interval*0.5); 
    if(Sstorage <= 0.0 || Last_c01 == c01[hh])
{freopen("c:\\injection.log", "a", stdout); printf("</floatClassClark::ChangeStorage(constfloat*kstorage,constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0.0;}
    LastOut[hh] =  (Sstorage*(1.0 - c2[hh]) - c01[hh]*LastIn[hh])/c2[hh];
{freopen("c:\\injection.log", "a", stdout); printf("</floatClassClark::ChangeStorage(constfloat*kstorage,constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return Sstorage;}
freopen("c:\\injection.log", "a", stdout); printf("</floatClassClark::ChangeStorage(constfloat*kstorage,constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
float ClassClark::ChangeLag(const float *newlag, const long hh)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatClassClark::ChangeLag(constfloat*newlag,constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    float LastValue;
    float Lag_storage = 0.0;
    long newilag = max<float> (newlag[hh], 0.0)/24.0*Global::Freq + 1.1; 
    for(int ii = 1;  ii < ilag[hh]; ++ii)
        Lag_storage += LagArray[hh][(ulag[hh] + ii) % ilag[hh]];
    if(newilag == ilag[hh])
    {
{freopen("c:\\injection.log", "a", stdout); printf("</floatClassClark::ChangeLag(constfloat*newlag,constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return Lag_storage;}
    }
    float* AccArray = new float[ilag[hh]]; 
    AccArray[0] = 0.0;
    for(int ii = 1; ii < ilag[hh]; ++ii)
        AccArray[ii] = AccArray[ii-1] + LagArray[hh][(ulag[hh] + ii) % ilag[hh]]; 
    NO_lag_release[hh] = 0.0;
    delete[] LagArray[hh]; 
    LagArray[hh] = new float[newilag]; 
    ulag[hh] = 0; 
    LagArray[hh][ulag[hh]] = 0; 
    for(int ii = 1; ii < newilag; ++ii) 
        LagArray[hh][ii] = 0.0;
    if(newilag == 1)  
    {
        NO_lag_release[hh] = AccArray[ilag[hh]-1];
    }
    else if(ilag[hh] > 1 && AccArray[ilag[hh]-1] > 0.0)
    {
        LastValue = 0.0;
        for(int mm = 1; mm < newilag-1; ++mm)
        {
            float Y = float(mm)/(newilag-1)*(ilag[hh]-1);
            int Yint = Y + 0.0001;
            float Ydif = Y - Yint;
            float NewValue = AccArray[Yint] + Ydif*(AccArray[Yint+1] - AccArray[Yint]);
            LagArray[hh][(ulag[hh] + mm) % newilag] = NewValue - LastValue;
            LastValue = NewValue;
        }
        LagArray[hh][(ulag[hh] + newilag - 1) % newilag] =  AccArray[ilag[hh]-1] - LastValue; 
    }
    delete[] AccArray; 
    ilag[hh] = newilag; 
{freopen("c:\\injection.log", "a", stdout); printf("</floatClassClark::ChangeLag(constfloat*newlag,constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return Lag_storage;}
freopen("c:\\injection.log", "a", stdout); printf("</floatClassClark::ChangeLag(constfloat*newlag,constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassClark::DoClark()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassClark::DoClark() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    for(long hh = 0; hh < nhru; hh++)
    {
        LagArray[hh][ulag[hh]] = inVar[hh] + NO_lag_release[hh];
        NO_lag_release[hh] = 0.0;
        ulag[hh] = ++ulag[hh] % ilag[hh];
        outVar[hh] = c01[hh]*(LagArray[hh][ulag[hh]] + LastIn[hh]) + c2[hh]*LastOut[hh];
        LastIn[hh] = LagArray[hh][ulag[hh]];
        LastOut[hh] = outVar[hh];
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassClark::DoClark() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassClark::DoClark(const long hh)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassClark::DoClark(constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    LagArray[hh][ulag[hh]] = inVar[hh] + NO_lag_release[hh];
    NO_lag_release[hh] = 0.0;
    ulag[hh] = ++ulag[hh] % ilag[hh];  
    outVar[hh] = c01[hh]*(LagArray[hh][ulag[hh]] + LastIn[hh]) + c2[hh]*LastOut[hh];
    LastIn[hh] = LagArray[hh][ulag[hh]];
    LastOut[hh] = outVar[hh];
freopen("c:\\injection.log", "a", stdout); printf("</voidClassClark::DoClark(constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
float ClassClark::Left(int hh)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatClassClark::Left(inthh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    float Slag = 0;
    for(int ii = 1;  ii < ilag[hh]; ++ii)
        Slag += LagArray[hh][(ulag[hh] + ii) % ilag[hh]];
    if(c2[hh] >= 1.0)
{freopen("c:\\injection.log", "a", stdout); printf("</floatClassClark::Left(inthh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0.0;}
    float Sstorage = (1.0/(1.0 - c2[hh]))*(c01[hh]*LastIn[hh] + c2[hh]*outVar[hh]);
{freopen("c:\\injection.log", "a", stdout); printf("</floatClassClark::Left(inthh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return Slag + Sstorage;}
freopen("c:\\injection.log", "a", stdout); printf("</floatClassClark::Left(inthh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
ClassMuskingum::ClassMuskingum(const float* inVar, float* outVar, const float* k, const float* X_M, const float* lag, const long nhru, const float setlag) : inVar(inVar), outVar(outVar), nhru(nhru)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassMuskingum::ClassMuskingum(constfloat*inVar,float*outVar,constfloat*k,constfloat*X_M,constfloat*lag,constlongnhru,constfloatsetlag):inVar(inVar),outVar(outVar),nhru(nhru) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    LastIn = new float[nhru];
    LastOut = new float[nhru];
    c0 = new float[nhru];
    c1 = new float[nhru];
    c2 = new float[nhru];
    ilag = new long[nhru];
    maxlag = new long[nhru];
    ulag = new long[nhru];
    long Biggest = 0;
    for(long hh = 0; hh < nhru; hh++)
    {
        c0[hh] = (Global::Interval - 2.0*k[hh]*X_M[hh])/
                 (2.0*k[hh]*(1.0 - X_M[hh]) + Global::Interval);  
        c1[hh] = (Global::Interval + 2.0*k[hh]*X_M[hh])/
                 (2.0*k[hh]*(1.0 - X_M[hh]) + Global::Interval); 
        c2[hh] = (2.0*k[hh]*(1.0 - X_M[hh]) - Global::Interval)/
                 (2.0*k[hh]*(1.0 - X_M[hh]) + Global::Interval); 
        ilag[hh] = max<float> (lag[hh], 0.0)/24.0*Global::Freq + 1.1; 
        if(setlag == -1 || ilag[hh] > setlag)
            maxlag[hh] = ilag[hh];
        else
            maxlag[hh] = setlag;
        ulag[hh] = 0;
        LastIn[hh] = 0.0; 
        LastOut[hh] = 0.0; 
        if(maxlag[hh] > Biggest)
            Biggest = maxlag[hh];
    }
    LagArray = new float*[nhru];   
    for(long hh = 0; hh < nhru; hh++)
    {
        LagArray[hh] = new float[maxlag[hh]];
        for(long jj = 0; jj < maxlag[hh]; jj++)
            LagArray[hh][jj] = 0.0;
    }
freopen("c:\\injection.log", "a", stdout); printf("</ClassMuskingum::ClassMuskingum(constfloat*inVar,float*outVar,constfloat*k,constfloat*X_M,constfloat*lag,constlongnhru,constfloatsetlag):inVar(inVar),outVar(outVar),nhru(nhru) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
ClassMuskingum::~ClassMuskingum()
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassMuskingum::~ClassMuskingum() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    delete[] LastIn;
    delete[] LastOut;
    delete[] c0;
    delete[] c1;
    delete[] c2;
    delete[] ilag;
    delete[] maxlag;
    delete[] ulag;
    for(long hh = 0; hh < nhru; hh++)
        delete[] LagArray[hh];
    delete[] LagArray;
freopen("c:\\injection.log", "a", stdout); printf("</ClassMuskingum::~ClassMuskingum() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassMuskingum::ChangeLag(const float *newlag, const long hh)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassMuskingum::ChangeLag(constfloat*newlag,constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    long newilag = max<float> (newlag[hh], 0.0)/24.0*Global::Freq + 1.1; 
    if(newilag == ilag[hh])
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassMuskingum::ChangeLag(constfloat*newlag,constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    float* AccArray = new float[ilag[hh]]; 
    AccArray[0] = 0.0;
    for(int ii = 1; ii < ilag[hh]; ++ii)
        AccArray[ii] = AccArray[ii-1] + LagArray[hh][(ulag[hh] + ii) % ilag[hh]]; 
    delete[] LagArray[hh]; 
    LagArray[hh] = new float[newilag]; 
    ulag[hh] = 0; 
    LagArray[hh][0] = 0.0; 
    float LastValue = 0.0;
    for(int mm = 1; mm < newilag-1; ++mm)
    {
        float Y = float(mm)/(newilag-1)*(ilag[hh]-1);
        int Yint = Y + 0.0001;
        float Ydif = Y - Yint;
        float NewValue = AccArray[Yint] + Ydif*(AccArray[Yint+1] - AccArray[Yint]);
        LagArray[hh][(ulag[hh] + mm) % newilag] = NewValue - LastValue;
        LastValue = NewValue;
    }
    LagArray[hh][(ulag[hh] + newilag-1) % newilag] =  AccArray[ilag[hh]-1] - LastValue; 
    delete[] AccArray; 
    ilag[hh] = newilag; 
freopen("c:\\injection.log", "a", stdout); printf("</voidClassMuskingum::ChangeLag(constfloat*newlag,constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassMuskingum::DoMuskingum()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassMuskingum::DoMuskingum() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    for(long hh = 0; hh < nhru; hh++)
    {
        LagArray[hh][ulag[hh]] = inVar[hh];
        ulag[hh] = ++ulag[hh] % ilag[hh];
        outVar[hh] = c0[hh]*LagArray[hh][ulag[hh]] + c1[hh]*LastIn[hh] + c2[hh]*LastOut[hh];
        LastIn[hh] = LagArray[hh][ulag[hh]];
        LastOut[hh] = outVar[hh];
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassMuskingum::DoMuskingum() @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassMuskingum::DoMuskingum(const long hh)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassMuskingum::DoMuskingum(constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    LagArray[hh][ulag[hh]] = inVar[hh];
    ulag[hh] = ++ulag[hh] % ilag[hh];  
    outVar[hh] = c0[hh]*LagArray[hh][ulag[hh]] + c1[hh]*LastIn[hh] + c2[hh]*LastOut[hh];
    LastIn[hh] = LagArray[hh][ulag[hh]];
    LastOut[hh] = outVar[hh];
freopen("c:\\injection.log", "a", stdout); printf("</voidClassMuskingum::DoMuskingum(constlonghh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
float ClassMuskingum::Left(int hh)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatClassMuskingum::Left(inthh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    float Slag = 0;
    for(int ii = 1;  ii < ilag[hh]; ++ii)
        Slag += LagArray[hh][(ulag[hh] + ii) % ilag[hh]];
    float Sstorage = (1.0/(1.0 - c2[hh]))*(c1[hh]*LastIn[hh] + c2[hh]*outVar[hh]);
{freopen("c:\\injection.log", "a", stdout); printf("</floatClassMuskingum::Left(inthh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return Slag + Sstorage;}
freopen("c:\\injection.log", "a", stdout); printf("</floatClassMuskingum::Left(inthh) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::getdim(CRHM::TDim dimen)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::getdim(CRHM::TDimdimen) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapDim::iterator itDim;
    string s;
    switch(dimen)
    {
    case CRHM::BASIN:
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::getdim(CRHM::TDimdimen) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return ((int) CRHM::ONE);}
    case CRHM::ONE:
    case CRHM::TWO:
    case CRHM::THREE:
    case CRHM::FOUR:
    case CRHM::FIVE:
    case CRHM::SIX:
    case CRHM::SEVEN:
    case CRHM::EIGHT:
    case CRHM::NINE:
    case CRHM::TEN:
    case CRHM::ELEVEN:
    case CRHM::TWELVE:
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::getdim(CRHM::TDimdimen) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return ((int) dimen);}
    case CRHM::NHRU:
        if(nhru)
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::getdim(CRHM::TDimdimen) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return (nhru);}
        else
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::getdim(CRHM::TDimdimen) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return (Global::nhru);}
    case CRHM::NOBS:
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::getdim(CRHM::TDimdimen) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return (Global::nhru);}
    case CRHM::NLAY:
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::getdim(CRHM::TDimdimen) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return (Global::nlay);}
    default:
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::getdim(CRHM::TDimdimen) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return (-1);}
    }
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::getdim(CRHM::TDimdimen) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
TAKA AKAtype(string type)
{
freopen("c:\\injection.log", "a", stdout); printf("<TAKAAKAtype(stringtype) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    TAKA Type = AKAERROR;
    for(int ii = VARG; ii < AKAEND; ++ii)
        if(type == AKAstrings[ii])
        {
            Type = (TAKA) ii;
            break;
        }
{freopen("c:\\injection.log", "a", stdout); printf("</TAKAAKAtype(stringtype) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return Type;}
freopen("c:\\injection.log", "a", stdout); printf("</TAKAAKAtype(stringtype) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
bool ClassModule::Variation_Skip(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<boolClassModule::Variation_Skip(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    if(Global::BuildFlag == CRHM::BUILD && variation == 0 ||                    
            (variation_set & 2048) != 0 && variation == 0 ||                        
            (variation_set & 4096) != 0 ||                        
            (variation_set  == 0) ||                                                
            (variation_set & variation) != 0)                                       
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::Variation_Skip(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return false;}
    else
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::Variation_Skip(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return true;}
freopen("c:\\injection.log", "a", stdout); printf("</boolClassModule::Variation_Skip(void) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::declputparam(string source, string param, string units, float **value, float ***layvalue)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::declputparam(stringsource,stringparam,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *newPar;
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputparam(stringsource,stringparam,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return -1;}
    }
    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString(Name, param, units);
    AKAhook(PARD, Name, param, param); 
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        PairstrV Item2 = PairstrV(param.c_str(), variation_set);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclpar.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputparam(stringsource,stringparam,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return -1;}
    }
    case CRHM::DECL:    
    {
        if((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end())
        {
            newPar = (*itPar).second;
            newPar->Inhibit_share = 1;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputparam(stringsource,stringparam,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
        }
        if((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
        {
            if((*itPar).second->dim == this->nhru)
                newPar = (*itPar).second;
            newPar->Inhibit_share = 1;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputparam(stringsource,stringparam,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
        }
        newPar = new ClassPar(string(Name.c_str()), string(param), CRHM::NHRU, "", 0, 0, "", units, CRHM::Float);
        newPar->basemodule = this->NameRoot;
        newPar->variation_set = variation_set;
        newPar->visibility = CRHM::USUAL;
        if(this->GroupCnt)
            newPar->Inhibit_share = 2;
        Myparser ob;
        ob.eval_exp(newPar);
        PairPar Item = PairPar(Name + " " + param, newPar);
        Global::MapPars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputparam(stringsource,stringparam,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return -1;}
    }
    case CRHM::INIT:
    {
        if(source[0] != '*')
        {
            if((itPar = Global::MapPars.find(source + " " + param)) != Global::MapPars.end())
            {
                newPar = (*itPar).second;
                if(newPar->Inhibit_share != 2)  
                {
                    *value = newPar->values;
                    if(layvalue != NULL)
                        const_cast<float **> (*layvalue) = newPar->layvalues;
                }
            }
        }
        else
        {
            if((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end())
            {
                newPar = (*itPar).second;
                *value = newPar->values;
                if(layvalue != NULL)
                    const_cast<float **> (*layvalue) = newPar->layvalues;
            }
            else if((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
            {
                newPar = (*itPar).second;
                if(newPar->Inhibit_share != 2)  
                {
                    *value = newPar->values;
                    if(layvalue != NULL)
                        const_cast<float **> (*layvalue) = newPar->layvalues;
                }
            }
            else if(newPar = ClassParFindPar(param))
            {
                if(newPar->Inhibit_share != 2)  
                {
                    *value = newPar->values;
                    if(layvalue != NULL)
                        const_cast<float **> (*layvalue) = newPar->layvalues;
                }
            }
            else
            {
                CRHMException Except("Parameter not found: " + Name + " " + param, TERMINATE);
                LogError(Except);
                throw Except; 
            }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputparam(stringsource,stringparam,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
        }
    } 
    } 
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputparam(stringsource,stringparam,stringunits,float**value,float***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::declgetparam(string source, string param, string units, const float **value, const float ***layvalue)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::declgetparam(stringsource,stringparam,stringunits,constfloat**value,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *newPar;
    if(Variation_Skip())
    {
        *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetparam(stringsource,stringparam,stringunits,constfloat**value,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return -1;}
    }
    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString(Name, param, units);
    AKAhook(PARD, Name, param, param); 
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        PairstrV Item2 = PairstrV(param.c_str(), variation_set);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclpar.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetparam(stringsource,stringparam,stringunits,constfloat**value,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return -1;}
    }
    case CRHM::DECL:
    {
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetparam(stringsource,stringparam,stringunits,constfloat**value,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return -1;}
    }
    case CRHM::INIT:
    {
        if(source[0] != '*')
        {
            if((itPar = Global::MapPars.find(source + " " + param)) != Global::MapPars.end())
            {
                newPar = (*itPar).second;
                *value = newPar->values;
                if(layvalue != NULL)
                    const_cast<float **> (*layvalue) = newPar->layvalues;
            }
        }
        else
        {
            if((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end())
            {
                newPar = (*itPar).second;
                *value = newPar->values;
                if(layvalue != NULL)
                    const_cast<float **> (*layvalue) = newPar->layvalues;
            }
            else if((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
            {
                newPar = (*itPar).second;
                *value = newPar->values;
                if(layvalue != NULL)
                    const_cast<float **> (*layvalue) = newPar->layvalues;
            }
            else if(newPar = ClassParFindPar(param))
            {
                *value = newPar->values;
                if(layvalue != NULL)
                    const_cast<float **> (*layvalue) = newPar->layvalues;
            }
            else
            {
                CRHMException Except("Parameter not found: " + Name + " " + param, TERMINATE);
                LogError(Except);
                throw Except; 
            }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetparam(stringsource,stringparam,stringunits,constfloat**value,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
        }
    } 
    } 
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declgetparam(stringsource,stringparam,stringunits,constfloat**value,constfloat***layvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::FindModule_from_parameter(string source, string param)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::FindModule_from_parameter(stringsource,stringparam) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *newPar;
    variation_max = variation_max | variation_set;
    AKAhook(PARD, Name, param, param); 
    if(source[0] != '*')
    {
        if((itPar = Global::MapPars.find(source + " " + param)) != Global::MapPars.end())
        {
            newPar = (*itPar).second;
        }
    }
    else
    {
        if((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end())
        {
            newPar = (*itPar).second;
        }
        else if((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
        {
            newPar = (*itPar).second;
        }
        else if(newPar = ClassParFindPar(param))
        {
        }
        else
        {
            CRHMException Except("Parameter not found: " + Name + " " + param, TERMINATE);
            LogError(Except);
            throw Except; 
        }
    }
    if(GroupCnt)
    {
        long ii = Global::OurModulesList->IndexOf(Name.c_str()); 
        ClassMacro* macro = (ClassMacro*) Global::OurModulesList->Objects[ii]; 
        long jj = macro->GrpStringList->IndexOf(newPar->basemodule.c_str()); 
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::FindModule_from_parameter(stringsource,stringparam) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return    (long) macro->GrpStringList->Objects[jj];}
    }
    else
    {
        long ii = Global::OurModulesList->IndexOf(newPar->basemodule.c_str());
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::FindModule_from_parameter(stringsource,stringparam) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return    (long) Global::OurModulesList->Objects[ii];}
    }
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::FindModule_from_parameter(stringsource,stringparam) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
long ClassModule::declputparam(string source, string param, string units, long **ivalue, long ***ilayvalue)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassModule::declputparam(stringsource,stringparam,stringunits,long**ivalue,long***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *newPar;
    if(Variation_Skip())
    {
        *ivalue = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputparam(stringsource,stringparam,stringunits,long**ivalue,long***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return -1;}
    }
    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString(Name, param, units);
    AKAhook(PARD, Name, param, param); 
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        PairstrV Item2 = PairstrV(param.c_str(), variation_set);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclpar.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputparam(stringsource,stringparam,stringunits,long**ivalue,long***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return -1;}
    }
    case CRHM::DECL:
    {
        if((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end())
        {
            newPar = (*itPar).second;
            newPar->Inhibit_share = 1;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputparam(stringsource,stringparam,stringunits,long**ivalue,long***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
        }
        if((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
        {
            if((*itPar).second->dim == this->nhru)
                newPar = (*itPar).second;
            newPar->Inhibit_share = 1;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputparam(stringsource,stringparam,stringunits,long**ivalue,long***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
        }
        newPar = new ClassPar(string(Name.c_str()), string(param), CRHM::NHRU, "", 0, 0, "", units, CRHM::Int);
        newPar->basemodule = this->NameRoot;
        newPar->variation_set = variation_set;
        newPar->visibility = CRHM::USUAL;
        newPar->Inhibit_share = 2;
        Myparser ob;
        ob.eval_exp(newPar);
        PairPar Item = PairPar(Name + " " + param, newPar);
        Global::MapPars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputparam(stringsource,stringparam,stringunits,long**ivalue,long***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return -1;}
    }
    case CRHM::INIT:
    {
        if(source[0] != '*')
        {
            if((itPar = Global::MapPars.find(source + " " + param)) != Global::MapPars.end())
            {
                newPar = (*itPar).second;
                if(newPar->Inhibit_share != 2)  
                {
                    *ivalue = newPar->ivalues;
                    if(ilayvalue != NULL)
                        const_cast<long **> (*ilayvalue) = newPar->ilayvalues;
                }
            }
        }
        else
        {
            if((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end())
            {
                newPar = (*itPar).second;
                *ivalue = newPar->ivalues;
                if(ilayvalue != NULL)
                    const_cast<long **> (*ilayvalue) = newPar->ilayvalues;
            }
            else if((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
            {
                newPar = (*itPar).second;
                if(newPar->Inhibit_share != 2)  
                {
                    *ivalue = newPar->ivalues;
                    if(ilayvalue != NULL)
                        const_cast<long **> (*ilayvalue) = newPar->ilayvalues;
                }
            }
            else if(newPar = ClassParFindPar(param))   
            {
                if(newPar->Inhibit_share != 2)  
                {
                    *ivalue = newPar->ivalues;
                    if(ilayvalue != NULL)
                        const_cast<long **> (*ilayvalue) = newPar->ilayvalues;
                }
            }
            else
            {
                CRHMException Except("Parameter not found: " + Name + " " + param, TERMINATE);
                LogError(Except);
                throw Except;
            }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputparam(stringsource,stringparam,stringunits,long**ivalue,long***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return 0;}
        }
    } 
    } 
freopen("c:\\injection.log", "a", stdout); printf("</longClassModule::declputparam(stringsource,stringparam,stringunits,long**ivalue,long***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
void ClassModule::declgetparam(string source, string param, string units, const long **ivalue, const long ***ilayvalue)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassModule::declgetparam(stringsource,stringparam,stringunits,constlong**ivalue,constlong***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *newPar;
    if(Variation_Skip())
    {
        *ivalue = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declgetparam(stringsource,stringparam,stringunits,constlong**ivalue,constlong***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString(Name, param, units);
    AKAhook(PARD, Name, param, param); 
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        PairstrV Item2 = PairstrV(param.c_str(), variation_set);
        PairstrI Item = PairstrI(Name.c_str(), Item2);
        Global::Mapdeclpar.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declgetparam(stringsource,stringparam,stringunits,constlong**ivalue,constlong***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    case CRHM::DECL:
    {
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declgetparam(stringsource,stringparam,stringunits,constlong**ivalue,constlong***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
    }
    case CRHM::INIT:
    {
        if(source[0] != '*')
        {
            if((itPar = Global::MapPars.find(source + " " + param)) != Global::MapPars.end())
            {
                newPar = (*itPar).second;
                *ivalue = newPar->ivalues;
                if(ilayvalue != NULL)
                    const_cast<long **> (*ilayvalue) = newPar->ilayvalues;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declgetparam(stringsource,stringparam,stringunits,constlong**ivalue,constlong***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
            }
        }
        else
        {
            if((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end())
            {
                newPar = (*itPar).second;
                *ivalue = newPar->ivalues;
                if(ilayvalue != NULL)
                    const_cast<long **> (*ilayvalue) = newPar->ilayvalues;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declgetparam(stringsource,stringparam,stringunits,constlong**ivalue,constlong***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
            }
            else if((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
            {
                newPar = (*itPar).second;
                *ivalue = newPar->ivalues;
                if(ilayvalue != NULL)
                    const_cast<long **> (*ilayvalue) = newPar->ilayvalues;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declgetparam(stringsource,stringparam,stringunits,constlong**ivalue,constlong***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
            }
            else if(newPar = ClassParFindPar(param))   
            {
                *ivalue = newPar->ivalues;
                if(ilayvalue != NULL)
                    const_cast<long **> (*ilayvalue) = newPar->ilayvalues;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declgetparam(stringsource,stringparam,stringunits,constlong**ivalue,constlong***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return;}
            }
            else
            {
                CRHMException Except("Parameter not found: " + Name + " " + param, TERMINATE);
                LogError(Except);
                throw Except;
            }
        }
    } 
    } 
freopen("c:\\injection.log", "a", stdout); printf("</voidClassModule::declgetparam(stringsource,stringparam,stringunits,constlong**ivalue,constlong***ilayvalue) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
ClassModule* ClassModule::link(string Module)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassModule*ClassModule::link(stringModule) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
    if(Name == Module.c_str())
{freopen("c:\\injection.log", "a", stdout); printf("</ClassModule*ClassModule::link(stringModule) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return NULL;}
    int jj = Global::OurModulesList->IndexOf(Module.c_str());
    if(jj == -1)
{freopen("c:\\injection.log", "a", stdout); printf("</ClassModule*ClassModule::link(stringModule) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return NULL;}
    else
{freopen("c:\\injection.log", "a", stdout); printf("</ClassModule*ClassModule::link(stringModule) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);return (ClassModule*) Global::OurModulesList->Objects[jj];}
freopen("c:\\injection.log", "a", stdout); printf("</ClassModule*ClassModule::link(stringModule) @@@ ClassModule.cpp_nocom>\n"); fclose(stdout);
}
