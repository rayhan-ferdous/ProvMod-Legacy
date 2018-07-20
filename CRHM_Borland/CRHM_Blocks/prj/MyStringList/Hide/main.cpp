// 08/23/12
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

typedef void TObject;

class TStringList;
class TStrings;
class TObjects;

class StringandObject{
public:
  string Name;
  TObject* Object;

  StringandObject(){Name = ""; Object = 0;}
  StringandObject(string Name_, TObject* Object_){Name = Name_; Object = Object_;}
  string get_Name(){return Name;}
  TObject* get_Object(){return Object;}
};

class TStringList{
  public:
  vector<StringandObject> array;
  vector<StringandObject>::iterator pos;

  TStrings Strings;
  TObjects Objects();

  int Count;
  bool CaseSensitive;
  bool Sorted;
  string DelimitedText;
  string CommaText;

  int IndexOf(string s);
  void Add(string s);
  void AddObject(string s, TObject* thing);
  void Clear();
  void Delete(int Index);
  string operator[](int ii);
//  void SaveToFile(string FileName){};
};

string TStringList::operator[](int ii) {
  return array[ii].Name;
  }

void TStringList::AddObject(string s, TObject* thing){
  array.push_back(StringandObject(s, thing));
}

int TStringList::IndexOf(string s){

  for(int ii = 0; ii < array.size(); ++ii)
    if(array.at(ii).get_Name() == s)
      return ii;

  return -1;
}

void TStringList::Add(string s){
  array.push_back(StringandObject(s, 0));
}

void TStringList::Clear(){
  array.clear();
}

void TStringList::Delete(int Index){
  int cnt = 0;
    for(pos = array.begin(); pos < array.end(); ++pos)
      if(Index == cnt){
        array.erase(pos);
        return;
      }
  ;
}

class TStrings{
public:
  int Test;
  TStrings(TStringList& StringList_) : StringList(StringList_) {Test = 987;};
  string operator[](int ii);

  TStringList& StringList;
};

class TObjects{
public:
  int Test;
//  TObjects(TStringList& StringList_) : StringList(StringList_) {Test = 789;};
//  TObject* operator[](int ii);

  TStringList* StringList;
};

string TStrings::operator[](int ii) {
  return StringList.array[ii].Name;
}

TObject* TObjects::operator[](int ii) {
  return StringList.array[ii].Object;
}

int main()
{
  TStringList Fred;
    cout << "Hello world!" << endl;

    for(int ii = 0; ii < 26; ++ii){

      string Name("nameA");
      Name[4]+= ii;

      Fred.AddObject(Name, (TObject*) ii);
    }

    for(int ii = 0; ii < 26; ++ii){

      cout << Fred[ii] << endl;
//      cout << (Fred.Strings).Test << endl;
//      cout << Fred.Strings[2] << endl;
//      cout << Fred.Strings[ii] << endl;
    }

    cout << Fred.IndexOf("nameD") << endl;
//    cout << Fred.Strings << endl;

    return 0;
}
