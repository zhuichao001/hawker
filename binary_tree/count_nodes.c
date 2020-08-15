#include <stdio.h>
#include <math.h>

//完全二叉树的节点数量

struct Node;
struct Node{
	Node *left;
    Node *right;
    int val;
};


int countNodes(Node *root){
    if(root==NULL) {
        return 0;
    }

    int lh=1, rh=1;
    {
        for(Node *cur=root; cur->left!=NULL; cur = cur->left){
           ++lh;
        }

        for(Node *cur=root; cur->right!=NULL; cur = cur->right){
           ++rh;
        }
    }
    if(lh==rh){
        return int(pow(2, lh)-1);
    }

    return 1+countNodes(root->left)+countNodes(root->right);
}


int main(){
    Node a, b, c, d, e, f;
    a.val=2;
    b.val=3;
    c.val=4;
    d.val=5;
    e.val=7;
    f.val=8;
    a.left=a.right=NULL;
    b.left=&a;
    b.right=&c;
    c.left=c.right=NULL;
    d.left=&b;
    d.right=&f;
    e.left=e.right=NULL;
    f.left=&e;
    f.right=NULL;
    printf("count of binary tree:%d\n", countNodes(&d));
    return 0;
}
