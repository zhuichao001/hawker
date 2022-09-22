#include <string>
#include <stdio.h>
#include "hash_map.h"

hash_map<std::string, std::string> map;

int main(){
    const int N = 1024;
    for(int i=0; i<N; ++i){
        map.insert(std::to_string(i), std::to_string(i));

        std::string v;
        int err = map.find(std::to_string(i), v);
        printf("err:%d, val:%s\n", err, v.c_str());

        if(i%2==1){
            map.remove(std::to_string(i));
        }
    }

    for(int i=0; i<N; ++i){
        std::string v;
        int err = map.find(std::to_string(i), v);
        printf("after err:%d, val:%s\n", err, v.c_str());
    }

    return 0;
}
