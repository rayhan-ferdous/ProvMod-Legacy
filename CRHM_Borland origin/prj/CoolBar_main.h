//---------------------------------------------------------------------------

#ifndef CoolBar_mainH
#define CoolBar_mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TCoolBar *CoolBar1;
        TRadioGroup *RadioGroup1;
        TRadioGroup *RadioGroup2;
        void __fastcall RadioGroup1Click(TObject *Sender);
        void __fastcall RadioGroup2Click(TObject *Sender);
        void __fastcall FormClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  long Choice;
  long Output;
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
