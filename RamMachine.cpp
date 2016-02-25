#include "RamMachine.h"

#define ACCUM 0

#define INDIRECT '*'
#define DIRECT 'd'
#define IMMEDIATE '='

RamMachine::RamMachine(string in, string out, string program, int size)
{
  pc_ = 0;
  inTape_ = new ITape(in);
  outTape_ = new OTape(out);
  program_ = new Program(program);
  memory_ = new Memory(size);
  error_ = false;
}

RamMachine::~RamMachine() {
  delete memory_;
  delete inTape_;
  delete outTape_;
  delete program_;
}


void RamMachine::runProgram (bool trace) {
  pc_ = 0;
  error_ = false;
  outTape_->reset ();
  memory_->reset ();
  inTape_->reset();
  bool halt = false;

  while (!halt && !error_)
  {

    bool salto = false;
    Instruction * actual = program_->getInstruction (pc_);

    if (actual->getOp () == "read") {               // READ
      int inTapeData = inTape_->read ();
      switch (actual->getType ()) {
        case INDIRECT:   // Indirect
          memory_->write (inTapeData,memory_->read (stoi (actual->getOperand ())));
          break;
        case DIRECT:   // Direct
          memory_->write (inTapeData,stoi (actual->getOperand ()));
          break;
        case IMMEDIATE:   // Immediate
          cout << "El modo inmediato no tiene sentido en la operacion READ. Saliendo al menu..." << endl;
          error_ = true;
          break;
        default:
          cout << "No se reconoce este tipo de READ. Saliendo al menu..." << endl;
          error_ = true;
      }
    }
    else if (actual->getOp () == "write") {         // WRITE
      switch (actual->getType ()) {
        case INDIRECT:
          outTape_->write (memory_->read (memory_->read (stoi (actual->getOperand ()))));
          break;
        case DIRECT:
          outTape_->write (memory_->read (stoi (actual->getOperand ())));
          break;
        case IMMEDIATE:
          outTape_->write (stoi (actual->getOperand()));
          break;
        default:
          cout << "No se reconoce este tipo de WRITE. Saliendo al menu..." << endl;
          error_ = true;
      }
    }
    else if (actual->getOp () == "load") {          // LOAD
      switch (actual->getType ()) {
        case INDIRECT:
          memory_->write (memory_->read (memory_->read (stoi (actual->getOperand ()))),ACCUM);
          break;
        case DIRECT:
          memory_->write (memory_->read (stoi (actual->getOperand ())),ACCUM);
          break;
        case IMMEDIATE:
          memory_->write (stoi (actual->getOperand ()),ACCUM);
          break;
        default:
          cout << "No se reconoce este tipo de LOAD. Saliendo al menu..." << endl;
          error_ = true;
      }
    }
    else if (actual->getOp() == "store") {
      switch (actual->getType()) {
        case INDIRECT:
          memory_->write (memory_->read (ACCUM), memory_->read (stoi (actual->getOperand())));
          break;
        case DIRECT:
          memory_->write (memory_->read (ACCUM),stoi (actual->getOperand()));
          break;
        case IMMEDIATE:
          cout << "No esta permitido el modo inmediato en la operacion STORE. Saliendo al menu.." << endl;
          error_ = true;
          break;
        default:
          cout << "No se reconoce este tipo de STORE. Saliendo al menu..." << endl;
          error_ = true;
      }
    }
    else if (actual->getOp() == "add") {
      switch (actual->getType()) {
        case INDIRECT:
          memory_->write(memory_->read (ACCUM) + memory_->read (memory_->read (stoi (actual->getOperand()))),ACCUM);
          break;
        case DIRECT:
          memory_->write (memory_->read (ACCUM) + memory_->read (stoi (actual->getOperand ())),ACCUM);
          break;
        case IMMEDIATE:
          memory_->write (memory_->read (ACCUM) + stoi (actual->getOperand ()),ACCUM);
          break;
        default:
          cout << "No se reconoce este tipo de SUB. Saliendo al menu..." << endl;
          error_ = true;
      }
    }
    else if (actual->getOp() == "sub") {
      switch (actual->getType()) {
        case INDIRECT:
          memory_->write(memory_->read (ACCUM) - memory_->read (memory_->read (stoi (actual->getOperand()))),ACCUM);
          break;
        case DIRECT:
          memory_->write (memory_->read (ACCUM) - memory_->read (stoi (actual->getOperand ())),ACCUM);
          break;
        case IMMEDIATE:
          memory_->write (memory_->read (ACCUM) - stoi (actual->getOperand ()),ACCUM);
          break;
        default:
          cout << "No se reconoce este tipo de SUB. Saliendo al menu..." << endl;
          error_ = true;
      }
    }
    else if (actual->getOp() == "mul") {
      switch (actual->getType()) {
        case INDIRECT:
          memory_->write(memory_->read (ACCUM) * memory_->read (memory_->read (stoi (actual->getOperand()))),ACCUM);
          break;
        case DIRECT:
          memory_->write (memory_->read (ACCUM) * memory_->read (stoi (actual->getOperand ())),ACCUM);
          break;
        case IMMEDIATE:
          memory_->write (memory_->read (ACCUM) * stoi (actual->getOperand ()),ACCUM);
          break;
        default:
          cout << "No se reconoce este tipo de MUL. Saliendo al menu..." << endl;
          error_ = true;
      }
    }
    else if (actual->getOp() == "div") {
      switch (actual->getType()) {
        case INDIRECT:
          memory_->write(memory_->read (ACCUM) / memory_->read (memory_->read (stoi (actual->getOperand()))),ACCUM);
          break;
        case DIRECT:
          memory_->write (memory_->read (ACCUM) / memory_->read (stoi (actual->getOperand ())),ACCUM);
          break;
        case IMMEDIATE:
          memory_->write (memory_->read (ACCUM) / stoi (actual->getOperand ()),ACCUM);
          break;
        default:
          cout << "No se reconoce este tipo de DIV. Saliendo al menu..." << endl;
          error_ = true;
      }
    }
    else if (actual->getOp () == "jump") {
      salto = true;
      jumpManager (actual);
    }
    else if (actual->getOp () == "jzero") {
      if (memory_->read (ACCUM) == 0) {
        salto = true;
        jumpManager (actual);
      }
    }
    else if (actual->getOp() == "jgtz") {
      if (memory_->read (ACCUM) > 0) {
        salto = true;
        jumpManager (actual);
      }
    }
    else if (actual->getOp() == "halt") {
      cout << "Se ha alcanzado HALT en la linea " << pc_ << ". Ahora se procedera a guardar el contenido en el fichero de salida." << endl;
      halt = true;
    }
    if (trace) {
      showActualState (actual);
    }
    if(error_) {
      cout << "We get error at line " << pc_ << endl;
      break;
    }
    if(!salto)
      pc_++;
  }
  saveToOutputTape ();
}

