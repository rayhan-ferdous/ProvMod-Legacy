#include <vcl.h>
#pragma hdrstop
#include "Bld.h"
#include "CRHMmain.h"
#include "DefCRHMGlobal.h"
#include "ClassModule.h"
#include "MacroUnit.h"
#include "Para.h"
#include <vector>
#include <algorithm>
#include <sstream>
#pragma package(smart_init)
#pragma resource "*.dfm"
TBldForm *BldForm;
extern string AKAstrings[];
String LVLStrings[] = {"BASIC", "MACRO", "ADVANCED", "SUPPORT", "CUSTOM", "PROTOTYPE", "OBSOLETE"};
using namespace std;
bool ModifyBuild = false;
class ClassEntry
{

public:
    unsigned long OrigPos; 
    long rank;             
    bool used;
    String Name;           
    ClassModule *module;   
    ClassEntry() : Name(""), OrigPos(0), rank(0), module(NULL) {};
    ClassEntry(String Name, ClassModule *module, int OrigPos_) : Name(Name), module(module), OrigPos(OrigPos_), rank(0) {};
    ClassEntry(const ClassEntry & Cl);
    ClassEntry & operator=(const ClassEntry & Cl);
    friend bool operator<(const ClassEntry &x, const ClassEntry &y);
};
bool operator<(const ClassEntry &x, const ClassEntry &y)
{
freopen("c:\\injection.log", "a", stdout); printf("<booloperator<(constClassEntry&x,constClassEntry&y) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</booloperator<(constClassEntry&x,constClassEntry&y) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return x.rank < y.rank;}
freopen("c:\\injection.log", "a", stdout); printf("</booloperator<(constClassEntry&x,constClassEntry&y) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
ClassEntry::ClassEntry(const ClassEntry & Cl)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassEntry::ClassEntry(constClassEntry&Cl) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    OrigPos = Cl.OrigPos;
    rank = Cl.rank;
    used = Cl.used;
    Name = Cl.Name;
    module = Cl.module;
freopen("c:\\injection.log", "a", stdout); printf("</ClassEntry::ClassEntry(constClassEntry&Cl) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
ClassEntry & ClassEntry::operator=(const ClassEntry & Cl)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassEntry&ClassEntry::operator=(constClassEntry&Cl) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    if (this == &Cl)
{freopen("c:\\injection.log", "a", stdout); printf("</ClassEntry&ClassEntry::operator=(constClassEntry&Cl) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return *this;}
    OrigPos = Cl.OrigPos;
    rank = Cl.rank;
    used = Cl.used;
    Name = Cl.Name;
    module = Cl.module;
{freopen("c:\\injection.log", "a", stdout); printf("</ClassEntry&ClassEntry::operator=(constClassEntry&Cl) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return *this;}
freopen("c:\\injection.log", "a", stdout); printf("</ClassEntry&ClassEntry::operator=(constClassEntry&Cl) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void  MoveDown(vector<ClassEntry> &Entries, long to, long from)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidMoveDown(vector<ClassEntry>&Entries,longto,longfrom) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    ClassEntry Temp = Entries[from]; 
    for(int jj = from; jj > to; --jj)
        Entries[jj] = Entries[jj-1]; 
    Entries[to] = Temp; 
freopen("c:\\injection.log", "a", stdout); printf("</voidMoveDown(vector<ClassEntry>&Entries,longto,longfrom) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
vector<ClassEntry> Entries;
__fastcall TBldForm::TBldForm(TComponent* Owner) : TForm(Owner)
{
freopen("c:\\injection.log", "a", stdout); printf("<__fastcallTBldForm::TBldForm(TComponent*Owner):TForm(Owner) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
freopen("c:\\injection.log", "a", stdout); printf("</__fastcallTBldForm::TBldForm(TComponent*Owner):TForm(Owner) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::FormActivate(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::FormActivate(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    StatusBar1->SimpleText = "";
    StatusBar1->SimplePanel = true;
    ListBox1->Clear();
    ListBox1->Sorted = false;
    Memo1->Lines->Clear();
    Max_Name_Width1 = 0;
    Max_Name_Width2 = 0;
    for(int ii = 0; ii < CheckListBox1->Count; ++ii)
        CheckListBox1->Checked[ii] = false;
    Label3->Caption = "";
    MapAKACopy = Global::MapAKA; 
    AKAselectiveDelete(Sender); 
    Global::Mapgetvar.clear();
    Global::Mapputvar.clear();
    Global::Mapreadvar.clear();
    Global::Mapdeclvar.clear();
    Global::Mapdeclstat.clear();
    Global::Mapdeclpar.clear();
    Global::Mapdeclobs.clear();
    CRHM::TBuild TempB = Global::BuildFlag;
    Global::BuildFlag = CRHM::BUILD; 
    for(int ii = 0; ii < Global::AllModulesList->Count; ++ii)
    {
        ClassModule* thisModule = (ClassModule*) Global::AllModulesList->Objects[ii];
        thisModule->variation_max = 0;
        long Temp = thisModule->variation;
        long Temp2 = thisModule->variation_set;
        thisModule->variation_set = 0;
        thisModule->variation = 0;
        thisModule->decl();
        thisModule->variation = Temp;
        thisModule->variation_set = Temp2;
        if(thisModule->variation > 0)
            thisModule->hh = log(thisModule->variation)/log(2) + 1; 
        else
            thisModule->hh = 0;
    }
    Global::OBS_AS_IS = 0; 
    Global::WQ_prj = false; 
    ListBox2->Clear();
    if(Global::OurModulesList->Count)
        ModifyBuild = true;
    else
    {
        ModifyBuild = false;
        CheckListBox1->Checked[CRHM::BASIC] = true;
    }
    for(int ii = 0 ; ii < Global::OurModulesList->Count; ++ii)  
    {
        CheckListBox1->Checked[((ClassModule*) Global::OurModulesList->Objects[ii])->Lvl] = true;
        ListBox2->Items->AddObject(Global::OurModulesList->Strings[ii], (TObject *) Global::OurModulesList->Objects[ii]);
        SetSuffix(ii);
        String S = Global::OurModulesList->Strings[ii];
        if(S.Length() > 33 && S.Length() > Max_Name_Width2) 
            Max_Name_Width2 = S.Length();
    }
    ListBox2->ScrollWidth =  Max_Name_Width2*6;
    Execute = false;
    for(int ii = 0 ; ii < Global::AllModulesList->Count; ++ii ) 
        if(CheckListBox1->Checked[((ClassModule*) Global::AllModulesList->Objects[ii])->Lvl] == true)
        {
            ListBox1->Items->AddObject(Global::AllModulesList->Strings[ii], (TObject *) Global::AllModulesList->Objects[ii]);
            String S = Global::AllModulesList->Strings[ii];
            if(S.Length() > 33 && S.Length() > Max_Name_Width1) 
                Max_Name_Width1 = S.Length();
        }
    ListBox1->ScrollWidth =  Max_Name_Width1*6;
    Global::BuildFlag = TempB;
    UpDownMAXHRU->Max = MAXHRU;
    UpDownMAXHRU->Position = Global::maxhru;
    LabelMAXHRU->Caption = "MAXHRU = " + String(UpDownMAXHRU->Position);
    UpDownMAXLAY->Max = MAXLAY;
    UpDownMAXLAY->Position = Global::maxlay;
    LabelMAXLAY->Caption = "MAXLAY = " + String(UpDownMAXLAY->Position);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::FormActivate(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::RemoveParameter(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::RemoveParameter(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *thisPar;
    for(itPar = Global::MapPars.begin(); itPar != Global::MapPars.end();)
    {
        thisPar = (*itPar).second;
        int kk = IndexOf(ListBox2, thisPar->module.c_str());
        if(kk == -1 && thisPar->module != "shared")    
        {
            Global::MapPars.erase(itPar++);
            delete thisPar;
        }
        else
        {
            ++itPar;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::RemoveParameter(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::BitBtn2Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::BitBtn2Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    Close();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::BitBtn2Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::DisplayModule(String S, ClassModule* thisModule, bool LBox1)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::DisplayModule(StringS,ClassModule*thisModule,boolLBox1) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    Mapstr::iterator itMap, pos, pos2;
    int indx;
    String SS, S1, S2;
    TGridOptions OurOptions;
    MapVar::iterator itVar;
    long Variation = 0;
    long Vindx = 0;
    int P;
    SS = S;
    if(P = S.Pos("#"), P > 0)  
    {
        Vindx = S[P+1] - char('0');
        Variation = pow(2, S[P+1] - char('1'));
        S = S.Delete(S.Length()-1, 2);
    }
    else
        Variation = 0;
    if(!thisModule->Description.IsEmpty())
    {
        TStringList* Fred = new TStringList;
        Fred->QuoteChar = '\'';
        Fred->DelimitedText = thisModule->Description;
        if(thisModule->variation_max > 0) 
            ++Vindx;
        if(LBox1)  
        {
            for(int ii = 0; ii < Fred->Count; ++ii)
            {
                S1 = S;
                if(ii == 0)
                    S1 += " Function summary";
                else if(ii > 1)
                    S1 += "#" + String(ii-1);
                else
                    S1 += "  ";
                S1 += " -> " + Fred->Strings[ii];
                Memo1->Lines->Add(S1);
            }
        }
        else
        {
            Memo1->Lines->Add(SS + " -> " + Fred->Strings[Vindx]);
            if(thisModule->DLLName == "Macro")
            {
                ClassMacro *thisMacro  = dynamic_cast<ClassMacro *> (thisModule);
                if(thisMacro->isGroup)
                {
                    Memo1->Lines->Add("Group with modules:");
                    String S;
                    for(int ii = 0; ii < thisMacro->GrpStringList->Count; ++ii)
                        if(ii == 0)
                            S = "  " + thisMacro->GrpStringList->Strings[ii];
                        else
                            S += ", " + thisMacro->GrpStringList->Strings[ii];
                    Memo1->Lines->Add(S);
                }
                else if(thisMacro->isStruct)
                {
                    Memo1->Lines->Add("Struct with modules:");
                    String S;
                    for(int ii = 0; ii < thisMacro->GrpStringList->Count; ++ii)
                        if(ii == 0)
                            S = "  " + thisMacro->GrpStringList->Strings[ii];
                        else
                            S += ", " + thisMacro->GrpStringList->Strings[ii];
                    Memo1->Lines->Add(S);
                }
                else
                {
                    Memo1->Lines->Add("Macro: " );
                    Memo1->Lines->Add("declarations:");
                    for(int ii = Global::MacroModulesList->IndexOf(thisMacro->Name.c_str()) + 1; ii < thisMacro->Begin - 1; ++ii)
                        Memo1->Lines->Add(" " + Global::MacroModulesList->Strings[ii]);
                    Memo1->Lines->Add("code:");
                    for(int ii = thisMacro->Begin; ii < thisMacro->End; ++ii)
                        Memo1->Lines->Add(" " + Global::MacroModulesList->Strings[ii]);
                }
            }
        }
        Memo1->Lines->Add(" ");
        delete Fred;
    }
    OurOptions << goHorzLine << goVertLine << goFixedVertLine << goColSizing;
    StringGrid1->Options = OurOptions;
    for (int I = 0; I < StringGrid1->ColCount; ++I)
        for (int J = 0; J < StringGrid1->RowCount; ++J)
            StringGrid1->Cells[I][J] = "";
    StringGrid1->ColCount = 6;
    StringGrid1->FixedRows = 0;
    StringGrid1->RowCount = 1;
    StringGrid1->Cells[0] [0] = "Observations";
    StringGrid1->Cells[1] [0] = "Modules";
    StringGrid1->Cells[2] [0] = "Inputs";
    StringGrid1->Cells[3] [0] = "Outputs";
    StringGrid1->Cells[4] [0] = "Parameters";
    StringGrid1->Cells[5] [0] = "New Observations";
    pair<Mapstr::iterator, Mapstr::iterator> range = Global::Mapreadvar.equal_range(S);
    int ii = 0;
    for(itMap = range.first; itMap != range.second; ++itMap)
    {
        SS = (itMap->second).first;
        if(StringGrid1->RowCount < ii+3)
            StringGrid1->RowCount = ii+3;
        int Indx = StringGrid1->Cols[0]->IndexOf(SS);
        if(Indx == -1 && Variation_Decide(Variation, (itMap->second).second))
        {
            StringGrid1->Cells[0] [ii+2] = SS;
            ++ii;
        }
    } 
    range = Global::Mapputvar.equal_range(S);
    ii = 0;
    for(itMap = range.first; itMap != range.second; ++itMap)
    {
        SS = itMap->second.first;
        int jj = SS.Pos(" ");
        S1 = SS.SubString(1, jj-1); 
        S2 = SS.SubString(jj+1, SS.Length() - jj); 
        if(S1 != S && Variation_Decide(Variation, (itMap->second).second))
        {
            if(StringGrid1->RowCount < ii+3)
                StringGrid1->RowCount = ii+3;
            StringGrid1->Cells[1] [ii+2] = S1;
            StringGrid1->Cells[2] [ii+2] = S2;
            ++ii;
        }
    } 
    range = Global::Mapgetvar.equal_range(S);
    for(itMap = range.first; itMap != range.second; ++itMap)
    {
        SS = itMap->second.first;
        int jj = SS.Pos(" ");
        S1 = SS.SubString(1, jj-1); 
        S2 = SS.SubString(jj+1, SS.Length() - jj); 
        if(S1 != S && Variation_Decide(Variation, (itMap->second).second))
        {
            int Indx = StringGrid1->Cols[2]->IndexOf(S2);
            if(Indx == -1)
            {
                if(StringGrid1->RowCount < ii+3)
                    StringGrid1->RowCount = ii+3;
                StringGrid1->Cells[1] [ii+2] = S1;
                StringGrid1->Cells[2] [ii+2] = S2;
                ++ii;
            }
        }
    } 
    range = Global::Mapdeclvar.equal_range(S);
    ii = 0;
    for(itMap = range.first; itMap != range.second; ++itMap)
    {
        SS = itMap->second.first;
        pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
                      value_equals<KeyType2,  KeyType2, Pairstr>(SS));
        pos2 = find_if(Global::Mapdeclobs.begin(), Global::Mapdeclobs.end(),
                       value_equals<KeyType2,  KeyType2, Pairstr>(SS));
        if((pos == Global::Mapreadvar.end() || Not_Obs(S, SS))&& pos2 == Global::Mapdeclobs.end())
        {
            int Indx = StringGrid1->Cols[3]->IndexOf(SS);
            if(Indx == -1 && Variation_Decide(Variation, (itMap->second).second) && Visible_Decide((itMap->second).second))
            {
                if(StringGrid1->RowCount < ii+3)
                    StringGrid1->RowCount = ii+3;
                StringGrid1->Cells[3] [ii+2] = SS;
                ++ii;
            }
        }
    } 
    range = Global::Mapdeclpar.equal_range(S);
    ii = 0;
    for(itMap = range.first; itMap != range.second; ++itMap)
    {
        if(Variation_Decide(Variation, (itMap->second).second) && Visible_Decide((itMap->second).second))
        {
            SS = itMap->second.first;
            if(StringGrid1->RowCount < ii+3)
                StringGrid1->RowCount = ii+3;
            StringGrid1->Cells[4] [ii+2] = SS;
            ++ii;
        }
    } 
    range = Global::Mapdeclobs.equal_range(S);
    ii = 0;
    for(itMap = range.first; itMap != range.second; ++itMap)
    {
        if(Variation_Decide(Variation, (itMap->second).second) && Visible_Decide((itMap->second).second))
        {
            SS = itMap->second.first;
            if(StringGrid1->RowCount < ii+3)
                StringGrid1->RowCount = ii+3;
            StringGrid1->Cells[5] [ii+2] = SS;
            ++ii;
        }
    } 
    if(StringGrid1->RowCount > 1)
        StringGrid1->FixedRows = 1;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::DisplayModule(StringS,ClassModule*thisModule,boolLBox1) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
long __fastcall TBldForm::Best_Match(String Var, TStringList *List)
{
freopen("c:\\injection.log", "a", stdout); printf("<long__fastcallTBldForm::Best_Match(StringVar,TStringList*List) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    long found = 10;
    long Indx = -1;
    for(int jj = 0; jj < List->Count; ++jj)
    {
        String Entry = List->Strings[jj];
        long kk = Entry.Pos(' ');
        String Var1 = Entry.SubString(kk+1, Entry.Length()); 
        bool rootVar = (Var.Pos("@") == 0); 
        bool rootVar1 = (Var1.Pos("@") == 0);
        if(Var1 == Var)  
        {
            found = 0;
            Indx = jj;
            break;
        }
        else if(rootVar && !rootVar1 && Var == Var1.SubString(0, Var1.Pos("@")) && found > 1)  
        {
            found = 1;
            Indx = jj;
        }
        else if(!rootVar && rootVar1 && Var.SubString(0, Var.Pos("@")) == Var1 && found > 2)   
        {
            found = 2;
            Indx = jj;
        }
        else if(!rootVar && !rootVar1 && Var.SubString(0, Var.Pos("@")) == Var1.SubString(0, Var1.Pos("@")) && found > 3)  
        {
            found = 3;
            Indx = jj;
        }
    } 
{freopen("c:\\injection.log", "a", stdout); printf("</long__fastcallTBldForm::Best_Match(StringVar,TStringList*List) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return Indx;}
freopen("c:\\injection.log", "a", stdout); printf("</long__fastcallTBldForm::Best_Match(StringVar,TStringList*List) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
long __fastcall TBldForm::CheckModel()
{
freopen("c:\\injection.log", "a", stdout); printf("<long__fastcallTBldForm::CheckModel() @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    long Showing = ListBox2->Items->Count;
    if(Showing == 0)
{freopen("c:\\injection.log", "a", stdout); printf("</long__fastcallTBldForm::CheckModel() @@@ Bld.cpp_nocom>\n"); fclose(stdout);return 0;}
    Mapstr::iterator itMap, pos, pos2;
    pair<Mapstr::iterator, Mapstr::iterator> rangeO;
    pair<Mapstr::iterator, Mapstr::iterator> rangeOobs;
    pair<Mapstr::iterator, Mapstr::iterator> rangeI;
    pair<Mapstr::iterator, Mapstr::iterator> rangeIobs;
    List = new TStringList;
    ListAll = new TStringList;
    ListUsed = new TStringList; 
    ListPuts = new TStringList;
    ListStats = new TStringList;
    List->Sorted = false; 
    ListUsed->Sorted = false; 
    ListPuts->Sorted = false; 
    ListStats->Sorted = false; 
    String S, SS, S1, S2;
    int indx, Error = 0, Wild = 0;
    MapAKAVar.clear();
    StatusBar1->SimpleText = "";
    Memo1->Lines->Clear();
    long Variation = 0;
    long Vindx = 0;
    int P;
Again:
    for(int ii = 0; ii < ListBox2->Items->Count; ++ii)
    {
        S = ListBox2->Items->Strings[ii];
        if(P = S.Pos("#"), P > 0)  
        {
            Vindx = S[P+1] - char('0');
            Variation = pow(2, S[P+1] - char('1'));
            S = S.Delete(S.Length()-1, 2);
        }
        else
            Variation = 0;
        rangeI = Global::Mapgetvar.equal_range(S);
        for(itMap = rangeI.first; itMap != rangeI.second; ++itMap)
        {
            SS = itMap->second.first;
            if(Variation_Decide(Variation, (itMap->second).second))
            {
                int jj = SS.Pos(" ");
                S1 = SS.SubString(1, jj-1);
                S2 = SS.SubString(jj+1, SS.Length() - jj); 
                if(S1[1] != '*')  
                {
                    rangeO = Global::Mapdeclvar.equal_range(S);
                    bool Found = false;
                    for(pos = rangeO.first; pos != rangeO.second; ++pos)
                    {
                        if(S2 == pos->second.first)  
                        {
                            Found = true;
                            break;
                        }
                    }
                    if(!Found)  
                    {
                        indx = IndexOf(ListBox2, S1); 
                        if(indx == -1)   
                        {
                            indx = IndexOf(ListBox1, S1); 
                            if(indx == -1)   
                            {
                                LogError("module not found: " + S1, ERR); 
                                Memo1->Lines->Add("module not found: " + S1);
                            }
                            else
                            {
                                int result = IDYES;
                                result = Application->MessageBox(String("To satisfy module " + S + " input " + SS).c_str(), String("Add module " + S1 + " ?").c_str(), MB_YESNO);
                                if(result == IDYES)
                                    ListBox2->Items->InsertObject(ii, S1, ListBox1->Items->Objects[indx]);
                            }
                        }
                    } 
                } 
            } 
        } 
    } 
    for(int ii = 0; ii < ListBox2->Items->Count; ++ii)
    {
        S = ListBox2->Items->Strings[ii];
        if(P = S.Pos("#"), P > 0)  
        {
            Vindx = S[P+1] - char('0');
            Variation = pow(2, S[P+1] - char('1'));
            S = S.Delete(S.Length()-1, 2);
        }
        else
            Variation = 0;
        rangeI = Global::Mapdeclstat.equal_range(S);
        for(itMap = rangeI.first; itMap != rangeI.second; ++itMap)
        {
            SS = itMap->second.first; 
            if(Variation_Decide(Variation, (itMap->second).second))
                ListStats->Add(SS);
        } 
        rangeO = Global::Mapdeclvar.equal_range(S);
        rangeOobs = Global::Mapdeclobs.equal_range(S);
        rangeI = Global::Mapgetvar.equal_range(S);
        rangeIobs = Global::Mapreadvar.equal_range(S);
        for(itMap = rangeOobs.first; itMap != rangeOobs.second; ++itMap)
        {
            SS = itMap->second.first; 
            if(Variation_Decide(Variation, (itMap->second).second))
                List->AddObject(S + " " + SS, (TObject *) 0);
        } 
        for(itMap = rangeO.first; itMap != rangeO.second; ++itMap)
        {
            SS = itMap->second.first; 
            if(Variation_Decide(Variation, (itMap->second).second))
            {
                pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
                              value_equals<KeyType2,  KeyType2, Pairstr>(SS));
                pos2 = find_if(Global::Mapdeclobs.begin(), Global::Mapdeclobs.end(),
                               value_equals<KeyType2,  KeyType2, Pairstr>(SS));
                if((pos == Global::Mapreadvar.end() || Not_Obs(S, SS))&& pos2 == Global::Mapdeclobs.end())
                {
                    S2 = ListBox2->Items->Strings[ii] + " " + SS;
                    String S3;
                    String M3;
                    bool Twice = false;
                    int tt;
                    for(tt = 0; tt < ListAll->Count; ++tt)
                    {
                        int jj = ListAll->Strings[tt].Pos(" ");
                        S3 = ListAll->Strings[tt].SubString(jj+1, ListAll->Strings[tt].Length() - jj); 
                        M3 = ListAll->Strings[tt].SubString(1, jj-1); 
                        if(S3 == SS && S != M3 && S != "obs")
                        {
                            if(S3[S3.Length()] != '#')
                            {
                                Twice = true;
                                break;
                            }
                        }
                    }
                    if(Twice)
                    {
                        int result = IDYES;
                        result = Application->MessageBox(String("YES to remove '" + S + "' or NO to remove '" + M3 + "'").c_str(),
                                                         String("Module output generated twice: '" + S2 + "' defined earlier as '" + ListAll->Strings[tt] + "'").c_str(), MB_YESNO);
                        if(result == IDYES)
                            tt = IndexOf(ListBox2, S); 
                        else if(result == IDNO)
                            tt = IndexOf(ListBox2, M3); 
                        ListBox2->Items->Delete(tt);
                        Entries.clear();
                        List->Clear();
                        ListAll->Clear();
                        ListUsed->Clear();
                        ListPuts->Clear();
                        ListStats->Clear();
                        goto Again;
                    }
                    ListAll->Add(S2);
                    int indx = List->IndexOf(S2);
                    if(indx == -1)
                        List->AddObject(S2, (TObject *) 0);
                } 
            } 
        } 
        for(itMap = rangeI.first; itMap != rangeI.second; ++itMap)
        {
            SS = itMap->second.first; 
            if(Variation_Decide(Variation, (itMap->second).second))
            {
                int indx = List->IndexOf(SS);
                if(indx == -1 && SS[1] != '*')   
                {
                    int jj = SS.Pos(" ");
                    S2 = SS.SubString(jj+1, SS.Length() - jj); 
                    S1 = S + ' ' + S2; 
                    indx = List->IndexOf(S1);
                    if(indx == -1 && S1[S1.Length()-1] == '@') 
                        indx = List->IndexOf(SS.SubString(0, SS.Pos("@"))); 
                }
                if(indx == -1)
                {
                    ListUsed->AddObject(SS, (TObject *) -(ii+1)); 
                }
                else
                {
                    int Cnt = (int) List->Objects[indx]; 
                    List->Objects[indx] = (TObject *) ++Cnt;
                    ListUsed->AddObject(SS, (TObject *) ii);
                }
            } 
        } 
        rangeI = Global::Mapputvar.equal_range(S);
        for(itMap = rangeI.first; itMap != rangeI.second; ++itMap)
        {
            SS = itMap->second.first; 
            if(Variation_Decide(Variation, (itMap->second).second))
            {
                int indx = List->IndexOf(SS);
                if(indx == -1)
                {
                    ListPuts->AddObject(SS, (TObject *) ListUsed->Count); 
                    ListUsed->AddObject(SS, (TObject *) -(ii+1)); 
                }
                else
                {
                    int Cnt = (int) List->Objects[indx]; 
                    List->Objects[indx] = (TObject *) ++Cnt;
                    ListPuts->AddObject(SS, (TObject *) ListUsed->Count);
                    ListUsed->AddObject(SS, (TObject *) ii);
                }
            } 
        } 
        for(itMap = rangeIobs.first; itMap != rangeIobs.second; ++itMap)
        {
            SS = itMap->second.first; 
            if(Variation_Decide(Variation, (itMap->second).second))
            {
                pos = find_if(Global::Mapdeclobs.begin(), Global::Mapdeclobs.end(),
                              value_equals<KeyType2,  KeyType2, Pairstr>(SS));
                if(pos == Global::Mapdeclobs.end())
                    continue; 
                indx = IndexOf(ListBox2, pos->first); 
                if(indx != ii && indx > -1)  
                {
                    S1 = pos->first;
                    SS = pos->second.first;
                    S2 = S1 + " " + SS;
                    indx = List->IndexOf(S2);
                    if(indx == -1)   
                    {
                        ListUsed->AddObject(S2, (TObject *) -(ii+1));
                    }
                    else
                    {
                        int Cnt = (int) List->Objects[indx]; 
                        List->Objects[indx] = (TObject *) ++Cnt;
                        ListUsed->AddObject(S2, (TObject *) ii);
                    }
                } 
            } 
        } 
    } 
    for(int ii = 0; ii < ListBox2->Items->Count; ++ii)
    {
        S = ListBox2->Items->Strings[ii];
        if(P = S.Pos("#"), P > 0)  
        {
            Vindx = S[P+1] - char('0');
            Variation = pow(2, S[P+1] - char('1'));
            S = S.Delete(S.Length()-1, 2);
        }
        else
        {
            Vindx = 0;
            Variation = 0;
        }
        ClassModule *Module = (ClassModule*) ListBox2->Items->Objects[ii];
        TStringList *Choices = new TStringList;
        Choices->CommaText = Module->PeerVar;
        if(Choices->Count > Vindx)
            SS = Choices->Strings[Vindx];
        else if(Choices->Count)
            SS = Choices->Strings[Choices->Count-1];
        else
            SS = "";
        if(SS != "")
        {
            for(int jj = 0; jj < List->Count; ++jj)
            {
                String Entry = List->Strings[jj];
                long kk = Entry.Pos(' ');
                S1 = Entry.SubString(kk+1, Entry.Length());
                if(S1 == SS)
                    break;
            } 
            if(S1 == SS)
            {
                SS = "* " + SS;
                ListUsed->AddObject(SS, (TObject *) -(ii+1)); 
                String SSS = "Ranking module '" + S + "' to '" + SS + "'";
                Memo1->Lines->Add(SSS);
            }
            else
            {
                S2 = "Ranking module '" + S + "' to an inaccessible variable '" + SS + "'";
                Memo1->Lines->Add(S2);
            }
        } 
    } 
    for(int ii = 0; ii < ListUsed->Count; ++ii)
    {
        if(ListUsed->Strings[ii][1] == '*')
        {
            String Var = ListUsed->Strings[ii];
            Var = Var.SubString(3, Var.Length());
            int jj = Best_Match(Var, List);
            if(jj > -1)  
            {
                ++Wild;
                int thisModule = (int) ListUsed->Objects[ii];
                thisModule = -(thisModule+1);
                String Module = ListBox2->Items->Strings[thisModule];
                ListUsed->Strings[ii] =  List->Strings[jj];
                ListUsed->Objects[ii] =  (TObject *) abs((int) ListUsed->Objects[ii]+1); 
            } 
        } 
        else   
        {
            int NotFoundIndx = (int) ListUsed->Objects[ii];
            if(NotFoundIndx < 0)   
            {
                int indx = List->IndexOf(ListUsed->Strings[ii]);
                if(ListPuts->IndexOf(ListUsed->Strings[ii]) == -1 && indx == -1)
                    ++Error;
                if(indx > -1)
                {
                    ListUsed->Objects[ii] =  (TObject *) abs((int) ListUsed->Objects[ii]+1); 
                    continue;
                }
            }
            else
            {
                continue; 
            }
        } 
        int NotFoundIndx = (int) ListUsed->Objects[ii];
        if(NotFoundIndx < 0 && ListUsed->Strings[ii][1] == '*')   
        {
            String Message;
            String Message2(" Suggestions: ");
            ++Error;
            LogError("wild variable not found: " + ListUsed->Strings[ii], WARNING);
            int kk =  abs((int) ListUsed->Objects[ii]+1); 
            String Sroot = ListUsed->Strings[ii];
            if(Sroot.Pos("@") != 0)
                Sroot = Sroot.SubString(0, Sroot.Pos("@"));
            Message = "wild variable not found: \" " + Sroot + "\" used by " + ListBox2->Items->Strings[kk] + ".";
            String SW = ListUsed->Strings[ii];
            SW = SW.SubString(3, ListUsed->Strings[ii].Length());
            bool Once = false;
            bool rootVar = (SW.Pos("@") == 0); 
            if(!rootVar)
                SW = SW.SubString(0, SW.Pos("@"));
            for(itMap = Global::Mapdeclvar.begin(); itMap != Global::Mapdeclvar.end(); ++itMap)
            {
                SS = itMap->second.first;
                bool rootVar1 = (SS.Pos("@") == 0); 
                if(!rootVar1)
                    SS = SS.SubString(0, SS.Pos("@"));
                if(SW == SS)
                {
                    Once = true;
                    String S = itMap->first;
                    VandP V;
                    V.Set((itMap->second).second);
                    long Variation = V.GetV() & 2047;
                    if(Variation > 0)
                    {
                        long NN = log(Variation)/log(2) + 1;
                        String  AA = "#0";
                        AA[2] += NN;
                        S += AA;
                    }
                    Message2 += S + ", ";
                }
            } 
            if(!Once)
                Memo1->Lines->Add(Message + " No " + Message2);
            else
                Memo1->Lines->Add(Message + Message2);
        } 
    } 
    if(Error)
    {
        S = "Errors: " + String(Error) + ';';
        String Line = AnsiString::StringOfChar('*', 80);;
        Memo1->Lines->Add(Line);
    }
    else
    {
        bool Loop = true;
        int Loops = 0;
        TStringList *OrgList = new TStringList; 
        for(int ii = 0; ii < ListBox2->Items->Count; ++ii)
        {
            OrgList->AddObject(ListBox2->Items->Strings[ii], (TObject*) ii);
            Entries.push_back(ClassEntry()); 
        }
        while(Loop)
        {
            Loop = false;
            ++Loops;
            for(int ii = 0; ii < ListBox2->Items->Count; ++ii)
            {
                Entries[ii].module = (ClassModule*) ListBox2->Items->Objects[ii];
                Entries[ii].Name = ListBox2->Items->Strings[ii]; 
                Entries[ii].rank = 0; 
                Entries[ii].used = false; 
                unsigned long index = OrgList->IndexOf(ListBox2->Items->Strings[ii]);
                if(index < 0 || index > Entries.size()-1)
                {
                    LogError("Build error: outside range", ERR);  
                }
                Entries[ii].OrigPos = index;
            } 
            for(int ii = 0; ii < ListPuts->Count; ++ii)   
            {
                ListPuts->Strings[ii] = ListUsed->Strings[(int) ListPuts->Objects[ii]];
            }
            for(int ii = 0; ii < ListUsed->Count; ++ii)
            {
                unsigned long thisModule = (int) ListUsed->Objects[ii]; 
                for(unsigned long nn = 0; nn  < Entries.size(); ++nn)
                {
                    if(Entries[nn].OrigPos == thisModule)
                    {
                        thisModule = nn; 
                        if(thisModule < 0 || thisModule > Entries.size()-1)
                        {
                            LogError("Build error: outside range", ERR);  
                        }
                        break;
                    } 
                } 
                String Entry = ListUsed->Strings[ii];
                long kk = Entry.Pos(' ');
                String UsesModule = Entry.SubString(1, kk-1); 
                String Var_only =  Entry.SubString(kk+1, Entry.Length() - kk); 
                unsigned long index;
                ClassModule* checkModule;
                for(index = 0; index < Entries.size(); ++index)  
                {
                    String Root = Entries[index].Name;
                    if(Root == UsesModule)
                    {
                        checkModule = Entries[index].module;
                        break;
                    }
                }
                if(checkModule && checkModule->isGroup)  
                {
                    Entries[index].used = true;
                    continue;
                }
                if(index >= Entries.size())
                    continue; 
                Entries[index].used = true;
                if(UsesModule == Entries[thisModule].Name) 
                    continue;
                int jj = Best_Match(Var_only, ListPuts);
                if(jj > -1 && ii == ((int) ListPuts->Objects[jj]))
                    continue; 
                jj = Best_Match(Var_only, ListStats);
                if(jj > -1)
                    continue; 
                long B = powl(2, index); 
                Entries[thisModule].rank |= B; 
            } 
            for(unsigned long ii = 0; ii < Entries.size()-1; ++ii)
            {
                for(unsigned long jj = ii+1; jj < Entries.size(); ++jj)
                {
                    if(Entries[jj].rank < Entries[ii].rank)
                    {
                        MoveDown(Entries, ii, jj);
                        Loop = true;
                    }
                } 
            } 
            for(long ii = 0; ii < Entries.size()-1; ++ii)
            {
                ClassModule * E2 = (ClassModule*) Entries[ii].module;
                if(E2->PeerRank < 0)
                    Entries[ii].used = true;
                for(long jj = ii+1; jj < Entries.size(); ++jj)
                {
                    if(Entries[jj].rank == Entries[ii].rank)
                    {
                        ClassModule * E1 = (ClassModule*) Entries[jj].module;
                        if(labs(E1->PeerRank) < labs(E2->PeerRank))
                        {
                            MoveDown(Entries, ii, jj);
                            Loop = true;
                        }
                    } 
                } 
            } 
            ListBox2->Clear();
            for(unsigned long ii = 0; ii <  Entries.size(); ++ii)
                ListBox2->Items->AddObject(Entries[ii].Name, (TObject*) Entries[ii].module);
            if(Loops > 20)   
            {
                Loop = false;
                Loops = -Loops;
            }
        } 
        bool Removed = false;
        for(unsigned long ii = 0; ii <  Entries.size()-1; ++ii)
        {
            if(!Entries[ii].used && Entries[ii].Name != "basin")   
            {
                int result = IDYES;
                result = Application->MessageBox(Entries[ii].Name.c_str(), "Module not used!  Remove module?", MB_YESNO);
                if(result != IDYES)
                    continue;
                int indx = IndexOf(ListBox2, Entries[ii].Name);
                ListBox2->Items->Delete(indx);
                Removed = true;
            }
        }
        Entries.clear();
        List->Clear();
        ListAll->Clear();
        ListUsed->Clear();
        ListPuts->Clear();
        ListStats->Clear();
        if(Removed)
            goto Again;
        int moves = 0;
        for(unsigned long ii = 0; ii < Entries.size(); ++ii)
            if(Entries[ii].OrigPos != ii)
                ++moves; 
        if(Loops)
        {
            Memo1->Lines->Add(" ");
            LogError("Number of loops to build: " + String(Loops) + " and modules moved: " + String(moves), WARNING);
            Memo1->Lines->Add("Number of loops to build: " + String(Loops) + " and modules moved: " + String(moves));
        }
        else
        {
            LogError("Problem with modules in build. Possibly modules referencing one another!", WARNING);
            Memo1->Lines->Add("Problem with modules in build. Possibly modules referencing one another!");
            Application->MessageBox("Problem with modules in build.", "Possibly modules referencing one another!", MB_OK);
        }
        Entries.clear();
        delete OrgList;
        S = "";
    } 
    if(Global::nlay != UpDownMAXLAY->Position || Global::nhru != UpDownMAXHRU->Position)
    {
        LogError("# of HRUs changed: *** edit parameters ***", WARNING);
        Memo1->Lines->Add(" ");
        Memo1->Lines->Add("# of HRUs changed: *** edit parameters ***");
    }
    if(Wild)
        S += "  Wild references: " + String(Wild) + ';';
    StatusBar1->SimpleText = S;
    StatusBar1->Repaint();
    delete List;
    delete ListAll;
    delete ListUsed;
{freopen("c:\\injection.log", "a", stdout); printf("</long__fastcallTBldForm::CheckModel() @@@ Bld.cpp_nocom>\n"); fclose(stdout);return Error;}
freopen("c:\\injection.log", "a", stdout); printf("</long__fastcallTBldForm::CheckModel() @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::CheckClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::CheckClick(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    CheckModel();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::CheckClick(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::FormClose(TObject *Sender, TCloseAction &Action)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::FormClose(TObject*Sender,TCloseAction&Action) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    Global::MapAKA = MapAKACopy;
    ListBox1->Clear();
    ListBox2->Clear();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::FormClose(TObject*Sender,TCloseAction&Action) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::FormDeactivate(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::FormDeactivate(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    for(int cc = 0; cc < StringGrid1->ColCount; ++cc)
        StringGrid1->Cols[cc]->Clear();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::FormDeactivate(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::UpDownMAXLAYClick(TObject *Sender, TUDBtnType Button)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::UpDownMAXLAYClick(TObject*Sender,TUDBtnTypeButton) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    LabelMAXLAY->Caption = "MAXLAY = " + String(UpDownMAXLAY->Position);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::UpDownMAXLAYClick(TObject*Sender,TUDBtnTypeButton) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::UpDownMAXHRUClick(TObject *Sender, TUDBtnType Button)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::UpDownMAXHRUClick(TObject*Sender,TUDBtnTypeButton) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    LabelMAXHRU->Caption = "MAXHRU = " + String(UpDownMAXHRU->Position);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::UpDownMAXHRUClick(TObject*Sender,TUDBtnTypeButton) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::SaveBuildParameters(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::SaveBuildParameters(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    ClassPar *thisPar;
    if(ModifyBuild)
    {
        Main->RemoveSharedParams(); 
        ParaList = new TStringList;
        MapPar::iterator itPar;
        itPar = Global::MapPars.begin();
        while (itPar !=  Global::MapPars.end())
        {
            thisPar = (*itPar).second;
            String S = String(((*itPar).second)->module.c_str()) + " " + ((*itPar).second)->param.c_str();
            if(ParaList->IndexOf(S) == -1)
            {
                ClassPar* par(new ClassPar(*thisPar));
                ParaList->AddObject(S, (TObject *) par);
            }
            ++itPar;
        } 
    } 
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::SaveBuildParameters(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::ReadBuildParameters(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::ReadBuildParameters(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *thisPar;
    if(ModifyBuild)
    {
        itPar = Global::MapPars.begin();
        while (itPar !=  Global::MapPars.end())
        {
            thisPar = (*itPar).second;
            String S = String(((*itPar).second)->module.c_str()) + " " + ((*itPar).second)->param.c_str();
            int ii = ParaList->IndexOf(S);
            if(ii != -1)
            {
                ClassPar *OldPar = (ClassPar *) ParaList->Objects[ii];
                thisPar->Change(*OldPar);  
            }
            ++itPar;
        } 
        for(int ii = 0; ii < ParaList->Count; ++ii)
            delete (ClassPar *) ParaList->Objects[ii]; 
        delete ParaList;
        ParaList = NULL;
        Main->SqueezeParams(Sender);  
    } 
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::ReadBuildParameters(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::BitBtn1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::BitBtn1MouseDown(TObject*Sender,TMouseButtonButton,TShiftStateShift,intX,intY) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    long Showing = ListBox2->Items->Count;
    if(Showing == 0)
    {
        Global::nlay = UpDownMAXLAY->Position;
        Global::nhru = UpDownMAXHRU->Position;
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::BitBtn1MouseDown(TObject*Sender,TMouseButtonButton,TShiftStateShift,intX,intY) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return;}
    }
    long Errors = CheckModel();
    if(Errors)
    {
        Application->MessageBox("Model has unsatisfied module inputs or multiple definitions",
                                String("Errors: " + String(Errors)).c_str(), MB_OK);
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::BitBtn1MouseDown(TObject*Sender,TMouseButtonButton,TShiftStateShift,intX,intY) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return;}
    }
    if(ModifyBuild)
    {
        SaveBuildParameters(Sender);
        RemoveParameter(Sender);
    }
    MapAKACopy = Global::MapAKA; 
    Main->ClearModules(Sender, false); 
    Global::nlay = UpDownMAXLAY->Position;
    Global::nhru = UpDownMAXHRU->Position;
    if(Global::nhru > Global::maxhru)
    {
        Update_Main_DIM(CRHM::NHRU, Global::nhru);
    }
    for(int ii = 0; ii < ListBox2->Items->Count; ++ii)   
    {
        ClassModule* thisModule = (ClassModule*) ListBox2->Items->Objects[ii];
        if(FormatMax(thisModule->variation_max) > 0)  
        {
            thisModule->variation = pow(2, thisModule->hh - 1); 
            if(ListBox2->Items->Strings[ii].Pos("#") > 0)  
            {
                ListBox2->Items->Strings[ii] = ListBox2->Items->Strings[ii].Delete(ListBox2->Items->Strings[ii].Length()-1, 2);
            }
        }
    }
    Global::OurModulesList->Assign(ListBox2->Items);
    Execute = true;
    Global::BuildFlag = CRHM::BUILD; 
    if(!MapAKAVar.empty())
    {
        Mapstr2::iterator it;
        for (it = MapAKAVar.begin(); it !=  MapAKAVar.end(); ++it)
            MapAKACopy.insert(*it);
    }
    Close();
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::BitBtn1MouseDown(TObject*Sender,TMouseButtonButton,TShiftStateShift,intX,intY) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return;}
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::BitBtn1MouseDown(TObject*Sender,TMouseButtonButton,TShiftStateShift,intX,intY) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::AKAselectiveDelete(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::AKAselectiveDelete(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    if(!Global::MapAKA.empty())   
    {
        Mapstr2::iterator it;
        for (it = Global::MapAKA.begin(); it !=  Global::MapAKA.end(); )
        {
            string Var = (*it).first; 
            string::size_type idx = Var.find(' ');
            string type = Var.substr(0, idx);
            TAKA Type = AKAtype(type);
            switch (Type)
            {
            case OBSR :
            case OBSF :
                ++it;
                break;
            default :
                Global::MapAKA.erase(it++);
            } 
        } 
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::AKAselectiveDelete(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
int __fastcall TBldForm::IndexOf(TListBox *Box, const AnsiString S)
{
freopen("c:\\injection.log", "a", stdout); printf("<int__fastcallTBldForm::IndexOf(TListBox*Box,constAnsiStringS) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < Box->Count; ++ii)
    {
        if(Box->Items->Strings[ii] == S)
{freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTBldForm::IndexOf(TListBox*Box,constAnsiStringS) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return ii;}
    }
{freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTBldForm::IndexOf(TListBox*Box,constAnsiStringS) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return -1;}
freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTBldForm::IndexOf(TListBox*Box,constAnsiStringS) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
bool __fastcall TBldForm::Not_Obs(String Mod, String Var)
{
freopen("c:\\injection.log", "a", stdout); printf("<bool__fastcallTBldForm::Not_Obs(StringMod,StringVar) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    pair<Mapstr::iterator, Mapstr::iterator> rangeIobs = Global::Mapreadvar.equal_range(Mod);
    for(Mapstr::iterator itMap = rangeIobs.first; itMap != rangeIobs.second; ++itMap)
        if(Var == itMap->second.first)
{freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTBldForm::Not_Obs(StringMod,StringVar) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return false;}
{freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTBldForm::Not_Obs(StringMod,StringVar) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return true;}
freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTBldForm::Not_Obs(StringMod,StringVar) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::Label1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::Label1Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    ListBox1->Sorted = !ListBox1->Sorted;
    ListBox1->Clear();
    Max_Name_Width1 = 0;
    for(int ii = 0 ; ii < Global::AllModulesList->Count; ++ii)
        if(CheckListBox1->Checked[((ClassModule*) Global::AllModulesList->Objects[ii])->Lvl] == true)
        {
            ListBox1->Items->AddObject(Global::AllModulesList->Strings[ii], (TObject *) Global::AllModulesList->Objects[ii]);
            String S = Global::AllModulesList->Strings[ii];
            if(S.Length() > 33 && S.Length() > Max_Name_Width1) 
                Max_Name_Width1 = S.Length();
        }
    ListBox1->ScrollWidth =  Max_Name_Width1*6;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::Label1Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::CheckListBox1ClickCheck(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::CheckListBox1ClickCheck(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    ListBox1->Clear();
    Max_Name_Width1 = 0;
    for(int ii = 0 ; ii < Global::AllModulesList->Count; ++ii )
        if(CheckListBox1->Checked[((ClassModule*) Global::AllModulesList->Objects[ii])->Lvl] == true)
        {
            ListBox1->Items->AddObject(Global::AllModulesList->Strings[ii], (TObject *) Global::AllModulesList->Objects[ii]);
            String S = Global::AllModulesList->Strings[ii];
            if(S.Length() > 33 && S.Length() > Max_Name_Width1) 
                Max_Name_Width1 = S.Length();
        }
    ListBox1->ScrollWidth =  Max_Name_Width1*6;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::CheckListBox1ClickCheck(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::Add1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::Add1Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    TComponent *pComponent = PopupMenuListBox1->PopupComponent;
    if(pComponent)
    {
        if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox1")
        {
            for(int ii = 0; ii < ListBox1->Items->Count; ++ii)
            {
                if(ListBox1->Selected[ii])
                {
                    String S = ListBox1->Items->Strings[ii] ;
                    if(IndexOf(ListBox2, S) == -1)
                    {
                        ListBox2->Items->AddObject(S, ListBox1->Items->Objects[ii]); 
                        if(S.Length() > 33 && S.Length() > Max_Name_Width2) 
                            Max_Name_Width2 = S.Length();
                        CheckListBox1->Checked[((ClassModule*) ListBox1->Items->Objects[ii])->Lvl] = true; 
                        int jj = 0;
                        for(int iii = 0; iii < ListBox1->Items->Count; ++iii)   
                        {
                            int kk = IndexOf(ListBox2, ListBox1->Items->Strings[iii]);
                            if(kk > -1)
                            {
                                if(kk != jj)
                                    ListBox2->Items->Exchange(kk, jj);
                                ++jj;
                                if(jj >= ListBox2->Items->Count-1)
                                    break;
                            }
                        }
                    } 
                } 
            } 
            ListBox2->ScrollWidth =  Max_Name_Width2*6;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::Add1Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::Delete1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::Delete1Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    TComponent *pComponent = PopupMenuListBox2->PopupComponent;
    if(pComponent)
    {
        if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox2")
        {
            for(int ii = ListBox2->Items->Count-1; ii >= 0; --ii)
            {
                if(ListBox2->Selected[ii])
                {
                    ListBox2->Items->Delete(ii);
                    Label3->Caption = "";
                } 
            } 
            Max_Name_Width2 = 0;
            for(int ii = ListBox2->Items->Count-1; ii >= 0; --ii)
            {
                String S = ListBox2->Items->Strings[ii] ;
                if(S.Length() > 33 && S.Length() > Max_Name_Width2) 
                    Max_Name_Width2 = S.Length();
            } 
            ListBox2->ScrollWidth =  Max_Name_Width2*6;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::Delete1Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::ListBox2Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::ListBox2Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    String S = ListBox2->Items->Strings[ListBox2->ItemIndex] ;
    ClassModule* thisModule = (ClassModule*)ListBox2->Items->Objects[IndexOf(ListBox2, S)];
    DisplayModule(S, thisModule, false);
    CRHM::LMODULE Lvl = thisModule->Lvl;
    Label3->Caption = LVLStrings[Lvl];
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::ListBox2Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::ListBox1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::ListBox1Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    String S = ListBox1->Items->Strings[ListBox1->ItemIndex] ;
    ClassModule* thisModule = (ClassModule*)ListBox1->Items->Objects[IndexOf(ListBox1, S)];
    DisplayModule(S, thisModule, true);
    CRHM::LMODULE Lvl = thisModule->Lvl;
    Label3->Caption = LVLStrings[Lvl];
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::ListBox1Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
long __fastcall TBldForm::FormatMax(long M)
{
freopen("c:\\injection.log", "a", stdout); printf("<long__fastcallTBldForm::FormatMax(longM) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    M = M & 2047;
    if(M == 0)
{freopen("c:\\injection.log", "a", stdout); printf("</long__fastcallTBldForm::FormatMax(longM) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return 0;}
    for(int ii = 1; ii < 8; ++ii)
    {
        M = (M >> 1);
        if(M == 0)
{freopen("c:\\injection.log", "a", stdout); printf("</long__fastcallTBldForm::FormatMax(longM) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return ii;}
    }
{freopen("c:\\injection.log", "a", stdout); printf("</long__fastcallTBldForm::FormatMax(longM) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return -1;}
freopen("c:\\injection.log", "a", stdout); printf("</long__fastcallTBldForm::FormatMax(longM) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::Variation1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::Variation1Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    TComponent *pComponent = PopupMenuListBox2->PopupComponent;
    if(pComponent)
    {
        if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox2")
        {
            for(int ii = 0; ii < ListBox2->Items->Count; ++ii)
            {
                if(ListBox2->Selected[ii])
                {
                    ClassModule* thisModule = (ClassModule*) ListBox2->Items->Objects[ii];
                    if(FormatMax(thisModule->variation_max) > 0)  
                    {
                        String AA;
                        ++thisModule->hh;
                        if(thisModule->hh > FormatMax(thisModule->variation_max))
                            thisModule->hh = 0;
                        else
                        {
                            AA = "#0";
                            AA[2] += thisModule->hh;
                        }
                        if(ListBox2->Items->Strings[ii].Pos("#") > 0) 
                            ListBox2->Items->Strings[ii] = ListBox2->Items->Strings[ii].Delete(ListBox2->Items->Strings[ii].Length()-1, 2);
                        ListBox2->Items->Strings[ii] = ListBox2->Items->Strings[ii] + AA;
                        DisplayModule(ListBox2->Items->Strings[ii], thisModule, false);
                        ListBox2->Selected[ii] = true;
                    }
                } 
            } 
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::Variation1Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::SetSuffix(long Row)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::SetSuffix(longRow) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    ClassModule* thisModule = (ClassModule*) ListBox2->Items->Objects[Row];
    String AA;
    if(thisModule->hh > 0)
    {
        AA = "#0";
        AA[2] += thisModule->hh;
    }
    if(ListBox2->Items->Strings[Row].Pos("#") > 0) 
        ListBox2->Items->Strings[Row] = ListBox2->Items->Strings[Row].Delete(ListBox2->Items->Strings[Row].Length()-1, 2);
    ListBox2->Items->Strings[Row] = ListBox2->Items->Strings[Row] + AA;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::SetSuffix(longRow) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TBldForm::Last1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTBldForm::Last1Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    TComponent *pComponent = PopupMenuListBox2->PopupComponent;
    if(pComponent)
    {
        if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox2")
        {
            for(int ii = 0; ii < ListBox2->Items->Count; ++ii)
            {
                if(ListBox2->Selected[ii])
                {
                    ClassModule* thisModule = (ClassModule*) ListBox2->Items->Objects[ii];
                    if(FormatMax(thisModule->variation_max) > 0)  
                    {
                        String AA;
                        --thisModule->hh;
                        if(thisModule->hh < 0)
                            thisModule->hh = FormatMax(thisModule->variation_max);
                        if(thisModule->hh > 0)
                        {
                            AA = "#0";
                            AA[2] += thisModule->hh;
                        }
                        if(ListBox2->Items->Strings[ii].Pos("#") > 0) 
                            ListBox2->Items->Strings[ii] = ListBox2->Items->Strings[ii].Delete(ListBox2->Items->Strings[ii].Length()-1, 2);
                        ListBox2->Items->Strings[ii] = ListBox2->Items->Strings[ii] + AA;
                        DisplayModule(ListBox2->Items->Strings[ii], thisModule, false);
                        ListBox2->Selected[ii] = true;
                    }
                } 
            } 
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTBldForm::Last1Click(TObject*Sender) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
bool TBldForm::Variation_Decide(int Variation_set, long Variation)
{
freopen("c:\\injection.log", "a", stdout); printf("<boolTBldForm::Variation_Decide(intVariation_set,longVariation) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    VandP V;
    V.Set(Variation);
    long variations = V.GetV(); 
    if((variations & 2048) != 0 && Variation_set == 0 || 
            (variations & 4096) != 0 ||                        
            (variations == 0) ||                               
            (variations & Variation_set) != 0)                 
{freopen("c:\\injection.log", "a", stdout); printf("</boolTBldForm::Variation_Decide(intVariation_set,longVariation) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return true;}
    else
{freopen("c:\\injection.log", "a", stdout); printf("</boolTBldForm::Variation_Decide(intVariation_set,longVariation) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return false;}
freopen("c:\\injection.log", "a", stdout); printf("</boolTBldForm::Variation_Decide(intVariation_set,longVariation) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
bool TBldForm::Visible_Decide(long Variation)
{
freopen("c:\\injection.log", "a", stdout); printf("<boolTBldForm::Visible_Decide(longVariation) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
    VandP V;
    V.Set(Variation);
    long Visible = V.GetP();
{freopen("c:\\injection.log", "a", stdout); printf("</boolTBldForm::Visible_Decide(longVariation) @@@ Bld.cpp_nocom>\n"); fclose(stdout);return Visible == 1;}
freopen("c:\\injection.log", "a", stdout); printf("</boolTBldForm::Visible_Decide(longVariation) @@@ Bld.cpp_nocom>\n"); fclose(stdout);
}
