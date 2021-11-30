#ifndef _H_HASH_INT_H_
#define _H_HASH_INT_H_

#include "hash_str.h"

uint64_t hash_int(int d){
    static HashFunc hash;
    return hash(d);
}

#endif
