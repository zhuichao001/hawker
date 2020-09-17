#include "count_primes.h"
#include "miller_rabin_primes.h"
#include <stdio.h>


void test_count_primes(){
    int64_t x;
    scanf("%d",&x);
    int c = countPrimes(x);
    printf("count:%d\n", c);
}

void test_miller_rabin(){
    int64_t x;
    scanf("%lld",&x);
    if(isPrime(x)) printf("Yes");
    else printf("No");
}

int main(){
    return 0;
}
