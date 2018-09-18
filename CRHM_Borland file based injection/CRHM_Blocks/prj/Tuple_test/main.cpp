#include <iostream>
#include "boost/tuple/tuple.hpp"
#include <boost/spirit/include/classic_core.hpp>
// #include "boost/tuple/tuple_comparison.hpp"

using namespace std;
using namespace boost;

int main()
{
  class Simple {
    public:
      long L;
      float F;
    Simple() : L(1001), F(3.142) {};
  };

  Simple MyClass;

  tuple<int, long> T1(10, 101);
  tuple<int, long, Simple> T1(10, 101, MyClass);

  int j = get<0>(T1);
  long jl = get<1>(T1);

  Simple S1 = get<2>(T1);

  cout << "Hello world!" << endl;
  return 0;
}
