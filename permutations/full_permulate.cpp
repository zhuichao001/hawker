//Array do not contain duplicate numbers
#include <iostream>
#include <algorithm>

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
        std::swap(arr[i], arr[j]);
        dfs(arr, n, i+1);
        std::swap(arr[i], arr[j]);
    }
}

void permulate(int arr[], int n){
    dfs(arr, n, 0);
}

int main(){
    int arr[] = {1, 2, 3};
    permulate(arr, sizeof(arr)/sizeof(arr[0]));
    return 0;
}
