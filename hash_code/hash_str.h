#ifndef _H_HASH_STR_H_
#define _H_HASH_STR_H_

#include "hash_func.h"

int hash_str(const char* src, const int len){
    static HashFunc hash;
    return hash(src, len);
}

#endif
