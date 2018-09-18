// 08/18/11
//---------------------------------------------------------------------------

#ifndef CRHM_parseH
#define CRHM_parseH
//---------------------------------------------------------------------------
#include <stack>
#include <map>
#include <list>
#include <functional>
#include <algorithm>
#include <string>
#include "common.h"
#include "ClassCRHM.h"
#include "ClassModule.h"
#include <boost/spirit/core.hpp>
#include <boost/spirit/symbols.hpp>
#include <boost/spirit/utility.hpp>
#include "boost/spirit/error_handling/exceptions.hpp"

/*=============================================================================
    Spirit v1.6.2
=============================================================================*/

using namespace std;
using namespace boost::spirit;

template <typename T, typename result = bool>
struct L_not : public unary_function<typename T, typename result> {
	result operator()(const T x) const { return (result)  (!x); }
};

template <typename T, typename result = bool>
struct L_and : public binary_function<typename T, typename T, typename result> {
	result operator()(const T x, const T y) const { return (result) (x && y);}
};

template <typename T, typename result = bool>
struct L_or : public binary_function<typename T, typename T, typename result> {
	result operator()(const T x, const T y) const { return (result) (x || y);}
};

template <typename T, typename result = bool>
struct L_GT : public binary_function<typename T, typename T, typename result> {
	result operator()(const T x, const T y) const { return (result) (x > y);}
};

template <typename T, typename result = bool>
struct L_GE : public binary_function<typename T, typename T, typename result> {
	result operator()(const T x, const T y) const { return (result) (x >= y);}
};

template <typename T, typename result = bool>
struct L_LT : public binary_function<typename T, typename T, typename result> {
	result operator()(const T x, const T y) const { return (result) (x < y);}
};

template <typename T, typename result = bool>
struct L_LE : public binary_function<typename T, typename T, typename result> {
	result operator()(const T x, const T y) const { return (result) (x <= y);}
};

template <typename T, typename result = bool>
struct L_EQ : public binary_function<typename T, typename T, typename result> {
	result operator()(const T x, const T y) const { return (result) (x == y);}
};

template <typename T, typename result = bool>
struct L_NE : public binary_function<typename T, typename T, bool> {
	result operator()(const T x, const T y) const { return (result) (x != y); }
};

template <typename arg1, typename result = arg1>
struct SineC : public unary_function<typename arg1, typename result> {
	result operator()(const arg1 x) const { return (result) sin(x/180*M_PI); }
};

template <typename arg1, typename result = arg1>
struct TanC : public unary_function<typename arg1, typename result> {
	result operator()(const arg1 x) const { return (result) tan(x/180*M_PI); }
};

template <typename arg1, typename result = arg1>
struct CosC : public unary_function<typename arg1, typename result> {
	result operator()(const arg1 x) const { return (result) cos(x/180*M_PI); }
};

template <typename arg1, typename result = arg1>
struct ExpC : public unary_function<typename arg1, typename result> {
	result operator()(const arg1 x) const { return (result) exp(x); }
};

template <typename arg1, typename result = arg1>
struct LogC : public unary_function<typename arg1, typename result> {
	result operator()(const arg1 x) const { return (result) log(x); }
};

template <typename arg1, typename result = arg1>
struct estarC : public unary_function<typename arg1, typename result> {
	result operator()(const arg1 x) const { return (result) estar(x); }
};

template <typename T, typename result = T>
struct patmosC : public unary_function<typename T, typename result> {
	result operator()(const T Ht) const { return (result)  (101.3*pow((293.0-0.0065*Ht)/293.0, 5.26)); } // kPa
};

template <typename arg1, typename result = arg1>
struct Log10C : public unary_function<typename arg1, typename result> {
	result operator()(const arg1 x) const { return (result) log10(x); }
};

template<typename arg1, typename arg2 = arg1, typename result = arg1>
class PowerC : binary_function <typename arg1, typename arg2, typename result> {
public:
	result operator() (const arg1  &x, const arg2 &x1) const { return (result) pow(x, x1); }
};

template<typename arg1, typename arg2 = arg1, typename result = arg1>
class MaxC : binary_function <typename arg1, typename arg2, typename result> {
public:
	result operator() (const arg1  &x, const arg2 &x1) const { return (result) max(x, x1); }
};

template<typename arg1, typename arg2 = arg1, typename result = arg1>
class MinC : binary_function <typename arg1, typename arg2, typename result> {
public:
	result operator() (const arg1  &x, const arg2 &x1) const { return (result) min(x, x1); }
};

template<typename arg1, typename arg2 = arg1, typename result = arg1>
class spec_humidC : binary_function <typename arg1, typename arg2, typename result> {
public:
    result operator() (const arg1  ea, const arg2 Pa) const { return (result) (0.622*ea/(Pa - ea*0.378)); }
};

template <class _Tp>
struct modulus : public binary_function<_Tp,_Tp,_Tp>
{
  _Tp operator()(const _Tp& __x, const _Tp& __y) const { return fmod(__x, __y); }
};

class ClassMacro;

class VarCHRM {
public:
  VarCHRM() : kind(LOCAL), val(NULL), value(NULL), ivalue(NULL), value2(NULL), ivalue2(NULL),
                 Ihh(0), Ill(0), IndexMax(0), IndexMaxLay(0), name("Undefined"), Me(NULL) {};
  VarCHRM(const VarCHRM & Cl); // copy constructor
  VarCHRM &operator=(const VarCHRM & Cl);
  ~VarCHRM();

  void put(float val_);
  float get(void);

  enum TV {CRHM, CRHMint, LOCAL, FUNget, FUNobs, CRHM2, CRHMint2, NOP};

  TV kind;          // enum TV {CRHM, CRHMint, LOCAL, FUNget, FUNobs, CRHM2, CRHMint2, NOP}
  float val;        // const value

