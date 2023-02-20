#include <iostream>

//Solution 2, Cost: O(Log(M+N)/2)

int kth_element(int arr1[], int m, int arr2[], int n, int k){
    int mb=0, nb=0; //left boder of arr1 and arr2 arrays
    int mi=0, ni=0;
    while(k>=0){
        mi = mb+k/2>=m? m-1: mb+k/2;
        ni = nb+k/2>=n? n-1: nb+k/2;

        if(arr1[mi]<=arr2[ni]){
            k -= (mi+1-mb);
            mb = mi+1;
        }else{
            k -= (ni+1-nb);
            nb = ni+1;
        }
    }
    return std::min(arr1[mi], arr2[ni]);
}

double midian_2arrays(int arr1[], int m, int arr2[], int n){
    int t = kth_element(arr1, m, arr2, n, (m+n)/2);
    if((m+n)%2 == 1) {
        return t;
    }
    return double(kth_element(arr1, m, arr2, n, (m+n)/2-1) + t)/2;
}

int main(){
    int arr1[] = {1,2,3,5,7,9,10,11,12, 13};
    int arr2[] = {4,6,7,8,15,17,19,20,21,112};
    const int len1 = sizeof(arr1)/sizeof(arr1[0]);
    const int len2 = sizeof(arr2)/sizeof(arr2[0]);
    double res = midian_2arrays(arr1, len1, arr2, len2);
    std::cout << "The midian val is:"  << res << std::endl;
    return 0;
}
