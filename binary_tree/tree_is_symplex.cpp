#include <iostream>
using namespace std;

//判断二叉树是否是内部对称的

struct Node{
    Node *left;
    Node *right;
    int val;
    Node(int v){val=v; left=right=NULL;}
};


bool isSubSymplex(Node * one, Node *another){
    if (one==NULL) {
        return another==NULL?true:false;
    }

    if (another==NULL) {
        return false;
    } else {
        bool a = isSubSymplex(one->left, another->right);
        bool b = isSubSymplex(one->right, another->left);
        return one->val==another->val && a && b;
    }
}


bool isSymplex(Node *root){
    if(root==NULL){
        return true;
    }
    return isSubSymplex(root->left, root->right);
}


int main(){
    /*       a
           /   \
          b     c
           \   /
            d e
    */
    Node a(1), b(2), c(2), d(3), e(3);
    a.left=&b;
    a.right=&c;
    b.right=&d;
    c.left=&e;
    cout<<isSymplex(&a);
}
