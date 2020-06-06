#include <memory.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned long long uint64_t;

bool CAS(uint64_t *ptr, uint64_t past, uint64_t now){
    return __sync_bool_compare_and_swap(ptr, past, now);
}

const int MSG_LEN=128;

struct Entry {
    char msg[MSG_LEN];
    int size;

    Entry * next;
};

struct EntryList {
    Entry head;

    EntryList() {
        head.next = NULL;
    }

    bool empty(){
        return head.next==NULL;
    }

    Entry* pop() {
        while(true){
            Entry *first = head.next;
            if (first==NULL){
                continue;
            }
            if( CAS((uint64_t*)(&head.next), uint64_t(first), uint64_t(first->next)) ){
                return first;
            }
        }
    }

    void push(Entry *e) {
        while(true){
            Entry *first = head.next;
            e->next = first;
            if( CAS((uint64_t*)(&head.next), uint64_t(first), uint64_t(e)) ){
                return;
            }
        }
    }
};

struct RingQueue {
    EntryList ready;
    EntryList raw;

    RingQueue(int n){
        Entry *all= new Entry[n];
        for (int i=0; i<n; ++i){
            raw.push(&all[i]);
        }
    }

    void push(char *data, int size){
        assert(size<=MSG_LEN);
        Entry *e = raw.pop();
        memcpy(e->msg, data, size);
        e->size = size;
        ready.push(e);
    }

    void pop(char *data, int &size){
        Entry *e = ready.pop(); 
        memcpy(data, e->msg, e->size);
        size = e->size;
        raw.push(e);
    }

    bool empty(){
        return ready.empty();
    }
};
