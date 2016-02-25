#ifndef _ITAPE_H_
#define _ITAPE_H_

#include "Tape.h"
#include <string>

// Input tape
class ITape : public Tape{
public:
  ITape(string);
  ~ITape();
  void load(string);
  void reset(string);
  void reset();
  int read();
  bool hasNext();
};


#endif
