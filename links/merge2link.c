#include <stdio.h>
#include <stdlib.h>

//合并两个有序单链表(递增)

struct Node{
    Node *next;
    int val;
    Node(){next=NULL;}
};


Node *mergeLink(Node *linka, Node *linkb){
    if (linka==NULL) {
        return linkb;
    }
    if (linkb==NULL) {
        return linka;
    }

    Node *head = NULL;
    Node *tail = NULL;
    Node *a = linka;
    Node *b = linkb;

    if (a->val <= b->val) {
        head = tail = a;
        a = a->next;
    } else {
        head = tail = b;
        b = b->next;
    }

    while(a!=NULL && b!=NULL){
        Node * poped = NULL;
        if (a->val <= b->val) {
            poped = a;
            a = a->next;
        } else {
            poped = b;
            b = b->next;
        }
        
        if (head==NULL) {
            head = tail = poped;
        }
        tail->next = poped;
        tail = tail->next;
    }
    tail->next = (a==NULL)?b:a;
    return head;
}


int main(){
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
