#include <iostream>
#include <string>
#include <vector>

using namespace std;

class String : string {
  string ClassString;
  public:

  String(string s) : ClassString(s){};
  String(char *ch) : ClassString(ch){};
  int Pos(String S);
  int Pos(string S);
  String LowerCase(String){return ClassString;}

};

class TStringList {

  vector<String> Strings;
  vector<int> Objects;

};

int main()
{
    string fred("Hello Fred");
    String S("123");
    String S2(fred);

    cout << "Hello world!" << S << endl;
    return 0;
}
