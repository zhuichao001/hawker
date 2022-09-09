#include <stdio.h>

int longest_mountain(int *arr, int len){
    if(arr==nullptr || len<=2){
        return 0;
    }

    int i = 1;
    while(i<len && arr[i]<arr[i-1])++i;

    int maxlen = 0;
    int curlen = 1;
    int direction = 1; //1:up, -1:down
    for(; i<len; ++i){
        if(arr[i]>arr[i-1]){ //in up hill
            curlen = direction==1 ? curlen+1 : 2;
            direction = 1;
        }else{ //in down hill
            ++curlen;
            if(curlen>maxlen){
                maxlen = curlen;
            }
            direction = -1;
        }
    }
    return maxlen;
}

int main(){
    int a[] = {1,2,3,2,1};
    int b[] = {5,1,2,3,1};
    int c[] = {5,1,3,1,4};
    int d[] = {1,5,4,1,3,2,1,4};
    fprintf(stderr, "a longest:%d\n", longest_mountain(a, sizeof(a)/sizeof(a[0])));
    fprintf(stderr, "b longest:%d\n", longest_mountain(b, sizeof(b)/sizeof(b[0])));
    fprintf(stderr, "c longest:%d\n", longest_mountain(c, sizeof(c)/sizeof(c[0])));
    fprintf(stderr, "d longest:%d\n", longest_mountain(d, sizeof(d)/sizeof(d[0])));
    return 0;
}
