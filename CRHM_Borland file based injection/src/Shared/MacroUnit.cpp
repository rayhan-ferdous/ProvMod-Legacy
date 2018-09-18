#pragma hdrstop
#include "MacroUnit.h"
#include <map>
#pragma package(smart_init)
#include "CRHM_parse.h"
#include "boost/spirit/error_handling/exceptions.hpp"
extern double xLimit;
float Fday()   
{
freopen("c:\\injection.log", "a", stdout); printf("<floatFday() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    unsigned short year, month, day;
    Global::DTnow.DecodeDate(&year, &month, &day);
{freopen("c:\\injection.log", "a", stdout); printf("</floatFday() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return day;}
freopen("c:\\injection.log", "a", stdout); printf("</floatFday() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
float Fmonth()   
{
freopen("c:\\injection.log", "a", stdout); printf("<floatFmonth() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    unsigned short year, month, day;
    Global::DTnow.DecodeDate(&year, &month, &day);
{freopen("c:\\injection.log", "a", stdout); printf("</floatFmonth() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return month;}
freopen("c:\\injection.log", "a", stdout); printf("</floatFmonth() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
float Fyear()   
{
freopen("c:\\injection.log", "a", stdout); printf("<floatFyear() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    unsigned short year, month, day;
    Global::DTnow.DecodeDate(&year, &month, &day);
{freopen("c:\\injection.log", "a", stdout); printf("</floatFyear() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return year;}
freopen("c:\\injection.log", "a", stdout); printf("</floatFyear() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
float Fjulian()   
{
freopen("c:\\injection.log", "a", stdout); printf("<floatFjulian() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</floatFjulian() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return julian("now");}
freopen("c:\\injection.log", "a", stdout); printf("</floatFjulian() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
float Fgetstep()   
{
freopen("c:\\injection.log", "a", stdout); printf("<floatFgetstep() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</floatFgetstep() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return getstep();}
freopen("c:\\injection.log", "a", stdout); printf("</floatFgetstep() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
float Fgetfirst()   
{
freopen("c:\\injection.log", "a", stdout); printf("<floatFgetfirst() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</floatFgetfirst() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return (getstep()%Global::Freq == 1);}
freopen("c:\\injection.log", "a", stdout); printf("</floatFgetfirst() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
float Fgetlast()   
{
freopen("c:\\injection.log", "a", stdout); printf("<floatFgetlast() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</floatFgetlast() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return (getstep()%Global::Freq == 0);}
freopen("c:\\injection.log", "a", stdout); printf("</floatFgetlast() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
float Fgetrand()   
{
freopen("c:\\injection.log", "a", stdout); printf("<floatFgetrand() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</floatFgetrand() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return (float) rand()/RAND_MAX;}
freopen("c:\\injection.log", "a", stdout); printf("</floatFgetrand() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
ClassMacro* ClassMacro::klone(string name) const
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassMacro*ClassMacro::klone(stringname)const @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</ClassMacro*ClassMacro::klone(stringname)const @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return new ClassMacro(name, MacroBegin,  "11/13/07");}
freopen("c:\\injection.log", "a", stdout); printf("</ClassMacro*ClassMacro::klone(stringname)const @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void ClassMacro::decl(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassMacro::decl(void) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    if(isGroup || isStruct)
    {
        this->ObsModule = NULL;
        if(Grpnhru > 0)
        {
            nhru = Grpnhru;
            if(Grpnhru > Global::maxhru)
                Global::maxhru = Grpnhru;
        }
        else if(nhru == 0)
            nhru = Global::nhru; 
        String S(max<long>(GroupCnt, StructCnt));
        if(isGroup)
        {
            declparam("HRU_group", CRHM::NHRU, S.c_str(), "1", "1e3", "group #", "()", &HRU_group);
        }
        if(isStruct)
        {
            String Choice = GrpStringList->CommaText;
            declparam("HRU_struct", CRHM::NHRU, "[1]", "1", String(GrpStringList->Count).c_str(), String("select using 1/2/3 ... module/group from '" + Choice + "'").c_str(), "()", &HRU_struct); 
        }
        Modules.clear();
        long Variation;
        for(int ii = 0; ii < GrpStringList->Count; ++ii)
        {
            String S = GrpStringList->Strings[ii];
            int idx = S.Pos("#");
            if(idx > 0)
            {
                Variation = pow(2, S[idx+1] - char('1'));
                S = S.SubString(1, idx-1);
            }
            else
                Variation = 0;
            int Indx = Global::AllModulesList->IndexOf(S);
            if(Indx == -1)
            {
                Application->MessageBox(String("Module: '" + S + "' not found!").c_str(), "Macro Error", MB_OK);
                CRHMException Except(string(string("module: ") + S.c_str() + " not found in " + Name).c_str(), TERMINATE);
                LogError(Except);
                throw Except;
            }
            ClassModule* Mod = (ClassModule*) Global::AllModulesList->Objects[Indx];
            ModulePtr Test(Mod->klone(Name));
            boost::weak_ptr<ClassModule> MG(Test);
            String S1 = typeid( *Mod).name();
            String S2 = typeid( *Test).name();
            if(S2 == "ClassMacro")
                Test->ID = S.c_str();
            else
            {
                Test->ID = typeid( *Test).name();
                if(S2 == "Classobs")
                    this->ObsModule = (ClassModule*) Test.get(); 
            }
            Test->HRU_struct = this->HRU_struct;
            Test->nhru = nhru;
            Test->GroupCnt = this->GroupCnt;
            Test->StructCnt = this->StructCnt;
            Test->variation = Variation;
            Test->DLLName = Mod->DLLName;
            Test->NameRoot = Mod->NameRoot;
            Test->Version = this->Version;
            if(isStruct)
                Test->ModuleIndx = ii+1;
            else
                Test->ModuleIndx = this->ModuleIndx;
            Modules.push_back(Test);
        }
        list<ModulePtr> ::iterator iterM;
        iterM = Modules.begin();
        while(iterM != Modules.end())
        {
            ClassModule* MPP = (ClassModule*) (*iterM).get();
            String SS = (*iterM)->NameRoot.c_str();
            if((*iterM)->variation > 0)  
            {
                String  AA = "#0";
                AA[2] += log((*iterM)->variation)/log(2) + 1;
                SS += AA;
            }
            long jj = GrpStringList->IndexOf(SS); 
            GrpStringList->Objects[jj] = (TObject *) MPP; 
            (*iterM)->nhru = nhru;
            (*iterM)->decl();
            ++iterM;
        }
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassMacro::decl(void) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return;}
    }
    list<DefCRHMPtr> ::iterator iterC; 
    iterC = Calls.begin();
    while(iterC != Calls.end())
    {
        boost::weak_ptr<DefCRHM> CP((*iterC));
        (*iterC)->CallDecl();
        ++iterC;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassMacro::decl(void) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void ClassMacro::init(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassMacro::init(void) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    nhru = getdim(CRHM::NHRU); 
    if(isGroup || isStruct)
    {
        LogMessage(" ");
        String SS;
        if(isGroup)
            SS = "Group: '" + String(NameRoot.c_str() + String("' ->"));
        else
            SS = "Struct: '" + String(NameRoot.c_str() + String("' ->"));
        for(int ii = 0; ii < GrpStringList->Count; ++ii)
            SS += " " + GrpStringList->Strings[ii];
        LogMessage(SS.c_str());
        list<ModulePtr> ::iterator iter;
        iter = Modules.begin();
        while(iter != Modules.end())
        {
            boost::weak_ptr<ClassModule> MP((*iter));
            (*iter)->init();
            ++iter;
        }
        if(StructCnt) 
            for(hh = 0; hh < nhru; ++hh)
            {
                if(HRU_struct[hh] < 1)
                    const_cast<long *>  (HRU_struct)[hh] = 1;
                if(HRU_struct[hh] > GrpStringList->Count)
                    const_cast<long *>  (HRU_struct)[hh]  = GrpStringList->Count;
            }
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassMacro::init(void) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return;}
    }
    list<DefCRHMPtr> ::iterator iter;
    iter = Calls.begin();
    while(iter != Calls.end())
    {
        DefCRHM Op = (*(*iter));
        (*iter)->CallInit(nhru, nlay);
        ++iter;
    }
    FP = vars.find("hh");
    if(FP == vars.end())
    {
        vars.insert(make_pair("hh", VarCHRM()));
        FP = vars.find("hh");
    }
    FP->second.kind = VarCHRM::CRHMint;
    FP->second.ivalue = const_cast<long*> (&hh);
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "hh";
    FP->second.Me = this;
    FP = vars.find("NHRU");
    if(FP == vars.end())
    {
        vars.insert(make_pair("NHRU", VarCHRM()));
        FP = vars.find("NHRU");
    }
    FP->second.kind = VarCHRM::LOCAL;
    FP->second.val = nhru;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "NHRU";
    FP->second.Me = this;
    FP = vars.find("GROUP");
    if(FP == vars.end())
    {
        vars.insert(make_pair("GROUP", VarCHRM()));
        FP = vars.find("GROUP");
    }
    FP->second.kind = VarCHRM::LOCAL;
    FP->second.val = GroupCnt;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "GROUP";
    FP->second.Me = this;
    FP = vars.find("STRUCT");
    if(FP == vars.end())
    {
        vars.insert(make_pair("STRUCT", VarCHRM()));
        FP = vars.find("STRUCT");
    }
    FP->second.kind = VarCHRM::LOCAL;
    FP->second.val = StructCnt;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "STRUCT";
    FP->second.Me = this;
    FP = vars.find("PI");
    if(FP == vars.end())
    {
        vars.insert(make_pair("PI", VarCHRM()));
        FP = vars.find("PI");
    }
    FP->second.kind = VarCHRM::LOCAL;
    FP->second.val = M_PI;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "PI";
    FP = vars.find("NO_DISPLAY");
    if(FP == vars.end())
    {
        vars.insert(make_pair("NO_DISPLAY", VarCHRM()));
        FP = vars.find("NO_DISPLAY");
    }
    FP->second.kind = VarCHRM::LOCAL;
    FP->second.val = xLimit;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "NO_DISPLAY";
    FP = vars.find("FREQ");
    if(FP == vars.end())
    {
        vars.insert(make_pair("FREQ", VarCHRM()));
        FP = vars.find("FREQ");
    }
    FP->second.kind = VarCHRM::LOCAL;
    FP->second.val = Global::Freq;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "FREQ";
    FP = vars.find("RAND");
    if(FP == vars.end())
    {
        vars.insert(make_pair("RAND", VarCHRM()));
        FP = vars.find("RAND");
    }
    FP->second.kind = VarCHRM::FUNget;
    FP->second.val = 0;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "RAND";
    FP->second.pget = Fgetrand;
    FP = vars.find("STEP");
    if(FP == vars.end())
    {
        vars.insert(make_pair("STEP", VarCHRM()));
        FP = vars.find("STEP");
    }
    FP->second.kind = VarCHRM::FUNget;
    FP->second.val = 0;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "STEP";
    FP->second.pget = Fgetstep;
    FP = vars.find("LASTINT");
    if(FP == vars.end())
    {
        vars.insert(make_pair("LASTINT", VarCHRM()));
        FP = vars.find("LASTINT");
    }
    FP->second.kind = VarCHRM::FUNget;
    FP->second.val = 0;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "LASTINT";
    FP->second.pget = Fgetlast;
    FP = vars.find("FIRSTINT");
    if(FP == vars.end())
    {
        vars.insert(make_pair("FIRSTINT", VarCHRM()));
        FP = vars.find("FIRSTINT");
    }
    FP->second.kind = VarCHRM::FUNget;
    FP->second.val = 0;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "FIRSTINT";
    FP->second.pget = Fgetfirst;
    FP = vars.find("JULIAN");
    if(FP == vars.end())
    {
        vars.insert(make_pair("JULIAN", VarCHRM()));
        FP = vars.find("JULIAN");
    }
    FP->second.kind = VarCHRM::FUNget;
    FP->second.val = 0;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "JULIAN";
    FP->second.pget = Fjulian;
    FP = vars.find("YEAR");
    if(FP == vars.end())
    {
        vars.insert(make_pair("YEAR", VarCHRM()));
        FP = vars.find("YEAR");
    }
    FP->second.kind = VarCHRM::FUNget;
    FP->second.val = 0;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "YEAR";
    FP->second.pget = Fyear;
    FP = vars.find("MONTH");
    if(FP == vars.end())
    {
        vars.insert(make_pair("MONTH", VarCHRM()));
        FP = vars.find("MONTH");
    }
    FP->second.kind = VarCHRM::FUNget;
    FP->second.val = 0;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "MONTH";
    FP->second.pget = Fmonth;
    FP = vars.find("DAY");
    if(FP == vars.end())
    {
        vars.insert(make_pair("DAY", VarCHRM()));
        FP = vars.find("DAY");
    }
    FP->second.kind = VarCHRM::FUNget;
    FP->second.val = 0;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "DAY";
    FP->second.pget = Fday;
    FP = vars.find("ReadAheadObs");
    if(FP == vars.end())
    {
        vars.insert(make_pair("ReadAheadObs", VarCHRM()));
        FP = vars.find("ReadAheadObs");
    }
    FP->second.kind = VarCHRM::FUNobs;
    FP->second.val = 0;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "ReadAheadObs";
    FP->second.Me = this;
    FP = vars.find("WriteAheadObs");
    if(FP == vars.end())
    {
        vars.insert(make_pair("WriteAheadObs", VarCHRM()));
        FP = vars.find("WriteAheadObs");
    }
    FP->second.kind = VarCHRM::FUNobs;
    FP->second.val = 0;
    FP->second.Ihh = 0;
    FP->second.IndexMax = 0;
    FP->second.name = "WriteAheadObs";
    FP->second.Me = this;
    calculator calc(eval, vars, Operations, PCiter, LastVar, LastVas); 
    Operations.clear();
    string str(Global::MacroModulesList->Strings[Begin].c_str());
    for(int jj = Begin+1; jj < End; ++jj)
    {
        int P = Global::MacroModulesList->Strings[jj].Pos("//");
        if(P)
        {
            if(P-1 > 0)
                str +=  " \n" + string(Global::MacroModulesList->Strings[jj].SubString(1, P-1).c_str());
        }
        else
            str += " \n" + string(Global::MacroModulesList->Strings[jj].c_str());
    }
    execbase::Index = 0;
    string::iterator first = str.begin();
    parse_info<string::iterator> info;
    do
    {
        info = parse(first, str.end(), calc, space_p);
        if (!info.hit || info.length == 0)
        {
            string err(first, str.end());
            CRHMException TExcept(string("cannot parse the command string: ") + err.c_str(), TERMINATE);
            LogError(TExcept);
        }
        else if (!info.full)
            first = info.stop;
    }
    while(!(info.full && info.hit));
    PCiter = Operations.begin();
    int n = 1;
    while(PCiter != Operations.end())
    {
        (*PCiter)->OurOrder = n++;
        ++PCiter;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassMacro::init(void) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void ClassMacro::run(void)   
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassMacro::run(void) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    if(isGroup || isStruct)
    {
        list<ModulePtr> ::iterator iter;
        iter = Modules.begin();
        while(iter != Modules.end())
        {
            ModulePtr Op = (*iter);
            (*iter)->run();
            ++iter;
        }
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassMacro::run(void) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return;}
    }
    for (hh = 1; chkStructOff(hh, nhru+1); ++hh)   
    {
        PCiter = Operations.begin();
        while(PCiter != Operations.end())
        {
            execbase Op = (*(*PCiter));
            float X = (*(*PCiter))(); 
            ++PCiter;
            int Cnt = eval.size();
        }
    }
    int Cnt = eval.size();
    assert(eval.empty());
    assert(LastVar.empty());
    assert(LastVas.empty());
freopen("c:\\injection.log", "a", stdout); printf("</voidClassMacro::run(void) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void ClassMacro::finish(bool good)   
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassMacro::finish(boolgood) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    if(isGroup || isStruct)
    {
        list<ModulePtr> ::iterator iter;
        iter = Modules.begin();
        while(iter != Modules.end())
        {
            ModulePtr Op = (*iter);
            Op->finish(true);
            ++iter;
        }
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassMacro::finish(boolgood) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return;}
    }
    Operations.clear();
    symtab_t::iterator pos;
    for(pos = vars.begin(); pos != vars.end();)  
    {
        if(pos->second.kind == VarCHRM::LOCAL)
        {
            vars.erase(pos++);
        }
        else
        {
            ++pos;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassMacro::finish(boolgood) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
ClassMacro::ClassMacro(string Name, int ThisBegin, String Version, string Desc): ClassModule(Name, Version, CRHM::MACRO)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassMacro::ClassMacro(stringName,intThisBegin,StringVersion,stringDesc):ClassModule(Name,Version,CRHM::MACRO) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    GrpStringList = NULL;
    int ThisEnd = ThisBegin;
    MacroBegin = ThisBegin;
    Description = Desc.c_str();
    String S;
    ID = Name;
    Grpnhru = 0;
    while(ThisEnd < Global::MacroModulesList->Count &&
            (S = Global::MacroModulesList->Strings[ThisEnd].TrimLeft(),
             !(S.SubString(1,3) == "end" &&
               (S.Length() == 3 || S.IsDelimiter(" /", 4)))))
        ++ThisEnd;
    if(!DefCRHM::DefStringList)
    {
        DefCRHM::DefStringList = new TStringList;
    }
    isGroup = false;
    isStruct = false;
    for(int ii = ThisBegin + 1; ii < ThisEnd; ++ii)
    {
        int Indx;
        if(Indx = Global::MacroModulesList->Strings[ii].Pos("//"))
        {
            String temp = Global::MacroModulesList->Strings[ii].SubString(1, Indx-1);
            temp = temp.TrimRight();
            DefCRHM::DefStringList->DelimitedText = temp;
        }
        else
            DefCRHM::DefStringList->DelimitedText = Global::MacroModulesList->Strings[ii];
        long Pcnt = DefCRHM::DefStringList->Count;
        if(Pcnt < 1)
            continue;
        DefCRHM::DefStringList->Strings[0].TrimLeft();
        if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("//") || DefCRHM::DefStringList->Strings[0].IsEmpty())
            continue;
        if(DefCRHM::DefStringList->Strings[0].Pos("command") == 1)
        {
            Begin = ii+1;
            End = ThisEnd;
            DefCRHMPtr Call(new Defcommand(this));
            break;
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("declgroup"))
        {
            if(!isGroup)
            {
                isGroup = true;
                GroupCnt = ++Global::GroupCntTrk;
                GrpStringList = new TStringList;
                if(DefCRHM::DefStringList->Count > 1 && !DefCRHM::DefStringList->Strings[1].Pos("//"))
                    Grpnhru = DefCRHM::DefStringList->Strings[1].ToInt();
                else
                    Grpnhru = nhru;
            }
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("declstruct"))
        {
            if(!isStruct)
            {
                isStruct = true;
                StructCnt = ++Global::StructCntTrk;
                GrpStringList = new TStringList;
                if(DefCRHM::DefStringList->Count > 1   && !DefCRHM::DefStringList->Strings[1].Pos("//"))
                    Grpnhru = DefCRHM::DefStringList->Strings[1].ToInt();
                else
                    Grpnhru = nhru;
            }
        }
        else if(isGroup || isStruct)
        {
            String S = DefCRHM::DefStringList->Strings[0];
            String V;
            long N = S.Pos("#"); 
            if(N)
            {
                V = S.SubString(N, 2);
                S = S.SubString(1, N-1);
            }
            long jj = Global::OldModuleName->IndexOf(S); 
            if(jj == -1) 
                GrpStringList->Add(DefCRHM::DefStringList->Strings[0]); 
            else
            {
                GrpStringList->Add(Global::NewModuleName->Strings[jj] + V); 
                String Message = "Converting module " + Global::OldModuleName->Strings[jj] + V + " to " + Global::NewModuleName->Strings[jj] + V + " in macro " + Name.c_str();
                LogMessage(Message.c_str());
            }
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("declparam") && Pcnt >= 8)
        {
            DefCRHMPtr Call(new Defdeclparam(this));
            Calls.push_back(Call);
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("decldiagparam") && Pcnt >= 8)
        {
            DefCRHMPtr Call(new Defdeclparam(this));
            Calls.push_back(Call);
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("declreadobs") && Pcnt >= 5)
        {
            DefCRHMPtr Call(new Defdeclreadobs(this));
            Calls.push_back(Call);
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("declobsfunc") && Pcnt >= 4)
        {
            DefCRHMPtr Call(new Defdeclobsfunc(this));
            Calls.push_back(Call);
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("declvar") && Pcnt >= 5)
        {
            DefCRHMPtr Call(new Defdeclvar(this));
            Calls.push_back(Call);
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("decldiag") && Pcnt >= 5)
        {
            DefCRHMPtr Call(new Defdecldiag(this));
            Calls.push_back(Call);
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("declstatvar") && Pcnt >= 5)
        {
            DefCRHMPtr Call(new Defdeclstatvar(this));
            Calls.push_back(Call);
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("decllocal") && Pcnt >= 5)
        {
            DefCRHMPtr Call(new Defdecllocal(this));
            Calls.push_back(Call);
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("declgetvar") && Pcnt >= 4)
        {
            DefCRHMPtr Call(new Defdeclgetvar(this));
            Calls.push_back(Call);
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("declputvar") && Pcnt >= 4)
        {
            DefCRHMPtr Call(new Defdeclputvar(this));
            Calls.push_back(Call);
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("declputparam") && Pcnt >= 4)
        {
            DefCRHMPtr Call(new Defdeclputparam(this));
            Calls.push_back(Call);
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("declgetparam") && Pcnt >= 4)
        {
            DefCRHMPtr Call(new Defdeclgetparam(this));
            Calls.push_back(Call);
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("declobs") && Pcnt >= 5)
        {
            DefCRHMPtr Call(new Defdeclobs(this));
            Calls.push_back(Call);
        }
        else if(!DefCRHM::DefStringList->Strings[0].AnsiCompareIC("setpeer"))
        {
            PeerVar = DefCRHM::DefStringList->Strings[1];
            if(DefCRHM::DefStringList->Count > 2)
                PeerRank = DefCRHM::DefStringList->Strings[2].ToIntDef(0);
        }
        else
        {
            Application->MessageBox(String(String("function not recognised or too few parameters: ")
                                           + "\"" + Global::MacroModulesList->Strings[ii] + "\"").c_str(), "Macro Error", MB_OK);
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</ClassMacro::ClassMacro(stringName,intThisBegin,StringVersion,stringDesc):ClassModule(Name,Version,CRHM::MACRO) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
ClassMacro::~ClassMacro()   
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassMacro::~ClassMacro() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    Calls.clear(); 
};
TStringList *DefCRHM::DefStringList = NULL;
CRHM::TDim DefCRHM::getTDim(String D)
{
freopen("c:\\injection.log", "a", stdout); printf("<CRHM::TDimDefCRHM::getTDim(StringD) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    char table[][6] =
    {
        "BASIN",
        "ONE",
        "TWO",
        "THREE",
        "FOUR",
        "FIVE",
        "SIX",
        "SEVEN",
        "EIGHT",
        "NINE",
        "TEN",
        "ELEVEN",
        "TWELVE",
        "NHRU",
        "NOBS",
        "NLAY",
        "NDEF",
        "NFREQ",
        "NREB",
        "NDEFN",
        "NDEFNZ"
    };
    for(long ii = 0; ii < 21; ++ii)
        if(D == table[ii])
{freopen("c:\\injection.log", "a", stdout); printf("</CRHM::TDimDefCRHM::getTDim(StringD) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return (CRHM::TDim) ii;}
{freopen("c:\\injection.log", "a", stdout); printf("</CRHM::TDimDefCRHM::getTDim(StringD) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return (CRHM::TDim) -1;}
freopen("c:\\injection.log", "a", stdout); printf("</CRHM::TDimDefCRHM::getTDim(StringD) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
CRHM::TFun DefCRHM::getTFunc(String D)
{
freopen("c:\\injection.log", "a", stdout); printf("<CRHM::TFunDefCRHM::getTFunc(StringD) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    char table[][8] =
    {
        "FOBS",
        "W_MJ",
        "MJ_W",
        "AVG",
        "MIN",
        "MAX",
        "DTOT",
        "POS",
        "TOT",
        "FIRST",
        "LAST",
        "CNT",
        "CNT0",
        "INTVL"
    };
    for(long ii = 1; ii < 11; ++ii)
        if(D == table[ii])
{freopen("c:\\injection.log", "a", stdout); printf("</CRHM::TFunDefCRHM::getTFunc(StringD) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return (CRHM::TFun) ii;}
{freopen("c:\\injection.log", "a", stdout); printf("</CRHM::TFunDefCRHM::getTFunc(StringD) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return (CRHM::TFun) -1;}
freopen("c:\\injection.log", "a", stdout); printf("</CRHM::TFunDefCRHM::getTFunc(StringD) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
Defdeclparam::Defdeclparam(ClassMacro *Macro_) : DefCRHM(Macro_)
{
freopen("c:\\injection.log", "a", stdout); printf("<Defdeclparam::Defdeclparam(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    if(DefStringList->Strings[0] == "decldiagparam")
        visibility = CRHM::DIAGNOSTIC;
    else
        visibility = CRHM::USUAL;
    name = DefStringList->Strings[1].c_str();
    Dim = getTDim(DefStringList->Strings[2].c_str());
    Default = DefStringList->Strings[3].c_str();
    Min = DefStringList->Strings[4].c_str();
    Max = DefStringList->Strings[5].c_str();
    Description = DefStringList->Strings[6].c_str();
    Units = DefStringList->Strings[7].c_str();
    if(DefCRHM::DefStringList->Count > 8 && DefStringList->Strings[8] == "Int")
        Int = true;
    else
        Int = false;
    if(DefCRHM::DefStringList->Count > 9)
        nlay = DefStringList->Strings[9].ToIntDef(Macro->nhru);
freopen("c:\\injection.log", "a", stdout); printf("</Defdeclparam::Defdeclparam(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
Defdeclvar::Defdeclvar(ClassMacro *Macro_) : DefCRHM(Macro_)
{
freopen("c:\\injection.log", "a", stdout); printf("<Defdeclvar::Defdeclvar(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    name = DefStringList->Strings[1].c_str();
    Dim = getTDim(DefStringList->Strings[2].c_str());
    Description = DefStringList->Strings[3].c_str();
    Units = DefStringList->Strings[4].c_str();
    if(DefCRHM::DefStringList->Count > 5 && DefStringList->Strings[5] == "Int")
        Int = true;
    else
        Int = false;
freopen("c:\\injection.log", "a", stdout); printf("</Defdeclvar::Defdeclvar(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
Defdecldiag::Defdecldiag(ClassMacro *Macro_) : DefCRHM(Macro_)
{
freopen("c:\\injection.log", "a", stdout); printf("<Defdecldiag::Defdecldiag(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    name = DefStringList->Strings[1].c_str();
    Dim = getTDim(DefStringList->Strings[2].c_str());
    Description = DefStringList->Strings[3].c_str();
    Units = DefStringList->Strings[4].c_str();
    if(DefCRHM::DefStringList->Count > 5 && DefStringList->Strings[5] == "Int")
        Int = true;
    else
        Int = false;
freopen("c:\\injection.log", "a", stdout); printf("</Defdecldiag::Defdecldiag(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
Defdeclstatvar::Defdeclstatvar(ClassMacro *Macro_) : DefCRHM(Macro_)
{
freopen("c:\\injection.log", "a", stdout); printf("<Defdeclstatvar::Defdeclstatvar(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    name = DefStringList->Strings[1].c_str();
    Dim = getTDim(DefStringList->Strings[2].c_str());
    Description = DefStringList->Strings[3].c_str();
    Units = DefStringList->Strings[4].c_str();
    if(DefCRHM::DefStringList->Count > 5 && DefStringList->Strings[5] == "Int")
        Int = true;
    else
        Int = false;
freopen("c:\\injection.log", "a", stdout); printf("</Defdeclstatvar::Defdeclstatvar(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
Defdecllocal::Defdecllocal(ClassMacro *Macro_) : DefCRHM(Macro_)
{
freopen("c:\\injection.log", "a", stdout); printf("<Defdecllocal::Defdecllocal(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    name = DefStringList->Strings[1].c_str();
    Dim = getTDim(DefStringList->Strings[2].c_str());
    Description = DefStringList->Strings[3].c_str();
    Units = DefStringList->Strings[4].c_str();
    if(DefCRHM::DefStringList->Count > 5 && DefStringList->Strings[5] == "Int")
        Int = true;
    else
        Int = false;
freopen("c:\\injection.log", "a", stdout); printf("</Defdecllocal::Defdecllocal(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
Defdeclobs::Defdeclobs(ClassMacro *Macro_) : DefCRHM(Macro_)
{
freopen("c:\\injection.log", "a", stdout); printf("<Defdeclobs::Defdeclobs(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    String S = DefStringList->Strings[1];
    int Pos = S.Pos("#");
    if(!Pos)
        S += "#"; 
    else
        S = S.SubString(1, Pos); 
    name = S.c_str();
    Dim = getTDim(DefStringList->Strings[2].c_str());
    Description = DefStringList->Strings[3].c_str();
    Units = DefStringList->Strings[4].c_str();
freopen("c:\\injection.log", "a", stdout); printf("</Defdeclobs::Defdeclobs(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
Defdeclgetvar::Defdeclgetvar(ClassMacro *Macro_) : DefCRHM(Macro_)
{
freopen("c:\\injection.log", "a", stdout); printf("<Defdeclgetvar::Defdeclgetvar(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    module = DefStringList->Strings[1].c_str();
    name = DefStringList->Strings[2].c_str();
    Units = DefStringList->Strings[3].c_str();
freopen("c:\\injection.log", "a", stdout); printf("</Defdeclgetvar::Defdeclgetvar(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
Defdeclputvar::Defdeclputvar(ClassMacro *Macro_) : DefCRHM(Macro_)
{
freopen("c:\\injection.log", "a", stdout); printf("<Defdeclputvar::Defdeclputvar(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    module = DefStringList->Strings[1].c_str();
    name = DefStringList->Strings[2].c_str();
    Units = DefStringList->Strings[3].c_str();
freopen("c:\\injection.log", "a", stdout); printf("</Defdeclputvar::Defdeclputvar(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
Defdeclputparam::Defdeclputparam(ClassMacro *Macro_) : DefCRHM(Macro_)
{
freopen("c:\\injection.log", "a", stdout); printf("<Defdeclputparam::Defdeclputparam(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    module = DefStringList->Strings[1].c_str();
    name = DefStringList->Strings[2].c_str();
    Units = DefStringList->Strings[3].c_str();
freopen("c:\\injection.log", "a", stdout); printf("</Defdeclputparam::Defdeclputparam(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
Defdeclgetparam::Defdeclgetparam(ClassMacro *Macro_) : DefCRHM(Macro_)
{
freopen("c:\\injection.log", "a", stdout); printf("<Defdeclgetparam::Defdeclgetparam(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    module = DefStringList->Strings[1].c_str();
    name = DefStringList->Strings[2].c_str();
    Units = DefStringList->Strings[3].c_str();
freopen("c:\\injection.log", "a", stdout); printf("</Defdeclgetparam::Defdeclgetparam(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
Defdeclreadobs::Defdeclreadobs(ClassMacro *Macro_) : DefCRHM(Macro_)
{
freopen("c:\\injection.log", "a", stdout); printf("<Defdeclreadobs::Defdeclreadobs(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    name = DefStringList->Strings[1].c_str();
    Dim = getTDim(DefStringList->Strings[2].c_str());
    Description = DefStringList->Strings[3].c_str();
    Units = DefStringList->Strings[4].c_str();
    if(DefCRHM::DefStringList->Count > 5)
        HRU_OBS_indexed = DefStringList->Strings[5].ToInt();
    else
        HRU_OBS_indexed = 0;
freopen("c:\\injection.log", "a", stdout); printf("</Defdeclreadobs::Defdeclreadobs(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
Defdeclobsfunc::Defdeclobsfunc(ClassMacro *Macro_) : DefCRHM(Macro_)
{
freopen("c:\\injection.log", "a", stdout); printf("<Defdeclobsfunc::Defdeclobsfunc(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    obs = DefStringList->Strings[1].c_str();
    name = DefStringList->Strings[2].c_str();
    typeFun = getTFunc(DefStringList->Strings[3].c_str());
freopen("c:\\injection.log", "a", stdout); printf("</Defdeclobsfunc::Defdeclobsfunc(ClassMacro*Macro_):DefCRHM(Macro_) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclparam::CallDecl()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclparam::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    if(Int)
        Macro->declparam(name, Dim, Default, Min, Max, Description, Units, &fix_long_const, &fix2_long_const, nlay, visibility);
    else
        Macro->declparam(name, Dim, Default, Min, Max, Description, Units, &fix_const, &fix2_const, Macro->nhru, visibility);
    if(Global::BuildFlag == CRHM::INIT)
    {
        FP = Macro->vars.find(name);
        if(FP == Macro->vars.end())
        {
            Macro->vars.insert(make_pair(name, VarCHRM()));
            FP = Macro->vars.find(name);
        }
        FP->second.name = name.c_str();
        FP->second.Ihh = 0;
        FP->second.IndexMax = Macro->nhru-1;
        FP->second.IndexMaxLay = Macro->nhru-1; 
        FP->second.Me = Macro;
        if(Int)
        {
            if(Dim == CRHM::NDEF || Dim == CRHM::NDEFN)
            {
                FP->second.kind = VarCHRM::CRHMint2;
                FP->second.ivalue2 = const_cast<long **> (fix2_long_const);
            }
            else
            {
                FP->second.kind = VarCHRM::CRHMint;
                FP->second.ivalue = const_cast<long *> (fix_long_const);
            }
        }
        else
        {
            if(Dim == CRHM::NDEF || Dim == CRHM::NDEFN)
            {
                FP->second.kind = VarCHRM::CRHM2;
                FP->second.value2 = const_cast<float **> (fix2_const);
            }
            else
            {
                FP->second.kind = VarCHRM::CRHM;
                FP->second.value = const_cast<float *> (fix_const);
            }
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclparam::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclparam::CallInit(long nhru, long nlay)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclparam::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclparam::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclvar::CallDecl()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclvar::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    if(Int)
        Macro->declvar(name, Dim, Description, Units, &fix_long);
    else
        Macro->declvar(name, Dim, Description, Units, &fix, &fix2);
    FP = Macro->vars.find(name);
    if(FP == Macro->vars.end())
    {
        Macro->vars.insert(make_pair(name, VarCHRM()));
        FP = Macro->vars.find(name);
    }
    FP->second.name = name;
    FP->second.Ihh = 0;
    FP->second.Ill = 0;
    FP->second.IndexMax = Global::nhru-1;
    FP->second.IndexMaxLay = Macro->nhru-1; 
    FP->second.Me = Macro;
    if(Int)
    {
        FP->second.kind = VarCHRM::CRHMint;
        FP->second.ivalue = const_cast<long *> (fix_long);
    }
    else if(Dim == CRHM::NDEF || Dim == CRHM::NDEFN)
    {
        FP->second.value2 = fix2;
        FP->second.kind = VarCHRM::CRHM2;
    }
    else
    {
        FP->second.kind = VarCHRM::CRHM;
        FP->second.value = fix;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclvar::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdecldiag::CallDecl()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdecldiag::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    if(Int)
        Macro->decldiag(name, Dim, Description, Units, &fix_long);
    else
        Macro->decldiag(name, Dim, Description, Units, &fix, &fix2);
    FP = Macro->vars.find(name);
    if(FP == Macro->vars.end())
    {
        Macro->vars.insert(make_pair(name, VarCHRM()));
        FP = Macro->vars.find(name);
    }
    FP->second.name = name;
    FP->second.Ihh = 0;
    FP->second.Ill = 0;
    FP->second.IndexMax = Global::nhru-1;
    FP->second.IndexMaxLay = Macro->nhru-1; 
    FP->second.Me = Macro;
    if(Int)
    {
        FP->second.kind = VarCHRM::CRHMint;
        FP->second.ivalue = const_cast<long *> (fix_long);
    }
    else if(Dim == CRHM::NDEF || Dim == CRHM::NDEFN)
    {
        FP->second.value2 = fix2;
        FP->second.kind = VarCHRM::CRHM2;
    }
    else
    {
        FP->second.kind = VarCHRM::CRHM;
        FP->second.value = fix;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdecldiag::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclstatvar::CallDecl()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclstatvar::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    if(Int)
        Macro->declstatvar(name, Dim, Description, Units, &fix_long);
    else
        Macro->declstatvar(name, Dim, Description, Units, &fix);
    FP = Macro->vars.find(name);
    if(FP == Macro->vars.end())
    {
        Macro->vars.insert(make_pair(name, VarCHRM()));
        FP = Macro->vars.find(name);
    }
    FP->second.name = name;
    FP->second.Ihh = 0;
    FP->second.Ill = 0;
    FP->second.IndexMax = Global::nhru-1;
    FP->second.IndexMaxLay = Macro->nhru-1; 
    FP->second.Me = Macro;
    if(Int)
    {
        FP->second.kind = VarCHRM::CRHMint;
        FP->second.ivalue = const_cast<long *> (fix_long);
    }
    else if(Dim == CRHM::NDEF || Dim == CRHM::NDEFN)
    {
        FP->second.value2 = fix2;
        FP->second.kind = VarCHRM::CRHM2;
    }
    else
    {
        FP->second.kind = VarCHRM::CRHM;
        FP->second.value = fix;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclstatvar::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdecllocal::CallDecl()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdecllocal::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    if(Int)
        Macro->decllocal(name, Dim, Description, Units, &fix_long);
    else
        Macro->decllocal(name, Dim, Description, Units, &fix);
    FP = Macro->vars.find(name);
    if(FP == Macro->vars.end())
    {
        Macro->vars.insert(make_pair(name, VarCHRM()));
        FP = Macro->vars.find(name);
    }
    FP->second.name = name;
    FP->second.Ihh = 0;
    FP->second.Ill = 0;
    FP->second.IndexMax = Global::nhru-1;
    FP->second.IndexMaxLay = Macro->nhru-1; 
    FP->second.Me = Macro;
    if(Int)
    {
        FP->second.kind = VarCHRM::CRHMint;
        FP->second.ivalue = const_cast<long *> (fix_long);
    }
    else if(Dim == CRHM::NDEF || Dim == CRHM::NDEFN)
    {
        FP->second.value2 = fix2;
        FP->second.kind = VarCHRM::CRHM2;
    }
    else
    {
        FP->second.kind = VarCHRM::CRHM;
        FP->second.value = fix;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdecllocal::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclgetvar::CallDecl()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclgetvar::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *thisVar;
    Macro->FindWildVarFloat(name, thisVar); 
    if(Global::thisVar != NULL && ((ClassVar*) Global::thisVar)->varType == CRHM::Int)
        Int = true;
    else
        Int = false;
    if(Int)
        Macro->declgetvar(module, name, Units, &fix_long_const, &fix2_long_const);
    else
        Macro->declgetvar(module, name, Units, &fix_const, &fix2_const);
    if(Global::BuildFlag == CRHM::INIT)  
    {
        FP = Macro->vars.find(name);
        if(FP == Macro->vars.end())
        {
            Macro->vars.insert(make_pair(name, VarCHRM()));
            FP = Macro->vars.find(name);
        }
        FP->second.name = name.c_str();
        FP->second.Ihh = 0;
        FP->second.Ill = 0;
        FP->second.IndexMax = Macro->nhru-1;
        FP->second.IndexMaxLay = Macro->nhru-1; 
        FP->second.Me = Macro;
        if(Int)
        {
            if(((ClassVar*) Global::thisVar)->varType == CRHM::NDEF || ((ClassVar*) Global::thisVar)->varType == CRHM::NDEFN)
            {
                FP->second.kind = VarCHRM::CRHMint2;
                FP->second.ivalue2 = const_cast<long **> (fix2_long_const);
            }
            else
            {
                FP->second.kind = VarCHRM::CRHMint;
                FP->second.ivalue = const_cast<long *> (fix_long_const);
            }
        }
        else
        {
            if(((ClassVar*) Global::thisVar)->varType == CRHM::NDEF || ((ClassVar*) Global::thisVar)->varType == CRHM::NDEFN)
            {
                FP->second.kind = VarCHRM::CRHM2;
                FP->second.value2 = const_cast<float **> (fix2_const);
            }
            else
            {
                FP->second.kind = VarCHRM::CRHM;
                FP->second.value = const_cast<float *> (fix_const);
            }
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclgetvar::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclputvar::CallDecl()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclputvar::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *thisVar;
    Macro->FindWildVarFloat(name, thisVar); 
    if(Global::thisVar != NULL && ((ClassVar*) Global::thisVar)->varType == CRHM::Int)
        Int = true;
    else
        Int = false;
    if(Int)
        Macro->declputvar(module, name, Units, &fix_long);
    else
        Macro->declputvar(module, name, Units, &fix, &fix2);
    if(Global::BuildFlag == CRHM::INIT)  
    {
        FP = Macro->vars.find(name);
        if(FP == Macro->vars.end())
        {
            Macro->vars.insert(make_pair(name, VarCHRM()));
            FP = Macro->vars.find(name);
        }
        FP->second.name = name.c_str();
        FP->second.Ihh = 0;
        FP->second.Ill = 0;
        FP->second.IndexMax = Macro->nhru-1;
        FP->second.IndexMaxLay = Macro->nhru-1; 
        FP->second.Me = Macro;
        if(Int)
        {
            FP->second.kind = VarCHRM::CRHMint;
            FP->second.ivalue = const_cast<long *> (fix_long);
        }
        else if(((ClassVar*) Global::thisVar)->varType == CRHM::NDEF || ((ClassVar*) Global::thisVar)->varType == CRHM::NDEFN)
        {
            FP->second.kind = VarCHRM::CRHM2;
            FP->second.value2 = const_cast<float **> (fix2);
        }
        else
        {
            FP->second.kind = VarCHRM::CRHM;
            FP->second.value = const_cast<float *> (fix);
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclputvar::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclputparam::CallDecl()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclputparam::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *thisPar = NULL;
    int GetUnit;
    GetUnit = Macro->FindWildParFloat(name, thisPar, false, false); 
    if(thisPar != NULL && thisPar->varType == CRHM::Int)
        Int = true;
    else
        Int = false;
    if(Int)
        Macro->declputparam(module, name, Units, &fix_long);
    else
        Macro->declputparam(module, name, Units, &fix, &fix2);
    if(Global::BuildFlag == CRHM::INIT)  
    {
        FP = Macro->vars.find(name);
        if(FP == Macro->vars.end())
        {
            Macro->vars.insert(make_pair(name, VarCHRM()));
            FP = Macro->vars.find(name);
        }
        FP->second.name = name.c_str();
        FP->second.Ihh = 0;
        FP->second.Ill = 0;
        FP->second.IndexMax = Macro->nhru-1;
        FP->second.IndexMaxLay = Macro->nhru-1; 
        FP->second.Me = Macro;
        if(Int)
        {
            FP->second.kind = VarCHRM::CRHMint;
            FP->second.ivalue = const_cast<long *> (fix_long);
        }
        else if(thisPar->varType == CRHM::NDEF || thisPar->varType == CRHM::NDEFN)
        {
            FP->second.kind = VarCHRM::CRHM2;
            FP->second.value2 = const_cast<float **> (fix2);
        }
        else
        {
            FP->second.kind = VarCHRM::CRHM;
            FP->second.value = const_cast<float *> (fix);
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclputparam::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclgetparam::CallDecl()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclgetparam::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *thisPar = NULL;
    int GetUnit;
    GetUnit = Macro->FindWildParFloat(name, thisPar, false, false); 
    if(thisPar != NULL && thisPar->varType == CRHM::Int)
        Int = true;
    else
        Int = false;
    if(Int)
        Macro->declgetparam(module, name, Units, &fix_long_const, &fix2_long_const);
    else
        Macro->declgetparam(module, name, Units, &fix_const, &fix2_const);
    if(Global::BuildFlag == CRHM::INIT)  
    {
        FP = Macro->vars.find(name);
        if(FP == Macro->vars.end())
        {
            Macro->vars.insert(make_pair(name, VarCHRM()));
            FP = Macro->vars.find(name);
        }
        FP->second.name = name.c_str();
        FP->second.Ihh = 0;
        FP->second.Ill = 0;
        FP->second.IndexMax = Macro->nhru-1;
        FP->second.IndexMaxLay = Macro->nhru-1; 
        FP->second.Me = Macro;
        if(Int)
        {
            if(thisPar->varType == CRHM::NDEF || thisPar->varType == CRHM::NDEFN)
            {
                FP->second.kind = VarCHRM::CRHMint2;
                FP->second.ivalue2 = const_cast<long **> (fix2_long_const);
            }
            else
            {
                FP->second.kind = VarCHRM::CRHMint;
                FP->second.ivalue = const_cast<long *> (fix_long_const);
            }
        }
        else
        {
            if(thisPar->varType == CRHM::NDEF || thisPar->varType == CRHM::NDEFN)
            {
                FP->second.kind = VarCHRM::CRHM2;
                FP->second.value2 = const_cast<float **> (fix2_const);
            }
            else
            {
                FP->second.kind = VarCHRM::CRHM;
                FP->second.value = const_cast<float *> (fix_const);
            }
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclgetparam::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclobs::CallDecl()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclobs::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    long cnt = Macro->declobs(Macro->Name, name, Dim, Description.c_str(), Units.c_str(), &fix);
    FP = Macro->vars.find(name);
    if(FP == Macro->vars.end())
    {
        Macro->vars.insert(make_pair(name, VarCHRM()));
        FP = Macro->vars.find(name);
    }
    if(fix)
        FP->second.kind = VarCHRM::CRHM;
    else
        FP->second.kind = VarCHRM::NOP;
    FP->second.name = name;
    FP->second.Ihh = 0;
    FP->second.IndexMax = cnt;
    FP->second.value = fix;
    FP->second.Me = Macro;
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclobs::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclobs::CallInit(long nhru, long nlay)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclobs::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    for(int hh = 0; hh <= FP->second.IndexMax; ++hh)
    {
        FP->second.Ihh = hh;
        FP->second.put(0.0);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclobs::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclvar::CallInit(long nhru, long nlay)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclvar::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    FP->second.IndexMax = nhru-1;
    for(int hh = 0; hh <= FP->second.IndexMax; ++hh)
    {
        FP->second.Ihh = hh;
        FP->second.put(0.0);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclvar::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdecldiag::CallInit(long nhru, long nlay)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdecldiag::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    FP->second.IndexMax = nhru-1;
    for(int hh = 0; hh <= FP->second.IndexMax; ++hh)
    {
        FP->second.Ihh = hh;
        FP->second.put(0.0);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdecldiag::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclstatvar::CallInit(long nhru, long nlay)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclstatvar::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    FP->second.IndexMax = nhru-1;
    for(int hh = 0; hh <= FP->second.IndexMax; ++hh)
    {
        FP->second.Ihh = hh;
        FP->second.put(0.0);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclstatvar::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdecllocal::CallInit(long nhru, long nlay)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdecllocal::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    FP->second.IndexMax = nhru-1;
    for(int hh = 0; hh <= FP->second.IndexMax; ++hh)
    {
        FP->second.Ihh = hh;
        FP->second.put(0.0);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdecllocal::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclgetvar::CallInit(long nhru, long nlay)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclgetvar::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    FP->second.IndexMax = nhru-1;
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclgetvar::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclputvar::CallInit(long nhru, long nlay)   
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclputvar::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    FP->second.IndexMax = nhru-1;
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclputvar::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclputparam::CallInit(long nhru, long nlay)   
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclputparam::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    FP->second.IndexMax = nhru-1;
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclputparam::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclgetparam::CallInit(long nhru, long nlay)   
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclgetparam::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    FP->second.IndexMax = nhru-1;
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclgetparam::CallInit(longnhru,longnlay) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclreadobs::CallDecl()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclreadobs::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    long cnt = Macro->declreadobs(name, Dim, Description, Units, &fix_const, HRU_OBS_indexed);
    FP = Macro->vars.find(name);
    if(FP == Macro->vars.end())
    {
        Macro->vars.insert(make_pair(name, VarCHRM()));
        FP = Macro->vars.find(name);
    }
    FP->second.kind = VarCHRM::CRHM;
    FP->second.name = name.c_str();
    FP->second.Ihh = 0;
    FP->second.IndexMax = cnt;
    FP->second.value = const_cast<float *> (fix_const);
    FP->second.Me = Macro;
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclreadobs::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
void Defdeclobsfunc::CallDecl()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDefdeclobsfunc::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    long cnt = Macro->declobsfunc(obs, name, &fix, typeFun);
    FP = Macro->vars.find(name);
    if(FP == Macro->vars.end())
    {
        Macro->vars.insert(make_pair(name, VarCHRM()));
        FP = Macro->vars.find(name);
    }
    FP->second.kind = VarCHRM::CRHM;
    FP->second.name = name.c_str();
    FP->second.Ihh = 0;
    FP->second.IndexMax = cnt;
    FP->second.value = fix;
    FP->second.Me = Macro;
freopen("c:\\injection.log", "a", stdout); printf("</voidDefdeclobsfunc::CallDecl() @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
long ClassMacro::declobs(string module, string name, CRHM::TDim dimen, string help, string units, float **value)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassMacro::declobs(stringmodule,stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *newVar;
    ClassVar *thisVar;
    int cnt = getdim(dimen);
    Convert convert;
    convert.CheckUnitsString(Name, name, units);
    switch(Global::BuildFlag)
    {
    case CRHM::BUILD:
    {
        PairstrV Item2 = PairstrV(name.c_str(), variation_set);
        PairstrI Item = PairstrI(module.c_str(), Item2);
        Global::Mapdeclvar.insert(Item);
        Global::Mapdeclobs.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassMacro::declobs(stringmodule,stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    case CRHM::DECL:
    {
        if((itVar = Global::MapVars.find(Name + " " + name)) != Global::MapVars.end())
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
            thisVar->dimen = dimen;
            thisVar->module = module;
            thisVar->DLLName = DLLName.c_str();
            thisVar->root = ID.c_str();
{freopen("c:\\injection.log", "a", stdout); printf("</longClassMacro::declobs(stringmodule,stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return(-1);}
        }
        newVar = new ClassVar("obs", name, cnt, 0, NULL);
        newVar->varType = CRHM::Float;
        newVar->help = help;
        newVar->units = units;
        newVar->module = module;
        newVar->DLLName = DLLName.c_str();
        newVar->root = ID.c_str();
        newVar->values = new float[cnt];
        PairVar Item = PairVar("obs " + name, newVar);
        Global::MapVars.insert(Item);
        Item = PairVar(Name + " " + name, newVar);
        Global::MapVars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassMacro::declobs(stringmodule,stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
    case CRHM::INIT:
    {
        if((itVar = Global::MapVars.find(Name + " " + name)) != Global::MapVars.end())
        {
            newVar = (*itVar).second;
            if(newVar->FileData)
            {
                *value = NULL;
{freopen("c:\\injection.log", "a", stdout); printf("</longClassMacro::declobs(stringmodule,stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return(-(newVar->cnt-1));}
            }
            else
            {
                *value = newVar->values;
                newVar->cnt = cnt; 
                LogError(CRHMException(" macro module '" + module + "' creating declared observation: '" + name + "'", WARNING));
{freopen("c:\\injection.log", "a", stdout); printf("</longClassMacro::declobs(stringmodule,stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return(newVar->cnt-1);}
            }
        }
        else
        {
            CRHMException Except("observation not found: " + module + " " + name, TERMINATE);
            LogError(Except);
            throw Except;
        }
    }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassMacro::declobs(stringmodule,stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);return 0;}
freopen("c:\\injection.log", "a", stdout); printf("</longClassMacro::declobs(stringmodule,stringname,CRHM::TDimdimen,stringhelp,stringunits,float**value) @@@ MacroUnit.cpp_nocom>\n"); fclose(stdout);
}
