#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <string>
#include <iostream>

using namespace std;

class Instruction {
  int line_;
  string tag_;
  string op_; // Operations: ADD, SUB, MULT,..
  char type_; // Types: '=', 'd' or '*'
  string operand_; // Register, number or nothing
  
public:
  Instruction (int line, string tag, string op, char type, string operand)
  {
    line_ = line;
    tag_ = tag;
    op_ = op;
    type_ = type;
    operand_ = operand;
  }

  Instruction () {
    line_ = -1;
    tag_ = "";
    op_ = "";
    type_ = '\0';
    operand_ = "";
  }

  ~Instruction () {}

  inline const int getLine () {
    return line_;
  }

  inline void setLine (int line) {
    line_ = line;
  }

  inline const string getTag () {
    return tag_;
  }

  inline void setTag (string tag) {
    tag_ = tag;
  }

  inline const string getOp () {
    return op_;
  }

  inline void setOp (string op) {
    op_ = op;
  }

  inline const char getType () {
    return type_;
  }

  inline void setType (char type) {
    type_ = type;
  }

  inline const  string getOperand () {
    return operand_;
  }

  inline void setOperand (string operand) {
    operand_ = operand;
  }

  inline void show () {
    cout << "[" << tag_ << "] at line " << line_ << " <" << op_ << " " << type_ << " " << operand_ << "> " << endl;
  }
};

#endif
