#include <iostream>

//Solution 1, Cost: O((M+N)/2)

int mid_2arrays(int arr1[], int m, int arr2[], int n){
    int midx = (m+n)/2;
    int i = 0, j = 0;
    while(i<m && j<n){
        if(arr1[i]<arr2[j]){
            ++i;
        }else{
            ++j;
        }
        if(i+j==midx){
            return std::min(arr1[i], arr2[j]);
        }
    }
    if(j==n){
        return arr1[midx-n];
    }
    //if(i==m)
    return arr2[midx-m];
}

int main(){
    int arr1[] = {1,2,2,3,5,5,7,9,10,11,12,205};
    int arr2[] = {4,6,7,8,8,15,17,19,20,21,112};
    const int arr1_len = sizeof(arr1)/sizeof(arr1[0]);
    const int arr2_len = sizeof(arr2)/sizeof(arr2[0]);
    int res = mid_2arrays(arr1, arr1_len, arr2, arr2_len);
    std::cout << "the middle val is:"  << res << std::endl;
    return 0;
}
