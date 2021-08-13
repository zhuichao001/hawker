#include <string>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

namespace bplus_tree {

const int ROADS = 4;
const string UNDEFINED_KEY = "[[UNDEFINED_KEY]]";

class bpnode{
public:
    int level;
    string minkey;
    bpnode *parent;
    bpnode *prev;
    bpnode *next;

    bpnode(){
        level = 0;
        minkey = UNDEFINED_KEY;
        parent = nullptr;
        prev = nullptr;
        next = nullptr;
    }

    virtual ~bpnode(){}
    virtual bool isleaf() = 0;
    virtual bool isroot() = 0;
    virtual bool full() = 0;
    virtual bool empty() = 0;
    virtual bpnode * split() = 0;
};

class bpjunc: public bpnode{
public:
    bpjunc(){
    }
    virtual ~bpjunc(){
        childs.clear();
    }
    vector<bpnode*> childs;

    bpnode * descend(string k);
    int adopt(bpnode * son);
    int abandon(bpnode * son);

    virtual bool isleaf(){return false;}
    virtual bool isroot(){return parent==nullptr;}
    virtual bool full(){return childs.size() >= ROADS;}
    virtual bool empty(){return childs.empty();}
    virtual bpnode * split();
};

class bpleaf: public bpnode{
public:
    bpleaf(){
        minkey = "~";
    }
    virtual ~bpleaf(){
        kvgroup.clear();
    }
    
    map<string, string> kvgroup;

    virtual bool isleaf(){return true;}
    virtual bool isroot(){return false;};
    virtual bool full(){return kvgroup.size() >= ROADS;}
    virtual bool empty(){return kvgroup.size()==0;}
    virtual bpnode * split();

    int get(string key, string &val);
    int put(string key, string val);
    int del(string key);
};

class bptree{
    bpnode *root;
    bpleaf * find(string key);
    int splitby(bpnode *node);
    bpnode * findlower(string key);
public:
    bptree(){
        root = new bpjunc;
    }

    ~bptree(){
        delete root;
    }

    int get(string key, string &val);
    int put(string key, string val);
    int del(string key);
    int scan(string lower, string upper);

    int print();
};

}; //end of namespace bplus_tree
