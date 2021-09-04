#include "bptree.h"
#include <stdio.h>

int test(){
    bptree tree;
    tree.put("a", "123");
    tree.put("b", "456");
    tree.put("c", "789");
    tree.put("d", "888");
    tree.put("e", "999");
    tree.put("f", "1000");
    //tree.put("g", "1001");
    tree.print();

    return 0;

    string val;
    tree.get("a", val);
    printf("val:%s !!!!!! \n", val.c_str());

    tree.del("a");
    tree.print();

    tree.put("a", "234");
    tree.print();

    return 0;
}

int main(){
    test();
    return 0;
}
