#include<iostream>
#include<string>
#include<memory.h>

using namespace std;

int min(int a, int b){
    return a<b?a:b;
}

int minDist(string a, string b){
    const int M=a.size(), N=b.size();
    int dp[2][N+1];
    memset(dp, 0, sizeof(dp));

    for(int j=1; j<=N; j++){
        dp[0][j]=j;
    }

    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            dp[i&1][0] = i;
            if(a[i]==b[j]){
                dp[(i+1)&1][j+1] = dp[i&1][j];
            }else{
                dp[(i+1)&1][j+1] = 1+min(dp[i&1][j], dp[i&1][j+1]);
            }
        }
    }
    return dp[M&1][N];
}

int main(){
    cout<<minDist("horse", "ros")<<endl;
}

