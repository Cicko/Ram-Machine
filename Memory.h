#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <vector>
#include <string>

typedef unsigned t_register; // Registers will be
typedef int t_data;

using namespace std;


class Memory{
    vector<t_data> registers_;
  public:
    Memory(int);
    ~Memory();

    void write(t_data,t_register);
    t_data read(t_register);
    void clear();
    void show();
    void reset();
};


#endif
