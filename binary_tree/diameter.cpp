//diameter-of-binary-tree
#include <iostream>
#include <algorithm>

struct Node{
    Node *left;
    Node *right;
    int val;
    Node(int v){val=v; left=right=nullptr;}
};

int depth(Node *root, int &max_dist){
    if(root==nullptr){
        return 0;
    }

    int ldepth = depth(root->left, max_dist);
    int rdepth = depth(root->right, max_dist);
    if(ldepth+rdepth > max_dist){
        max_dist = ldepth+rdepth;
    }
    return std::max(ldepth, rdepth)+1;
}

int diameter(Node *root){
    int max_dist = 0;
    depth(root, max_dist);
    return max_dist;
}

int main(){
    Node a(1), b(2), c(3), d(4), e(5);
    a.left=&b;
    a.right=&c;
    b.left=&d;
    b.right=&e;

    int dist = diameter(&a);
    std::cout << dist << std::endl;
    return 0;
}
