#include "bbst.h"


void test(){
    Tree t;
    for(int i=1; i<10; i++){
        t.addNode(i);
    }
    t.print();
}

int main(){
    test();
    return 0;
}
