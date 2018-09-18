#include <vcl.h>
#pragma hdrstop
#include "EntryForm.h"
#include "DefCRHMGlobal.h"
#include "ClassModule.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormEntry *FormEntry;
long Module::GrpCnt;
long Module::StructCnt;
__fastcall TFormEntry::TFormEntry(TComponent* Owner) : TForm(Owner)
{
freopen("c:\\injection.log", "a", stdout); printf("<__fastcallTFormEntry::TFormEntry(TComponent*Owner):TForm(Owner) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
freopen("c:\\injection.log", "a", stdout); printf("</__fastcallTFormEntry::TFormEntry(TComponent*Owner):TForm(Owner) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormEntry::FormActivate(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormEntry::FormActivate(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
    if(SaveDialogMcr->InitialDir.IsEmpty())
        SaveDialogMcr->InitialDir = GetCurrentDir();
    if(OpenDialogMcr->InitialDir.IsEmpty())
        OpenDialogMcr->InitialDir = GetCurrentDir();
    Memo->Lines->Clear();
    for (int ii = 0; ii < Global::MacroModulesList->Count; ++ii)
        Memo->Lines->Add(Global::MacroModulesList->Strings[ii]);
    Memo->SelStart = 0;
    Memo->SetFocus();
    Module::GrpCnt = 0;
    Module::StructCnt = 0;
    ParaList = NULL;
    AKAList = NULL;
    ModalResult = mrCancel;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::FormActivate(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormEntry::DoSave(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormEntry::DoSave(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
    if(Memo->SelLength == 0)
        Memo->Lines->SaveToFile(SaveDialogMcr->FileName);
    else
    {
        MemoFile->Text = Memo->SelText;
        MemoFile->Lines->SaveToFile(SaveDialogMcr->FileName);
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::DoSave(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormEntry::ExitClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormEntry::ExitClick(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
    Close();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::ExitClick(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormEntry::SaveClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormEntry::SaveClick(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
    if(!SaveDialogMcr->FileName.IsEmpty())
        DoSave(Sender);
    else
        SaveAsClick(Sender);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::SaveClick(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormEntry::SaveAsClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormEntry::SaveAsClick(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
    SaveDialogMcr->Title = "Save As";
    SaveDialogMcr->DefaultExt = "mcr";
    SaveDialogMcr->Filter = "Save Macro Files (*.mcr)|*.mcr";
    if(SaveDialogMcr->Execute())
    {
        SaveDialogMcr->InitialDir = ExtractFilePath(SaveDialogMcr->FileName);
        if(SaveDialogMcr->InitialDir.IsEmpty())
            SaveDialogMcr->InitialDir = GetCurrentDir();
        DoSave(Sender);
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::SaveAsClick(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormEntry::DoLoad(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormEntry::DoLoad(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
    MemoFile->Clear();
    MemoFile->Lines->LoadFromFile(OpenDialogMcr->FileName);
    MemoFile->SelectAll();
    Memo->SelText = MemoFile->Text;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::DoLoad(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormEntry::OpenClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormEntry::OpenClick(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
    OpenDialogMcr->Filter = "Macro Files (*.mcr)|*.mcr";
    OpenDialogMcr->DefaultExt = "mcr";
    OpenDialogMcr->Title = "Open Macro File";
    if(OpenDialogMcr->Execute())
    {
        OpenDialogMcr->InitialDir = ExtractFilePath(OpenDialogMcr->FileName);
        if(OpenDialogMcr->InitialDir.IsEmpty())
            OpenDialogMcr->InitialDir = GetCurrentDir();
        SaveDialogMcr->InitialDir = OpenDialogMcr->InitialDir;
        DoLoad(Sender);
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::OpenClick(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormEntry::SaveChangesClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormEntry::SaveChangesClick(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
    Global::MacroModulesList->Clear();
    for (int ii = 0; ii < Memo->Lines->Count; ++ii)
    {
        String S;
        if(Memo->Lines->Strings[ii].IsEmpty())
            S = " "; 
        else
            S = Memo->Lines->Strings[ii].TrimRight();
        Memo->Lines->Strings[ii] = S;
        Global::MacroModulesList->Add(S);
    }
    Memo->SelStart = 0;
    Memo->SetFocus();
    if(ParaList)
    {
        ParaList->Add("#####");
        SaveDialogPar->Filter = "Parameter Files (*.par)|*.par";
        SaveDialogPar->DefaultExt = "par";
        SaveDialogPar->Title = "Save Original Parameters As (Load this parameter file after Building the new project to keep the parameters from the cloned projects)";
        SaveDialogPar->InitialDir = GetCurrentDir();
        SaveDialogPar->FileName = "CreateGroup.par";
        if(SaveDialogPar->Execute())
        {
            ParaList->SaveToFile(SaveDialogPar->FileName);
            delete ParaList;
            ParaList = NULL;
        }
    }
    if(AKAList && AKAList->Count)
    {
        SaveDialogPar->FileName = "CreateGroup.aka";
        AKAList->SaveToFile(SaveDialogPar->FileName);
        delete AKAList;
        AKAList = NULL;
    }
    ModalResult = mrOk;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::SaveChangesClick(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormEntry::CancelChangesClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormEntry::CancelChangesClick(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
    Memo->Lines->Clear();
    Memo->SelStart = 0;
    Memo->SetFocus();
    Module::GrpCnt = 0;
    Module::StructCnt = 0;
    if(ParaList)
    {
        delete ParaList;
        ParaList = NULL;
    }
    if(AKAList)
    {
        delete AKAList;
        AKAList = NULL;
    }
    ModalResult = mrCancel;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::CancelChangesClick(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormEntry::ClearClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormEntry::ClearClick(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
    Memo->Lines->Clear();
    Module::GrpCnt = 0;
    Module::StructCnt = 0;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::ClearClick(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormEntry::CreateGroup1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormEntry::CreateGroup1Click(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
    String Txt, S, MacroName, GrpName;
    int Indx;
    OpenDialogMcr->Filter = "Project Files (*.prj)|*.prj";
    OpenDialogMcr->DefaultExt = "prj";
    OpenDialogMcr->Title = "Create Group from project file";
    if(OpenDialogMcr->Execute())
    {
        OpenDialogMcr->InitialDir = ExtractFilePath(OpenDialogMcr->FileName);
        if(OpenDialogMcr->InitialDir.IsEmpty())
            OpenDialogMcr->InitialDir = GetCurrentDir();
        SaveDialogMcr->InitialDir = OpenDialogMcr->InitialDir;
        MacroName = OpenDialogMcr->FileName;
        if(Indx = MacroName.LastDelimiter("\\"), Indx != 0) 
            MacroName = MacroName.SubString(Indx+1, MacroName.Length() - Indx);
        if(Indx = MacroName.LastDelimiter("."), Indx != 0)  
        {
            String AA;
            GroupEnding(AA, ++Module::GrpCnt);
            MacroName = MacroName.SubString(1, Indx-1) + "_Grp" + AA.SubString(2, 2);
        }
        if(!isalpha(MacroName[1]))  
        {
            Application->MessageBox("Alpha characters are upper-/lowercase characters from A through Z.", "Project file name must begin with an alpha character.", MB_OK);
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::CreateGroup1Click(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);return;}
        }
        GrpName = MacroName;
        if(Module::GrpCnt > 1)
            Module::GrpCnt = 1;
        ProjectFile = new TStringList; 
        ModuleList = new TStringList;  
        MacroList = new TStringList;   
        DefinedList = new TStringList; 
        if(!ParaList)
        {
            ParaList = new TStringList; 
            ParaList->Add("Parameters for created Group Macro");
            ParaList->Add("#####");
        }
        if(!AKAList)
        {
            AKAList = new TStringList; 
        }
        ProjectFile->LoadFromFile(OpenDialogMcr->FileName); 
        int ThisEnd = 0;
        Module *ThisModule;
        while (ThisEnd < Memo->Lines->Count)   
        {
            if(Memo->Lines->Strings[ThisEnd].Length() == 0) 
                continue;
            while(ThisEnd < Memo->Lines->Count && (Txt = Memo->Lines->Strings[ThisEnd].TrimLeft(),
                                                   Txt[1] == '/'))
                ++ThisEnd;
            if(Indx = Txt.Pos(" "))
                Txt = Txt.SubString(1, Indx-1);
            ThisModule = new Module;
            ThisModule->head = ThisEnd;
            do
                S = Memo->Lines->Strings[++ThisEnd].Trim();
            while(S[1] == '/');
            if(S.Pos("declgroup"))
            {
                ++ThisModule->GrpCnt;
                ThisModule->isGroup = true;
            }
            if(S.Pos("declstruct"))
            {
                ++ThisModule->StructCnt;
                ThisModule->isStruct = true;
            }
            while(ThisEnd < Memo->Lines->Count && !(S = Memo->Lines->Strings[ThisEnd].Trim(),
                                                    S.SubString(1,3) == "end" && (S.Length() == 3 || S.IsDelimiter(" /", 4))))
                ++ThisEnd;
            ThisModule->tail = ThisEnd++;
            DefinedList->AddObject(Txt, (TObject*) ThisModule);
        } 
        for (int ii = 0; ii < ProjectFile->Count; ++ii)  
        {
            Txt = ProjectFile->Strings[ii];
            if(Txt == "Dimensions:")
            {
                Global::nhru = (ProjectFile->Strings[ii+2].SubString(5,10)).ToInt(); 
                Global::nlay = (ProjectFile->Strings[ii+3].SubString(5,10)).ToInt(); 
            }
            if(Txt == "Parameters:")
            {
                ++ii;
                ++ii; 
                while(ProjectFile->Strings[ii][1] != '#')  
                {
                    if(ProjectFile->Strings[ii][1] == '\'' || ProjectFile->Strings[ii][1] == '-' || isdigit(ProjectFile->Strings[ii][1]))
                        ParaList->Add(ProjectFile->Strings[ii]);
                    else
                    {
                        Indx = ProjectFile->Strings[ii].Pos(" ");
                        S = ProjectFile->Strings[ii].SubString(Indx+1, ProjectFile->Strings[ii].Length() - Indx);
                        ParaList->Add(GrpName + " " + S);
                    }
                    ++ii;
                } 
                continue;
            } 
            if(Txt == "Macros:")
            {
                ++ii;
                ++ii; 
                ThisModule = NULL;
                while(ProjectFile->Strings[ii][1] != '#')  
                {
                    while(ii < ProjectFile->Count && (S = ProjectFile->Strings[ii].TrimLeft(),
                                                      S[2] == '/')) 
                        ++ii;
                    S = S.SubString(2, S.Length() - 2); 
                    if(!ThisModule)
                    {
                        if(Indx = S.Pos(" "))
                            S = S.SubString(1, Indx-1);
                        ThisModule = new Module;
                        ThisModule->head = MacroList->Count;
                        MacroList->Add(S);
                    }
                    else
                    {
                        if(S.Pos("declgroup"))
                        {
                            ++ThisModule->GrpCnt;
                            ThisModule->isGroup = true;
                        }
                        if(S.Pos("declstruct"))
                        {
                            ++ThisModule->StructCnt;
                            ThisModule->isStruct = true;
                        }
                        MacroList->Add(S);
                        if(S.SubString(1,3) == "end" && (S.Length() == 3 || S.IsDelimiter(" /", 4)))
                        {
                            ThisModule->tail = MacroList->Count;
                            MacroList->Objects[ThisModule->head] = (TObject*) (ThisModule);
                            ThisModule = NULL;
                        }
                    }
                    ++ii;
                } 
                continue;
            } 
        } 
        for (int ii = 0; ii < ProjectFile->Count; ++ii)  
        {
            Txt = ProjectFile->Strings[ii];
            if(Txt == "AKAs:")
            {
                ++ii;
                ++ii; 
                while(ProjectFile->Strings[ii][1] != '#')  
                {
                    String S = ProjectFile->Strings[ii].Trim();
                    int Indx = S.Pos(" ");
                    String type = S.SubString(1, Indx-1);
                    S = S.SubString(Indx+1, S.Length() - Indx);
                    Indx = S.Pos(" ");
                    String module = S.SubString(1, Indx-1);
                    S = S.SubString(Indx+1, S.Length() - Indx);
                    Indx = S.Pos(" ");
                    String name = S.SubString(1, Indx-1);
                    S = S.SubString(Indx+1, S.Length() - Indx);
                    String alias;
                    Indx = S.Pos(" ");
                    if(Indx == 0)
                    {
                        alias = S;
                        ParaList->Add(type + " " + GrpName + " " + name + " " + alias);
                    }
                    else
                    {
                        alias = S.SubString(1, Indx-1);
                        String source = S.SubString(Indx+1, S.Length() - Indx);
                        if(MacroList->IndexOf(source) > -1)
                            AKAList->Add(type + " " + GrpName + " " + name + " " + alias + " " + source);
                        else
                            AKAList->Add(type + " " + GrpName + " " + name + " " + alias + " " + GrpName);
                    }
                    ++ii;
                } 
            } 
            if(Txt == "Modules:")
            {
                ++ii;
                ++ii; 
                while(DefinedList->IndexOf(S) > -1)  
                {
                    ++S[S.Length()];
                }
                ModuleList->Add(GrpName);
                ModuleList->Add("declgroup " + String(Global::nhru));
                while(ProjectFile->Strings[ii][1] != '#')
                {
                    S = ProjectFile->Strings[ii].Trim();
                    if(S.Pos("+"))  
                    {
                        ++ii;
                        continue;
                    }
                    if(S.Pos(" "))
                        S = S.SubString(1, S.Pos(" ")-1);
                    ModuleList->Add(S);
                    ++ii;
                }
                ModuleList->Add("command");
                ModuleList->Add("end");
                break;
            } 
        } 
        ProjectFile->Clear();
        int EndList = ModuleList->Count-2; 
        for(int ii = 2; ii < EndList; ++ii)  
        {
            AddGroup(ii);
        }
        Memo->Lines->AddStrings(ModuleList);
        delete ProjectFile;
        delete ModuleList;
        for(int ii = 0; ii < MacroList->Count; ++ii)
            delete (Module*) MacroList->Objects[ii];
        delete MacroList;
        for(int ii = 0; ii < DefinedList->Count; ++ii)
            delete (Module*) DefinedList->Objects[ii];
        delete DefinedList;
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::CreateGroup1Click(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormEntry::AddGroup(int ii)  
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormEntry::AddGroup(intii) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
    int Indx;
    if(DefinedList->IndexOf(ModuleList->Strings[ii]) == -1)  
    {
        if(Indx = MacroList->IndexOf(ModuleList->Strings[ii]), Indx > -1)
        {
            Module* ThisModule = (Module*) MacroList->Objects[Indx];
            AddSupport(ThisModule); 
            for(int jj = ThisModule->head; jj < ThisModule->tail; ++jj) 
                Memo->Lines->Add(MacroList->Strings[jj]);
            ThisModule->avail = true;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::AddGroup(intii) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormEntry::AddSupport(Module* ThisModule)  
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormEntry::AddSupport(Module*ThisModule) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
    int Indx;
    for(int ii = ThisModule->head + 2; ii < ThisModule->tail-2; ++ii)  
    {
        if(DefinedList->IndexOf(MacroList->Strings[ii]) > -1) 
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::AddSupport(Module*ThisModule) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);return;}
        if(Indx = MacroList->IndexOf(MacroList->Strings[ii]), Indx > -1 && MacroList->Objects[Indx])
        {
            Module* ThisModule = (Module*) MacroList->Objects[Indx];
            if(ThisModule->avail) 
                continue;
            if(ThisModule->isGroup || ThisModule->isStruct)  
            {
                AddSupport(ThisModule);
                ThisModule->avail = true;
            }
            for(int jj = Indx; jj < ThisModule->tail; ++jj) 
                Memo->Lines->Add(MacroList->Strings[jj]);
            ThisModule->avail = true;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::AddSupport(Module*ThisModule) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFormEntry::FormDeactivate(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFormEntry::FormDeactivate(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
    if(ParaList)
    {
        delete ParaList;
        ParaList = NULL;
    }
    if(AKAList)
    {
        delete AKAList;
        AKAList = NULL;
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFormEntry::FormDeactivate(TObject*Sender) @@@ EntryForm.cpp_nocom>\n"); fclose(stdout);
}
