#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

template<class T>
class node {
public:
    node * next_;
    T val_;
    node():next_(nullptr){
    }
};


template<class T>
class List {
    node<T> *head_, _;
    node<T> *tail_;
public:

    List() {
        head_  = &_;
        tail_ = &_;
    }

    ~List(){
        node<T> *cur = head_->next_;
        while(cur){
            node<T> *next = cur->next_;
            delete cur;
            cur = next;
        }
    }

    bool empty(){
        return head_->next_ == nullptr;
    }

    void push(T &t) {
        node<T> * e = new node<T>();
        e->next_ = nullptr;
        e->val_ = std::move(t);

        node<T> *last = nullptr;
        while(true){
            last = tail_;
            node<T> *back = last->next_;
            if(back!=nullptr){
                continue;
            }

            if(!__sync_bool_compare_and_swap((uint64_t**)(&last->next_), (uint64_t*)back, (uint64_t*)e)){
                continue;
            }
            break;
        }
        __sync_bool_compare_and_swap((uint64_t**)(&tail_), (uint64_t*)last, (uint64_t*)e);
    }

    bool pop(T *t) {
        node<T> *first=nullptr;
        node<T> *last=nullptr;
        while(true){
            last = tail_;
            //smb acquire
            first = head_->next_;
            if (first == nullptr){
                return false;
            }
            if(__sync_bool_compare_and_swap((uint64_t**)(&head_->next_), (uint64_t*)first, (uint64_t*)(first->next_))){
                break;
            }
        }

        if(first==last){
            __sync_bool_compare_and_swap((uint64_t**)(&tail_), (uint64_t*)last, (uint64_t*)head_);
        }

        *t = std::move(first->val_);
        delete first;
        return true;
    }
};
