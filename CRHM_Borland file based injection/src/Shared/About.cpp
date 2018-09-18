#include <vcl.h>
#pragma hdrstop
#include "About.h"
#include <stdio.h>
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutBox *AboutBox;
__fastcall TAboutBox::TAboutBox(TComponent* Owner): TForm(Owner)
{
freopen("c:\\injection.log", "a", stdout); printf("<__fastcallTAboutBox::TAboutBox(TComponent*Owner):TForm(Owner) @@@ About.cpp_nocom>\n"); fclose(stdout);
freopen("c:\\injection.log", "a", stdout); printf("</__fastcallTAboutBox::TAboutBox(TComponent*Owner):TForm(Owner) @@@ About.cpp_nocom>\n"); fclose(stdout);
}
