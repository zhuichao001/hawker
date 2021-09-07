#include "bptree.h"
#include <stdio.h>
#include <random>

int randint(){
    static std::default_random_engine generator;
    static std::uniform_int_distribution<int> distribution(1, 99999999);
    auto dice = std::bind(distribution, generator);
    return dice();
}

int test1(){
    bptree tree;
    tree.put("a", "123");
    tree.put("b", "456");
    tree.put("c", "789");
    tree.put("d", "888");
    tree.put("e", "999");
    tree.put("f", "1000");
    printf("\nWHEN put a,b,c,d,e,f\n");
    tree.print();

    std::string val;
    tree.get("a", val);
    printf("val:%s !!!!!! \n", val.c_str());

    tree.del("a");
    printf("\nWHEN del a\n");
    tree.print();

    tree.put("a", "234");
    printf("\nWHEN put a\n");
    tree.print();

    return 0;
}

int test2(){
    bptree tree;
    int total=0, suc =0;
    for(int i=0; i<2000000; ++i){
        std::string key("_key_."), val("_val_.");
        key += std::to_string(randint());
        val += std::to_string(randint());
        tree.put(key, val);

        total += 1;
        
        std::string real;
        tree.get(key, real);
        if(real==val){
            suc+=1;
        }
    }
    printf("FINISH total:%d suc:%d \n", total, suc);
    return 0;
}

int main(){
    test1();
    return 0;
}
