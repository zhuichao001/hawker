#include "bptree.h"
#include <stdio.h>

using namespace bplus_tree;

int test(){
    bptree tree;
    tree.put("a", "123");
    tree.print();
    string val;
    tree.get("a", val);
    printf("val:%s\n", val.c_str());
    tree.del("a");

    return 0;
}

int main(){
    test();
    return 0;
}
