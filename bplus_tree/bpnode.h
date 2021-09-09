#ifndef __BPNODE_H__
#define __BPNODE_H__

#include <assert.h>
#include <string>
#include <algorithm>
#include <functional>


const int ROADS = 8;

class bpindex;

class bpnode{
public:
    bpnode():
        _parent(nullptr),
        _size(0){
    }
    virtual ~bpnode(){}

    virtual bool isleaf() =0;
    virtual bool isroot() =0;

    virtual std::string minkey() =0;
    virtual std::string maxkey() =0;

    virtual bpnode * divide() =0;
    virtual void extend(bpnode *) =0;

    virtual void bringhead(bpnode *) =0;
    virtual void bringtail(bpnode *) =0;

    virtual bool balanced() =0;
    virtual bool redundant() =0;

    bpnode * leftside();
    bpnode * rightside();

    bool full(){return _size == ROADS;}
    bool empty(){return _size == 0;}

    bpindex * parent(){ return _parent; }
    void setparent(bpindex *p){ _parent=p; }

    bpindex *_parent;
    int _size;
};

class bpindex: public bpnode{
public:
    bpindex(){ 
    }

    bpindex(bpnode *lson, bpnode *rson):
        bpnode(){
        _childs[0] = lson;
        _childs[1] = rson;
        _index[0] = rson->minkey();
        _size = 1; //size of _index[]
    }

    virtual ~bpindex(){
    }

    virtual bool isleaf(){return false;}
    virtual bool isroot(){return _parent==nullptr;}

    virtual std::string minkey(){return _size>0 ? _childs[0]->minkey() : "";}
    virtual std::string maxkey(){return _size>0 ? _childs[_size-1]->maxkey() : std::string(128,'\xff');}

    virtual bpnode * divide();
    virtual void extend(bpnode *);

    virtual void bringhead(bpnode *);
    virtual void bringtail(bpnode *);

    virtual bool balanced(){return _size >= ROADS/2;}
    virtual bool redundant(){return _size > ROADS/2;}

    bpnode * descend(const std::string &k);
    int insert(bpnode * after_son, bpnode * new_son);
    int erase(bpnode * son);
    int replace(bpnode * old, bpnode *neo);
    int offset(bpnode *son);

    std::string _index[ROADS];
    bpnode* _childs[ROADS+1];
};

class bpleaf: public bpnode{
public:
    bpleaf():
        bpnode(),
        _next(nullptr){
    }

    virtual ~bpleaf(){
    }
    
    virtual bool isleaf(){return true;}
    virtual bool isroot(){return _parent==nullptr;}
    virtual std::string minkey(){return _size>0 ? _keys[0]:"";}
    virtual std::string maxkey(){return _size>0 ? _keys[_size-1]:"";}

    virtual bpnode * divide();
    virtual void extend(bpnode *);

    virtual void bringhead(bpnode *);
    virtual void bringtail(bpnode *);

    virtual bool balanced(){return _size >= ROADS/2;}
    virtual bool redundant(){return _size > ROADS/2;}

    int get(const std::string &key, std::string &val);
    int put(const std::string &key, const std::string &val);
    int del(const std::string &key);

    bpleaf *_next;
    std::string _keys[ROADS];
    std::string _dats[ROADS];
};

#endif
