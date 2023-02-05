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

bool isSame(Node * one, Node *another){
    if (one==NULL) {
        return another==NULL?true:false;
    }

    if (another==NULL) {
        return false;
    }

    if (one->val!=another->val) {
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
    //      a:1
    //     /   \
    //    b:2   c:2
    //     \     /
    //     d:3  e:3
    Node a(1), b(2), c(2), d(3), e(3);
    a.left=&b;      
    c.left=&e;      
    a.right=&c;     
    b.right=&d;     

    //     a:1                  
    //    /   \
    //   b:2  c:2
    //    \    /
    //    d:3 e:3
    Node _a(1), _b(2), _c(2), _d(3), _e(3);
    _a.left=&_b;    
    _a.right=&_c;   
    _b.right=&_d;   
    _c.left=&_e;    
                    
    printf("%s\n", isSame(&a, &_a)?"same":"different");
    return 0;
}
