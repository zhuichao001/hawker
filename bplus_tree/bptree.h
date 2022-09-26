#ifndef __BPTREE_H__
#define __BPTREE_H__

#include "bpnode.h"
#include <vector>

typedef std::pair<std::string, std::string> kvpair;

class bptree{
    bpnode *_root;

    bpleaf * find(const std::string &key);
    int split(bpnode *orig);
    void upindex(bpnode *node);

    bpnode * rebalance(bpnode *node);
public:
    bptree(){
        _root = new bpleaf;
    }

    ~bptree(){
        //TODO clear
    }

    int get(const std::string &key, std::string &val);
    int put(const std::string &key, const std::string &val);
    int del(const std::string &key);
    int scan(const std::string &start, const std::string &end, std::vector<kvpair> &res);

    void print();
};

#endif
