#include <string>
#include <iostream>

inline char tochar(uint8_t c){
    return c+'0';
}

void add(const std::string &sa, const std::string &sb, std::string &res){
    char rest=0;
    const int N = std::max(sa.size(),sb.size())+1;
    char digits[N+1];
    int k = N-1;
    int i=sa.size()-1, j=sb.size()-1;
    while(i>=0 || j>=0){
        char cur = rest;
        if(i>=0) cur += sa[i--] - '0';
        if(j>=0) cur += sb[j--] - '0';
        char c = cur%10;
        rest = cur>=10? 1: 0;
        digits[k--] = tochar(c);
    }
    if(rest>0){
        digits[k] = tochar(rest);
    }else{
        ++k;
    }
    res.reserve(N);
    res.append(&digits[k], N-k);
}


int main(){
    const char *a="123";
    const char *b="1999";
    std::string res;
    add(a,b,res);
    std::cout << res << std::endl;
    return 0;
}
