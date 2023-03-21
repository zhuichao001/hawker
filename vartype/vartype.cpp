#include <stdio.h>
#include <malloc.h>
#include <string.h>

class vartype{
    enum class Type{
        UNKNOWN =0,
        BOOL =1,
        INT =2,
        DOUBLE =3,
        STR =4,
    };
    void *data;
    int len;
    Type type;

    void check_memlen(int length){
        if(length>len){
            if(data){
                free(data);
                data = nullptr;
            }
        }
        len = length;
        data = malloc(len);
    }
    friend void print(const vartype &v);
public:
    vartype():
        data(nullptr),
        len(0),
        type(Type::UNKNOWN){
        check_memlen(8);
    }

    vartype &operator=(bool v){
        type = Type::BOOL;
        *(static_cast<bool*>(data)) = v;
        return *this;
    }
    
    vartype &operator=(int v){
        memset(data, 0, len);
        type = Type::INT;
        memcpy(data, &v, sizeof(int));
        return *this;
    }

    vartype &operator=(double v){
        memset(data, 0, len);
        type = Type::DOUBLE;
        memcpy(data, &v, sizeof(double));
        return *this;
    }

    vartype &operator=(const char *v){
        memset(data, 0, len);
        size_t vlen = strlen(v)+1;
        check_memlen(vlen);
        memcpy(data,v,vlen);
        type = Type::STR;
        return *this;
    }
};

void print(const vartype &v){
    switch(v.type){
        case vartype::Type::BOOL:
            fprintf(stderr, "%s\n", v.type==vartype::Type::BOOL ? "true" : "false");
            break;
        case vartype::Type::INT:
            fprintf(stderr, "%d\n", *static_cast<int*>(v.data));
            break;
        case vartype::Type::DOUBLE:
            fprintf(stderr, "%f\n", *static_cast<double*>(v.data));
            break;
        case vartype::Type::STR:
            fprintf(stderr, "%s\n", static_cast<const char*>(v.data));
            break;
    }
}

void test1(){
    vartype v;
    v = true;
    print(v);
    v = 3.14159;
    print(v);
    v = 9;
    print(v);
    v = "hello,world";
    print(v);
}

int main(){
    test1();
    return 0;
}
