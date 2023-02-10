#include <stdio.h>

//数组中出现次数超过一半的数字

int more_than_half(int a[], int n){
    int v = a[0];
    int freq = 1;
    for(int i=1; i<n; ++i){
        if(a[i]==v){
            ++freq;
        }else{
            if(--freq==0){
                v = a[i];
                freq=1;
            }
        }
    }
    return v;
}

int main(){
    int a[]={1,2,3,3,2,3,3};
    fprintf(stderr, "%d\n", more_than_half(a, sizeof(a)/sizeof(a[0])));
    return 0;
}
