#include<queue>
#include<vector>
#include<utility>
#include<iostream>
#include<iterator>

//使用双端队列来实现
std::vector<int> maxval_sliding(const std::vector<int> &nums, const int window_size){
    std::vector<int> res;
    typedef int IndexType;
    std::deque<IndexType> maxq;
    res.reserve(nums.size()-window_size+1);
    for (int i=0; i<nums.size(); ++i) {
        while (!maxq.empty() && nums[i]>nums[maxq.back()]) {
            maxq.pop_back();
        }
        maxq.push_back(i);
        if (i < window_size-1) {
            continue;
        }
        if (maxq.front() <= i-window_size) {
            maxq.pop_front();
        }
        res.push_back(nums[maxq.front()]);
    }
    return res;
}


int main(){
    std::vector<int> sequence={2,3,6,1,7,9,2,1,5};
    std::vector<int> res = maxval_sliding(sequence, 3);
    std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout," "));
    std::cout << std::endl;
}
