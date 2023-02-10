#include <stdio.h>

//不用加减乘除做加法
//求2个整数之和

int sum(int a,int b){
    while(b!=0){
        int s = a^b;
        int carry = (a&b)<<1;
        a = s;
        b = carry;
    }
    return a;
}


int main(){
    fprintf(stderr, "113 + -221=%d\n", sum(113,-221));
    return 0;
}
