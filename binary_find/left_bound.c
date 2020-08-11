#include<iostream>

using namespace std;


int leftBound(int *nums, int len, int target) {
    if (nums==NULL || len == 0) return -1;
    int left = 0;
    int right = len;
    
    while (left < right) {  //...
        int mid = (left + right) / 2;
        if (nums[mid] == target) {
            right = mid;
                            //...
        } else if (nums[mid] < target) {
            left = mid + 1; //...
        } else if (nums[mid] > target) {
            right = mid;    //...
        }
    }
    return left;
}


int main(){
    int a[]={1,2,3,3,3,3,5,6,8,9,10,12,18};
    cout<<leftBound(a, sizeof(a)/sizeof(a[0]), 3)<<endl;
}
