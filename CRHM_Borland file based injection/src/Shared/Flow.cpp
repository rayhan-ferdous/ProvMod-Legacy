#include <vcl.h>
#pragma hdrstop
#include "Flow.h"
#include "DefCRHMGlobal.h"
#include "ClassModule.h"
#include <printers.hpp>
#include <Graphics.hpp>
#include "About.h"
#include "CRHMmain.h"
#include <vcl\Clipbrd.hpp>
#pragma package(smart_init)
#pragma resource "*.dfm"
TFlowForm *FlowForm;
using namespace std;
__fastcall TFlowForm::TFlowForm(TComponent* Owner) : TForm(Owner)
{
freopen("c:\\injection.log", "a", stdout); printf("<__fastcallTFlowForm::TFlowForm(TComponent*Owner):TForm(Owner) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    pFlow = NULL;
    pMetafile = NULL;
    OurDiagram = NULL;
    LocalModulesList = NULL;
    if(Printer()->Printers->Count)
    {
        Printer()->Orientation = poLandscape;
    }
    else
    {
        TMenuItem *FileItem0 = File1->Items[0]; 
        FileItem0->Enabled = false;
        TMenuItem *FileItem1 = File1->Items[1]; 
        FileItem1->Enabled = false;
    }
    DisplyPar = true;
freopen("c:\\injection.log", "a", stdout); printf("</__fastcallTFlowForm::TFlowForm(TComponent*Owner):TForm(Owner) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::DeleteRow(TStringGrid *Grid, int Row)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::DeleteRow(TStringGrid*Grid,intRow) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    for(int rr = Row; rr < Grid->RowCount-1; ++rr)
        Grid->Rows[rr] = Grid->Rows[rr+1];
    Grid->RowCount = Grid->RowCount - 1;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::DeleteRow(TStringGrid*Grid,intRow) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::DeleteBlankRows(TStringGrid *Grid)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::DeleteBlankRows(TStringGrid*Grid) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    for(int rr = Grid->RowCount - 1; rr > 1 ; --rr)
    {
        bool Used = false;
        for (int cc = 1; cc < Grid->ColCount; ++cc)
        {
            if(Grid->Rows[rr]->Strings[cc] != "")
            {
                Used = true;
                break;
            }
        }
        if(!Used)
            DeleteRow(Grid, rr);
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::DeleteBlankRows(TStringGrid*Grid) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::DeleteCol(TStringGrid *Grid, int Column)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::DeleteCol(TStringGrid*Grid,intColumn) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    for(int cc = Column; cc < Grid->ColCount-1; ++cc)
        Grid->Cols[cc] = Grid->Cols[cc+1];
    Grid->ColCount = Grid->ColCount - 1;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::DeleteCol(TStringGrid*Grid,intColumn) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::FormActivate(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::FormActivate(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    if(OurCntrl)
        StringGrid1->Visible = true;
    else
        StringGrid1->Visible = false;
    Global::Mapgetvar.clear();
    Global::Mapputvar.clear();
    Global::Mapreadvar.clear();
    Global::Mapdeclvar.clear();
    Global::Mapdeclpar.clear();
    Global::Mapdeclobs.clear();
    Global::BuildFlag = CRHM::BUILD; 
    if(LocalModulesList != NULL)
        delete LocalModulesList;
    LocalModulesList = new TStringList; 
    LocalModulesList->Assign(Global::OurModulesList);
    for(int ii = 0; ii < Global::OurModulesList->Count; ii++)
    {
        ClassModule* thisModule = (ClassModule*) Global::OurModulesList->Objects[ii];
        thisModule->variation_max = 0;
        thisModule->decl();
    }
    Global::BuildFlag = CRHM::DECL; 
    DrawGrid(Sender);
    if(LocalModulesList->Count <= 0)
    {
        if(pMetafile)
            pMetafile->Clear();
        Application->MessageBox("No modules to display", "No Model loaded", MB_OK);
{freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::FormActivate(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);return;}
    }
    if(OurDiagram != NULL)
        delete OurDiagram;
    OurDiagram = new Diagram(FlowForm);
    OurDiagram->DrawModules();
    FormPaint(Sender);
    OurCntrl = false;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::FormActivate(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::DrawGrid(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::DrawGrid(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    Mapstr::iterator itMap, pos;
    pair<Mapstr::iterator, Mapstr::iterator> rangeO;
    pair<Mapstr::iterator, Mapstr::iterator> rangeOobs;
    pair<Mapstr::iterator, Mapstr::iterator> rangeI;
    pair<Mapstr::iterator, Mapstr::iterator> rangeIobs;
    String S, S1, S2, SS;
    TGridOptions OurOptions;
    OurOptions << goFixedVertLine << goFixedHorzLine << goVertLine
               << goHorzLine << goTabs << goColSizing;
    StringGrid1->Options = OurOptions;
    StringGrid1->FixedCols = 0;
    StringGrid1->FixedRows = 0;
    StringGrid1->ColCount = 1; 
    StringGrid1->RowCount = LocalModulesList->Count + 2;
    StringGrid1->Cells[0][0] = "Variable";
    StringGrid1->Cells[0][1] = "Module";
    for (int ii = 0; ii < LocalModulesList->Count; ++ii)
        StringGrid1->Cells[0][ii+2] = LocalModulesList->Strings[ii];
    for(int ii = 0 ; ii < LocalModulesList->Count; ++ii)
    {
        S = LocalModulesList->Strings[ii];
        rangeO = Global::Mapdeclvar.equal_range(S);
        rangeOobs = Global::Mapdeclobs.equal_range(S);
        for(itMap = rangeO.first; itMap != rangeO.second; itMap++)
        {
            SS = itMap->second.first;
            pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
                          value_equals<KeyType2,  KeyType2, Pairstr>(SS));
            if(pos == Global::Mapreadvar.end() && SS[SS.Length()] != '#' && StringGrid1->Rows[0]->IndexOf(SS) < 0 && Variation_Decide(ii, itMap->second.second))  
            {
                StringGrid1->ColCount = StringGrid1->ColCount + 1;
                StringGrid1->Cols[StringGrid1->ColCount-1]->Clear();
                StringGrid1->Cells[StringGrid1->ColCount-1][0] = SS; 
                StringGrid1->Cells[StringGrid1->ColCount-1][ii+2] = "D";
                StringGrid1->Cells[StringGrid1->ColCount-1][1] = S; 
            }
        }
        for(itMap = rangeOobs.first; itMap != rangeOobs.second; itMap++)
        {
            SS = itMap->second.first; 
            if(Variation_Decide(ii, itMap->second.second))
            {
                StringGrid1->ColCount = StringGrid1->ColCount + 1;
                StringGrid1->Cols[StringGrid1->ColCount-1]->Clear();
                StringGrid1->Cells[StringGrid1->ColCount-1][0] = SS; 
                StringGrid1->Cells[StringGrid1->ColCount-1][ii+2] = "DO";
                StringGrid1->Cells[StringGrid1->ColCount-1][1] = S; 
            } 
        } 
    }
    for (int ii = 0; ii < LocalModulesList->Count; ++ii)
    {
        S = LocalModulesList->Strings[ii];
        rangeI = Global::Mapgetvar.equal_range(S);
        rangeIobs = Global::Mapreadvar.equal_range(S);
        for(itMap = rangeI.first; itMap != rangeI.second; itMap++)
        {
            SS = itMap->second.first;
            if(Variation_Decide(ii, itMap->second.second))
            {
                int jj = SS.Pos(" ");
                S1 = SS.SubString(1, jj-1);  
                S2 = SS.SubString(jj+1, SS.Length() - jj); 
                int cc = StringGrid1->Rows[0]->IndexOf(S2); 
                int rr = StringGrid1->Cols[0]->IndexOf(S); 
                if(cc == -1)
                {
                    String V2;
                    int indx = S2.Pos("@");
                    if(indx > 0)
                    {
                        V2 = S2.SubString(1, indx);
                        cc = StringGrid1->Rows[0]->IndexOf(V2); 
                        if(cc == -1)
                        {
                            for(int cc2 = 1; cc2 < StringGrid1->ColCount; ++cc2)   
                            {
                                String V3 = StringGrid1->Cells[cc2][0].SubString(1, StringGrid1->Cells[cc2][0].Pos("@"));
                                if(V2 == V3)
                                {
                                    cc = cc2;
                                    break;
                                }
                            }
                        }
                    }
                    else  
                    {
                        for(int cc2 = 1; cc2 < StringGrid1->ColCount; ++cc2)   
                        {
                            String V3 = StringGrid1->Cells[cc2][0].SubString(1, StringGrid1->Cells[cc2][0].Pos("@"));
                            if(S2 == V3)
                            {
                                cc = cc2;
                                break;
                            }
                        }
                    }
                } 
                if(rr > -1 && cc > -1 && S != StringGrid1->Cells[cc][1]) 
                    if(Variation_Decide(ii, itMap->second.second))
                    {
                        if(S1 == "*")
                            StringGrid1->Cells[cc][rr] = "*G";
                        else
                            StringGrid1->Cells[cc][rr] = "G";
                    }
            } 
        }
        rangeI = Global::Mapputvar.equal_range(S);
        for(itMap = rangeI.first; itMap != rangeI.second; itMap++)
        {
            SS = itMap->second.first;
            if(Variation_Decide(ii, itMap->second.second))
            {
                int jj = SS.Pos(" ");
                S1 = SS.SubString(1, jj-1);  
                S2 = SS.SubString(jj+1, SS.Length() - jj); 
                int cc = StringGrid1->Rows[0]->IndexOf(S2); 
                int rr = StringGrid1->Cols[0]->IndexOf(S); 
                if(cc == -1)
                {
                    if(Variation_Decide(ii, itMap->second.second))
                    {
                        String V2;
                        int indx = S2.Pos("@");
                        if(indx > 0)
                        {
                            V2 = S2.SubString(1, indx);
                            cc = StringGrid1->Rows[0]->IndexOf(V2); 
                            if(cc == -1)
                            {
                                for(int cc2 = 1; cc2 < StringGrid1->ColCount; ++cc2)
                                {
                                    String V3 = StringGrid1->Cells[cc2][0].SubString(1, StringGrid1->Cells[cc2][0].Pos("@"));
                                    if(V2 == V3)
                                    {
                                        cc = cc2;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                if(rr > -1 && cc > -1 && S != StringGrid1->Cells[cc][1])  
                {
                    if(S1 == "*")
                        StringGrid1->Cells[cc][rr] = "*P";
                    else
                        StringGrid1->Cells[cc][rr] = "P";
                }
            } 
        } 
        for(itMap = rangeIobs.first; itMap != rangeIobs.second; itMap++)
        {
            SS = itMap->second.first; 
            pos = find_if(Global::Mapdeclobs.begin(), Global::Mapdeclobs.end(),
                          value_equals<KeyType2,  KeyType2, Pairstr>(SS));
            if(pos == Global::Mapdeclobs.end())
                continue; 
            if(Variation_Decide(ii, itMap->second.second))
            {
                S1 = pos->first; 
                S2 = pos->second.first;
                int cc = MatchDecl_Obs(S, S2); 
                if(cc > -1)
                    continue; 
                cc     = StringGrid1->Rows[0]->IndexOf(S2); 
                int rr = StringGrid1->Cols[0]->IndexOf(S); 
                if(rr > -1 && cc > -1)
                {
                    StringGrid1->Cells[cc][rr] = "O";
                }
            }
        } 
    }  
    if(StringGrid1->ColCount > 1)
        StringGrid1->FixedCols = 1;
    if(StringGrid1->RowCount > 2)
        StringGrid1->FixedRows = 2;
    for (int ii = 0; ii < LocalModulesList->Count; ++ii)
    {
        S = LocalModulesList->Strings[ii];
        int mm = StringGrid1->Rows[1]->IndexOf(S);
        if(mm == -1) 
            if(StringGrid1->Rows[ii+2]->IndexOf("P") == -1 && StringGrid1->Rows[ii+2]->IndexOf("P*") == -1 || S == "shared")  
            {
                int result = IDNO;
                if(result == IDYES ||	S == "shared")  
                {
                    DeleteRow(StringGrid1, ii+2);
                    LocalModulesList->Delete(ii--); 
                }
                else
                {
                    S = LocalModulesList->Strings[ii];
                    rangeO = Global::Mapdeclvar.equal_range(S);
                    for(itMap = rangeO.first; itMap != rangeO.second; itMap++)
                    {
                        SS = itMap->second.first;
                        pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
                                      value_equals<KeyType2,  KeyType2, Pairstr>(SS));
                        if(pos == Global::Mapreadvar.end())
                        {
                            if(Variation_Decide(ii, itMap->second.second))
                            {
                                StringGrid1->ColCount = StringGrid1->ColCount + 1;
                                StringGrid1->Cols[StringGrid1->ColCount-1]->Clear();
                                StringGrid1->Cells[StringGrid1->ColCount-1][0] = SS;
                                StringGrid1->Cells[StringGrid1->ColCount-1][ii+2] = "D";
                                StringGrid1->Cells[StringGrid1->ColCount-1][1] = S;
                            }
                        }
                    }
                }
            } 
    } 
    long* UseCount = new long[LocalModulesList->Count]; 
    for (int ii = 0; ii < LocalModulesList->Count; ++ii)
        UseCount[ii] = 0;
    for(int cc = StringGrid1->ColCount - 1; cc > 0 ; --cc)
    {
        for (int ii = 0; ii < LocalModulesList->Count; ++ii)
        {
            if(StringGrid1->Cols[cc]->Strings[ii+2] == "G" ||
                    StringGrid1->Cols[cc]->Strings[ii+2] == "*G" ||
                    StringGrid1->Cols[cc]->Strings[ii+2] == "P" ||
                    StringGrid1->Cols[cc]->Strings[ii+2] == "*P" ||
                    StringGrid1->Cols[cc]->Strings[ii+2] == "O")
            {
                long indx = LocalModulesList->IndexOf(StringGrid1->Cols[cc]->Strings[1]);
                ++UseCount[indx];
            }
        } 
    }
    for(int cc = StringGrid1->ColCount - 1; cc > 0 ; --cc)
    {
        bool Used = false;
        for (int ii = LocalModulesList->Count-1; ii > 0; --ii)   
        {
            if(StringGrid1->Cols[cc]->Strings[ii+2] == "G" ||
                    StringGrid1->Cols[cc]->Strings[ii+2] == "*G" ||
                    StringGrid1->Cols[cc]->Strings[ii+2] == "P" ||
                    StringGrid1->Cols[cc]->Strings[ii+2] == "*P" ||
                    StringGrid1->Cols[cc]->Strings[ii+2] == "O" )
            {
                Used = true;
                break;
            }
        }
        long indx = LocalModulesList->IndexOf(StringGrid1->Cols[cc]->Strings[1]);
        if(!Used && UseCount[indx] != 0) 
            DeleteCol(StringGrid1, cc);
    } 
    delete[] UseCount;
    int CurVarIndx = 0;
    int CurModIndx = -1;
    for(int cc = StringGrid1->ColCount - 1; cc > 0 ; --cc)
    {
        int mm = LocalModulesList->IndexOf(StringGrid1->Cols[cc]->Strings[1]);
        if(mm != CurModIndx)   
        {
            CurModIndx = mm;
            CurVarIndx = 0;
        }
        else
            ++CurVarIndx;
        StringGrid1->Cols[cc]->Objects[1] = (TObject*) CurModIndx; 
        StringGrid1->Cols[cc]->Objects[0] = (TObject*) CurVarIndx; 
    } 
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::DrawGrid(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
Diagram::Diagram(TFlowForm *FlowForm) : FlowForm(FlowForm)
{
freopen("c:\\injection.log", "a", stdout); printf("<Diagram::Diagram(TFlowForm*FlowForm):FlowForm(FlowForm) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    int Count = FlowForm->LocalModulesList->Count;
    Boxes = new Box[Count];
    CSpacing = FlowForm->Canvas->TextHeight("ABC") + 1;
    Width = FlowForm->ClientWidth/Count/4;
    Width = (Width/CSpacing +1)*CSpacing;
    Height = FlowForm->ClientHeight/Count/2;
    Height = (Height/CSpacing +1)*CSpacing;
    HSpacing = (Width/2/CSpacing +1)*CSpacing;
    VSpacing = (Height/2/CSpacing +1)*CSpacing;
freopen("c:\\injection.log", "a", stdout); printf("</Diagram::Diagram(TFlowForm*FlowForm):FlowForm(FlowForm) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
Diagram::~Diagram()
{
freopen("c:\\injection.log", "a", stdout); printf("<Diagram::~Diagram() @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    delete[] Boxes;
freopen("c:\\injection.log", "a", stdout); printf("</Diagram::~Diagram() @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void Diagram::DrawModules()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidDiagram::DrawModules() @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    Mapstr::iterator itMap;
    pair<Mapstr::iterator, Mapstr::iterator> rangeO;
    String S, SS;
    if(FlowForm->pMetafile != NULL)
        delete FlowForm->pMetafile;
    FlowForm->pMetafile = new TMetafile;
    FlowForm->pMetafile->Enhanced = true; 
    FlowForm->pFlow = new TMetafileCanvas(FlowForm->pMetafile, 0);
    TStringList *List = new TStringList;     
    TStringList *ModList = new TStringList;  
    TStringList *InputCnt = new TStringList; 
    int ObsX = CSpacing*8;
    int X = ObsX ;
    int Y = VSpacing;
    int AdjWidth;
    int AdjHeight;
    for (int ii = 0; FlowForm->LocalModulesList->Count > ii; ++ii)
    {
        S = FlowForm->LocalModulesList->Strings[ii];
        for(int cc = 1; cc < FlowForm->StringGrid1->ColCount; ++cc)
        {
            if(FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "P" ||
                    FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*P" ||
                    FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "G" ||
                    FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*G")
            {
                int Mod = (int) FlowForm->StringGrid1->Cols[cc]->Objects[1];
                if(ii < Mod)  
                {
                    ++Boxes[ii].PadjY;
                } 
            } 
        } 
    } 
    for (int ii = 0; FlowForm->LocalModulesList->Count > ii; ++ii)
    {
        S = FlowForm->LocalModulesList->Strings[ii];
        Mapstr::iterator pos, End;
        if(FlowForm->DisplyPar)
        {
            Boxes[ii].ObsCnt = Global::Mapdeclpar.count(S);
            rangeO = Global::Mapdeclpar.equal_range(S);
            End = Global::Mapdeclpar.end();
        }
        else
        {
            Boxes[ii].ObsCnt = Global::Mapreadvar.count(S);
            rangeO = Global::Mapreadvar.equal_range(S);
            End = Global::Mapreadvar.end();
        }
        for(itMap = rangeO.first; itMap != rangeO.second; itMap++)
        {
            SS = itMap->second.first; 
            if(FlowForm->Variation_Decide(ii, itMap->second.second))
            {
                int Indx = InputCnt->IndexOf(SS);
                if(Indx == -1) 
                    InputCnt->AddObject(SS, (TObject*) -1);
                else
                {
                    int InCnt = (int) InputCnt->Objects[Indx];
                    if(InCnt > 0)
                        InputCnt->Objects[Indx] = (TObject*) -2; 
                } 
            } 
        } 
        for( int ii = 0; ii < InputCnt->Count; ++ii) 
            InputCnt->Objects[ii] = (TObject*) abs((int) InputCnt->Objects[ii]);
    }
    for (int ii = 0; FlowForm->LocalModulesList->Count > ii; ++ii)
    {
        S = FlowForm->LocalModulesList->Strings[ii];
        Mapstr::iterator pos, End;
        if(FlowForm->DisplyPar)
        {
            Boxes[ii].ObsCnt = Global::Mapdeclpar.count(S);
            rangeO = Global::Mapdeclpar.equal_range(S);
            End = Global::Mapdeclpar.end();
        }
        else
        {
            Boxes[ii].ObsCnt = Global::Mapreadvar.count(S);
            rangeO = Global::Mapreadvar.equal_range(S);
            End = Global::Mapreadvar.end();
        }
        for(itMap = rangeO.first; itMap != rangeO.second; itMap++)
        {
            SS = itMap->second.first; 
            int Indx = InputCnt->IndexOf(SS);
            if(Indx > -1)
            {
                int InCnt = (int) InputCnt->Objects[Indx];
                if(InCnt > 1)
                {
                    ++Boxes[ii].ObsCntX;
                    InputCnt->Objects[Indx] = (TObject*) -2; 
                }
            }
        }
        for( int ii = 0; ii < InputCnt->Count; ++ii) 
            InputCnt->Objects[ii] = (TObject*) abs((int) InputCnt->Objects[ii]);
    }
    for (int ii = 0; FlowForm->LocalModulesList->Count > ii; ++ii)
    {
        S = FlowForm->LocalModulesList->Strings[ii];
        X = X + Boxes[ii].ObsCntX*CSpacing;
        Mapstr::iterator pos, End;
        if(FlowForm->DisplyPar)
        {
            Boxes[ii].ObsCnt = Global::Mapdeclpar.count(S);
            rangeO = Global::Mapdeclpar.equal_range(S);
            End = Global::Mapdeclpar.end();
        }
        else
        {
            Boxes[ii].ObsCnt = Global::Mapreadvar.count(S);
            rangeO = Global::Mapreadvar.equal_range(S);
            End = Global::Mapreadvar.end();
        }
        int jj = 0;
        int kk = 0;
        ModList->Clear(); 
        for(itMap = rangeO.first; itMap != rangeO.second; itMap++)
        {
            SS = itMap->second.first; 
            if(!FlowForm->Variation_Decide(ii, itMap->second.second)) 
                continue;
            if(ModList->IndexOf(SS) > -1) 
                continue;
            ModList->Add(SS);
            int Indx = InputCnt->IndexOf(SS); 
            kk = 0;
            if(InputCnt->Objects[Indx] == (TObject*) 2)
                ++kk;
            ++jj;
            Indx = List->IndexOf(SS);
            if(Indx == -1)
            {
                FlowForm->pFlow->MoveTo(CSpacing, Y + Height/2 + jj*CSpacing);
                FlowForm->pFlow->LineTo(X, Y + Height/2 + jj*CSpacing);
                FlowForm->pFlow->TextOut(CSpacing, Y + Height/2 + (jj-1)*CSpacing +1, SS);
                ++Boxes[ii].PadjX;
                ModandVar XY;
                XY.PutX(ObsX);
                XY.PutY(Y + Height/2 + jj*CSpacing);
                List->AddObject(SS, (TObject*) XY.both);
                ObsX += (kk*CSpacing);
            }
            else
            {
                ModandVar XY;
                XY.both = (int) List->Objects[Indx];
                FlowForm->pFlow->MoveTo(XY.GetX(), XY.GetY());
                FlowForm->pFlow->LineTo(XY.GetX(), Y + Height/2 + jj*CSpacing);
                FlowForm->pFlow->LineTo(X, Y + Height/2 + jj*CSpacing);
                XY.PutY(Y + Height/2 + jj*CSpacing);
                List->Objects[Indx] = (TObject*) XY.both;
                int W = FlowForm->pFlow->TextWidth(SS);
                FlowForm->pFlow->TextOut(X - W - 1, Y + Height/2 + (jj-1)*CSpacing +1, SS);
            } 
        } 
        Boxes[ii].InCnt = 0;
        for(int cc = 1; cc < FlowForm->StringGrid1->ColCount; ++cc)
        {
            if(FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "G" ||
                    FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*G" ||
                    FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "P" ||
                    FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*P")
            {
                ++Boxes[ii].InCnt;
                int Var = (int) FlowForm->StringGrid1->Cols[cc]->Objects[0];
                int Mod = (int) FlowForm->StringGrid1->Cols[cc]->Objects[1];
                int ToX, ToY;
                int InX = X + Width/2 + Boxes[ii].InCnt*CSpacing - CSpacing/2;
                if(FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "G" ||
                        FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*G")
                {
                    Boxes[Mod].GetXY(Var, InX, ToX, ToY);
                    if(ii > Mod)
                    {
                        FlowForm->pFlow->MoveTo(InX, Y);
                        FlowForm->pFlow->LineTo(InX, ToY);
                        FlowForm->pFlow->LineTo(ToX, ToY);
                    }
                }
            } 
        } 
        int First, Last;
        Boxes[ii].OutCnt = FlowForm->GetNumVar(ii, First, Last);
        Boxes[ii].OutXs = new int[Boxes[ii].OutCnt];
        Boxes[ii].OutYs = new int[Boxes[ii].OutCnt];
        for(int jj = 0; Boxes[ii].OutCnt > jj; ++jj)
        {
            Boxes[ii].OutXs[jj] = 0;
            Boxes[ii].OutYs[jj] = 0;
        } 
        AdjWidth = Width + Boxes[ii].InCnt*CSpacing;
        AdjHeight = Height + max(Boxes[ii].OutCnt, Boxes[ii].ObsCnt)*CSpacing;
        Boxes[ii].Height = Height;
        FlowForm->pFlow->RoundRect(X, Y, X + AdjWidth, Y + AdjHeight, 10, 10);
        Boxes[ii].Xul = X;
        Boxes[ii].Yul = Y;
        Boxes[ii].Xlr = X + AdjWidth;
        Boxes[ii].Ylr = Y + AdjHeight;
        Boxes[ii].CSpacing = CSpacing;
        for(int cc = First; Last > cc; ++cc)
        {
            String S = FlowForm->StringGrid1->Cols[cc]->Strings[0];
            FlowForm->pFlow->TextOut(X + AdjWidth + 1, Y + Height/2 + (cc-First)*CSpacing, S);
            int W = FlowForm->pFlow->TextWidth(S);
            W = (W/CSpacing +1)*CSpacing;
            if(W > Boxes[ii].MaxOutNameLen)
                Boxes[ii].MaxOutNameLen = W;
        }
        int W = FlowForm->pFlow->TextWidth(FlowForm->LocalModulesList->Strings[ii]);
        String S = FlowForm->LocalModulesList->Strings[ii]; 
        ClassModule* thisModule = (ClassModule*) FlowForm->LocalModulesList->Objects[ii];
        if(thisModule->variation != 0)
        {
            String AA("#0");
            AA[2] += log(thisModule->variation)/log(2) + 1;
            S += AA;
        }
        FlowForm->pFlow->TextOut(X + AdjWidth/2 - W/2, Y + AdjHeight + VSpacing/4, S);
        X = X + Boxes[ii].MaxOutNameLen + AdjWidth;
        Y = Y + VSpacing + AdjHeight;
    } 
    Xmax = (X/20 + 2)*20;
    Ymax = (Y/20 + 2)*20;
    int Yn = Global::MapAKA.size() + 5;
    int Xn = Xmax - 350;
    for (int ii = 0; FlowForm->LocalModulesList->Count > ii; ++ii)
    {
        X = Boxes[ii].Xul;
        Y = Boxes[ii].Yul;
        Boxes[ii].InCnt = 0;
        long Back_PGs = 0; 
        for(int cc = 1; cc < FlowForm->StringGrid1->ColCount; ++cc)
        {
            if(FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "G" ||
                    FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*G" ||
                    FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "P" ||
                    FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*P")
            {
                ++Boxes[ii].InCnt;
                int Var = (int) FlowForm->StringGrid1->Cols[cc]->Objects[0];
                int Mod = (int) FlowForm->StringGrid1->Cols[cc]->Objects[1];
                int ToX, ToY;
                int InX = X + Width/2 + Boxes[ii].InCnt*CSpacing - CSpacing/2;
                Boxes[Mod].GetXY(Var, InX, ToX, ToY);
                int W = FlowForm->pFlow->TextWidth(FlowForm->StringGrid1->Cols[cc]->Strings[ii+2]);
                if(ii > Mod)
                {
                    if(FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "P" ||
                            FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*P")
                    {
                        FlowForm->pFlow->TextOut(InX-W/2, Y + CSpacing/4, FlowForm->StringGrid1->Cols[cc]->Strings[ii+2]);
                        FlowForm->pFlow->MoveTo(InX, Y);
                        FlowForm->pFlow->LineTo(InX, ToY);
                        FlowForm->pFlow->LineTo(ToX, ToY);
                    }
                }
                else   
                {
                    if(FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "G" ||
                            FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*G")
                    {
                        String Message = "backward GET" + String(" variable \"") +
                                         FlowForm->StringGrid1->Cols[cc]->Strings[1] + String(" - ") +
                                         FlowForm->StringGrid1->Cols[cc]->Strings[0] + String("\" to ") +
                                         FlowForm->StringGrid1->Cols[0]->Strings[ii+2];
                        FlowForm->pFlow->TextOut(Xn, ++Yn*CSpacing, Message.c_str());
                    }
                    else
                    {
                        String Message = "backward PUT" + String(" variable \"") +
                                         FlowForm->StringGrid1->Cols[cc]->Strings[1] + String(" - ") +
                                         FlowForm->StringGrid1->Cols[cc]->Strings[0] + String("\" to ") +
                                         FlowForm->StringGrid1->Cols[0]->Strings[ii+2];
                        FlowForm->pFlow->TextOut(Xn, ++Yn*CSpacing, Message.c_str());
                    }
                    FlowForm->pFlow->TextOut(InX-W/2, Y + CSpacing/4, FlowForm->StringGrid1->Cols[cc]->Strings[ii+2]);
                    FlowForm->pFlow->MoveTo(InX, Y);
                    FlowForm->pFlow->LineTo(InX, Y-(Boxes[ii].PadjY -Back_PGs)*CSpacing);
                    float XX = Boxes[Mod].Xlr + (Boxes[Mod].OutCnt - Var)*CSpacing + CSpacing + Boxes[Mod].MaxOutNameLen;
                    FlowForm->pFlow->LineTo(XX, Y-(Boxes[ii].PadjY -Back_PGs++)*CSpacing);
                    FlowForm->pFlow->LineTo(XX, ToY);
                    FlowForm->pFlow->LineTo(Boxes[Mod].Xlr, ToY);
                }
            }
        } 
    } 
    if(!Global::MapAKA.empty())
    {
        Mapstr2::iterator it;
        int Yn = 3;
        int Yf = 3;
        int Xn = Xmax - 350;
        int Xf = Xn + 25;
        for (it = Global::MapAKA.begin(); it !=  Global::MapAKA.end(); ++it)
        {
            string Message = (*it).first;
            Message = Message.substr(Message.find(' ')+1);
            Message.insert(Message.find(' ')+1, " -  ");
            Message = '\"' + Message + '\"';
            if(Yn == 3)
                FlowForm->pFlow->TextOut(Xn, Yn++*CSpacing, "AKAs.");
            string Message2 = (*it).second;
            string::size_type idx = Message2.find(' ');
            Message += " linked to \"" + Message2.substr(idx+1) + " - " + Message2.substr(0, idx) + '\"';
            FlowForm->pFlow->TextOut(Xn, ++Yn*CSpacing, Message.c_str());
        }
    }
    int Mod = FlowForm->LocalModulesList->Count-1;
    Xmax += Boxes[Mod].MaxOutNameLen  + (Boxes[Mod].OutCnt -1)*CSpacing;
    FlowForm->pFlow->MoveTo(Xmax-20, Ymax);
    FlowForm->pFlow->LineTo(Xmax, Ymax);
    FlowForm->pFlow->LineTo(Xmax, Ymax-20);
    int W = FlowForm->pFlow->TextWidth(FlowForm->Title);
    FlowForm->pFlow->TextOut(Xmax/2 - W/2, CSpacing, FlowForm->Title);
    FlowForm->HorzScrollBar->Range = Xmax;
    FlowForm->VertScrollBar->Range = Ymax;
    delete FlowForm->pFlow;
    FlowForm->pFlow->Refresh();
    delete List;
    delete ModList;
    delete InputCnt;
freopen("c:\\injection.log", "a", stdout); printf("</voidDiagram::DrawModules() @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::FormDestroy(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::FormDestroy(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    delete OurDiagram;
    delete LocalModulesList;
    delete pMetafile;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::FormDestroy(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
int __fastcall TFlowForm::GetNumVar(int Mod, int &First, int &Last)
{
freopen("c:\\injection.log", "a", stdout); printf("<int__fastcallTFlowForm::GetNumVar(intMod,int&First,int&Last) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    First = -1;
    Last = -1;
    for(int cc = 1; cc < StringGrid1->ColCount; ++cc)
    {
        if((int) StringGrid1->Cols[cc]->Objects[1] == Mod)
        {
            if(First == -1)
            {
                First = cc;
                Last = First;
            }
            ++Last;
        }
    }
    if(First == -1)
    {
        String S = LocalModulesList->Strings[Mod];
{freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTFlowForm::GetNumVar(intMod,int&First,int&Last) @@@ Flow.cpp_nocom>\n"); fclose(stdout);return 0;}
    }
{freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTFlowForm::GetNumVar(intMod,int&First,int&Last) @@@ Flow.cpp_nocom>\n"); fclose(stdout);return (Last - First);}
freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTFlowForm::GetNumVar(intMod,int&First,int&Last) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
Box::~Box()
{
freopen("c:\\injection.log", "a", stdout); printf("<Box::~Box() @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    if(OutXs)
    {
        delete[] OutXs;
        delete[] OutYs;
    }
freopen("c:\\injection.log", "a", stdout); printf("</Box::~Box() @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void Box::GetXY(int Out_Var, int InX, int &ToX, int &ToY)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidBox::GetXY(intOut_Var,intInX,int&ToX,int&ToY) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    if(!OutXs)
    {
        ToX = 0;
        ToY = 0;
{freopen("c:\\injection.log", "a", stdout); printf("</voidBox::GetXY(intOut_Var,intInX,int&ToX,int&ToY) @@@ Flow.cpp_nocom>\n"); fclose(stdout);return;}
    }
    if(OutXs[Out_Var] != 0)
    {
        ToX = OutXs[Out_Var];
        OutXs[Out_Var] = InX;
    }
    else
        ToX = Xlr;
    ToY = Yul + Height/2 + (OutCnt - Out_Var)*CSpacing;
freopen("c:\\injection.log", "a", stdout); printf("</voidBox::GetXY(intOut_Var,intInX,int&ToX,int&ToY) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::Exit1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::Exit1Click(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    Close();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::Exit1Click(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::FormResize(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::FormResize(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    Refresh();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::FormResize(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::FormPaint(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::FormPaint(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    FlowForm->Canvas->Brush->Color = clWhite;
    FlowForm->Canvas->FillRect(Rect(0, 0, FlowForm->ClientWidth, FlowForm->ClientHeight));
    int X = FlowForm->HorzScrollBar->Position;
    int Y = FlowForm->VertScrollBar->Position;
    FlowForm->Canvas->Draw(-X, -Y, pMetafile);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::FormPaint(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::FormCreate(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::FormCreate(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    FlowForm->HorzScrollBar->Range = FlowForm->ClientWidth;
    FlowForm->VertScrollBar->Range = FlowForm->ClientHeight;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::FormCreate(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::Print1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::Print1Click(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    TPicture *pPicture = new TPicture;
    pPicture->Metafile = pMetafile;
    Printer()->BeginDoc();
    float ScaleX = (float) pPicture->Width/OurDiagram->Xmax;
    float ScaleY = (float) pPicture->Height/OurDiagram->Ymax;
    Printer()->Canvas->StretchDraw(Rect(0, 0, Printer()->PageWidth*ScaleX, Printer()->PageHeight*ScaleY), pPicture->Graphic);
    Printer()->EndDoc();
    delete pPicture;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::Print1Click(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::PrinterSetUp1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::PrinterSetUp1Click(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    PrinterSetupDialog1->Execute();
    Printer()->Canvas->Font = FontDialog1->Font;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::PrinterSetUp1Click(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void TFlowForm::SetTitle(String Text)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidTFlowForm::SetTitle(StringText) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    Title = Text;
freopen("c:\\injection.log", "a", stdout); printf("</voidTFlowForm::SetTitle(StringText) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::Selection1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::Selection1Click(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    DisplyPar = !DisplyPar;
    FormActivate(Sender);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::Selection1Click(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::BitFile1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::BitFile1Click(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    TPicture *pPicture = new TPicture;
    pPicture->Metafile = pMetafile;
    Clipboard()->Assign(pPicture);
    delete pPicture;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::BitFile1Click(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::MetaFile1Click(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::MetaFile1Click(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    TPicture *pPicture = new TPicture;
    pPicture->Metafile = pMetafile;
    FlowForm->pFlow = new TMetafileCanvas(pPicture->Metafile, 0);
    float ScaleX = (float) pMetafile->Width/OurDiagram->Xmax;
    float ScaleY = (float) pMetafile->Height/OurDiagram->Ymax;
    FlowForm->pFlow->Refresh();
    FlowForm->Canvas->Refresh();
    pPicture->Graphic->SaveToFile("c:\\oneeye.jpg");
    Clipboard()->Assign(pPicture->Graphic);
    FlowForm->pFlow->Refresh();
    delete pPicture;
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::MetaFile1Click(TObject*Sender) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::FormKeyDown(TObject*Sender,WORD&Key,TShiftStateShift) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    if(Shift.Contains(ssCtrl))
    {
        OurCntrl = true; 
    }
    else
    {
        OurCntrl = false; 
    }
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::FormKeyDown(TObject*Sender,WORD&Key,TShiftStateShift) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TFlowForm::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTFlowForm::FormKeyUp(TObject*Sender,WORD&Key,TShiftStateShift) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    OurCntrl = false; 
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTFlowForm::FormKeyUp(TObject*Sender,WORD&Key,TShiftStateShift) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
int __fastcall TFlowForm::MatchDecl_Obs(String module, String Obs)
{
freopen("c:\\injection.log", "a", stdout); printf("<int__fastcallTFlowForm::MatchDecl_Obs(Stringmodule,StringObs) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    int Col;
    for(Col = 2; Col < StringGrid1->ColCount; ++Col) 
        if(module == StringGrid1->Cells[Col][1] && Obs == StringGrid1->Cells[Col][0])
{freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTFlowForm::MatchDecl_Obs(Stringmodule,StringObs) @@@ Flow.cpp_nocom>\n"); fclose(stdout);return Col;}
{freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTFlowForm::MatchDecl_Obs(Stringmodule,StringObs) @@@ Flow.cpp_nocom>\n"); fclose(stdout);return -1;}
freopen("c:\\injection.log", "a", stdout); printf("</int__fastcallTFlowForm::MatchDecl_Obs(Stringmodule,StringObs) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
bool TFlowForm::Variation_Decide(int indx, long Variation)
{
freopen("c:\\injection.log", "a", stdout); printf("<boolTFlowForm::Variation_Decide(intindx,longVariation) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
    ClassModule* thisModule = (ClassModule*) FlowForm->LocalModulesList->Objects[indx];
    VandP V;
    V.Set(Variation);
    long variations = V.GetV(); 
    long Variation_set = thisModule->variation;
    if((variations & 2048) != 0 && Variation_set == 0 || 
            (variations & 4096) != 0 ||                        
            (variations == 0) ||                               
            (variations & Variation_set) != 0)                 
{freopen("c:\\injection.log", "a", stdout); printf("</boolTFlowForm::Variation_Decide(intindx,longVariation) @@@ Flow.cpp_nocom>\n"); fclose(stdout);return true;}
    else
{freopen("c:\\injection.log", "a", stdout); printf("</boolTFlowForm::Variation_Decide(intindx,longVariation) @@@ Flow.cpp_nocom>\n"); fclose(stdout);return false;}
freopen("c:\\injection.log", "a", stdout); printf("</boolTFlowForm::Variation_Decide(intindx,longVariation) @@@ Flow.cpp_nocom>\n"); fclose(stdout);
}
