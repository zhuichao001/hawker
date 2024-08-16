#include<iostream>

using namespace std;

// 注意：有多个重复值时，不能保证返回的是第一个
int binarySearch(int *nums, int len, int target) {
    if(nums==NULL || len==0) return -1;

    int left = 0; 
    int right = len - 1;

    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            left = mid + 1;
        else if (nums[mid] > target)
            right = mid - 1;
    }
    return -1;
}

void test1(){
    int a[]={1,2,2,2,3,5,6,8,9,10,12,18};
    cout<<binarySearch(a, sizeof(a)/sizeof(a[0]), 2)<<endl;
}

int main(){
    test1();
}
