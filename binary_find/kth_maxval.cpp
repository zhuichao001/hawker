#include <iostream>
#include <algorithm>

//kth-largest-element-in-an-array

int kth_max(int arr[], int left, int right, int kth){
    int pivot = (left+right)/2;
    std::swap(arr[left], arr[pivot]);
    int select = arr[left];
    int i=left, j=right;
    while(i<j){
        while(i<j && arr[j]<select){
            --j;
        }
        if(i==j)break;
        arr[i++]=arr[j];

        while(i<j && arr[i]>=select){
            ++i;
        }
        if(i==j)break;
        arr[j--]=arr[i];
    }

    arr[i] = select;
    const int rest = i-left+1;
    if(rest==kth){
        return select;
    }else if(rest<kth){
        return kth_max(arr, i+1, right, kth-rest);
    }else{
        return kth_max(arr, left, i-1, kth);
    }
}

int main(){
    for(int i=1; i<=9; ++i){
        int a[]={3,9,6,0,2,8,7,5,1};
        std::cout << i << "th:" << kth_max(a, 0, sizeof(a)/sizeof(a[0])-1, i) << std::endl;
    }
    return 0;
}
