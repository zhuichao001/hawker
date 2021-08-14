#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

const int MSG_LEN=64;

struct node_t {
    node_t * next;
    char data[MSG_LEN];
};

struct List {
    node_t *head;
    node_t *tail;

    List() {
        head = tail = new node_t();
        head->next = nullptr;
    }

    ~List(){
        node_t *cur = head;
        while(cur){
            node_t *next = cur->next;
            delete cur;
            cur = next;
        }
    }

    bool empty(){
        return head->next == nullptr;
    }

    void push(const char *data) {
        node_t * e = new node_t();
        e->next = nullptr;
        memcpy(e->data, data, strlen(data)+1);

        node_t *last = nullptr;
        while(true){
            last = this->tail;
            //if tailor is moved, try again
            if(last!=this->tail){
                continue;
            }

            node_t *back = last->next;
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
        node_t *first = nullptr;
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
