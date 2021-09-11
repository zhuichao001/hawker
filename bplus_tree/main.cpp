#include "bpnode.h"
#include "bptree.h"
#include <stdio.h>
#include <random>
#include <vector>

int randint(){
    static std::default_random_engine generator;
    static std::uniform_int_distribution<int> distribution(1, 99999999);
    static auto dice = std::bind(distribution, generator);
    return dice();
}

bptree * gentree(){
    bptree *tree = new bptree;
    tree->put("a", "123");
    tree->put("b", "456");
    tree->put("c", "789");
    tree->put("d", "888");
    tree->put("e", "999");
    tree->put("f", "1000");
    return tree;
}

int test1(){
    bptree *tree = gentree();
    printf("\nWHEN put a,b,c,d,e,f\n");
    tree->print();

    std::string val;
    tree->get("a", val);
    printf("val:%s !!!!!! \n", val.c_str());

    tree->del("a");
    printf("\nWHEN del a\n");
    tree->print();

    tree->put("a", "234");
    printf("\nWHEN put a\n");
    tree->print();

    return 0;
}

int test1_1(){
    bptree *tree = new bptree;
    tree->put("a", "123");
    tree->put("b", "456");
    tree->put("c", "789");
    tree->put("d", "888");
    printf("\nWHEN put a,b,c,d\n");
    tree->print();

    std::string val;
    tree->get("d", val);
    printf("val:%s !!!!!! \n", val.c_str());

    tree->del("d");
    printf("\nWHEN del d\n");
    tree->print();

    tree->del("c");
    printf("\nWHEN del c\n");
    tree->print();
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

int test2_1(){
    bptree tree;
    const int N = 1000;
    std::string keys[N];
    for(int i=0; i<N; ++i){
        std::string key("_key_."), val("_val_.");
        key += std::to_string(randint());
        val += std::to_string(randint());
        tree.put(key, val);
        keys[i] = key;
    }

    printf("\n");
    tree.print();

    for(int i=0; i<N; ++i){
        printf("i=%d, to del:%s\n", i, keys[i].c_str());
        tree.del(keys[i]);
        printf("\nWHEN del %s\n", keys[i].c_str());
        tree.print();
    }

    printf("FINISH \n");
    return 0;
}

int test2_2(){
    bptree tree;
    std::string keys[] = { "u", "z", "f",  "j", "c", "h", "l","a", "n", "x", "w", "c", "m", "b","i", };//"w", "c","a","m","g","b","i","d"};
    //std::string keys[] = {"z",  "h", "l", "n", "u", "x", "f", "w", "c", "a", "m", "g", "b", "i", "d"};
    //std::string keys[] = {"z",  "h", "l", "n", "u", "x", "f", "w", "c", "a", "m", "g"};
    const int N = sizeof(keys)/sizeof(keys[0]);
    for(int i=0; i<N; ++i){
        tree.put(keys[i], keys[i]);
    }

    printf("\n");
    tree.print();

    for(int i=0; i<N; ++i){
        printf("i=%d, to del:%s\n", i, keys[i].c_str());
        tree.del(keys[i]);
        printf("\nWHEN del %s\n", keys[i].c_str());
        tree.print();
    }

    printf("FINISH \n");
    return 0;
}

int test3(){
    bptree *tree = gentree();
    std::vector<kvpair> vec;
    tree->scan("a", "g", vec);
    for(int i=0; i<int(vec.size()); ++i){
        printf("%s:%s ", vec[i].first.c_str(), vec[i].second.c_str());
    }
    printf("FINISH scan\n");
    return 0;
}

int main(){
    test2_1();
    return 0;
}
