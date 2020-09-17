#ifndef _H_HASH_FUNC_H_
#define _H_HASH_FUNC_H_

#include<stdint.h>
#include<string>

using namespace std;

class HashFunc{
  uint64_t seed;
  uint64_t roll;
  public:
    HashFunc(uint64_t _roll=63689, uint64_t _seed=131313):roll(_roll),seed(_seed){} 

    void setKey(uint64_t _roll=63689, uint64_t _seed=131313){
        _roll = roll;
        _seed = seed;
    }

    uint64_t operator()(const char*src, const int len)const{
        uint64_t _seed(seed), _roll(roll);
        uint64_t code = 2166136261;
        for(int i=0; i<len; ++i){
            _seed *= _roll;
            code = (_seed*code) ^ uint64_t(src[i]); 

            code += code << 21;
            code ^= code >> 9;

            code += code << 14;
            code ^= code >> 18;

            code += code << 7;
            code ^= code >> 27;
        }
        return code;
    }

    uint64_t operator()(const string &src)const{
        return (*this)(src.c_str(), src.length());
    }
};

#endif
