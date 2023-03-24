#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

//unordered full arrangement

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
       if(i!=start) swap(arr[start], arr[i]);
       arrange(arr, len, start+1);
       if(i!=start) swap(arr[start], arr[i]);
   }
}

int main(){
    char arr[] = "123";
    arrange(arr, strlen(arr), 0);
    return 0;
}
