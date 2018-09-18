// 10/23/15 ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "New.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  RadioGroupFunct->ItemIndex = 0;;
  RadioGroupDisplay->ItemIndex = 0;;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioGroupFunctClick(TObject *Sender)
{
  Choice = RadioGroupFunct->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioGroupDisplayClick(TObject *Sender)
{
  Output = RadioGroupDisplay->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClick(TObject *Sender)
{
  CoolBar1->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CancelClick(TObject *Sender)
{
  CoolBar1->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CancelScreenClick(TObject *Sender)
{
  CoolBar1->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  CoolBar1->Hide();
}
//---------------------------------------------------------------------------

