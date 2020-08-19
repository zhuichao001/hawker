#ifndef _BALANCED_SEARCH_TREE_H_
#define _BALANCED_SEARCH_TREE_H_

#include <stdlib.h>
#include <stdio.h>


inline int max(int a, int b) {
     return a>b ? a:b;
}

struct Node{
    Node *left;
    Node *right;
    int val;
    int height;

    Node(){val=0; left=NULL; right=NULL; height=1;}

    Node(int v){val=v; left=NULL; right=NULL; height=1;}

    int getBalanced(){
        int lh = (left==NULL)?0:left->height;
        int rh = (right==NULL)?0:right->height;
        return lh - rh;
    }

    bool isBalanced(){
        if(left==NULL){
            return right==NULL;
        }
        if(right==NULL){
            return false;
        }
        return left->isBalanced() && right->isBalanced();
    }

    int getHeight(){
        return this->height;
    }

    void updateHeight() {
        int lh = (left==NULL)?0:left->height;
        int rh = (right==NULL)?0:right->height;
        this->height = max(lh, rh)+1;
    }

    void print() {
        int l = (left==NULL)? -1:left->val;
        int r = (right==NULL)? -1:right->val;
        if (l+r==-2){ //leaf
            return;
        }

        printf("%d : <%d, %d>, height:%d\n", val, l, r, height);

        if(left){
            left->print();
        }
        if(right){
            right->print();
        }
    }
};


struct Tree{
    Node *root;
    int size;

    Tree(){root=NULL; size=0;}
    int getHeight(){return root!=NULL?root->height:0;}
    int getSize(){return this->size;}
    int isEmpty(){return root==NULL;}

    int getNodeHeight(Node *node){
        if(node==NULL){
            return 0;
        }
        return node->getHeight();
    }

    int getBalancedFactor(Node *node){
        if(node==NULL){
            return 0;
        }
        return node->getBalanced();
    }

    Node *rightRotate(Node *z) {
        Node *y = z->left;
        Node *t = y->right;
        z->left = t;
        y->right = z;

        z->updateHeight();
        y->updateHeight();
        return y;
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *t = y->left;
        x->right = t;
        y->left = x;

        x->updateHeight();
        y->updateHeight();
        return y;
    }

    Node *getNode(int val) {
        Node *node = root;
        while (node!= NULL) {
            if (node->val < val) {
                node = node->right;
            } else if (node->val > val) {
                node = node->left;
            } else {
                return node;
            }
        }
        return node;
    }

    Node *getMinNode(Node *root) {
        if (root==NULL) {
            return NULL;
        }

        Node *node = root;
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    Node *getMaxNode(Node *root) {
        if (root==NULL) {
            return NULL;
        }

        Node *node = root;
        while (node->right != NULL) {
            node = node->right;
        }
        return node;
    }

    Node *addNode(int val) {
        if(root==NULL){
            root = new Node(val);
        } else {
            root = add(root, val);
        }
        size += 1;
    }

    Node *add(Node *node, int val) {
        if(node==NULL){
            return new Node(val);
        }

        if(node->val < val) {
            node->right = add(node->right, val);
        } else if (node->val > val) {
            node->left = add(node->left, val);
        }
        node->updateHeight();

        return rebalance(node);
    }

    Node *delNode(int val) {
        Node *node = this->getNode(val);
        if (node==NULL) {
            return NULL;
        }
        root = del(root, node);
        delete node;
    }

    Node *del(Node *node, Node *target) {
        if(node==NULL || target==NULL){
            return NULL;
        }

        if(node->val < target->val) {
            node->right = del(node->right, target);
        } else if (node->val > target->val) {
            node->left = del(node->left, target);
        } else {
            size -= 1;
            Node *suc = NULL; 
            if (node->left==NULL) {
                suc = node->right;
                node->right = NULL;
            } else if (node->right==NULL) {
                suc = node->left;
                node->left = NULL;
            } else {
                int factor = getBalancedFactor(node);
                if (factor>0) {
                    suc = getMaxNode(node->left);
                    if (suc!=NULL) {
                        suc->left = del(node->left, suc);
                        suc->right = node->right;
                    }
                } else {
                    suc = getMinNode(node->right);
                    if (suc!=NULL) {
                        suc->right = del(node->right, suc);
                        suc->left = node->left;
                    }
                }
            }
            node = suc;
        }
        if (node != NULL) {
            node->updateHeight();
            return rebalance(node);
        } else {
            return node;
        }
    }

    Node *rebalance(Node *node){
        int factor = getBalancedFactor(node);
        int leftFactor = getBalancedFactor(node->left); 
        int rightFactor = getBalancedFactor(node->right); 

        if(factor>1 && leftFactor>0){ //LL
            return rightRotate(node);
        }
        if(factor<-1 && rightFactor<0){ //RR
            return leftRotate(node);
        }

        if(factor>1 && leftFactor<0){ //LR
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if(factor<-1 && rightFactor>0){ //RL
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void print(){
        if (root==NULL){
            printf("empty tree\n");
            return;
        }
        root->print();
    }
};

#endif
