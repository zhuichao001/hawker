#ifndef _H_BROOM_FILTER_H_
#define _H_BROOM_FILTER_H_

#include "get_primes.h"
#include "hash_func.h"
#include <memory.h>
#include <stdio.h>
#include <string>

using namespace std;


class BloomFilter{
    uint8_t *flags;
    const int size;

    HashFunc *hashers;
    int hashnum;

  public:
    BloomFilter(int _bytes):size(((_bytes+7)/8)<<3){
        flags = new uint8_t[size];
        memset(flags, 0, sizeof(uint8_t)*size);

        hashnum = size>>3;
        hashers = new HashFunc[hashnum];

        uint64_t roll=63689, seed = 131313;
        for(int i=0; i<hashnum; ++i){
            roll = getPrime_GT(roll);
            seed = getPrime_GT(seed);
            hashers[i].SetSeed(roll, seed);
        }
    }

    void _set_flag(int start, uint64_t val){
        for(int i=7; i>=0; --i){
            flags[start+i] |= uint8_t(val&0xFF); 
            val >>= 8;
        }
    }

    void _print_flag(){
        for(int i=0; i<size; ++i){
            printf("0x%02x ", uint8_t(flags[i]));
        }
        printf("\n");
    }

    uint64_t _get_flag(int start){
        uint64_t val = 0;
        for(int i=0; i<8; ++i){
           val = ((val<<8) | flags[start+i]);
        }
        return val;
    }

    void insert(string key){
        for(int i=0; i<hashnum; ++i){
            uint64_t code =  hashers[i](key);
            _set_flag(i*8, code);
        }
    }

    bool exist(string key){
        for(int i=0; i<hashnum; ++i){
            uint64_t code = hashers[i](key);
            uint64_t model = _get_flag(i*8);
            if((model&code)!=code){
                return false;
            }
        }
        return true;
    }
};

#endif
