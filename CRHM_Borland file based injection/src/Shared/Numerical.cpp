#include <vcl.h>
#include <String>
#include <Math.hpp>
#include "DefCRHMGlobal.h"
#pragma hdrstop
#include "Numerical.h"
using namespace std;
using namespace Numerical;
#pragma package(smart_init)
void Poly::Transform(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidPoly::Transform(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    float XDataMin, XDataMax;
    Off = XData[0];
    if(OffsetTime)
        for (int ii = 0; ii < NumPoints; ++ii)
            XData[ii] = XData[ii] - Off;
    XDataMax = XData[0];
    XDataMin = XData[0];
    for (int ii = 0; ii < NumPoints; ++ii)
    {
        if(XDataMin > XData[ii])
            XDataMin = XData[ii];
        if(XDataMax < XData[ii])
            XDataMax = XData[ii];
    }
    Multiplier = 2.0 / (XDataMax - XDataMin);
    Constant = - Multiplier * (XDataMax + XDataMin) / 2.0;
    for (int ii = 0; ii < NumPoints; ++ii)
    {
        WData[ii] = Multiplier * XData[ii] + Constant;
        ZData[ii] = YData[ii];
    }
    Y << YData;
freopen("c:\\injection.log", "a", stdout); printf("</voidPoly::Transform(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Poly::InverseTransform(int Index)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidPoly::InverseTransform(intIndex) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    if(OffsetTime)
        XData[Index] = XData[Index] + Off;
freopen("c:\\injection.log", "a", stdout); printf("</voidPoly::InverseTransform(intIndex) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Poly::CreateBasisFunctions(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidPoly::CreateBasisFunctions(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    for(int Row = 0; Row < NumPoints; ++Row)
    {
        X(Row+1, 1) = 1.0;
        X(Row+1, 2) = WData[Row];
        for(int Column = 2; Column < NumTerms; ++Column)
            X(Row+1, Column+1) = 2 * WData[Row] * X(Row+1, Column)
                                 - X(Row+1, Column-1);
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidPoly::CreateBasisFunctions(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Poly::TransformSolution(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidPoly::TransformSolution(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    float Sum;
    float *ConversionVec = new float [NumTerms];
    float *OldConversionVec = new float [NumTerms];
    float *OldSolution = new float [NumTerms];
    for(int ii = 0; ii < NumTerms; ++ii)
    {
        OldConversionVec[ii] = 0.0;
        OldSolution[ii] = Solution[ii];
    }
    for(int Index = 0; Index < NumTerms; ++Index)
    {
        Sum = 0;
        if(Index > 0)
            ConversionVec[Index - 1] = 0;
        for(int Term = Index; Term < NumTerms; ++Term)
        {
            if(Term == 0)
                ConversionVec[Term] = 1.0;
            else
            {
                if(Term == 1)
                {
                    if(Index == 0)
                        ConversionVec[Term] = Constant;
                    else
                        ConversionVec[Term] = Multiplier;
                }
                else
                    ConversionVec[Term] = 2*Multiplier*OldConversionVec[Term - 1] + 2*Constant*ConversionVec[Term - 1] - ConversionVec[Term - 2];
            }
            Sum = Sum + ConversionVec[Term] * OldSolution[Term];
        }
        Solution[Index] = Sum;
        for(int ii = 0; ii < NumTerms; ++ii)
            OldConversionVec[ii] = ConversionVec[ii];
    }
    delete[] ConversionVec;
    delete[] OldConversionVec;
    delete[] OldSolution;
freopen("c:\\injection.log", "a", stdout); printf("</voidPoly::TransformSolution(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Fourier::Transform(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidFourier::Transform(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    if(NumPoints/Global::Freq > 366)
        Period = 2*M_PI/365.0; 
    else
        Period = 2*M_PI; 
    for(int ii = 0; ii < NumPoints; ++ii)
    {
        WData[ii] = (XData[ii] - XData[0])*Period;
        ZData[ii] = YData[ii];
    }
    Y << YData;
freopen("c:\\injection.log", "a", stdout); printf("</voidFourier::Transform(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Fourier::InverseTransform(int Index)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidFourier::InverseTransform(intIndex) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
freopen("c:\\injection.log", "a", stdout); printf("</voidFourier::InverseTransform(intIndex) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Fourier::CreateBasisFunctions(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidFourier::CreateBasisFunctions(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < NumPoints; ++ii)
    {
        X(ii+1, 1) = 1;                                  
        X(ii+1, 2) = cos(WData[ii]);                     
        X(ii+1, 3) = sin(WData[ii]);                     
        for(int Column = 3; Column < NumTerms; ++Column)
        {
            float M = floor((float) (Column+1)/2);
            if(Column%2 != 0) 
                X(ii+1, Column+1) = cos(M*WData[ii]);          
            else 
                X(ii+1, Column+1) = sin(M*WData[ii]);          
        }
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidFourier::CreateBasisFunctions(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Fourier::TransformSolution(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidFourier::TransformSolution(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
freopen("c:\\injection.log", "a", stdout); printf("</voidFourier::TransformSolution(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Power::Transform(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidPower::Transform(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    float YPoint;
    Off = floor(XData[0]);
    if(OffsetTime)
        for (int ii = 0; ii < NumPoints; ++ii)
            XData[ii] = XData[ii] - Off;
    if (YData[0] < 0)
        Multiplier = -1;
    else
        Multiplier = 1;
    for(int ii = 0; ii < NumPoints; ++ii)
    {
        if (XData[ii] <= 0)
        {
            Error = 5;    
            break;
        }
        YPoint = Multiplier * YData[ii];
        if (YPoint <= 0)    
        {
            Error = 6;
            break;
        }
        WData[ii] = log(XData[ii]);
        ZData[ii] = log(YPoint);
    } 
    Y << ZData;
freopen("c:\\injection.log", "a", stdout); printf("</voidPower::Transform(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Power::InverseTransform(int Index)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidPower::InverseTransform(intIndex) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    if(OffsetTime)
        XData[Index] = XData[Index] + Off;
    YFit[Index] = Multiplier * exp(YFit[Index]);
freopen("c:\\injection.log", "a", stdout); printf("</voidPower::InverseTransform(intIndex) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Power::CreateBasisFunctions(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidPower::CreateBasisFunctions(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    X.Column(1) = 1;
    X.Column(2) << WData;
freopen("c:\\injection.log", "a", stdout); printf("</voidPower::CreateBasisFunctions(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Power::TransformSolution(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidPower::TransformSolution(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    Solution[0] = Multiplier * exp(Solution[0]);
freopen("c:\\injection.log", "a", stdout); printf("</voidPower::TransformSolution(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Expo::Transform(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidExpo::Transform(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    Off = XData[0];
    if(OffsetTime)
        for (int ii = 0; ii < NumPoints; ++ii)
            XData[ii] = XData[ii] - Off;
    if (YData[0] < 0)
        Multiplier = -1;
    else
        Multiplier = 1;
    for(int ii = 0; ii < NumPoints; ++ii)
    {
        float YPoint = Multiplier * YData[ii];
        if (YPoint <= 0)
        {
            Error = 6;   
            break;
        }
        WData[ii] = XData[ii];
        ZData[ii] = log(YPoint);
    }
    Y << ZData;
freopen("c:\\injection.log", "a", stdout); printf("</voidExpo::Transform(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Expo::InverseTransform(int Index)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidExpo::InverseTransform(intIndex) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    if(OffsetTime)
        XData[Index] = XData[Index] + Off;
    YFit[Index] = Multiplier * exp(YFit[Index]) ;
freopen("c:\\injection.log", "a", stdout); printf("</voidExpo::InverseTransform(intIndex) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Expo::CreateBasisFunctions(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidExpo::CreateBasisFunctions(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    X.Column(1) = 1;
    X.Column(2) << WData;
freopen("c:\\injection.log", "a", stdout); printf("</voidExpo::CreateBasisFunctions(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Expo::TransformSolution(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidExpo::TransformSolution(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    Solution[0] = Multiplier * exp(Solution[0]);
freopen("c:\\injection.log", "a", stdout); printf("</voidExpo::TransformSolution(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Log::Transform(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidLog::Transform(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    if(OffsetTime)
    {
        Off = floor(XData[0]);
        for (int ii = 0; ii < NumPoints; ++ii)
            XData[ii] = (XData[ii] - Off)*Global::Freq;
    }
    if (XData[NumPoints/2] < 0)
        Multiplier = -1;
    else
        Multiplier = 1;
    double NU;
    for(int ii = 0; ii < NumPoints; ++ii)
    {
        float XPoint = Multiplier * (ii+1)/Global::Freq;
        if (XPoint <= 0)
        {
            Error = 7;   
            break;
        }
        WData[ii] = log(Multiplier *XData[ii]);
        ZData[ii] = YData[ii];
    }
    Y << ZData;
freopen("c:\\injection.log", "a", stdout); printf("</voidLog::Transform(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Log::InverseTransform(int Index)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidLog::InverseTransform(intIndex) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    if(OffsetTime)
        XData[Index] = XData[Index]/Global::Freq + Off;
freopen("c:\\injection.log", "a", stdout); printf("</voidLog::InverseTransform(intIndex) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Log::CreateBasisFunctions(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidLog::CreateBasisFunctions(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    X.Column(1) = 1;
    X.Column(2) << WData;
freopen("c:\\injection.log", "a", stdout); printf("</voidLog::CreateBasisFunctions(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void Log::TransformSolution(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidLog::TransformSolution(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    Solution[1] = Multiplier * exp(Solution[1]/Solution[0]);
freopen("c:\\injection.log", "a", stdout); printf("</voidLog::TransformSolution(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void MLinReg::Transform(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidMLinReg::Transform(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < NumPoints; ++ii)
    {
        WData[ii] = XData[ii];
        ZData[ii] = YData[ii];
    }
    Y << YData;
freopen("c:\\injection.log", "a", stdout); printf("</voidMLinReg::Transform(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void MLinReg::InverseTransform(int Index)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidMLinReg::InverseTransform(intIndex) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
freopen("c:\\injection.log", "a", stdout); printf("</voidMLinReg::InverseTransform(intIndex) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void MLinReg::CreateBasisFunctions(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidMLinReg::CreateBasisFunctions(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
freopen("c:\\injection.log", "a", stdout); printf("</voidMLinReg::CreateBasisFunctions(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void MLinReg::TransformSolution(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidMLinReg::TransformSolution(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < NumPoints; ++ii)
    {
        YFit[ii] = 0.0;
        for(int jj = 0; jj < NumTerms; ++jj)
            YFit[ii] += Basis[ii][jj] * Solution[jj];
    }
    for(int ii = 0; ii < NumPoints; ii++)
        delete[] Basis[ii];
    delete[] Basis;
freopen("c:\\injection.log", "a", stdout); printf("</voidMLinReg::TransformSolution(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void MLinReg::CopyAndDelete(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidMLinReg::CopyAndDelete(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    for(int ii = 0; ii < NumPoints; ++ii)
    {
        for(int jj = 0; jj < NumTerms; ++jj)
            X(ii+1, jj+1) = Basis[ii][jj];
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidMLinReg::CopyAndDelete(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void LeastSquares::InitializeAndFormBasisVectors(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidLeastSquares::InitializeAndFormBasisVectors(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    if(NumPoints < 2)
        Error = 1;   
    if(NumTerms < 1)
        Error = 2;   
    if(NumTerms > NumPoints)
        Error = 3;   
    else
        Error = 0;
    if(Error == 0)
    {
        Transform();
        CreateBasisFunctions();
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidLeastSquares::InitializeAndFormBasisVectors(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void LeastSquares::ComputeYFitAndResiduals(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidLeastSquares::ComputeYFitAndResiduals(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    float SumExp = 0;
    float SumTot = 0;
    for(int Index = 0; Index < NumPoints; ++Index)
    {
        InverseTransform(Index);
        SumExp += sqr(YFit[Index] - Ymean);
        SumTot += sqr(YData[Index] - Ymean);
    }
    R2 = SumExp/SumTot;
freopen("c:\\injection.log", "a", stdout); printf("</voidLeastSquares::ComputeYFitAndResiduals(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void LeastSquares::TransformSolutionAndFindResiduals(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidLeastSquares::TransformSolutionAndFindResiduals(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    ComputeYFitAndResiduals();
    TransformSolution();
freopen("c:\\injection.log", "a", stdout); printf("</voidLeastSquares::TransformSolutionAndFindResiduals(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void LeastSquares::CreateAndSolveEquations(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidLeastSquares::CreateAndSolveEquations(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    SymmetricMatrix SSQ;
    SSQ << X.t() * X;
    ColumnVector A = SSQ.i() * (X.t() * Y);
    DiagonalMatrix D;
    D << SSQ.i();
    ColumnVector V = D.AsColumn();
    ColumnVector Fitted = X * A;
    ColumnVector Residual = Y - Fitted;
    DiagonalMatrix Hat;
    Hat << X * (X.t() * X).i() * X.t();
    for(int Index = 0; Index < NumPoints; ++Index)
        YFit[Index] = Fitted(Index+1);
    for(int Index = 0; Index < NumTerms; ++Index)
        Solution[Index] = A(Index+1);
freopen("c:\\injection.log", "a", stdout); printf("</voidLeastSquares::CreateAndSolveEquations(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
LeastSquares::LeastSquares(int NumPoints, float x[], float y[],int NumTerms, String Type, String Desc) :NumPoints(NumPoints), NumTerms(NumTerms), Type(Type), Desc(Desc)
{
freopen("c:\\injection.log", "a", stdout); printf("<LeastSquares::LeastSquares(intNumPoints,floatx[],floaty[],intNumTerms,StringType,StringDesc):NumPoints(NumPoints),NumTerms(NumTerms),Type(Type),Desc(Desc) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    XData = new double [NumPoints];
    YData = new double [NumPoints];
    float SumX = 0;
    float SumY = 0;
    for(int ii = 0; ii < NumPoints; ++ii)
    {
        XData[ii] = x[ii];
        SumX += x[ii];
        YData[ii] = y[ii];
        SumY += y[ii];
    }
    Xmean = SumX/NumPoints;
    Ymean = SumY/NumPoints;
    WData = new double [NumPoints];
    ZData = new double [NumPoints];
    YFit = new float [NumPoints];
    Solution = new float [NumTerms];
    for(int ii = 0; ii < NumTerms; ++ii)
        Solution[ii] = 0.0;
freopen("c:\\injection.log", "a", stdout); printf("</LeastSquares::LeastSquares(intNumPoints,floatx[],floaty[],intNumTerms,StringType,StringDesc):NumPoints(NumPoints),NumTerms(NumTerms),Type(Type),Desc(Desc) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
LeastSquares::LeastSquares(int NumTerms, String Type, String Desc, TLineSeries *Data, bool OffsetTime) :NumPoints(Data->Count()), NumTerms(NumTerms), Type(Type), Desc(Desc), OffsetTime(OffsetTime)
{
freopen("c:\\injection.log", "a", stdout); printf("<LeastSquares::LeastSquares(intNumTerms,StringType,StringDesc,TLineSeries*Data,boolOffsetTime):NumPoints(Data->Count()),NumTerms(NumTerms),Type(Type),Desc(Desc),OffsetTime(OffsetTime) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    XData = new double [NumPoints];
    YData = new double [NumPoints];
    float SumX = 0;
    float SumY = 0;
    for(int ii = 0; ii < NumPoints; ++ii)
    {
        XData[ii] = Data->XValue[ii];
        SumX += XData[ii];
        YData[ii] = Data->YValue[ii];
        SumY += YData[ii];
    }
    Xmean = SumX/NumPoints;
    Ymean = SumY/NumPoints;
    WData = new double [NumPoints];
    ZData = new double [NumPoints];
    YFit = new float [NumPoints];
    Solution = new float [NumTerms];
    for(int ii = 0; ii < NumTerms; ++ii)
        Solution[ii] = 0.0;
    X.ReSize(NumPoints, NumTerms);
    Y.ReSize(NumPoints);
    SE.ReSize(NumTerms);
freopen("c:\\injection.log", "a", stdout); printf("</LeastSquares::LeastSquares(intNumTerms,StringType,StringDesc,TLineSeries*Data,boolOffsetTime):NumPoints(Data->Count()),NumTerms(NumTerms),Type(Type),Desc(Desc),OffsetTime(OffsetTime) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
LeastSquares::~LeastSquares()
{
freopen("c:\\injection.log", "a", stdout); printf("<LeastSquares::~LeastSquares() @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    delete[] XData;
    delete[] YData;
    delete[] WData;
    delete[] ZData;
    delete[] YFit;
    delete[] Solution;
    SSQ.CleanUp();
    D.CleanUp();
    Hat.CleanUp();
    X.CleanUp();
    Y.CleanUp();
    A.CleanUp();
    V.CleanUp();
    Fitted.CleanUp();
    Residual.CleanUp();
    SE.CleanUp();
freopen("c:\\injection.log", "a", stdout); printf("</LeastSquares::~LeastSquares() @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
void LeastSquares::DoIt(void)
{
freopen("c:\\injection.log", "a", stdout); printf("<voidLeastSquares::DoIt(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
    try
    {
        InitializeAndFormBasisVectors();
        CreateAndSolveEquations();
        TransformSolutionAndFindResiduals();
    }
    catch(const Sysutils::Exception &E)
    {
        ShowMessage(AnsiString(E.Message));
        Error = 8;
    }
freopen("c:\\injection.log", "a", stdout); printf("</voidLeastSquares::DoIt(void) @@@ Numerical.cpp_nocom>\n"); fclose(stdout);
}
