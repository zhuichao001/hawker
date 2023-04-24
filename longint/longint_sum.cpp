#include <memory.h>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void reverse(char *s, int len){
    for(int i=0; i<len/2; ++i){
        char c = s[i];
        s[i] = s[len-1-i];
        s[len-1-i]=c;
    }
}

std::string sum(const std::string &s1, const std::string &s2){
    const int len1 = s1.size();
    const int len2 = s2.size();

    const int len = std::max(len1, len2)+1;
    char res[len];
    memset(res, 0, sizeof(res));
   
    int rest = 0;
    int i=0;
    while(i<len-1){
        int v = rest;
        if(i<len1){
            v += s1[len1-1-i]-'0';
        }
        if(i<len2){
            v += s2[len2-1-i]-'0';
        }
        res[i] = '0'+v%10;
        rest = v>9?1:0;
        ++i;
    }
    if(rest==0){
        res[i] = 0;
    }else{
        res[i] = '1';
        res[++i] = 0;
    }
    
    reverse(res, i);
    return std::string(res);
}

int main() {
    std::string s1;
    std::string s2;
    std::cin>>s1;
    std::cin>>s2;

    std::string s3 = sum(s1,s2);
    std::cout << s3 << std::endl;
    return 0;
}
