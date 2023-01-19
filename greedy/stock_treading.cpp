//Buy and sell only once, how to get the maximum profit

#include <iostream>
#include <algorithm>
#include <limits.h>

int max_profit(int prices[], int num){
    int res = 0;
    int min = INT_MAX;
    for(int i=0; i<num; ++i){
        min = std::min(min, prices[i]);
        res = std::max(res, prices[i]-min);
    }
    return res;
}

int main(){
    int prices[] = {7,1,5,3,6,4};
    int profit = max_profit(prices, sizeof(prices)/sizeof(prices[0]));
    std::cout << "profit:" << profit << std::endl;
    return 0;
}
