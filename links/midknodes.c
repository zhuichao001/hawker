#include <stdio.h>
#include <stdlib.h>

//截取中间k个节点

struct Node{
    Node *next;
    int val;
};

void subMidLink(Node *root, int n, Node **head, Node **tail){
    if(root==NULL || n<=0){
        head=tail=NULL;
        return;
    }
    *head = *tail = root;
    
    for(int i=0; i<n-1; ++i){
        *tail = (*tail)->next;
        if (*tail==NULL){
            *head = *tail = NULL;
            return;
        }
    }
    
    Node *forward = *tail;
    while( forward!=NULL && forward->next!=NULL){
        *head = (*head)->next;
        *tail = (*tail)->next;
        forward = forward->next;
        forward = forward->next;
    }
}

int main(){
    Node nodes[9];
    for(int i=0;i<8;++i){
        nodes[i].next=&nodes[i+1];
        nodes[i].val=i+1;
    }
    nodes[8].val=9;
    nodes[8].next=NULL;

    Node *first, *last;
    subMidLink(&nodes[0], 5, &first, &last);
    printf("first:%d,last:%d\n",first->val, last->val);
}