  float *value;     // CRHM array
  long *ivalue;     // CRHM array
  float **value2;     // CRHM array
  long **ivalue2;     // CRHM array

  long Ihh;         // CRHM array element 0-based
  long Ill;         // CRHM array element 0-based
  long IndexMax;    // Max index - (#HRUs - 1)
  long IndexMaxLay; // Max index - (#HRUs - 1)
  string name;      // identifier
  float (*pget) (void);
  ClassModule* Me;
};

typedef std::map<std::string, VarCHRM> symtab_t;

///////////////////////////////////////////////////////////////////////////////
//
//  Semantic actions
//
///////////////////////////////////////////////////////////////////////////////

class execbase;
typedef boost::shared_ptr<execbase> Execbase;

class execbase {
public:
  execbase(stack<float>& eval_, list<Execbase>& oper_, string s_, VarCHRM* Lvar_ = NULL)
    : eval(eval_), oper(oper_), s(s_), Lvar(Lvar_), OurOrder(-1) {OurIndex = ++Index; };

  execbase(const execbase & Cl); // copy constructor
  execbase &operator=(const execbase & Cl);

  virtual float operator()() const {return -777;} ;

  mutable VarCHRM* Lvar; // pointer to this operation variable

  static  long Index; // reference number

  string s; // class identification string. e.g. Vadd for execVadd etc.

  long OurIndex;
  long OurOrder;

protected:
  stack<float>& eval;
  list<Execbase>& oper;
};

class execNegate : public execbase {
public:
  execNegate(stack<float>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "negate"){};
  execNegate(const execNegate & Cl) : execbase(Cl){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const {
    Execbase Sp(new execNegate(*this));
    oper.push_back(Sp);
  }

  float operator()() const {
    float X = eval.top();
    eval.pop();
    eval.push(-X);
    return X;
  }
};

class execInvert : public execbase {
public:
  execInvert(stack<float>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "invert"){};
  execInvert(const execInvert & Cl) : execbase(Cl){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const {
    Execbase Sp(new execInvert(*this));
    oper.push_back(Sp);
  }

  float operator()() const {
    float X = eval.top();
    eval.pop();

    if(X == 0.0)
      X = 1.0;
    else
      X = 0.0;

    eval.push(X);
    return X;
  }
};

class execRHOa : public execbase {
public:
  execRHOa(stack<float>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "RHOa"){};
  execRHOa(const execRHOa & Cl) : execbase(Cl){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const {
    Execbase Sp(new execRHOa(*this));
    oper.push_back(Sp);
  }

  float operator()() const {
    float Pa = eval.top();
    eval.pop();

    float ea = eval.top();
    eval.pop();

    float t = eval.top();
    eval.pop();

    float X = RHOa(t, ea, Pa);

    eval.push(X);
    return X;
  }

  float RHOa(float t, float ea, float Pa) const // atmospheric density (kg/m^3)
  {
    const float R = 2870;
     return (1E4*Pa /(R*( 273.15 + t))*(1.0 - 0.379*(ea/Pa)) ); //
  }
};

class execIf : public execbase {
public:
  execIf(stack<float>& eval_, list<Execbase>& oper_,
    list<Execbase> ::iterator & PCiter_, stack<list<Execbase> ::iterator> & PCiterIF_)
    : execbase(eval_, oper_, "If"), PCiter(PCiter_), PCiterIF(PCiterIF_), False_iter(NULL),
      End_iter(NULL){};

