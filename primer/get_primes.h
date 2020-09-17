#include "miller_rabin_primes.h"


uint64_t getPrime_GT(uint64_t start){
    while(true){
        if(isPrime(start)){
            return start;
        }
        start++;
    }
}
