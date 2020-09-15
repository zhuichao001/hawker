#include "hash_str.h"
#include "hash_int.h"
#include "hash_obj.h"
#include "hash_func.h"
#include <stdio.h>
#include <string>

using namespace std;

void test_str(){
    int code=0;

    code = hash_str("a", 1);
    printf("hash a:%d\n", code);

    code = hash_str("b", 1);
    printf("hash b:%d\n", code);
}

void test_int(){
    int code=0;

    code = hash_int(0);
    printf("hash 0:%d\n", code);

    code = hash_int(1);
    printf("hash 1:%d\n", code);
}

void test_obj(){
    class A: public HashBase{
      const char *name;
      public:
        A(const char *a):name(a){}
        virtual string ToStr(){
           return string(name); 
        }
    };

    int code=0;

    A a("he"), b("she");
    code = hash_obj((HashBase*)&a);
    printf("hash a:%d\n", code);

    code = hash_obj((HashBase*)&b);
    printf("hash b:%d\n", code);
}

void test_func(){
    HashFunc hash_str;
    HashFunc hash_str2(63679);
    int code=0;

    code = hash_str("a", 1);
    printf("hash a:%d\n", code);

    code = hash_str2("a", 1);
    printf("hash2 a:%d\n", code);
}

int main(){
    test_str();
    test_int();
    test_obj();
    test_func();
}
