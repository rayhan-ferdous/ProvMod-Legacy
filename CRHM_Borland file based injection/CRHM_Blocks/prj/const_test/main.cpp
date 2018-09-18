#include <iostream>

using namespace std;

  float *new_values;
  float **new_lay_values;

void One(const float **values){
  float  *local_values;
  float const *const_values;

  local_values = new_values; // const_cast<float*>

  *values = local_values;

//  const_cast<float*> (*values) = local_values;

}

void Two(const float ***lay_values){
  float const **const_lay_values;
  float **local_lay_values;
  float ***adrs_lay_values;

  *const_lay_values = **lay_values;
//  *lay_values = new_lay_values;

   local_lay_values = const_cast<float**> (*lay_values);
   adrs_lay_values = const_cast<float***> (lay_values);
   *adrs_lay_values = new_lay_values;

   local_lay_values = const_cast<float**> (*lay_values);

}

int main()
{
  const int lay = 3;
  const int dim = 4;

  const float *values;
  const float **lay_values;

  new_lay_values = new float*[lay];
  for(int jj = 0; jj < lay; ++jj){
    new_lay_values[jj] = new float[dim];
    for(int ii = 0; ii < dim;++ii){
      new_lay_values[jj][ii] = jj*10+ii;
    }
  }

  new_values = new float[dim];
  for(int ii = 0; ii < dim;++ii)
    new_values[ii] = ii;

    cout << "Hello world!" << endl;

    One(&values);

    Two(&lay_values);

    return 0;
}
