//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CoolBar_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
  Choice = RadioGroup1->ItemIndex;
  CoolBar1->Hide;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioGroup2Click(TObject *Sender)
{
  Output = RadioGroup1->ItemIndex;
  CoolBar1->Hide;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClick(TObject *Sender)
{
  CoolBar1->Show;
}
//---------------------------------------------------------------------------
