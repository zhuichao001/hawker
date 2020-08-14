
#include <stdio.h>
#include <stdlib.h>

//反转链表

struct Node{
    Node *next;
    int val;
};


Node *reverseLink(Node *head){
    Node *newhead = NULL;
    Node *current = head;
    while(current!=NULL){
        Node *forward = current->next;
        current->next=newhead;
        newhead = current;
        current = forward;
    }
    return newhead;
}


int main(){
    Node nodes[9];
    for(int i=0;i<8;++i){
        nodes[i].next=&nodes[i+1];
        nodes[i].val=i+1;
    }
    nodes[8].val=9;
    nodes[8].next=NULL;

    Node *head = reverseLink(&nodes[0]);
    while(head!=NULL){
        printf("%d ->", head->val);
        head = head->next;
    }
    printf("NULL\n");
}
