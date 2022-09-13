#include <stdio.h>
#include "deque.h"

int main(){
    deque<int> q;
    q.push_back(4);
    q.push_back(5);
    q.push_back(6);
    q.push_front(3);
    q.push_front(2);
    q.push_front(1);

    int t;
    for(int i=0;i<6;++i){
        q.pop_front(t);
        fprintf(stderr, "pop:%d\n", t);
    }
    return 0;
}
