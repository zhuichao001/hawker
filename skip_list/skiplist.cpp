#include "skiplist.h"
#include <stdlib.h>
#include <iostream>

using namespace std;


int skiplist::rand_level(){
    int h = 1;
    while(h<this->maxheight && rand()%BRANCHING==0){
        ++h;
    }
    return h;
}


node *skiplist::search(string k){
    node *cur = this->head;
    for(int i=this->height-1; i>=0; --i){
        while(cur->forwards[i]->key<k){
            cur = cur->forwards[i];
        }
        if(cur->forwards[i]->key==k){
            return cur->forwards[i];
        }
    }
    return NULL;
}


node *skiplist::insert(string k, const string &v){
    node *updates[this->maxheight];
    node *cur = this->head;

    for(int i=this->height-1; i>=0; --i){
        while(cur->forwards[i]->key < k){
            cur = cur->forwards[i];
        }
        updates[i]=cur;
    }

    if(cur->forwards[0]->key==k) { //update
        cur->forwards[0]->val = v;
        return cur->forwards[0];
    } else { //insert
        int level = this->rand_level();
        for(int i=this->height; i<level; ++i) {
            updates[i] = this->head;
        }
        this->height = level>this->height?level:this->height;
        
        node * tmp=new node(k,v,level);
        for(int i=0; i<level; ++i){
            tmp->forwards[i] = updates[i]->forwards[i];
            updates[i]->forwards[i] = tmp;
        }
        return tmp;
    }
}

void skiplist::print(){
    cout<<"----level:"<<this->height<<endl;;
    for(int i=this->height-1; i>=0; --i){
        node *cur = this->head;
        while(cur != this->nil){
            cout << cur->key << ":" << cur->val << " |-> ";
            cur = cur->forwards[i];
        }
        cout << "nil" << endl;
    }
}
