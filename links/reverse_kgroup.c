
#include <stdio.h>
#include <stdlib.h>

//反转链表

struct Node{
    Node *next;
    int val;
};


Node *reverseKgroup(Node *head, int k){
    Node *newhead = NULL;
    Node *newtail = NULL;

    Node *innerhead = NULL;
    Node *innertail = NULL;

    int n = 1 ;
    for(Node *current = head; current!=NULL; n++){
        if(innertail==NULL){
            innertail = current;
        }
        Node *forward = current->next;
        current->next = innerhead;
        innerhead = current;
        current = forward;
        if(n%k==0){
            if(newhead==NULL){
                 newhead = innerhead;
                 newtail = innertail;
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


int main(){
    const int N = 11;
    Node nodes[N];
    for(int i=0;i<N-1;++i){
        nodes[i].next=&nodes[i+1];
        nodes[i].val=i+1;
    }
    nodes[N-1].val=N;
    nodes[N-1].next=NULL;

    Node *head = reverseKgroup(&nodes[0], 3);
    while(head!=NULL){
        printf("%d ->", head->val);
        head = head->next;
    }
    printf("NULL\n");
}
