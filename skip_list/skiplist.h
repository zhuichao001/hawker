#ifndef __H_SKIP_LIST_H__
#define __H_SKIP_LIST_H__

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <string>

template<typename S, typename T>
struct node_t {
    S key;
    T val;
    int height;
    node_t **forwards;

    node_t(const int level, const S &k, const T &v=""):
        key(k),
        val(v){
        forwards = new node_t*[level];
        for(int i=0; i<level; ++i){
            forwards[i] = nullptr;
        }
    }
};

template<typename S, typename T>
struct skiplist_t {
    node_t<S,T> *head;
    node_t<S,T> *nil;

    int length;
    int height;

    const int MAXHEIGHT;
    const int WIDTH;

    skiplist_t(int maxh=16, int width=4):
        MAXHEIGHT(maxh),
        WIDTH(width){
        height = 1;
        head = new node_t<S,T>(MAXHEIGHT, "");
        nil = new node_t<S,T>(MAXHEIGHT, std::string(2048, '\xff')); 
        for(int i=0; i<MAXHEIGHT; ++i){
            head->forwards[i] = nil;
        }
    }

    int rand_level(){
        int h = 1;
        while(h < MAXHEIGHT && rand()%WIDTH == 0){
            ++h;
        }
        return h;
    }

    node_t<S,T> *search(const std::string &k){
        node_t<S,T> *cur = this->head;
        for(int i=this->height-1; i>=0; --i){
            while(cur->forwards[i]->key<k){
                cur = cur->forwards[i];
            }
            if(cur->forwards[i]->key==k){
                return cur->forwards[i];
            }
        }
        return nullptr;
    }

    node_t<S,T> *insert(const std::string &k, const std::string &v){
        node_t<S,T> *updates[this->MAXHEIGHT];
        node_t<S,T> *cur = this->head;
    
        for(int i=this->height-1; i>=0; --i){
            while(cur->forwards[i]->key < k){
                cur = cur->forwards[i];
            }
            updates[i] = cur;
        }
    
        if(cur->forwards[0]->key==k) { //update
            cur->forwards[0]->val = v;
            return cur->forwards[0];
        } else { //insert
            const int level = rand_level();
            for(int i=this->height; i<level; ++i) {
                updates[i] = this->head;
            }
    
            this->height = level>this->height ? level : this->height;
            
            node_t<S,T> * neo = new node_t<S,T>(level, k, v);
            for(int i=0; i<level; ++i){
                neo->forwards[i] = updates[i]->forwards[i];
                updates[i]->forwards[i] = neo;
            }
            return neo;
        }
    }

    void print(){
        std::cout << "level:" << this->height << std::endl;
        for(int i=this->height-1; i>=0; --i){
            node_t<S,T> *cur = this->head;
            while(cur != this->nil){
                std::cout << cur->key << ":" << cur->val << " |-> ";
                cur = cur->forwards[i];
            }
            std::cout << "nil" << std::endl;
        }
    }
};


#endif
