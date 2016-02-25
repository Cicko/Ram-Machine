#include <iostream>
#include "Tape.h"

using namespace std;

Tape::Tape():
  nodes_(), inx_(0)
  {
  }

Tape::~Tape(){}

void Tape::clear()
{
  nodes_.clear();
  inx_ = 0;
}

unsigned Tape::getInx()
{
  return inx_;
}

void Tape::show()
{
  cout << "[" ;
  for (int i = 0; i < nodes_.size(); i++)
  {
    cout << " " << nodes_[i];
    if (i < nodes_.size()-1) {
      cout << ",";
    }
  }
  cout << "]" << endl;
  cout << endl;
}

string Tape::getFileName () {
  return fileName_;
}
