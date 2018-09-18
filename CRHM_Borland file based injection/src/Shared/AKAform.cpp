#include <vcl.h>
#pragma hdrstop
#include "AKAform.h"
#include "DefCRHMGlobal.h"
#include "ClassModule.h"
#include "CRHMmain.h"
#include <sstream>
#define REN 3 
#define ROW2 2 
using namespace std;
extern string AKAstrings[];
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAKA *FormAKA;
__fastcall TFormAKA::TFormAKA(TComponent* Owner) : TForm(Owner)
{
freopen("c:\\injection.log", "a", stdout); printf("<__fastcallTFormAKA::TFormAKA(TComponent*Owner):TForm(Owner) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
freopen("c:\\injection.log", "a", stdout); printf("</__fastcallTFormAKA::TFormAKA(TComponent*Owner):TForm(Owner) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::FormActivate(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::FormActivate(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    if(SaveDialogAKA->InitialDir.IsEmpty())
        SaveDialogAKA->InitialDir = GetCurrentDir();
    if(OpenDialogAKA->InitialDir.IsEmpty())
        OpenDialogAKA->InitialDir = GetCurrentDir();
    LastScreenIndex = RadioGroup->ItemIndex; 
    TGridOptions OurOptions;
    OurOptions << goEditing << goFixedVertLine << goFixedHorzLine << goColSizing << goTabs;
    StringGrid1->Options = OurOptions;
    StringGrid1->ColWidths[0] = 120;
    StringGrid1->ColWidths[1] = 100;
    StringGrid1->ColWidths[2] = 80;
    MapAKACopy = Global::MapAKA;
    AKAseparate(Sender); 
    Global::MapAKA.clear(); 
    Global::Mapgetvar.clear();
    Global::Mapputvar.clear();
    Global::Mapreadvar.clear();
    Global::Mapdeclvar.clear();
    Global::Mapdeclpar.clear();
    Global::Mapdeclobs.clear();
    Global::BuildFlag = CRHM::BUILD; 
    for(int ii = 0; ii < Global::OurModulesList->Count; ii++)
        ((ClassModule*) Global::OurModulesList->Objects[ii])->decl();
    Global::BuildFlag = CRHM::DECL; 
    ListBox1->Clear();
    for(int ii = 0 ; ii < Global::OurModulesList->Count; ii++ )
    {
        ListBox1->Items->AddObject(Global::OurModulesList->Strings[ii],
                                   (TObject *) Global::OurModulesList->Objects[ii]);
    }
    RadioGroupClick(Sender);
    selectCol = REN;
    selectRow = 2;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::FormActivate(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::DrawGridObs(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::DrawGridObs(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    Mapstr::iterator itMap, pos;
    pair<Mapstr::iterator, Mapstr::iterator> rangeO;
    String S, S2, SS;
    int There, uu;
    ClearGrid(Sender);
    StringGrid1->FixedCols = 0;
    StringGrid1->FixedRows = 0;
    StringGrid1->ColCount = 4;
    StringGrid1->RowCount = 2;
    StringGrid1->Cells[0][0] = "Module";
    StringGrid1->Cells[1][1] = "Original Name";
    StringGrid1->Cells[2][1] = "units";
    StringGrid1->Cells[REN][1] = "Renamed";
    for(int ii = 0 ; ii < ListBox1->Items->Count; ++ii)
    {
        if(ListBox1->Selected[ii] == false  && ListBox1->SelCount != 0)
            continue;
        S = ListBox1->Items->Strings[ii]; 
        rangeO = Global::Mapdeclobs.equal_range(S);
        for(itMap = rangeO.first; itMap != rangeO.second; itMap++)
        {
            SS = itMap->second.first; 
            StringGrid1->RowCount = StringGrid1->RowCount + 1;
            StringGrid1->Rows[StringGrid1->RowCount-1]->Clear();
            StringGrid1->Cells[0][StringGrid1->RowCount-1] = S;
            StringGrid1->Cells[1][StringGrid1->RowCount-1] = SS;
            StringGrid1->Cells[2][StringGrid1->RowCount-1] = GetUnits(S, SS);
        } 
        rangeO = Global::Mapreadvar.equal_range(S);
        for(itMap = rangeO.first; itMap != rangeO.second; itMap++)
        {
            SS = itMap->second.first; 
            int rr = StringGrid1->Cols[1]->IndexOf(SS); 
            if(rr == -1)   
            {
                StringGrid1->RowCount = StringGrid1->RowCount + 1;
                StringGrid1->Rows[StringGrid1->RowCount-1]->Clear();
                StringGrid1->Cells[0][StringGrid1->RowCount-1] = "obs";
                StringGrid1->Cells[1][StringGrid1->RowCount-1] = SS;
                StringGrid1->Cells[2][StringGrid1->RowCount-1] = GetUnits(S, SS);
                rr = StringGrid1->RowCount-1;
            }
            There = StringGrid1->Rows[0]->IndexOf(S.c_str());
            if(There < 0)  
            {
                ++StringGrid1->ColCount;
                There = StringGrid1->ColCount-1;
                StringGrid1->Cells[There][0] = S; 
            }
            StringGrid1->Cells[There][rr] = SS;
        } 
    } 
    if(StringGrid1->ColCount > REN)
        StringGrid1->FixedCols = REN;
    if(StringGrid1->RowCount > 2)
        StringGrid1->FixedRows = 2;
    Memo->Lines->Clear();
    if(!MapAKAObs.empty())
    {
        Mapstr2::iterator it;
        for (it = MapAKAObs.begin(); it !=  MapAKAObs.end(); ++it)
        {
            string Obs = (*it).first + ' ' + (*it).second;
            TAKA Type = Digest(it, module, name, Newname, source);
            if(source != "obs" && Newname[Newname.length()-1] != '#')
                Newname += '#';
            int rr, cc2;
            switch (Type)
            {
            case OBSR :
            case OBSF :
                cc2 = StringGrid1->Rows[0]->IndexOf(module.c_str()); 
                if(cc2 == -1) 
                    break;
                rr = MatchMod_Name("obs", name.c_str(), 1); 
                if(rr == -1)  
                {
                    StringGrid1->RowCount = StringGrid1->RowCount + 1;
                    rr = StringGrid1->RowCount-1;
                    StringGrid1->Rows[rr]->Clear();
                    StringGrid1->Cells[0][rr] = "obs";
                    StringGrid1->Cells[1][rr] = name.c_str();
                }
                StringGrid1->Cells[cc2][rr] = String("[ ") + name.c_str() + " -> " + Newname.c_str() + " ]"; 
                if(Newname[Newname.size()-1] == '#')
                    rr = MatchMod_Name(module.c_str(), Newname.c_str(), 1); 
                else
                    rr = MatchMod_Name("obs", Newname.c_str(), 1); 
                int rr3 = MatchMod_Name(source.c_str(), Newname.c_str(), 1); 
                if(rr3 == -1)
                    rr3 = MatchMod_Name(source.c_str(), Newname.c_str(), 3); 
                if(rr3 > -1)
                    StringGrid1->Cells[cc2][rr3] = String("--> ") + Newname.c_str(); 
                Memo->Lines->Add(Obs.c_str());
                break;
            } 
        } 
    } 
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::DrawGridObs(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::DrawGridVar(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::DrawGridVar(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    Mapstr::iterator itMap, pos;
    pair<Mapstr::iterator, Mapstr::iterator> rangeO;
    pair<Mapstr::iterator, Mapstr::iterator> rangeI;
    String S, S1, S2, SS;
    int There;
    ClassVar* thisVar;
    ClearGrid(Sender);
    StringGrid1->FixedCols = 0;
    StringGrid1->FixedRows = 0;
    StringGrid1->ColCount = 4;
    StringGrid1->RowCount = 2;
    StringGrid1->Cells[0][0] = "Module";
    StringGrid1->Cells[1][1] = "Original Name";
    StringGrid1->Cells[2][1] = "units";
    StringGrid1->Cells[REN][1] = "select";
    for(int ii = 0 ; ii < ListBox1->Items->Count; ++ii)
    {
        if(ListBox1->Selected[ii] == false && ListBox1->SelCount != 0)
            continue;
        S = ListBox1->Items->Strings[ii]; 
        rangeO = Global::Mapdeclvar.equal_range(S);
        for(itMap = rangeO.first; itMap != rangeO.second; itMap++)
        {
            SS = itMap->second.first; 
            int Pound = SS.Pos("#"); 
            if(Pound > 0)
                continue;
            pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
                          value_equals<KeyType2,  KeyType2, Pairstr>(SS)); 
            if(pos == Global::Mapreadvar.end())  
            {
                thisVar = GetVar(S, SS);
                if(thisVar == NULL || thisVar->visibility != CRHM::USUAL) 
                    continue;
                int rr = StringGrid1->Cols[1]->IndexOf(SS); 
                if(rr == -1)
                {
                    StringGrid1->RowCount = StringGrid1->RowCount + 1;
                    StringGrid1->Rows[StringGrid1->RowCount-1]->Clear();
                    StringGrid1->Cells[0][StringGrid1->RowCount-1] = S;
                    StringGrid1->Cells[1][StringGrid1->RowCount-1] = SS;
                    StringGrid1->Cells[2][StringGrid1->RowCount-1] = GetUnits(S, SS);
                }
            } 
        } 
    } 
    for(int ii = 0 ; ii < ListBox1->Items->Count; ++ii)
    {
        if(ListBox1->Selected[ii] == false && ListBox1->SelCount != 0)
            continue;
        S = ListBox1->Items->Strings[ii]; 
        rangeI = Global::Mapgetvar.equal_range(S);
        for(itMap = rangeI.first; itMap != rangeI.second; itMap++)
        {
            SS = itMap->second.first;
            int jj = SS.Pos(" ");
            S1 = SS.SubString(1, jj-1);  
            S2 = SS.SubString(jj+1, SS.Length() - jj); 
            int rr = StringGrid1->Cols[1]->IndexOf(S2); 
            There = StringGrid1->Rows[0]->IndexOf(S.c_str());
            if(There < 0 && rr > -1)  
            {
                ++StringGrid1->ColCount;
                There = StringGrid1->ColCount-1;
                StringGrid1->Cells[There][0] = S; 
            }
            if(rr > -1)   
            {
                StringGrid1->Cells[There][rr] = S2;
            }
        }
        rangeI = Global::Mapputvar.equal_range(S);
        for(itMap = rangeI.first; itMap != rangeI.second; itMap++)
        {
            SS = itMap->second.first;
            int jj = SS.Pos(" ");
            S1 = SS.SubString(1, jj-1);  
            S2 = SS.SubString(jj+1, SS.Length() - jj); 
            int rr = StringGrid1->Cols[1]->IndexOf(S2); 
            There = StringGrid1->Rows[0]->IndexOf(S.c_str());
            if(There < 0)  
            {
                ++StringGrid1->ColCount;
                There = StringGrid1->ColCount-1;
                StringGrid1->Cells[There][0] = S; 
            }
            if(rr > -1)   
            {
                StringGrid1->Cells[There][rr] = S2; 
            }
        } 
    } 
    if(StringGrid1->ColCount > REN)
        StringGrid1->FixedCols = REN;
    if(StringGrid1->RowCount > 2)
        StringGrid1->FixedRows = 2;
    Memo->Lines->Clear();
    if(!MapAKAVar.empty())
    {
        Mapstr2::iterator it;
        for (it = MapAKAVar.begin(); it !=  MapAKAVar.end(); ++it)
        {
            string Var = (*it).first + ' ' + (*it).second;
            TAKA Type = Digest(it, module, name, Newname, source);
            int indx, indx2, cc2;
            switch (Type)
            {
            case VARG :
                cc2 = StringGrid1->Rows[0]->IndexOf(module.c_str()); 
                if(cc2 == -1) 
                    break;
                indx2 = StringGrid1->Rows[0]->IndexOf(module.c_str()); 
                indx = StringGrid1->Cols[1]->IndexOf(name.c_str()); 
                int indx3 = MatchMod_Name(source.c_str(), Newname.c_str(), 1); 
                if(indx > -1 && indx2 > -1 && indx3 > -1)  
                {
                    StringGrid1->Cells[indx2][indx] = String("[ ") + name.c_str() + " -> " + Newname.c_str() + " ]";
                    if(indx != indx3)
                        StringGrid1->Cells[indx2][indx3] = String("--> ") + Newname.c_str();
                }
                Memo->Lines->Add(Var.c_str());
                break;
            } 
        } 
    } 
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::DrawGridVar(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::ListBox1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::ListBox1Click(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    RadioGroupClick(Sender);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::ListBox1Click(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::StringGrid1SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::StringGrid1SelectCell(TObject*Sender,intACol,intARow,bool&CanSelect) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    int There;
    if(ACol == REN && ARow > 1 && ARow < StringGrid1->RowCount)
    {
        CanSelect = true;
        selectCol = ACol;
        selectRow = ARow;
    }
    else
    {
        CanSelect = false;
        if(ACol > REN && ACol < StringGrid1->ColCount && ARow > 1 && ARow < StringGrid1->RowCount && !StringGrid1->Cells[ACol][ARow].IsEmpty())
            if(StringGrid1->Cells[ACol][ARow][1] == '-' )
            {
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::StringGrid1SelectCell(TObject*Sender,intACol,intARow,bool&CanSelect) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return;}
            }
        if(!StringGrid1->Cells[ACol][ARow].IsEmpty())
            if(StringGrid1->Cells[ACol][ARow][1] != '[' && !StringGrid1->Cells[REN][ARow].IsEmpty())  
            {
                if(StringGrid1->Cells[ACol][ARow] != StringGrid1->Cells[REN][ARow])
                {
                    StringGrid1->Cells[ACol][ARow] = String("[ ") + StringGrid1->Cells[ACol][ARow] + " -> " + StringGrid1->Cells[REN][ARow] + " ]";
                    StringGrid1->Objects[ACol][ARow] = (TObject*) ARow; 
                }
            }
            else
            {
                StringGrid1->Cells[ACol][ARow] = StringGrid1->Cells[1][ARow];
                StringGrid1->Objects[ACol][ARow] = (TObject*) -ARow; 
            }
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::StringGrid1SelectCell(TObject*Sender,intACol,intARow,bool&CanSelect) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::StringGrid1KeyPress(TObject *Sender, char &Key)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::StringGrid1KeyPress(TObject*Sender,char&Key) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    if(Key == VK_RETURN)     
    {
        Key = 0;
        StringGrid1->Cells[selectCol][selectRow] = LocalValue;
    }
    else if(Key == VK_ESCAPE)
    {
        Key = 0;
        StringGrid1->Cells[selectCol][selectRow] = LastValue;
    }
    else   
    {
        if(StringGrid1->Cells[0][selectRow] != "obs")
            Key = 0;
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::StringGrid1KeyPress(TObject*Sender,char&Key) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::StringGrid1SetEditText(TObject *Sender, int ACol, int ARow, const AnsiString Value)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::StringGrid1SetEditText(TObject*Sender,intACol,intARow,constAnsiStringValue) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    selectCol = ACol;
    selectRow = ARow;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::StringGrid1SetEditText(TObject*Sender,intACol,intARow,constAnsiStringValue) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::StringGrid1GetEditText(TObject *Sender, int ACol, int ARow, AnsiString &Value)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::StringGrid1GetEditText(TObject*Sender,intACol,intARow,AnsiString&Value) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    LastValue = Value;
    LocalValue = Value;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::StringGrid1GetEditText(TObject*Sender,intACol,intARow,AnsiString&Value) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::Open1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::Open1Click(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    OpenDialogAKA->Filter = "Macro Files (*.aka)|*.aka";
    OpenDialogAKA->DefaultExt = "aka";
    OpenDialogAKA->Title = "Open AKA File";
    if(OpenDialogAKA->Execute())
    {
        OpenDialogAKA->InitialDir = ExtractFilePath(OpenDialogAKA->FileName);
        if(OpenDialogAKA->InitialDir.IsEmpty())
            OpenDialogAKA->InitialDir = GetCurrentDir();
        SaveDialogAKA->InitialDir = OpenDialogAKA->InitialDir; 
        Memo->Lines->Clear();
        Memo->Lines->LoadFromFile(OpenDialogAKA->FileName);
        ReadMemo(Sender);
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::Open1Click(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::SaveClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::SaveClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    if(!SaveDialogAKA->FileName.IsEmpty())
        Memo->Lines->SaveToFile(SaveDialogAKA->FileName);
    else
        SaveAsClick(Sender);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::SaveClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::SaveAsClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::SaveAsClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    SaveDialogAKA->Title = "Save As";
    SaveDialogAKA->DefaultExt = "aka";
    SaveDialogAKA->Filter = "Macro Files (*.aka)|*.aka";
    if(SaveDialogAKA->Execute())
    {
        SaveDialogAKA->InitialDir = ExtractFilePath(SaveDialogAKA->FileName);
        if(SaveDialogAKA->InitialDir.IsEmpty())
            SaveDialogAKA->InitialDir = GetCurrentDir();
        Memo->Lines->SaveToFile(SaveDialogAKA->FileName);
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::SaveAsClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::ExitClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::ExitClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    Close();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::ExitClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::RadioGroupClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::RadioGroupClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    switch (RadioGroup->ItemIndex)
    {
    case 0 :
        DrawGridVar(Sender);
        break;
    case 1 :
        DrawGridObs(Sender);
        break;
    }
    selectCol = 0;
    selectRow = 0; 
    LastScreenIndex = RadioGroup->ItemIndex;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::RadioGroupClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::FormDeactivate(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::FormDeactivate(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    AKAcombine(Sender);
    Global::MapAKA = MapAKACopy;
    MapAKACopy.clear();
    Main->InitModules(Sender);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::FormDeactivate(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
TAKA TFormAKA::Digest(Mapstr2::iterator it, string & module, string & name, string & Newname, string & source)
{
freopen("c:\\injection.log", "a", stdout); printf("<TAKATFormAKA::Digest(Mapstr2::iteratorit,string&module,string&name,string&Newname,string&source) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    string Var = (*it).first; 
    string::size_type idx = Var.find(' ');
    string type = Var.substr(0, idx);
    Var = Var.substr(idx+1);
    idx = Var.find(' ');
    module = Var.substr(0, idx);
    name = Var.substr(idx+1);
    TAKA Type = AKAtype(type);
    if(Type == VARG || Type == OBSR || Type == OBSF)
    {
        Var = (*it).second; 
        idx = Var.find(' ');
        Newname = Var.substr(0, idx);
        source = Var.substr(idx+1);
    }
    else
    {
        Newname =  (*it).second;
        source = "";
    }
{freopen("c:\\injection.log", "a", stdout); printf("</TAKATFormAKA::Digest(Mapstr2::iteratorit,string&module,string&name,string&Newname,string&source) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return Type;}
freopen("c:\\injection.log", "a", stdout); printf("</TAKATFormAKA::Digest(Mapstr2::iteratorit,string&module,string&name,string&Newname,string&source) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::SaveScreenCode(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::SaveScreenCode(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    int OnRow, InCol;
    switch (LastScreenIndex)
    {
    case 0 : 
        AKAModuleDelete(MapAKAVar);
        for(int rr = ROW2; rr < StringGrid1->RowCount; ++rr)
        {
            for(int cc = 4; cc < StringGrid1->ColCount; ++cc)
            {
                if(!StringGrid1->Cells[cc][rr].IsEmpty() && StringGrid1->Cells[cc][rr][1] == '-')  
                {
                    StringGrid1->Cells[cc][rr] = "";
                    continue;
                }
                if(StringGrid1->Cells[cc][rr].IsEmpty() || StringGrid1->Cells[cc][rr][1] != '[') 
                    continue;
                name = StringGrid1->Cells[1][rr].c_str();
                Newname = StringGrid1->Cells[cc][rr].c_str();
                string::size_type idx = Newname.find('>');
                string::size_type idx2 = Newname.find(" ]");
                Newname = Newname.substr(idx+2, idx2 - idx-2);
                module =  StringGrid1->Cells[cc][0].c_str();
                int Indx = StringGrid1->Cols[1]->IndexOf(Newname.c_str()); 
                if(Indx > -1)
                    source = StringGrid1->Cells[0][Indx].c_str();
                if(name != Newname || module != source)
                    MapAKAVar.insert(make_pair(AKAstrings[VARG] + " " + module + " " + name, Newname + ' ' + source));
            } 
        } 
        DrawGridVar(Sender);
        break;
    case 1 : 
        AKAModuleDelete(MapAKAObs);
        for(int rr = ROW2; rr < StringGrid1->RowCount; ++rr)
        {
            for(int cc = 4; cc < StringGrid1->ColCount; ++cc)
            {
                if(!StringGrid1->Cells[cc][rr].IsEmpty() && StringGrid1->Cells[cc][rr][1] == '-')  
                {
                    StringGrid1->Cells[cc][rr] = "";
                    continue;
                }
                if(StringGrid1->Cells[cc][rr].IsEmpty() || StringGrid1->Cells[cc][rr][1] != '[') 
                    continue;
                name = StringGrid1->Cells[1][rr].c_str();
                Newname = StringGrid1->Cells[cc][rr].c_str();
                string::size_type idx = Newname.find('>');
                string::size_type idx2 = Newname.find(" ]");
                Newname = Newname.substr(idx+2, idx2 - idx-2);
                module =  StringGrid1->Cells[cc][0].c_str();
                int Indx = MatchMod_Name(module.c_str(), Newname.c_str(), 1); 
                if(Indx == -1)
                    Indx = MatchSimple_Name(Newname.c_str(), 1); 
                if(Indx == -1 && Newname[Newname.length()-1] == '#') 
                    Indx = StringGrid1->Cols[3]->IndexOf(Newname.c_str()); 
                if(Indx > -1) 
                    source = StringGrid1->Cells[0][Indx].c_str();
                else
                {
                    Indx = MatchMod_Name(module.c_str(), Newname.c_str(), 1); 
                    if(Indx == -1)
                        Indx = MatchMod_Name(module.c_str(), Newname.c_str(), 2);   
                    if(Indx > -1) 
                        source = StringGrid1->Cells[0][Indx].c_str();
                    else 
                        source = "obs";
                }
                if(name != Newname || module != source && source != "obs")
                    MapAKAObs.insert(make_pair(AKAstrings[OBSR] + " " + module + " " + name, Newname + ' ' + source));
            } 
        } 
        DrawGridObs(Sender);
        break;
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::SaveScreenCode(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::Save1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::Save1Click(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    SaveScreenCode(Sender);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::Save1Click(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::VoidClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::VoidClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    RadioGroupClick(Sender);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::VoidClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::RemoveUnusedClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::RemoveUnusedClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    if(RadioGroup->ItemIndex != 1) 
        for(int rr = StringGrid1->RowCount - 1; rr > 1 ; --rr)
        {
            bool Used = false;
            for (int cc = 4; cc < StringGrid1->ColCount; ++cc)
            {
                if(!StringGrid1->Rows[rr]->Strings[cc].IsEmpty())
                {
                    Used = true;
                    break;
                }
            }
            if(!Used)
                DeleteRow(rr);
        }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::RemoveUnusedClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::DeleteRow(int Row)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::DeleteRow(intRow) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    for(int rr = Row; rr < StringGrid1->RowCount-1; ++rr)
        StringGrid1->Rows[rr] = StringGrid1->Rows[rr+1];
    StringGrid1->RowCount = StringGrid1->RowCount - 1;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::DeleteRow(intRow) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::AKAseparate(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::AKAseparate(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    MapAKAVar.clear();
    MapAKAPar.clear();
    MapAKAObs.clear();
    if(!MapAKACopy.empty())   
    {
        Mapstr2::iterator it;
        for (it = MapAKACopy.begin(); it !=  MapAKACopy.end(); ++it)
        {
            TAKA Type = Digest(it, module, name, Newname, source);
            switch (Type)
            {
            case VARG :
                MapAKAVar.insert(make_pair(it->first, it->second));
                break;
            case OBSR :
            case OBSF :
                MapAKAObs.insert(make_pair(it->first, it->second));
                break;
            } 
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::AKAseparate(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::AKAcombine(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::AKAcombine(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    Mapstr2::iterator it;
    MapAKACopy.clear();
    if(!MapAKAVar.empty()) 
        for (it = MapAKAVar.begin(); it !=  MapAKAVar.end(); ++it)
            MapAKACopy.insert(make_pair(it->first, it->second));
    if(!MapAKAPar.empty()) 
        for (it = MapAKAPar.begin(); it !=  MapAKAPar.end(); ++it)
            MapAKACopy.insert(make_pair(it->first, it->second));
    if(!MapAKAObs.empty()) 
        for (it = MapAKAObs.begin(); it !=  MapAKAObs.end(); ++it)
            MapAKACopy.insert(make_pair(it->first, it->second));
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::AKAcombine(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::EscapeClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::EscapeClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    AKAseparate(Sender);
    Close();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::EscapeClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::ClearGrid(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::ClearGrid(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    for(int rr = 0; rr < StringGrid1->RowCount; ++rr)
        for(int cc = 0; cc < StringGrid1->ColCount; ++cc)
        {
            StringGrid1->Cells[cc][rr] = "";
            StringGrid1->Objects[cc][rr] = NULL;
        }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::ClearGrid(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::StringGrid1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::StringGrid1MouseDown(TObject*Sender,TMouseButtonButton,TShiftStateShift,intX,intY) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    if(selectRow < ROW2)
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::StringGrid1MouseDown(TObject*Sender,TMouseButtonButton,TShiftStateShift,intX,intY) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return;}
    int selectCol1, selectRow1; 
    StringGrid1->MouseToCell(X, Y, selectCol1, selectRow1);
    if(Button == mbRight && selectCol1 > REN)
    {
        if(StringGrid1->Cells[selectCol1][selectRow1][1] == '[')  
        {
            int Pos = StringGrid1->Cells[selectCol1][selectRow1].Pos(" ->");
            StringGrid1->Cells[selectCol1][selectRow1] = StringGrid1->Cells[selectCol1][selectRow1].SubString(3, Pos-3);
        }
        if(StringGrid1->Cells[REN][selectRow].IsEmpty())
            if(selectRow1 != selectRow) 
                StringGrid1->Cells[selectCol1][selectRow1] = String("[ ") + StringGrid1->Cells[selectCol1][selectRow1] + " -> " + StringGrid1->Cells[1][selectRow] + " ]";
            else
                StringGrid1->Cells[selectCol1][selectRow1] = StringGrid1->Cells[1][selectRow];
        else  
        {
            if(StringGrid1->Cells[selectCol1][selectRow1] != StringGrid1->Cells[REN][selectRow])
            {
                if(StringGrid1->Cells[1][selectRow][StringGrid1->Cells[1][selectRow].Length()] == '#' && StringGrid1->Cells[REN][selectRow][StringGrid1->Cells[REN][selectRow].Length()] != '#')
                    StringGrid1->Cells[REN][selectRow] = StringGrid1->Cells[REN][selectRow] + '#';
                if(StringGrid1->Cells[selectCol1][selectRow1][1] != '-')
                    StringGrid1->Cells[selectCol1][selectRow1] = String("[ ") + StringGrid1->Cells[selectCol1][selectRow1] + " -> " + StringGrid1->Cells[REN][selectRow] + " ]";
            }
        }
        if(selectCol == 3)
            StringGrid1->Objects[selectCol1][selectRow1] = (TObject*) selectRow; 
        else
            StringGrid1->Objects[selectCol1][selectRow1] = (TObject*) -selectRow; 
    }
    else if(Button == mbRight && selectCol1 == REN && !StringGrid1->Cells[REN][selectRow1].IsEmpty())
    {
        int rr = StringGrid1->Cols[1]->IndexOf(StringGrid1->Cells[REN][selectRow1]); 
        if(rr == -1)   
        {
            StringGrid1->RowCount = StringGrid1->RowCount + 1;
            StringGrid1->Rows[StringGrid1->RowCount-1]->Clear();
            StringGrid1->Cells[1][StringGrid1->RowCount-1] = StringGrid1->Cells[REN][selectRow1];
            StringGrid1->Cells[0][StringGrid1->RowCount-1] = "obs";
            rr = StringGrid1->RowCount-1;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::StringGrid1MouseDown(TObject*Sender,TMouseButtonButton,TShiftStateShift,intX,intY) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::ReadMemo(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::ReadMemo(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    istringstream instr;
    string type;
    Mapstr2 MapAKALocal;
    TAKA Type;
    for (int ii = 0; ii < Memo->Lines->Count; ++ii)
    {
        if(Memo->Lines->Strings[ii].IsEmpty())
            continue;
        instr.clear(); 
        instr.str(Memo->Lines->Strings[ii].c_str());
        instr >> type >> module >> name >> Newname;
        Type = AKAtype(type);
        if(Type == VARG || Type == OBSR || Type == OBSF)
        {
            instr >> source;
            Newname += ' ' + source;
        }
        if(instr.fail() || Type == AKAERROR)
        {
            Application->MessageBox((OpenDialogAKA->FileName + " on line " + String(ii+1)).c_str(), "Faulty data", MB_OK);
            break;
        }
        if(Type != AKAERROR)
        {
            Pairstr2 Item = Pairstr2(type + " " + module + " " + name, Newname);
            MapAKALocal.insert(Item);
        }
    }
    switch (RadioGroup->ItemIndex)
    {
    case 0 :
        MapAKAVar.clear();
        MapAKAVar = MapAKALocal;
        DrawGridVar(Sender);
        break;
    case 1 :
        MapAKAObs.clear();
        MapAKAObs = MapAKALocal;
        DrawGridObs(Sender);
        break;
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::ReadMemo(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::MemoDblClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::MemoDblClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    ReadMemo(Sender);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::MemoDblClick(TObject*Sender) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
bool __fastcall TFormAKA::OriginalVar(String module, String name)
{
freopen("c:\\injection.log", "a", stdout); printf("<bool__fastcallTFormAKA::OriginalVar(Stringmodule,Stringname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    Mapstr::iterator itMap, pos;
    pair<Mapstr::iterator, Mapstr::iterator> rangeI;
    String SS, S2;
    rangeI = Global::Mapgetvar.equal_range(module);
    for(itMap = rangeI.first; itMap != rangeI.second; itMap++)
    {
        SS = itMap->second.first;
        int jj = SS.Pos(" ");
        S2 = SS.SubString(jj+1, SS.Length() - jj); 
        if(S2 == name)
{freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTFormAKA::OriginalVar(Stringmodule,Stringname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return true;}
    }
    rangeI = Global::Mapputvar.equal_range(module);
    for(itMap = rangeI.first; itMap != rangeI.second; itMap++)
    {
        SS = itMap->second.first;
        int jj = SS.Pos(" ");
        S2 = SS.SubString(jj+1, SS.Length() - jj); 
        if(S2 == name)
{freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTFormAKA::OriginalVar(Stringmodule,Stringname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return true;}
    }
{freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTFormAKA::OriginalVar(Stringmodule,Stringname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return false;}
freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTFormAKA::OriginalVar(Stringmodule,Stringname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
bool __fastcall TFormAKA::OriginalObs(String module, String name)
{
freopen("c:\\injection.log", "a", stdout); printf("<bool__fastcallTFormAKA::OriginalObs(Stringmodule,Stringname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    Mapstr::iterator itMap, pos;
    pair<Mapstr::iterator, Mapstr::iterator> rangeI;
    String SS, S2;
    rangeI = Global::Mapreadvar.equal_range(module);
    for(itMap = rangeI.first; itMap != rangeI.second; itMap++)
    {
        SS = itMap->second.first;
        int jj = SS.Pos(" ");
        S2 = SS.SubString(jj+1, SS.Length() - jj); 
        if(S2 == name)
{freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTFormAKA::OriginalObs(Stringmodule,Stringname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return true;}
    }
{freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTFormAKA::OriginalObs(Stringmodule,Stringname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return false;}
freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTFormAKA::OriginalObs(Stringmodule,Stringname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
int __fastcall TFormAKA::MatchMod_Name(String module, String name, int Col)  
{
freopen("c:\\injection.log", "a", stdout); printf("<int__fastcallTFormAKA::MatchMod_Name(Stringmodule,Stringname,intCol) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    int Row;
    for(Row = 2; Row < StringGrid1->RowCount; ++Row) 
        if(module == StringGrid1->Cells[0][Row] && name == StringGrid1->Cells[Col][Row])
{freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTFormAKA::MatchMod_Name(Stringmodule,Stringname,intCol) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return Row;}
{freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTFormAKA::MatchMod_Name(Stringmodule,Stringname,intCol) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return -1;}
freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTFormAKA::MatchMod_Name(Stringmodule,Stringname,intCol) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
int __fastcall TFormAKA::MatchSimple_Name(String name, int Col)  
{
freopen("c:\\injection.log", "a", stdout); printf("<int__fastcallTFormAKA::MatchSimple_Name(Stringname,intCol) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    int Row;
    for(Row = 2; Row < StringGrid1->RowCount; ++Row) 
        if(!isGroup(StringGrid1->Cells[0][Row].c_str()) && name == StringGrid1->Cells[Col][Row])
{freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTFormAKA::MatchSimple_Name(Stringname,intCol) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return Row;}
{freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTFormAKA::MatchSimple_Name(Stringname,intCol) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return -1;}
freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTFormAKA::MatchSimple_Name(Stringname,intCol) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
bool __fastcall TFormAKA::isGroup(string name)
{
freopen("c:\\injection.log", "a", stdout); printf("<bool__fastcallTFormAKA::isGroup(stringname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    int Indx = Global::OurModulesList->IndexOf(name.c_str());
    if(Indx == -1)
{freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTFormAKA::isGroup(stringname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return false;}
    ClassModule *thisMod = (ClassModule *) Global::OurModulesList->Objects[Indx];
{freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTFormAKA::isGroup(stringname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return (thisMod->GroupCnt > 0);}
freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTFormAKA::isGroup(stringname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
bool __fastcall TFormAKA::isSame_decl(string name, string Newname)
{
freopen("c:\\injection.log", "a", stdout); printf("<bool__fastcallTFormAKA::isSame_decl(stringname,stringNewname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    string s;
    if(name.size() > Newname.size())
        s = name.substr(Newname.size());
    else
        s = Newname.substr(name.size());
    if(s == "#")
{freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTFormAKA::isSame_decl(stringname,stringNewname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return true;}
    else
{freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTFormAKA::isSame_decl(stringname,stringNewname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return false;}
freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTFormAKA::isSame_decl(stringname,stringNewname) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
String  __fastcall TFormAKA::GetUnits(String S, String SS)
{
freopen("c:\\injection.log", "a", stdout); printf("<String__fastcallTFormAKA::GetUnits(StringS,StringSS) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    string s = string(S.c_str()) + ' ' + SS.c_str();
    if((itVar = Global::MapVars.find(s)) != Global::MapVars.end())
    {
        ClassVar *thisVar = ((*itVar).second);
{freopen("c:\\injection.log", "a", stdout); printf("</String__fastcallTFormAKA::GetUnits(StringS,StringSS) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return thisVar->units.c_str();}
    }
    else
{freopen("c:\\injection.log", "a", stdout); printf("</String__fastcallTFormAKA::GetUnits(StringS,StringSS) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return "";}
freopen("c:\\injection.log", "a", stdout); printf("</String__fastcallTFormAKA::GetUnits(StringS,StringSS) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
ClassVar*  __fastcall TFormAKA::GetVar(String S, String SS)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassVar*__fastcallTFormAKA::GetVar(StringS,StringSS) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    string s = string(S.c_str()) + ' ' + SS.c_str();
    if((itVar = Global::MapVars.find(s)) != Global::MapVars.end())
{freopen("c:\\injection.log", "a", stdout); printf("</ClassVar*__fastcallTFormAKA::GetVar(StringS,StringSS) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return ((*itVar).second);}
    else
{freopen("c:\\injection.log", "a", stdout); printf("</ClassVar*__fastcallTFormAKA::GetVar(StringS,StringSS) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);return NULL;}
freopen("c:\\injection.log", "a", stdout); printf("</ClassVar*__fastcallTFormAKA::GetVar(StringS,StringSS) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormAKA::AKAModuleDelete(Mapstr2 &MapAKAany)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormAKA::AKAModuleDelete(Mapstr2&MapAKAany) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
    if(!MapAKAany.empty())   
    {
        Mapstr2::iterator it;
        for (it = MapAKAany.begin(); it !=  MapAKAany.end(); )
        {
            string Var = (*it).first; 
            string::size_type idx = Var.find(' ');
            idx = Var.find(' ', idx);
            Var = Var.substr(idx+1);
            idx = Var.find(' ', idx);
            string module = Var.substr(0, idx);
            bool erased = false;
            for(int ii = 0 ; ii < ListBox1->Items->Count; ++ii)
            {
                if(ListBox1->Selected[ii] == false  && ListBox1->SelCount != 0)
                    continue;
                if(module == ListBox1->Items->Strings[ii].c_str())
                {
                    MapAKAany.erase(it++);
                    erased = true;
                    break;
                }
            }
            if(!erased)
                ++it;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormAKA::AKAModuleDelete(Mapstr2&MapAKAany) @@@ AKAform.cpp_nocom>\n"); fclose(stdout);
}
