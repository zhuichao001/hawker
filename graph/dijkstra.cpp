#include <iostream>
#include <algorithm>
#include <cstring>
#include <limits.h>

using namespace std;

const int N = 3;

int g[N][N] = {{1,2,2},{2,3,1},{1,3,4}};
int dist[N];
bool visted[N];

int dijkstra(){
    for (int i=0; i<N; ++i){
        dist[i] = INT_MAX;
    }
    dist[1] = 0;

    for (int i = 0; i < N; i ++){
        int t = -1;
        for (int j = 0; j < N; j ++)
            if (!visted[j] && (t == -1 || dist[t] > dist[j]))
                t = j;

        for (int j = 0; j < N; j ++)
            dist[j] = min(dist[j], dist[t] + g[t][j]);

        visted[t] = true;
    }


    if (dist[N-1] == INT_MAX) return -1;
    return dist[N-1];
}

int main(){
    cout << dijkstra() << endl;
    return 0;
}
