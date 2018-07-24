//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Para.cpp", Parameter);
USEFORM("report.cpp", Rprt);
USEFORM("About.cpp", AboutBox);
USEFORM("Bld.cpp", BldForm);
USEFORM("CRHMmain.cpp", Main);
USEFORM("Export.cpp", FileOutput);
USEFORM("Log.cpp", LogForm);
USEFORM("Shape.cpp", ShapeForm);
USEFORM("Analy.cpp", Analysis);
USEFORM("Flow.cpp", FlowForm);
USEFORM("EntryForm.cpp", FormEntry);
USEFORM("AKAform.cpp", FormAKA);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMain), &Main);
     Application->CreateForm(__classid(TParameter), &Parameter);
     Application->CreateForm(__classid(TRprt), &Rprt);
     Application->CreateForm(__classid(TAboutBox), &AboutBox);
     Application->CreateForm(__classid(TBldForm), &BldForm);
     Application->CreateForm(__classid(TFileOutput), &FileOutput);
     Application->CreateForm(__classid(TLogForm), &LogForm);
     Application->CreateForm(__classid(TShapeForm), &ShapeForm);
     Application->CreateForm(__classid(TAnalysis), &Analysis);
     Application->CreateForm(__classid(TFlowForm), &FlowForm);
     Application->CreateForm(__classid(TFormEntry), &FormEntry);
     Application->CreateForm(__classid(TFormAKA), &FormAKA);
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