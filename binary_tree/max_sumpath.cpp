//We have a binary tree. Each node contains an integer. Now please output the largest sum of any path in the tree. Suppose empty path has sum zero. 

struct tree_node {
    struct tree_node *left;
    struct tree_node *right;
    int weight;
}; 


void cal_maxpath(const struct tree_node_t *root, int &end_on_max, int &end_off_max){
    if(root==nullptr){
        end_on_max =0;
        end_off_max =0;
        return;
    }

    if(root->left==nullptr){
        int son_on;
        int son_off;
        cal_maxpath(root->right, son_on, son_off);
        end_off_max = max(son_on, son_off);
        end_on_max = son_on + root->weight;
        return;
    }else{
        int lson_on;
        int lson_off;
        cal_maxpath(root->left, lson_on, lson_off);
        if(root->right==nullptr){
            end_off_max = max(lson_on, lson_off);
            end_on_max = lson_on + root->weight;
            return;
        }else{
            int rson_on;
            int rson_off;
            cal_maxpath(root->right, rson_on, rson_off);
            end_off_max = max(max(lson_off, rson_off), lson_on+root->weight+rson_on);
            end_on_max = root->weight + max(lson_on, rson_on);
        }
    }
}

int sum_maxpath(const struct tree_node_t *root){
    if(root==nullptr){
        return 0;
    }
    int end_on_max =0; 
    int end_off_max =0; 
    cal_maxpath(root, end_on_max, end_off_max);
    return end_on_max > end_off_max ? end_on_max : end_off_max;
}

int main(){
    return 0;
}
