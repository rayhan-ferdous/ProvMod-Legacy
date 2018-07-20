// 08/24/12
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

typedef void TObject;

class TStringList;

class StringandObject{
public:
  string Name;
  TObject* Object;

  StringandObject(){Name = ""; Object = 0;}
  StringandObject(string Name_, TObject* Object_){Name = Name_; Object = Object_;}
  string get_Name(){return Name;}
  TObject* get_Object(){return Object;}
};

class TStrings{
//  vector<StringandObject>* array;
public:
//  TStrings(TStringList* StringList_) : StringList(StringList_) {};

  string &operator[](int ii);
  void Init(TStringList* StringList_){StringList = StringList_;};

  TStringList* StringList;
};

class TObjects{
public:
//  TObjects(TStringList* StringList_) : StringList(StringList_) {};

  TObject* &operator[](int ii);
  void Init(TStringList* StringList_){StringList = StringList_;};

  TStringList* StringList;
};

class TStringList{
  public:
  vector<StringandObject> array;

  TStrings Strings;
  TObjects Objects;

  int Count;
  bool CaseSensitive;
  bool Sorted;

  string QuoteChar; // Strings = new TStrings(this); Objects = new TObjects(this);
  string Delimiter;

  TStringList(){array.reserve(64); QuoteChar = "'"; Delimiter = ","; Strings.Init(this); Objects.Init(this);}; //
//  TStringList(this);

  int IndexOf(string s);
  void Add(string s);
  void AddObject(string s, TObject* thing);
  void Clear();
  void Delete(int Index);
  string &operator[](int ii);

  void DelimitedText(string s);
  void CommaText(string s);
  string DelimitedText(void);
  string CommaText(void);

//  void SaveToFile(string FileName){};
};

  string TStringList::DelimitedText(void){
    ostringstream temp;

    for(unsigned int ii = 0; ii < array.size(); ++ii){
      if(ii)
         temp << ", ";
      temp << array.at(ii).get_Name();
    }
    temp << endl;
    return temp.str();

  }

  string TStringList::CommaText(void){
    ostringstream temp;

    for(unsigned int ii = 0; ii < array.size(); ++ii){
      if(ii)
         temp << ", ";
      temp << array.at(ii).get_Name();
    }
    temp << endl;
    return temp.str();

  }

  void TStringList::DelimitedText(string s){
    string in_quote;
    string::size_type pos, here, last_quote, done_to = 0;
    array.clear();
    s.append(",");
    for(pos = 0; pos < s.size(); ++pos){
      here = s.find_first_of("' ,", pos);
      switch(s[here]){
        case '\'':
          last_quote = s.find("'", pos);
          in_quote = s.substr(here+1, last_quote-1);
          pos = last_quote+1;
          break;
        case ',':
        case ' ':
          in_quote.append(s.substr(done_to, here-done_to));
          Add(in_quote);
          done_to = s.find_first_not_of(" ", here+1);

          if(done_to == string::npos)
            pos = s.size();
          else{
            pos = done_to;
            in_quote = "";
          }
      } // switch
    } // for
  }


string &TStringList::operator[](int ii) {
  return array[ii].Name;
  }

void TStringList::AddObject(string s, TObject* thing){
  array.push_back(StringandObject(s, thing));
  Count = array.size();
}

int TStringList::IndexOf(string s){

  for(unsigned int ii = 0; ii < array.size(); ++ii)
    if(array.at(ii).get_Name() == s)
      return ii;

  return -1;
}

void TStringList::Add(string s){
  array.push_back(StringandObject(s, 0));
  Count = array.size();
}

void TStringList::Clear(){
  array.clear();
  Count = array.size();
}

void TStringList::Delete(int Index){
  vector<StringandObject>::iterator pos;
  int cnt = -1;
    for(pos = array.begin(); pos < array.end(); ++pos)
      if(Index == ++cnt){
        array.erase(pos);
        Count = array.size();
        return;
      }
  ;
}

string &TStrings::operator[](int ii) {
  return StringList->array[ii].Name;
}

TObject* &TObjects::operator[](int ii) {
  return StringList->array[ii].Object;
}

int main()
{
  TStringList Fred;
  TStringList* FredP;

  FredP = new TStringList;

    cout << "Hello world!" << endl;
/*
    for(int ii = 0; ii < Fred.Count; ++ii){

      string Name("nameA");
      Name[4]+= ii;

      Fred.AddObject(Name, (TObject*) ii);
    }

    Fred.Delete(2);*/

    Fred.DelimitedText("1234,5678, 9999");
    FredP->DelimitedText("1234,5678, 9999");

    for(int ii = 0; ii < Fred.Count; ++ii){

      cout << Fred[ii] << endl;
      cout << Fred.Strings[ii] << endl;
      cout << Fred.Objects[ii] << endl;
      cout << (*FredP)[ii] << endl;
      cout << FredP->Strings[ii] << endl;
      cout << FredP->Objects[ii] << endl;
//      cout << Fred.Strings[Fred.IndexOf(Fred.Strings[ii])] << endl;
    }

    cout << Fred.DelimitedText();
    cout << FredP->DelimitedText();

    Fred.Clear();
    FredP->Clear();

    return 0;
}
