#include <vcl.h>
#pragma hdrstop
#include "Export.h"
#include <String>
#include "CRHMmain.h"
#include "DefCRHMGlobal.h"
#include <Math.hpp>
#pragma package(smart_init)
#pragma resource "*.dfm"
String Sstrings[] = {"", "_VPsat", "_WtoMJ", "_MJtoW", "_Avg", "_Min", "_Max", "_Tot", "_Pos", "_First", "_Last", "_Pk", "_Cnt", "_Cnt0", "_Dlta"};
TFileOutput *FileOutput;
__fastcall TFileOutput::TFileOutput(TComponent* Owner) : TForm(Owner)
{
freopen("c:\\injection.log", "a", stdout); printf("<__fastcallTFileOutput::TFileOutput(TComponent*Owner):TForm(Owner) @@@ Export.cpp_nocom>\n"); fclose(stdout);
freopen("c:\\injection.log", "a", stdout); printf("</__fastcallTFileOutput::TFileOutput(TComponent*Owner):TForm(Owner) @@@ Export.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFileOutput::FormActivate(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFileOutput::FormActivate(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
    long Max_Name_Width = 0;
    MaxCount = 0;
    if(SaveDialog1->InitialDir.IsEmpty())
        SaveDialog1->InitialDir = GetCurrentDir();
    ListBox1->Items->Clear();
    ListBox2->Items->Clear();
    String S;
    for(int ii = 0; ii < Main->Chart->SeriesCount(); ii++)
    {
        S = Main->Chart->Series[ii]->Title;
        if(S.Length() == 0)
            S = Main->Chart->Series[ii]->Name;
        ListBox1->Items->AddObject(S, (TObject*) ii);
        if(S.Length() > Max_Name_Width)
            Max_Name_Width = S.Length();
    }
    if(Max_Name_Width*6 > ListBox1->Width)
        ListBox1->ScrollWidth = Max_Name_Width*6;
    if(Max_Name_Width*6 > ListBox2->Width)
        ListBox2->ScrollWidth = Max_Name_Width*6;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::FormActivate(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFileOutput::FormClose(TObject *Sender, TCloseAction &Action)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFileOutput::FormClose(TObject*Sender,TCloseAction&Action) @@@ Export.cpp_nocom>\n"); fclose(stdout);
    Memo1->Clear();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::FormClose(TObject*Sender,TCloseAction&Action) @@@ Export.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFileOutput::ListBox1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFileOutput::ListBox1Click(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
    for (int ii = 0; ii < ListBox1->Items->Count; ++ii)
    {
        if(ListBox1->Selected[ii])
        {
            int found = IndexOf(ListBox2, ListBox1->Items->Strings[ii]);
            if(found == -1)
                ListBox2->Items->AddObject(ListBox1->Items->Strings[ii], (TObject*) ListBox1->Items->Objects[ii]);
        }
    }
    ShowLines = 0;
    MaxCount = 0;
    FirstFreq = -1;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::ListBox1Click(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
}
long __fastcall TFileOutput::GetFreq(TObject *Sender, long Indx)
{
freopen("c:\\injection.log", "a", stdout); printf("<long__fastcallTFileOutput::GetFreq(TObject*Sender,longIndx) @@@ Export.cpp_nocom>\n"); fclose(stdout);
    long Fix = 1.0/(Main->Chart->Series[Indx]->XValue[1] - Main->Chart->Series[Indx]->XValue[0]) + 0.5;
{freopen("c:\\injection.log", "a", stdout); printf("</long__fastcallTFileOutput::GetFreq(TObject*Sender,longIndx) @@@ Export.cpp_nocom>\n"); fclose(stdout);return Fix;}
freopen("c:\\injection.log", "a", stdout); printf("</long__fastcallTFileOutput::GetFreq(TObject*Sender,longIndx) @@@ Export.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFileOutput::Button1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFileOutput::Button1Click(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
    if(ListBox2->Items->Count == 0)
    {
        Application->MessageBox("Make a selection.", "Nothing selected!", MB_OK);
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::Button1Click(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);return;}
    }
    String Sx, Sy;
    long SecondFreq;
    long iii;
    long Indx;
    ClassVar *thisVar;
    Memo1->Lines->Clear();
    if(ListBox2->Items->Count == 0)
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::Button1Click(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);return;}
    if(ShowLines >= MaxCount)
        ShowLines = 0;
    long ShowTo = ShowLines + 1000;
    Memo1->Lines->Add("Future File Description");
    for (long jj = 0; jj < ListBox2->Items->Count; jj++)
    {
        Indx = (int) ListBox2->Items->Objects[jj]; 
        if(Main->Chart->Series[Indx]->Count() <= 0)
        {
            String Message = String("No data available for ") + String(Main->Chart->Series[Indx]->Title) + " !";
            Application->MessageBox("Run model model first.", Message.c_str(), MB_OK);
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::Button1Click(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);return;}
        }
        Sx = Main->HRUStdString(Main->Chart->Series[Indx]->Title);
        Sx += String(" 1 " + String(Main->Chart->Series[Indx]->Count())) + String(" lines");
        Memo1->Lines->Add(Sx);
        SecondFreq = GetFreq(Sender, Indx);
        if(SecondFreq > FirstFreq)  
        {
            FirstFreq = SecondFreq;
            Indx1 = Indx;
        }
        if(Main->Chart->Series[Indx]->Count() > MaxCount)
            MaxCount = Main->Chart->Series[Indx]->Count();
    } 
    Memo1->Lines->Add("######");
    for (long ii = ShowLines; ii < MaxCount; ii++)
    {
        if(ii == 0)
        {
            TDateTime Dt = TDateTime (Main->Chart->Series[Indx1]->XValue[ii]);
        }
        if(Dsply == CRHM::MDY)
        {
            TDateTime Dt = TDateTime (Main->Chart->Series[Indx1]->XValue[ii]);
            Sx = Dt.DateString()+  FormatDateTime(" hh:mm ", Dt)+ " ";
        }
        else if(Dsply == CRHM::FRACT)
        {
            TDateTime Dt = TDateTime (Main->Chart->Series[Indx1]->XValue[ii]);
            Sx = FloatToStrF(Dt, ffFixed	, 10, 5);
        }
        else if(Dsply == CRHM::BOTH)
        {
            TDateTime Dt = TDateTime (Main->Chart->Series[Indx1]->XValue[ii]);
            Sx = FloatToStrF(Dt, ffFixed, 10, 5) + ", " + FloatToStrF(ii+1, ffFixed, 10, 0) + ", " + FloatToStrF(julian(Dt), ffFixed, 3, 0) + ", " + Dt.DateString() + FormatDateTime(" hh:mm ", Dt)+ " ";
        }
        else if(Dsply == CRHM::OBS)
        {
            unsigned short year, month, day, hr, min, sec, msec;
            TDateTime Dt = TDateTime (Main->Chart->Series[Indx1]->XValue[ii]);
            Dt.DecodeDate(&year, &month, &day);
            Dt.DecodeTime(&hr, &min, &sec, &msec);
            char buff[30];
            sprintf(buff, "%4d %2d %2d %2d %2d ",
                    year, month, day, hr, min);
            Sx = String(buff);
        }
        else
            Sx = "";
        for (long jj = 0; jj < ListBox2->Items->Count; jj++)
        {
            long Indx = (int) ListBox2->Items->Objects[jj];
            thisVar =  (ClassVar *) Main->Chart->Series[Indx]->Tag;
            long prec = 6;
            if(thisVar && (thisVar->varType == CRHM::Int || thisVar->varType == CRHM::ReadI))
                prec = 4;
            iii = ii;
            SecondFreq = GetFreq(Sender, Indx);
            if(FirstFreq > SecondFreq)
                iii = ii*SecondFreq/FirstFreq;
            if(iii >= Main->Chart->Series[Indx]->Count())
                Sy = -9999.0;
            else
                Sy = FloatToStrF(Main->Chart->Series[Indx]->YValue[iii], ffGeneral, prec, 0);
            Sx = Sx + " " + Sy;
        } 
        Memo1->Lines->Add(Sx);
        if(ii > ShowTo)
            break;
    } 
    if(ShowTo >= MaxCount - 1)
    {
        Memo1->Lines->Add("### end ###");
        MaxCount = 0;
    }
    ShowLines = ShowTo;
    Memo1->SelStart = 0;
    Memo1->SelLength = 1;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::Button1Click(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFileOutput::ListBox2Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFileOutput::ListBox2Click(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
    int EndCnt = ListBox2->Items->Count;
    for(int ii = EndCnt-1; ii>=0; --ii)
        if(ListBox2->Selected[ii])
            ListBox2->Items->Delete(ii);
    ShowLines = 0;
    MaxCount = 0;
    FirstFreq = -1;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::ListBox2Click(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFileOutput::ExitClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFileOutput::ExitClick(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
    Close();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::ExitClick(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFileOutput::SaveClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFileOutput::SaveClick(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
    if(!SaveDialog1->FileName.IsEmpty())
        DoSave(Sender);
    else
        SaveAsClick(Sender);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::SaveClick(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFileOutput::SaveAsClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFileOutput::SaveAsClick(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
    SaveDialog1->Title = "Save As";
    if(Dsply == CRHM::OBS || Dsply == CRHM::FRACT)
    {
        SaveDialog1->DefaultExt = "obs";
        SaveDialog1->Filter = "OBS Files (*.obs)|*.obs";
    }
    else
    {
        SaveDialog1->DefaultExt = "txt";
        SaveDialog1->Filter = "Text Files (*.txt)|*.txt";
    }
    if(SaveDialog1->Execute())
    {
        SaveDialog1->InitialDir = ExtractFilePath(SaveDialog1->FileName);
        if(SaveDialog1->InitialDir.IsEmpty())
            SaveDialog1->InitialDir = GetCurrentDir();
        DoSave(Sender);
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::SaveAsClick(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFileOutput::Button2Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFileOutput::Button2Click(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
    switch (Dsply)
    {
    case CRHM::FRACT:
        Dsply = CRHM::OBS;
        Button2->Caption = "Observation";
        break;
    case   CRHM::OBS:
        Dsply = CRHM::BOTH;
        Button2->Caption = "Excel + Line# + Julian + Date";
        break;
    case CRHM::BOTH:
        Dsply = CRHM::MDY;
        Button2->Caption = "MM/DD/YY hh:mm";
        break;
    case CRHM::MDY:
        Dsply = CRHM::FRACT;
        Button2->Caption = "Excel";
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::Button2Click(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFileOutput::FormCreate(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFileOutput::FormCreate(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
    ExportList = new TStringList;
    ShowLines = 0;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::FormCreate(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFileOutput::FormDestroy(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFileOutput::FormDestroy(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
    delete ExportList;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::FormDestroy(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFileOutput::DoSave(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFileOutput::DoSave(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
    ExportList->Clear();
    if(ListBox2->Items->Count == 0)
    {
        Application->MessageBox("Make a selection.", "Nothing selected!", MB_OK);
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::DoSave(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);return;}
    }
    String Sx, Sy;
    long SecondFreq;
    long iii;
    long Indx;
    ClassVar *thisVar;
    MaxCount = 0;
    FirstFreq = -1;
    ExportList->Add("Future File Description");
    for (long jj = 0; jj < ListBox2->Items->Count; jj++)
    {
        Indx = (int) ListBox2->Items->Objects[jj]; 
        if(Main->Chart->Series[Indx]->Count() <= 0)
        {
            String Message = String("No data available for ") + String(Main->Chart->Series[Indx]->Title) + " !";
            Application->MessageBox("Run model model first.", Message.c_str(), MB_OK);
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::DoSave(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);return;}
        }
        Sx = Main->HRUStdString(Main->Chart->Series[Indx]->Title);
        Sx += String(" 1");
        ExportList->Add(Sx);
        SecondFreq = GetFreq(Sender, Indx);
        if(SecondFreq > FirstFreq)  
        {
            FirstFreq = SecondFreq;
            Indx1 = Indx;
        }
        if(Main->Chart->Series[Indx]->Count() > MaxCount)
            MaxCount = Main->Chart->Series[Indx]->Count();
    } 
    ExportList->Add("######");
    for (long ii = 0; ii < MaxCount; ii++)
    {
        if(Dsply == CRHM::MDY)
        {
            TDateTime Dt = TDateTime (Main->Chart->Series[Indx1]->XValue[ii]);
            Sx = Dt.DateString()+  FormatDateTime(" hh:mm ", Dt)+ " ";
        }
        else if(Dsply == CRHM::FRACT)
            Sx = FloatToStrF(Main->Chart->Series[Indx1]->XValue[ii],
                             ffFixed	, 10, 5);
        else if(Dsply == CRHM::BOTH)
        {
            TDateTime Dt = TDateTime (Main->Chart->Series[Indx1]->XValue[ii]);
            Sx = FloatToStrF(Dt, ffFixed, 10, 5) + ", " + FloatToStrF(ii+1, ffFixed, 10, 0) + ", " + FloatToStrF(julian(Dt), ffFixed, 3, 0) + ", " + Dt.DateString() + FormatDateTime(" hh:mm ", Dt)+ " ";
        }
        else if(Dsply == CRHM::OBS)
        {
            unsigned short year, month, day, hr, min, sec, msec;
            TDateTime Dt = TDateTime (Main->Chart->Series[Indx1]->XValue[ii]);
            Dt.DecodeDate(&year, &month, &day);
            Dt.DecodeTime(&hr, &min, &sec, &msec);
            char buff[30];
            sprintf(buff, "%4d %2d %2d %2d %2d ",
                    year, month, day, hr, min);
            Sx = String(buff);
        }
        else
            Sx = "";
        for (long jj = 0; jj < ListBox2->Items->Count; jj++)
        {
            long Indx = (int) ListBox2->Items->Objects[jj];
            thisVar =  (ClassVar *) Main->Chart->Series[Indx]->Tag;
            long prec = 6;
            if(thisVar && (thisVar->varType == CRHM::Int || thisVar->varType == CRHM::ReadI))
                prec = 4;
            iii = ii;
            SecondFreq = GetFreq(Sender, Indx);
            if(FirstFreq > SecondFreq)
                iii = ii*SecondFreq/FirstFreq;
            if(iii >= Main->Chart->Series[Indx]->Count())
                Sy = -9999.0;
            else
                Sy = FloatToStrF(Main->Chart->Series[Indx]->YValue[iii], ffGeneral, prec, 0);
            Sx = Sx + "\t" + Sy;
        } 
        ExportList->Add(Sx);
    } 
    ExportList->SaveToFile(SaveDialog1->FileName);
    ExportList->Clear();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFileOutput::DoSave(TObject*Sender) @@@ Export.cpp_nocom>\n"); fclose(stdout);
}
int __fastcall TFileOutput::IndexOf(TListBox *Box, const AnsiString S)
{
freopen("c:\\injection.log", "a", stdout); printf("<int__fastcallTFileOutput::IndexOf(TListBox*Box,constAnsiStringS) @@@ Export.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < Box->Count; ++ii)
    {
        if(Box->Items->Strings[ii] == S)
{freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTFileOutput::IndexOf(TListBox*Box,constAnsiStringS) @@@ Export.cpp_nocom>\n"); fclose(stdout);return ii;}
    }
{freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTFileOutput::IndexOf(TListBox*Box,constAnsiStringS) @@@ Export.cpp_nocom>\n"); fclose(stdout);return -1;}
freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTFileOutput::IndexOf(TListBox*Box,constAnsiStringS) @@@ Export.cpp_nocom>\n"); fclose(stdout);
}
