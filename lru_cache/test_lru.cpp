#include "lru.h"


void test_lru(){
    LRUCache<std::string, std::string> lru(3); 
    std::string a("123"), b("234"), c("555");
    lru.put("a", a); 
    lru.put("b", b); 
    lru.put("c", c); 
    lru.display();

    a = "399";
    lru.put("a", a);
    lru.display();

    std::string v1;
    lru.get("a", v1);
    std::cout<<"val of a:"<<v1<<std::endl;
    lru.display();

    std::string v2;
    lru.get("b", v2);
    std::cout<<"val of b:"<<v2<<std::endl;
    lru.display();
}

int main(){
    test_lru();
    return 0;
}
