#include <iostream>
using namespace std;

inline int max(int a, int b){
    return a>b?a:b;
}

inline int sum(int a, int b){
    return a+b;
}

struct SegmentTree{
    int *data, n;
    int *max_tree;
    int *sum_tree;

    SegmentTree(int *_data, int _n):data(_data), n(_n){
        build();
    }

    ~SegmentTree(){
        delete []max_tree;
        delete []sum_tree;
    }

    void build(){
        max_tree = new int[n<<1];
        sum_tree = new int[n<<1];

        for(int j=0; j<n; ++j){
            max_tree[n+j] = data[j];
            sum_tree[n+j] = data[j];
        }
        for(int i=n-1; i>0; --i){
            int left = i*2, right = i*2+1;
            max_tree[i] = max(max_tree[left], max_tree[right]);
            sum_tree[i] = sum(sum_tree[left], sum_tree[right]);
        }
    }

    void print(){
        for(int i=1; i<2*n; ++i){
            cout<<"i="<<i<<", max_val="<<max_tree[i]<<endl;
        }
    }

    int max_range(int i, int j){
        int l=i+n, r=j+n;
        int maxval = 1<<31;
        while(l<=r){
            if(l%2==1){
                maxval = max(max_tree[l], maxval);
                ++l;
            }
            if(r%2==0){
                maxval = max(max_tree[r], maxval);
                --r;
            }
            l = l/2;
            r = r/2;
        }
        return maxval;
    }

    int sum_range(int i, int j){
        int l=i+n, r=j+n;
        int sumval = 0;
        while(l<=r){
            if(l%2==1){
                sumval += sum_tree[l];
                ++l;
            }
            if(r%2==0){
                sumval += sum_tree[r];
                --r;
            }
            l = l/2;
            r = r/2;
        }
        return sumval;
    }
};


int main(){
    int a[6]={6,4,5,9,7,3};
    SegmentTree st(a, 6);
    int s = st.max_range(0,2);
    cout<<"sum:"<<s<<endl;
}
