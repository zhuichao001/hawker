#include <iostream>
#include <queue>

using namespace std;


struct Node{
    Node *left;
    Node *right;
    int val;
    Node(int v){val=v; left=right=NULL;}
};


int treeHeight(Node *root){
	queue<Node*> nodes;
    nodes.push(root);
    int height = 0;
    while(!nodes.empty()){
        int size = nodes.size();
        height += 1;
        while(size-->0){
            Node *cur = nodes.front();
            nodes.pop();
            if(cur->left){
                nodes.push(cur->left);
            }
            if(cur->right){
                nodes.push(cur->right);
            }
        }
    }
    return height;
}


int main(){
    Node a(1), b(2), c(2), d(3), e(3);
    a.left=&b;
    a.right=&c;
    b.right=&d;
    c.left=&e;

    cout<<treeHeight(&a)<<endl;
    return 0;
}
