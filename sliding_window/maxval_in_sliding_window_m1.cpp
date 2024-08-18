#include<queue>
#include<vector>
#include<utility>
#include<iostream>
#include<iterator>

typedef int ValType ;
typedef int IndexType ;
typedef std::pair<ValType,IndexType> SlidPairType;

//使用最大堆实现
std::vector<int> maxval_sliding(const std::vector<int> &nums, const int window_size){
    std::vector<int> res;
    std::priority_queue<SlidPairType> maxheap;
    res.reserve(nums.size()-window_size+1);
    for(int i=0; i<nums.size(); ++i){
        maxheap.push(SlidPairType(nums[i],i));
        if(i<window_size-1){
            continue;
        }
        SlidPairType t = maxheap.top();
        while(t.second <= i-window_size){
            maxheap.pop();
            t=maxheap.top();
        }
        res.push_back(t.first);
    }
    return res;
}


int main(){
    std::vector<int> sequence={2,3,6,1,7,9,2,1,5};
    std::vector<int> res = maxval_sliding(sequence, 3);
    std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout," "));
    std::cout << std::endl;
}
