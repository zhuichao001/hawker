#include <iostream>
#include <algorithm>
#include <string>
#include <map>

//无重复字符的最长子串
int max_sublen(const std::string &src) {
    std::unordered_map<char, int> index;
    int res=0;
    for (int i=0, left=0; i<src.size(); ++i) {
        const char &c = src[i];
        if (index.find(c) == index.end()) {
            res = std::max(res, i-left+1);
        } else {
            left = index[c]+1;
        }
        index[c] = i;
    }
    return res;
}

int main(){
    std::cout << max_sublen("aabcabkda") << std::endl;
    return 0;
}
