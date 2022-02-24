#include "lfu.h"


void test_lfu(){
    LFUCache<std::string> lfu(3); 
    std::string a("123"), b("234"), c("555");
    lfu.put("a", a); 
    lfu.put("b", b); 
    lfu.put("c", c); 
    lfu.display();

    a = "399";
    lfu.put("a", a);
    lfu.display();

    std::string v1;
    lfu.get("a", v1);
    std::cout<<"val of a:"<<v1<<std::endl;
    lfu.display();

    std::string v2;
    lfu.get("b", v2);
    std::cout<<"val of b:"<<v2<<std::endl;
    lfu.display();
}

int main(){
    test_lfu();
    return 0;
}
