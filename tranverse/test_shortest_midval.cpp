#include <stdio.h>
#include "shortest_midval.h"

char itoh(uint8_t d){
    if(d<10){
        return '0'+d;
    }else{
        return 'a'+d-10;
    }
}

std::string str_to_hex(const std::string &in){
    std::string out;
    char buf[3*in.size()];
    for(int i=0; i<in.size(); ++i){
        buf[i*3+0] = itoh(in[i]>>4); 
        buf[i*3+1] = itoh(in[i]&0xf); 
        buf[i*3+2] = ' ';
    }
    buf[3*in.size()-1] = '\0';
    out = buf;
    return out;
}

void test(){
    std::string a = "a";
    std::string b = "af";
    std::string m; 
    shortest_midstr(a, b, m);
    fprintf(stderr, "mid hex:0x %s\n", str_to_hex(m).c_str());
    fprintf(stderr, "mid str:%s\n", m.c_str());
}

int main(){
    test();
    return 0;
}
