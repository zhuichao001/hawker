#ifndef __BPTREE_H__
#define __BPTREE_H__

#include "bpnode.h"

typedef std::pair<std::string, std::string> kvpair;

class bptree{
    bpnode *_root;

    bpleaf * find(const std::string &key);
    int split(bpnode *orig);
    void upindex(bpnode *node);

    enum Reaction{NONE=0, BRING_FROM_LEFT=1, BRING_FROM_RIGHT=2, MERGE_TO_LEFT=3, MERGE_TO_RIGHT=4};
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
