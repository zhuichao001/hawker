#include <stdio.h>


int longest_mountain(int *arr, int len){
    if(arr==nullptr || len<=2){
        return 0;
    }
    int max = 0;
    int cur = arr[1]>arr[0]?2:0;
    int direction = arr[1]>arr[0]?1:-1;
    for(int i=2; i<len; ++i){
        if(direction==1){  //up
            if(arr[i]<arr[i-1]){
                if(cur>0){ //end first half
                    ++cur;
                    if(cur>max){
                        max = cur;
                    }
                }
                direction = -1;
            }else{
                ++cur;
            }
        }else{ //down
            if(arr[i]<arr[i-1]){
                if(cur>0){ //second half
                    ++cur;
                    if(cur>max){
                        max = cur;
                    }
                }
            }else{ //maybe start first half
                direction = 1;
                cur = 2;
            }
        } 
    }
    return max;
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
}
