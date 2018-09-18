//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused

long sub(long *p){
  long B = p[6];
  long *C;
  return B;
}

float sub2(float *p){
  float B = p[6];
  float *C;
  return B;
}

int main(int argc, char* argv[])
{
  long A[5][6][7];
  long *p1;
  long **p2;
  long ***p3;

  float AR[5][6][7];
  float *pR1;

  for(long ii = 0; ii < 5; ++ii)
    for(long jj = 0; jj < 6; ++jj)
      for(long kk = 0; kk < 7; ++kk)
        A[ii][jj][kk] = ii*jj*kk;

  p1 = A[1][1];
  long Z = sub(p1);

  for(long ii = 0; ii < 5; ++ii)
    for(long jj = 0; jj < 6; ++jj)
      for(long kk = 0; kk < 7; ++kk)
        AR[ii][jj][kk] = ii*jj*kk;

  pR1 = AR[1][1];
  float ZR = sub2(pR1);

  return 0;
}
//---------------------------------------------------------------------------
 