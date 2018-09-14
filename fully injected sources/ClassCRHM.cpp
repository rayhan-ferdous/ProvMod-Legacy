#include <vcl.h>
#pragma hdrstop
#include "ClassCRHM.h"
#include "newModules.h"
#include <cstring>
#include "stddef.h"
#include <sstream>
#include <iostream>
#include <fstream.h>
#include <iomanip>
#include <bitset>
#include "DefCRHMGlobal.h"
#include <Math.hpp>
#pragma package(smart_init)
using namespace std;
extern double xLimit;
extern long lLimit;
long Index_; 
void ClassVar::BackUp()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::BackUp() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    long Fix = lay;
    if(lay == 0)
        Fix = 1;
    if(varType == CRHM::Float)
    {
        layvaluesBkup = new float *[Fix];
        for(int ii = 0; ii < Fix; ii++)
            layvaluesBkup[ii] = new float[dim];
        for(int jj = 0; jj < Fix; jj++)
            for(int ii = 0; ii < dim; ii++)
                if(lay == 0 && jj == 0)
                    layvaluesBkup[jj][ii] = values[ii];
                else
                    layvaluesBkup[jj][ii] = layvalues[jj][ii];
    }
    else if(varType == CRHM::Int)
    {
        ilayvaluesBkup = new long *[Fix];
        for(int ii = 0; ii < Fix; ii++)
            ilayvaluesBkup[ii] = new long[dim];
        for(int jj = 0; jj < Fix; jj++)
            for(int ii = 0; ii < dim; ii++)
                if(lay == 0 && jj == 0)
                    ilayvaluesBkup[jj][ii] = ivalues[ii];
                else
                    ilayvaluesBkup[jj][ii] = ilayvalues[jj][ii];
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassVar::BackUp() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassVar::Restore()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Restore() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    long Fix = lay;
    if(lay == 0)
        Fix = 1;
    if(varType == CRHM::Float)
    {
        for(int jj = 0; jj < Fix; jj++)
            for(int ii = 0; ii < dim; ii++)
                if(lay == 0 && jj == 0)
                    values[ii] = layvaluesBkup[jj][ii];
                else
                    layvalues[jj][ii] = layvaluesBkup[jj][ii];
        for(int ii = 0; ii < Fix; ++ii)
            delete [] layvaluesBkup[ii];
        delete [] layvaluesBkup;  
        layvaluesBkup = NULL;
    }
    else if(varType == CRHM::Int)
    {
        for(int jj = 0; jj < Fix; jj++)
            for(int ii = 0; ii < dim; ii++)
                if(lay == 0 && jj == 0)
                    ivalues[ii] = ilayvaluesBkup[jj][ii];
                else
                    ilayvalues[jj][ii] = ilayvaluesBkup[jj][ii];
        for(int ii = 0; ii < Fix; ++ii)
            delete [] ilayvaluesBkup[ii];
        delete [] ilayvaluesBkup; 
        ilayvaluesBkup = NULL;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassVar::Restore() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassVar::ReadVar(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::ReadVar(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(FileData->Times == NULL)
    {
        if(varType == CRHM::ReadF || varType == CRHM::Read)
        {
            if(dimen == CRHM::NHRU)
                for(long ii = 0; ii < dim; ++ii)
                    values[ii] = FileData->Data
                                 [offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [Global::DTindx/FileData->ModN - FileData->IndxMin];
            else
            {
                bool exists = (Global::DTindx/FileData->ModN >= FileData->IndxMin) && (Global::DTindx/FileData->ModN <= FileData->IndxMax);
                long cnt0 = min<long>(cnt, dim);
                for(long ii = 0; ii < cnt0; ++ii)
                    if(exists)
                        values[ii] = FileData->Data
                                     [offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [Global::DTindx/FileData->ModN - FileData->IndxMin];
                    else
                        values[ii] = xLimit;
            }
        }
        else if (varType == CRHM::ReadI)
            if(dimen == CRHM::NHRU)
                for(long ii = 0; ii < dim; ++ii)
                    ivalues[ii] = INT(FileData->Data
                                      [offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [Global::DTindx/FileData->ModN - FileData->IndxMin] + 0.5);
            else
            {
                bool exists = (Global::DTindx/FileData->ModN >= FileData->IndxMin) && (Global::DTindx/FileData->ModN <= FileData->IndxMax);
                for(long ii = 0; ii < cnt; ++ii)
                    if(exists)
                        ivalues[ii] = INT(FileData->Data
                                          [offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [Global::DTindx/FileData->ModN - FileData->IndxMin] + 0.5);
                    else
                        ivalues[ii] = lLimit;
            }
    }
    else if(FileData->GoodInterval)  
    {
        if(varType == CRHM::ReadF || varType == CRHM::Read)
            if(dimen == CRHM::NHRU)
                for(long ii = 0; ii < dim; ++ii)
                    values[ii] = FileData->Data
                                 [offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [FileData->TimeIndx];
            else
                for(long ii = 0; ii < cnt; ++ii)
                    values[ii] = FileData->Data
                                 [offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [FileData->TimeIndx];
        else if (varType == CRHM::ReadI)
            if(dimen == CRHM::NHRU)
                for(long ii = 0; ii < dim; ++ii)
                    ivalues[ii] = INT(FileData->Data
                                      [offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [FileData->TimeIndx] + 0.5);
            else
                for(long ii = 0; ii < cnt; ++ii)
                    ivalues[ii] = INT(FileData->Data
                                      [offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [FileData->TimeIndx] + 0.5);
    }
    else
    {
        float doN = dim;
        if(dimen == CRHM::NOBS)
            doN = cnt;
        if(varType == CRHM::ReadF || varType == CRHM::Read)
            for(long ii = 0; ii < doN; ++ii)
                values[ii] = xLimit;
        else if (varType == CRHM::ReadI)
            for(long ii = 0; ii < doN; ++ii)
                ivalues[ii] = lLimit;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassVar::ReadVar(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassVar::WriteVar(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::WriteVar(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(FileData->Times == NULL)
    {
        if(varType == CRHM::ReadF || varType == CRHM::Read)
            if(dimen == CRHM::NHRU)
                for(long ii = 0; ii < dim; ++ii)
                    FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [Global::DTindx/FileData->ModN - FileData->IndxMin] = values[ii];
            else
                for(long ii = 0; ii < cnt; ++ii)
                    FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [Global::DTindx/FileData->ModN - FileData->IndxMin] = values[ii];
        else if (varType == CRHM::ReadI)
            for(long ii = 0; ii < dim; ++ii)
                FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [Global::DTindx/FileData->ModN - FileData->IndxMin] = ivalues[ii];
        else
            for(long ii = 0; ii < cnt; ++ii)
                FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [Global::DTindx/FileData->ModN - FileData->IndxMin] = ivalues[ii];
    }
    else if(FileData->GoodInterval)  
    {
        if(varType == CRHM::ReadF || varType == CRHM::Read)
            if(dimen == CRHM::NHRU)
                for(long ii = 0; ii < dim; ++ii)
                    FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [FileData->TimeIndx] = values[ii];
            else
                for(long ii = 0; ii < cnt; ++ii)
                    FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [FileData->TimeIndx] = values[ii];
        else if (varType == CRHM::ReadI)
            if(dimen == CRHM::NHRU)
                for(long ii = 0; ii < dim; ++ii)
                    FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [FileData->TimeIndx] = ivalues[ii];
            else
                for(long ii = 0; ii < cnt; ++ii)
                    FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt)-1] [FileData->TimeIndx] = ivalues[ii];
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassVar::WriteVar(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassVar::Intvl(void)   
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Intvl(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    float X;
    for(int ii = 0; ii < this->dim; ++ii)
    {
        for(int tt = 0; tt < Global::Freq; ++tt)
        {
            X = FileData->Data [this->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt)-1] [(Global::DTindx + tt)/ FileData->ModN - FileData->IndxMin];
            if(layvalues != NULL)
                layvalues[tt][ii] = X;
            else
                ilayvalues[tt][ii] = int(X);
        }
    }
};
void ClassVar::LoopFirst(long dim_n)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::LoopFirst(longdim_n) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Index_ = Global::DTindx/FunctVar->FileData->ModN;
    (this->*(this->UserFunct_))(dim_n);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassVar::LoopFirst(longdim_n) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassVar::LoopLast(long dim_n)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::LoopLast(longdim_n) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Index_ = Global::DTindx/FunctVar->FileData->ModN + FunctVar->FileData->Freq -1;
    (this->*(this->UserFunct_))(dim_n);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassVar::LoopLast(longdim_n) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassVar::LoopRange(long dim_n)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::LoopRange(longdim_n) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Index_ = Global::DTindx/FunctVar->FileData->ModN;
    do
    {
        (this->*(this->UserFunct_))(dim_n);
    }
    while (++Index_%FunctVar->FileData->Freq != 0);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassVar::LoopRange(longdim_n) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassVar::Tot_(long dim_n)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Tot_(longdim_n) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt)-1] [Index_-FunctVar->FileData->IndxMin];
    values[dim_n] += X;
};
void ClassVar::Pos_(long dim_n)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Pos_(longdim_n) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt-1)] [Index_-FunctVar->FileData->IndxMin];
    if(X > 0.0)
        values[dim_n] += X;
};
void ClassVar::Max_(long dim_n)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Max_(longdim_n) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt)-1] [Index_-FunctVar->FileData->IndxMin];
    if(X > values[dim_n])
        values[dim_n] = X;
};
void ClassVar::Min_(long dim_n)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Min_(longdim_n) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt)-1] [Index_-FunctVar->FileData->IndxMin];
    if(X < values[dim_n])
        values[dim_n] = X;
};
void ClassVar::Last_(long dim_n)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Last_(longdim_n) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt)-1] [Index_-FunctVar->FileData->IndxMin];
    values[dim_n] = X;
};
void ClassVar::First_(long dim_n)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::First_(longdim_n) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt)-1] [Index_-FunctVar->FileData->IndxMin];
    values[dim_n] = X;
};
void ClassVar::Avg_(long dim_n)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Avg_(longdim_n) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt)-1] [Index_-FunctVar->FileData->IndxMin];
    values[dim_n] += X/this->FileData->Freq;
};
void ClassVar::Count_(long dim_n)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Count_(longdim_n) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt)-1] [Index_-FunctVar->FileData->IndxMin];
    if(X > 0.0)
        values[dim_n] += 1.0/this->FileData->Freq;
};
void ClassVar::Count0_(long dim_n)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Count0_(longdim_n) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt)-1] [Index_-FunctVar->FileData->IndxMin];
    if(X == 0.0)
        values[dim_n] += 1.0/this->FileData->Freq;
};
void ClassVar::Avg(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Avg(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    long Index = Global::DTindx/FunctVar->FileData->ModN;
    long Count = 0;
    for(long ii = 0; ii < this->dim; ++ii)
        values[ii] = 0.0;
    do
    {
        for(long ii = 0; ii < this->dim; ++ii)
        {
            float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt)-1] [Index-FunctVar->FileData->IndxMin];
            values[ii] += X;
        }
        Count++;
    }
    while (++Index%FunctVar->FileData->Freq != 0);
    for(long ii = 0; ii < this->dim; ++ii)
    {
        values[ii] = values[ii]/Count;
    }
};
void ClassVar::Max(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Max(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    long Index = Global::DTindx/FunctVar->FileData->ModN;
    for(long ii = 0; ii < this->dim; ++ii)
        values[ii] = -100000.0;
    do
    {
        for(long ii = 0; ii < this->dim; ++ii)
        {
            float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt)-1] [Index-FunctVar->FileData->IndxMin];
            if(X > values[ii])
                values[ii] = X;
        }
    }
    while (++Index%FunctVar->FileData->Freq != 0);
};
void ClassVar::Min(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Min(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    long Index = Global::DTindx/FunctVar->FileData->ModN;
    for(long ii = 0; ii < this->dim; ++ii)
        values[ii] = 100000.0;
    do
    {
        for(long ii = 0; ii < this->dim; ++ii)
        {
            float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt)-1] [Index-FunctVar->FileData->IndxMin];
            if(X < values[ii])
                values[ii] = X;
        }
    }
    while (++Index%FunctVar->FileData->Freq != 0);
};
void ClassVar::Dtot(void)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Dtot(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    long Index = Global::DTindx/FunctVar->FileData->ModN;
    for(long ii = 0; ii < this->dim; ++ii)
        values[ii] = 0.0;
    do
    {
        for(long ii = 0; ii < this->dim; ++ii)
        {
            float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt)-1] [Index-FunctVar->FileData->IndxMin];
            values[ii] += X;
        }
    }
    while (++Index%FunctVar->FileData->Freq != 0);
};
void ClassVar::Tot(void)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Tot(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    long Index = Global::DTindx/FunctVar->FileData->ModN;
    do
    {
        for(long ii = 0; ii < this->dim; ++ii)
        {
            float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt)-1] [Index-FunctVar->FileData->IndxMin];
            values[ii] += X;
        }
    }
    while (++Index%FunctVar->FileData->Freq != 0);
};
void ClassVar::Last(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Last(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    long Index = Global::DTindx/FunctVar->FileData->ModN + FunctVar->FileData->Freq -1;
    for(long ii = 0; ii < this->dim; ++ii)
    {
        float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt)-1] [Index-FunctVar->FileData->IndxMin];
        values[ii] = X;
    }
};
void ClassVar::First(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::First(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    long Index = Global::DTindx/FunctVar->FileData->ModN;
    for(long ii = 0; ii < this->dim; ++ii)
    {
        float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt)-1] [Index-FunctVar->FileData->IndxMin];
        values[ii] = X;
    }
};
void ClassVar::Peak(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Peak(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    long Index = Global::DTindx/FunctVar->FileData->ModN;
    do
    {
        for(long ii = 0; ii < this->dim; ++ii)
        {
            float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt)-1] [Index-FunctVar->FileData->IndxMin];
            if(X > values[ii])
                values[ii] = X;
        }
    }
    while (++Index%FunctVar->FileData->Freq != 0);
};
void ClassVar::Count(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Count(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    long Index = Global::DTindx/FunctVar->FileData->ModN;
    float Divisor = FunctVar->FileData->ModN;
    if(this->root !="") 
        Divisor = this->FileData->Freq;
    do
    {
        for(long ii = 0; ii < this->dim; ++ii)
        {
            float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt)-1] [Index-FunctVar->FileData->IndxMin];
            if(X > 0.0)
                values[ii] += 1.0/Divisor;
        }
    }
    while (++Index%FunctVar->FileData->Freq != 0);
};
void ClassVar::Count0(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Count0(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    long Index = Global::DTindx/FunctVar->FileData->ModN;
    float Divisor = FunctVar->FileData->ModN;
    if(this->root !="") 
        Divisor = this->FileData->Freq;
    do
    {
        for(long ii = 0; ii < this->dim; ++ii)
        {
            float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt)-1] [Index-FunctVar->FileData->IndxMin];
            if(X == 0.0)
                values[ii] += 1.0/Divisor;
        }
    }
    while (++Index%FunctVar->FileData->Freq != 0);
};
void ClassVar::Pos(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::Pos(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    long Index = Global::DTindx/FunctVar->FileData->ModN;
    for(long ii = 0; ii < this->dim; ++ii)
        values[ii] = 0.0;
    do
    {
        for(long ii = 0; ii < this->dim; ++ii)
        {
            float X = FunctVar->FileData->Data [FunctVar->offset+min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt-1)] [Index-FunctVar->FileData->IndxMin];
            if(X > 0.0)
                values[ii] += X;
        }
    }
    while (++Index%FunctVar->FileData->Freq != 0);
};
void ClassVar::do_t(ClassModule *thisModule)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::do_t(ClassModule*thisModule) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < this->dim; ++ii) 
        values[ii] -= Global::lapse_rate[ii]*(Global::hru_elev[ii] - Global::OBS_ELEV[0][ii])/100.0;
};
void ClassVar::do_t_Clim(ClassModule *thisModule)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::do_t_Clim(ClassModule*thisModule) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    do_t(thisModule);
    for(int ii = 0; ii < this->dim; ++ii) 
        values[ii] += Global::Warming_t[ii];
};
void ClassVar::do_ppt(ClassModule *thisModule)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::do_ppt(ClassModule*thisModule) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < this->dim; ++ii)
    {
        values[ii] = values[ii]*(1.0 + (Global::hru_elev[ii] - Global::OBS_ELEV[1][ii])/100.0 *Global::ppt_adj[ii]);
    }
};
void ClassVar::do_p(ClassModule *thisModule)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::do_p(ClassModule*thisModule) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < this->dim; ++ii)
    {
        values[ii] = FunctVar->values[ii]*(1.0 + (Global::hru_elev[ii] - Global::OBS_ELEV[1][ii])/100.0 *Global::ppt_adj[ii]);
    }
};
void ClassVar::do_p_Clim(ClassModule *thisModule)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::do_p_Clim(ClassModule*thisModule) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    do_p(thisModule);
    for(int ii = 0; ii < this->dim; ++ii)
    {
        values[ii] = values[ii]*Global::Warming_p[ii];
    }
};
void ClassVar::do_ppt_Clim(ClassModule *thisModule)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::do_ppt_Clim(ClassModule*thisModule) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    do_ppt(thisModule);
    for(int ii = 0; ii < this->dim; ++ii)
    {
        values[ii] = values[ii]*Global::Warming_p[ii];
    }
};
void ClassVar::do_t_day(ClassModule *thisModule)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::do_t_day(ClassModule*thisModule) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < this->dim; ++ii)
    {
        float Fix = Global::lapse_rate[ii]*(Global::hru_elev[ii] - Global::OBS_ELEV[0][ii])/100.0;
        for(int tt = 0; tt < Global::Freq; ++tt)
        {
            Global::obs_t_obs[tt][ii] = layvalues[tt][ii]; 
            layvalues[tt][ii] -= Fix; 
            Global::obs_t[tt][ii] = layvalues[tt][ii];
        }
    }
};
void ClassVar::do_t_day_Clim(ClassModule *thisModule)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::do_t_day_Clim(ClassModule*thisModule) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    do_t_day(thisModule);
    for(int ii = 0; ii < this->dim; ++ii)
    {
        for(int tt = 0; tt < Global::Freq; ++tt)
        {
            Global::obs_t_obs[tt][ii] = layvalues[tt][ii]; 
            layvalues[tt][ii] += Global::Warming_t[ii]; 
            Global::obs_t[tt][ii] = layvalues[tt][ii];
        }
    }
};
void ClassVar::do_rh_day(ClassModule *thisModule)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::do_rh_day(ClassModule*thisModule) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < this->dim; ++ii)
    {
        for(int tt = 0; tt < Global::Freq; ++tt)
        {
            if(Global::RH_VP_flag[ii])  
            {
                Global::obs_ea[tt][ii] = estar(Global::obs_t[tt][ii])*layvalues[tt][ii]/100.0; 
                if(Global::obs_t_obs[tt][ii] > Global::obs_t[tt][ii])  
                {
                    float New_es = estar(Global::obs_t[tt][ii]); 
                    if(Global::obs_ea[tt][ii] > New_es)
                    {
                        Global::obs_ea[tt][ii] = New_es;  
                        layvalues[tt][ii] = 100.0; 
                    }
                    else
                        layvalues[tt][ii] = Global::obs_ea[tt][ii]/New_es*100.0; 
                }
            }
            else 
                Global::obs_ea[tt][ii] = estar(Global::obs_t[tt][ii])*layvalues[tt][ii]/100.0; 
        }
    }
};
void ClassVar::do_rh_day_Clim(ClassModule *thisModule)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::do_rh_day_Clim(ClassModule*thisModule) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    do_rh_day(thisModule);
    for(int ii = 0; ii < this->dim; ++ii)
    {
        for(int tt = 0; tt < Global::Freq; ++tt)
        {
            if(Global::RH_VP_flag2[ii])  
            {
                Global::obs_ea[tt][ii] = estar(Global::obs_t[tt][ii])*layvalues[tt][ii]/100.0; 
                if(Global::obs_t_obs[tt][ii] > Global::obs_t[tt][ii])  
                {
                    float New_es = estar(Global::obs_t[tt][ii]); 
                    if(Global::obs_ea[tt][ii] > New_es)
                    {
                        Global::obs_ea[tt][ii] = New_es;  
                        layvalues[tt][ii] = 100.0; 
                    }
                    else
                        layvalues[tt][ii] = Global::obs_ea[tt][ii]/New_es*100.0; 
                }
            }
            else 
                Global::obs_ea[tt][ii] = estar(Global::obs_t[tt][ii])*layvalues[tt][ii]/100.0; 
        }
    }
};
void ClassVar::do_ea_day(ClassModule *thisModule)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::do_ea_day(ClassModule*thisModule) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    float New_es;
    for(int ii = 0; ii < this->dim; ++ii)
    {
        for(int tt = 0; tt < Global::Freq; ++tt)
        {
            Global::obs_rh[tt][ii] = layvalues[tt][ii]/estar(Global::obs_t_obs[tt][ii])*100.0; 
            New_es = estar(Global::obs_t[tt][ii]); 
            if(Global::RH_VP_flag[ii])  
            {
                if(Global::obs_t_obs[tt][ii] > Global::obs_t[tt][ii])  
                {
                    if(layvalues[tt][ii] > New_es)
                    {
                        layvalues[tt][ii] = New_es;  
                        Global::obs_rh[tt][ii] = 100.0; 
                    }
                    else
                        Global::obs_rh[tt][ii] = layvalues[tt][ii]/New_es*100.0; 
                }
            }
            else  
            {
                layvalues[tt][ii] = New_es*Global::obs_rh[tt][ii]/100.0; 
                float X = layvalues[tt][ii];
            }
        }
    }
};
void setdim(string name, long dim)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidsetdim(stringname,longdim) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    string s = name;
    if(name == "nhru")
    {
        Update_Main_DIM(CRHM::NHRU, dim);
    }
    else if(name == "nobs")
    {
        Update_Main_DIM(CRHM::NOBS, dim);
    }
    else if(name == "nlay")
    {
        Update_Main_DIM(CRHM::NLAY, dim);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidsetdim(stringname,longdim) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
float sqr(float X)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatsqr(floatX) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</floatsqr(floatX) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return X * X;}
freopen("c:\\injection.log", "a", stdout); printf("</floatsqr(floatX) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassPar::ClassPar(string module, string param, CRHM::TDim dimen,string CommaText, string help, CRHM::TVar varType, int Grpdim) : module(module), basemodule(""), param(param), varType(varType), dimen(dimen), help(help),units(""), valstr(""), minVal(0), maxVal(0), Inhibit_share(0),values(NULL), ivalues(NULL), layvalues(NULL), ilayvalues(NULL), Identical(NULL), Strings(NULL),layvaluesBkup(NULL), ilayvaluesBkup(NULL), StringsBkup(NULL), lay(1)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassPar::ClassPar(stringmodule,stringparam,CRHM::TDimdimen,stringCommaText,stringhelp,CRHM::TVarvarType,intGrpdim):module(module),basemodule(""),param(param),varType(varType),dimen(dimen),help(help),units(""),valstr(""),minVal(0),maxVal(0),Inhibit_share(0),values(NULL),ivalues(NULL),layvalues(NULL),ilayvalues(NULL),Identical(NULL),Strings(NULL),layvaluesBkup(NULL),ilayvaluesBkup(NULL),StringsBkup(NULL),lay(1) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(Grpdim == 0 && dimen >= CRHM::NHRU)
        Grpdim = Global::nhru;
    if(dimen < CRHM::NHRU)
        dim = getdim(dimen); 
    else
        dim = Grpdim;
    Strings = new TStringList;
    Strings->QuoteChar = '\'';
    Strings->DelimitedText = CommaText.c_str();
    if(Strings->Count == 0) 
        Strings->Add("");
    if(dimen == CRHM::NHRU)
        for(int ii = Strings->Count; ii < dim; ++ii)
        {
            Strings->Add(Strings->Strings[0] + IntToStr(ii+1));
        }
freopen("c:\\injection.log", "a", stdout); printf("</ClassPar::ClassPar(stringmodule,stringparam,CRHM::TDimdimen,stringCommaText,stringhelp,CRHM::TVarvarType,intGrpdim):module(module),basemodule(""),param(param),varType(varType),dimen(dimen),help(help),units(""),valstr(""),minVal(0),maxVal(0),Inhibit_share(0),values(NULL),ivalues(NULL),layvalues(NULL),ilayvalues(NULL),Identical(NULL),Strings(NULL),layvaluesBkup(NULL),ilayvaluesBkup(NULL),StringsBkup(NULL),lay(1) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassPar::ExpandShrink(long new_dim)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassPar::ExpandShrink(longnew_dim) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(varType == CRHM::Txt)
    {
        StringsBkup = new TStringList;
        StringsBkup->Assign(Strings);
    }
    else if(varType == CRHM::Float)
    {
        layvaluesBkup = new float *[lay];
        for(int ii = 0; ii < lay; ii++)
            layvaluesBkup[ii] = new float[dim];
        for(int jj = 0; jj<lay; jj++)
            for(int ii = 0; ii<dim; ii++)
                layvaluesBkup[jj][ii] = layvalues[jj][ii];
    }
    else if(varType == CRHM::Int)
    {
        ilayvaluesBkup = new long *[lay];
        for(int ii = 0; ii < lay; ii++)
            ilayvaluesBkup[ii] = new long[dim];
        for(int jj = 0; jj<lay; jj++)
            for(int ii = 0; ii<dim; ii++)
                ilayvaluesBkup[jj][ii] = ilayvalues[jj][ii];
    }
    if(varType == CRHM::Float)
    {
        for(int ii = 0; ii < lay; ++ii)
            delete [] layvalues[ii];
        delete [] layvalues;  
        values = NULL;
    }
    else if(varType == CRHM::Int)
    {
        for(int ii = 0; ii < lay; ++ii)
            delete [] ilayvalues[ii];
        delete [] ilayvalues; 
        ivalues = NULL;
    }
    else if(varType == CRHM::Txt)
    {
        Strings->Clear();
    }
    long lay0 = lay;
    long dim0 = dim;
    dim = new_dim;
    if(dimen == CRHM::NDEFN) 
        lay = new_dim;
    if(varType == CRHM::Float)
    {
        if(lay > 0)
        {
            layvalues = new float *[lay];
            for(int ii = 0; ii < lay; ii++)
                layvalues[ii] = new float[dim];
            for(int jj = 0; jj < lay; ++jj)
                for(int kk = 0; kk < dim; ++kk)
                    layvalues[jj][kk] = 0.0;
        }
        values = new float[dim];
        for(int kk = 0; kk < dim; ++kk)
            values[kk] = 0.0;
    }
    else if(varType == CRHM::Int)
    {
        if(lay > 0)
        {
            ilayvalues = new long *[lay];
            for(int ii = 0; ii < lay; ii++)
                ilayvalues[ii] = new long[dim];
            for(int jj = 0; jj < lay; ++jj)
                for(int kk = 0; kk < dim; ++kk)
                    ilayvalues[jj][kk] = 0.0;
        }
        ivalues = new long[dim];
        for(int kk = 0; kk < dim; ++kk)
            ivalues[kk] = 0;
    }
    else if(varType == CRHM::Txt)
    {
        Strings->Clear();
    }
    if(varType == CRHM::Txt)
    {
        for(int kk = 0; kk < dim; ++kk)
            Strings->Add(StringsBkup->Strings[min<int>(kk, dim0-1)]);
        delete StringsBkup;
        StringsBkup = NULL;
    }
    else if(varType == CRHM::Float)
    {
        for(int jj = 0; jj<lay; jj++)
            for(int ii = 0; ii<dim; ii++)
                layvalues[jj][ii] = layvaluesBkup[min<int>(jj, lay0-1)][min<int>(ii, dim0-1)];
        for(int ii = 0; ii < lay0; ++ii)
            delete [] layvaluesBkup[ii];
        delete [] layvaluesBkup;  
        layvaluesBkup = NULL;
    }
    else if(varType == CRHM::Int)
    {
        for(int jj = 0; jj<lay; jj++)
            for(int ii = 0; ii<dim; ii++)
                ilayvalues[jj][ii] = ilayvaluesBkup[min<int>(jj, lay0-1)][min<int>(ii, dim0-1)];
        for(int ii = 0; ii < lay0; ++ii)
            delete [] ilayvaluesBkup[ii];
        delete [] ilayvaluesBkup; 
        ilayvaluesBkup = NULL;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassPar::ExpandShrink(longnew_dim) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassPar::BackUp()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassPar::BackUp() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(varType == CRHM::Txt)
    {
        StringsBkup = new TStringList;
        StringsBkup->Assign(Strings);
    }
    else if(varType == CRHM::Float)
    {
        layvaluesBkup = new float *[lay];
        for(int ii = 0; ii < lay; ii++)
            layvaluesBkup[ii] = new float[dim];
        for(int jj = 0; jj<lay; jj++)
            for(int ii = 0; ii<dim; ii++)
                layvaluesBkup[jj][ii] = layvalues[jj][ii];
    }
    else if(varType == CRHM::Int)
    {
        ilayvaluesBkup = new long *[lay];
        for(int ii = 0; ii < lay; ii++)
            ilayvaluesBkup[ii] = new long[dim];
        for(int jj = 0; jj<lay; jj++)
            for(int ii = 0; ii<dim; ii++)
                ilayvaluesBkup[jj][ii] = ilayvalues[jj][ii];
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassPar::BackUp() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassPar::Restore()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassPar::Restore() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(varType == CRHM::Txt)
    {
        Strings->Assign(StringsBkup);
        delete StringsBkup;
        StringsBkup = NULL;
    }
    else if(varType == CRHM::Float)
    {
        for(int jj = 0; jj<lay; jj++)
            for(int ii = 0; ii<dim; ii++)
                layvalues[jj][ii] = layvaluesBkup[jj][ii];
        for(int ii = 0; ii < lay; ++ii)
            delete [] layvaluesBkup[ii];
        delete [] layvaluesBkup;  
        layvaluesBkup = NULL;
    }
    else if(varType == CRHM::Int)
    {
        for(int jj = 0; jj<lay; jj++)
            for(int ii = 0; ii<dim; ii++)
                ilayvalues[jj][ii] = ilayvaluesBkup[jj][ii];
        for(int ii = 0; ii < lay; ++ii)
            delete [] ilayvaluesBkup[ii];
        delete [] ilayvaluesBkup; 
        ilayvaluesBkup = NULL;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassPar::Restore() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassPar::ClassPar(string module, string param, CRHM::TDim dimen,string valstr, float minVal, float maxVal,string help, string units, CRHM::TVar varType, int defdim, int Grpdim) : module(module), basemodule(""), param(param), varType(varType), dimen(dimen),valstr(valstr), minVal(minVal), maxVal(maxVal), Inhibit_share(0),help(help), units(units),values(NULL), ivalues(NULL),layvalues(NULL), ilayvalues(NULL), Strings(NULL),layvaluesBkup(NULL), ilayvaluesBkup(NULL), Identical(NULL), StringsBkup(NULL), lay(1)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassPar::ClassPar(stringmodule,stringparam,CRHM::TDimdimen,stringvalstr,floatminVal,floatmaxVal,stringhelp,stringunits,CRHM::TVarvarType,intdefdim,intGrpdim):module(module),basemodule(""),param(param),varType(varType),dimen(dimen),valstr(valstr),minVal(minVal),maxVal(maxVal),Inhibit_share(0),help(help),units(units),values(NULL),ivalues(NULL),layvalues(NULL),ilayvalues(NULL),Strings(NULL),layvaluesBkup(NULL),ilayvaluesBkup(NULL),Identical(NULL),StringsBkup(NULL),lay(1) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(Grpdim == 0 && dimen >= CRHM::NHRU)
        Grpdim = Global::nhru;
    if(dimen == CRHM::NLAY)
    {
        lay = Global::nlay;
        dim = Grpdim;
    }
    else if(dimen == CRHM::NDEF)
    {
        lay = defdim;
        dim = 1; 
    }
    else if(dimen == CRHM::NDEFNZ)
    {
        lay = defdim;
        dim = 1; 
    }
    else if(dimen == CRHM::NDEFN)
    {
        lay = defdim;
        dim = Grpdim; 
    }
    else if(dimen < CRHM::NHRU)
    {
        dim = getdim(dimen); 
        lay = 1;
    }
    else
    {
        dim = Grpdim;
        lay = 1;
    }
    try
    {
        if(varType == CRHM::Float)
        {
            layvalues = new float *[lay];
            for(int ii = 0; ii < lay; ii++)
                layvalues[ii] = new float[dim];
            values = layvalues[0];
        }
        else if(varType == CRHM::Int)
        {
            ilayvalues = new long *[lay];
            for(int ii = 0; ii < lay; ii++)
                ilayvalues[ii] = new long[dim];
            ivalues = ilayvalues[0];
        }
    }
    catch (std::bad_alloc)
    {
        CRHMException Except("Could not allocate in ClassPar.", TERMINATE);
        LogError(Except);
        throw CRHMException(Except);
    }
freopen("c:\\injection.log", "a", stdout); printf("</ClassPar::ClassPar(stringmodule,stringparam,CRHM::TDimdimen,stringvalstr,floatminVal,floatmaxVal,stringhelp,stringunits,CRHM::TVarvarType,intdefdim,intGrpdim):module(module),basemodule(""),param(param),varType(varType),dimen(dimen),valstr(valstr),minVal(minVal),maxVal(maxVal),Inhibit_share(0),help(help),units(units),values(NULL),ivalues(NULL),layvalues(NULL),ilayvalues(NULL),Strings(NULL),layvaluesBkup(NULL),ilayvaluesBkup(NULL),Identical(NULL),StringsBkup(NULL),lay(1) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassPar::ClassPar(ClassPar &p)   
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassPar::ClassPar(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    module = string(p.module);
    basemodule = string(p.basemodule);
    param = string(p.param);
    units = string(p.units);
    help = string(p.help);
    varType = p.varType;
    dimen = p.dimen;
    dim = p.dim;
    lay = p.lay;
    variation_set = p.variation_set;
    visibility = p.visibility;
    Inhibit_share = p.Inhibit_share;
    valstr = string(p.valstr);
    minVal = p.minVal;
    maxVal = p.maxVal;
    layvaluesBkup = NULL;
    ilayvaluesBkup = NULL;
    Strings = NULL;
    ivalues = NULL;
    values = NULL;
    ilayvalues = NULL;
    layvalues = NULL;
    Identical = NULL;
    try
    {
        if(varType == CRHM::Float)
        {
            layvalues = new float *[lay];
            for(int ii = 0; ii < lay; ii++)
                layvalues[ii] = new float[dim];
            values = layvalues[0];
        }
        else if(varType == CRHM::Int)
        {
            ilayvalues = new long *[lay];
            for(int ii = 0; ii < lay; ii++)
                ilayvalues[ii] = new long[dim];
            ivalues = ilayvalues[0];
        }
        else if(varType == CRHM::Txt)
        {
            Strings = new TStringList;
        }
    }
    catch (std::bad_alloc)
    {
        CRHMException Except("Could not allocate in ClassPar.", TERMINATE);
        LogError(Except);
        throw CRHMException(Except);
    }
    if(varType == CRHM::Float)
        for(int jj = 0; jj<lay; jj++)
            for(int ii = 0; ii<dim; ii++)
                layvalues[jj][ii] = p.layvalues[jj][ii];
    else if(varType == CRHM::Int)
        for(int jj = 0; jj<lay; jj++)
            for(int ii = 0; ii<dim; ii++)
                ilayvalues[jj][ii] = p.ilayvalues[jj][ii];
    else if(varType == CRHM::Txt)
        Strings->Assign(p.Strings);
freopen("c:\\injection.log", "a", stdout); printf("</ClassPar::ClassPar(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
bool ClassPar::Same(ClassPar &p)   
{
freopen("c:\\injection.log", "a", stdout); printf("<boolClassPar::Same(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(varType == p.varType && dim == p.dim && param == p.param)
    {
        if(Inhibit_share != 0 || p.Inhibit_share != 0) 
            if(Global::GroupCntTrk)
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassPar::Same(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return(false);}
            else
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassPar::Same(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return(true);}
        if(dim == p.dim)
        {
            if(varType == CRHM::Txt)
            {
                if(!Strings && !p.Strings)
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassPar::Same(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return true;}
                if(Strings->Count != p.Strings->Count)
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassPar::Same(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return(false);}
                for(int ii = 0; ii < Strings->Count; ++ii)
                    if(Strings->Strings[ii] != p.Strings->Strings[ii])
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassPar::Same(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return(false);}
            }
            else
            {
                for(int jj = 0; jj<lay; ++jj)
                    for(int ii = 0; ii<dim; ++ii)
                        if(varType == CRHM::Float)
                        {
                            if(layvalues[jj][ii] != p.layvalues[jj][ii])
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassPar::Same(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return(false);}
                        }
                        else if(varType == CRHM::Int)
                        {
                            if(ilayvalues[jj][ii] != p.ilayvalues[jj][ii])
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassPar::Same(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return(false);}
                        }
            }
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassPar::Same(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return(true);}
        }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassPar::Same(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return(false);}
freopen("c:\\injection.log", "a", stdout); printf("</boolClassPar::Same(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassPar::Change(ClassPar &p)   
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassPar::Change(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(this == &p)
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassPar::Change(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
    if(varType == CRHM::Txt)
    {
        Strings->Assign(p.Strings);
        while(Strings->Count < dim)  
            Strings->Append(Strings->Strings[Strings->Count-1]);
    }
    else
    {
        bool Bang = valstr.find("!") != string::npos;
        for(int jj = 0; jj < lay; ++jj)
        {
            long jj0 = min<long> (jj, p.lay-1);
            for(int ii = 0; ii < dim; ++ii)
            {
                long ii0 = min<long> (ii, p.dim-1);
                if(Bang && ii0 < ii)
                {
                    if(varType == CRHM::Float)
                        layvalues[jj][ii] = layvalues[jj][ii-1] + 1;
                    else if(varType == CRHM::Int)
                        ilayvalues[jj][ii] = ilayvalues[jj][ii-1] + 1;
                }
                else
                {
                    if(varType == CRHM::Float)
                        layvalues[jj][ii] = p.layvalues[jj0][ii0];
                    else if(varType == CRHM::Int)
                        ilayvalues[jj][ii] = p.ilayvalues[jj0][ii0];
                }
            }
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassPar::Change(ClassPar&p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassPar *ClassParFindShared(string name)  
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassPar*ClassParFindShared(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    if((itPar = Global::SharedMapPars.find(name)) == Global::SharedMapPars.end())
    {
        CRHMException Except("Could not find Parameter: " + name, WARNING);
        LogError(Except);
{freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFindShared(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return NULL;}
    }
{freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFindShared(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return ((*itPar).second);}
freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFindShared(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassPar *ClassParFind(string name)  
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassPar*ClassParFind(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    if((itPar = Global::MapPars.find(name)) == Global::MapPars.end())
    {
        CRHMException Except("Could not find Parameter: " + name, WARNING);
        LogError(Except);
{freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFind(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return NULL;}
    }
{freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFind(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return ((*itPar).second);}
freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFind(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassPar *ClassParFindPar(string name)  
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassPar*ClassParFindPar(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *thisPar;
    for(itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); ++itPar)
    {
        thisPar = (*itPar).second;
        if(thisPar->param == name)
{freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFindPar(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return ((*itPar).second);}
    }
{freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFindPar(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return (NULL);}
freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFindPar(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
long ClassParFindParBld(ClassPar *thisPar)  
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassParFindParBld(ClassPar*thisPar) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Mapstr::iterator itPar;                   
    ClassPar *newPar;
    string sparam, smodule;
    long Count = 0;
    for(itPar = Global::Mapdeclpar.begin(); itPar != Global::Mapdeclpar.end(); ++itPar)
    {
        sparam = (itPar->second.first).c_str();
        smodule = (itPar->first).c_str();
        if(sparam == thisPar->param)
        {
            MapPar::iterator itPar0 = Global::MapPars.find(smodule + ' ' + thisPar->param);
            if(itPar0 != Global::MapPars.end()) 
                continue;
            if(Global::OurModulesList->IndexOf(smodule.c_str()) == -1) 
                continue; 
            ++Count;
            ClassPar *newPar= new ClassPar(*thisPar);
            newPar->module = smodule;
            PairPar Item = PairPar(newPar->module + ' ' + newPar->param, newPar);
            Global::MapPars.insert(Item);
        }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassParFindParBld(ClassPar*thisPar) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return (Count);}
freopen("c:\\injection.log", "a", stdout); printf("</longClassParFindParBld(ClassPar*thisPar) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassParSet(ClassPar *p)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassParSet(ClassPar*p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    ClassPar *thisPar;
    if((itPar = Global::MapPars.find("Shared " + p->param)) != Global::MapPars.end())
    {
        thisPar = ((*itPar).second);
        if(thisPar->Same(*p))
        {
            delete p;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassParSet(ClassPar*p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
        }
    }
    if((itPar = Global::MapPars.find(p->module + ' ' + p->param)) != Global::MapPars.end())
    {
        thisPar = ((*itPar).second);
        if(!thisPar->Same(*p) && thisPar->dim == p->dim)
            thisPar->Change(*p);
        delete p;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassParSet(ClassPar*p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
    }
    else
    {
        PairPar Item = PairPar(p->module + ' ' + p->param, p);
        Global::MapPars.insert(Item);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassParSet(ClassPar*p) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassPar *ClassParFind(string module, string param)  
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassPar*ClassParFind(stringmodule,stringparam) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    if((itPar = Global::MapPars.find(module + ' ' + param)) != Global::MapPars.end())
    {
{freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFind(stringmodule,stringparam) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return ((*itPar).second);}
    }
    if((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
{freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFind(stringmodule,stringparam) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return ((*itPar).second);}
    else
    {
        long jj = Global::OldModuleName->IndexOf(module.c_str()); 
        if(jj > -1)
        {
            string s = Global::NewModuleName->Strings[jj].c_str(); 
            if((itPar = Global::MapPars.find(s + ' ' + param)) != Global::MapPars.end())
            {
{freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFind(stringmodule,stringparam) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return ((*itPar).second);}
            }
        }
        LogError(CRHMException("Parameter defined in module: " + param + ", " + module + " not found", WARNING));
{freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFind(stringmodule,stringparam) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return NULL;}
    }
freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFind(stringmodule,stringparam) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassPar *ClassParFindRev(string module, string param)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassPar*ClassParFindRev(stringmodule,stringparam) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    MapPar::iterator itPar;
    if((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
{freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFindRev(stringmodule,stringparam) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return ((*itPar).second);}
    if((itPar = Global::MapPars.find(module + ' ' + param)) != Global::MapPars.end())
    {
{freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFindRev(stringmodule,stringparam) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return ((*itPar).second);}
    }
    else
    {
        LogError(CRHMException("Parameter defined in module: " + param + ", " + module + " not found", TERMINATE));
{freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFindRev(stringmodule,stringparam) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return NULL;}
    }
freopen("c:\\injection.log", "a", stdout); printf("</ClassPar*ClassParFindRev(stringmodule,stringparam) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
__fastcall ClassPar::~ClassPar()
{
freopen("c:\\injection.log", "a", stdout); printf("<__fastcallClassPar::~ClassPar() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(varType == CRHM::Float)
    {
        for(int ii = 0; ii < lay; ++ii)
            delete [] layvalues[ii];
        delete [] layvalues;  
        values = NULL;
    }
    else if(varType == CRHM::Int)
    {
        for(int ii = 0; ii < lay; ++ii)
            delete [] ilayvalues[ii];
        delete [] ilayvalues; 
        ivalues = NULL;
    }
    else if(varType == CRHM::Txt)
    {
        delete Strings;
    }
    varType = CRHM::none;
freopen("c:\\injection.log", "a", stdout); printf("</__fastcallClassPar::~ClassPar() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassVar *ClassVarFind(string name)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassVar*ClassVarFind(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    if((itVar = Global::MapVars.find(name)) == Global::MapVars.end())
        if((itVar = Global::MapVars.find('#' + name)) == Global::MapVars.end())  
        {
            CRHMException Except("Could not find Variable: " + name, WARNING);
            LogError(Except);
{freopen("c:\\injection.log", "a", stdout); printf("</ClassVar*ClassVarFind(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return NULL;}
        }
{freopen("c:\\injection.log", "a", stdout); printf("</ClassVar*ClassVarFind(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return ((*itVar).second);}
freopen("c:\\injection.log", "a", stdout); printf("</ClassVar*ClassVarFind(stringname) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassVar::ClassVar(string module, string name, CRHM::TDim dimen,string help, string units, CRHM::TVar varType, bool PointPlot, int Grpdim, int defdim) : module(module), name(name), DLLName(""), root(""), varType(varType), lay(0), nfreq(false),optional(false), StatVar(false), InGroup(0), visibility(CRHM::USUAL), FunKind(CRHM::FOBS),help(help), units(units), layvalues(NULL), ilayvalues(NULL), dim(0), dimMax(0),values(NULL), ivalues(NULL), offset(0), cnt(0), FileData(NULL), HRU_OBS_indexed(0),UserFunct(NULL), FunctVar(NULL), CustomFunct(NULL), No_ReadVar(0), PointPlot(PointPlot), TchrtOpt(0),dimen(dimen)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassVar::ClassVar(stringmodule,stringname,CRHM::TDimdimen,stringhelp,stringunits,CRHM::TVarvarType,boolPointPlot,intGrpdim,intdefdim):module(module),name(name),DLLName(""),root(""),varType(varType),lay(0),nfreq(false),optional(false),StatVar(false),InGroup(0),visibility(CRHM::USUAL),FunKind(CRHM::FOBS),help(help),units(units),layvalues(NULL),ilayvalues(NULL),dim(0),dimMax(0),values(NULL),ivalues(NULL),offset(0),cnt(0),FileData(NULL),HRU_OBS_indexed(0),UserFunct(NULL),FunctVar(NULL),CustomFunct(NULL),No_ReadVar(0),PointPlot(PointPlot),TchrtOpt(0),dimen(dimen) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(Grpdim == 0)
        Grpdim = Global::nhru;
    if(dimen == CRHM::NLAY)
        lay = Global::nlay;
    else if(dimen == CRHM::NFREQ)
    {
        lay = Global::Freq;
        nfreq = true;
    }
    else if(dimen == CRHM::NDEF)
    {
        lay = defdim;
        dim = 1;
    }
    else if(dimen == CRHM::NDEFN)
    {
        lay = defdim;
        dim = Grpdim;
    }
    else if(dimen == CRHM::NREB)
        lay = Grpdim; 
    else
        lay = 0;
    if(dimen == CRHM::NOBS)
        dim = Global::nobs;
    else
        dim = Grpdim;
    try
    {
        if(varType == CRHM::Float)
        {
            if(lay > 0)
            {
                layvalues = new float *[lay];
                if(!values)
                    values = new float[dim];
                if(dimen != CRHM::NREB)  
                {
                    for(int ii = 0; ii < lay; ii++)
                        layvalues[ii] = new float[dim];
                    values = layvalues[0]; 
                    for(int jj = 0; jj < lay; ++jj)
                        for(int kk = 0; kk < dim; ++kk)
                            layvalues[jj][kk] = 0.0;
                }
            }
            if(lay == 0 || dimen == CRHM::NREB)
            {
                values = new float[dim];
                for(int kk = 0; kk < dim; ++kk)
                    values[kk] = 0.0;
            }
        }
        else if(varType == CRHM::Int)
        {
            if(lay > 0)
            {
                ilayvalues = new long *[lay];
                if(dimen != CRHM::NREB)  
                {
                    for(int ii = 0; ii < lay; ii++)
                        ilayvalues[ii] = new long[dim];
                    ivalues = ilayvalues[0];
                    for(int jj = 0; jj < lay; ++jj)
                        for(int kk = 0; kk < dim; ++kk)
                            ilayvalues[jj][kk] = 0.0;
                }
            }
            if(lay == 0 || dimen == CRHM::NREB)
            {
                ivalues = new long[dim];
                for(int kk = 0; kk < dim; ++kk)
                    ivalues[kk] = 0;
            }
        }
    }
    catch (std::bad_alloc)
    {
        CRHMException Except("Could not allocate in ClassVar.", TERMINATE);
        LogError(Except);
        throw CRHMException(Except);
    }
freopen("c:\\injection.log", "a", stdout); printf("</ClassVar::ClassVar(stringmodule,stringname,CRHM::TDimdimen,stringhelp,stringunits,CRHM::TVarvarType,boolPointPlot,intGrpdim,intdefdim):module(module),name(name),DLLName(""),root(""),varType(varType),lay(0),nfreq(false),optional(false),StatVar(false),InGroup(0),visibility(CRHM::USUAL),FunKind(CRHM::FOBS),help(help),units(units),layvalues(NULL),ilayvalues(NULL),dim(0),dimMax(0),values(NULL),ivalues(NULL),offset(0),cnt(0),FileData(NULL),HRU_OBS_indexed(0),UserFunct(NULL),FunctVar(NULL),CustomFunct(NULL),No_ReadVar(0),PointPlot(PointPlot),TchrtOpt(0),dimen(dimen) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassVar::ClassVar(string module, string name, long dim,string help, string units, CRHM::TVar varType, bool PointPlot) : module(module), name(name), DLLName(""), root(""), varType(varType), dim(dim), dimMax(0), lay(0), nfreq(false),optional(false), StatVar(false), InGroup(0), visibility(CRHM::USUAL), FunKind(CRHM::FOBS),help(help), units(units), layvalues(NULL), ilayvalues(NULL),values(NULL), ivalues(NULL), offset(0), cnt(0), FileData(NULL), HRU_OBS_indexed(0),UserFunct(NULL), FunctVar(NULL), CustomFunct(NULL), No_ReadVar(0), PointPlot(PointPlot), TchrtOpt(0),dimen(CRHM::NHRU)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassVar::ClassVar(stringmodule,stringname,longdim,stringhelp,stringunits,CRHM::TVarvarType,boolPointPlot):module(module),name(name),DLLName(""),root(""),varType(varType),dim(dim),dimMax(0),lay(0),nfreq(false),optional(false),StatVar(false),InGroup(0),visibility(CRHM::USUAL),FunKind(CRHM::FOBS),help(help),units(units),layvalues(NULL),ilayvalues(NULL),values(NULL),ivalues(NULL),offset(0),cnt(0),FileData(NULL),HRU_OBS_indexed(0),UserFunct(NULL),FunctVar(NULL),CustomFunct(NULL),No_ReadVar(0),PointPlot(PointPlot),TchrtOpt(0),dimen(CRHM::NHRU) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    try
    {
        if(varType == CRHM::Float)
            values = new float[dim];
        else if(varType == CRHM::Int)
            ivalues = new long[dim];
    }
    catch (std::bad_alloc)
    {
        CRHMException Except("Could not allocate in ClassVar.", TERMINATE);
        LogError(Except);
        throw CRHMException(Except);
    }
freopen("c:\\injection.log", "a", stdout); printf("</ClassVar::ClassVar(stringmodule,stringname,longdim,stringhelp,stringunits,CRHM::TVarvarType,boolPointPlot):module(module),name(name),DLLName(""),root(""),varType(varType),dim(dim),dimMax(0),lay(0),nfreq(false),optional(false),StatVar(false),InGroup(0),visibility(CRHM::USUAL),FunKind(CRHM::FOBS),help(help),units(units),layvalues(NULL),ilayvalues(NULL),values(NULL),ivalues(NULL),offset(0),cnt(0),FileData(NULL),HRU_OBS_indexed(0),UserFunct(NULL),FunctVar(NULL),CustomFunct(NULL),No_ReadVar(0),PointPlot(PointPlot),TchrtOpt(0),dimen(CRHM::NHRU) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassVar::ReleaseM(bool Keep)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::ReleaseM(boolKeep) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(!values && !ivalues)
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassVar::ReleaseM(boolKeep) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
    if(varType == CRHM::Float || varType == CRHM::ReadF)
    {
        if(lay > 0)
        {
            if(dimen != CRHM::NREB)
                values = NULL;
            if(dimen != CRHM::NREB) 
                for(int ii = 0; ii < lay; ++ii)
                    delete [] layvalues[ii];
            delete [] layvalues;  
            layvalues = NULL;
        }
        if(!Keep && values != NULL)
        {
            delete[] values;
            values = NULL;
        }
    }
    else if(varType == CRHM::Int || varType == CRHM::ReadI)
    {
        if(lay > 0)
        {
            if(dimen != CRHM::NREB)
                ivalues = NULL;
            if(dimen != CRHM::NREB) 
                for(int ii = 0; ii < lay; ++ii)
                    delete [] ilayvalues[ii];
            delete [] ilayvalues;  
            ilayvalues = NULL;
        }
        if(!Keep && ivalues != NULL)
        {
            delete[] ivalues;
            ivalues = NULL;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassVar::ReleaseM(boolKeep) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassVar::ClassVar(const ClassVar & Cl)   
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassVar::ClassVar(constClassVar&Cl) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    module = Cl.module;
    root = Cl.root;
    name = Cl.name;
    help = Cl.help;
    units = Cl.units;
    dim = Cl.dim;
    dimMax = Cl.dimMax;
    variation_set = Cl.variation_set;
    dimen = Cl.dimen;
    lay = Cl.lay;
    varType = Cl.varType;
    visibility = Cl.visibility;
    optional = Cl.optional;
    PointPlot = Cl.PointPlot;
    TchrtOpt = Cl.TchrtOpt;
    VarFunct = Cl.VarFunct;
    StatVar = Cl.StatVar;
    InGroup = Cl.InGroup;
    nfreq = Cl.nfreq;
    FunKind = Cl.FunKind;
    ivalues = NULL;
    ilayvalues = NULL;
    layvalues = NULL;
    offset = Cl.offset;
    cnt = Cl.cnt;
    if(Cl.FileData)
        FileData = new ClassData(*Cl.FileData);
    else
        FileData = NULL;
    HRU_OBS_indexed = Cl.HRU_OBS_indexed;
    UserFunct = Cl.UserFunct;
    FunctVar  = Cl.FunctVar;
    CustomFunct  = Cl.CustomFunct;
    CustomFunctName  = Cl.CustomFunctName;
    No_ReadVar  = Cl.No_ReadVar;
    if(lay > 0)
    {
        layvalues = new float *[lay];
        if(dimen != CRHM::NREB)  
        {
            for(int ii = 0; ii < lay; ii++)
                layvalues[ii] = new float[dim];
            values = layvalues[0];
            for(int jj = 0; jj < lay; ++jj)
                for(int kk = 0; kk < dim; ++kk)
                    layvalues[jj][kk] = 0.0;
        }
    }
    if(lay == 0 || dimen == CRHM::NREB)
    {
        varType = CRHM::Float; 
        values = new float[dim];
        ivalues = NULL;
        for(int kk = 0; kk < dim; ++kk)
            values[kk] = 0.0;
    }
freopen("c:\\injection.log", "a", stdout); printf("</ClassVar::ClassVar(constClassVar&Cl) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassVar & ClassVar::operator=(const ClassVar & Cl)   
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassVar&ClassVar::operator=(constClassVar&Cl) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if (this == &Cl)
{freopen("c:\\injection.log", "a", stdout); printf("</ClassVar&ClassVar::operator=(constClassVar&Cl) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return *this;}
    module = Cl.module;
    root = Cl.root;
    name = Cl.name;
    help = Cl.help;
    units = Cl.units;
    dim = Cl.dim;
    dimMax = Cl.dimMax;
    variation_set = Cl.variation_set;
    dimen = Cl.dimen;
    lay = 0;
    varType = Cl.varType;
    visibility = Cl.visibility;
    optional = Cl.optional;
    PointPlot = Cl.PointPlot;
    TchrtOpt = Cl.TchrtOpt;
    VarFunct = Cl.VarFunct;
    StatVar = Cl.StatVar;
    InGroup = Cl.InGroup;
    nfreq = Cl.nfreq;
    FunKind = Cl.FunKind;
    ivalues = NULL;
    values = NULL;
    ilayvalues = NULL;
    layvalues = NULL;
    offset = Cl.offset;
    cnt = Cl.cnt;
    FileData = Cl.FileData;
    HRU_OBS_indexed = Cl.HRU_OBS_indexed;
    UserFunct = Cl.UserFunct;
    FunctVar  = Cl.FunctVar;
    CustomFunct = Cl.CustomFunct;
    CustomFunctName  = Cl.CustomFunctName;
    No_ReadVar  = Cl.No_ReadVar;
{freopen("c:\\injection.log", "a", stdout); printf("</ClassVar&ClassVar::operator=(constClassVar&Cl) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return *this;}
freopen("c:\\injection.log", "a", stdout); printf("</ClassVar&ClassVar::operator=(constClassVar&Cl) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassVar::review_HRU_OBS(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassVar::review_HRU_OBS(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(name == "t" || name == "t_max" || name == "t_min" || name == "rh" || name == "ea")
        HRU_OBS_indexed = 0;
    else if(name == "p" || name == "ppt")
        HRU_OBS_indexed = 1;
    else if(name == "u")
        HRU_OBS_indexed = 2;
    else if(name == "Qsi" || name == "SunAct" || name == "Qli")
        HRU_OBS_indexed = 3;
    else
        HRU_OBS_indexed = 4;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassVar::review_HRU_OBS(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
double ClassData::Encode24(int D[])
{
freopen("c:\\injection.log", "a", stdout); printf("<doubleClassData::Encode24(intD[]) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    try
    {
        if(D[3] == 24) 

                    EncodeDate((Word)D[0], (Word)D[1], (Word)D[2]) + 1.0;
        else

                    EncodeDate((Word)D[0], (Word)D[1], (Word)D[2]);
    }
    catch(...)
    {
        String S;
        S.sprintf("Invalid Date: \"%5u %3u %3u %3u %3u\" at line: %u", D[0], D[1], D[2], D[3], D[4], Position+1);
        Application->MessageBox(S.c_str(), string("Observation File: " + DataFileName).c_str(), MB_OK);
        throw;
    }
freopen("c:\\injection.log", "a", stdout); printf("</doubleClassData::Encode24(intD[]) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
long ClassData::Veto_Freq(long Freq)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassData::Veto_Freq(longFreq) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    const long OK_Values[14] = {1, 2, 3, 4, 6, 8, 12, 24, 48, 72, 96, 144, 192, 288};
    if(Freq <= 1)
{freopen("c:\\injection.log", "a", stdout); printf("</longClassData::Veto_Freq(longFreq) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return 1;}
    if(Freq >= OK_Values[13])
{freopen("c:\\injection.log", "a", stdout); printf("</longClassData::Veto_Freq(longFreq) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return OK_Values[13];}
    for(int ii = 1; ii < 14; ++ii)
    {
        if(Freq <= OK_Values[ii])
        {
            if((Freq - OK_Values[ii-1]) < (OK_Values[ii] - Freq))
{freopen("c:\\injection.log", "a", stdout); printf("</longClassData::Veto_Freq(longFreq) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return OK_Values[ii-1];}
            else
{freopen("c:\\injection.log", "a", stdout); printf("</longClassData::Veto_Freq(longFreq) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return OK_Values[ii];}
        }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</longClassData::Veto_Freq(longFreq) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return(-1);}
freopen("c:\\injection.log", "a", stdout); printf("</longClassData::Veto_Freq(longFreq) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
bool ClassData::DataReadFile(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<boolClassData::DataReadFile(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    ifstream DataFile;
    ifstream::pos_type Here;
    string Header, Var, Comment;
    istringstream instr;
    bool DecimalTime;
    FirstFile = !Global::DTstart;
    int D[5];
    long jj;
    long MaxLines; 
    bool SparseFlag = false;
    bool LineError = false;
    bool OneLine = false;
    ModN = 1;
    bitset <128> MyBitSet;
    DataFile.open(DataFileName.c_str(), ios_base::in);
    if(!DataFile)
    {
        CRHMException Except("Missing observation " + DataFileName, ERR);
        Application->MessageBox(Except.Message.c_str(),
                                "Project observation file", MB_OK);
        LogError(Except);
        DataFile.close();
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassData::DataReadFile(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return false;}
    }
    getline(DataFile, Description);
    HdrLen = 1;
    myMacro = new Classmacro(this);
    while (!DataFile.eof())
    {
        char c = DataFile.peek();
        if(DataFile.fail())
        {
            CRHMException Except("Errors in observation file header" + DataFileName, ERR);
            Application->MessageBox(Except.Message.c_str(),
                                    "Project observation file", MB_OK);
            LogError(Except);
            DataFile.close();
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassData::DataReadFile(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return false;}
        }
        ++HdrLen;
        if(c == '#')
        {
            getline(DataFile, Comment);
            break;
        }
        if(c == '/')
            getline(DataFile, Comment); 
        else if(c == '$')
        {
            getline(DataFile, Comment);
            myMacro->addfilter(Comment.c_str());
        }
        else   
        {
            if(FilterCnt != 0)
            {
                CRHMException Except("Filters must follow observations in file header " + DataFileName, ERR);
                Application->MessageBox(Except.Message.c_str(),
                                        "Project observation file", MB_OK);
                LogError(Except);
                DataFile.close();
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassData::DataReadFile(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return false;}
            }
            DataFile >> Var ; 
            DataFile >> jj; 
            getline(DataFile, Comment);
            bool negative = false; 
            if(jj < 0)
            {
                jj = labs(jj);
                negative = true;
            }
            ClassVar *ThisVar = declread("obs", Var, jj, DataCnt, this, Comment);
            if(!ThisVar)   
            {
                string S = string("Observation '") + Var + "' defined in earlier observation file";
                CRHMException Except("Observation variable already defined " + DataFileName, ERR);
                Application->MessageBox(S.c_str(), Except.Message.c_str(), MB_OK);
                DataFile.close();
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassData::DataReadFile(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return false;}
            }
            ThisVar->review_HRU_OBS();
            for (int ii = 0; ii < jj; ++ii)
                if(negative)
                    MyBitSet.set(DataCnt + jj -1);
            DataCnt = DataCnt + jj;
        }
    } 
    if(!Simulation)
    {
        do
        {
            Here = DataFile.tellg();
            DataFile >> Dt1;
            if(Dt1 > 3000.0)
                DecimalTime = true;
            else
            {
                DecimalTime = false;
                DataFile.seekg(Here-1);  
                for (int ii = 0; ii < 5; ii++)
                    DataFile >> D[ii];
                Position = HdrLen;
                Dt1 = Encode24(D);
            }
            Dt1 += TimeShiftFilter;
            if(DataFile.eof())
            {
                CRHMException Except("Error in observation file header " + DataFileName, ERR);
                Application->MessageBox(Except.Message.c_str(),
                                        "File observations end early!", MB_OK);
                LogError(Except);
                DataFile.close();
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassData::DataReadFile(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return false;}
            }
            if(Global::DTstart != 0.0 && Dt1 >= Global::DTend)
            {
                CRHMException Except("Error in observation file " + DataFileName, ERR);
                Application->MessageBox(Except.Message.c_str(),
                                        "File observations begin after period!", MB_OK);
                LogError(Except);
                DataFile.close();
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassData::DataReadFile(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return false;}
            }
            getline(DataFile, Var);  
            instr.clear(); 
            instr.str(Var);
            float V;
            long Cols = 0;
            for (;;)
            {
                instr >> V;
                if(instr.fail())
                    break;
                ++Cols;
            }
            if(Cols < DataCnt)
            {
                CRHMException Except("Observation file header Error " + DataFileName, ERR);
                Application->MessageBox(Except.Message.c_str(),
                                        String("Header of file defines more observations than data columns (" + String(Cols) + ")").c_str(), MB_OK);
                LogError(Except);
                DataFile.close();
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassData::DataReadFile(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return false;}
            }
            else if(Cols > DataCnt)
            {
                CRHMException Except("Observation file header Warning - Column count > Data count " + DataFileName, WARNING);
                Application->MessageBox(Except.Message.c_str(),
                                        String("Header of file defines fewer observations than data columns (" + String(Cols) + ")").c_str(), MB_OK);
                LogError(Except);
            }
            char c = DataFile.peek();
            if(DataFile.eof())   
            {
                DataFile.clear();
                CRHMException Except("Observation file: one data line file warning " + DataFileName, WARNING);
                LogError(Except);
                OneLine = true;
                Dt2 = Dt1 + 1.0;
                Freq = 1;
                SparseFlag = true;
                Interval = 0.0;
                break;
            }
        }
        while(Global::DTstart != 0.0 && Global::DTstart > Dt1);
        if(Global::DTstart == 0.0)
            Global::DTstart = floor(Dt1);
        if(!OneLine)
        {
            if(DecimalTime)
                DataFile >> Dt2;
            else
            {
                for (int ii = 0; ii < 5; ii++)
                    DataFile >> D[ii];
                Position = HdrLen + 1;
                Dt2 = Encode24(D);
            }
            Dt2 += TimeShiftFilter;
            Interval = Dt2 - Dt1;
            if(Interval > 1.0)
            {
                Interval = 1.0;
                SparseFlag = true;
            }
            Freq = (1.0/Interval + 0.8*Interval);
            Freq = Veto_Freq(Freq);
            Interval = (double) 1.0/Freq;
            if(FirstFile)
                IndxMin = 0;
            else
            {
                IndxMin = floor((Dt1-Global::DTstart)*Freq+Interval/2.0);
                if(Interval != 1) 
                    --IndxMin;
            }
            double mid = floor(Dt1) + Interval;
            float range = 0.00002;
            if(Dt1 > mid + range || Dt1 < mid - range && Interval < 1.0)  
            {
                CRHMException Except("Observation file WARNING " + DataFileName, ERR);
                Application->MessageBox(Except.Message.c_str(),
                                        "First interval must start at midnight + interval! ", MB_OK);
                LogError(Except);
                if(IndxMin == 0)
                    IndxMin = (Dt1 - floor(Dt1))/Interval - 1;
            }
            DataFile.seekg(0, ios_base::end);
            ifstream::off_type Back = DataFile.tellg() -3;
            char c;
            bool white = true;
            do
            {
                DataFile.seekg(Back--);  
                c = DataFile.get();
                if(white)
                    white = isspace(c);
            }
            while (c != '\n' || white);
            if(DecimalTime)
                DataFile >> Dt2;
            else
            {
                for (int ii = 0; ii < 5; ii++)  
                    DataFile >> D[ii];
                Position = 99998;
                Dt2 = Encode24(D);
            }
        } 
        Dt2 += TimeShiftFilter;
        if(Global::DTend == 0.0)
            Global::DTend = Dt2;  
        if(Global::DTend != 0.0 && Global::DTend < Dt2)
            Dt2 = Global::DTend;
        Lines = ceil((Dt2-Dt1 + 1.0/(Freq*2))* Freq);
        if(SparseFlag && Lines < Global::Freq) 
            Lines = Global::Freq;
        IndxMax = IndxMin + Lines -1;
        DataFile.seekg(Here-1);  
    } 
    try
    {
        Data = new float*[DataCnt + FilterCnt];   
        MaxLines = Lines;
        if(fmodl(Lines, Freq) > 0) 
            MaxLines = (Lines/Freq + 1)*Freq;
        for (int jj = 0; jj < DataCnt + FilterCnt; jj++)
            Data[jj] = new float[MaxLines];
        Times = new double[MaxLines];
    }
    catch (std::bad_alloc)
    {
        CRHMException Except("Could not allocate for observations file: " +
                             DataFileName, ERR);
        LogError(Except);
        Data = NULL;
    }
    myMacro->fixup(); 
    TCursor OriginalCursor = Screen->Cursor;
    Screen->Cursor = crHourGlass;
    Dt1 = floor(Dt1);
    try
    {
        char c;
        double DeltaH = Interval*1.5;
        for (Position = 0; Position < Lines; ++Position)
        {
            if(Position%100 == 0)
            {
                if(!Simulation)
                    Update_Main_Status("Observation Line " + String(Position+1));
                else
                    Update_Main_Status("Simulation Line " + String(Position+1));
                Application->ProcessMessages();
            }
            if(!Simulation)
            {
                if(DecimalTime)
                    DataFile >> Times[Position];
                else
                    for (int ii = 0; ii < 5; ++ii)
                        DataFile >> D[ii];
                if(DataFile.eof())   
                {
                    Lines = Position;
                    break;
                }
                if(!DecimalTime)
                    Times[Position] = Encode24(D);
                Times[Position] += TimeShiftFilter;
                Global::DTnow = Times[Position];
                if(Position != 0 && Times[Position] <= Times[Position-1])
                {
                    String S;
                    S.sprintf("Earlier Date at line: %u+, %5u %3u %3u %3u %3u in observation file ", Position, D[0], D[1], D[2], D[3], D[4]);
                    CRHMException Except(S.c_str() + DataFileName, ERR);
                    Application->MessageBox(S.c_str(), "Error in Observation File", MB_OK);
                    LogError(Except);
                    LineError = true;
                    break;
                }
                for (int ii = 0; ii < DataCnt; ++ii)
                {
                    char c;
                    while(c = DataFile.peek(), c == ' ' || c == '\t')
                        DataFile.get();
                    if(DataFile.peek() == '\n')   
                    {
                        String S = String("Check line ") + String(HdrLen + Position + 1) + String(" for missing columns in ");
                        CRHMException Except(S.c_str() + DataFileName, ERR);
                        if(!SparseFlag)
                        {
                            Application->MessageBox(Except.Message.c_str(),
                                                    "Project observation file - too few columns", MB_OK);
                        }
                        if(FirstFile)  
                        {
                            LogError(Except);
                            LineError = true; 
                        }
                        else if(ii == 0)  
                        {
                            SparseFlag = true;
                            --Position;
                            continue;
                        }
                        else 
                            Data[ii][Position] = -999999;
                    }
                    else
                        DataFile >> Data[ii][Position];
                    if(DataFile.fail())  
                    {
                        String S = String("Faulty data at line ") + String(HdrLen + Position + 1)
                                   + String(" in observation file ");
                        CRHMException Except(S.c_str() + DataFileName, ERR);
                        Application->MessageBox(Except.Message.c_str(),
                                                "Project observation file", MB_OK);
                        LogError(Except);
                        Lines = Position-1;
                        LineError = true;
                        break;
                    } 
                } 
                if(LineError)
                    break;
                if(DataFile.peek() != '\n') 
                    DataFile.ignore(256, '\n');
                if(Position != 0 && Times[Position] >= Times[Position-1] + DeltaH)
                    if(!SparseFlag)
                    {
                        SparseFlag = true;
                        if(FirstFile)
                        {
                            String S;
                            if(DecimalTime)
                                S.sprintf("Discontinuous Date: \"%5f\" at line: %u", Times[Position], Position + HdrLen + 1);
                            else
                                S.sprintf("Discontinuous Date: \"%5u %3u %3u %3u %3u\" at line: %u", D[0], D[1], D[2], D[3], D[4], HdrLen + Position + 1);
                            Application->MessageBox(S.c_str(), string("First file must be Sequential: " + DataFileName).c_str(), MB_OK);
                        }
                    }
            } 
            myMacro->execute(Position);
        } 
    } 
    __finally
    {
        Screen->Cursor = OriginalCursor;
    }
    if(Dt2 > Times[Position - 1] + Interval/2.0 && !SparseFlag && !Simulation)
    {
        String S = String("Interval frequency increases ") + String(" in observation file ");
        CRHMException Except(S.c_str() + DataFileName, ERR);
        Application->MessageBox(Except.Message.c_str(), "Project observation file", MB_OK);
        LogError(Except);
        SparseFlag = true;
    }
    if(Freq > 1 && fmodl(Lines, Freq) > 0 && !SparseFlag)
    {
        CRHMException Except("Last day is incomplete and is padded with 0.0 " + DataFileName, WARNING);
        LogError(Except);
        IndxMax = IndxMin + MaxLines -1;
        for(long ll = Position; ll <= MaxLines - 1; ++ll)
        {
            Times[ll] = Times[ll - 1] + 1.0/Freq;
            Dt2 = Times[ll];
            for(long dd = 0; dd < DataCnt; ++dd)
                Data[dd][ll] = 0.0;
        }
    }
    if(LineError)   
    {
        for (int ii = 0; ii < DataCnt + FilterCnt; ii++)
            if(Data[ii])  
            {
                delete[] Data[ii];
                Data[ii] = NULL;
            }
        delete[] Data;
        Data = NULL;
        delete[] Times;
        Times = NULL;
    }
    else
    {
        if(Lines < Freq)  
            SparseFlag = true;
        if(!SparseFlag)
        {
            delete[] Times;
            Times = NULL;
            if(ForceInterval == 96 && Freq == 144 || ForceInterval == 144 && Freq == 96)  
            {
                String S = String("cannot convert 10 minute interval to 15 minute or vice versa") + String(" in observation file ");
                CRHMException Except(S.c_str() + DataFileName, ERR);
                Application->MessageBox(Except.Message.c_str(), "Project observation file", MB_OK);
                LogError(Except);
                ForceInterval = 0;
            }
            if(ForceInterval != Freq && ForceInterval)
            {
                float Result = 0.0;
                for(int jj = 0; jj < DataCnt + FilterCnt; ++jj)   
                {
                    if(!Data[jj])
                    {
                        continue;
                    }
                    float Divisor = 1.0;
                    long NCnt;
                    float Delta;
                    if(ForceInterval > Freq)  
                    {
                        NCnt = ForceInterval/Freq;
                        float *NewData =  new float [Lines*NCnt];
                        if(!MyBitSet[jj])
                        {
                            for(long ii = 0; ii < Lines*NCnt; ++ii)
                            {
                                long kk = ii%NCnt;
                                if(kk == 0)
                                {
                                    if(ii == 0)
                                    {
                                        Result = Data[jj][ii/NCnt]*Divisor;
                                        Delta = 0.0;
                                    }
                                    else if(ii + NCnt >= Lines*NCnt)
                                    {
                                        Result = Data[jj][ii/NCnt]*Divisor;
                                        Delta = 0.0;
                                    }
                                    else
                                    {
                                        Result = Data[jj][ii/NCnt-1]*Divisor;
                                        Delta = (Data[jj][ii/NCnt] - Data[jj][ii/NCnt-1])*Divisor;
                                    }
                                }
                                NewData[ii] = Result + Delta*(ii%NCnt+1)/NCnt;
                            }
                        }
                        else
                        {
                            Divisor = 1.0/NCnt;
                            for(long ii = 0; ii < Lines*NCnt; ++ii)
                            {
                                long kk = ii%NCnt;
                                if(kk == 0)
                                    Result = Data[jj][ii/NCnt]*Divisor;
                                NewData[ii] = Result;
                            }
                        }
                        delete[] Data[jj];
                        Data[jj] = NewData;
                        if(jj+1 == DataCnt + FilterCnt)
                        {
                            Lines = Lines*NCnt;
                            Freq = Freq*NCnt;
                            Interval = Interval/NCnt;
                            IndxMin *= TimeShiftFilter;
                            IndxMax = IndxMin+Lines-1;
                        }
                    } 
                    else   
                    {
                        long NCnt = Freq/ForceInterval;
                        float *NewData =  new float [Lines/NCnt];
                        if(!MyBitSet[jj])
                            Divisor = NCnt;
                        Result = 0.0;
                        for(long ii = 0; ii < Lines; ++ii)
                        {
                            Result += Data[jj][ii];
                            long kk = ii%NCnt;
                            if(kk == NCnt-1)
                            {
                                NewData[ii/NCnt] = Result/Divisor;
                                Result = 0.0;
                            }
                        }
                        delete[] Data[jj];
                        Data[jj] = NewData;
                    } 
                } 
                if(ForceInterval < Freq)  
                {
                    long NCnt = Freq/ForceInterval;
                    Lines = Lines/NCnt;
                    Freq = Freq/NCnt;
                    Interval = Interval*NCnt;
                    IndxMax = IndxMin+Lines-1;
                }
                myMacro->fixup(); 
            }
        }
        else   
        {
            double *Temp = new double[Lines];
            for(long ii = 0; ii < Lines; ++ii)
                Temp[ii] = Times[ii];
            delete[] Times;
            Times = Temp;
        }
    }
    delete myMacro;
    myMacro = NULL;
    DataFile.close();
{freopen("c:\\injection.log", "a", stdout); printf("</boolClassData::DataReadFile(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return true;}
freopen("c:\\injection.log", "a", stdout); printf("</boolClassData::DataReadFile(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
__fastcall ClassData::~ClassData()
{
freopen("c:\\injection.log", "a", stdout); printf("<__fastcallClassData::~ClassData() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(Times != NULL)
    {
        delete[] Times;
        Times = NULL;
    }
    if(Data != NULL)
    {
        for (int ii = 0; ii < DataCnt + FilterCnt; ii++)
            if(Data[ii])  
            {
                delete[] Data[ii];
                Data[ii] = NULL;
            }
        delete[] Data;
        Data = NULL;
    }
    if(HdrLen == 0)
{freopen("c:\\injection.log", "a", stdout); printf("</__fastcallClassData::~ClassData() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
    if(myMacro)
    {
        delete myMacro;
        myMacro = NULL;
    }
    MapVar::iterator itVar;
    ClassVar *thisVar;
    for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end();)
    {
        thisVar = (*itVar).second;
        if(thisVar->varType == CRHM::Read && thisVar->FileData == this)
        {
            delete thisVar;
            Global::MapVars.erase(itVar++);
        }
        else
            ++itVar;
    }
    for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++)
    {
        thisVar = (*itVar).second;
        if(thisVar->FileData == this && (thisVar->varType == CRHM::ReadF || thisVar->varType == CRHM::ReadI || thisVar->varType == CRHM::Float))
        {
            thisVar->FileData = NULL;
            if(thisVar->varType == CRHM::Float)  
            {
                thisVar->FunctVar = NULL;
                thisVar->CustomFunct = NULL;
                thisVar->CustomFunctName = "";
                continue;
            }
            thisVar->ReleaseM();
            thisVar->dim = 1;
            thisVar->dimMax = 1;
            if(thisVar->DLLName.empty())
                thisVar->cnt = 0;
            thisVar->offset = 0;
            if(thisVar->varType == CRHM::ReadI)
                thisVar->varType = CRHM::Int;
            if(thisVar->varType == CRHM::ReadF)
                thisVar->varType = CRHM::Float;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</__fastcallClassData::~ClassData() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
long julian(char *when)
{
freopen("c:\\injection.log", "a", stdout); printf("<longjulian(char*when) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Word Y,M,D;
    TDateTime DtBegin;
    if(!strcmp(when, "start"))
    {
        ((TDateTime) Global::DTstart).DecodeDate(&Y,&M,&D);
        DtBegin = EncodeDate((Word)Y-1, (Word)12, (Word)31);
{freopen("c:\\injection.log", "a", stdout); printf("</longjulian(char*when) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return  INT(Global::DTstart - DtBegin);}
    }
    else if(!strcmp(when, "end"))
    {
        ((TDateTime) Global::DTend).DecodeDate(&Y,&M,&D);
        DtBegin = EncodeDate((Word)Y-1, (Word)12, (Word)31);
{freopen("c:\\injection.log", "a", stdout); printf("</longjulian(char*when) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return  INT(Global::DTend - DtBegin);}
    }
    else  
    {
        Global::DTnow.DecodeDate(&Y,&M,&D);
        DtBegin = EncodeDate((Word)Y-1, (Word)12, (Word)31);
{freopen("c:\\injection.log", "a", stdout); printf("</longjulian(char*when) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return  INT(Global::DTnow - DtBegin);}
    }
freopen("c:\\injection.log", "a", stdout); printf("</longjulian(char*when) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
long julian(TDateTime DT)
{
freopen("c:\\injection.log", "a", stdout); printf("<longjulian(TDateTimeDT) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Word Y,M,D;
    TDateTime DtBegin;
    DT.DecodeDate(&Y,&M,&D);
    DtBegin = EncodeDate((Word)Y-1, (Word)12, (Word)31);
{freopen("c:\\injection.log", "a", stdout); printf("</longjulian(TDateTimeDT) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return  INT(DT - DtBegin);}
freopen("c:\\injection.log", "a", stdout); printf("</longjulian(TDateTimeDT) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
long MonthDaysCnt(TDateTime DT)
{
freopen("c:\\injection.log", "a", stdout); printf("<longMonthDaysCnt(TDateTimeDT) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Word Y,M,D;
    TDateTime DTNext;
    DT.DecodeDate(&Y,&M,&D);
    ++M;
    if(M > 12)  
    {
        M = 1;
        ++Y;
    }
    DTNext = EncodeDate((Word)Y, (Word)M, (Word)D);
{freopen("c:\\injection.log", "a", stdout); printf("</longMonthDaysCnt(TDateTimeDT) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return  INT(DTNext - DT);}
freopen("c:\\injection.log", "a", stdout); printf("</longMonthDaysCnt(TDateTimeDT) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
float Julian(char *when)
{
freopen("c:\\injection.log", "a", stdout); printf("<floatJulian(char*when) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Word Y,M,D;
    TDateTime DtBegin;
    if(!strcmp(when, "start"))
    {
        ((TDateTime) Global::DTstart).DecodeDate(&Y,&M,&D);
        DtBegin = EncodeDate((Word)Y-1, (Word)12, (Word)31);
{freopen("c:\\injection.log", "a", stdout); printf("</floatJulian(char*when) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return  (Global::DTstart - DtBegin);}
    }
    else if(!strcmp(when, "end"))
    {
        ((TDateTime) Global::DTend).DecodeDate(&Y,&M,&D);
        DtBegin = EncodeDate((Word)Y-1, (Word)12, (Word)31);
{freopen("c:\\injection.log", "a", stdout); printf("</floatJulian(char*when) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return  (Global::DTend - DtBegin);}
    }
    else  
    {
        Global::DTnow.DecodeDate(&Y,&M,&D);
        DtBegin = EncodeDate((Word)Y-1, (Word)12, (Word)31);
{freopen("c:\\injection.log", "a", stdout); printf("</floatJulian(char*when) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return  float((double) Global::DTnow -  DtBegin);}
    }
freopen("c:\\injection.log", "a", stdout); printf("</floatJulian(char*when) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
bool last_timestep(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<boollast_timestep(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(Global::DTindx == Global::DTmax-1)
{freopen("c:\\injection.log", "a", stdout); printf("</boollast_timestep(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return true;}
    else
{freopen("c:\\injection.log", "a", stdout); printf("</boollast_timestep(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return false;}
freopen("c:\\injection.log", "a", stdout); printf("</boollast_timestep(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void dattim(char *type, long *itime)   
{
freopen("c:\\injection.log", "a", stdout); printf("<voiddattim(char*type,long*itime) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Word Year, Month, Day, Hour, Min, Sec, MSec;
    if(type == "start")
    {
        DecodeDate(Global::DTstart, Year, Month, Day);
        DecodeTime(Global::DTstart, Hour, Min, Sec, MSec);
    }
    else if(type == "end")
    {
        DecodeDate(Global::DTend, Year, Month, Day);
        DecodeTime(Global::DTend, Hour, Min, Sec, MSec);
    }
    else
    {
        DecodeDate(Global::DTnow, Year, Month, Day);
        DecodeTime(Global::DTnow, Hour, Min, Sec, MSec);
    }
    itime[0] = Year;
    itime[1] = Month;
    itime[2] = Day;
    itime[3] = Hour;
    itime[4] = Min;
    itime[5] = Sec;
freopen("c:\\injection.log", "a", stdout); printf("</voiddattim(char*type,long*itime) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void dattim(double DT, long *itime)   
{
freopen("c:\\injection.log", "a", stdout); printf("<voiddattim(doubleDT,long*itime) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Word Year, Month, Day, Hour, Min, Sec, MSec;
    DecodeDate(DT, Year, Month, Day);
    DecodeTime(DT, Hour, Min, Sec, MSec);
    itime[0] = Year;
    itime[1] = Month;
    itime[2] = Day;
    itime[3] = Hour;
    itime[4] = Min;
    itime[5] = Sec;
freopen("c:\\injection.log", "a", stdout); printf("</voiddattim(doubleDT,long*itime) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ModVarRemove(MapVar & MapVars)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidModVarRemove(MapVar&MapVars) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    ClassVar *thisVar;
    ClassVar *thisVar2;
    ClassPar *thisPar;
    MapVar::iterator itVar;
    MapVar::iterator itVar2, itVar3;
    MapPar::iterator itPar;
    string S, S2;
    for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++)
    {
        thisVar = (*itVar).second;
        if(thisVar != NULL)
        {
            S = (*itVar).first;
            if(thisVar->varType < CRHM::Read)
            {
                for (itVar2 = Global::MapVars.begin(); itVar2 != Global::MapVars.end(); itVar2++)
                {
                    thisVar2 = (*itVar2).second;
                    if(thisVar2 != NULL)
                    {
                        S2 = (*itVar2).first;
                        if(thisVar == thisVar2)
                            (*itVar2).second = NULL;
                    }
                }
                if(thisVar->module != "")
                    delete thisVar; 
                else
                    S = "Fault";
            }
            else
            {
                if(S != ("obs " + thisVar->name))
                    (*itVar).second = NULL;
            }
        } 
    }  
    for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end();)
    {
        thisVar = (*itVar).second;
        if(thisVar == NULL)
            Global::MapVars.erase(itVar++);
        else
            ++itVar;
    }
    for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++)
    {
        thisVar = (*itVar).second;
        switch(thisVar->varType)
        {
        case CRHM::ReadI:
            if(thisVar->lay > 0)   
            {
                for(int ii = 0; ii < thisVar->lay; ++ii)
                    delete [] thisVar->ilayvalues[ii];
                delete [] thisVar->ilayvalues;  
                thisVar->lay = 0;
                thisVar->ilayvalues = NULL;
            }
            delete []thisVar->ivalues;
            thisVar->ivalues = NULL;
            thisVar->varType = CRHM::Read;
            thisVar->dim = thisVar->cnt;
            break;
        case CRHM::ReadF:
            if(thisVar->lay > 0)   
            {
                for(int ii = 0; ii < thisVar->lay; ++ii)
                    delete [] thisVar->layvalues[ii];
                delete [] thisVar->layvalues;  
                thisVar->lay = 0;
                thisVar->layvalues = NULL;
            }
            delete []thisVar->values;
            thisVar->values = NULL;
            thisVar->varType = CRHM::Read;
            thisVar->dim = thisVar->cnt;
            break;
        case CRHM::Int:
        case CRHM::Float:
            exit(1); 
        }
    }
    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++)
    {
        thisPar = (*itPar).second;
        delete thisPar;
    }
    Global::MapPars.clear();
    Global::SharedMapPars.clear();
freopen("c:\\injection.log", "a", stdout); printf("</voidModVarRemove(MapVar&MapVars) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassVar *declread(string module, string name, long cnt, long offset, ClassData * FileData, string Comment)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassVar*declread(stringmodule,stringname,longcnt,longoffset,ClassData*FileData,stringComment) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    ClassVar *thisVar;
    string s1(module);
    string s2(name);
    string units;
    if(Comment.empty())
        Comment = "No information in observation file";
    else
    {
        units = extract_units(Comment);
    }
    if(cnt > Global::nobs)
    {
        Global::nobs = cnt; 
        Global::maxobs = cnt;
    }
    if((itVar = Global::MapVars.find(s1 + " " + s2)) != Global::MapVars.end())
    {
        thisVar = (*itVar).second;
        if(thisVar->varType >= CRHM::Read)
        {
            LogError(CRHMException("Duplicate Observation variable: " + s1 + " " + s2, ERR));
{freopen("c:\\injection.log", "a", stdout); printf("</ClassVar*declread(stringmodule,stringname,longcnt,longoffset,ClassData*FileData,stringComment) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return NULL;}
        }
        thisVar->FileData = FileData;
        thisVar->cnt = cnt;
        thisVar->offset = offset;
        /*
            if(thisVar->cnt && thisVar->dim != thisVar->cnt) {
              thisVar->ReleaseM(); 
              if(thisVar->lay > 0) {
                thisVar->layvalues = new float *[thisVar->lay];
                for(int ii = 0; ii < thisVar->lay; ii++)
                  thisVar->layvalues[ii] = new float[thisVar->dim];
              }
              thisVar->values = new float[thisVar->dim];
            }
        */
        if(thisVar->varType == CRHM::Int)
            thisVar->varType = CRHM::ReadI;
        if(thisVar->varType == CRHM::Float)
            thisVar->varType = CRHM::ReadF;
{freopen("c:\\injection.log", "a", stdout); printf("</ClassVar*declread(stringmodule,stringname,longcnt,longoffset,ClassData*FileData,stringComment) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return thisVar;}
    }
    thisVar = new ClassVar(module, name, cnt, offset, FileData);
    if(thisVar->name == "p" || thisVar->name == "ppt") 
        thisVar->dimen = CRHM::NHRU;
    thisVar->varType =  CRHM::Read;
    thisVar->units = units;
    thisVar->help = Comment;
    PairVar Item = PairVar(s1+' '+s2, thisVar);
    Global::MapVars.insert(Item);
{freopen("c:\\injection.log", "a", stdout); printf("</ClassVar*declread(stringmodule,stringname,longcnt,longoffset,ClassData*FileData,stringComment) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return thisVar;}
freopen("c:\\injection.log", "a", stdout); printf("</ClassVar*declread(stringmodule,stringname,longcnt,longoffset,ClassData*FileData,stringComment) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classfilter::fixup(void)   
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassfilter::fixup(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    for (int ii = 0; ii < Vs; ++ii)    
    {
        if(!Data[ii])
            Data[ii] = new float *[ObsCnt];
        for(int jj = 0; jj < ObsCnt; ++jj)   
        {
            if(ii == Vs - 1 && DataIndx[ii]+jj < TotalCnt)  
            {
                if(MyObs->Data[TotalCnt+jj]) 
                    delete[] MyObs->Data[TotalCnt+jj];  
                MyObs->Data[TotalCnt+jj] = NULL;    
            }
            int jjj = jj;
            if(jjj > DataObsCnt[ii]-1) 
                jjj = DataObsCnt[ii]-1; 
            float * X =  MyObs->Data[DataIndx[ii]+jjj];
            Data[ii][jj] = X;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassfilter::fixup(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classfilter::readargs()
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassfilter::readargs() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    MapVar::iterator itVar;
    istringstream instr;
    double C;
    string V;
    long ee = args.Pos(")");
    string Comment = (args.SubString(ee+1, args.Length())).c_str();
    if(Comment.empty())
        Comment = "filter";
    args = args.SubString(1, ee-1);
    while(ee = args.Pos(','), ee > 0)
        args[ee] = ' ';
    instr.str(args.c_str());
    long Cnt;
    long IndexC = 0;
    long IndexV = 0;
    string::size_type pp, pp2;
    for (Cnt = 0; Cnt < argtypes.Length(); ++Cnt)   
    {
        instr >> V;
        if(instr.fail())
            break;
        pp = V.find_first_not_of("0123456789 //:.+-Ee_");
        if(pp == string::npos)   
        {
            if(argtypes[Cnt+1] != 'C')
            {
                error("expected constant");
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassfilter::readargs() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
            }
            pp = V.find_first_of("://_");
            if(pp != string::npos)   
            {
                pp2 = V.find_first_of("_");
                if(pp2 == string::npos)
                {
                    if(V[pp] == '/')
                        C = StrToDate(V.c_str());
                    else
                        C = StrToTime(V.c_str());
                }
                else
                {
                    string z(V, 1, pp2-1);
                    C = StrToDate(z.c_str());
                    z.assign(V, pp2+1, V.size());
                    C += double(StrToTime(z.c_str()) - 1.0/Global::Freq);
                }
            }
            else
                C = String(V.c_str()).ToDouble();
            Constants[IndexC++] = C;
        }
        else                 
        {
            if(argtypes[Cnt+1] != 'V')
            {
                error("expecting CONSTANT");
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassfilter::readargs() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
            }
            if((itVar = Global::MapVars.find("obs " + V)) != Global::MapVars.end())
            {
                thisVar = (*itVar).second;
                if(thisVar->varType < CRHM::Read)
                {
                    error("not observation variable");
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassfilter::readargs() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
                }
            }
            else
            {
                error("unknown variable");
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassfilter::readargs() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
            }
            DataIndx[IndexV] = thisVar->offset;
            DataObsCnt[IndexV] = thisVar->dim;
            ++IndexV;
            if(ObsCnt == 0 || thisVar->cnt < ObsCnt) 
                ObsCnt = thisVar->cnt;
        }
    }
    if(Cnt != argtypes.Length())
    {
        error("too few arguments");
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassfilter::readargs() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
    }
    if(Cnt > argtypes.Length())
    {
        error("too many arguments");
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassfilter::readargs() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
    }
    if(!ToVar.IsEmpty())
    {
        TotalCnt = MyObs->DataCnt + MyObs->FilterCnt;
        if(ObsCnt == 0)
            ++ObsCnt; 
        MyObs->FilterCnt += ObsCnt;
        if((itVar = Global::MapVars.find("obs " + string(ToVar.c_str()))) != Global::MapVars.end())
        {
            outVar = (*itVar).second;
            if(outVar->varType >= CRHM::Read)
            {
                DataIndx[Vs-1] = outVar->offset;
                DataObsCnt[Vs-1] = ObsCnt;
                outVar->units = extract_units(Comment);
                outVar->help = Comment;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassfilter::readargs() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
            }
        }
        outVar = declread("obs", ToVar.c_str(), ObsCnt, TotalCnt, MyObs, Comment.c_str()); 
        DataIndx[Vs-1] = TotalCnt;
        DataObsCnt[Vs-1] = ObsCnt;
        outVar->review_HRU_OBS();
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassfilter::readargs() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classfilter::Classfilter(ClassData *MyObs, String ToVar, String args, String argtypes) : MyObs(MyObs), ToVar(ToVar), args(args), argtypes(argtypes),Vs(0), Cs(0), Error(0), ObsCnt(0), TotalCnt(0), FirstTime(true)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classfilter::Classfilter(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):MyObs(MyObs),ToVar(ToVar),args(args),argtypes(argtypes),Vs(0),Cs(0),Error(0),ObsCnt(0),TotalCnt(0),FirstTime(true) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 1; ii < argtypes.Length()+1; ++ii)
    {
        if(argtypes[ii] == 'V')
            Vs++;
        else if(argtypes[ii] == 'C')
            Cs++;
    }
    if(!ToVar.IsEmpty()) 
        ++Vs;
    if(Vs)
    {
        Data = new float **[Vs];  
        for(int ii = 0; ii < Vs; ++ii)
            Data[ii] = NULL;
        DataIndx = new long [Vs];
        DataObsCnt = new long [Vs];
    }
    if(Cs > 0)
        Constants = new double [Cs];
freopen("c:\\injection.log", "a", stdout); printf("</Classfilter::Classfilter(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):MyObs(MyObs),ToVar(ToVar),args(args),argtypes(argtypes),Vs(0),Cs(0),Error(0),ObsCnt(0),TotalCnt(0),FirstTime(true) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classfilter::doFunctions(long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassfilter::doFunctions(longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    for(int jj = 0; jj < ObsCnt; ++jj)
        doFunc(jj, Line);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassfilter::doFunctions(longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classfilter::~Classfilter()
{
freopen("c:\\injection.log", "a", stdout); printf("<Classfilter::~Classfilter() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(Vs > 0)
    {
        if(!Error) 
            for(int jj = 0; jj < Vs; ++jj)
                delete [] Data[jj];
        delete [] Data;
        delete [] DataIndx;
        delete [] DataObsCnt;
    }
    if(Cs > 0)
        delete [] Constants;
freopen("c:\\injection.log", "a", stdout); printf("</Classfilter::~Classfilter() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classfilter::error(String Mess)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassfilter::error(StringMess) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String Mess2 = String(Mess);
    String F = String(String("\"") + typeid(*this).name());
    CRHMException Except(Mess2.c_str(), ERR);
    Application->MessageBox(Mess2.c_str(), String("Error in filter: " + F + "\" in observation file: \"" + MyObs->DataFileName.c_str() + "\"").c_str(), MB_OK);
    LogError(Except);
    Error = true;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassfilter::error(StringMess) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classmacro::addfilter(String Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassmacro::addfilter(StringLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Classfilter *NewFilter;
    String S = Line.SubString(2, Line.Length()).Trim();
    if(Line.SubString(2, 1) == "$")
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassmacro::addfilter(StringLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
    long bb = S.Pos('(');
    long ee;
    for(ee = 1; ee < bb; ++ee)
        if(S.IsDelimiter(" \t", ee))
            break;
    String ToVar = "";
    if(bb > ee)    
        ToVar = S.SubString(1, ee-1);
    else
        ee = 1;      
    S =  S.SubString(ee, Line.Length()).Trim();
    ee = S.Pos('(');
    String Filter = S.SubString(1, ee-1);
    String FilterStuff = S.SubString(ee+1, Line.Length()).Trim();
    if(ToVar.IsEmpty())
    {
        if(Filter == "Sim")
            NewFilter = (Classfilter*) new ClassSim(File, ToVar, FilterStuff);
        else if(Filter == "ForceInterval")
            NewFilter = (Classfilter*) new ClassForce(File, ToVar, FilterStuff);
        else if(Filter == "TimeShift")
            NewFilter = (Classfilter*) new ClassTimeshift(File, ToVar, FilterStuff);
        else
        {
            String Mess = "Filter: '" + Filter + " has no 'to variable'";
            CRHMException Except(Mess.c_str(), ERR);
            Application->MessageBox(Mess.c_str(), "Error in filter in observation file", MB_OK);
            LogError(Except);
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassmacro::addfilter(StringLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
        }
    }
    else if(Filter == "missing")
        NewFilter = (Classfilter*) new ClassMissing(File, ToVar, FilterStuff);
    else if(Filter == "missing0")
        NewFilter = (Classfilter*) new ClassMissing0(File, ToVar, FilterStuff);
    else if(Filter == "missingC")
        NewFilter = (Classfilter*) new ClassMissingC(File, ToVar, FilterStuff);
    else if(Filter == "missingFlag")
        NewFilter = (Classfilter*) new ClassMissingFlag(File, ToVar, FilterStuff);
    else if(Filter == "missingFlagAfter")
        NewFilter = (Classfilter*) new ClassMissingFlagAfter(File, ToVar, FilterStuff);
    else if(Filter == "missingrepl")
        NewFilter = (Classfilter*) new ClassMissingrepl(File, ToVar, FilterStuff);
    else if(Filter == "missinginter")
    {
        NewFilter = (Classfilter*) new ClassMissingInter(File, ToVar, FilterStuff);
        ++Interpolation;
    }
    else if(Filter == "ea")
        NewFilter = (Classfilter*) new Classea(File, ToVar, FilterStuff);
    else if(Filter == "rh")
        NewFilter = (Classfilter*) new Classrh(File, ToVar, FilterStuff);
    else if(Filter == "RH_WtoI")
        NewFilter = (Classfilter*) new ClassRH_WtoI(File, ToVar, FilterStuff);
    else if(Filter == "add")
        NewFilter = (Classfilter*) new Classadd(File, ToVar, FilterStuff);
    else if(Filter == "sub")
        NewFilter = (Classfilter*) new Classsub(File, ToVar, FilterStuff);
    else if(Filter == "mul")
        NewFilter = (Classfilter*) new Classmul(File, ToVar, FilterStuff);
    else if(Filter == "div")
        NewFilter = (Classfilter*) new Classdiv(File, ToVar, FilterStuff);
    else if(Filter == "addV")
        NewFilter = (Classfilter*) new ClassaddV(File, ToVar, FilterStuff);
    else if(Filter == "subV")
        NewFilter = (Classfilter*) new ClasssubV(File, ToVar, FilterStuff);
    else if(Filter == "mulV")
        NewFilter = (Classfilter*) new ClassmulV(File, ToVar, FilterStuff);
    else if(Filter == "divV")
        NewFilter = (Classfilter*) new ClassdivV(File, ToVar, FilterStuff);
    else if(Filter == "refwind")
        NewFilter = (Classfilter*) new Classrefwind(File, ToVar, FilterStuff);
    else if(Filter == "const")
        NewFilter = (Classfilter*) new Classconst(File, ToVar, FilterStuff);
    else if(Filter == "sine")
        NewFilter = (Classfilter*) new Classsin(File, ToVar, FilterStuff); 
    else if(Filter == "sin")
        NewFilter = (Classfilter*) new Classsin(File, ToVar, FilterStuff);
    else if(Filter == "cos")
        NewFilter = (Classfilter*) new Classcos(File, ToVar, FilterStuff);
    else if(Filter == "abs")
        NewFilter = (Classfilter*) new Classabs(File, ToVar, FilterStuff);
    else if(Filter == "square")
        NewFilter = (Classfilter*) new Classsquare(File, ToVar, FilterStuff);
    else if(Filter == "ramp")
        NewFilter = (Classfilter*) new Classramp(File, ToVar, FilterStuff);
    else if(Filter == "pulse")
        NewFilter = (Classfilter*) new Classpulse(File, ToVar, FilterStuff);
    else if(Filter == "exp")
        NewFilter = (Classfilter*) new Classexp(File, ToVar, FilterStuff);
    else if(Filter == "expV")
        NewFilter = (Classfilter*) new Classexpv(File, ToVar, FilterStuff);
    else if(Filter == "log")
        NewFilter = (Classfilter*) new Classlog(File, ToVar, FilterStuff);
    else if(Filter == "logV")
        NewFilter = (Classfilter*) new Classlogv(File, ToVar, FilterStuff);
    else if(Filter == "pow")
        NewFilter = (Classfilter*) new Classpow(File, ToVar, FilterStuff);
    else if(Filter == "powV")
        NewFilter = (Classfilter*) new Classpowv(File, ToVar, FilterStuff);
    else if(Filter == "time")
        NewFilter = (Classfilter*) new Classtime(File, ToVar, FilterStuff);
    else if(Filter == "julian")
        NewFilter = (Classfilter*) new Classjulian(File, ToVar, FilterStuff);
    else if(Filter == "random")
        NewFilter = (Classfilter*) new Classrandom(File, ToVar, FilterStuff);
    else if(Filter == "poly")
        NewFilter = (Classfilter*) new Classpoly(File, ToVar, FilterStuff);
    else if(Filter == "polyV")
        NewFilter = (Classfilter*) new Classpolyv(File, ToVar, FilterStuff);
    else if(Filter == "smear")
        NewFilter = (Classfilter*) new ClassSmear(File, ToVar, FilterStuff);
    else if(Filter == "FtoC")
        NewFilter = (Classfilter*) new ClassFtoC(File, ToVar, FilterStuff);
    else if(Filter == "KtoC")
        NewFilter = (Classfilter*) new ClassKtoC(File, ToVar, FilterStuff);
    else if(Filter == "CtoK")
        NewFilter = (Classfilter*) new ClassCtoK(File, ToVar, FilterStuff);
    else if(Filter == "replace")
        NewFilter = (Classfilter*) new ClassReplace(File, ToVar, FilterStuff);
    else
    {
        String Mess = "Filter: '" + Filter + "' name not recognised";
        CRHMException Except(Mess.c_str(), ERR);
        Application->MessageBox(Mess.c_str(), "Error in filter in observation file", MB_OK);
        LogError(Except);
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassmacro::addfilter(StringLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
    }
    if(!NewFilter->Error)
        FilterList->AddObject(Filter, (TObject*) NewFilter);
    else
        delete NewFilter;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassmacro::addfilter(StringLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classmacro::execute(long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassmacro::execute(longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < FilterList->Count; ii++)
        ((Classfilter*) FilterList->Objects[ii])->doFunctions(Line);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassmacro::execute(longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classmacro::fixup(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassmacro::fixup(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < FilterList->Count; ii++)
        ((Classfilter*) FilterList->Objects[ii])->fixup();
freopen("c:\\injection.log", "a", stdout); printf("</voidClassmacro::fixup(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classmacro::Classmacro(ClassData *File) : File(File), Interpolation(0)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classmacro::Classmacro(ClassData*File):File(File),Interpolation(0) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    FilterList = new TStringList;
    FilterList->Sorted = false;
freopen("c:\\injection.log", "a", stdout); printf("</Classmacro::Classmacro(ClassData*File):File(File),Interpolation(0) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classmacro::~Classmacro()   
{
freopen("c:\\injection.log", "a", stdout); printf("<Classmacro::~Classmacro() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(Interpolation > 0 && FilterList->Count > Interpolation)
        LogError(String("Filter execution occurs before interpolation -> values may be incorrect.") + File->DataFileName.c_str(), WARNING);
    for(int ii = 0; ii < FilterList->Count; ii++)
        delete (Classfilter*) FilterList->Objects[ii];
    delete FilterList;
freopen("c:\\injection.log", "a", stdout); printf("</Classmacro::~Classmacro() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassFtoC::ClassFtoC(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassFtoC::ClassFtoC(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</ClassFtoC::ClassFtoC(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassFtoC::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassFtoC::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = (Data[0][Obs][Line]-32.0)*5.0/9.0;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassFtoC::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassCtoK::ClassCtoK(ClassData *MyObs, String ToVar, String args, String argtypes) :Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassCtoK::ClassCtoK(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</ClassCtoK::ClassCtoK(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassCtoK::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassCtoK::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = (Data[0][Obs][Line]+273.15);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassCtoK::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassReplace::ClassReplace(ClassData *MyObs, String ToVar, String args, String argtypes) :Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassReplace::ClassReplace(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</ClassReplace::ClassReplace(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassReplace::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassReplace::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    long shift = thisVar->FileData->IndxMin;
    for(int Obs = 0; Obs < ObsCnt; ++Obs)
        outVar->FileData->Data[Obs + DataIndx[Vs-1]][Line  + shift] = Data[0][Obs][Line];
freopen("c:\\injection.log", "a", stdout); printf("</voidClassReplace::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassKtoC::ClassKtoC(ClassData *MyObs, String ToVar, String args, String argtypes) :Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassKtoC::ClassKtoC(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</ClassKtoC::ClassKtoC(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassKtoC::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassKtoC::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = (Data[0][Obs][Line]-273.15);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassKtoC::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassTimeshift::ClassTimeshift(ClassData *MyObs, String ToVar, String args, String argtypes) :Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassTimeshift::ClassTimeshift(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
    MyObs->TimeShiftFilter = Constants[0];
freopen("c:\\injection.log", "a", stdout); printf("</ClassTimeshift::ClassTimeshift(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassRH_WtoI::ClassRH_WtoI(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassRH_WtoI::ClassRH_WtoI(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</ClassRH_WtoI::ClassRH_WtoI(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassRH_WtoI::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassRH_WtoI::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    float T =  Data[0][Obs][Line];
    float RH = Data[1][Obs][Line];
    if( T < 0.0)
        Data[Vs-1][Obs][Line] = RH*0.9995*exp(22.452*T/(272.55+T))/exp(17.502*T/(240.97+T));
    else
        Data[Vs-1][Obs][Line] = RH;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassRH_WtoI::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classea::Classea(ClassData *MyObs, String ToVar, String args, String argtypes) :  Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classea::Classea(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classea::Classea(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
double estar(float t) /* Saturation vapour pressure */
{
freopen("c:\\injection.log", "a", stdout); printf("<doubleestar(floatt)/*Saturationvapourpressure*/ @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if (t > 0.0)
{freopen("c:\\injection.log", "a", stdout); printf("</doubleestar(floatt)/*Saturationvapourpressure*/ @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return 0.611 * exp(17.27*t / (t + 237.3));}
    else
{freopen("c:\\injection.log", "a", stdout); printf("</doubleestar(floatt)/*Saturationvapourpressure*/ @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return 0.611 * exp(21.88*t / (t + 265.5));}
freopen("c:\\injection.log", "a", stdout); printf("</doubleestar(floatt)/*Saturationvapourpressure*/ @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classea::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassea::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(Line == MyObs->IndxMax) 
        for(int Obs = 0; Obs < ObsCnt; ++Obs)
            for(long Line = MyObs->IndxMin; Line <= MyObs->IndxMax; ++Line)
                Data[Vs-1][Obs][Line] = estar(Data[0][Obs][Line])* Data[1][Obs][Line]/100.0;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassea::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classabs::Classabs(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classabs::Classabs(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classabs::Classabs(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classabs::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassabs::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = abs(Data[0][Obs][Line]);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassabs::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classrh::Classrh(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classrh::Classrh(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classrh::Classrh(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classrh::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassrh::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = Data[1][Obs][Line]/estar(Data[0][Obs][Line])*100.0;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassrh::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classsin::Classsin(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classsin::Classsin(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classsin::Classsin(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classsin::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClasssin::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(!Error)
    {
        if(FirstTime)
        {
            period = Constants[0]*MyObs->Freq;
            phase = Constants[1]*MyObs->Freq;
            if(Constants[2] > MyObs->Dt1 && Constants[2] < MyObs->Dt2)
                delay = (Constants[2] - MyObs->Dt1)*MyObs->Freq;
            else
                delay = 0;
            if(Constants[3] > 0.0)
            {
                duration = (Constants[3] - MyObs->Dt1)*MyObs->Freq - 1;
                if(duration <= 0)
                    duration = MyObs->IndxMax;
            }
            else
                duration = MyObs->IndxMax;
            FirstTime = false;
        }
        if(Line <= delay || Line > duration)
            Data[Vs-1][Obs][Line] = 0.0;
        else
            Data[Vs-1][Obs][Line] = sin((float(Line)/period-float(phase)/period)*2*M_PI);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClasssin::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classcos::Classcos(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classcos::Classcos(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classcos::Classcos(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classcos::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClasscos::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(!Error)
    {
        if(FirstTime)
        {
            period = Constants[0]*MyObs->Freq;
            phase = Constants[1]*MyObs->Freq;
            if(Constants[2] > MyObs->Dt1 && Constants[2] < MyObs->Dt2)
                delay = (Constants[2] - MyObs->Dt1)*MyObs->Freq;
            else
                delay = 0;
            if(Constants[3] > 0.0)
            {
                duration = (Constants[3] - MyObs->Dt1)*MyObs->Freq - 1;
                if(duration <= 0)
                    duration = MyObs->IndxMax;
            }
            else
                duration = MyObs->IndxMax;
            FirstTime = false;
        }
        if(Line <= delay || Line > duration)
            Data[Vs-1][Obs][Line] = 0.0;
        else
            Data[Vs-1][Obs][Line] = cos((float(Line)/period-float(phase)/period)*2*M_PI);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClasscos::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classramp::Classramp(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classramp::Classramp(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classramp::Classramp(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classramp::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassramp::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(!Error)
    {
        if(FirstTime)
        {
            period = Constants[0]*MyObs->Freq;
            phase = Constants[1]*MyObs->Freq;
            if(Constants[2] > MyObs->Dt1 && Constants[2] < MyObs->Dt2)
                delay = (Constants[2] - MyObs->Dt1)*MyObs->Freq;
            else
                delay = 0;
            if(Constants[3] > 0.0)
            {
                duration = (Constants[3] - MyObs->Dt1)*MyObs->Freq - 1;
                if(duration <= 0)
                    duration = MyObs->IndxMax;
            }
            else
                duration = MyObs->IndxMax;
            FirstTime = false;
        }
        if(Line <= delay || Line > duration)
            Data[Vs-1][Obs][Line] = 0.0;
        else
        {
            Data[Vs-1][Obs][Line] = 0.0;
            float X = fmod(float(Line-delay)/float(period)*2.0, 1.0);
            if(((Line + phase - delay)%period) >= period/2)
                Data[Vs-1][Obs][Line] = 1.0 - X;
            else
                Data[Vs-1][Obs][Line] = X;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassramp::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classsquare::Classsquare(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classsquare::Classsquare(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classsquare::Classsquare(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classsquare::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClasssquare::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(!Error)
    {
        if(FirstTime)
        {
            period = Constants[0]*MyObs->Freq;
            phase = Constants[1]*MyObs->Freq;
            if(Constants[2] > MyObs->Dt1 && Constants[2] < MyObs->Dt2)
                delay = (Constants[2] - MyObs->Dt1)*MyObs->Freq - 1;
            else
                delay = -1;
            if(Constants[3] > 0.0)
            {
                duration = (Constants[3] - MyObs->Dt1)*MyObs->Freq - 1;
                if(duration <= 0)
                    duration = MyObs->IndxMax;
            }
            else
                duration = MyObs->IndxMax;
            FirstTime = false;
        }
        if(Line <= delay || Line > duration)
            Data[Vs-1][Obs][Line] = 0.0;
        else
        {
            if(((Line + phase)%period) >= period/2)
                Data[Vs-1][Obs][Line] = 0.0;
            else
                Data[Vs-1][Obs][Line] = 1.0;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClasssquare::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classpulse::Classpulse(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classpulse::Classpulse(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classpulse::Classpulse(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classpulse::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClasspulse::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(!Error)
    {
        if(FirstTime)
        {
            if(Constants[0] > MyObs->Dt1 && Constants[0] < MyObs->Dt2)
                delay = (Constants[0] - MyObs->Dt1)*MyObs->Freq - 1;
            else
                delay = -1;
            if(Constants[1] > 0.0)
            {
                duration = (Constants[1] - MyObs->Dt1)*MyObs->Freq - 1;
                if(duration <= 0)
                    duration = MyObs->IndxMax;
            }
            else
                duration = MyObs->IndxMax;
            FirstTime = false;
        }
        if(Line <= delay || Line > duration)
            Data[Vs-1][Obs][Line] = 0.0;
        else
            Data[Vs-1][Obs][Line] = 1.0;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClasspulse::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classexp::Classexp(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classexp::Classexp(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classexp::Classexp(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classexp::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassexp::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(!Error)
    {
        if(FirstTime)
        {
            if(Constants[0] > MyObs->Dt1 && Constants[0] < MyObs->Dt2)
                delay = (Constants[0] - MyObs->Dt1)*MyObs->Freq - 1;
            else
                delay = -1;
            if(Constants[1] > 0.0)
            {
                duration = (Constants[1] - MyObs->Dt1)*MyObs->Freq - 1;
                if(duration <= 0)
                    duration = MyObs->IndxMax;
            }
            else
                duration = MyObs->IndxMax;
            A = Constants[2];
            B = Constants[3]/MyObs->Freq;
            FirstTime = false;
        }
        if(Line <= delay || Line > duration)
            Data[Vs-1][Obs][Line] = 0.0;
        else
            Data[Vs-1][Obs][Line] = A*exp(B*(Line - delay - 1));
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassexp::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classexpv::Classexpv(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classexpv::Classexpv(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
    if(!Error)
    {
        A = Constants[0];
        B = Constants[0];
    }
freopen("c:\\injection.log", "a", stdout); printf("</Classexpv::Classexpv(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classexpv::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassexpv::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = A*exp(B*Data[0][Obs][Line]);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassexpv::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classpoly::Classpoly(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classpoly::Classpoly(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classpoly::Classpoly(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classpoly::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClasspoly::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(!Error)
    {
        if(FirstTime)
        {
            if(Constants[0] > MyObs->Dt1 && Constants[0] < MyObs->Dt2)
                delay = (Constants[0] - MyObs->Dt1)*MyObs->Freq - 1;
            else
                delay = -1;
            if(Constants[1] > 0.0)
            {
                duration = (Constants[1] - MyObs->Dt1)*MyObs->Freq - 1;
                if(duration <= 0)
                    duration = MyObs->IndxMax;
            }
            else
                duration = MyObs->IndxMax;
            FirstTime = false;
        }
        if(Line <= delay || Line > duration)
            Data[Vs-1][Obs][Line] = 0.0;
        else
        {
            float x = (Line - delay - 1)/float(MyObs->Freq);
            Data[Vs-1][Obs][Line] = Constants[2] + Constants[3]*x + Constants[4]*x*x
                                    + Constants[5]*x*x*x + Constants[6]*x*x*x*x;
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClasspoly::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classpolyv::Classpolyv(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classpolyv::Classpolyv(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classpolyv::Classpolyv(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classpolyv::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClasspolyv::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    float x = Data[0][Obs][Line];
    Data[Vs-1][Obs][Line] = Constants[0] + Constants[1]*x +
                            Constants[2]*x*x +
                            Constants[3]*x*x*x +
                            Constants[4]*x*x*x*x;
freopen("c:\\injection.log", "a", stdout); printf("</voidClasspolyv::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classlog::Classlog(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classlog::Classlog(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classlog::Classlog(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classlog::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClasslog::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(!Error)
    {
        if(FirstTime)
        {
            if(Constants[0] > MyObs->Dt1 && Constants[0] < MyObs->Dt2)
                delay = (Constants[0] - MyObs->Dt1)*MyObs->Freq - 1;
            else
                delay = -1;
            if(Constants[1] > 0.0)
            {
                duration = (Constants[1] - MyObs->Dt1)*MyObs->Freq - 1;
                if(duration <= 0)
                    duration = MyObs->IndxMax;
            }
            else
                duration = MyObs->IndxMax;
            A = Constants[2];
            B = fabs(Constants[3]);
            FirstTime = false;
        }
        if(Line <= delay || Line > duration)
            Data[Vs-1][Obs][Line] = 0.0;
        else
            Data[Vs-1][Obs][Line] = A*log(B*float(Line - delay)/MyObs->Freq);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClasslog::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classlogv::Classlogv(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classlogv::Classlogv(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
    if(!Error)
    {
        A = fabs(Constants[0]);
        B = fabs(Constants[1]);
    }
freopen("c:\\injection.log", "a", stdout); printf("</Classlogv::Classlogv(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classlogv::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClasslogv::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = A*log(B*Data[0][Obs][Line]);
freopen("c:\\injection.log", "a", stdout); printf("</voidClasslogv::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classpow::Classpow(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classpow::Classpow(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classpow::Classpow(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classpow::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClasspow::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(!Error)
    {
        if(FirstTime)
        {
            if(Constants[0] >= MyObs->Dt1 && Constants[0] <= MyObs->Dt2)
                delay = (Constants[0] - MyObs->Dt1)*MyObs->Freq;
            else
                delay = -1;
            if(Constants[1] > 0.0)
            {
                duration = (Constants[1] - MyObs->Dt1)*MyObs->Freq - 1;
                if(duration <= 0)
                    duration = MyObs->IndxMax;
            }
            else
                duration = MyObs->IndxMax;
            A = Constants[2];
            B = Constants[3];
            FirstTime = false;
        }
        if(Line < delay || Line > duration)
            Data[Vs-1][Obs][Line] = 0.0;
        else
            Data[Vs-1][Obs][Line] = A*pow((Line - delay + 1)/float(MyObs->Freq), B);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClasspow::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classpowv::Classpowv(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classpowv::Classpowv(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
    if(!Error)
    {
        A = Constants[0];
        B = Constants[1];
    }
freopen("c:\\injection.log", "a", stdout); printf("</Classpowv::Classpowv(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classpowv::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClasspowv::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = A*pow(Data[0][Obs][Line], B);
freopen("c:\\injection.log", "a", stdout); printf("</voidClasspowv::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classtime::Classtime(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classtime::Classtime(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classtime::Classtime(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classtime::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClasstime::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(!Error)
    {
        if(FirstTime)
        {
            option = Constants[0];
            if(option)
                start = 0.0;
            else
                start = floor(Global::DTstart);
            FirstTime = false;
        }
        Data[Vs-1][Obs][Line] = start + Line/float(MyObs->Freq);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClasstime::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classjulian::Classjulian(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classjulian::Classjulian(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
    if(!Error)
        option = Constants[0];
freopen("c:\\injection.log", "a", stdout); printf("</Classjulian::Classjulian(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classjulian::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassjulian::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    switch(option)
    {
    case 0 :
        Data[Vs-1][Obs][Line] = julian("now");
        break;
    case 1 :
        Data[Vs-1][Obs][Line] = julian("start");
        break;
    case 2 :
        Data[Vs-1][Obs][Line] = julian("end");
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassjulian::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classrandom::Classrandom(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classrandom::Classrandom(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
    if(!Error)
        srand((unsigned) Constants[0]);
freopen("c:\\injection.log", "a", stdout); printf("</Classrandom::Classrandom(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classrandom::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassrandom::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = (float) rand()/RAND_MAX;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassrandom::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classrefwind::Classrefwind(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classrefwind::Classrefwind(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
    if(!Error)
    {
        float d = Constants[2]*2.0/3.0;  
        float Z = Constants[2]*0.123;    
        Const = log((Constants[1] - d)/Z)/log((Constants[0] - d)/Z);
    }
freopen("c:\\injection.log", "a", stdout); printf("</Classrefwind::Classrefwind(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classrefwind::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassrefwind::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = Data[0][Obs][Line]*Const;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassrefwind::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classadd::Classadd(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classadd::Classadd(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classadd::Classadd(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classadd::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassadd::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = Data[0][Obs][Line] + Constants[0];
freopen("c:\\injection.log", "a", stdout); printf("</voidClassadd::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classsub::Classsub(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classsub::Classsub(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classsub::Classsub(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classsub::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClasssub::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = Data[0][Obs][Line] - Constants[0];
freopen("c:\\injection.log", "a", stdout); printf("</voidClasssub::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classmul::Classmul(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classmul::Classmul(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classmul::Classmul(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classmul::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassmul::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = Data[0][Obs][Line]*Constants[0] ;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassmul::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classdiv::Classdiv(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classdiv::Classdiv(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classdiv::Classdiv(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classdiv::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassdiv::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = Data[0][Obs][Line]/Constants[0] ;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassdiv::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassaddV::ClassaddV(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassaddV::ClassaddV(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</ClassaddV::ClassaddV(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassaddV::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassaddV::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = Data[0][Obs][Line] + Data[1][Obs][Line];
freopen("c:\\injection.log", "a", stdout); printf("</voidClassaddV::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClasssubV::ClasssubV(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClasssubV::ClasssubV(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</ClasssubV::ClasssubV(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClasssubV::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClasssubV::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = Data[0][Obs][Line] - Data[1][Obs][Line];
freopen("c:\\injection.log", "a", stdout); printf("</voidClasssubV::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassmulV::ClassmulV(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassmulV::ClassmulV(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</ClassmulV::ClassmulV(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassmulV::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassmulV::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = Data[0][Obs][Line]*Data[1][Obs][Line];
freopen("c:\\injection.log", "a", stdout); printf("</voidClassmulV::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassdivV::ClassdivV(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassdivV::ClassdivV(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</ClassdivV::ClassdivV(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassdivV::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassdivV::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = Data[0][Obs][Line]/Data[1][Obs][Line];
freopen("c:\\injection.log", "a", stdout); printf("</voidClassdivV::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Classconst::Classconst(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<Classconst::Classconst(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</Classconst::Classconst(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Classconst::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassconst::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Data[Vs-1][Obs][Line] = Constants[0];
freopen("c:\\injection.log", "a", stdout); printf("</voidClassconst::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassSim::ClassSim(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassSim::ClassSim(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
    MyObs->Simulation = true;
    MyObs->Dt1 =  Constants[0];
    MyObs->Dt2 =  Constants[1];
    MyObs->Interval = Constants[2]/24.0;
    MyObs->Freq = 1.0/MyObs->Interval + 1.0/192.0;
    MyObs->Lines = ceil(MyObs->Dt2 - MyObs->Dt1)*MyObs->Freq;
    MyObs->IndxMin = 0;
    MyObs->IndxMax = floor((MyObs->Dt2 - MyObs->Dt1)*MyObs->Freq + MyObs->Interval/2.0) - 1;
    if(Global::DTstart == 0.0)
    {
        Global::DTstart = floor(MyObs->Dt1);
        Global::DTend = floor(MyObs->Dt2);
        Global::DTnow = Global::DTstart;
        Global::Freq = MyObs->Freq;
        Global::Interval = MyObs->Interval;
    }
    if(Global::DTend == 0.0)
        Global::DTend = MyObs->Dt2;
    if(Global::DTend != 0.0 && Global::DTend < MyObs->Dt2)
        MyObs->Dt2 = Global::DTend;
freopen("c:\\injection.log", "a", stdout); printf("</ClassSim::ClassSim(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassSim::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassSim::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassSim::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassForce::ClassForce(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassForce::ClassForce(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
    if(MyObs->FilterCnt > 0)
        error("ForceFilter filter must be the first filter.");
    if(Constants[0] > 288)
        error("ForceFilter filter interval cannot be less than 5 minutes ");
    if(Constants[0] < 1)
        error("ForceFilter filter interval cannot be greater than daily ");
    MyObs->ForceInterval = Constants[0];
freopen("c:\\injection.log", "a", stdout); printf("</ClassForce::ClassForce(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassForce::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassForce::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
freopen("c:\\injection.log", "a", stdout); printf("</voidClassForce::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassSmear::ClassSmear(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes), Minus(false)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassSmear::ClassSmear(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes),Minus(false) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
freopen("c:\\injection.log", "a", stdout); printf("</ClassSmear::ClassSmear(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes),Minus(false) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassSmear::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassSmear::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(FirstTime)
    {
        if(Constants[0] < 0.0)
            Minus = true;
        if(Constants[0] <= 0.0)
            Constants[0] = MyObs->Dt1;
        if(Constants[1] <= 0.0)
            Constants[1] = MyObs->Dt2;
        Constants[0] = MyObs->Dt1 - MyObs->Interval/2.0;
        Constants[1] = MyObs->Dt2 + MyObs->Interval/2.0;
        FirstTime = false;
    }
    double now = MyObs->Dt1 + Line*MyObs->Interval;
    double delta = MyObs->Interval/2.0;
    double now0  = fmod(now, 1.0);
    if(now0 > -delta && now0 < delta)   
    {
        float value = Data[0][Obs][Line-MyObs->Freq+1]/MyObs->Freq;
        if(now > Constants[0] && now < Constants[1] && (Minus && value < 0.0 || !Minus))
        {
            if(value < 0.0)
                value  = -value;
            for(long ii = 0; ii < MyObs->Freq; ++ii)
            {
                if(Line - ii < 0)
                    break; 
                Data[Vs-1][Obs][Line-ii] = value;
            }
        }
        else
        {
            for(long ii = 0; ii < MyObs->Freq; ++ii)
            {
                if(Line - ii < 0)
                    break; 
                Data[Vs-1][Obs][Line-ii] = Data[0][Obs][Line-ii];
            }
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassSmear::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassMissing::ClassMissing(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes), GoodData(NULL)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassMissing::ClassMissing(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes),GoodData(NULL) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
    GoodData = new float[ObsCnt];
freopen("c:\\injection.log", "a", stdout); printf("</ClassMissing::ClassMissing(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes),GoodData(NULL) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassMissing::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassMissing::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    static bool Warned = false;
    if(FirstTime)
    {
        if((Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1]) && !Warned)
        {
            Application->MessageBox(MyObs->DataFileName.c_str(), "Missing data in first interval of filter 'missing'", MB_OK);
            LogError(String("Missing data in first interval of ") + MyObs->DataFileName.c_str(), WARNING);
            Warned = true;
        }
        Data[Vs-1][Obs][Line] = Data[0][Obs][Line];
        GoodData[Obs] = Data[0][Obs][Line];
        if(Obs+1 >= ObsCnt)
            FirstTime = false;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassMissing::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
    }
    if(Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
        Data[Vs-1][Obs][Line] = GoodData[Obs];
    else
    {
        Data[Vs-1][Obs][Line] = Data[0][Obs][Line];
        GoodData[Obs] = Data[0][Obs][Line];
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassMissing::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassMissing::~ClassMissing()
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassMissing::~ClassMissing() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    delete[] GoodData;
freopen("c:\\injection.log", "a", stdout); printf("</ClassMissing::~ClassMissing() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassMissingInter::ClassMissingInter(ClassData *MyObs, String ToVar, String args, String argtypes) : Classfilter(MyObs, ToVar, args, argtypes), GoodData(NULL)
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassMissingInter::ClassMissingInter(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes),GoodData(NULL) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    readargs();
    GoodData = new float[ObsCnt];
    LastGoodData = new long[ObsCnt];
freopen("c:\\injection.log", "a", stdout); printf("</ClassMissingInter::ClassMissingInter(ClassData*MyObs,StringToVar,Stringargs,Stringargtypes):Classfilter(MyObs,ToVar,args,argtypes),GoodData(NULL) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassMissingInter::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassMissingInter::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    static bool Warned = false;
    if(FirstTime)
    {
        if((Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1]) && !Warned)
        {
            Application->MessageBox(MyObs->DataFileName.c_str(), "Missing data in first interval of filter 'missinginter'", MB_OK);
            LogError(String("Missing data in first interval of ") + MyObs->DataFileName.c_str(), WARNING);
            Warned = true;
            LastGoodData[Obs] = -1;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassMissingInter::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
        }
        Data[Vs-1][Obs][Line] = Data[0][Obs][Line];
        GoodData[Obs] = Data[0][Obs][Line];
        LastGoodData[Obs] = Line;
        if(Obs+1 >= ObsCnt)
            FirstTime = false;
{freopen("c:\\injection.log", "a", stdout); printf("</voidClassMissingInter::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
    }
    if(Data[0][Obs][Line] > Constants[0] && Data[0][Obs][Line] < Constants[1])
    {
        if(Line-1 > LastGoodData[Obs] && LastGoodData[Obs] != -1)
        {
            float dif = (Data[0][Obs][Line] - GoodData[Obs])/(Line - LastGoodData[Obs]);
            for (int ii = LastGoodData[Obs]+1; ii < Line; ++ii)
                Data[Vs-1][Obs][ii] = Data[Vs-1][Obs][ii-1] + dif;
        }
        Data[Vs-1][Obs][Line] = Data[0][Obs][Line];
        GoodData[Obs] = Data[0][Obs][Line];
        LastGoodData[Obs] = Line;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidClassMissingInter::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassMissingInter::~ClassMissingInter()
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassMissingInter::~ClassMissingInter() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    delete[] GoodData;
    delete[] LastGoodData;
freopen("c:\\injection.log", "a", stdout); printf("</ClassMissingInter::~ClassMissingInter() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassMissing0::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassMissing0::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
        Data[Vs-1][Obs][Line] = 0.0;
    else
        Data[Vs-1][Obs][Line] = Data[0][Obs][Line];
freopen("c:\\injection.log", "a", stdout); printf("</voidClassMissing0::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassMissingC::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassMissingC::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
        Data[Vs-1][Obs][Line] = Constants[2];
    else
        Data[Vs-1][Obs][Line] = Data[0][Obs][Line];
freopen("c:\\injection.log", "a", stdout); printf("</voidClassMissingC::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassMissingFlagAfter::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassMissingFlagAfter::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(FirstTime)
    {
        First = Line;
        FirstTime = false;
    }
    else
        Last = Line;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassMissingFlagAfter::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassMissingFlag::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassMissingFlag::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
        Data[Vs-1][Obs][Line] = 1.0;
    else
        Data[Vs-1][Obs][Line] = 0.0;
freopen("c:\\injection.log", "a", stdout); printf("</voidClassMissingFlag::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassMissingFlagAfter::~ClassMissingFlagAfter()
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassMissingFlagAfter::~ClassMissingFlagAfter() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    for(int Obs = 0; Obs < ObsCnt; ++Obs)
        for(int Line = First; Line <= Last; ++Line)
        {
            if(Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
                Data[Vs-1][Obs][Line] = 1.0;
            else
                Data[Vs-1][Obs][Line] = 0.0;
        }
freopen("c:\\injection.log", "a", stdout); printf("</ClassMissingFlagAfter::~ClassMissingFlagAfter() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void ClassMissingrepl::doFunc(long Obs, long Line)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidClassMissingrepl::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if(Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
        Data[Vs-1][Obs][Line] = Data[1][Obs][Line];
    else
        Data[Vs-1][Obs][Line] = Data[0][Obs][Line];
freopen("c:\\injection.log", "a", stdout); printf("</voidClassMissingrepl::doFunc(longObs,longLine) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall Update_Main_DIM(CRHM::TDim Dim, long dim)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallUpdate_Main_DIM(CRHM::TDimDim,longdim) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    SendMessage(Global::crhmMain, WM_CRHM_Main_DIM, (unsigned int) Dim, (unsigned int) dim);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallUpdate_Main_DIM(CRHM::TDimDim,longdim) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall Update_Main_Dirty(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallUpdate_Main_Dirty(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    SendMessage(Global::crhmMain, WM_CRHM_Main_DIRTY, (unsigned int) 0, (unsigned int) 0);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallUpdate_Main_Dirty(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
long getdim(CRHM::TDim dimen)
{
freopen("c:\\injection.log", "a", stdout); printf("<longgetdim(CRHM::TDimdimen) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    MapDim::iterator itDim;
    string s;
    switch(dimen)
    {
    case CRHM::BASIN:
{freopen("c:\\injection.log", "a", stdout); printf("</longgetdim(CRHM::TDimdimen) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return ((int) CRHM::ONE);}
    case CRHM::ONE:
    case CRHM::TWO:
    case CRHM::THREE:
    case CRHM::FOUR:
    case CRHM::FIVE:
    case CRHM::SIX:
    case CRHM::SEVEN:
    case CRHM::EIGHT:
    case CRHM::NINE:
    case CRHM::TEN:
    case CRHM::ELEVEN:
    case CRHM::TWELVE:
{freopen("c:\\injection.log", "a", stdout); printf("</longgetdim(CRHM::TDimdimen) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return ((int) dimen);}
    case CRHM::NHRU:
{freopen("c:\\injection.log", "a", stdout); printf("</longgetdim(CRHM::TDimdimen) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return (Global::nhru);}
    case CRHM::NOBS:
{freopen("c:\\injection.log", "a", stdout); printf("</longgetdim(CRHM::TDimdimen) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return (Global::nobs);}
    case CRHM::NLAY:
{freopen("c:\\injection.log", "a", stdout); printf("</longgetdim(CRHM::TDimdimen) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return (Global::nlay);}
    default:
{freopen("c:\\injection.log", "a", stdout); printf("</longgetdim(CRHM::TDimdimen) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return(-1);}
    }
freopen("c:\\injection.log", "a", stdout); printf("</longgetdim(CRHM::TDimdimen) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
long getstep(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<longgetstep(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</longgetstep(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return Global::DTindx - Global::DTmin +1;}
freopen("c:\\injection.log", "a", stdout); printf("</longgetstep(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
bool laststep(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<boollaststep(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</boollaststep(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return (Global::DTindx == Global::DTmax-1);}
freopen("c:\\injection.log", "a", stdout); printf("</boollaststep(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void setdim(CRHM::TDim dimen, long dim)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidsetdim(CRHM::TDimdimen,longdim) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    MapDim::iterator itDim;
    string s;
    switch(dimen)
    {
    case CRHM::NHRU:
        s = "nhru";
        Update_Main_DIM(CRHM::NHRU, dim);
        break;
    case CRHM::NOBS:
        s = "nobs";
        Update_Main_DIM(CRHM::NOBS, dim);
        break;
    case CRHM::NLAY:
        s = "nlay";
        Update_Main_DIM(CRHM::NLAY, dim);
        break;
    default:
{freopen("c:\\injection.log", "a", stdout); printf("</voidsetdim(CRHM::TDimdimen,longdim) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidsetdim(CRHM::TDimdimen,longdim) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogError(CRHMException Except)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogError(CRHMExceptionExcept) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    SendMessage(Global::crhmLog, WM_CRHM_LOG_EXCEPTION, (unsigned int) &Except, 0);
    if(Except.Kind == TERMINATE)
        throw (Except);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogError(CRHMExceptionExcept) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogError(String S, TExcept Kind)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogError(StringS,TExceptKind) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    SendMessage(Global::crhmLog, WM_CRHM_LOG_EXCEPTION1, (unsigned int) &S, (unsigned int) &Kind);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogError(StringS,TExceptKind) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogMessage(const char *S, float V, const char *S2, TExtra Opt)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogMessage(constchar*S,floatV,constchar*S2,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String SS = S + FloatToStrF(V, ffFixed, 10, 4) + " " + S2;
    LogMessage(SS.c_str(), Opt);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogMessage(constchar*S,floatV,constchar*S2,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogMessage(const char *S, float V, TExtra Opt)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogMessage(constchar*S,floatV,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String D, SS;
    switch (Opt)
    {
    case BLANK:
        break;
    case DD :
        D = Global::DTnow.FormatString("yy mm dd ");
        break;
    case DT :
        D = Global::DTnow.FormatString("yy mm dd hh nn ");
        break;
    case TT :
        D = Global::DTnow.FormatString("hh nn ");
    }
    if(Opt == BLANK)
        SS = S + FloatToStrF(V, ffFixed, 10, 4);
    else
        SS = D + S + FloatToStrF(V, ffFixed, 10, 4);
    SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int) &SS, (unsigned int) 0);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogMessage(constchar*S,floatV,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogMessage(const char *S, long V, TExtra Opt)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogMessage(constchar*S,longV,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String D, SS;
    switch (Opt)
    {
    case BLANK:
        break;
    case DD :
        D = Global::DTnow.FormatString("yy mm dd ");
        break;
    case DT :
        D = Global::DTnow.FormatString("yy mm dd hh nn ");
        break;
    case TT :
        D = Global::DTnow.FormatString("hh nn ");
    }
    if(Opt == BLANK)
        SS = S + String(V);
    else
        SS = D + S + String(V);
    SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int) &SS, (unsigned int) 0);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogMessage(constchar*S,longV,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogMessage(const char *S, TExtra Opt)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogMessage(constchar*S,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String D, SS;
    switch (Opt)
    {
    case BLANK:
        break;
    case DD :
        D = Global::DTnow.FormatString("yy mm dd ");
        break;
    case DT :
        D = Global::DTnow.FormatString("yy mm dd hh nn ");
        break;
    case TT :
        D = Global::DTnow.FormatString("hh nn ");
    }
    if(Opt == BLANK)
        SS = S;
    else
        SS = D + S;
    SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int) &SS, (unsigned int) 0);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogMessage(constchar*S,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogMessage(long hh, const char *S, float V, TExtra Opt)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogMessage(longhh,constchar*S,floatV,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String A = String("HRU " + String(hh+1) + ": ");
    String D;
    switch (Opt)
    {
    case BLANK:
        break;
    case DD :
        D = Global::DTnow.FormatString("yy mm dd ");
        break;
    case DT :
        D = Global::DTnow.FormatString("yy mm dd hh nn ");
        break;
    case TT :
        D = Global::DTnow.FormatString("hh nn ");
    }
    String SS = A + D + S + FloatToStrF(V, ffFixed, 10, 4);
    SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int) &SS, (unsigned int) 0);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogMessage(longhh,constchar*S,floatV,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogMessage(long hh, const char *S, long V, TExtra Opt)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogMessage(longhh,constchar*S,longV,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String A = String("HRU " + String(hh+1) + ": ");
    String D;
    switch (Opt)
    {
    case BLANK:
        break;
    case DD :
        D = Global::DTnow.FormatString("yy mm dd ");
        break;
    case DT :
        D = Global::DTnow.FormatString("yy mm dd hh nn ");
        break;
    case TT :
        D = Global::DTnow.FormatString("hh nn ");
    }
    String SS = A + D + S + String(V);
    SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int) &SS, (unsigned int) 0);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogMessage(longhh,constchar*S,longV,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogMessage(long hh, const char *S, TExtra Opt)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogMessage(longhh,constchar*S,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String A = String("HRU " + String(hh+1) + ": ");
    String D;
    switch (Opt)
    {
    case BLANK:
        break;
    case DD :
        D = Global::DTnow.FormatString("yy mm dd ");
        break;
    case DT :
        D = Global::DTnow.FormatString("yy mm dd hh nn ");
        break;
    case TT :
        D = Global::DTnow.FormatString("hh nn ");
    }
    String SS = A + D + S;
    SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int) &SS, (unsigned int) 0);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogMessage(longhh,constchar*S,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogDebug(char *S)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogDebug(char*S) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String SS = S;
    SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int) &SS, (unsigned int) 0);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogDebug(char*S) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogDebug(long h, char *Text, float v)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogDebug(longh,char*Text,floatv) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String S = h+1;
    S += String(Text) + v;
    SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int) &S, (unsigned int) 0);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogDebug(longh,char*Text,floatv) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogDebugD(char *S)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogDebugD(char*S) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String D = Global::DTnow.FormatString("yy mm dd ");
    String SS = D+S;
    SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int) &SS, (unsigned int) 0);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogDebugD(char*S) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogDebugT(char *S)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogDebugT(char*S) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String D = Global::DTnow.FormatString("yy mm dd hh nn ");
    String SS = "yy mm dd hh mm - ";
    SS += D + " - " + S;
    SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int) &SS, (unsigned int) 0);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogDebugT(char*S) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall Update_Main_Status(String S)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallUpdate_Main_Status(StringS) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    SendMessage(Global::crhmMain, WM_CRHM_Main_STATUS, (unsigned int) &S, (unsigned int) 0);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallUpdate_Main_Status(StringS) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogMessage(long hh, const char *S, float V1, float V2, TExtra Opt)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogMessage(longhh,constchar*S,floatV1,floatV2,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String SS = S + FloatToStrF(V1, ffFixed, 10, 4) + ' ' + FloatToStrF(V2, ffFixed, 10, 4);
    LogMessage(hh, SS.c_str(), Opt);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogMessage(longhh,constchar*S,floatV1,floatV2,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogMessage(long hh, const char *S, float V1, float V2, float V3, TExtra Opt)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogMessage(longhh,constchar*S,floatV1,floatV2,floatV3,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String SS = S + FloatToStrF(V1, ffFixed, 10, 4) + " " + FloatToStrF(V2, ffFixed, 10, 4) + " " + FloatToStrF(V3, ffFixed, 10, 4);
    LogMessage(hh, SS.c_str(), Opt);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogMessage(longhh,constchar*S,floatV1,floatV2,floatV3,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogMessageA(long hh, const char *S, float V1, TExtra Opt)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogMessageA(longhh,constchar*S,floatV1,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String SS = S + FloatToStrF(V1, ffFixed, 10, 2);
    LogMessage(hh, SS.c_str(), Opt);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogMessageA(longhh,constchar*S,floatV1,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogMessageA(long hh, const char *S, float V1, const char *S2, TExtra Opt)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogMessageA(longhh,constchar*S,floatV1,constchar*S2,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String SS = S + FloatToStrF(V1, ffFixed, 10, 2) + " " + S2;
    LogMessage(hh, SS.c_str(), Opt);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogMessageA(longhh,constchar*S,floatV1,constchar*S2,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogMessageA(long hh, const char *S, float V1, const float HRU_area, const float Basin_area, TExtra Opt)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogMessageA(longhh,constchar*S,floatV1,constfloatHRU_area,constfloatBasin_area,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String SS = S + FloatToStrF(V1, ffFixed, 10, 2) + " " +
                FloatToStrF(V1*HRU_area, ffFixed, 10, 2) + " " +
                FloatToStrF(V1*HRU_area/Basin_area, ffFixed, 10, 3);
    LogMessage(hh, SS.c_str(), Opt);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogMessageA(longhh,constchar*S,floatV1,constfloatHRU_area,constfloatBasin_area,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogMessageA(long hh, const char *S, float V1, const float HRU_area, const float Basin_area, const char *S2, TExtra Opt)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogMessageA(longhh,constchar*S,floatV1,constfloatHRU_area,constfloatBasin_area,constchar*S2,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String SS = S + FloatToStrF(V1, ffFixed, 10, 2) + " " +
                FloatToStrF(V1*HRU_area, ffFixed, 10, 2) + " " +
                FloatToStrF(V1*HRU_area/Basin_area, ffFixed, 10, 3) + " " + S2;
    LogMessage(hh, SS.c_str(), Opt);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogMessageA(longhh,constchar*S,floatV1,constfloatHRU_area,constfloatBasin_area,constchar*S2,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogMessageA(long hh, const char *S, float V1, const float Basin_area, TExtra Opt)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogMessageA(longhh,constchar*S,floatV1,constfloatBasin_area,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String SS = S + FloatToStrF(V1, ffFixed, 10, 2) + " " +
                FloatToStrF(V1/Basin_area, ffFixed, 10, 3);
    LogMessage(hh, SS.c_str(), Opt);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogMessageA(longhh,constchar*S,floatV1,constfloatBasin_area,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void __fastcall LogMessageA(long hh, const char *S, float V1, const float Basin_area, const char *S2, TExtra Opt)
{
freopen("c:\\injection.log", "a", stdout); printf("<void__fastcallLogMessageA(longhh,constchar*S,floatV1,constfloatBasin_area,constchar*S2,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    String SS = S + FloatToStrF(V1, ffFixed, 10, 2) + " " +
                FloatToStrF(V1/Basin_area, ffFixed, 10, 3) + " " + S2;
    LogMessage(hh, SS.c_str(), Opt);
freopen("c:\\injection.log", "a", stdout); printf("</void__fastcallLogMessageA(longhh,constchar*S,floatV1,constfloatBasin_area,constchar*S2,TExtraOpt) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
long GetSharedUnit(string units)
{
freopen("c:\\injection.log", "a", stdout); printf("<longGetSharedUnit(stringunits) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    const string delims("()/* \t,.-_");
    string::size_type begIdx, endIdx;
    begIdx = units.find_first_not_of(delims);
    while(begIdx != string::npos)
    {
        endIdx = units.find_first_of(delims, begIdx);
        if(endIdx == string::npos)
            endIdx = units.length();
        string name(units.substr(begIdx, endIdx-begIdx));
        if(name == "d")
{freopen("c:\\injection.log", "a", stdout); printf("</longGetSharedUnit(stringunits) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return Global::Freq;}
        else if(name == "int")
{freopen("c:\\injection.log", "a", stdout); printf("</longGetSharedUnit(stringunits) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return 1;}
        begIdx = units.find_first_not_of(delims, endIdx);
    }
{freopen("c:\\injection.log", "a", stdout); printf("</longGetSharedUnit(stringunits) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return 0;}
freopen("c:\\injection.log", "a", stdout); printf("</longGetSharedUnit(stringunits) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
long ClassVar::GetUnit(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassVar::GetUnit(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassVar::GetUnit(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return GetSharedUnit(units);}
freopen("c:\\injection.log", "a", stdout); printf("</longClassVar::GetUnit(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
long ClassPar::GetUnit(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<longClassPar::GetUnit(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</longClassPar::GetUnit(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return GetSharedUnit(units);}
freopen("c:\\injection.log", "a", stdout); printf("</longClassPar::GetUnit(void) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Convert::Convert()
{
freopen("c:\\injection.log", "a", stdout); printf("<Convert::Convert() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    NumUnits = 0;
    NumBasicUnits = 0;
    NumMultipliers = 0;
    while (!(Infos[NumUnits].Abbr).empty())
    {
        if((Infos[NumUnits].Expr).empty())
        {
            Infos[NumUnits].k = NumBasicUnits;
            ++NumBasicUnits;
        }
        ++NumUnits;
    }
    while (Multipliers[NumMultipliers].Abbr)
    {
        ++NumMultipliers;
    }
freopen("c:\\injection.log", "a", stdout); printf("</Convert::Convert() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
Unit_Info Convert::Infos[] =
{

    Unit_Info("1", "1", 1, ""),
    Unit_Info("A", "Ampere", 1, ""),
    Unit_Info("Bq", "becquerel", 1, "l/s"),
    Unit_Info("Btu", "InternationalTableBtu", 1055.05585262, "Kg*m^2/s^2"),
    Unit_Info("C", "Coulomb", 1, "A*s"),
    Unit_Info("Ci", "Curie", 3.7*1010, "l/s"),
    Unit_Info("F", "Farad", 1, "A^2*s^4/Kg*m^2"),
    Unit_Info("Fdy", "Faraday", 96487, "A*s"),
    Unit_Info("Gy", "Gray", 1, "m^2/s^2"),
    Unit_Info("H", "Henry", 1, "Kg*m^2/A^2*s^2"),
    Unit_Info("Hz", "Hertz", 1, "s^-1"),
    Unit_Info("J", "Joule", 1, "Kg*m^2/s^2"),
    Unit_Info("K", "Kelvin", 1, ""),
    Unit_Info("Knot", "NauticalMilesPerHour", 463.0/900.0, "m/s"),
    Unit_Info("N", "Newton", 1, "Kg*m/s^2"),
    Unit_Info("Ohm", "Ohm", 1, "Kg*m^2/A^2*s^3"),
    Unit_Info("OzUK", "UKFluidOunce", 2.8413075e-5, "m^3"),
    Unit_Info("P", "Poise", 0.1, "Kg/m*s"),
    Unit_Info("Pa", "Pascal", 1, "Kg/m*s"),
    Unit_Info("Pdl", "Poundal", 0.13825495376, "Kg*m/s^2"),
    Unit_Info("Pica", "Pica", 1.0/72.0, "in"),
    Unit_Info("R", "Roentgen", 0.000258, "A*s/Kg"),
    Unit_Info("S", "Siemens", 1, "A^2*s^3/Kg*m^2"),
    Unit_Info("St", "Stokes", 0.0001, "m^2/s"),
    Unit_Info("Sv", "Sievert", 1, "m^2/s^2"),
    Unit_Info("T", "Tesla", 1, "Kg/A*s^2"),
    Unit_Info("U", "UnifiedAtomicMass", 1.6605402e-27, "Kg"),
    Unit_Info("V", "Volt", 1, "Kg*m^2/A*s^2"),
    Unit_Info("W", "Watt", 1, "Kg*m^2/s^3"),
    Unit_Info("Wb", "Weber", 1, "Kg*m^2/A*s^2"),
    Unit_Info("acre", "Acre", 4046.87260987, "m^2"),
    Unit_Info("arcmin", "ArcMinute", 2.9088820866e-4, "r"),
    Unit_Info("arcs", "ArcSecond", 4.848136111e-6, "r"),
    Unit_Info("atm", "Attmosphere", 101325, "Kg/m*s^2"),
    Unit_Info("au", "AstronomicalUnit", 1.495979*1011, "m"),
    Unit_Info("b", "Barn", 1e-28, "m^2"),
    Unit_Info("bar", "Bar", 100000, "Kg/m*s^2"),
    Unit_Info("bbl", "Barrel", 0.158987294928, "m^3"),
    Unit_Info("bu", "Bushel", 0.03523907, "m^3"),
    Unit_Info("c", "LightSpeed", 299792458, "m/s"),
    Unit_Info("cal", "Calorie", 4.1868, "Kg*m^2/s^2"),
    Unit_Info("cd", "Candela", 1, ""),
    Unit_Info("chain", "Chain", 20.1168402337, "m"),
    Unit_Info("ct", "Carat", 0.0002, "Kg"),
    Unit_Info("cu", "USCup", 2.365882365e-4, "m^3"),
    Unit_Info("d", "day", 86400, "s"),
    Unit_Info("dyn", "Dyne", 0.00001, "Kg*m/s^2"),
    Unit_Info("eV", "ElectronVolt", 1.60217733e-19, "Kg*m^2/s^2"),
    Unit_Info("erg", "Erg", 0.0000001, "Kg*m^2/s^2"),
    Unit_Info("fath", "Fathom", 1.82880365761, "m"),
    Unit_Info("fbm", "BoardFoot", 0.002359737216, "m^3"),
    Unit_Info("fc", "Footcandle", 10.7639104167, "cd*sr/m^2"),
    Unit_Info("fermi", "Fermi", 1e-15, "m"),
    Unit_Info("flam", "Footlambert", 3.42625909964, "cd/m^2"),
    Unit_Info("ft", "InternationalFoot", 0.3048, "m"),
    Unit_Info("ftUS", "SurveyFoot", 0.304800609601, "m"),
    Unit_Info("g", "Gram", 1, ""),
    Unit_Info("ga", "StandardFreefall", 9.80665, "m/s^2"),
    Unit_Info("gal", "USGallon", 0.003785411784, "m^3"),
    Unit_Info("galC", "CanadianGallon", 0.00454609, "m^3"),
    Unit_Info("galUK", "UKGallon", 0.004546092, "m^3"),
    Unit_Info("gf", "GramForce", 0.00980665, "Kg*m/s^2"),
    Unit_Info("grad", "Grade", 1.57079632679e-2, "r"),
    Unit_Info("grain", "Grain", 0.00006479891, "Kg"),
    Unit_Info("h", "Hour", 3600, "s"),
    Unit_Info("ha", "Hectare", 10000, "m^2"),
    Unit_Info("hp", "horsepower", 745.699871582, "Kg*m^2/s^2"),
    Unit_Info("in", "Inch", 0.0254, "m"),
    Unit_Info("inH2O", "InchesOfWater", 248.84, "Kg/m*s^2"),
    Unit_Info("inHg", "InchesOfMercury", 3386.38815789, "Kg/m*s^2"),
    Unit_Info("int", "CRHM time step", 3600, "s"),
    Unit_Info("kip", "KilopoundForce", 4448.22161526, "Kg*m/s^2"),
    Unit_Info("kph", "KilometersPerHour", 5.0/18.0, "m/s"),
    Unit_Info("l", "Liter", 0.001, "m^3"),
    Unit_Info("lam", "Lambert", 3183.09886184, "cd/m^2"),
    Unit_Info("lb", "AvoirdupoisPound", 0.45359267, "Kg"),
    Unit_Info("lbf", "PoundForce", 4.44822161526, "Kg*m/s^2"),
    Unit_Info("lbt", "TroyPound", 0.3732417216, "Kg"),
    Unit_Info("lm", "Lumen", 1, "cd*sr"),
    Unit_Info("lx", "Lux", 1, "cd*sr/m^2"),
    Unit_Info("lyr", "LightYear", 9.46052840488*1015, "m"),
    Unit_Info("m", "Meter", 1, ""),
    Unit_Info("mho", "Mho", 1, "A^2*s^2/Kg*m^2"),
    Unit_Info("mi", "InternationalMile", 1609.344, "m"),
    Unit_Info("miUS", "USStatuteMile", 1609.34721869, "m"),
    Unit_Info("mil", "Mil", 0.0000254, "m"),
    Unit_Info("min", "Minute", 60, "s"),
    Unit_Info("mmHg", "MilimeterOfMercury", 133.322368421, "Kg/m*s^2"),
    Unit_Info("mol", "Mole", 1, ""),
    Unit_Info("mph", "MilesPerHour", 0.44704, "m/s"),
    Unit_Info("nmi", "NauticalMile", 1852, "m"),
    Unit_Info("oz", "Ounce", 0.028349523125, "Kg"),
    Unit_Info("ozfl", "USFluidOunce", 2.95735295625e-5, "m^3"),
    Unit_Info("ozt", "TroyOunce", 0.0311034768, "Kg"),
    Unit_Info("pc", "Parsec", 3.08567818585106, "m"),
    Unit_Info("ph", "Phot", 10000, "cd*sr/m^2"),
    Unit_Info("pk", "Peck", 0.0088097675, "m^3"),
    Unit_Info("psi", "PoundsPerSquareInch", 6894.75729317, "Kg/m*s^2"),
    Unit_Info("pt", "Pint", 0.000473176473, "m^3"),
    Unit_Info("qt", "Quart", 0.000946352946, "m^3"),
    Unit_Info("r", "Radian", 1, ""),
    Unit_Info("rad", "Rad", 0.01, "m^2/s^2"),
    Unit_Info("rd", "Rod", 5.02921005842, "m"),
    Unit_Info("rem", "Rem", 0.01, "m^2/s^2"),
    Unit_Info("s", "Second", 1, ""),
    Unit_Info("sb", "Stilb", 10000, "cd/m^2"),
    Unit_Info("slug", "Slug", 14.5939029372, "Kg"),
    Unit_Info("sr", "Steradian", 1, ""),
    Unit_Info("st", "Stere", 1, "m^3"),
    Unit_Info("t", "MetricTon", 1000, "Kg"),
    Unit_Info("tbsp", "Tablespoon", 1.47867647813e-5, "m^3"),
    Unit_Info("therm", "EECTherm", 105506000, "Kg*m^2/s^2"),
    Unit_Info("ton", "ShortTon", 907.18474, "Kg"),
    Unit_Info("tonUK", "UKLongTon", 1016.0469088, "Kg"),
    Unit_Info("torr", "Torr", 133.322368421, "Kg/m^2"),
    Unit_Info("tsp", "Teaspoon", 4.92892159375e-6, "m^3"),
    Unit_Info("yd", "InternationalYard", 0.9144, "m"),
    Unit_Info("yr", "Year", 31556925.9747, "s"),
    Unit_Info("�", "Degree", 1.74532925199e-2, "r"),
    Unit_Info("�C", "DegreeCelsius", 1.0, "K"),
    Unit_Info("�F", "DegreesFahrenheit", 1.0/1.8, "K"),
    Unit_Info("�R", "DegreesRankine", 1.0/1.8, "K"),
    Unit_Info("�", "Micron", 1e-6, "m"),
    Unit_Info("�", "Angstrom", 1e-10, "m"),
    Unit_Info("", "", 0, "")
};
Multiplier_Info Convert::Multipliers[] =
{

    Multiplier_Info( 'Y',	"Yotta",   1e+24   ),
    Multiplier_Info( 'Z',	"Zetta",   1e+21   ),
    Multiplier_Info( 'E',	"Exa",     1e+18   ),
    Multiplier_Info( 'P',	"Peta",    1e+15   ),
    Multiplier_Info( 'T',	"Tera",    1e+12   ),
    Multiplier_Info( 'G',	"Giga",    1e+9    ),
    Multiplier_Info( 'M',	"Mega",    1e+6    ),
    Multiplier_Info( 'k',        "kilo",    1e+3    ),
    Multiplier_Info( 'K',        "Kilo",    1e+3    ),
    Multiplier_Info( 'h',        "hecto",   1e+2    ),
    Multiplier_Info( 'H',        "Hecto",   1e+2    ),
    Multiplier_Info( 'D',	"Deka",    1e+1    ),
    Multiplier_Info( 'd',	"deci",    1e-1    ),
    Multiplier_Info( 'c',	"cent",    1e-2    ),
    Multiplier_Info( 'm',	"mili",    1e-3    ),
    Multiplier_Info( 'u',	"micro",   1e-6    ),
    Multiplier_Info( '�',        "micro",   1e-6    ),
    Multiplier_Info( 'n',	"nano",    1e-9    ),
    Multiplier_Info( 'p',	"pico",    1e-12   ),
    Multiplier_Info( 'f',	"femto",   1e-15   ),
    Multiplier_Info( 'a',	"atto",    1e-18   ),
    Multiplier_Info( 'z',	"zepto",   1e-21   ),
    Multiplier_Info( 'y',	"yocto",   1e-24   ),
    Multiplier_Info( '\0',	"",          0.0   )
};
string tcsinc(string pszIn)
{
freopen("c:\\injection.log", "a", stdout); printf("<stringtcsinc(stringpszIn) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
{freopen("c:\\injection.log", "a", stdout); printf("</stringtcsinc(stringpszIn) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return pszIn.substr(1);}
freopen("c:\\injection.log", "a", stdout); printf("</stringtcsinc(stringpszIn) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
string tcsSkipSpaces(string pszIn )
{
freopen("c:\\injection.log", "a", stdout); printf("<stringtcsSkipSpaces(stringpszIn) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    while(pszIn[0] == ' ')
        pszIn = pszIn.substr(1);
{freopen("c:\\injection.log", "a", stdout); printf("</stringtcsSkipSpaces(stringpszIn) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return pszIn;}
freopen("c:\\injection.log", "a", stdout); printf("</stringtcsSkipSpaces(stringpszIn) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
string tcsSqueeze(string pszIn )
{
freopen("c:\\injection.log", "a", stdout); printf("<stringtcsSqueeze(stringpszIn) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    string::iterator pos;
    string::size_type Idx;
    char const Misc[] = {"( )%�\t"};
    Idx = pszIn.find_first_of(Misc);
    while (Idx != string::npos)
    {
        pszIn = pszIn.erase(Idx, 1);
        Idx = pszIn.find_first_of(Misc);
    }
{freopen("c:\\injection.log", "a", stdout); printf("</stringtcsSqueeze(stringpszIn) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return pszIn;}
freopen("c:\\injection.log", "a", stdout); printf("</stringtcsSqueeze(stringpszIn) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
bool Convert::ConvertUnit( double& dValue, string pszSrcUnit, string pszDstUnit)
{
freopen("c:\\injection.log", "a", stdout); printf("<boolConvert::ConvertUnit(double&dValue,stringpszSrcUnit,stringpszDstUnit) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    pszSrcUnit = tcsSkipSpaces( pszSrcUnit );
    pszDstUnit = tcsSkipSpaces( pszDstUnit );
    dValue = 1.0;
    if( pszSrcUnit.compare(pszDstUnit ) == 0 )
{freopen("c:\\injection.log", "a", stdout); printf("</boolConvert::ConvertUnit(double&dValue,stringpszSrcUnit,stringpszDstUnit) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return TRUE;}
    Tresult uSrcUnit(NumBasicUnits);
    try
    {
        pszSrcUnit = ParseDivUnitExpr( pszSrcUnit, uSrcUnit );
    }
    catch(int i)
    {
{freopen("c:\\injection.log", "a", stdout); printf("</boolConvert::ConvertUnit(double&dValue,stringpszSrcUnit,stringpszDstUnit) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return FALSE;}
    }
    Tresult uDstUnit(NumBasicUnits);
    try
    {
        pszDstUnit = ParseDivUnitExpr( pszDstUnit, uDstUnit );
    }
    catch(int i)
    {
{freopen("c:\\injection.log", "a", stdout); printf("</boolConvert::ConvertUnit(double&dValue,stringpszSrcUnit,stringpszDstUnit) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return FALSE;}
    }
    for( int i = 0; i < NumBasicUnits; ++i )
        if( uSrcUnit.aExp[i] != uDstUnit.aExp[i] )
        {
            dValue = -999;
{freopen("c:\\injection.log", "a", stdout); printf("</boolConvert::ConvertUnit(double&dValue,stringpszSrcUnit,stringpszDstUnit) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return FALSE;}
        }
    dValue *= uSrcUnit.k;
    dValue /= uDstUnit.k;
{freopen("c:\\injection.log", "a", stdout); printf("</boolConvert::ConvertUnit(double&dValue,stringpszSrcUnit,stringpszDstUnit) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return TRUE;}
freopen("c:\\injection.log", "a", stdout); printf("</boolConvert::ConvertUnit(double&dValue,stringpszSrcUnit,stringpszDstUnit) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
double Convert::quickPow( double k, int nPow )
{
freopen("c:\\injection.log", "a", stdout); printf("<doubleConvert::quickPow(doublek,intnPow) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    bool bNegative = ( nPow < 0 );
    if( bNegative )
        nPow = -nPow;
    double r = 1.0;
    while( nPow != 0 )
    {
        if( nPow & 1 )
            r *= k;
        k *= k;
        nPow >>= 1;
    }
    if( bNegative )
        r = 1.0 / r;
{freopen("c:\\injection.log", "a", stdout); printf("</doubleConvert::quickPow(doublek,intnPow) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return r;}
freopen("c:\\injection.log", "a", stdout); printf("</doubleConvert::quickPow(doublek,intnPow) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
int Convert::LookupUnit( string pszIn )
{
freopen("c:\\injection.log", "a", stdout); printf("<intConvert::LookupUnit(stringpszIn) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    int iFirst = 0;
    int iLast = NumUnits;
    int i;
    string::size_type Idx;
    Idx = pszIn.find_first_of("*/^");
    if(Idx == string::npos)
        Idx = pszIn.size();
    while( iLast >= iFirst )
    {
        i = ( iLast + iFirst ) / 2;
        int nCmp = pszIn.compare(0, Idx, Infos[i].Abbr);
        if( nCmp == 0 )
{freopen("c:\\injection.log", "a", stdout); printf("</intConvert::LookupUnit(stringpszIn) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return i;}
        if( nCmp < 0 )
            iLast = i - 1;
        else
            iFirst = i + 1;
    }
{freopen("c:\\injection.log", "a", stdout); printf("</intConvert::LookupUnit(stringpszIn) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return -1;}
freopen("c:\\injection.log", "a", stdout); printf("</intConvert::LookupUnit(stringpszIn) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Convert::DivUnit( Tresult& u1, const Tresult& u2 )
{
freopen("c:\\injection.log", "a", stdout); printf("<voidConvert::DivUnit(Tresult&u1,constTresult&u2) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    u1.k /= u2.k;
    for( int i = 0; i < NumBasicUnits; ++i )
        u1.aExp[i] -= u2.aExp[i];
};
void Convert::MulUnit( Tresult& u1, const Tresult& u2 )
{
freopen("c:\\injection.log", "a", stdout); printf("<voidConvert::MulUnit(Tresult&u1,constTresult&u2) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    u1.k *= u2.k;
    for( int i = 0; i < NumBasicUnits; ++i )
        u1.aExp[i] += u2.aExp[i];
};
void Convert::MulUnitK( Tresult& u, double k )
{
freopen("c:\\injection.log", "a", stdout); printf("<voidConvert::MulUnitK(Tresult&u,doublek) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    u.k *= k;
};
void Convert::PowUnit( Tresult& u, char nPow )
{
freopen("c:\\injection.log", "a", stdout); printf("<voidConvert::PowUnit(Tresult&u,charnPow) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    for( int i = 0; i < NumBasicUnits; ++i )
        u.aExp[i] *= nPow;
    u.k = quickPow( u.k, nPow );
};
void Convert::SetBasicUnit( Tresult& u, double k, int iUnit )
{
freopen("c:\\injection.log", "a", stdout); printf("<voidConvert::SetBasicUnit(Tresult&u,doublek,intiUnit) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    u.k = k;
    int iBasicUnit = Infos[iUnit].k;
    if( 0 <= iBasicUnit)
        u.aExp[iBasicUnit] = 1;
freopen("c:\\injection.log", "a", stdout); printf("</voidConvert::SetBasicUnit(Tresult&u,doublek,intiUnit) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Convert::ExpandUnitExpr( Tresult& u, double k, string pszExpr )
{
freopen("c:\\injection.log", "a", stdout); printf("<voidConvert::ExpandUnitExpr(Tresult&u,doublek,stringpszExpr) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    pszExpr = ParseDivUnitExpr( pszExpr, u );
    u.k *= k;
freopen("c:\\injection.log", "a", stdout); printf("</voidConvert::ExpandUnitExpr(Tresult&u,doublek,stringpszExpr) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
string Convert::ParseDivUnitExpr( string pszIn, Tresult& u )
{
freopen("c:\\injection.log", "a", stdout); printf("<stringConvert::ParseDivUnitExpr(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    pszIn = ParseMulUnitExpr( pszIn, u );
    if(pszIn.empty())
{freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParseDivUnitExpr(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return pszIn;}
    string pszMark = pszIn;
    pszIn = tcsSkipSpaces( pszIn );
    if( pszIn[0] != '/' )
        throw 3;
    pszIn = tcsinc( pszIn );
    pszIn = tcsSkipSpaces( pszIn );
    Tresult uAux(NumBasicUnits);
    pszIn = ParseMulUnitExpr( pszIn, uAux );
    DivUnit( u, uAux );
    pszMark = pszIn;
{freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParseDivUnitExpr(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return pszMark;}
freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParseDivUnitExpr(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
string Convert::ParseMulUnitExpr( string pszIn, Tresult& u )
{
freopen("c:\\injection.log", "a", stdout); printf("<stringConvert::ParseMulUnitExpr(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    pszIn = ParsePowUnitExpr( pszIn, u );
    if(pszIn.empty())
{freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParseMulUnitExpr(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return pszIn;}
    string pszMark = pszIn;
    while( pszIn = tcsSkipSpaces( pszIn ), pszIn[0] == '*' )
    {
        pszIn = tcsinc( pszIn );
        Tresult uAux(NumBasicUnits);
        pszIn = ParsePowUnitExpr( pszIn, uAux );
        if( pszIn == "error" )
{freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParseMulUnitExpr(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return pszMark;}
        MulUnit( u, uAux );
        pszMark = pszIn;
    }
{freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParseMulUnitExpr(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return pszIn;}
freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParseMulUnitExpr(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
string Convert::ParsePowUnitExpr( string pszIn, Tresult& u )
{
freopen("c:\\injection.log", "a", stdout); printf("<stringConvert::ParsePowUnitExpr(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    pszIn = ParseUnitPhase1( pszIn, u );
    if(pszIn.empty())
{freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParsePowUnitExpr(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return pszIn;}
    string pszMark = pszIn;
    pszIn = tcsSkipSpaces( pszIn );
    if( pszIn[0] != '^' )
{freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParsePowUnitExpr(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return pszMark;}
    pszIn = tcsinc( pszIn );
    pszIn = tcsSkipSpaces( pszIn );
    bool bNegative = ( pszIn[0] == '-' );
    if( pszIn[0] == '+' || pszIn[0] == '-' )
        pszIn = tcsinc( pszIn );
    if( !_istdigit(pszIn[0]) )
{freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParsePowUnitExpr(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return pszMark;}
    char nPow = 0;
    while( _istdigit(pszIn[0]) )
    {
        char nPow2 = nPow * 10 + ( pszIn[0] - '0' );
        if( nPow2 < nPow )
            break;
        nPow = nPow2;
        pszIn = tcsinc( pszIn );
    }
    if( bNegative )
        nPow = -nPow;
    PowUnit( u, nPow );
{freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParsePowUnitExpr(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return pszIn;}
freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParsePowUnitExpr(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
string Convert::ParseUnitPhase1( string pszIn, Tresult& u )
{
freopen("c:\\injection.log", "a", stdout); printf("<stringConvert::ParseUnitPhase1(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    string pszMark = pszIn;
    pszIn = ParseUnitPhase2( pszIn, u );
    if(pszIn != "????" )
{freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParseUnitPhase1(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return pszIn;}
    pszIn = pszMark;
    double k;
    int ii;
    for(ii = 0; ii < NumMultipliers; ++ii)
        if( pszIn[0] == Multipliers[ii].Abbr )
        {
            k = Multipliers[ii].k;
            break;
        }
    if(ii >= NumMultipliers)
    {
        bool bNegative = ( pszIn[0] == '-' );
        if( pszIn[0] == '+' || pszIn[0] == '-' )
            pszIn = tcsinc( pszIn );
        if(!_istdigit(pszIn[0]) )
            throw 1; 
        else
        {
            k = 0;
            while( _istdigit(pszIn[0]) )
            {
                char nPow2 = k * 10 + ( pszIn[0] - '0' );
                if( nPow2 < k )
                    break;
                k = nPow2;
                pszIn = tcsinc( pszIn );
            }
            if( bNegative )
                k = -k;
            if( pszIn[0] == '*') 
                pszIn = tcsinc( pszIn );
        }
    }
    else
        pszIn = tcsinc( pszIn );
    pszIn = ParseUnitPhase2( pszIn, u );
    MulUnitK( u, k );
{freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParseUnitPhase1(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return pszIn;}
freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParseUnitPhase1(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
string Convert::ParseUnitPhase2( string pszIn, Tresult& u )
{
freopen("c:\\injection.log", "a", stdout); printf("<stringConvert::ParseUnitPhase2(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    int iUnit = LookupUnit( pszIn );
    if( iUnit < 0 )
{freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParseUnitPhase2(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return "????";}
    if( Infos[iUnit].Expr.empty() )
        SetBasicUnit( u, 1.0, iUnit);
    else
        ExpandUnitExpr( u, Infos[iUnit].k, Infos[iUnit].Expr );
    pszIn = pszIn.substr(Infos[iUnit].Abbr.size() );
{freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParseUnitPhase2(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return pszIn;}
freopen("c:\\injection.log", "a", stdout); printf("</stringConvert::ParseUnitPhase2(stringpszIn,Tresult&u) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
bool Convert::CheckUnitsTable()
{
freopen("c:\\injection.log", "a", stdout); printf("<boolConvert::CheckUnitsTable() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    bool bSuccess = TRUE;
    for( int i = 0; i < NumUnits-1; ++i )
    {
        const Unit_Info info1 = Infos[i];
        const Unit_Info info2 = Infos[i+1];
        if( info1.Abbr.compare(info2.Abbr ) >= 0 )
        {
            bSuccess = FALSE;
        }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</boolConvert::CheckUnitsTable() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return bSuccess;}
freopen("c:\\injection.log", "a", stdout); printf("</boolConvert::CheckUnitsTable() @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Convert::CheckUnitsString(string Name, string variable, string units)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidConvert::CheckUnitsString(stringName,stringvariable,stringunits) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    string::size_type Idx;
    string temp(units);
    units = tcsSqueeze(units);
    if(units.empty())
{freopen("c:\\injection.log", "a", stdout); printf("</voidConvert::CheckUnitsString(stringName,stringvariable,stringunits) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return;}
    Tresult uSrcUnit(NumBasicUnits);
    try
    {
        units = ParseDivUnitExpr( units, uSrcUnit );
        if(!units.empty())
        {
            units = temp;
            throw 2;
        }
    }
    catch(int i)
    {
        CRHMException Except("Units error: '" + units + "' in " + Name + ' ' + variable, WARNING);
        LogError(Except);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidConvert::CheckUnitsString(stringName,stringvariable,stringunits) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
void Convert::CheckUnitsObs(string Vunits, string Munits, string declaration)  
{
freopen("c:\\injection.log", "a", stdout); printf("<voidConvert::CheckUnitsObs(stringVunits,stringMunits,stringdeclaration) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    string::size_type Idx;
    double d;
    if(!Vunits.empty())
    {
        if(!ConvertUnit(d, tcsSqueeze(Vunits), tcsSqueeze(Munits)) || d != 1.0)
        {
            CRHMException Except("Units error: '" + Vunits + " instead of " + Munits + "' in "  + declaration, WARNING);
            LogError(Except);
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidConvert::CheckUnitsObs(stringVunits,stringMunits,stringdeclaration) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
long julian_month(long Year, long julian)
{
freopen("c:\\injection.log", "a", stdout); printf("<longjulian_month(longYear,longjulian) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    Word Y, Month, Day;
    TDateTime DT = EncodeDate((Word)Year-1, (Word)12, (Word)31);
    DT += (double) julian;
    DecodeDate(DT, Y, Month, Day);
{freopen("c:\\injection.log", "a", stdout); printf("</longjulian_month(longYear,longjulian) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return Month;}
freopen("c:\\injection.log", "a", stdout); printf("</longjulian_month(longYear,longjulian) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
string extract_units(string& Comment)
{
freopen("c:\\injection.log", "a", stdout); printf("<stringextract_units(string&Comment) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    string Lunits;
    string::size_type Idx, Idx2;
    Idx = Comment.find_first_of("(");
    if(Idx != string::npos)
    {
        Idx2 = Comment.find_first_of(")");
        if(Idx != string::npos)
        {
            Lunits = Comment.substr(Idx, Idx2-Idx+1);
            Comment = Comment.substr(Idx2+1);
            Idx = Comment.find_first_not_of(" \t");
            if(Idx != string::npos)
                Comment = Comment.substr(Idx);
            else
                Comment = "";
        }
    }
{freopen("c:\\injection.log", "a", stdout); printf("</stringextract_units(string&Comment) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return Lunits;}
freopen("c:\\injection.log", "a", stdout); printf("</stringextract_units(string&Comment) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassData::ClassData(const ClassData & Cl)   
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassData::ClassData(constClassData&Cl) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    DataFileName = Cl.DataFileName;
    Description = Cl.Description;
    Dt1 = Cl.Dt1;
    Dt2 = Cl.Dt2;
    Interval = Cl.Interval;
    Lines = Cl.Lines;
    Freq = Cl.Freq;
    IndxMin = Cl.IndxMin;
    IndxMax = Cl.IndxMax;
    ModN = Cl.ModN;
    HdrLen = Cl.HdrLen;
    Position = Cl.Position;
    DataCnt = Cl.DataCnt;
    FilterCnt = Cl.FilterCnt;
    myMacro = Cl.myMacro;
    Simulation = Cl.Simulation;
    ForceInterval = Cl.ForceInterval;
    GoodInterval = Cl.GoodInterval;
    GoodDay = Cl.GoodDay;
    RunUsed = Cl.RunUsed;
    Success = Cl.Success;
    TimeIndx = Cl.TimeIndx;
    FirstFile = Cl.FirstFile;
    Data = new float*[DataCnt + FilterCnt];   
    for (int jj = 0; jj < DataCnt + FilterCnt; ++jj)
        Data[jj] = new float[Lines];
    for (int jj = 0; jj < DataCnt + FilterCnt; ++jj)
        for (int kk = 0; kk < Lines; ++kk)
            Data[jj][kk];
    if(Cl.Times)
    {
        Times = new double[Lines];
        for(long ii = 0; ii < Lines; ++ii)
            Times[ii] = Cl.Times[ii];
    }
    else
        Times = NULL;
freopen("c:\\injection.log", "a", stdout); printf("</ClassData::ClassData(constClassData&Cl) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
ClassData & ClassData::operator=(const ClassData & Cl)   
{
freopen("c:\\injection.log", "a", stdout); printf("<ClassData&ClassData::operator=(constClassData&Cl) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
    if (this == &Cl)
{freopen("c:\\injection.log", "a", stdout); printf("</ClassData&ClassData::operator=(constClassData&Cl) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);return *this;}
    DataFileName = Cl.DataFileName;
    Description = Cl.Description;
    Dt1 = Cl.Dt1;
    Dt2 = Cl.Dt2;
    Interval = Cl.Interval;
    Lines = Cl.Lines;
    Freq = Cl.Freq;
    IndxMin = Cl.IndxMin;
    IndxMax = Cl.IndxMax;
    ModN = Cl.ModN;
    HdrLen = Cl.HdrLen;
    Position = Cl.Position;
    DataCnt = Cl.DataCnt;
    FilterCnt = Cl.FilterCnt;
    myMacro = Cl.myMacro;
    Simulation = Cl.Simulation;
    ForceInterval = Cl.ForceInterval;
    GoodInterval = Cl.GoodInterval;
    GoodDay = Cl.GoodDay;
    RunUsed = Cl.RunUsed;
    Success = Cl.Success;
    TimeIndx = Cl.TimeIndx;
    FirstFile = Cl.FirstFile;
    Data = new float*[DataCnt + FilterCnt];   
    for (int jj = 0; jj < DataCnt + FilterCnt; ++jj)
        Data[jj] = new float[Lines];
    for (int jj = 0; jj < DataCnt + FilterCnt; ++jj)
        for (int kk = 0; kk < Lines; ++kk)
            Data[jj][kk];
    if(Cl.Times)
    {
        Times = new double[Lines];
        for(long ii = 0; ii < Lines; ++ii)
            Times[ii] = Cl.Times[ii];
    }
    else
        Times = NULL;
freopen("c:\\injection.log", "a", stdout); printf("</ClassData&ClassData::operator=(constClassData&Cl) @@@ ClassCRHM.cpp_nocom>\n"); fclose(stdout);
}
