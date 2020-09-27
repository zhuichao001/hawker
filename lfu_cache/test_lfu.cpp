#include "lfu.h"
#include <iostream>


void display(LFUCache *lfu){
    FreqNode *cur = lfu->freq_list.post;
    while(cur!=nullptr){
        cout<<"freq:"<<cur->freq<<"|";
        Node *node = cur->first;
        while(node!=nullptr){
           cout<<"("<<node->key<<","<<node->val<<"),"; 
           node = node->down;
        }
        cout<<endl;
        cur = cur->post;
    }
}

void test_lfu(){
    LFUCache lfu(3); 
    lfu.put("a", "123"); 
    lfu.put("b", "234"); 
    lfu.put("c", "555"); 
    display(&lfu);

    lfu.put("a", "399"); 
    string v1;
    lfu.get("a", v1);
    cout<<"val of a:"<<v1<<endl;
    display(&lfu);

    string v2;
    lfu.get("b", v2);
    cout<<"val of b:"<<v2<<endl;

    display(&lfu);
}

int main(){
    test_lfu();
    return 0;
}
