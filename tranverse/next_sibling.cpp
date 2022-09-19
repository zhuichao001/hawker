#include <iostream>
#include <string>

std::string NextSibling(const std::string& in) {   
    std::string res;
    if (!in.empty()) {
        res.reserve(in.size()+1);
    }
    bool tailed_0xff = false;
    for (auto it = in.crbegin(); it != in.crend(); ++it) {
        auto ch = static_cast<uint8_t>(*it);
        if (ch < 0xff) {
            if(tailed_0xff){
                res.assign(in.cbegin(), it.base());
                res.back() = static_cast<char>(ch + 1);
            }else{
                res = in;
                res.push_back(static_cast<char>(1));
            }
            break;
        }else{
            tailed_0xff = true;
        }
    }
    return res;
}

void printString(const std::string &s){
    for(int i=0; i<s.size(); ++i){
        if(s[i]>='a'){
            std::cout << s[i] << " ";
        }else{
            std::cout << "\\" << int(s[i]);
        }
    }
    std::cout << std::endl;
}

int main(){
    std::string in = "b";
    in.push_back(char(0xff));
    in.push_back(char(0xff));
    std::string out = NextSibling(in);
    printString(out);
    return 0;
}
