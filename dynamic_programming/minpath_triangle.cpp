#include <iostream>
#include <cmath>
#include <algorithm>

//the minimal path for triangle

int main(){
    const int N = 4;
    int arr[N][N] = {{2}, {3,4}, {6,5,7}, {4,1,8,3}};
    int dp[N] = {0,0,0,0};
    for(int i=0; i<N; ++i){
        dp[i] = arr[N-1][i];
    }

    for(int i=N-2; i>=0; --i){
        for(int j=0; j<=i; ++j){
            dp[j] = std::min(dp[j], dp[j+1]) + arr[i][j];
        }
    }
    std::cout << "min path :" << dp[0] << std::endl;
    return 0;
}
