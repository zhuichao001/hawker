#include "bloom.h"
#include <string>
#include <iostream>

using namespace std;


void test_bloom(){
    BloomFilter bf(256);
    bf.insert("abc");
    bool flag = bf.exist("abc");
    cout<<"flag:"<<flag<<endl;

    flag = bf.exist("bc");
    cout<<"flag:"<<flag<<endl;

    flag = bf.exist("bca");
    cout<<"flag:"<<flag<<endl;
}

int main(){
    test_bloom();
    return 0;
}

