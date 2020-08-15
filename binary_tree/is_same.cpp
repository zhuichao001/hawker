#include <stdio.h>


//判断两棵二叉树是否相同

struct Node{
    Node *left;
    Node *right;
    int val;
    Node(int v){val=v; left=right=NULL;}
};


bool isSame(Node * one, Node *another){
    if (one==NULL) {
        return another==NULL?true:false;
    }

    if (another==NULL) {
        return false;
    }

    if (! one->val==another->val) {
        return false;
    }

    if (! isSame(one->left, another->left)) {
        return false;
    }
    
    if (! isSame(one->right, another->right)) {
        return false;
    }
    return true;
}


int main(){
    Node a(1), b(2), c(2), d(3), e(3);
    a.left=&b;
    a.right=&c;
    b.right=&d;
    c.left=&e;

    Node _a(1), _b(2), _c(2), _d(3), _e(3);
    _a.left=&_b;
    _a.right=&_c;
    _b.right=&_d;
    _c.left=&_e;

    printf("%d\n", isSame(&a, &_a));
    return 0;
}
