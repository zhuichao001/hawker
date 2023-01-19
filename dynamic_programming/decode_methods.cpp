//https://leetcode-cn.com/problems/decode-ways
#include <iostream>
#include <string>

int decode_methods(std::string s){
    int pre1=1, pre2 = 1;
    int cur=1;
    for(int i=0; i<s.size(); ++i){
        if(s[i]=='0'){
            if(i>0 && s[i-1]>='1' && s[i-1]<='2'){
                cur = pre2;
            }else{
                cur = 0;
            }
        }else{
            if(i-1>0 && s[i-1]>='1'){
                cur += pre1;
            }
            if(i-2>0 && s[i-2]<='2' && s[i-1]<='6'){
                cur += pre2;
            }
        }
        pre2 = pre1;
        pre1 = cur;
    }
    return pre1+pre2;
}

int main(){
    int n = decode_methods("226");
    std::cout << n << std::endl;
    return 0;
}
