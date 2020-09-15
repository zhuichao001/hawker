#include <stdio.h>

/*
 * 计算比某个数大的N个素数
 */


inline void setNotPrime(char * bitMap, int i){
    int idx = i / 8;
    int bit = i % 8;
    bitMap[idx] &= ~(1<<bit);
}

inline bool isPrime(char * bitMap, int i){
    int idx = i / 8;
    int bit = i % 8;
    return 0!=(bitMap[idx]&(1<<bit));
}

void getPrimes(const int lowat, int res[], int res_len) {
    int n = res_len*lowat*lowat;

    int size = (n+7)/8;
    char *bitMap = new char[size];
    for (int i = 0; i <= size; ++i) {
        bitMap[i] = 255;
    }

    int found = 0;
    for (int i = 2; i * i <= n; ++i) {
        if (isPrime(bitMap, i)) {
            for (int j = i * i; j <= n; j += i) {
                setNotPrime(bitMap, j);
            }
            if(i>=lowat){
                res[found++] = i;
            }
            if(found==res_len)break;
       }
    }

    delete []bitMap;
}

int main(){
    int a[8];
    getPrimes(1001, a, 8);
    for(int i=0; i<8; ++i){
        printf("%d\n", a[i]);
    }
    return 0;
}

