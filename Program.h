#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>    // std::reverse
#include <sstream>
#include <exception>
#include <regex>
#include "Instruction.h"
#include "Tag.h"

using namespace std;




class Program{
  vector<Instruction*> instructions_;
  vector<Tag*> tags_;
  string fileName_;
public:
  Program(string);
  ~Program();


  Instruction* getInstruction(unsigned line);
  void reset(string);
  bool reachHalt(unsigned);
  void show();
  int getLineByTag(string);
  string getFileName ();
private:
  void load(string);
  void setTags(string);
  string readFile(string);
  void parseInstructions(string);
  bool existsTag(string);
  string getTagFromString(string);
};



#endif
