#include <stdio.h>
#include <stdlib.h>

//合并两个有序单链表(递增)

struct Node{
    Node *next;
    int val;
    Node(){next=NULL;}
};


Node *mergeLink(Node *a, Node *b){
    if (a == NULL) {
        return b;
    }
    if (b == NULL) {
        return a;
    }

    Node rope; //head:=rope.next
    Node *tail = &rope;

    while(a!=NULL && b!=NULL){
        Node * poped = NULL;
        if (a->val <= b->val) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = a!=NULL?a:b;
    return rope.next;
}

void test(){
    Node linka[4], linkb[5];
    for(int i=0;i<3;++i){
        linka[i].next = &linka[i+1];
        linka[i].val = i*2+1;
    }
    linka[3].val = 3*2+1;
   
    for(int i=0;i<4;++i){
        linkb[i].next = &linkb[i+1];
        linkb[i].val = i*3-1;
    }
    linkb[4].val = 4*3-1;

    Node * head = mergeLink(linka, linkb);

    while(head!=NULL){
        printf("%d ->", head->val);
        head = head->next;
    }
    printf("NULL\n");
}


int main(){
    test();
    return 0;
}
