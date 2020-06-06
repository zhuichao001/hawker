#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned long long uint64_t;

const int MSG_LEN=64;

struct Entry {
    char msg[MSG_LEN];

    Entry * next;
};

struct RingQueue {
    Entry head;

    RingQueue() {
        head.next = NULL;
    }

    bool empty(){
        return head.next==NULL;
    }

    Entry* pop() {
        while(true){
            Entry *first = head.next;
            if (first==NULL){
                printf("queue is empty\n");
                continue;
            }
            if( __sync_bool_compare_and_swap((uint64_t*)(&head.next), uint64_t(first), uint64_t(first->next)) ){
                return first;
            }
        }
    }

    void push(Entry *e) {
        while(true){
            Entry *first = head.next;
            e->next = first;
            if( __sync_bool_compare_and_swap((uint64_t*)(&head.next), uint64_t(first), uint64_t(e)) ){
                return;
            }
        }
    }
};
