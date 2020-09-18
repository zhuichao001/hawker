
inline int abs(int x){
    int y = x >>31;
    return (x+y)^y;
}

inline int max(int x, int y){
    return y&((x-y)>>31) | x&~((x-y)>>31);
}

inline int average(int x, int y){
    return (x&y) + ((x^y)>>1);
}

//x * y % p
long long multiply(long long x, long long y, long long p){
    long long ret = 0;
    for(; y; y>>=1){
        if(y&1）ret = (ret+x)%p;
        x = (x+x)%p;
    }
    return ret;
}
