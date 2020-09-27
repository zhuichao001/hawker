#include "lfu.h"
#include <iostream>


void test_lfu(){
    LFUCache lfu(3); 
    lfu.put("a", "123"); 
    lfu.put("b", "234"); 
    lfu.put("c", "555"); 
    lfu.put("a", "399"); 
    string v;
    lfu.get("b", v);
    cout<<"v:"<<v<<endl;
}

int main(){
    test_lfu();
    return 0;
}


