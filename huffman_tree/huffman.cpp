#include<iostream>
#include<string.h>
#include<cctype>
#include<queue>
#include<vector>

using namespace std;


struct node{
    char cha;
    int weight;
    struct node *left, *right;

    node():cha(' '), weight(0), left(NULL), right(NULL){}
    node(char c, int w, node *l, node *r):cha(c), weight(w), left(l), right(r){}
    node(char c, int w):cha(c), weight(w), left(NULL), right(NULL){}

    friend bool operator < (const node &a, const node &b) {
        return a.weight < b.weight;
    }
};


struct compare_node_ptr{
    bool operator()(node *a, node *b)const{return a->weight>b->weight;}
};


node *build(const char *src, int n){
    priority_queue<node*, vector<node*>, compare_node_ptr> pq;
    int hash[26]={0,};
    for(int i=0; i<n; ++i){
        char c = tolower(src[i]);
        if(c>='a'&&c<='z'){
            hash[c-'a'] += 1;
        }
    }

    for(int j=0; j<26; ++j){
        if(hash[j]>0){
            node *p = new node(j+'a', hash[j]);
            cout<<char(j+'a')<<" -> "<<hash[j]<<endl;
            pq.push(p);
        }
    }

    while(pq.size()>1){
        node *first = pq.top();
        pq.pop();
        node *second = pq.top();
        pq.pop();
        
        node *parent = new node(' ', first->weight + second->weight, first, second);
        pq.push(parent);
    }
    return pq.top();
}


void display(node *root, char *prefix, int len){
    if(root->cha!=' '){
        cout<<root->cha <<":"<<prefix<<endl;
    }
    if(root->left!=0){
        prefix[len]='0';
        prefix[len+1]='\0';
        display(root->left, prefix, len+1);
    }
    if(root->right!=0){
        prefix[len]='1';
        prefix[len+1]='\0';
        display(root->right, prefix, len+1);
    }
}


void release(node *root){
    if(root==NULL){
        return;
    }

    if(root->left==NULL && root->right==NULL){
        delete root;
        return;
    }

    if(root->left!=NULL){
        release(root->left);
    }
    if(root->right!=NULL){
        release(root->right);
    }

    delete root;
}


void test(){
    const char *src = "abaaassdsadssssaaassss";
    node *root = build(src, strlen(src));
    char prefix[20]={0,};
    display(root, prefix, 0);
    release(root);
}


int main(){
    test();
    return 0;
}
