#include <assert.h>
#include <string>
#include <algorithm>
#include <functional>


const int ROADS = 3;
const std::string UNDEFINED_KEY = "[[BPLUS-TREE-UNDEFINED-KEY]]";

class bpindex;

class bpnode{
public:
    bpnode():
        _parent(nullptr),
        _size(0){
    }
    virtual ~bpnode(){}
    virtual bool isleaf() = 0;
    virtual bool isroot() = 0;
    virtual std::string minkey() = 0;
    virtual std::string maxkey() = 0;
    virtual bpnode * divide() = 0;
    virtual void extend(bpnode *) = 0;
    virtual bpnode * leftsib() = 0;
    virtual bpnode * rightsib() = 0;
    virtual void borrowfirst(bpnode *) =0;
    virtual void borrowlast(bpnode *) =0;
    virtual bool balanced() = 0;
    virtual bool redundant() = 0;
    virtual void print() = 0;

    bool full(){return _size == ROADS;}
    bool empty(){return _size == 0;}
    bpindex * parent(){ return _parent; }
    void set_parent(bpindex *p){ _parent=p; }

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
    virtual bpnode * leftsib();
    virtual bpnode * rightsib();
    virtual void borrowfirst(bpnode *);
    virtual void borrowlast(bpnode *);
    virtual bool balanced(){return _size >= ROADS/2;}
    virtual bool redundant(){return _size >= ROADS/2;}
    virtual void print();

    bpnode * descend(const std::string &k);
    int insert(bpnode * after_son, bpnode * new_son);
    int erase(bpnode * son);
    int merge(bpnode * lson, bpnode * rson);

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
    virtual bpnode * leftsib();
    virtual bpnode * rightsib(){return _next;}
    virtual void borrowfirst(bpnode *);
    virtual void borrowlast(bpnode *);
    virtual bool balanced(){return _size >= ROADS/2;}
    virtual bool redundant(){return _size-1 >= ROADS/2;}
    virtual void print();

    int get(const std::string &key, std::string &val);
    int put(const std::string &key, const std::string &val);
    int del(const std::string &key);

    bpleaf *_next;
    std::string _keys[ROADS];
    std::string _dats[ROADS];
};

class bptree{
    bpnode *_root;
    bpleaf * find(const std::string &key);
    int split(bpnode *orig);
    bpnode * findbottom(const std::string &key);

    enum Reaction{NOTHING=0, BORROW_LEFT, BORROW_RIGHT, MERGE_LEFT, MERGE_RIGHT};

    int rebalance(bpnode *node);
public:
    bptree(){
        _root = new bpleaf;
    }

    ~bptree(){
        //TODO release
    }

    int get(const std::string &key, std::string &val);
    int put(const std::string &key, const std::string &val);
    int del(const std::string &key);
    int scan(const std::string &start, const std::string &end/*, vector<std::pastd::string> &data*/);

    int print();
};
