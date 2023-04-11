#include <stdlib.h>
#include <assert.h>
#include <iostream>

template <typename T>
struct Node{
    Node *next;
    T val;
    Node(){
        next=nullptr;
    }
    Node(T v):
        val(v){
        next=nullptr;
    }
    Node(T v, Node *nex):
        val(v){
        next=nex;
    }
};

template<typename T>
Node<T> *mergeLink(Node<T> *a, Node<T> *b){
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }

    Node<T> rope; //head:=rope.next
    Node<T> *tail = &rope;

    while(a!=nullptr && b!=nullptr){
        if (a->val <= b->val) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = a!=nullptr?a:b;
    return rope.next;
}

template<typename T>
Node<T> *initLink(T *a, const int len){
    Node<T> *link = new Node<T>[len];
    for(int i=0;i<len;++i){
        link[i].next = (i == len-1)? nullptr : &link[i+1];
        link[i].val = a[i];
    }
    return &link[0];
}

template<typename T>
void printLink(Node<T> *link){
    while(link!=nullptr){
        std::cout << link->val << " ";
        link = link->next;
    }
    std::cout << std::endl;
}

void test(){
    int a[3] = {1,2,4};
    int b[3] = {1,3,4};
    auto la = initLink(a, 3);
    auto lb = initLink(b, 3);

    auto lc = mergeLink(la, lb);
    assert(lc!=nullptr);
    printLink(lc);
}

int main(){
    test();
}
