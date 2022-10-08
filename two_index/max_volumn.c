#include <stdlib.h>
#include <stdio.h>

//给定一个长度为n的整数数组height，找出其中的两条线，找出它们与 x 轴共同构成的容器可以容纳最多的水量

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
