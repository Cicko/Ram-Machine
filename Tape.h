#ifndef _TAPE_H_
#define _TAPE_H_

#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

class Tape{
protected:
    vector<int> nodes_;
    unsigned inx_;
    string fileName_;
public:
    Tape();
    ~Tape();

    void clear(); // reinitialize node vector
    unsigned getInx();
    void show();
    string getFileName();
};


#endif
