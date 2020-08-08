#ifndef __H_SKIP_LIST_H__
#define __H_SKIP_LIST_H__

#include <limits.h>
#include <stddef.h>
#include <string>

using namespace std;


const int MAX_HEIGHT = 8;
const int BRANCHING = 3;


struct node {
    string key;
    string val;
    int height;
    node **forwards;

    node(string k, string v, int level):key(k),val(v){
        key = k;
        val = v;
        forwards = new node*[level];
    }
};

struct skiplist {
    node *head;
    node *nil;
    int length;
    int height;
    int maxheight;

    skiplist(int h):maxheight(h){
        height = 1;
        head = new node("", "", maxheight);
        nil = new node("~~~~~~~~", "", maxheight); 
        for(int i=0; i<maxheight; ++i){
            head->forwards[i] = nil;
        }
    }

    int rand_level();
    node *search(string k);
    node *insert(string k, const string &v);
    void print();
};


#endif
