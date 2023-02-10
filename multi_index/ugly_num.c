#include <stdio.h>
#include <cmath>

//只包含因子 2，3，5的数叫做丑数；比如 6(2x3), 8(2x2x2) 是丑数（ugly number）
//求按从小到大的顺序，第1500个丑数

int ugly(const int seq){
    int u2=0, u3=0, u5=0;
    int ugs[seq];
    ugs[0]=1;

    for(int i=1; i<seq; ++i){
        ugs[i] = std::min(ugs[u2]*2, std::min(ugs[u3]*3, ugs[u5]*5));
        if(ugs[u2]*2 <= ugs[i])++u2;
        if(ugs[u3]*3 <= ugs[i])++u3;
        if(ugs[u5]*5 <= ugs[i])++u5;
    }
    return ugs[seq-1];
}

int main(){
    for(int seq = 1; seq<20; ++seq){
        fprintf(stderr, "the %dth ugly number:%d\n", seq, ugly(seq));
    }
    return 0;
}
