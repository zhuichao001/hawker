#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<cctype>
#include<queue>
#include<vector>
#include<cmath>

using namespace std;

struct pos{
    int x;
    int y;
    pos():x(0),y(0){}
    pos(const pos &_p):x(_p.x),y(_p.y){}
    pos(int i, int j):x(i),y(j){}
};

struct node{
    pos p;
    int F, G, H; //F:src->cur->dest cost, G: src->cur, H: cur->dest
    node():F(0),G(0),H(0){}
    node(const pos &_p){
        p.x = _p.x;
        p.y = _p.y;
        F = G = H = 0;
    }
    friend bool operator < (const node &a, const node &b) {
        return a.F < b.F;
    }
};

struct compare_node_ptr{
    bool operator()(node *a, node *b)const{return a->F > b->F;}
};

struct area{
    char **Map;
    bool **Visited;
    int  **Cost;
    pos  **Prev;
    int  R, C;
    const char Empty, Wall;
    pos src, dst;

    area(char **_map, int _r, int _c, char _e, char _w, pos _src, pos _dst) : R(_r), C(_c), Empty(_e), Wall(_w){
        src = _src;
        dst = _dst;

        Map = new char*[R*sizeof(char*)];

        Visited = new bool*[R*sizeof(bool*)];
        Visited[0] = new bool[R*C*sizeof(bool)];

        Cost = new int*[R*sizeof(int*)];
        Cost[0] = new int[R*C*sizeof(int)];

        Prev = new pos*[R*sizeof(pos*)];
        Prev[0] = new pos[R*C*sizeof(pos)];

        for(int i=0; i<R; ++i){
            Map[i] = (char*)_map + i*C*sizeof(char);
            Visited[i] = Visited[0] + i*C*sizeof(bool); 
            Cost[i] = Cost[0] + i*C*sizeof(int); 
            Prev[i] = Prev[0] + i*C*sizeof(pos); 

            for(int j=0; j<C; ++j){
                Visited[i][j] = false;
                Cost[i][j] = 0;
                Prev[i][j].x = i;
                Prev[i][j].y = j;
            }
        }
    }

    ~area(){
        delete []Map;

        delete []Visited[0];
        delete []Visited;

        delete []Cost[0];
        delete []Cost;
    }

    int estimate(pos *const dot)const{ //value of H
        int delta_x = abs(dot->x - dst.x);
        int delta_y = abs(dot->y - dst.y);
        int m = min(delta_x, delta_y);
        return 141*sqrt(m*m) + 100*abs(delta_x - delta_y);
    }

    bool reachgoal(pos *const dot)const{
        return dot->x==dst.x && dot->y==dst.y;
    }

    void mark(pos *const dot){
        if(!isinside(dot)){
            return;
        }
        Visited[dot->x][dot->y] = 1;
    }

    bool isinside(pos *const dot) const {
        if(dot->x>=0 && dot->x<R && dot->y>=0 && dot->y<C){
            return true;
        } else {
            return false;
        }
    }

    bool iswall(pos *const dot, pos *const last) const {
        int x = dot->x;
        int y = dot->y;
        if(Map[x][y]==Wall){
            return true;
        }
        
        if(last->x!=x && last->y!=y){
            return Map[last->x][y]==Wall || Map[x][last->y]==Wall;
        }
        return false;
    }

    bool isvisited(pos *const dot) const {
        return Visited[dot->x][dot->y]==1;
    }
};

node* shortest_path(area *map){
    int direc[8][2] = {{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
    priority_queue<node*, vector<node*>, compare_node_ptr> pq;

    node *start = new node(map->src);
    pq.push(start);

    while(!pq.empty()){
        node *nearest = pq.top();
        pq.pop();

        if(map->isvisited(&nearest->p)){
            continue;
        }
        map->mark(&nearest->p);

        if(map->reachgoal(&nearest->p)){
            return nearest; //FINISHED
        }

        pos foot;
        for(int i=0; i<8; ++i){
            foot.x = nearest->p.x + direc[i][0];
            foot.y = nearest->p.y + direc[i][1];
            if(!map->isinside(&foot)){
                continue;
            } 
            if(map->iswall(&foot, &nearest->p)){
                continue;
            } 

            int mvcost = direc[i][0]*direc[i][1]==0? 100:100;
            node *cur = new node(foot);
            cur->G = nearest->G + mvcost;
            cur->H = map->estimate(&foot);
            cur->F = cur->G/4 + cur->H*3/4; //important

            if(map->isvisited(&foot) && cur->F>=map->Cost[foot.x][foot.y]){
                delete cur;
                continue;
            }

            map->Cost[foot.x][foot.y] = cur->F;
            pq.push(cur);
            map->Prev[foot.x][foot.y].x = nearest->p.x;
            map->Prev[foot.x][foot.y].y = nearest->p.y;
        }
        delete nearest;
    }
    return NULL;
}

void display_path(area *map, const pos *goal, const pos *from) {
    if(goal==NULL){
        cout<<"warning, goal is null"<<endl;
        return;
    }

    for(int i=0; i<map->R; ++i){
        for(int j=0; j<map->C; ++j){
            cout<< map->Prev[i][j].x<<","<<map->Prev[i][j].y<< " ";
        }
        cout<<endl;
    }

    int x=goal->x, y=goal->y;
    while(x!=from->x || y!=from->y){
        cout<<x<<","<<y<<" -> ";
        int i=x, j=y;
        x = map->Prev[i][j].x;
        y = map->Prev[i][j].y;
    }
    cout<<x<<","<<y<<endl;
}

void test(){
    const int R=8, C=8;
    char o=' ', w='*';
    char dots[R][C] = {
        {o, o, o, o, o, o, o, o,},
        {o, o, w, o, o, o, o, o,},
        {o, o, w, o, o, o, o, o,},
        {o, o, w, o, o, o, o, o,},
        {o, o, o, w, w, o, o, o,},
        {o, o, w, o, o, o, o, o,},
        {o, o, w, o, o, o, o, o,},
        {o, o, o, o, o, o, o, o,},
    };

    pos src(3, 0);
    pos dst(4, 7);

    area map((char**)dots, C, R, o, w, src, dst);
    node *goal = shortest_path(&map);
    display_path(&map, &dst, &src);
}

int main(){
    test();
    return 0;
}
