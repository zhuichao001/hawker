#include <memory.h>
#include <string>

int shortest_midstr(const std::string &left, const std::string &right, std::string &mid){
    if(left>=right){
        return -1;
    }

    const int len = std::min(left.size(), right.size());
    char buf[len+2];
    memset(buf, 0, sizeof(buf));

    for(int i=0; i<len; ++i){
        if(left[i] != right[i]){
            buf[i] = left[i] + (right[i]-left[i])/2;
            mid = buf;
            return 0;
        }
        buf[i] = left[i];
    }
    buf[len] = right[len]/2;
    mid = buf;
    return 0;
}
