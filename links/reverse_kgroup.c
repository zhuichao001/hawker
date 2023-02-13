#include <stdio.h>
#include <stdlib.h>

//k个一组反转链表

struct Node{
    Node *next;
    int val;
};

Node *reverseKgroup(Node *head, int k){
    Node *newhead = NULL;
    Node *newtail = NULL;

    Node *innerhead = NULL;
    Node *innertail = head;

    int n = 0 ;
    for(Node *current = head; current!=NULL; ){
        Node *forward = current->next;
        current->next = innerhead;
        innerhead = current;
        current = forward;

        if(++n%k==0){
            if(newhead==NULL){
                 newhead = innerhead;
                 newtail = head;
            } 
            newtail->next = innerhead;
            newtail = innertail;
            innertail = current;
        }
    }
    newtail->next = innerhead;
    newtail = innertail;
    newtail -> next = NULL;
    return newhead;
}


Node *prepareLink(){
    const int N = 11;
    Node *nodes = new Node[N];
    for(int i=0;i<N-1;++i){
        nodes[i].next=&nodes[i+1];
        nodes[i].val=i+1;
    }
    nodes[N-1].val=N;
    nodes[N-1].next=NULL;
    return &nodes[0];
}

int main(){
    Node *head = prepareLink();
    head = reverseKgroup(head, 3);
    while(head!=NULL){
        printf("%d ->", head->val);
        head = head->next;
    }
    printf("NULL\n");
    delete []head;
}
