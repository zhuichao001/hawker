#include<iostream>
#include<string>
#include<memory.h>

using namespace std;

int min3(int a, int b, int c){
    if (a<b){
        return a<c?a:(b<c?b:c);
    } else {
        return b<c?b:c;
    }
}

int minDist(string a, string b){
    const int M=a.size(), N=b.size();
    int dp[M+1][N+1];
    memset(dp, 0, sizeof(dp));

    for(int i=1; i<=M; i++){
        dp[i][0]=i;
    }

    for(int j=1; j<=N; j++){
        dp[0][j]=j;
    }

    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            if(a[i]==b[j]){
                dp[i+1][j+1] = dp[i][j];
            }else{
                dp[i+1][j+1] = 1+min3(dp[i][j], dp[i][j+1], dp[i+1][j]);
            }
        }
    }
    return dp[M][N];
}

int main(){
    cout<<minDist("horse", "ros")<<endl;
}

