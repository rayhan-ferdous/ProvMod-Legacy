#pragma hdrstop
#include "CRHM_parse.h"
#pragma package(smart_init)
using namespace std;
VarCHRM::~VarCHRM()
{
freopen("c:\\injection.log", "a", stdout); printf("<VarCHRM::~VarCHRM() @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);
    if(Me == NULL && (kind == CRHM || kind == CRHM2))
    {
        switch(kind)
        {
        case CRHM :
            delete[] value;
            value = NULL;
            break;
        case CRHM2 :
            for(int ii = 0; ii <= IndexMaxLay; ii++)
                delete[] value2[ii];
            delete[] value2;
            value2 = NULL;
            break;
        }
    }
};
VarCHRM::VarCHRM(const VarCHRM & Cl)
{
freopen("c:\\injection.log", "a", stdout); printf("<VarCHRM::VarCHRM(constVarCHRM&Cl) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);
    kind = Cl.kind;
    val = Cl.val;
    value = Cl.value;
    ivalue = Cl.ivalue;
    value2 = Cl.value2;
    ivalue2 = Cl.ivalue2;
    Ihh = Cl.Ihh;
    Ill = Cl.Ill;
    IndexMax = Cl.IndexMax;
    IndexMaxLay = Cl.IndexMaxLay;
    name = Cl.name;
    Me = Cl.Me;
freopen("c:\\injection.log", "a", stdout); printf("</VarCHRM::VarCHRM(constVarCHRM&Cl) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);
}
VarCHRM & VarCHRM::operator=(const VarCHRM & Cl)
{
freopen("c:\\injection.log", "a", stdout); printf("<VarCHRM&VarCHRM::operator=(constVarCHRM&Cl) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);
    if(this == &Cl)
{freopen("c:\\injection.log", "a", stdout); printf("</VarCHRM&VarCHRM::operator=(constVarCHRM&Cl) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);return *this;}
    kind = Cl.kind;
    val = Cl.val;
    value = Cl.value;
    ivalue = Cl.ivalue;
    value2 = Cl.value2;
    ivalue2 = Cl.ivalue2;
    Ihh = Cl.Ihh;
    Ill = Cl.Ill;
    IndexMax = Cl.IndexMax;
    IndexMaxLay = Cl.IndexMaxLay;
    name = Cl.name;
{freopen("c:\\injection.log", "a", stdout); printf("</VarCHRM&VarCHRM::operator=(constVarCHRM&Cl) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);return *this;}
freopen("c:\\injection.log", "a", stdout); printf("</VarCHRM&VarCHRM::operator=(constVarCHRM&Cl) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);
}
void VarCHRM::put(float val_)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidVarCHRM::put(floatval_) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);
    switch (kind)
    {
    case LOCAL :
        val = val_;
        break;
    case CRHM :
        value[min<long> (Ihh, IndexMax)] = val_;
        break;
    case CRHM2 :
        value2[min<long> (Ill, IndexMaxLay)][min<long> (Ihh, IndexMax)] = val_;
        break;
    case CRHMint :
        ivalue[min<long> (Ihh, IndexMax)] = (int) val_;
        break;
    case CRHMint2 :
        ivalue2[min<long> (Ill, IndexMaxLay)][min<long> (Ihh, IndexMax)] = (int) val_;
        break;
    case FUNobs :
        if(name == "ReadAheadObs")
            val = !Me->ReadAheadObsMacro(val_);
        else
            val = !Me->WriteAheadObsMacro(val_);
        break;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidVarCHRM::put(floatval_) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);
}
float VarCHRM::get(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatVarCHRM::get(void) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);
    switch (kind)
    {
    case LOCAL :
{freopen("c:\\injection.log", "a", stdout); printf("</floatVarCHRM::get(void) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);return val;}
    case CRHM :
{freopen("c:\\injection.log", "a", stdout); printf("</floatVarCHRM::get(void) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);return value[min<long>  (Ihh, IndexMax)];}
    case CRHM2 :
{freopen("c:\\injection.log", "a", stdout); printf("</floatVarCHRM::get(void) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);return value2[min<long> (Ill, IndexMaxLay)][min<long> (Ihh, IndexMax)];}
    case CRHMint :
{freopen("c:\\injection.log", "a", stdout); printf("</floatVarCHRM::get(void) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);return ivalue[min<long> (Ihh, IndexMax)];}
    case CRHMint2 :
{freopen("c:\\injection.log", "a", stdout); printf("</floatVarCHRM::get(void) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);return ivalue2[min<long> (Ill, IndexMaxLay)][min<long> (Ihh, IndexMax)];}
    case FUNget :
{freopen("c:\\injection.log", "a", stdout); printf("</floatVarCHRM::get(void) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);return (*pget)();}
    case FUNobs :
{freopen("c:\\injection.log", "a", stdout); printf("</floatVarCHRM::get(void) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);return (val);}
    }
{freopen("c:\\injection.log", "a", stdout); printf("</floatVarCHRM::get(void) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);return -999;}
freopen("c:\\injection.log", "a", stdout); printf("</floatVarCHRM::get(void) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);
}
long    execbase::Index;
execbase::execbase(const execbase & Cl) : eval(Cl.eval), oper(Cl.oper)
{
freopen("c:\\injection.log", "a", stdout); printf("<execbase::execbase(constexecbase&Cl):eval(Cl.eval),oper(Cl.oper) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);
    s = Cl.s;
    Lvar = Cl.Lvar;
    OurIndex = Cl.OurIndex;
    OurOrder = Cl.OurOrder;
freopen("c:\\injection.log", "a", stdout); printf("</execbase::execbase(constexecbase&Cl):eval(Cl.eval),oper(Cl.oper) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);
}
execbase & execbase::operator=(const execbase & Cl)
{
freopen("c:\\injection.log", "a", stdout); printf("<execbase&execbase::operator=(constexecbase&Cl) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);
    if(this == &Cl)
{freopen("c:\\injection.log", "a", stdout); printf("</execbase&execbase::operator=(constexecbase&Cl) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);return *this;}
    eval = Cl.eval;
    oper = Cl.oper;
    s = Cl.s;
    Lvar = Cl.Lvar;
    OurIndex = Cl.OurIndex;
    OurOrder = Cl.OurOrder;
{freopen("c:\\injection.log", "a", stdout); printf("</execbase&execbase::operator=(constexecbase&Cl) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);return *this;}
freopen("c:\\injection.log", "a", stdout); printf("</execbase&execbase::operator=(constexecbase&Cl) @@@ CRHM_parse.cpp_nocom>\n"); fclose(stdout);
}
