#include "bbst.h"


void test(){
    Tree t;
    for(int i=1; i<10; i++){
        t.addNode(i*3);
    }
    t.addNode(2);
    t.addNode(99);
    t.addNode(24);
    t.addNode(28);
    t.print();

    t.delNode(28);
    t.delNode(99);
    t.delNode(21);
    t.delNode(27);
    t.delNode(15);
    t.delNode(24);
    t.print();
}

int main(){
    test();
    return 0;
}
