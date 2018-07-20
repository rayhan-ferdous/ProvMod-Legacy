#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

class module {
  public:

    module() : Var0(1){};

    virtual module* Klone() const = 0;

    long Var0;
};

class module1 : public module{
  public:

    module1() : Var1(11){};

    virtual module1* Klone() const{
      return new module1(*this);
    }

    long Var1;

};

class module11 : public module1{
  public:

    module11() : Var11(1011){};

    virtual module11* Klone() const{
      return new module11(*this);
    }

    long Var11;

};

class module2 : public module{
  public:

    module2() : Var2(21){};

    virtual module2* Klone() const{
      return new module2(*this);
    }

    long Var2;

};

int main()
{
    cout << "Hello world!" << endl;

    module1 *M1 = new module1;
    module1 *M11 = new module11;
    module2 *M2 = new module2;

    module1 *M1K = M1->Klone();
    module1 *M11K = M11->Klone();
    module2 *M2K = M2->Klone();

    string S1 = typeid( *M1K).name();
    string S11 = typeid( *M11K).name();
    string S2 = typeid( *M2K).name();


    return 0;
}
