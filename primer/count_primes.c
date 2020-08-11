#include <stdio.h>

int countPrimes(int n) {
    bool *isPrim = new bool[n+1];
    for (int i = 2; i <= n; ++i){
        isPrim[i] = true;
    }

    int count = n-1; //except 1
    for (int i = 2; i * i <= n; ++i) {
        if (isPrim[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrim[j] = false;
                --count;
            }
       }
    }
    
    return count;
}

int main(){
    int c = countPrimes(9);
    printf("count:%d\n", c);
    return 0;
}

