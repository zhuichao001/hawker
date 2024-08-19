#include <iostream>
#include <string>
#include <cstdint>

//return errcode. 0:success, -1:failed
int ip_to_uint32(const std::string &ipstr, uint32_t &res){
    res = 0;

    uint16_t sub = 0;
    size_t doc_cnt = 0;
    size_t dig_cnt = 0;
    for (int i=0; i<ipstr.size(); ++i) {
        if (ipstr[i]=='.') {
            if (++doc_cnt==4 || dig_cnt==0) { //check format
                return -1;
            }
            res = (res<<8) + sub;
            sub = 0;
            dig_cnt = 0;
        } else if (ipstr[i]>='0' && ipstr[i]<='9') {
            if (dig_cnt>0 && sub==0) { //check double-0
                return -1;
            }
            sub = sub*10 + (ipstr[i]-'0');
            if (sub>=256) {
                return -1;
            }
            ++dig_cnt;
        } else {
            return -1;
        }
    }
    res = (res<<8) + sub;
    return doc_cnt==3 ? 0:-1;
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
