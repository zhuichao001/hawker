#ifndef _HAWK_SEGMENT_TREE_H_
#define _HAWK_SEGMENT_TREE_H_

#include <iostream>
#include<limits.h>

using namespace std;

inline int max(int a, int b){
    return a>b?a:b;
}

inline int sum(int a, int b){
    return a+b;
}

typedef int (*ReduceFunc)(int, int);

struct SegmentTree{
    int *data, n;
    int *tree;
    int initval;
    ReduceFunc func;

    SegmentTree(int *_data, int _n, ReduceFunc f, int _ival):data(_data), n(_n), func(f), initval(_ival){
        build();
    }

    ~SegmentTree(){
        delete []tree;
    }

    void build(){
        tree = new int[n<<1];

        for(int j=0; j<n; ++j){
            tree[n+j] = data[j];
        }

        for(int i=n-1; i>0; --i){
            tree[i] = func(tree[2*i], tree[2*i+1]);
        }
    }

    void print(){
        for(int i=1; i<2*n; ++i){
            cout<<"i="<<i<<", val="<<tree[i]<<endl;
        }
    }

    int query_range(int i, int j){
        int l=i+n, r=j+n;
        int val = initval; //TODO init val
        while(l<=r){
            if(l%2==1){
                val = func(tree[l], val);
                ++l;
            }
            if(r%2==0){
                val = func(tree[r], val);
                --r;
            }
            l = l/2;
            r = r/2;
        }
        return val;
    }
};

#endif
