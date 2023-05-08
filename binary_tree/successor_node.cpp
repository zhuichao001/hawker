#include <stdio.h>
#include <assert.h>

struct Node{
    Node *parent;
    Node *left;
    Node *right;
    int val;
    Node(int v):
        parent(nullptr),
        left(nullptr),
        right(nullptr){
        val=v;
    }
    
    void setParent(Node *p){
        parent = p;
    }

    void setChilds(Node *l, Node *r){
        left = l;
        right = r;
    }
};

Node *rightAncestor(Node *node){
    Node *ancestor = node;
    while(node->parent!=nullptr && node->parent->right==node){
        ancestor = node->parent;
        node = node->parent;
    }
    return ancestor;
}

Node *minimalNode(Node *node){
    while(node->left!=nullptr){
        node = node->left;
    }
    return node;
}

Node * successorNode(Node *node){
    assert(node!=nullptr);
    if(node->right==nullptr){
        node = rightAncestor(node);
        if(node->parent==nullptr){
            return nullptr;
        }
        if(node->parent->left==node){
            return node->parent;
        }else{
            return nullptr;
        }
    }else{
        return minimalNode(node->right);
    }
}

int main(){
    //       a:5
    //     /     \
    //    b:2    c:7
    //    / \    /  \
    //  d:1 e:3 f:6 g:8
    Node a(5), b(2), c(7), d(1), e(3), f(6), g(8);
    a.setChilds(&b, &c);
    b.setChilds(&d, &e);
    c.setChilds(&f, &g);
    b.setParent(&a);
    c.setParent(&a);
    d.setParent(&b);
    e.setParent(&b);
    f.setParent(&c);
    g.setParent(&c);

    Node * nodes[] = {&a, &b, &c, &d, &e, &f, &g};
    for(int i=0; i<sizeof(nodes)/sizeof(nodes[0]); ++i){
        Node *node = nodes[i];
        Node *successor = successorNode(node);
        if(successor!=nullptr){
            printf("%d successor is %d\n", node->val, successor->val);
        }else{
            printf("%d has no successor\n", node->val);
        }
    }

    return 0;
}
