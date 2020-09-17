#ifndef _H_MILLER_ROBIN_H_
#define _H_MILLER_ROBIN_H_

#include <stdint.h>

uint64_t littlePrimes[10] = {2,3,5,7,11,13,17,19,23,29};

uint64_t quickMultiply(uint64_t a, uint64_t b, uint64_t c){
    uint64_t ans = 0, res = a;
    while(b){
        if(b & 1){
            ans = (ans + res) % c;
        }
        res = (res + res) % c;
        b >>= 1;
    }
    return ans;
}


//(a^b)%m
uint64_t quickPower(uint64_t a, uint64_t b, uint64_t m){
    uint64_t ans = 1;
    while(b){
        if(b & 1){
            ans = ans * a % m;
        }
        a = a * a % m;
        b >>= 1;
    }
    return ans;
}


//Miller Rabin
bool isPrime(uint64_t x){ 
    uint64_t i, j, k;
    uint64_t s = 0, t = x-1;
    if(x == 2) return true;
    if(x < 2 || !(x & 1)) return false;
    while(!(t & 1)){ //x-1 = (2^s)*t
        s++;
        t >>= 1;
    }

    for(i = 0; i < 10 && littlePrimes[i] < x; i++){
        uint64_t a = littlePrimes[i];
        uint64_t b = quickPower(a, t, x); //a^t
        for(j = 1; j <= s; j++){
            k = quickMultiply(b,b,x); //b^2
            if(k == 1 && b != 1 && b != x-1){
                return false;
            }
            b = k;
        }
        if(b != 1){
            return false;
        }
    }
    return true; //maybe primer
}

#endif
