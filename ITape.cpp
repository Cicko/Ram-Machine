#include "ITape.h"
#include <fstream>
#include <iostream>

using namespace std;

ITape::ITape(string fileName) {
  load(fileName);
}


ITape::~ITape(){
   clear();
}

void ITape::load(string fileName) {
  inx_ = 0;
  fstream file;
  int num;
  fileName_ = fileName;
  file.open(fileName.c_str(), ios::in );

  if(file.is_open()) {
      nodes_.clear();
    while(file >> num){
      nodes_.push_back(num);
    }
    file.close();
  }
  else{
      cerr << "El fichero no existe" << endl;
  }
}

int ITape::read()
{
  if (inx_ < nodes_.size())
      return nodes_[inx_++];
  else
      return 0;
}

bool ITape::hasNext()
{
  return inx_ < nodes_.size();
}

void ITape::reset(string fileName)
{
  load(fileName);
}

void ITape::reset() {
  inx_ = 0;
}
