#include <string>
#include <iostream>


int incr_subseq(int *arr, int len){
    int maxseq=1;
    int longest[len];
    for(int i=0; i<len; ++i)longest[i]=1;
    for(int i=1; i<len; ++i){
        for(int j=0; j<i; ++j){
            if(arr[i]>arr[j]){
                longest[i] = std::max(longest[i], longest[j]+1);
            }
        }
        maxseq = std::max(maxseq, longest[i]);
    }
    return maxseq;
}

int main(){
    int arr[]={12, 3, 2, 5, 1, 6}; //longest increasing subsequence:3,5,6
    int longest = incr_subseq(arr, sizeof(arr)/sizeof(arr[0]));
    std::cout << "longest increasing subsequence len:" << longest << std::endl;
    return 0;
}
