#include <stdlib.h>
#include <stdio.h>

int max_volum(int* height, const int size){
    int l = 0;
    int r = size - 1;
    int volum = 0;
    while(l<r) {
        int temp = ((height[l]<=height[r])?height[l]:height[r])*(r-l);
        volum = (volum>=temp)?volum:temp;
        if(height[l] <= height[r]){
            ++l;
        } else {
            --r;
        }
    }
    return volum;
}

int main(){
    int height[] = {1,3,2,4,6,2};
    int volum = max_volum(height, sizeof(height)/sizeof(height[0]));
    printf("max volumn:%d\n", volum);
    return 0;
}
