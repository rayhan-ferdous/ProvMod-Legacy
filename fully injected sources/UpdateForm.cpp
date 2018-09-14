#include <vcl.h>
#pragma hdrstop
#include "UpdateForm.h"
#include <stdio.h>
#pragma package(smart_init)
#pragma resource "*.dfm"
TPlotControl *PlotControl;
__fastcall TPlotControl::TPlotControl(TComponent* Owner) : TForm(Owner)
{
freopen("c:\\injection.log", "a", stdout); printf("<__fastcallTPlotControl::TPlotControl(TComponent*Owner):TForm(Owner) @@@ UpdateForm.cpp_nocom>\n"); fclose(stdout);
    IntervalLength = PlotUpdate->ItemIndex; 
freopen("c:\\injection.log", "a", stdout); printf("</__fastcallTPlotControl::TPlotControl(TComponent*Owner):TForm(Owner) @@@ UpdateForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TPlotControl::PlotUpdateClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTPlotControl::PlotUpdateClick(TObject*Sender) @@@ UpdateForm.cpp_nocom>\n"); fclose(stdout);
    FormClick(Sender);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTPlotControl::PlotUpdateClick(TObject*Sender) @@@ UpdateForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TPlotControl::FormClick(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTPlotControl::FormClick(TObject*Sender) @@@ UpdateForm.cpp_nocom>\n"); fclose(stdout);
    if(PlotUpdate->ItemIndex > 1) 
        IntervalLength = PlotUpdate->ItemIndex;
    else
        IntervalControl = PlotUpdate->ItemIndex; 
    Close();
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTPlotControl::FormClick(TObject*Sender) @@@ UpdateForm.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall TPlotControl::FormActivate(TObject *Sender)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallTPlotControl::FormActivate(TObject*Sender) @@@ UpdateForm.cpp_nocom>\n"); fclose(stdout);
    if(PlotUpdate->ItemIndex < 2) 
        PlotUpdate->ItemIndex = IntervalLength; 
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallTPlotControl::FormActivate(TObject*Sender) @@@ UpdateForm.cpp_nocom>\n"); fclose(stdout);
}
