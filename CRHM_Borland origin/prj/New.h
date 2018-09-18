// 10/23/15 ---------------------------------------------------------------------------

#ifndef NewH
#define NewH
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
        TPanel *PanelA;
        TRadioGroup *RadioGroupFunct;
        TPanel *PanelB;
        TRadioGroup *RadioGroupDisplay;
        TPanel *PanelC;
        TLabel *CancelScreen;
        void __fastcall RadioGroupFunctClick(TObject *Sender);
        void __fastcall RadioGroupDisplayClick(TObject *Sender);
        void __fastcall FormClick(TObject *Sender);
        void __fastcall CancelClick(TObject *Sender);
        void __fastcall CancelScreenClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
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
