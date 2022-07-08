//We have a binary tree. Each node contains an integer. Now please output the largest sum of any path in the tree. Suppose empty path has sum zero. 

#include <stdio.h>
#include <assert.h>
#include <cmath>
#include <initializer_list>

typedef struct tree_node_t {
    struct tree_node_t *left;
    struct tree_node_t *right;
    int weight;
    tree_node_t(int w=0):
        left(nullptr),
        right(nullptr),
        weight(w){
    }
    void set_sons(tree_node_t *lson, tree_node_t *rson){
        left = lson;
        right = rson;
    }
}tree_node_t;


template<typename T>
T Max(std::initializer_list<T> some){
    assert(some.size()>=1);
    T data = *some.begin();
    for (T one : some){
        data =std::max(data, one);
    }
    return data;
}

void cal_maxpath(const tree_node_t *node, int &end_on_max, int &end_off_max){
    if(node==nullptr){
        end_on_max =0;
        end_off_max =0;
        return;
    }

    if(node->left==nullptr){
        int son_on;
        int son_off;
        cal_maxpath(node->right, son_on, son_off);
        end_off_max = std::max(son_on, son_off);
        end_on_max = son_on + node->weight;
        return;
    }else{
        int lson_on;
        int lson_off;
        cal_maxpath(node->left, lson_on, lson_off);
        if(node->right==nullptr){
            end_off_max = std::max(lson_on, lson_off);
            end_on_max = lson_on + node->weight;
            return;
        }else{
            int rson_on;
            int rson_off;
            cal_maxpath(node->right, rson_on, rson_off);
            end_off_max = Max({lson_off, rson_off, lson_on, rson_on, lson_on+rson_on+node->weight}); 
            end_on_max = node->weight + std::max(lson_on, rson_on);
        }
    }
}

int sum_maxpath(tree_node_t *root){
    if(root==nullptr){
        return 0;
    }
    int end_on_max =0; 
    int end_off_max =0; 
    cal_maxpath(root, end_on_max, end_off_max);
    return end_on_max > end_off_max ? end_on_max : end_off_max;
}

void test0(){
    tree_node_t n0(-4);
    tree_node_t n1(3);
    tree_node_t n2(6);
    n0.set_sons(&n1, &n2);
    int m = sum_maxpath(&n0);
    fprintf(stderr, "%d\n", m);
}

int main(){
    test0();
    return 0;
}
