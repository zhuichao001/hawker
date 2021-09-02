#ifndef __H_SKIP_LIST_H__
#define __H_SKIP_LIST_H__

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <string>

using namespace std;




struct node {
    string key;
    string val;
    int height;
    node **forwards;

    node(const int level, const string &k, const string &v=""):
        key(k),
        val(v){
        forwards = new node*[level];
        for(int i=0; i<level; ++i){
            forwards[i] = nullptr;
        }
    }
};

struct skiplist {
    node *head;
    node *nil;

    int length;
    int height;

    const int MAXHEIGHT;
    const int BRANCHING;

    skiplist(int maxh, int branch):
        MAXHEIGHT(maxh),
        BRANCHING(branch){
        height = 1;
        head = new node(MAXHEIGHT, "");
        nil = new node(MAXHEIGHT, std::string(2048, '\xff')); 
        for(int i=0; i<MAXHEIGHT; ++i){
            head->forwards[i] = nil;
        }
    }

    int rand_level(){
        int h = 1;
        while(h < MAXHEIGHT && rand()%BRANCHING == 0){
            ++h;
        }
        return h;
    }

    node *search(const string &k);

    node *insert(const string &k, const string &v);

    void print();
};


#endif
