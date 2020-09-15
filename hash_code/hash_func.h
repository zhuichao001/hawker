#ifndef _H_HASH_FUNC_H_
#define _H_HASH_FUNC_H_

class HashFunc{
  int seed;
  int roll;
  public:
    HashFunc(int _roll=63689, int _seed=131313):roll(_roll),seed(_seed){} 
    int operator()(const char*src, const int len)const{
        int _seed(seed), _roll(roll);
        int code = 2166136261;
        for(int i=0; i<len; ++i){
            _seed *= _roll;
            code = (_seed*code) ^ int(src[i]); 

            code += code << 21;
            code ^= code >> 9;

            code += code << 14;
            code ^= code >> 18;

            code += code << 7;
            code ^= code >> 27;
        }
        return code;
    }
};

#endif
