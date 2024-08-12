#include<string>
#include<iostream>

int shortest_edit_distance(const std::string &a, const std::string &b){
    int dist[a.size()+1][b.size()+1];
    dist[0][0]=0;
    dist[1][0]=1;
    dist[0][1]=1;
    for(int i=1; i<=a.size(); ++i){
        for(int j=1; j<=b.size(); ++j){
           if(a[i]==b[j]){
               dist[i][j]=dist[i-1][j-1];
           }else{
               dist[i][j]=std::min(dist[i-1][j], dist[i][j-1])+1;
           }
        }
    }
    return dist[a.size()][b.size()];
}

int main(){
    std::string a="adcdef";
    std::string b="abcdf";
    int min_dist = shortest_edit_distance(a,b);
    std::cout << "min edit distance:" << min_dist << std::endl;
    return 0;
}
