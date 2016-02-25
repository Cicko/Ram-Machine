#include "Memory.h"
#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;

Memory::Memory(int size) {
  registers_.resize(size); // 10 registers
}

Memory::~Memory() {}

void Memory::write(t_data data, t_register reg) {
    registers_[reg] = data;          // because reg have format RX where X is the number of register_t
}                                    // we only take the number and use it as index in the registers vector.



t_data Memory::read(t_register reg) {
  return registers_[reg];
}

void Memory::clear() {
  registers_.clear();
}

void Memory::reset() {
  int size = registers_.size();
  registers_.clear();
  registers_.resize(size,0);
}

void Memory::show() {
    cout << "\u2605 Memory \u2605 " << endl;
    for(int i = 0; i < registers_.size(); i++)
      cout << "R" << i << " \u27F9   " << registers_[i] <<  endl;
}
