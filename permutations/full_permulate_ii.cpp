//Array contain duplicate numbers!
#include <iostream>
#include <algorithm>
#include <stdlib.h>

void print(int arr[], int n){
    for(int i=0; i<n-1; ++i){
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[n-1] << std::endl;
}

void dfs(int arr[], int n, int i){
    if(i>=n){
        print(arr, n);
        return;
    }

    for(int j=i; j<n; j++){
        if(j!=i && arr[j]==arr[i]) continue;        
        if(j!=i && arr[j]==arr[j-1]) continue;
        std::swap(arr[i], arr[j]);
        dfs(arr, n, i+1);
        std::swap(arr[i], arr[j]);
    }
}

void permulate(int arr[], int n){
    dfs(arr, n, 0);
}

int cmpfunc (const void *a, const void *b){
       return ( *(int*)a - *(int*)b );
}

int main(){
    int arr[] = {1, 2, 1, 2};
    const int n = sizeof(arr)/sizeof(arr[0]);
    qsort(arr, n, sizeof(int), cmpfunc);
    permulate(arr, n);
    return 0;
}
