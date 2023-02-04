#include <stdio.h>
#include <math.h>
#include <vector>
#include <list>

//binary-tree-level-order-traversal

struct Node{
    Node *left;
    Node *right;
    int val;
    Node(int v){
        val = v; 
        left = NULL;
        right=NULL;
    }
};


int traversal(Node *root, std::vector<int> &res){
    if(root==NULL) {
        return 0;
    }

    std::list<Node*> queue;
    queue.push_back(root);
    while(!queue.empty()){
        Node *tmp = queue.front();
        queue.pop_front();

        res.push_back(tmp->val);
        if(tmp->left){
            queue.push_back(tmp->left);
        }
        if(tmp->right){
            queue.push_back(tmp->right);
        }
    }
    return res.size();
}


int main(){
    Node a(2), b(3), c(4), d(5), e(7), f(8);
    b.left = &a;
    b.right = &c;
    d.left = &b;  // d is root
    d.right = &f;
    f.left = &e;

    std::vector<int> result;
    printf("count of binary tree:%d\n sorted node values:", traversal(&d, result));
    for(int i=0; i<result.size(); ++i){
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}
