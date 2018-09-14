#include <vcl.h>
#pragma hdrstop
#include "Log.h"
#include "DefCRHMGlobal.h"
#include <string>
#include "ClassModule.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
using namespace std;
TLogForm *LogForm;
__fastcall TLogForm::TLogForm(TComponent* Owner) : TForm(Owner)
{
freopen("c:\\injection.log", "a", stdout); printf("<__fastcallTLogForm::TLogForm(TComponent*Owner):TForm(Owner) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    LogForm->Warnings = 0;
    LogForm->Errors = 0;
    LogForm->DeclErrors = 0;
    if(!Printer()->Printers->Count)
    {
        TMenuItem *FileItem3 = File->Items[3]; 
        FileItem3->Enabled = false;
        TMenuItem *FileItem4 = File->Items[4]; 
        FileItem4->Enabled = false;
    }
freopen("c:\\injection.log", "a", stdout); printf("</__fastcallTLogForm::TLogForm(TComponent*Owner):TForm(Owner) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::LogError(CRHMException Except)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::LogError(CRHMExceptionExcept) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    String S = Except.Message.c_str();
    switch (Except.Kind)
    {
    case WARNING:
        LogForm->MemoLog->Lines->Add("Warning: " + S);
        LogForm->Warnings++;
        break;
    case ERR:
        LogForm->MemoLog->Lines->Add("Error:   " + S);
        LogForm->Errors++;
        break;
    case TERMINATE:
        LogForm->MemoLog->Lines->Add("Fatal Error: " + S);
        LogForm->Errors++;
        break;
    case DECLERR:
        LogForm->MemoLog->Lines->Add("Declaration Error: " + S);
        LogForm->DeclErrors++;
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::LogError(CRHMExceptionExcept) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::LogError(String S, TExcept Kind)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::LogError(StringS,TExceptKind) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    switch (Kind)
    {
    case WARNING:
        LogForm->MemoLog->Lines->Add("Warning: " + S);
        LogForm->Warnings++;
        break;
    case ERR:
        LogForm->MemoLog->Lines->Add("Error:   " + S);
        LogForm->Errors++;
        break;
    case TERMINATE:
        LogForm->MemoLog->Lines->Add("Fatal Error: " + S);
        LogForm->Errors++;
        break;
    case DECLERR:
        LogForm->MemoLog->Lines->Add("Declaration Error: " + S);
        LogForm->DeclErrors++;
        break;
    default:
        LogForm->MemoLog->Lines->Add("Unknown Error(should not happen): " + S);
        LogForm->DeclErrors++;
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::LogError(StringS,TExceptKind) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::ClearAllLogs(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::ClearAllLogs(void) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    LogForm->MemoLog->Clear();
    LogForm->MemoDebug->Clear();
    LogForm->Warnings = 0;
    LogForm->Errors = 0;
    LogForm->DeclErrors = 0;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::ClearAllLogs(void) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::ClearRunLogs(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::ClearRunLogs(void) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    LogForm->MemoLog->Clear();
    LogForm->MemoDebug->Clear();
    LogForm->Warnings = 0;
    LogForm->Errors = 0;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::ClearRunLogs(void) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::Exit1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::Exit1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    this->Close();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::Exit1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::FileSaveClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::FileSaveClick(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    if(!SaveDialog1->FileName.IsEmpty())
        if(MemoSel == LOG)
            MemoLog->Lines->SaveToFile(SaveDialog1->FileName);
        else
            MemoDebug->Lines->SaveToFile(SaveDialog1->FileName);
    else
        FileSaveAsClick(Sender);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::FileSaveClick(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::FileSaveAsClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::FileSaveAsClick(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    SaveDialog1->Title = "Save As";
    if(MemoSel == LOG)
    {
        SaveDialog1->DefaultExt = "log";
        SaveDialog1->Filter = "Log Files (*.log)|*.log";
        if(SaveDialog1->Execute())
        {
            SaveDialog1->InitialDir = ExtractFilePath(SaveDialog1->FileName);
            if(SaveDialog1->InitialDir.IsEmpty())
                SaveDialog1->InitialDir = GetCurrentDir();
            MemoLog->Lines->SaveToFile(SaveDialog1->FileName);
        }
    }
    else
    {
        SaveDialog1->DefaultExt = "txt";
        SaveDialog1->Filter = "Debug Files (*.txt)|*.txt";
        if(SaveDialog1->Execute())
        {
            SaveDialog1->InitialDir = ExtractFilePath(SaveDialog1->FileName);
            if(SaveDialog1->InitialDir.IsEmpty())
                SaveDialog1->InitialDir = GetCurrentDir();
            MemoDebug->Lines->SaveToFile(SaveDialog1->FileName);
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::FileSaveAsClick(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::MemoLogEnter(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::MemoLogEnter(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    MemoSel = LOG;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::MemoLogEnter(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::MemoDebugEnter(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::MemoDebugEnter(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    MemoSel = DEBUG;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::MemoDebugEnter(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::WMLogException(TMessage &Message)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::WMLogException(TMessage&Message) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    LogError(*((CRHMException*) Message.WParam));
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::WMLogException(TMessage&Message) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::WMLogException1(TMessage &Message)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::WMLogException1(TMessage&Message) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    String S = *((String*) Message.WParam);
    LogError(S, (TExcept) *(int*) Message.LParam);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::WMLogException1(TMessage&Message) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::WMLogDebug(TMessage &Message)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::WMLogDebug(TMessage&Message) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    int POS;
    String S = *((String*) Message.WParam);
    if((S.SubString(1, 3)).Pos("HRU"))
    {
        if(POS = S.Pos("_Grp"))
            S = S.SubString(1, 8) + S.SubString(++POS, 150);
    }
    else if(S.Pos("'"))  
    {
        if(POS = S.Pos("_Grp"))
            S = S.SubString(++POS, S.Length());
    }
    LogForm->MemoDebug->Lines->Add(S);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::WMLogDebug(TMessage&Message) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::ClearErrorsClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::ClearErrorsClick(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    LogForm->MemoLog->Clear();
    LogForm->Warnings = 0;
    LogForm->Errors = 0;
    LogForm->DeclErrors = 0;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::ClearErrorsClick(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::ClearDebugClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::ClearDebugClick(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    LogForm->MemoDebug->Clear();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::ClearDebugClick(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::Print1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::Print1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    int LineOnPage, LinesPerPage;
    int StartLine, EndLine, PagesInDoc, FromPage, ToPage;
    int x, y, z, PageNumber;
    bool NewPageRequired;
    TMemo *Memo1;
    TPrinter *OurPrinter = Printer();
    TPrintDialog *PrintDialog1 = new TPrintDialog(LogForm);
    TFontDialog *FontDialog1 = new TFontDialog(LogForm);
    if(MemoSel == LOG)
        Memo1 = MemoLog;
    else
        Memo1 = MemoDebug;
    if(Memo1->Lines->Count == 0)
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::Print1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);return;}
    OurPrinter->Refresh();
    NewPageRequired = FALSE;
    LinesPerPage = (OurPrinter->PageHeight /
                    OurPrinter->Canvas->TextHeight("W"));
    PagesInDoc = Memo1->Lines->Count / LinesPerPage;
    if ((Memo1->Lines->Count % LinesPerPage) > 0)
        PagesInDoc++;
    PrintDialog1->Options.Clear();
    PrintDialog1->Options << poPageNums;
    PrintDialog1->MinPage = 1;
    PrintDialog1->MaxPage = PagesInDoc;
    PrintDialog1->FromPage = 1;
    PrintDialog1->ToPage = PagesInDoc;
    if (!PrintDialog1->Execute())
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::Print1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);return;}
    OurPrinter->Canvas->Font = FontDialog1->Font;
    if(PrintDialog1->PrintRange == prPageNums)      
    {
        FromPage = PrintDialog1->FromPage;
        ToPage = PrintDialog1->ToPage;
    }
    else             
    {
        FromPage = 1;
        ToPage = PagesInDoc;
    }
    OurPrinter->Title = Memo1->Lines->Strings[6];
    OurPrinter->BeginDoc();
    LineOnPage = 0;
    PageNumber = FromPage;
    do
    {
        for (y = 0; y < PrintDialog1->Copies; y++)
        {
            if (NewPageRequired)
            {
                OurPrinter->NewPage();
                LineOnPage = 0;
            }
            NewPageRequired = TRUE;
            StartLine = ((PageNumber - 1) * (LinesPerPage-2));
            EndLine = (LinesPerPage-2) + ((PageNumber - 1) * (LinesPerPage-2));
            if (EndLine >= Memo1->Lines->Count)
                EndLine = Memo1->Lines->Count;
            for (z = StartLine; z < EndLine; z++)
            {
                OurPrinter->Canvas->TextOut(20,
                                            OurPrinter->Canvas->TextHeight(Memo1->Lines->Strings[z]) * LineOnPage,
                                            ("          " + Memo1->Lines->Strings[z]));
                LineOnPage++;
            }
            OurPrinter->Canvas->TextOut(20,
                                        OurPrinter->Canvas->TextHeight("W") * (LinesPerPage-1),
                                        ("           Page " + IntToStr(PageNumber) + " of " + IntToStr(ToPage)));
        } 
        PageNumber++;
    }
    while (PageNumber <= ToPage);
    OurPrinter->EndDoc();
    delete PrintDialog1;
    delete FontDialog1;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::Print1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::PrinterSetup1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::PrinterSetup1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    TPrinter *OurPrinter = Printer();
    TPrinterSetupDialog *PrinterSetupDialog1 = new TPrinterSetupDialog(LogForm);
    TFontDialog *FontDialog1 = new TFontDialog(LogForm);
    if(PrinterSetupDialog1->Execute()) 
        OurPrinter->Canvas->Font = FontDialog1->Font;
    delete PrinterSetupDialog1;
    delete FontDialog1;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::PrinterSetup1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::Font1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::Font1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    TPrinter *OurPrinter = Printer();
    TFontDialog *FontDialog1 = new TFontDialog(LogForm);
    if (FontDialog1->Execute()) 
        OurPrinter->Canvas->Font = FontDialog1->Font;
    delete FontDialog1;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::Font1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::FormActivate(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::FormActivate(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    if(SaveDialog1->InitialDir.IsEmpty())
        SaveDialog1->InitialDir = GetCurrentDir();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::FormActivate(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::Flags1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::Flags1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *thisPar;
    String Smod, Sv, SS;
    bool First;
    SaveDebugLog(Sender); 
    LogForm->MemoDebug->Clear();
    for(int ii = -1; ii < Global::OurModulesList->Count; ++ii)
    {
        if(ii == -1)
            Smod = "Shared";
        else
            Smod = Global::OurModulesList->Strings[ii];
        First = true;
        for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++)
        {
            thisPar = (*itPar).second;
            if(thisPar->module == "basin" || !(thisPar->module == Smod.c_str()))
                continue;
            if(thisPar->ivalues && !(thisPar->basemodule == "basin"))
            {
                if(First)
                {
                    LogForm->MemoDebug->Lines->Add(String("****** '") + Smod + "' ******");
                    LogForm->MemoDebug->Lines->Add("");
                    First = false;
                }
                Sv = String(thisPar->param.c_str()) + "   \"" + thisPar->help.c_str() + "\"";
                LogForm->MemoDebug->Lines->Add(Sv);
                if(thisPar->lay == 1)
                {
                    Sv = "";
                    for (int hh = 0; hh < thisPar->dim; ++hh)
                        Sv = Sv + FloatToStrF(thisPar->ivalues[hh], ffGeneral, 8, 0) + "\t";
                    LogForm->MemoDebug->Lines->Add(Sv);
                }
                else
                {
                    LogForm->MemoDebug->Lines->Add("");
                    for (int ll = 0; ll < thisPar->lay; ++ll)
                    {
                        Sv = String(thisPar->param.c_str()) + "[" + IntToStr(ll+1) + "]\t";
                        for (int hh = 0; hh < thisPar->dim; ++hh)
                            Sv = Sv + FloatToStrF(thisPar->ilayvalues[ll][hh], ffGeneral, 8, 0) + "\t";
                        LogForm->MemoDebug->Lines->Add(Sv);
                    }
                }
                LogForm->MemoDebug->Lines->Add("");
            }
        }
    } 
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::Flags1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::Coefficients1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::Coefficients1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *thisPar;
    String Smod, Sv, SS;
    bool First;
    SaveDebugLog(Sender); 
    LogForm->MemoDebug->Clear();
    for(int ii = -1; ii < Global::OurModulesList->Count; ++ii)
    {
        if(ii == -1)
            Smod = "Shared";
        else
            Smod = Global::OurModulesList->Strings[ii];
        First = true;
        for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++)
        {
            thisPar = (*itPar).second;
            if(thisPar->module == "basin" || !(thisPar->module == Smod.c_str()))
                continue;
            bool IsCoeff = (String(thisPar->param.c_str()).Pos("_K") > 0);
            if(thisPar->values && IsCoeff && !(thisPar->basemodule == "basin"))
            {
                if(First)
                {
                    LogForm->MemoDebug->Lines->Add(String("****** '") + Smod + "' ******");
                    LogForm->MemoDebug->Lines->Add("");
                    First = false;
                }
                Sv = String(thisPar->param.c_str()) + "   \"" + thisPar->help.c_str() + "\"";
                LogForm->MemoDebug->Lines->Add(Sv);
                if(thisPar->lay == 1)
                {
                    Sv = "";
                    for (int hh = 0; hh < thisPar->dim; ++hh)
                        Sv = Sv + FloatToStrF(thisPar->values[hh], ffGeneral, 4, 0) + "\t";
                    LogForm->MemoDebug->Lines->Add(Sv);
                }
                else
                {
                    LogForm->MemoDebug->Lines->Add("");
                    for (int ll = 0; ll < thisPar->lay; ++ll)
                    {
                        Sv = String(thisPar->param.c_str()) + "[" + IntToStr(ll+1) + "]\t";
                        for (int hh = 0; hh < thisPar->dim; ++hh)
                            Sv = Sv + FloatToStrF(thisPar->layvalues[ll][hh], ffGeneral, 8, 0) + "\t";
                        LogForm->MemoDebug->Lines->Add(Sv);
                    }
                }
                LogForm->MemoDebug->Lines->Add("");
            }
        }
    } 
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::Coefficients1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::Parameters1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::Parameters1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *thisPar;
    String Smod, Sv, SS;
    bool First;
    SaveDebugLog(Sender); 
    LogForm->MemoDebug->Clear();
    for(int ii = -1; ii < Global::OurModulesList->Count; ++ii)
    {
        if(ii == -1)
            Smod = "Shared";
        else
            Smod = Global::OurModulesList->Strings[ii];
        First = true;
        for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++)
        {
            thisPar = (*itPar).second;
            if(thisPar->module == "basin" || !(thisPar->module == Smod.c_str()))
                continue;
            if(thisPar->values && !(thisPar->basemodule == "basin"))
            {
                if(First)
                {
                    LogForm->MemoDebug->Lines->Add(String("****** '") + Smod + "' ******");
                    LogForm->MemoDebug->Lines->Add("");
                    First = false;
                }
                Sv = String(thisPar->param.c_str()) + "   \"" + thisPar->help.c_str() + "\"";
                LogForm->MemoDebug->Lines->Add(Sv);
                if(thisPar->lay == 1)
                {
                    Sv = "";
                    for (int hh = 0; hh < thisPar->dim; ++hh)
                        Sv = Sv + FloatToStrF(thisPar->values[hh], ffGeneral, 4, 0) + "\t";
                    LogForm->MemoDebug->Lines->Add(Sv);
                }
                else
                {
                    LogForm->MemoDebug->Lines->Add("");
                    for (int ll = 0; ll < thisPar->lay; ++ll)
                    {
                        Sv = String(thisPar->param.c_str()) + "[" + IntToStr(ll+1) + "]\t";
                        for (int hh = 0; hh < thisPar->dim; ++hh)
                            Sv = Sv + FloatToStrF(thisPar->layvalues[ll][hh], ffGeneral, 8, 0) + "\t";
                        LogForm->MemoDebug->Lines->Add(Sv);
                    }
                }
                LogForm->MemoDebug->Lines->Add("");
            }
        }
    } 
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::Parameters1Click(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::FormClose(TObject *Sender, TCloseAction &Action)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::FormClose(TObject*Sender,TCloseAction&Action) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    if(MemoDebugBkup)
    {
        MemoDebug->Clear();
        for(long ii = 0; ii < MemoDebugBkup->Count; ++ii)
        {
            MemoDebug->Lines->Add(MemoDebugBkup->Strings[ii]);
        }
        delete MemoDebugBkup;
        MemoDebugBkup = NULL;
    }
    if(MemoLogBkup)
    {
        MemoLog->Clear();
        for(long ii = 0; ii < MemoLogBkup->Count; ++ii)
        {
            MemoLog->Lines->Add(MemoLogBkup->Strings[ii]);
        }
        delete MemoLogBkup;
        MemoLogBkup = NULL;
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::FormClose(TObject*Sender,TCloseAction&Action) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::SaveDebugLog(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::SaveDebugLog(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    if(MemoDebugBkup)
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::SaveDebugLog(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);return;}
    MemoDebugBkup = new TStringList;
    for(long ii = 0; ii < MemoDebug->Lines->Count; ++ii)
        MemoDebugBkup->Add(MemoDebug->Lines->Strings[ii]);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::SaveDebugLog(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TLogForm::SaveMemoLog(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTLogForm::SaveMemoLog(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
    if(MemoLogBkup)
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::SaveMemoLog(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);return;}
    MemoLogBkup = new TStringList;
    for(long ii = 0; ii < MemoLog->Lines->Count; ++ii)
        MemoLogBkup->Add(MemoLog->Lines->Strings[ii]);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTLogForm::SaveMemoLog(TObject*Sender) @@@ Log.cpp_nocom>\n"); fclose(stdout);
}
