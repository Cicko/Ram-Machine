/****
Author: Rudolf Cicko
Date: 23-02-16
Description: Ram Machine class
****/


#ifndef _RAMMACHINE_H_
#define _RAMMACHINE_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

#include "OTape.h"
#include "ITape.h"
#include "Memory.h"
#include "Program.h"
#include "Instruction.h"

using namespace std;



class RamMachine {
  ITape * inTape_;
  OTape * outTape_;
  Memory * memory_;
  Program * program_;
  unsigned pc_;
  bool error_;

public:
  RamMachine (string in, string out, string program, int size); // Cinta de entrada, Cinta de salida, programa y tamaño de memoria
  ~RamMachine ();

  /** \brief This function execute the uploaded program.
       * \param if trace is true it will show memory state in each instruction
       * \return No value
       *
       * This method uses inTape_ as input data, program_ to decide the set of operations to perform
       *
       *
       */
  void runProgram (bool);
  void resetMachine (string,string,string);
  void resetProgram (string);
  void resetInTape (string);
  void resetOutTape (string);
  void showProgram ();
  void showMemory ();
  void showInputTape ();
  void showActualState (Instruction*);

  string getInputFileName ();
  string getProgramFileName ();
  string getOutputFileName ();

  void saveToOutputTape ();

private:
  void jumpManager (Instruction*);
};

#endif
