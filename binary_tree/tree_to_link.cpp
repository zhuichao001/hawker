#include <stdio.h>
#include <iostream>

//二叉树转双链表

struct Node{
    Node *left;
    Node *right;
    int val;
    Node(int v):
        left(nullptr),
        right(nullptr){
        val=v;
    }
};


Node * transfer(Node *root){
    if(root==nullptr){
        return nullptr;
    }
    Node *head=nullptr;
    Node *lside = transfer(root->left);
    Node *rside = transfer(root->right);

    if(lside!=nullptr){
        head = lside;

        lside->left->right = root;
        root->left = lside->left;

        root->right = lside;
        lside->left = root;
    }else{
        head=root;
    }

    if(rside!=nullptr){
        head->left = rside->left;
        rside->left->right = head;

        root->right = rside;  //the assign order is important!
        rside->left = root;
    }else{
        root->right = head;
        head->left = root;
    }
    return head;
}

void printLink(Node *head){
    Node *node = head;
    while(node->right!=head){
        std::cout << node->val << " ";
        node = node->right;
    }
    std::cout<< node->val << " ";
    std::cout << std::endl;
}

int main(){
    Node a(1), b(2), c(2), d(3), e(5), f(5), g(3);
    a.left=&b;
    a.right=&c;
    b.left=&d;
    b.right=&e;
    c.left=&f;
    c.right=&g;
    //        a
    //       / \
    //      b   c
    //     /\   /\
    //    d  e f  g
    Node *head = transfer(&a);
    printLink(head);
    return 0;
}
