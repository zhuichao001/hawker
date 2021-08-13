#include "bptree.h"
#include <stdio.h>

using namespace bplus_tree;

int test(){
    bptree tree;
    tree.put("a", "123");
    tree.print();
    printf("---------\n");

    string val;
    tree.get("a", val);
    printf("val:%s\n", val.c_str());
    printf("---------\n");

    tree.del("a");
    tree.print();
    printf("---------\n");

    return 0;
}

int main(){
    test();
    return 0;
}
