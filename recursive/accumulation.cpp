#include <stdio.h>

//求 1+2+...+n
//要求不用乘除法，for/while/if/else/switch等关键字及条件判断语句

int sum(int n){
    if(n<=1){
        return n;
    }
    return n+sum(n-1);
}

int main(){
    int v = 5;
    fprintf(stderr, "sum of %d:%d\n", v, sum(v));
}
