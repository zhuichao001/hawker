#include<bits/stdc++.h>
#include<stdio.h>

using namespace std;

int64_t littlePrimes[10] = {2,3,5,7,11,13,17,19,23,29};

int64_t quickMultiply(int64_t a, int64_t b, int64_t c){
    int64_t ans = 0, res = a;
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
int64_t quickPower(int64_t a, int64_t b, int64_t m){
    int64_t ans = 1;
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
bool isPrime(int64_t x){ 
    int64_t i, j, k;
    int64_t s = 0, t = x-1;
    if(x == 2) return true;
    if(x < 2 || !(x & 1)) return false;
    while(!(t & 1)){ //x-1 = (2^s)*t
        s++;
        t >>= 1;
    }

    for(i = 0; i < 10 && littlePrimes[i] < x; i++){
        int64_t a = littlePrimes[i];
        int64_t b = quickPower(a, t, x); //a^t
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
