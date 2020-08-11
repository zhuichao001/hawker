#include <iostream>

using namespace std;

class UnionFind{
    int count;
    int units; //连通性
    int *parent;
    int *weight; //树的节点数

  public:

    UnionFind(int n):count(n),units(n){
        parent = new int[count];
        weight = new int[count];
        for (int i = 0; i < count; ++i) {
            parent[i] = i;
            weight[i] = 1;
        }
    }

    void Union(int p, int q) {
         int root_p = Root(p);
         int root_q = Root(q);
         if (weight[root_p] < weight[root_q]) {
             parent[root_p] = root_q;
             weight[root_q] += weight[root_p];
         } else {
             parent[root_q] = root_p;
             weight[root_p] += weight[root_q];
         }
         units -= 1;
    }

    int Root(int x) {
        while(parent[x]!=x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    int Units() {
        return units;
    }

    void Print() {
        for (int i = 0; i < count; ++i) {
            cout<<"parent of "<<i<<":"<<parent[i]<<endl;
        }
    }

    ~UnionFind() {
        delete []parent;
        delete []weight;
    }
};


int main(){
    UnionFind u(9);
    u.Union(0,1);
    u.Union(2,1);
    u.Union(6,2);
    u.Union(8,2);
    u.Union(5,2);
    u.Union(4,5);

    u.Union(7,3);

    u.Print();

    cout<<"unions:"<<u.Units()<<endl;
}
