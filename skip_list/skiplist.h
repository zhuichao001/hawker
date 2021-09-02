#ifndef __H_SKIP_LIST_H__
#define __H_SKIP_LIST_H__

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <string>

using namespace std;


const int MAX_HEIGHT = 8;
const int BRANCHING = 3;


struct node {
    string key;
    string val;
    int height;
    node **forwards;

    node(const int level, const string &k, const string &v=""):
        key(k),
        val(v){
        forwards = new node*[level];
    }
};

struct skiplist {
    node *head;
    node *nil;
    int length;
    int height;
    int maxheight;

    skiplist(int maxh):
        maxheight(maxh){
        height = 1;
        head = new node(maxheight, "");
        nil = new node(maxheight, std::string(2048, '\xff')); 
        for(int i=0; i<maxheight; ++i){
            head->forwards[i] = nil;
        }
    }

    int rand_level(){
        int h = 1;
        while(h < maxheight && rand()%BRANCHING == 0){
            ++h;
        }
        return h;
    }

    node *search(const string &k);

    node *insert(const string &k, const string &v);

    void print();
};


#endif
