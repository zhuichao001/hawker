#include <string>
#include <algorithm>
#include <iostream>


std::string shortestSeparator(const std::string &s1, const std::string &s2){
    std::string sep; //separator
    sep.reserve(std::min(s1.size(),s2.size())+1);
    for(int i=0; ;++i){
        if(i==s1.size() || i==s2.size()){
            sep += char(1);
            break;
        }
        if(s1[i]!=s2[i]){
            sep += char(std::min(s1[i],s2[i])+1);
            break;
        }
        sep +=s1[i];
    }
    return sep;
}

void test(){
    std::string sep = shortestSeparator("a", "abfg");
    for(int i=0; i<sep.size(); ++i){
        std::cout << int(sep[i]) << " " << sep[i] << std::endl;
    }
}

int main(){
    test();
    return 0;
}

