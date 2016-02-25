
#include "OTape.h"
#include <fstream>
#include <iostream>

using namespace std;

OTape::OTape(string fileName){
  fileName_ = fileName;
}

OTape::~OTape(){
  clear();
}


void OTape::write(int v) {
  nodes_.push_back(v);
  inx_++;
}


void OTape::saveToFile() {
  ofstream outFile;
  outFile.open(fileName_.c_str());
  char option;
  cout << "¿Desea ver el contenido que se va a volcar en la cinta de salida? (s/n): " ;
  cin >> option;
  if (option == 's')
     show();

  for(int i = 0; i < nodes_.size(); i++) {
    outFile << nodes_[i] << " ";
  }
  outFile.close();
}

void OTape::reset() {
  nodes_.clear();
  inx_ = 0;
}

void OTape::reset(string fileName) {
  nodes_.clear();
  inx_ = 0;
  fileName_ = fileName;
}
