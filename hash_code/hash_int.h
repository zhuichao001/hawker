#ifndef _H_HASH_INT_H_
#define _H_HASH_INT_H_

#include "hash_str.h"

int hash_int(int d){
    const int LEN = 4;
    char src[LEN];
   
    for(int i=0; i<LEN; ++i){
        src[i] = d & 0xFF;
        d >>= 8;
    }
    return hash_str(src, LEN);
}

#endif
