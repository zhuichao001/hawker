#include <stdio.h>
#include <math.h>
#include <vector>

//lowest-common-ancestor

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

int path_to_dest(Node *current, int dest_val, std::vector<Node *> &path, bool &found){
    if(current == nullptr){
        return -1;
    }
    if(current->val == dest_val){
        path.push_back(current);
        found = true;
        return 0;
    }
    
    path.push_back(current);
    path_to_dest(current->left, dest_val, path, found);
    if(found) return 0;

    path_to_dest(current->right, dest_val, path, found);
    if(found)return 0;

    path.pop_back();
    return -1;
}

int lowest_common(const std::vector<Node *> &va, const std::vector<Node *> &vb, int &res){
    bool found = false;
    int steps = std::min(va.size(), vb.size());
    for(int i=0; i<steps; ++i){
        if(va[i]==vb[i]){
            res = va[i]->val;
            found = true;
        }else{
            break;
        }
    }
    return found?0:-1;
}

/*             d:5
 *            /   \
 *          b:3   f:8
 *          / \    /
 *        a:2 c:4 e:7
*/
Node *init_tree(){
    static Node a(2), b(3), c(4), d(5), e(7), f(8);
    b.left = &a;
    b.right = &c;
    d.left = &b;  // d is root
    d.right = &f;
    f.left = &e;
    return &d;
}

int main(){
    Node *root = init_tree();

    bool found_a = false, found_b = false;
    std::vector<Node *> path_a;
    std::vector<Node *> path_b;
    path_to_dest(root, 3, path_a, found_a);
    path_to_dest(root, 2, path_b, found_b);

    int res = -1;
    if(lowest_common(path_a, path_b, res)==0){
        printf("success! found common ancestor:%d\n", res);
    }else{
        printf("failed! not found common ancestor\n");
    }
    return 0;
}
