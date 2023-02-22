#include <iostream>
#include <string>
#include <cstdint>

//return errcode. 0:success, -1:failed
int ip_to_uint32(const std::string &ipstr, uint32_t &res){
    res = 0;
    int len = ipstr.size();

    uint16_t sub = 0;
    size_t dot_num = 0;
    size_t dig_num = 0;
    for (int i=0; i<len; ++i) {
        if (ipstr[i]=='.') {
            if (++dot_num==4 || dig_num==0) { //check format
                return -1;
            }
            res = (res<<8) + sub;
            sub = 0;
            dig_num = 0;
        } else if (ipstr[i]>='0' && ipstr[i]<='9') {
            if (dig_num>0 && sub==0) { //check double-0
                return -1;
            }
            sub = sub*10 + (ipstr[i]-'0');
            if (sub>256) {
                return -1;
            }
            ++ dig_num;
        } else {
            return -1;
        }
    }
    res = (res<<8) + sub;
    return dot_num==3 ? 0:-1;
}

int main() {
    std::string ipstr;

    std::cout << "Input IP:";
    std::cin >> ipstr;

    uint32_t res;
    int err = ip_to_uint32(ipstr, res);
    std::cout << err <<":" << res << std::endl;

    return 0;
}
