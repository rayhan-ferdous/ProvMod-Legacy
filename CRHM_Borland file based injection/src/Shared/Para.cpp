#include <vcl.h>
#pragma hdrstop
#include "GlobalCommon.h"
#include "CRHMmain.h"
#include "DefCRHMGlobal.h"
#include "ClassModule.h"
#include "Para.h"
#include <string>
#include <map>
#include <excpt.h>
#include <fstream>
#include <sstream>
long Dims, Rows, ParaNameWidth;
String LastValue, LocalValue, CurrentModule;
int selectCol, selectRow;
long CurrentDisply = CRHM::USUAL;
string Line, Descrip("Description - to be added");
#pragma package(smart_init)
#pragma resource "*.dfm"
TParameter *Parameter;
String ParameterDisply[] = { "All parameters", "Basic parameters", "Advance parameters", "Private parameters"};
__fastcall TParameter::TParameter(TComponent* Owner): TForm(Owner)
{
freopen("c:\\injection.log", "a", stdout); printf("<__fastcallTParameter::TParameter(TComponent*Owner):TForm(Owner) @@@ Para.cpp_nocom>\n"); fclose(stdout);
freopen("c:\\injection.log", "a", stdout); printf("</__fastcallTParameter::TParameter(TComponent*Owner):TForm(Owner) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TParameter::FormActivate(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTParameter::FormActivate(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *thisPar;
    String S, SS;
    int Indx;
    CurrentDisply = CRHM::USUAL;
    for(int ii = 0; ii<StringGrid1->ColCount; ii++)
        StringGrid1->Cols[ii]->Clear();
    if(Global::OurModulesList->Count <= 0)
    {
        Application->MessageBox("no parameters to edit", "No modules loaded", MB_OK);
        Close();
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::FormActivate(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);return;}
    }
    if(SaveDialogPar->InitialDir.IsEmpty())
        SaveDialogPar->InitialDir = GetCurrentDir();
    if(OpenDialogPar->InitialDir.IsEmpty())
        OpenDialogPar->InitialDir = GetCurrentDir();
    CurrentModule = "";
    ParaNameWidth = 0;
    ExtraCols = 0;
    ListBox1->Sorted = false;
    long Max_Name_Width = 0;
    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++)
    {
        thisPar = (*itPar).second;
        S = thisPar->module.c_str();
        if(S.Length() > 33 && S.Length() > Max_Name_Width) 
            Max_Name_Width = S.Length();
        ParaNameWidth = max<long> (ParaNameWidth, thisPar->param.length());
        Indx = ListBox1->Items->IndexOf(S);
        if(Indx == -1)
            ListBox1->Items->AddObject((*itPar).second->module.c_str(),
                                       (TObject *) 1);
        else
            ListBox1->Items->Objects[Indx] = (TObject *)
                                             ((int) ListBox1->Items->Objects[Indx] + 1);
        if(thisPar->dim > ExtraCols)
            if(thisPar->varType == CRHM::Txt)
            {
                int jj;
                for(jj =0; jj < thisPar->Strings->Count; ++jj)
                    if(thisPar->Strings->Strings[jj] == NULL || thisPar->Strings->Strings[jj] == " ") 
                        break;
                ExtraCols = max<long> (ExtraCols, min<long> (thisPar->dim, jj)); 
            }
            else
                ExtraCols = thisPar->dim;
    } 
    ListBox1->ItemIndex = 0;
    ListBox1->ScrollWidth =  Max_Name_Width*6;
    LabelHelp->Caption = "";
    LabelUnits->Caption = "";
    TGridRect myRect;
    myRect.Left = 0;
    myRect.Right = 0;
    myRect.Top = 0;
    myRect.Bottom = 0;
    StringGrid1->Selection = myRect;
    dirty = false;
    Label5->Caption = ParameterDisply[CurrentDisply];
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::FormActivate(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TParameter::FormClose(TObject *Sender, TCloseAction &Action)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTParameter::FormClose(TObject*Sender,TCloseAction&Action) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *thisPar;
    ClassPar *firstPar;
    TStringList *List = new TStringList;
    int Indx;
    int Warn = 0, Warn2;
    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++)
    {
        thisPar = (*itPar).second;
        bool Equal = true;
        String Sv, Sv2;
        if("Shared" != thisPar->module.c_str())
        {
            String S = thisPar->param.c_str();
            if(S == "HRU_struct" || S == "HRU_group")
                continue;
            Indx = List->IndexOf(S);
            if(Indx < 0)
                List->AddObject(S, (TObject*) (thisPar));
            else
            {
                firstPar = (ClassPar*) List->Objects[Indx];
                if(thisPar->dim != firstPar->dim || thisPar->lay != firstPar->lay)
                    continue;
                if(thisPar->varType != firstPar->varType)
                {
                    Application->MessageBox((String(thisPar->param.c_str()) + " not same type in " + String(firstPar->module.c_str()) + " and " + String(thisPar->module.c_str())).c_str(), "parameters not same type (integer/float)", MB_OK);
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::FormClose(TObject*Sender,TCloseAction&Action) @@@ Para.cpp_nocom>\n"); fclose(stdout);return;}
                }
                if(thisPar->varType == CRHM::Float)
                {
                    Sv = String(thisPar->module.c_str()) + " - ";
                    Sv2 = String(firstPar->module.c_str()) + " - ";
                    for (int ll = 0; ll < thisPar->lay; ++ll)
                    {
                        for (int hh = 0; hh < thisPar->dim; ++hh)
                        {
                            Sv = Sv + FloatToStrF(thisPar->layvalues[ll][hh], ffGeneral, 4, 0) + "\t";
                            Sv2 = Sv2 + FloatToStrF(firstPar->layvalues[ll][hh], ffGeneral, 4, 0) + "\t";
                            if(thisPar->layvalues[ll][hh] != firstPar->layvalues[ll][hh])
                                Equal = false;
                        }
                        Sv = Sv + "\n\n" + Sv2 + "\n";
                    }
                }
                else if(thisPar->varType == CRHM::Int)
                {
                    Sv = String(thisPar->module.c_str()) + " - ";
                    Sv2 = String(firstPar->module.c_str()) + " - ";
                    for (int ll = 0; ll < thisPar->lay; ++ll)
                    {
                        Sv2 = "";
                        for (int hh = 0; hh < thisPar->dim; ++hh)
                        {
                            Sv = Sv + FloatToStrF(thisPar->ilayvalues[ll][hh], ffGeneral, 8, 0) + "\t";
                            Sv2 = Sv2 + FloatToStrF(firstPar->ilayvalues[ll][hh], ffGeneral, 8, 0) + "\t";
                            if(thisPar->ilayvalues[ll][hh] != firstPar->ilayvalues[ll][hh])
                                Equal = false;
                        }
                        Sv = Sv + "\n\n" + Sv2 + "\n";
                    }
                }
                else if(thisPar->varType == CRHM::Txt)
                {
                    Sv = String(thisPar->module.c_str()) + " - ";
                    Sv2 = String(firstPar->module.c_str()) + " - ";
                    for (int hh = 0; hh < thisPar->dim; ++hh)
                    {
                        if(hh >= thisPar->Strings->Count-1)
                            break;
                        Sv = Sv + thisPar->Strings->Strings[hh] + "\t";
                        Sv2 = Sv2 + firstPar->Strings->Strings[hh] + "\t";
                        if(thisPar->Strings->Strings[hh] != firstPar->Strings->Strings[hh])
                            Equal = false;
                    }
                    Sv = Sv + "\n\n" + Sv2 + "\n";
                }
                if(!Equal && Warn != IDCANCEL)
                {
                    String HH =  "parameter: \"" + S + "\" has different values in";
                    String SS = "modules: \"" + String(thisPar->module.c_str()) + "\" and \"" + String(firstPar->module.c_str()) + "\"";
                    SS = SS + "\n\nYES\t - Change parameter values, \nNO\t - but continue checking, \nCancel\t - stop checking.";
                    Warn = Application->MessageBox(SS.c_str(), HH.c_str(), MB_YESNOCANCEL);
                    if(Warn == IDYES)
                    {
                        SS = Sv +
                             "\n\nYes\t - Change parameter to " + String(thisPar->module.c_str())
                             + " value(s), \nNo\t - Change parameter to " + String(firstPar->module.c_str()) + " value(s), \nCancel\t - Do Not change value(s).";
                        HH = "Change parameter \"" + S + "\"";
                        Warn2 = Application->MessageBox(SS.c_str(), HH.c_str(), MB_YESNOCANCEL);
                        if(Warn2 == IDYES)
                        {
                            firstPar->Change(*thisPar);
                        }
                        else if(Warn2 == IDNO)
                        {
                            thisPar->Change(*firstPar);
                        }
                        else
                            Warn = IDYES; 
                    }
                }
            }
        } 
    } 
    delete List;
    if(dirty)
        Update_Main_Dirty();
    ListBox1->Clear();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::FormClose(TObject*Sender,TCloseAction&Action) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TParameter::ListBox1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTParameter::ListBox1Click(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *thisPar;
    int Indx;
    String S, SS;
    TGridOptions OurOptions;
    OurOptions << goEditing << goFixedVertLine << goFixedHorzLine << goColSizing << goTabs;
    StringGrid1->Options = OurOptions;
    for(int ii = 0; ii<StringGrid1->ColCount; ii++)
        StringGrid1->Cols[ii]->Clear();
    Indx = ListBox1->ItemIndex;
    S = ListBox1->Items->Strings[Indx];
    CurrentModule = S;
    LocalParaCount = ((int) ListBox1->Items->Objects[Indx]);
    FindParaCount(Sender, Indx); 
    int jjj = Global::AllModulesList->IndexOf(S.c_str()); 
    ClassModule* thisModule = (ClassModule*) Global::AllModulesList->Objects[jjj];
    Rows = 0;
    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++)
    {
        thisPar = (*itPar).second;
        if(S == thisPar->module.c_str() && ((thisPar->visibility == CurrentDisply) 
                                            || CurrentDisply == 0))
        {
            for(int  jj = 0; jj < thisPar->dim; jj++)
                StringGrid1->Cells[jj+1][0] = IntToStr(jj+1);
            if(Rows == 0)
            {
                FindParaCount(Sender, Indx);
                StringGrid1->ColCount = ExtraCols + 4;
                StringGrid1->RowCount = ParaCount + 3;
                if(LocalParaCount != ParaCount)
                    StringGrid1->RowCount +=1;
                StringGrid1->Cells[0][0] =  "HRU";
                for(int  jj = 0; jj < thisPar->dim; jj++)
                    StringGrid1->Cells[jj+1][0] = IntToStr(jj+1);
                StringGrid1->Cells[ExtraCols + 2][0] =  "Minimum";
                StringGrid1->Cells[ExtraCols + 3][0] =  "Maximum";
                StringGrid1->ColWidths[0] = ParaNameWidth*6;
            }
            Dims = thisPar->dim;
            StringGrid1->RowCount = StringGrid1->RowCount + thisPar->lay - 1;
            for(int nn = 0; nn < thisPar->lay; ++nn)
            {
                Rows++;
                SS = thisPar->param.c_str();
                if(thisPar->lay > 1)
                    SS += "[" + String(nn+1) + "]";
                StringGrid1->Cells[0][Rows+1] = SS;
                StringGrid1->Objects[0][Rows+1] = (TObject*) (thisPar);
                for(int jj = 0; jj < ExtraCols; ++jj)
                {
                    if(jj < Dims)
                    {
                        if(thisPar->varType == CRHM::Float)
                        {
                            StringGrid1->Cells[jj+1][Rows+1] = FloatToStrF(thisPar->layvalues[nn][jj],
                                                               ffGeneral, 4, 0);
                            StringGrid1->Objects[jj+1][Rows+1] = (TObject*) (thisPar->layvalues[nn]);
                        }
                        else if(thisPar->varType == CRHM::Int)
                        {
                            StringGrid1->Cells[jj+1][Rows+1] = FloatToStrF(thisPar->ilayvalues[nn][jj],
                                                               ffGeneral, 8, 0);
                            StringGrid1->Objects[jj+1][Rows+1] = (TObject*) (thisPar->ilayvalues[nn]);
                        }
                        else if(thisPar->varType == CRHM::Txt)
                        {
                            if(thisPar->Strings->Count > 0)
                                StringGrid1->Cells[jj+1][Rows+1] = thisPar->Strings->Strings[jj];
                            else
                                StringGrid1->Cells[jj+1][Rows+1] = "";
                            StringGrid1->Objects[jj+1][Rows+1] = (TObject*) (thisPar->Strings);
                        }
                    }
                    else
                    {
                        StringGrid1->Cells[jj+1][Rows+1] = "";
                        StringGrid1->Objects[jj+1][Rows+1] = (TObject*) NULL;
                    }
                }
                if(nn == 0 && thisPar->varType != CRHM::Txt)
                {
                    int prec = 6;
                    if(thisPar->varType == CRHM::Int || thisPar->varType == CRHM::ReadI)
                        prec = 4;
                    StringGrid1->Cells[ExtraCols + 2][Rows+1] = FloatToStrF(thisPar->minVal,
                            ffGeneral, prec, 0);
                    StringGrid1->Cells[ExtraCols + 3][Rows+1] = FloatToStrF(thisPar->maxVal,
                            ffGeneral, prec, 0);
                }
            } 
        }
    }
    DisplayBasin(Sender, Indx, Rows);
    TGridRect myRect;
    myRect.Left = 0;
    myRect.Right = 0;
    myRect.Top = 0;
    myRect.Bottom = 0;
    StringGrid1->Selection = myRect;
    LabelHelp->Caption = "";
    LabelUnits->Caption = "";
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::ListBox1Click(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TParameter::StringGrid1GetEditText(TObject *Sender,int ACol, int ARow, AnsiString &Value)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTParameter::StringGrid1GetEditText(TObject*Sender,intACol,intARow,AnsiString&Value) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    LastValue = Value;
    LocalValue = Value;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::StringGrid1GetEditText(TObject*Sender,intACol,intARow,AnsiString&Value) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TParameter::StringGrid1SelectCell(TObject *Sender,int ACol, int ARow, bool &CanSelect)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTParameter::StringGrid1SelectCell(TObject*Sender,intACol,intARow,bool&CanSelect) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    ClassPar *thisPar;
    if(ListBox1->ItemIndex == -1)
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::StringGrid1SelectCell(TObject*Sender,intACol,intARow,bool&CanSelect) @@@ Para.cpp_nocom>\n"); fclose(stdout);return;}
    if(ARow > 1 && ARow < Rows + 2)
    {
        thisPar = (ClassPar*) StringGrid1->Objects[0][ARow];
        if(thisPar == NULL)
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::StringGrid1SelectCell(TObject*Sender,intACol,intARow,bool&CanSelect) @@@ Para.cpp_nocom>\n"); fclose(stdout);return;}
        LabelHelp->Caption = thisPar->help.c_str();
        LabelUnits->Caption = thisPar->units.c_str();
        Dims = thisPar->dim;
    }
    if((endBasin > endLocal) && (ARow > endLocal + 2 && ARow < endBasin + 3))
    {
        thisPar = (ClassPar*) StringGrid1->Objects[0] [ARow];
        int Reply = Application->MessageBox("Change to local parameter?",
                                            ("'Shared' parameter " + String(thisPar->param.c_str())).c_str(), IDOK);
        if(Reply == IDOK)    
        {
            ClassPar *newPar = new ClassPar(*thisPar);
            newPar->module = CurrentModule.c_str();
            PairPar Item = PairPar(newPar->module + ' ' + newPar->param, newPar);
            Global::MapPars.insert(Item);
            Close();
        }
    }
    if(ACol < 1 || ACol > Dims || ARow < 2 || ARow > Rows + 2 )
        CanSelect = false;
    else
        CanSelect = true;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::StringGrid1SelectCell(TObject*Sender,intACol,intARow,bool&CanSelect) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TParameter::FileExitClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTParameter::FileExitClick(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    Close();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::FileExitClick(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TParameter::SaveParameters(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTParameter::SaveParameters(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *thisPar;
    String Ext;
    char Text[80];
    Ext = ExtractFileExt(SaveDialogPar->FileName.c_str());
    if(Ext.LowerCase() == ".par")
    {
        Main->RemoveSharedParams(); 
        ParaList = new TStringList;
        ParaList->CaseSensitive = true;
        ParaList->Add(Descrip.c_str());
        ParaList->Add("######");
        for(int bb = 0; bb < 2; ++bb)  
        {
            for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++)
            {
                thisPar = (*itPar).second;
                if(thisPar->param == "HRU_group")
                    continue;
                if(bb == 0 && thisPar->module != "shared")
                    continue;
                if(bb == 1 && thisPar->module == "shared")
                    continue;
                String S = String(thisPar->module.c_str()) + " " + String(thisPar->param.c_str());
                if(thisPar->varType != CRHM::Txt)
                    S += " <" + FloatToStrF(thisPar->minVal, ffGeneral, 4, 0)+ " to " + FloatToStrF(thisPar->maxVal, ffGeneral, 4, 0) + ">";
                ParaList->Add(S);
                for(int jj = 0; jj<thisPar->lay; jj++)
                {
                    S = "";
                    for(int ii = 0; ii < thisPar->dim; ii++)
                    {
                        if(thisPar->varType == CRHM::Float)
                            S = S + FloatToStrF(thisPar->layvalues[jj][ii], ffGeneral, 4, 0) + " ";
                        else if(thisPar->varType == CRHM::Int)
                            S = S + FloatToStrF(thisPar->ilayvalues[jj][ii], ffFixed, 8, 0) + " ";
                        else if(thisPar->varType == CRHM::Txt)
                            if(thisPar->Strings->Count > ii)
                                S = S + "'" + thisPar->Strings->Strings[ii] + "' ";
                            else
                                S = "''"; 
                        if(ii%10 == 9)
                        {
                            ParaList->Add(S);
                            S = "";
                        }
                    } 
                    if(!S.IsEmpty())
                    {
                        ParaList->Add(S);
                        S = "";
                    }
                } 
                if(!S.IsEmpty())
                    ParaList->Add(S);
            } 
        }
        ParaList->Add("######");
        ParaList->SaveToFile(SaveDialogPar->FileName);
        delete ParaList;
        Main->SqueezeParams(Sender);  
        FormActivate(Sender);
    } 
    else
    {
        CRHMException Except("File extension has to be .par.", ERR);
        Application->MessageBox(Except.Message.c_str(),
                                "Inappropriate file extension.", MB_OK);
        LogError(Except);
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::SaveParameters(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TParameter::FileSaveClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTParameter::FileSaveClick(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    if(!SaveDialogPar->FileName.IsEmpty())
        SaveParameters(Sender);
    else
        FileSaveAsClick(Sender);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::FileSaveClick(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TParameter::FileSaveAsClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTParameter::FileSaveAsClick(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    SaveDialogPar->Filter = "Parameter Files (*.par)|*.par";
    SaveDialogPar->DefaultExt = "par";
    SaveDialogPar->Title = "Save Parameter File As";
    if(SaveDialogPar->Execute())
    {
        SaveDialogPar->InitialDir = ExtractFilePath(SaveDialogPar->FileName);
        if(SaveDialogPar->InitialDir.IsEmpty())
            SaveDialogPar->InitialDir = GetCurrentDir();
        OpenDialogPar->InitialDir = SaveDialogPar->InitialDir;
        SaveParameters(Sender);
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::FileSaveAsClick(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TParameter::FileOpenClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTParameter::FileOpenClick(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    Mapstr::iterator itstrPar;
    ClassPar *thisPar;
    string module, param;
    ifstream DataFile;
    string S, s;
    String Ext;
    char pszFieldName[12];
    int pnWidth;
    int pnDecimals;
    int c;
    int Warn = IDYES;
    bool TooFewHRUs = false;
    OpenDialogPar->Filter = "Parameter Files (*.par)|*.par";
    OpenDialogPar->DefaultExt = "par";
    OpenDialogPar->Title = "Open Parameter File";
    if(OpenDialogPar->Execute())
    {
        OpenDialogPar->InitialDir = ExtractFilePath(OpenDialogPar->FileName);
        if(OpenDialogPar->InitialDir.IsEmpty())
            OpenDialogPar->InitialDir = GetCurrentDir();
        SaveDialogPar->InitialDir = OpenDialogPar->InitialDir;
        Ext = ExtractFileExt(OpenDialogPar->FileName.c_str());
        if(Ext.LowerCase() == ".par")
        {
            int c, Cols;
            string ss;
            DataFile.open(OpenDialogPar->FileName.c_str());
            if(!DataFile)
            {
                Application->MessageBox("cannot open file", "File Error", MB_OK);
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::FileOpenClick(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);return;}
            }
            getline(DataFile, Descrip);
            DataFile.ignore(80, '#');
            getline(DataFile, Line);
            Main->RemoveSharedParams(); 
            while(!DataFile.eof() && Warn != IDCANCEL)
            {
                DataFile >> module;
                if(module[1] == '#')
                    break;
                DataFile  >> param;
                if(DataFile.eof())
                    break;
                DataFile.ignore(80, '\n'); 
                S = "";
                do
                {
                    getline(DataFile, ss);
                    S += ss + ' ';
                    while(c = DataFile.peek(), iscntrl(c) || isspace(c))
                        DataFile.get();
                }
                while(c = DataFile.peek(), !isalpha(c) && c != '#');
                string Sc = S; 
                string::iterator pos; 
                bool inField = false;
                for(pos = Sc.begin(); pos != Sc.end(); ++pos)
                {
                    if(*pos == '\'')
                        inField = !inField;
                    if(inField && *pos == ' ')
                        *pos = '_';
                }
                istringstream instr; 
                instr.clear();
                instr.str(Sc);
                Cols = 0;
                for (;;)
                {
                    instr >> s;
                    if(instr.fail())
                        break;
                    ++Cols; 
                }
                if(module == "Shared")
                {
                    MapPar::iterator itPar;
                    for(itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); ++itPar)
                    {
                        thisPar = (*itPar).second;
                        if(thisPar->param == string(param))
                        {
                            if(thisPar->dim == Cols/thisPar->lay) 
                                break;
                            else if(thisPar->varType == CRHM::Txt && thisPar->dimen < CRHM::NHRU) 
                                break;
                            else   
                            {
                                if(thisPar->param == string(param) && (thisPar->dim == Cols/thisPar->dim))
                                    break;
                                else
                                    thisPar = NULL;
                            }
                        }
                    }
                }
                else
                    thisPar = ClassParFind(module, param); 
                if(thisPar)
                {
                    ClassPar *newPar = new ClassPar(*thisPar);
                    newPar->module = module; 
                    if(thisPar->varType == CRHM::Txt)
                    {
                        newPar->Strings->DelimitedText = S.c_str();
                    }
                    else
                    {
                        istringstream instr; 
                        instr.clear();
                        instr.str(S);
                        for(int jj = 0; jj<thisPar->lay; jj++)
                        {
                            for(int ii = 0; ii < newPar->dim; ii++)
                            {
                                if(newPar->varType == CRHM::Float)
                                    instr >> newPar->layvalues[jj][ii];
                                else if(newPar->varType == CRHM::Int)
                                {
                                    float x;
                                    instr >> x;
                                    newPar->ilayvalues[jj][ii] = x;
                                }
                            }
                            if(newPar->dim > Cols)
                            {
                                if(!TooFewHRUs)
                                {
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
                    if(module == "Shared")
                    {
                        Main->SetSharedParams(newPar); 
                        delete newPar;
                    }
                    else
                        ClassParSet(newPar);  
                }
                else if(Warn == IDYES)
                {
                    CRHMException Except("Unknown Module Parameter: " + string(module) + " -> "+ string(param) +
                                         " in\n\n" + string(OpenDialogPar->FileName.c_str()) + "\n\nYES - Continue displaying warnings, \nNO - Continue without displaying warnings, \nCancel - stop reading the parameter file.", ERR);
                    Warn = Application->MessageBox(Except.Message.c_str(), "Unknown Parameter in parameter file", MB_YESNOCANCEL);
                    LogError(Except);
                    while(c = DataFile.peek(), !isalpha(c) && c != '#')
                        DataFile.ignore(256, '\n');
                }
                DataFile.clear();
            } 
            Main->SqueezeParams(Sender);  
            FormActivate(Sender);
        }
        ListBox1Click(Sender);
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::FileOpenClick(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TParameter::StringGrid1KeyPress(TObject *Sender, char &Key)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTParameter::StringGrid1KeyPress(TObject*Sender,char&Key) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    if(Key == VK_RETURN || Key == VK_TAB)
    {
        Key = 0;
        ClassPar *selectPar = (ClassPar*) StringGrid1->Objects[0] [selectRow];
        float x;
        long  i;
        if(LocalValue.IsEmpty() && selectPar->varType != CRHM::Txt)
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::StringGrid1KeyPress(TObject*Sender,char&Key) @@@ Para.cpp_nocom>\n"); fclose(stdout);return;}
        try
        {
            if(selectPar->varType == CRHM::Float)
                x = LocalValue.ToDouble();
            else if(selectPar->varType == CRHM::Int)
                i = LocalValue.ToInt();
        }
        catch  (EConvertError &E)
        {
            String S = AnsiString(E.ClassName()) + E.Message;
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::StringGrid1KeyPress(TObject*Sender,char&Key) @@@ Para.cpp_nocom>\n"); fclose(stdout);return;}
        }
        catch (...)
        {
            StringGrid1->Cells[selectCol] [selectRow] = LastValue;
        }
        dirty = true;
        if(selectPar->varType == CRHM::Float)
            if(x >= selectPar->minVal && x <= selectPar->maxVal)
            {
                float *values = (float*) StringGrid1->Objects[selectCol] [selectRow];
                values[selectCol-1] = x;
                StringGrid1->Cells[selectCol] [selectRow] =
                    FloatToStrF(x, ffGeneral, 4, 0);
            }
            else
                StringGrid1->Cells[selectCol] [selectRow] = LastValue;
        else if(selectPar->varType == CRHM::Int)
            if(i >= selectPar->minVal && i <= selectPar->maxVal)
            {
                long *ivalues = (long*) StringGrid1->Objects[selectCol] [selectRow];
                ivalues[selectCol-1] = i;
                StringGrid1->Cells[selectCol] [selectRow] =
                    FloatToStrF(i, ffGeneral, 8, 0);
            }
            else
                StringGrid1->Cells[selectCol] [selectRow] = LastValue;
        else if(selectPar->varType == CRHM::Txt)
        {
            TStringList *Strings = (TStringList*) StringGrid1->Objects[selectCol] [selectRow];
            Strings->Strings[selectCol-1] = LocalValue;
        }
    }
    else   if(Key == VK_ESCAPE)
    {
        Key = 0;
        StringGrid1->Cells[selectCol][selectRow] = LastValue;
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::StringGrid1KeyPress(TObject*Sender,char&Key) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TParameter::StringGrid1SetEditText(TObject *Sender,int ACol, int ARow, const AnsiString Value)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTParameter::StringGrid1SetEditText(TObject*Sender,intACol,intARow,constAnsiStringValue) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    selectCol = ACol;
    selectRow = ARow;
    LocalValue = Value;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::StringGrid1SetEditText(TObject*Sender,intACol,intARow,constAnsiStringValue) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TParameter::FindParaCount(TObject *Sender, int Indx)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTParameter::FindParaCount(TObject*Sender,intIndx) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *thisPar;
    String S = ListBox1->Items->Strings[Indx];
    if(S == "Shared")
    {
        ParaCount = ((int) ListBox1->Items->Objects[Indx]);
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::FindParaCount(TObject*Sender,intIndx) @@@ Para.cpp_nocom>\n"); fclose(stdout);return;}
    }
    Global::Mapgetvar.clear();
    Global::Mapreadvar.clear();
    Global::Mapdeclvar.clear();
    Global::Mapdeclpar.clear();
    Global::Mapdeclobs.clear();
    Global::BuildFlag = CRHM::BUILD; 
    long index = Global::OurModulesList->IndexOf(S);
    ((ClassModule*) Global::OurModulesList->Objects[index])->decl();
    Global::BuildFlag = CRHM::DECL; 
    ParaCount = Global::Mapdeclpar.size();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::FindParaCount(TObject*Sender,intIndx) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TParameter::DisplayBasin(TObject *Sender, int Indx, int Rows)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTParameter::DisplayBasin(TObject*Sender,intIndx,intRows) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    Mapstr::iterator itPar;
    MapPar::iterator it2Par;
    ClassPar *thisPar;
    String S, SS;
    S = ListBox1->Items->Strings[Indx];
    if(S == "Shared")
    {
        endLocal = 100;
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::DisplayBasin(TObject*Sender,intIndx,intRows) @@@ Para.cpp_nocom>\n"); fclose(stdout);return;}
    }
    int jjj = Global::AllModulesList->IndexOf(S.c_str()); 
    ClassModule* thisModule = (ClassModule*) Global::AllModulesList->Objects[jjj];
    endLocal = Rows;
    Rows += 3;
    itPar = Global::Mapdeclpar.begin();
    while(itPar !=  Global::Mapdeclpar.end())   
    {
        SS = ((*itPar).second).first;
        string ss = string(S.c_str()) + ' ' + string(SS.c_str());
        long indx = -1;
        if((it2Par = Global::MapPars.find(ss)) != Global::MapPars.end())
        {
            thisPar = (*it2Par).second;
            if(thisPar->visibility != CurrentDisply && CurrentDisply != 0 ||
                    !Variation_Decide(thisModule->variation, thisPar->variation_set))  
            {
                itPar++;
                continue;
            }
            if(thisPar->lay > 1) 
                SS += "[1]";
            indx = StringGrid1->Cols[0]->IndexOf(SS);
        } 
        if(indx != -1)
        {
            itPar++;
            continue;
        }
        else
        {
            thisPar = ClassParFindShared(string("Shared ") + SS.c_str());
            int Indx2 = StringGrid1->Cols[0]->IndexOf(SS); 
            if(thisPar && Indx2 == -1)
            {
                if((thisPar->visibility == CurrentDisply || CurrentDisply == 0) &&
                        Variation_Decide(thisModule->variation, thisPar->variation_set))  
                {
                    StringGrid1->Cells[0] [Rows] = SS;
                    StringGrid1->Objects[0] [Rows] = (TObject*) thisPar;
                    StringGrid1->Cells[3] [Rows++] = "Shared";
                }
            }
            itPar++;
        }
    } 
    endBasin = Rows - 3;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::DisplayBasin(TObject*Sender,intIndx,intRows) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
bool __fastcall TParameter::FileExistsSp(String FileName)
{
freopen("c:\\injection.log", "a", stdout); printf("<bool__fastcallTParameter::FileExistsSp(StringFileName) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    ifstream DataFile;
    DataFile.open(FileName.c_str());
    if(DataFile)
    {
        DataFile.close();
{freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTParameter::FileExistsSp(StringFileName) @@@ Para.cpp_nocom>\n"); fclose(stdout);return true;}
    }
    else
{freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTParameter::FileExistsSp(StringFileName) @@@ Para.cpp_nocom>\n"); fclose(stdout);return false;}
freopen("c:\\injection.log", "a", stdout); printf("</bool__fastcallTParameter::FileExistsSp(StringFileName) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TParameter::Label5Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTParameter::Label5Click(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    ++CurrentDisply;
    CurrentDisply &= 3;
    Label5->Caption = ParameterDisply[CurrentDisply];
    ListBox1Click(Sender);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTParameter::Label5Click(TObject*Sender) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
bool TParameter::Variation_Decide(long variation, long variation_set)
{
freopen("c:\\injection.log", "a", stdout); printf("<boolTParameter::Variation_Decide(longvariation,longvariation_set) @@@ Para.cpp_nocom>\n"); fclose(stdout);
    if(Global::BuildFlag == CRHM::BUILD && variation == 0 ||                    
            (variation_set & 2048) != 0 && variation == 0 ||                        
            (variation_set  == 0) ||                                                
            (variation_set & variation) != 0)                                       
{freopen("c:\\injection.log", "a", stdout); printf("</boolTParameter::Variation_Decide(longvariation,longvariation_set) @@@ Para.cpp_nocom>\n"); fclose(stdout);return true;}
    else
{freopen("c:\\injection.log", "a", stdout); printf("</boolTParameter::Variation_Decide(longvariation,longvariation_set) @@@ Para.cpp_nocom>\n"); fclose(stdout);return false;}
freopen("c:\\injection.log", "a", stdout); printf("</boolTParameter::Variation_Decide(longvariation,longvariation_set) @@@ Para.cpp_nocom>\n"); fclose(stdout);
}
