//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("..\src\Shared\About.cpp", AboutBox);
USEFORM("..\src\Shared\AKAform.cpp", FormAKA);
USEFORM("..\src\Shared\Analy.cpp", Analysis);
USEFORM("..\src\Shared\Bld.cpp", BldForm);
USEFORM("..\src\Shared\CRHMmain.cpp", Main);
USEFORM("..\src\Shared\EntryForm.cpp", FormEntry);
USEFORM("..\src\Shared\Export.cpp", FileOutput);
USEFORM("..\src\Shared\Flow.cpp", FlowForm);
USEFORM("..\src\Shared\Log.cpp", LogForm);
USEFORM("..\src\Shared\Para.cpp", Parameter);
USEFORM("..\src\Shared\report.cpp", Rprt);
USEFORM("..\src\Shared\Shape.cpp", ShapeForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMain), &Main);
                 Application->CreateForm(__classid(TAboutBox), &AboutBox);
                 Application->CreateForm(__classid(TFormAKA), &FormAKA);
                 Application->CreateForm(__classid(TAnalysis), &Analysis);
                 Application->CreateForm(__classid(TBldForm), &BldForm);
                 Application->CreateForm(__classid(TFormEntry), &FormEntry);
                 Application->CreateForm(__classid(TFileOutput), &FileOutput);
                 Application->CreateForm(__classid(TFlowForm), &FlowForm);
                 Application->CreateForm(__classid(TParameter), &Parameter);
                 Application->CreateForm(__classid(TRprt), &Rprt);
                 Application->CreateForm(__classid(TLogForm), &LogForm);
                 Application->CreateForm(__classid(TShapeForm), &ShapeForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
