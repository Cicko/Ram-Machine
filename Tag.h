#ifndef _Tag_
#define _Tag_

#include <string>

using namespace std;

class Tag {
    string id_;
    unsigned line_;
public:
    Tag (string id, unsigned line) {
      id_ = id;
      line_ = line;
    }

    ~Tag() {}

    inline const string getId () {
      return id_;
    }

    inline const unsigned getLine () {
      return line_;
    }

    inline const void show () {
      cout << "< TAG: " << id_ << "  at line: " << line_ << " >" << endl;
    }
};


#endif
