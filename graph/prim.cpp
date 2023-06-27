#include <iostream>
#include <string>
#include <limits.h>

using namespace std;

const int MaxVertex = 10;
const int Maxedges = 100;
typedef string DataType;

const int VertexNum = 6;

struct Edge {
    int adj;
    int cost;
}edges[MaxVertex];

class Graph {
public:
    void Prim(int v);
    int MinAdjace();
private: 
    DataType vertex[MaxVertex] = {"v0", "v1", "v2", "v3", "v4", "v5"}; 
    int edge[MaxVertex][MaxVertex] = {{0,34,46,INT_MAX,INT_MAX,19}, 
        {34,0,INT_MAX,INT_MAX,12,INT_MAX},
        {46,INT_MAX,0,17,INT_MAX,25},
        {INT_MAX,INT_MAX,17,0,38,25},
        {INT_MAX,12,INT_MAX,38,0,26},
        {19,INT_MAX,25,25,26,0}};
};

//从顶点v出发构造最小生成树
void Graph::Prim(int v){
    for(int i=0; i<VertexNum; i++) { //初始化辅助数组 
        edges[i].cost = edge[v][i];
        edges[i].adj = v;
    }
    edges[v].cost = 0;

    for(int k=1; k<VertexNum; k++) {
        int j = MinAdjace();
        cout<<vertex[j]<<" "<<vertex[edges[j].adj]<<" "<<edges[j].cost<<" "<<endl;

        edges[j].cost = 0;
        for(int i=0; i<VertexNum; i++) {
            if(edge[i][j]<edges[i].cost){
                edges[i].cost = edge[i][j];
                edges[i].adj = j;
            }
        }
    }
}

int Graph::MinAdjace() {
    int min = INT_MAX;
    int dest;
    for(int i=0; i<VertexNum; i++) {
        if(edges[i].cost<min && edges[i].cost!=0) {
            min = edges[i].cost;
            dest = i;
        }
    }
    return dest;
}

int main() {
    Graph g{};
    g.Prim(0);
}
