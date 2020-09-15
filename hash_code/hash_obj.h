#ifndef _H_HASH_OBJ_H_
#define _H_HASH_OBJ_H_

#include "hash_str.h"
#include <string>

using namespace std;

class HashBase{
  public:
    virtual string ToStr()=0;
};

int hash_obj(HashBase *obj ){
    string val = obj->ToStr();
    return hash_str(val.c_str(), val.length());
}

#endif
