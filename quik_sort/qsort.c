#include<stdio.h>

void qsort(int *a, int l, int r) {
    if (l>=r) {
        return ;
    }

    const int mid = (l+r)>>1;
    int pivot = a[mid];
    a[mid] = a[r];

    int i=l, j=r; 
    while(i<j){
        for(; i<j; ++i){
            if(a[i]>=pivot){
                a[j--]=a[i];
                break;
            }
        }
        for(; i<j; --j){
            if(a[j]<pivot){
               a[i++]=a[j];
                break;
            }
        }
    }

    a[i] = pivot;
    qsort(a, l, i-1);
    qsort(a, i+1, r);
}

int main(){
    int a[] = {5,10,9,6,33,12,98,5,4,3,17,2,1};
    int len = sizeof(a)/sizeof(a[0]);
    qsort(a, 0, len-1);
    
    for (int i=0; i<len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
