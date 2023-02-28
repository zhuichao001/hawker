#include <iostream>
#include <string>
#include <memory.h>

int max_common_substr(const std::string &s1, const std::string &s2){
    int maxcom = -1;

    const int len1 = s1.size();
    const int len2 = s2.size();

    int com[len1+1][len2+1];
    memset(&com, 0, sizeof(com));

    for(int i=0; i<len1; ++i){
        for(int j=0; j<len2; ++j){
            if(s1[i]==s2[j]){
                com[i+1][j+1] = std::max(com[i][j]+1, std::max(com[i+1][j], com[i][j+1]));
            }else{
                com[i+1][j+1] = std::max(com[i+1][j], com[i][j+1]);
            }
            if(com[i+1][j+1]>maxcom){
                maxcom = com[i+1][j+1];
            }
        }
    }
    return maxcom;
}


int main(){
    std::string s1 = "a2ds3ds4fa5";
    std::string s2 = "3h45g12";
    int maxcom = max_common_substr(s1, s2);
    std::cout << "max length of common substring is:" << maxcom << std::endl;
    return 0;
}