  execIf(const execIf & Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterIF(Cl.PCiterIF),
    False_iter(Cl.False_iter), End_iter(Cl.End_iter){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const { // compilation

    Execbase Sp(new execIf(*this));
    oper.push_back(Sp);

    PCiterIF.push(--oper.end()); // push self
  }

  float operator()() const { // execution

    if(!eval.top()) {
      PCiter = False_iter; // execute false statement, otherwise fall through
      ++PCiter; // value before 'else' pushed on to stack and skips 'else'.
    }
    eval.pop();

    return -1;
  }

  void setFalse_iter(list<Execbase> ::iterator PCiter) { // used by execElse
    False_iter = PCiter;
  };

  void setEnd_iter(list<Execbase> ::iterator PCiter) { // used by execEndif
    End_iter = PCiter;

    if(False_iter == NULL) { // no 'else'
      False_iter = PCiter;
      --False_iter; // make instruction
    }
  };

  void jmpEnd_iter(void) { // used by execElse
    PCiter = End_iter;
  };

private:
  list<Execbase> ::iterator False_iter;
  list<Execbase> ::iterator End_iter;

  list<Execbase> ::iterator & PCiter;   // changes for each if
  stack<list<Execbase> ::iterator> & PCiterIF; // changes for each if
};

class execElse : public execbase {
public:
  execElse(stack<float>& eval_, list<Execbase>& oper_,
    list<Execbase> ::iterator & PCiter_, stack<list<Execbase> ::iterator> & PCiterIF_)
    : execbase(eval_, oper_, "Else"), PCiter(PCiter_), PCiterIF(PCiterIF_),
      MyIf(NULL){};

  execElse(const execElse & Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterIF(Cl.PCiterIF),
      MyIf(Cl.MyIf){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const { // compilation

    list<Execbase> ::iterator PCiterIFc = PCiterIF.top();
    PCiter = PCiterIFc;

    MyIf = (PCiter)->get(); // list of shared_ptrs to class execbase

    PCiter = oper.end();
    --PCiter; // value before else pushed on to stack.

    ((execIf*) MyIf)->setFalse_iter(PCiter);

    Execbase Sp(new execElse(*this));
    oper.push_back(Sp);
  }

  float operator()() const { // execution
    ((execIf*) MyIf)->jmpEnd_iter();

    return -1;
  }

private:
  list<Execbase> ::iterator & PCiter;   // changes for each if
  stack<list<Execbase> ::iterator> & PCiterIF; // changes for each if

  mutable execbase *MyIf;
};

class execEndif : public execbase { // NOT pushed on to stack!
public:
  execEndif(stack<float>& eval_, list<Execbase>& oper_,
    list<Execbase> ::iterator & PCiter_, stack<list<Execbase> ::iterator> & PCiterIF_)
    : execbase(eval_, oper_, "Endif"), PCiter(PCiter_), PCiterIF(PCiterIF_){};

  execEndif(const execEndif & Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterIF(Cl.PCiterIF){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const { // compilation

    list<Execbase> ::iterator PCiterIFc = PCiterIF.top();
    PCiter = PCiterIFc;

    execbase *MyIf = (PCiter)->get();

    PCiter = oper.end();
    --PCiter;

    ((execIf*) MyIf)->setEnd_iter(PCiter);

    PCiterIF.pop(); // all done
  }

  float operator()() const { // execution. Not used
    return -1;
  }

private:
  list<Execbase> ::iterator & PCiter;   // changes for each if
  stack<list<Execbase> ::iterator> & PCiterIF; // changes for each if
};

class execWhile : public execbase { // Pushed onto stack!
public:
  execWhile(stack<float>& eval_, list<Execbase>& oper_,
    list<Execbase> ::iterator & PCiter_, stack<list<Execbase> ::iterator> & PCiterWHILE_)
    : execbase(eval_, oper_, "While"), PCiter(PCiter_), PCiterWHILE(PCiterWHILE_),
      Begin_iter(NULL), End_iter(NULL){};

  execWhile(const execWhile & Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterWHILE(Cl.PCiterWHILE),
    Begin_iter(Cl.Begin_iter), End_iter(Cl.End_iter){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const { // compilation

    setBegin_iter();

    Execbase Sp(new execWhile(*this));
    oper.push_back(Sp);

    PCiterWHILE.push(--oper.end()); // push self
  }

  float operator()() const { // no execution - does not alter stack

    return -1;
  }

  void setBegin_iter(void) const { // used by self
    Begin_iter = oper.end();
    --Begin_iter; // save self. After execEndwhile pushed - updated
  };

  void setEnd_iter(list<Execbase> ::iterator PCiter) { // used by execEndwhile
    End_iter = PCiter;
    ++Begin_iter; // done once after execEndwhile pushed on stack
  };

  void jmpBegin_iter(void) { // used by execWhile2
    PCiter = Begin_iter;
  };

  void jmpEnd_iter(void) { // used by execWhile2
    PCiter = End_iter;
  };

private:
  mutable list<Execbase> ::iterator Begin_iter;
  list<Execbase> ::iterator End_iter;

  list<Execbase> ::iterator & PCiter;   // changes for each while
  stack<list<Execbase> ::iterator> & PCiterWHILE; // changes for each while
};

class execWhile2 : public execbase { // Pushed on to stack!
public:
  execWhile2(stack<float>& eval_, list<Execbase>& oper_,
    list<Execbase> ::iterator & PCiter_, stack<list<Execbase> ::iterator> & PCiterWHILE_)
    : execbase(eval_, oper_, "While2"), PCiter(PCiter_), PCiterWHILE(PCiterWHILE_),
      MyWhile(NULL){};

  execWhile2(const execWhile2 & Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterWHILE(Cl.PCiterWHILE),
    MyWhile(Cl.MyWhile) {}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const { // compilation

    list<Execbase> ::iterator PCiterWHILEc = PCiterWHILE.top();
    PCiter = PCiterWHILEc;

    MyWhile = (PCiter)->get();

    Execbase Sp(new execWhile2(*this));
    oper.push_back(Sp);
  }

  float operator()() const { // execution

    if(!eval.top()) // false
      ((execWhile*) MyWhile)->jmpEnd_iter();

    eval.pop();

    return -1;
  }

private:
  list<Execbase> ::iterator & PCiter;   // changes for each while
  stack<list<Execbase> ::iterator> & PCiterWHILE; // changes for each while

  mutable execbase *MyWhile;
};

class execEndwhile : public execbase { // Pushed on to stack!
public:
  execEndwhile(stack<float>& eval_, list<Execbase>& oper_,
    list<Execbase> ::iterator & PCiter_, stack<list<Execbase> ::iterator> & PCiterWHILE_)
    : execbase(eval_, oper_, "EndWhile"), PCiter(PCiter_), PCiterWHILE(PCiterWHILE_),
      MyWhile(NULL){};

  execEndwhile(const execEndwhile & Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterWHILE(Cl.PCiterWHILE),
    MyWhile(Cl.MyWhile) {}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const { // compilation

    list<Execbase> ::iterator PCiterWHILEc = PCiterWHILE.top();
    PCiter = PCiterWHILEc;

    MyWhile = (PCiter)->get();

    PCiterWHILE.pop(); // all done

    Execbase Sp(new execEndwhile(*this));
    oper.push_back(Sp);

    PCiter = oper.end();
    --PCiter;

    ((execWhile*) MyWhile)->setEnd_iter(PCiter);
  }

  float operator()() const { // execution
    ((execWhile*) MyWhile)->jmpBegin_iter(); // goto start and retest
    return -1;
  }

private:
  list<Execbase> ::iterator & PCiter;   // changes for each while
  stack<list<Execbase> ::iterator> & PCiterWHILE; // changes for each while

  mutable execbase *MyWhile;
};

class execFor : public execbase {
public:
  execFor(stack<float>& eval_, list<Execbase>& oper_,
    list<Execbase> ::iterator & PCiter_, stack<list<Execbase> ::iterator> & PCiterFOR_)
    : execbase(eval_, oper_, "For"), PCiter(PCiter_), PCiterFOR(PCiterFOR_), Begin_iter(NULL),
      Con_iter(NULL), Inc_iter(NULL), End_iter(NULL){};

  execFor(const execFor & Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterFOR(Cl.PCiterFOR),
    Begin_iter(Cl.Begin_iter), Con_iter(Cl.Con_iter), Inc_iter(Cl.Inc_iter), End_iter(Cl.End_iter){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const { // compilation

    setBegin_iter();

    Execbase Sp(new execFor(*this));
    oper.push_back(Sp);

    PCiterFOR.push(--oper.end()); // push self
  }

  float operator()() const { // execution - do nothing

    return -1;
  }

  void setBegin_iter(void) const { // used by self
    Begin_iter = oper.end();
    --Begin_iter; // save self. After execEndfor pushed - updated
  };

  void setEnd_iter(list<Execbase> ::iterator PCiter) { // used by execEndfor
    End_iter = PCiter;
    ++Begin_iter; // done once after execEndfor pushed on stack

    list<Execbase> ::iterator Con1_iter = Con_iter;
    list<Execbase> ::iterator Inc1_iter = Inc_iter;

/*    list<Execbase> ::iterator PCit = oper.begin();
    while(PCit != oper.end()) {
      execbase Op = (*(*PCit));
      ++PCit;
    } */

    oper.splice(End_iter, oper, ++Con1_iter, ++Inc1_iter); // move increment code to after statement code
  };

  void setCon_iter(list<Execbase> ::iterator PCiter) { // used by execForI
    Con_iter = PCiter;
  };

  void setInc_iter(list<Execbase> ::iterator PCiter) { // used by execForI
    Inc_iter = PCiter;
  };

  void jmpBegin_iter(void) { // used by execFOR
    PCiter = Begin_iter;
  };

  void jmpEnd_iter(void) { // used by execFor
    PCiter = End_iter;
  };

private:
  mutable list<Execbase> ::iterator Begin_iter;
  list<Execbase> ::iterator Con_iter; // points to ForC (conditional) instruction
  list<Execbase> ::iterator Inc_iter; // points to last increment instruction
  list<Execbase> ::iterator End_iter; // points to EndFor (end) instruction

  list<Execbase> ::iterator & PCiter;   // changes for each for
  stack<list<Execbase> ::iterator> & PCiterFOR; // changes for each for
};

class execForC : public execbase {
public:
  execForC(stack<float>& eval_, list<Execbase>& oper_,
    list<Execbase> ::iterator & PCiter_, stack<list<Execbase> ::iterator> & PCiterFOR_)
    : execbase(eval_, oper_, "ForC"), PCiter(PCiter_), PCiterFOR(PCiterFOR_),
      MyFor(NULL){};

  execForC(const execForC & Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterFOR(Cl.PCiterFOR),
    MyFor(Cl.MyFor){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const { // compilation

    list<Execbase> ::iterator PCiterFORc = PCiterFOR.top();
    PCiter = PCiterFORc;

    MyFor = (PCiter)->get();

    Execbase Sp(new execForC(*this));
    oper.push_back(Sp);

    PCiter = oper.end();
    --PCiter;

    ((execFor*) MyFor)->setCon_iter(PCiter);
  }

  float operator()() const { // execution

    if(!eval.top()) // false
      ((execFor*) MyFor)->jmpEnd_iter();

    eval.pop();

    return -1;
  }

private:

  list<Execbase> ::iterator & PCiter;   // changes for each for
  stack<list<Execbase> ::iterator> & PCiterFOR; // changes for each for

  mutable execbase *MyFor;
};

class execForI : public execbase {
public:
  execForI(stack<float>& eval_, list<Execbase>& oper_,
    list<Execbase> ::iterator & PCiter_, stack<list<Execbase> ::iterator> & PCiterFOR_)
    : execbase(eval_, oper_, "ForI"), PCiter(PCiter_), PCiterFOR(PCiterFOR_),
      MyFor(NULL){};

  execForI(const execForI & Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterFOR(Cl.PCiterFOR),
    MyFor(Cl.MyFor){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const { // compilation

    list<Execbase> ::iterator PCiterFORc = PCiterFOR.top();
    PCiter = PCiterFORc;

    MyFor = (PCiter)->get();

//    Execbase Sp(new execForI(*this));
//    oper.push_back(Sp);

    PCiter = oper.end();
    --PCiter;

    ((execFor*) MyFor)->setInc_iter(PCiter);
  }

  float operator()() const { // execution

    return -1;
  }

private:

  list<Execbase> ::iterator & PCiter;   // changes for each for
  stack<list<Execbase> ::iterator> & PCiterFOR; // changes for each for

  mutable execbase *MyFor;
};

class execEndFor : public execbase {
public:
  execEndFor(stack<float>& eval_, list<Execbase>& oper_,
    list<Execbase> ::iterator & PCiter_, stack<list<Execbase> ::iterator> & PCiterFOR_)
    : execbase(eval_, oper_, "EndFor"), PCiter(PCiter_), PCiterFOR(PCiterFOR_),
      MyFor(NULL){};

  execEndFor(const execEndFor & Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterFOR(Cl.PCiterFOR),
    MyFor(Cl.MyFor){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const { // compilation

    list<Execbase> ::iterator PCiterFORc = PCiterFOR.top();
    PCiter = PCiterFORc;

    MyFor = (PCiter)->get();

    PCiterFOR.pop(); // all done

    Execbase Sp(new execEndFor(*this));
    oper.push_back(Sp);

    PCiter = oper.end();
    --PCiter;

    ((execFor*) MyFor)->setEnd_iter(PCiter);
  }

  float operator()() const { // execution

    ((execFor*) MyFor)->jmpBegin_iter(); // goto condition and retest
    return -1;
  }

private:

  list<Execbase> ::iterator & PCiter;   // changes for each for
  stack<list<Execbase> ::iterator> & PCiterFOR; // changes for each for

  mutable execbase *MyFor;
};

class execPush : public execbase {
public:
  execPush(stack<float>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "Push"){};
  execPush(const execPush & Cl) : execbase(Cl), Ln(Cl.Ln){}; // copy constructor

  void operator()(float n) const {
    Ln = n;

    Execbase Sp(new execPush(*this));
    oper.push_back(Sp);
  }

  float operator()() const {
    eval.push(Ln);
    return Ln;
  }

private:
  mutable float Ln;
};

template<typename op>
class execDO1 : public execbase {
public:
  execDO1(op m_op_, stack<float>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "DO1"), m_op(m_op_){};
  execDO1(const execDO1 & Cl) : execbase(Cl), m_op(Cl.m_op){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const {

    Execbase Sp(new execDO1(*this));
    oper.push_back(Sp);
  }

  float operator()() const {
    const float rhs = eval.top();
    eval.pop();

    eval.push(m_op(rhs));
    return eval.top();
  }
private:
  op m_op;
};

template <class op>
execDO1<op>
make_op1(op const& the_op, stack<float>& eval, list<Execbase>& oper)
{
    return execDO1<op>(the_op, eval, oper);
}

template<typename op>
class execDO1BB : public execbase {
public:
  execDO1BB(op m_op_, stack<float>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "DO1BB"), m_op(m_op_){};
  execDO1BB(const execDO1BB & Cl) : execbase(Cl), m_op(Cl.m_op){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const {

    Execbase Sp(new execDO1BB(*this));
    oper.push_back(Sp);
  }

  float operator()() const {
    bool rhs = eval.top();
    eval.pop();

    eval.push(m_op(rhs));
    return  eval.top();
  }
private:
  op m_op;
};

template <class op>
execDO1BB<op>
make_op1BB(op const& the_op, stack<float>& eval, list<Execbase>& oper)
{
    return execDO1BB<op>(the_op, eval, oper);
}

template<typename op>
class execDO2 : public execbase {
public:
  execDO2(op m_op_, stack<float>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "DO2"), m_op(m_op_){};
  execDO2(const execDO2 & Cl) : execbase(Cl), m_op(Cl.m_op){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const {

    Execbase Sp(new execDO2(*this));
    oper.push_back(Sp);
  }

  float operator()() const {
    float rhs = eval.top();
    eval.pop();
    float lhs = eval.top();
    eval.pop();

    eval.push(m_op(lhs, rhs));
    return eval.top();
  }
private:
  op m_op;
};

template <class op>
execDO2<op>
make_op2(op const& the_op, stack<float>& eval, list<Execbase>& oper)
{
    return execDO2<op>(the_op, eval, oper);
}

template<typename op>
class execDO2B : public execbase {
public:
  execDO2B(op m_op_, stack<float>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "DO2B"), m_op(m_op_){};
  execDO2B(const execDO2B & Cl) : execbase(Cl), m_op(Cl.m_op){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const {

    Execbase Sp(new execDO2B(*this));
    oper.push_back(Sp);
  }

  float operator()() const {
    float rhs = eval.top();
    eval.pop();
    float lhs = eval.top();
    eval.pop();

    eval.push(m_op(lhs, rhs));
    return  eval.top();
  }
private:
  op m_op;
};

template <class op>
execDO2B<op>
make_op2B(op const& the_op, stack<float>& eval, list<Execbase>& oper)
{
    return execDO2B<op>(the_op, eval, oper);
}

template<typename op>
class execDO2BB : public execbase {
public:
  execDO2BB(op m_op_, stack<float>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "DO2BB"), m_op(m_op_){};
  execDO2BB(const execDO2BB & Cl) : execbase(Cl), m_op(Cl.m_op){}; // copy constructor

  void operator()(const string::iterator, const string::iterator) const {

    Execbase Sp(new execDO2BB(*this));
    oper.push_back(Sp);
  }

  float operator()() const {
    const bool rhs = eval.top();
    eval.pop();
    const bool lhs = eval.top();
    eval.pop();

    eval.push(m_op(lhs, rhs));
    return eval.top();
  }
private:
  op m_op;
};

template <class op>
execDO2BB<op>
make_op2BB(op const& the_op, stack<float>& eval, list<Execbase>& oper)
{
    return execDO2BB<op>(the_op, eval, oper);
}

class execVset : public execbase {
public:
  execVset(symtab_t &vars_, stack<float>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVas_)
     : execbase(eval_, oper_, "Vset"), vars(vars_), LastVas(LastVas_) {};
  execVset(const execVset & Cl) : execbase(Cl), vars(Cl.vars), LastVas(Cl.LastVas) {}; // copy constructor

  void operator()(const string::iterator b, const string::iterator e) const {

    string S(b, e);
    int ii = S.find_first_of("[ =\t");

    if(ii > 0)
      S.erase(ii);

    symtab_t::iterator FP = vars.find(S);
    if(FP == vars.end()){
      string SS("macro code - writing to an undefined variable: \"" + S + "\".  Suggestion - declared observations always end with a # symbol");
      CRHMException Except(SS , TERMINATE);
      throw CRHMException(Except);
    }

    Lvar = &FP->second;
    LastVas.push(&FP->second);

    Execbase Sp(new execVset(*this));
    oper.push_back(Sp);
  }

  float operator()() const {
    Lvar->Ihh = 0;
    return -888;
  }

private:
  symtab_t &vars;
  stack<VarCHRM*>& LastVas;
};

struct execVindex : public execbase { // used by execVset
  execVindex(stack<float>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVas_)
    : execbase(eval_, oper_, "Vindex"), LastVas(LastVas_) {}
  execVindex(const execVindex & Cl) : execbase(Cl), LastVas(Cl.LastVas) {}; // copy constructor

  void operator()(const string::iterator b, const string::iterator e) const
  {
    string S(b, e);

    string::size_type eq = S.find_last_not_of("= \t");

    Lvar = LastVas.top();

    Execbase Sp(new execVindex(*this));
    oper.push_back(Sp);

  }

  float operator()() const {
    int T = eval.size();
    switch(T){
      case 2 :
        Lvar->Ill = (int) eval.top() - 1;  // set by re-arrange in execbase
        if(Lvar->Ill < 0) Lvar->Ill = 0;
        eval.pop(); // remove element index
      case 1 :
        Lvar->Ihh = (int) eval.top() - 1;  // set by re-arrange in execbase
        if(Lvar->Ihh < 0) Lvar->Ihh = 0;
        eval.pop(); // remove element index
        break;
      default :
        Lvar->Ihh = 0;
    }
    return Lvar->Ihh;
  }
private:
  stack<VarCHRM*>& LastVas;
};

class execVassign : public execbase {
public:
  execVassign(stack<float>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVas_)
    : execbase(eval_, oper_, "Vassign"), LastVas(LastVas_) {};
  execVassign(const execVassign & Cl) : execbase(Cl), LastVas(Cl.LastVas) {}; // copy constructor

  void operator()(const string::iterator b, const string::iterator e) const {

    Lvar = LastVas.top();
    LastVas.pop();

    Execbase Sp(new execVassign(*this));
    oper.push_back(Sp);
  }

  float operator()() const {
    float X = eval.top();
    Lvar->put(X);
    eval.pop();
    int Cnt = eval.size();
    return X;
  }
  stack<VarCHRM*>& LastVas;
};

class execVget : public execbase {
public:
  execVget(symtab_t &vars_, stack<float>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVar_) :
    execbase(eval_, oper_, "Vget"), vars(vars_), LastVar(LastVar_) {};
  execVget(const execVget & Cl) : execbase(Cl), vars(Cl.vars), LastVar(Cl.LastVar) {}; // copy constructor
  execVget &operator=(const execVget & Cl); //  assigment operator

  void operator()(const string::iterator b, const string::iterator e) const {

    string S(b, e);
    symtab_t::iterator FP = vars.find(S);

    if(FP == vars.end()){
      string SS("macro code - reading from an undefined variable: " + S);
      CRHMException Except(SS , TERMINATE);
      throw CRHMException(Except);
    }

    Lvar = &FP->second;

    string SS(e, e+1); // !!! wrong ???
    string::size_type eq = SS.find_first_not_of(" \t\n");

    if(SS[eq] == '[')
      LastVar.push(&FP->second);

    Execbase Sp(new execVget(*this));
    oper.push_back(Sp);
  }

  float operator()() const {
    Lvar->Ihh = 0;

    float X = Lvar->get(); // in case there is no array element [n]
    eval.push(X);
    return X;
  }

private:
  symtab_t &vars;
  stack<VarCHRM*>& LastVar;
};

struct execVindexVget : public execbase {
  execVindexVget(stack<float>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVar_) : execbase(eval_, oper_, "VindexVget"), LastVar(LastVar_), Indices(0), Idle(true) {}
  execVindexVget(const execVindexVget & Cl) : execbase(Cl), LastVar(Cl.LastVar), Indices(Cl.Indices), Idle(Cl.Idle) {}; // copy constructor

  void operator()(const string::iterator b, const string::iterator e) const
  {
    if(Lvar != LastVar.top() || Idle){ // reset for new variable
      Indices = 0;
      Idle = false;
      Lvar = LastVar.top();
    }
    
    ++Indices;

    if(e[0] != '['){
      LastVar.pop();
      Idle = true;
      
      Execbase Sp(new execVindexVget(*this));
      oper.push_back(Sp);
    }
  }

  float operator()() const {
    switch(Indices){
      case 2 :
        Lvar->Ill = (int) eval.top() - 1;  // set by re-arrange in execbase
        if(Lvar->Ill < 0) Lvar->Ill = 0;
        eval.pop(); // remove element index
      case 1 :
        Lvar->Ihh = (int) eval.top() - 1;  // set by re-arrange in execbase
        if(Lvar->Ihh < 0) Lvar->Ihh = 0;
        eval.pop(); // remove element index
    }

    eval.pop(); // remove variable not indexed

    float X = Lvar->get();
    eval.push(X); // push indexed variable to stack
    int Cnt = eval.size();
    return X;
  }

private:
  stack<VarCHRM*>& LastVar; // could be redundant
  mutable long Indices; // handles 1D & 2D
  mutable bool Idle; // Flags all variable dimensions handled. Required when variable has consecutive references
};

struct execVadd : public execbase { // pushed on to stack!
  execVadd(symtab_t &vars_, stack<float>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVar_) : execbase(eval_, oper_, "Vadd"), vars(vars_), LastVar(LastVar_) {}
  execVadd(const execVadd & Cl) : execbase(Cl), vars(Cl.vars), LastVar(Cl.LastVar) {}; // copy constructor

  void operator()(const string::iterator b, const string::iterator e) const {

    string S(b, e);

    symtab_t::iterator FP = vars.find(S);
    if(FP != vars.end()){
      vars.erase(FP);
    }

    vars.insert(make_pair(S, VarCHRM()));
    FP = vars.find(S);
    FP->second.name = S;
    FP->second.Ihh = 0;

    Lvar = &FP->second;
    LastVar.push(&FP->second);

    Execbase Sp(new execVadd(*this));
    oper.push_back(Sp);
  }

  float operator()() const { // used
    if(!LastVar.empty()) // handles the simple case
      LastVar.pop();

    int Cnt = eval.size();
    return -555;
  }

private:
  symtab_t &vars;
  stack<VarCHRM*>& LastVar;
};

struct execVaddN : public execbase { // pushed on to stack!
  execVaddN(stack<float>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVar_) : execbase(eval_, oper_, "VaddN"), LastVar(LastVar_), Indices(0) {}
  execVaddN(const execVaddN & Cl) : execbase(Cl), LastVar(Cl.LastVar), Indices(Cl.Indices) {}; // copy constructor

  void operator()(const string::iterator b, const string::iterator e) const {

    string S(b, e);

    if(Lvar != LastVar.top()){ // reset for new variable
      Indices = 0;
      Lvar = LastVar.top();
    }

    ++Indices;
    if(Indices == 2){
      Lvar->IndexMaxLay = -1;
      LastVar.pop();
    }

    Execbase Sp(new execVaddN(*this));
    oper.push_back(Sp);
  }

  float operator()() const { // used
    switch(Indices){
      case 2 : // lay
        Lvar->IndexMaxLay = (int) eval.top();  // set by re-arrange in execbase
        if(Lvar->IndexMaxLay < 1) Lvar->IndexMaxLay = 1;
        eval.pop(); // remove element index
        
        Lvar->value2 = new float *[Lvar->IndexMaxLay];
        for(int ii = 0; ii < Lvar->IndexMaxLay; ii++)
          Lvar->value2[ii] = new float[Lvar->IndexMax];
          
        --Lvar->IndexMaxLay; // held as maximum index
        --Lvar->IndexMax; // held as maximum index

        Indices = 0; // one shot
        break;
      case 1 :  // hru
        Lvar->IndexMax = (long) eval.top();  // set by re-arrange in execbase
        if(Lvar->IndexMax < 1) Lvar->IndexMax = 1;
        eval.pop(); // remove element index

        if(Lvar->IndexMaxLay){
          Lvar->kind = VarCHRM::CRHM2; // allocated on next entry above
        }
        else {
          Lvar->kind = VarCHRM::CRHM;
          Lvar->value = new float[Lvar->IndexMax];
          --Lvar->IndexMax;
        }

        Indices = 0; // one shot
        break;
      default :
        eval.pop(); // remove element index
    }
    int Cnt = eval.size();
  }

private:
  stack<VarCHRM*>& LastVar;
  mutable long Indices;
};

struct calculator : public grammar<calculator>
{
    calculator(stack<float>& eval_, symtab_t &vars_,
      list<Execbase>& oper_, list<Execbase> ::iterator & PCiter_, stack<VarCHRM*> & LastVar_, stack<VarCHRM*> & LastVas_)
      : eval(eval_), vars(vars_), oper(oper_), PCiter(PCiter_), LastVar(LastVar_), LastVas(LastVas_) {}

    template <typename ScannerT>
    struct definition
    {
        definition(calculator const& self)
        {
            self.keywords.add("if") ("else") ("endif") ("var")
            ("while") ("endwhile")
            ("sin") ("cos") ("exp") ("log10") ("log") ("estar")
            ("rhoa") ("patmos") ("max") ("min") ("spec_humid");

            routines =
                    ((chseq<>("exp(") >> expression >> ')')  [make_op1(ExpC<const float>(), self.eval, self.oper)])
                |   ((chseq<>("log(") >> expression >> ')')  [make_op1(LogC<const float>(), self.eval, self.oper)])
                |   ((chseq<>("max(") >> expression >> *(ch_p(',')) >> expression >> ')')  [make_op2(MaxC<const float>(), self.eval, self.oper)])
                |   ((chseq<>("min(") >> expression >> *(ch_p(',')) >> expression >> ')')  [make_op2(MinC<const float>(), self.eval, self.oper)])
//                |   ((chseq<>("log10(") >> expression >> ')')[make_op1(Log10C<const float>(), self.eval, self.oper)]) //
                ;
            hydrology =
                    ((chseq<>("estar(") >> expression >> ')')  [make_op1(estarC<const float>(), self.eval, self.oper)])
//                |   ((chseq<>("patmos(") >> expression >> ')')  [make_op1(patmosC<const float>(), self.eval, self.oper)]) //
//                |   ((chseq<>("spec_humid(") >> expression >> *(ch_p(',')) >> expression >> ')')  [make_op2(spec_humidC<const float>(), self.eval, self.oper)]) //
//                |   ((chseq<>("rhoa(") >> expression >> *(ch_p(',')) >> expression >> *(ch_p(',')) >> expression >> ')')  [execRHOa(self.eval, self.oper)]) //
                ;
            trignometry =
                    ((chseq<>("sin(") >> expression >> ')')  [make_op1(SineC<const float>(), self.eval, self.oper)])
                |   ((chseq<>("cos(") >> expression >> ')')  [make_op1(CosC<const float>(), self.eval, self.oper)])
//                |   ((chseq<>("tan(") >> expression >> ')')  [make_op1(TanC<const float>(), self.eval, self.oper)])
                ;
            factor =
                    routines
                |   hydrology
                |   trignometry
                |   real_p[execPush(self.eval, self.oper)]
                |   '(' >> logical >> ')'
                |   ('-' >> factor)[execNegate(self.eval, self.oper)]
                |   ('!' >> factor)[execInvert(self.eval, self.oper)]

                |   (identifier [execVget(self.vars, self.eval, self.oper, self.LastVar)]
                    >>  *('[' >> factor >> ']')  [execVindexVget(self.eval, self.oper, self.LastVar)])
                ;

            term2 =
                factor
                >> *(('^' >> factor)[make_op2(PowerC<const float>(), self.eval, self.oper)]
                    )
                    ;

            term1 =
                term2
                >> *(   ('*' >> term2)[make_op2(multiplies<const float>(), self.eval, self.oper)]
                    |   ('/' >> term2)[make_op2(divides<const float>(),    self.eval, self.oper)]
                    |   ('%' >> term2)[make_op2(::modulus<const float>(),  self.eval, self.oper)]
                    )
                    ;

            expression =
                term1
                >> *(   ('+' >> term1)[make_op2(plus<const float>(),  self.eval, self.oper)]
                    |   ('-' >> term1)[make_op2(minus<const float>(), self.eval, self.oper)]
                    )
                    ;

            logical2 =
                expression
                >> *(            (">"   >> expression) [make_op2B(L_GT<float>(), self.eval, self.oper)]
                    |   (strlit<>(">=") >> expression) [make_op2B(L_GE<float>(), self.eval, self.oper)]
                    |   (strlit<>("<=") >> expression) [make_op2B(L_LE<float>(), self.eval, self.oper)]
                    |            ('<'   >> expression) [make_op2B(L_LT<float>(), self.eval, self.oper)]
                    |   (strlit<>("==") >> expression) [make_op2B(L_EQ<float>(), self.eval, self.oper)]
                    |   (strlit<>("!=") >> expression) [make_op2B(L_NE<float>(), self.eval, self.oper)]
                    )
                    ;

            logical1 =
                logical2
                >> *(   (strlit<>("&&") >> logical2) [make_op2BB(L_and<bool>(), self.eval, self.oper)]
                    |   (strlit<>("AND") >> logical2) [make_op2BB(L_and<bool>(), self.eval, self.oper)]
                    )
                    ;

            logical =
                logical1
                >> *(   (strlit<>("||") >> logical1) [make_op2BB(L_or<bool>(), self.eval, self.oper)]
                    |   (strlit<>("OR") >> logical1) [make_op2BB(L_or<bool>(), self.eval, self.oper)]
                    )
                    ;

            IF =
                    (((strlit<>("if")
                >> *(blank_p)
                >> "(")
                >>  logical >> ')')  [execIf(self.eval, self.oper, self.PCiter, self.PCiterIF)])
                >>  (*(statement))
                >>  (*(strlit<>("else"))  [execElse(self.eval, self.oper, self.PCiter, self.PCiterIF)])
                >>  (*(statement))
                >>  ((strlit<>("endif")) [execEndif(self.eval, self.oper, self.PCiter, self.PCiterIF)])
                ;

            WHILE =
                    (((strlit<>("while") [execWhile(self.eval, self.oper, self.PCiter, self.PCiterWHILE)])
                >> *(blank_p)
                >> "(")
                >>  logical >> ')')  [execWhile2(self.eval, self.oper, self.PCiter, self.PCiterWHILE)]
                >>  (*(statement))
                >>  ((strlit<>("endwhile")) [execEndwhile(self.eval, self.oper, self.PCiter, self.PCiterWHILE)])
                ;

            FOR =
                    (((strlit<>("for")
                >> *(blank_p)
                >> "("
                >>  (assignment >> *(',' >> assignment) >> ';'))) [execFor(self.eval, self.oper, self.PCiter, self.PCiterWHILE)])
                >>  ((logical >> ';')  [execForC(self.eval, self.oper, self.PCiter, self.PCiterWHILE)])
                >>  ((assignment >> *(',' >> assignment) >> ')') [execForI(self.eval, self.oper, self.PCiter, self.PCiterWHILE)])
                >>  (*(statement))
                >>  ((strlit<>("endfor")) [execEndFor(self.eval, self.oper, self.PCiter, self.PCiterWHILE)])
                ;

            identifier =
                lexeme_d [
                       (alpha_p >> *(alnum_p | ch_p('_') | '@' | '#' ))
                       - (self.keywords >> anychar_p - (alnum_p | ch_p('_') | '@' | '#' ))
                       
                ]
                ;

            assignment =
                IF
                | (  identifier >> *('[' >> expression >> ']') >> '='
                )  [execVset(self.vars, self.eval, self.oper, self.LastVas)][execVindex(self.eval, self.oper, self.LastVas)]
                >> expression [execVassign(self.eval, self.oper, self.LastVas)]
                ;

            var_decl =
                  identifier[execVadd(self.vars, self.eval, self.oper, self.LastVar)]
                >> *('[' >> factor >> ']')[execVaddN(self.eval, self.oper, self.LastVar)]
                ;

            declaration =
                "var" >> var_decl >> *(',' >> var_decl)
                ;

            comment =
                lexeme_d [
                   ("//"   >> *(anychar_p - '\n'))
                |    ("rem " >> *(anychar_p - '\n'))
                |    ("/*"   >> *(anychar_p - "*/") >> "*/")
                ]
                ;

            statement =
                ( declaration
                  | assignment
                  | IF
                  | WHILE
                  | FOR
                  | comment
                  | end_p
                  | eol_p
                  | ch_p(';')
                  | blank_p
                )
                ;
        }
        rule<ScannerT>      statement, declaration, var_decl, identifier,
                            assignment, expression, term, term1, term2,
                            factor, routines, hydrology, trignometry, logical, logical1, logical2,
                            comment, IF, WHILE, FOR;

        rule<ScannerT> const&
        start() const { return statement; }
    };

public:
    symtab_t & vars;
    symbols<char*> keywords;

    stack<float> & eval;
    stack<VarCHRM*> & LastVar;
    stack<VarCHRM*> &LastVas;

    list<Execbase> & oper;
    list<Execbase> ::iterator & PCiter;

    mutable stack<list<Execbase> ::iterator> PCiterIF;
    mutable stack<list<Execbase> ::iterator> PCiterWHILE;
    mutable stack<list<Execbase> ::iterator> PCiterFOR;
};

#endif

