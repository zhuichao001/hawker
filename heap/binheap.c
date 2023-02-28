#include <stdio.h>
#include <assert.h>

#define LIKELY(x) __builtin_expect(!!(x), 1) 
#define UNLIKELY(x) __builtin_expect(!!(x), 0)

void swap(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}

struct heap{
    int *base;
    int size;
    int capacity;

    heap(int *arr, int _n, int _cap){
        size = _n;
        capacity = _cap;

        base = new int[capacity];
        for(int i=size-1; i>=0; i--){
            base[i]=arr[i];
        }
        _build();
    }

    bool empty(){
        return size==0;
    }

    bool full(){
        return size==capacity;
    }

    void push(int v){
        if(full()){
            _scale();
        }
        base[size++] = v;
        _sift_up();
    }

    int pop(){
        assert(!empty());

        swap(base[0], base[--size]);
        _sift_down(0);
        return base[size];
    }

    void _sift_up(){
        for(int i=size-1; i>0; ){
            int p = (i-1)>>1;
            if(base[i]<base[p]){
                swap(base[i], base[p]);
            } else {
                break;
            }
            i = p;
        }
    }

    void _sift_down(int i){
        while(i<size/2){
            int left = i*2+1, right = i*2+2;
            if(LIKELY(right<=size-1)){
                int idx = base[left] < base[right]? left:right;
                if (base[idx]<base[i]){
                    swap(base[idx], base[i]); 
                    i = idx;
                } else {
                    break;
                }
            }else if (left<=size-1){
                if(base[left]<base[i]){
                    swap(base[left], base[i]); 
                    i = left;
                } else {
                    break;
                }
            }
        }
    }

    void _build(){
        for(int i=size-1; i>0; i--){
            int p = (i-1)>>1;
            if(base[i] < base[p]){
                swap(base[p], base[i]);
                _sift_down(i);
            }
        }
    }

    void _scale(){
         capacity <<=1;
         int * tmp=new int(capacity);
         for (int i=0; i<size; i++){
             tmp[i] = base[i];
         }
         delete []base;
         base = tmp;
    }

    void print(){
        for(int i=0; i<size; i++){
            fprintf(stderr, "%d ", base[i]);
        }
        fprintf(stderr, "\n");
    }
};


int main(){
    int a[] = {8,1,9,2,4,5,0};
    int len = sizeof(a) / sizeof(a[0]);

    heap h(a, len, len*2);

    h.push(99);
    h.push(6);
    h.push(3);

    while(!h.empty()){
        fprintf(stderr, "%d ===>\n", h.pop());
    }
    return 0;
}
