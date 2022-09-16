#include <stdio.h>
#include <vector>


//output the most right side

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

void  most_right_side(Node *root, std::vector<Node *> &out){
    if(root==nullptr){
        return;
    }

    std::vector<Node *> level[2];
    level[0].push_back(root);
    int idx=0;
    while(!level[idx].empty()){
        out.push_back(level[idx].back());
        int next = 1-idx;
        level[next].clear();
        for(Node *node : level[idx]){
            if(node->left!=nullptr){
                level[next].push_back(node->left); 
            }
            if(node->right!=nullptr){
                level[next].push_back(node->right); 
            }
        }
        idx = next;
    }
}

int main(){
    Node a(0), b(1), c(2), d(3), e(4), f(5), g(3);
    //a.left=&b;
    a.right=&c;
    //b.left=&d;
    //b.right=&e;
    c.left=&f;
    //c.right=&g;

    std::vector<Node *> side;
    most_right_side(&a, side);

    for(int i=0; i<side.size(); ++i){
        fprintf(stderr, "%d\n", side[i]->val);
    }
    return 0;
}
