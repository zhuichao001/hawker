#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

//typedef unsigned long long uint64_t;

const int MSG_LEN=64;

struct node {
    node * next;
    char data[MSG_LEN];
};

struct lf_queue {
    node *head;
    node *tail;

    lf_queue() {
        head = tail = new node();
        head->next = nullptr;
    }

    bool empty(){
        return head->next == nullptr;
    }

    void push(const char *data) {
        node * e = new node();
        e->next = nullptr;
        memcpy(e->data, data, strlen(data)+1);

        node *last = nullptr;
        while(true){
            last = this->tail;
            //if tailor is moved, try again
            if(last!=this->tail){
                continue;
            }

            node *back = last->next;
            //if tailor's next is not null, set tailor to back
            if(back!=nullptr){
                __sync_bool_compare_and_swap((uint64_t**)(&tail), (uint64_t*)last, (uint64_t*)back);
                continue;
            }

            if(__sync_bool_compare_and_swap((uint64_t**)(&tail->next), (uint64_t*)back, (uint64_t*)e)){
                break;
            }
        }
        __sync_bool_compare_and_swap((uint64_t**)(&tail), (uint64_t*)last, (uint64_t*)e);
    }

    char* pop() {
        node *first = nullptr;
        do{
            first = head;
            if (first->next == nullptr){
                return nullptr;
            }
        } while( !__sync_bool_compare_and_swap((uint64_t**)(&head), (uint64_t*)first, (uint64_t*)(first->next)) );
        char *ret = first->next->data;
        delete first;
        return ret;
    }
};