void RamMachine::showActualState (Instruction* actual) {
  cout << "Input tape:" << endl;
  inTape_->show();
  actual->show();
  memory_->show();
  cout << "Contenido de la cinta de salida: " ;
  outTape_->show();
  cout << endl << endl << "Pulse Enter para continuar..." << endl;
  cin.get();
}

void RamMachine::saveToOutputTape () {
  outTape_->saveToFile();
  cout << "Pulse Enter para volver al menu..." << endl;
  cin.get();
  cin.get();
  system("clear");
}


void RamMachine::resetMachine (string in, string out, string program)
{
  resetInTape(in);
  resetOutTape(out);
  resetProgram(program);
}


void RamMachine::resetProgram (string fileName) {
  program_->reset (fileName);
  memory_->reset();
  outTape_->reset();
}

void RamMachine::resetInTape (string fileName) {
  inTape_->reset (fileName);
  memory_->reset();
  outTape_->reset();
}

void RamMachine::resetOutTape (string fileName) {
  outTape_->reset (fileName);
}


void RamMachine::showProgram () {
  program_->show ();
}

void RamMachine::showMemory () {
  memory_->show ();
}

void RamMachine::showInputTape () {
  inTape_->show ();
}


void RamMachine::jumpManager (Instruction* actual) {
  pc_ = program_->getLineByTag (actual->getOperand());
  if (pc_ == -1) {
    cout << "el Tag " << actual->getOperand () << " no se encuentra en el programa.\nSaliendo al menu..." << endl;
    error_ = true;
  }
}

string RamMachine::getInputFileName() {
  return inTape_->getFileName ();
}

string RamMachine::getProgramFileName () {
  return program_->getFileName ();
}

string RamMachine::getOutputFileName () {
  return outTape_->getFileName ();
}
