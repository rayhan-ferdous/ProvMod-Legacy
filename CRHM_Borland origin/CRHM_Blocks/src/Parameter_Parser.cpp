// 07/30/12

#include <string>
#include <string.h>
#include <stdlib.h>
#include "Common.h"

enum types { DELIMITER = 1, NUMBER};

using namespace std;

void LogError(string s){
}

class ClassPar{
  public:
  string module;
  string param;
  string name;

  string valstr;
  float minVal;
  float maxVal;

  float *values;
  long *ivalues;

  int ** ilayvalues;
  float ** layvalues;

  long dim;
  long lay;

  CRHM::TVar varType;

  ClassPar (string name){};
  ClassPar* klone(string name) const;

};

//ClasssPar* ClassPar::klone(string name) const{
//  return new ClassPar(name);
//}
//
class Myparser_old {
  const char *exp_ptr;  // points to the expression
  char token[80]; // holds current token
  char tok_type;  // holds token's type

  int row, col;
  int repeat;
  int rowrepeat;
  int Bang;
  bool repeatset;
  ClassPar *LocalPar;

  void eval_exp2(float &result);
  void eval_exp3(float &result);
  void eval_exp4(float &result);
  void eval_exp5(float &result);
  void eval_exp6(float &result);
  void atom(float &result);
  void get_token();
  void serror(int error);
  int isdelim(char c);
public:
  Myparser_old();
  void eval_exp(ClassPar *Par);
};

//---------------------------------------------------------------------------
Myparser_old::Myparser_old() // parser constructor
{
  exp_ptr = NULL;
}

// Parser entry point.
void Myparser_old::eval_exp(ClassPar *Par)
{
  LocalPar = Par;
  float result, Last;
  int stop;
  bool OpenBrkt;

  //"points to the expression"
  exp_ptr = Par->valstr.c_str();

  row = 0; col = 0;
  rowrepeat = 1;
  Bang = 0;

next:
  repeat = 1;
  repeatset = false;
  OpenBrkt = false;

  //determine if the current token is a number, delimeter or variable
  get_token();

  if(*token == '[')
    result = 0.0;
  else if(*token) {
    eval_exp2(result);
    if(result > Par->maxVal) result = Par->maxVal;
    if(result < Par->minVal) result = Par->minVal;
    Last = result;
  }
  else
    result = 0.0;

  bool end = !*exp_ptr;

  switch(*token) {
    case '\0' :
      if(col >= Par->dim) break;

      if(Par->varType == CRHM::Float)
        Par->layvalues[row][col++] = result;
      else if (Par->varType == CRHM::Int)
        Par->ilayvalues[row][col++] = result;

      for(int ll = row; ll < Par->lay; ++ll) {
          if(Bang){ // N.B. loop start
            for(int ii = col-1; ii < Par->dim; ++ii){
              if(Par->varType == CRHM::Float)
                Par->layvalues[ll][ii] = Last;
              else if (Par->varType == CRHM::Int)
                Par->ilayvalues[ll][ii] = Last;

              Last += 1;
            }
          }
          else{
            for(int ii = col; ii < Par->dim; ++ii)
              if(Par->varType == CRHM::Float)
                Par->layvalues[ll][ii] = 0.0;
              else if (Par->varType == CRHM::Int)
                Par->ilayvalues[ll][ii] = 0.0;
          }

        col = 0;;
      }
      break;
    case '[' :
      rowrepeat = repeat;
      repeat = 1;
      repeatset = false;
      OpenBrkt = true;
      goto next;
    case ']' :
      OpenBrkt = false;
      while(isspace(*exp_ptr)) ++exp_ptr; // skip over white space
      if(*exp_ptr == ',') ++exp_ptr; // skip over comma

      stop = col + repeat;
      if(stop > Par->dim) stop = Par->dim;
      for(int ii = col; ii < stop; ++ii)
        if(Par->varType == CRHM::Float)
          Par->layvalues[row][col++] = result;
        else if(Par->varType == CRHM::Int)
          Par->ilayvalues[row][col++] = result;

      for(int ii = col; ii < Par->dim; ++ii){
        Last += Bang;
        if(Par->varType == CRHM::Float)
          Par->layvalues[row][ii] = Last;
        else if(Par->varType == CRHM::Int)
          Par->ilayvalues[row][ii] = Last;
      }

      Bang = 0;
      row++; col = 0;
      if(rowrepeat > 1 || end) {
        stop = row + rowrepeat-1;
        if(stop > Par->lay || end) stop = Par->lay;

        for(int ll = row; ll < stop; ++ll) {
          for(int ii = col; ii < Par->dim; ++ii)
            if(Par->varType == CRHM::Float)
              Par->layvalues[ll][ii] = Par->layvalues[ll-1][ii];
            else if(Par->varType == CRHM::Int)
              Par->ilayvalues[ll][ii] = Par->ilayvalues[ll-1][ii];
        }
        row = stop;
        rowrepeat = 1;
      }
      if(row >= Par->lay) break;

      goto next;
    case ',' :
      stop = col + repeat;
      if(stop > Par->dim) stop = Par->dim;
      for(int ii = col; ii < stop; ++ii)
        if(Par->varType == CRHM::Float)
          Par->layvalues[row][col++] = result;
        else if(Par->varType == CRHM::Int)
          Par->ilayvalues[row][col++] = result;
      if(col >= Par->dim)
        if(!OpenBrkt && (row+1 < Par->lay)) {
          col = 0;
          ++row;
        }

      goto next;
    default :
      serror(0); // last token must be null
      break;
  } // switch
}

