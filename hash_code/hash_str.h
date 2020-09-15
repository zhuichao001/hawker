#ifndef _H_HASH_STR_H_
#define _H_HASH_STR_H_

int hash_str(const char* src, const int len){
    int seed = 131313;
    int roll = 63689;
    int code = 2166136261;
    for(int i=0; i<len; ++i){
        seed *= roll;
        code = (seed*code) ^ int(src[i]); 

        code += code << 21;
        code ^= code >> 9;

        code += code << 14;
        code ^= code >> 18;

        code += code << 7;
        code ^= code >> 27;
    }
    return code;
}

#endif
