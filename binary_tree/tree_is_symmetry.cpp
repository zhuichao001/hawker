#include <stdio.h>


//Check whether two binary trees are the same

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

bool  is_symmetry(Node *a, Node *b){
    if(a&&!b || !a&&b){
        return false;
    }
    if(!a && !b){
        return true;
    }
    if(a->val != b->val){
        return false;
    }
    if(is_symmetry(a->left, b->right) && is_symmetry(b->left, a->right)){
        return true;
    }
    return false;
}

bool  self_symmetry(Node *root){
    if(!root){
        return true;
    }
    return is_symmetry(root->left, root->right);
}

int main(){
    Node a(1), b(2), c(2), d(3), e(5), f(5), g(3);
    a.left=&b;
    a.right=&c;
    b.left=&d;
    b.right=&e;
    c.left=&f;
    c.right=&g;

    printf("is symmetry:%d\n", self_symmetry(&a));
    return 0;
}