// Add or subtract two terms.
void Myparser_old::eval_exp2(float &result)
{
  register char op;
  float temp;

  eval_exp3(result);
  while((op = *token) == '+' || op == '-') {
    get_token();
    eval_exp3(temp);
    switch(op) {
      case '-':
        result = result - temp;
        break;
      case '+':
        result = result + temp;
        break;
    }
  }
}

// Multiply or divide two factors.
void Myparser_old::eval_exp3(float &result)
{
  register char op;
  float temp;

  eval_exp4(result);
  while((op = *token) == '*' || op == '/' || op == '%') {
    get_token();
    if(op == '*' && !repeatset) {
      repeat = result;
      repeatset = true;
      if(*token == '[') return;
      eval_exp4(result);
      return;
    }
    eval_exp4(temp);
    switch(op) {
      case '*':
        result = result * temp;
        break;
      case '/':
        result = result / temp;
        break;
      case '%':
        result = (int) result % (int) temp;
        break;
    }
  }
}

// Process an exponent
void Myparser_old::eval_exp4(float &result)
{
  float temp, ex;
  register int t;

  eval_exp5(result);
  if(*token== '^') {
    get_token();
    eval_exp4(temp);
    if(temp==0.0) {
      result = 1.0;
      return;
    }
    result = pow(result, temp);
  }
}

// Evaluate a unary + or -.
void Myparser_old::eval_exp5(float &result)
{
  register char  op;

  op = 0;
  if((tok_type == DELIMITER) && *token=='+' || *token == '-') {
    op = *token;
    get_token();
  }
  eval_exp6(result);
  if(op=='-') result = -result;
}

// Process a parenthesized expression.
void Myparser_old::eval_exp6(float &result)
{
  if((*token == '(')) {
    repeatset = true;
    get_token();
    eval_exp2(result);
    if(*token != ')')
      serror(1);
    get_token();
  }
  else atom(result);
}

// Get the value of a number.
void Myparser_old::atom(float &result)
{
  switch(tok_type) {
    case NUMBER:
      result = atof(token);
      get_token();
      return;
    default:
      serror(0);
  }
}

// Display a syntax error.
void Myparser_old::serror(int error)
{
  static char *e[]= {
      "Syntax Error",
      "Unbalanced Parentheses",
      "No expression Present"
  };
  LogError(string(e[error]) + " in module '" +
             LocalPar->module + "' parameter '" + LocalPar->param + "'");

  for(int ll = row; ll < LocalPar->lay; ++ll) { // reset remainder of parameter values to 0
    for(int ii = col; ii < LocalPar->dim; ++ii)
      if(LocalPar->varType == CRHM::Float)
        LocalPar->layvalues[ll][ii] = 0.0;
      else if(LocalPar->varType == CRHM::Int)
        LocalPar->ilayvalues[ll][ii] = 0;
  }
}

// Obtain the next token.
void Myparser_old::get_token()
{
  register char *temp;

  tok_type = 0;
  temp = token;
  *temp = '\0';

  if(!*exp_ptr) return; // at end of expression

  while(isspace(*exp_ptr)) ++exp_ptr; // skip over white space

  if(*exp_ptr == '!'){ // make series
    Bang = 1;
    ++exp_ptr;
  }

  //check if exp_ptr is pointing to a valid character, that is, one of +-*/%^=(),[]!
  if((*exp_ptr) && strchr("+-*/%^=(),[]!", *exp_ptr)){  // added ','
    tok_type = DELIMITER;
    // advance to next char
    *temp++ = *exp_ptr++;
  }
  else if(isalpha(*exp_ptr)) {
    while(!isdelim(*exp_ptr)) *temp++ = *exp_ptr++;
    tok_type = CRHM::VARIABLE;
  }
  else if(isdigit(*exp_ptr)) {
    while((*exp_ptr) && strchr("0123456789.",*exp_ptr)) *temp++ = *exp_ptr++;
    if((*exp_ptr) && strchr("eE", *exp_ptr)) {
      *temp++ = *exp_ptr++;
      while((*exp_ptr) && strchr("+- ", *exp_ptr))  *temp++ = *exp_ptr++;
      while(!isdelim(*exp_ptr)) *temp++ = *exp_ptr++;
    }
    tok_type = NUMBER;
  }

  *temp = '\0';
}

// Return true if c is a delimiter.
int Myparser_old::isdelim(char c)
{
  if((*exp_ptr) && strchr(" +-/*%^=(),[]", c) || c==9 || c=='\r' || c==0)  // added ','
    return 1;
  return 0;
}
