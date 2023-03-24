#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

//ordered full arrangement

template<typename T>
void swap(T &a, T &b){
    T const c = a;
    a = b;
    b = c;
}

void print(char *arr, int len){
   for(int i=0; i<len; ++i){
       fprintf(stderr, "%c", arr[i]);
   }
   fprintf(stderr, "\n");
}

void arrange(char *arr, int len, int start){
    if(start==len){
        print(arr, len);
        return;
    }
    for(int i=start; i<len; ++i){
        if(i!=start){
            char c = arr[i];
            for(int k=i; k>start; --k)arr[k]=arr[k-1];
            arr[start]=c;
        }
        arrange(arr, len, start+1);
        if(i!=start){
            char c = arr[start];
            for(int k=start; k<i; ++k)arr[k]=arr[k+1];
            arr[i]=c;
        }
    }
}

int main(){
    char arr[] = "12345";
    arrange(arr, strlen(arr), 0);
    return 0;
}
