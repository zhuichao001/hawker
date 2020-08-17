#ifndef _BALANCED_SEARCH_TREE_H_
#define _BALANCED_SEARCH_TREE_H_

#include <stdlib.h>
#include <stdio.h>


#define max(a,b) ((a)>(b))?(a):(b)

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
        int l, r;
        if(left==NULL) l = -1;
        else l = left->val;

        if(right==NULL) r = -1;
        else r = right->val;

        printf("%d : <%d, %d>\n", val, l, r);
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

    Node *rightRotate(Node *x) {
        Node *y = x->left;
        x->left = y->right;
        y->right = x;

        x->updateHeight();
        y->updateHeight();
        return y;
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        y->left = x;

        x->updateHeight();
        y->updateHeight();
        return y;
    }

    Node *addNode(int val) {
        if(root==NULL){
            root = new Node(val);
        } else {
            add(root, val);
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
        node->height = 1 + max(getNodeHeight(node->left), getNodeHeight(node->right));

        int factor = getBalancedFactor(node);
        int leftFactor = getBalancedFactor(node->left); 
        int rightFactor = getBalancedFactor(node->right); 

        if(factor>1 && leftFactor>0){
            return rightRotate(node);
        }

        if(factor<-1 && rightFactor<0){
            return leftRotate(node);
        }

        if(factor>1 && leftFactor>0){
            node->left = leftRotate(node->left);
		    return rightRotate(node);
        }

        if(factor<-1 && rightFactor<0){
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
