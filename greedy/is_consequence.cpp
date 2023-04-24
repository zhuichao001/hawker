//有两副扑克牌，从中任意拿出5张牌（扑克牌有1-9及大小王，大小王用0表示），判断这5张牌是否为顺子
//判断顺子的标准：1-9，数字连续即为顺子(大小王可以代替任何牌)，比如：00246为顺子，22340不为顺子

#include <iostream>
#include <string>
#include <memory.h>
using namespace std;

bool is_consequence(const std::string &s){
    if(s.size()!=5){
        return false;
    }

    int num[10];
    memset(num,0,sizeof(num));

    for(int i=0;i<s.size();++i){
        ++num[s[i]-'0'];
        if(s[i]!='0' && num[i]>=2){
            return false;
        }
    }

    int left=0, right=0;
    {
        for(int i=1;i<10;++i){
            if(num[i]!=0){
                left=i;
                break;
            }
        }

        for(int j=9;j>=1;--j){
            if(num[j]!=0){
                right=j;
                break;
            }
        }
    }

    return right-left>=3-num[0] && right-left<=5;
}

int main() {
    std::string s;
    std::cin>>s;

    bool ok =  is_consequence(s);
    std::cout << (ok?"yes":"no") << std::endl;
    return 0;
}
