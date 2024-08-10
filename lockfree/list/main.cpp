#include <string>
#include <pthread.h>
#include "list.h"

const int NP = 30;
const int NC = 20;
const int JOBS = 10000;


struct worker{
    char name[16];
    List<std::string*> *list;
};

void* produce(void *arg){
    worker * w = (worker*)arg;
    for(int i=0; i<JOBS; ){
        char data[64];
        sprintf(data, "[%s] job:%d", w->name, i);
        std::string *e = new std::string(data);
        w->list->push(e);
        ++i;
    }
    return nullptr;
}

void* consume(void *arg){
    worker * r = (worker*)arg;
    for(int i=0; i<JOBS*NP/NC; ){
        std::string *data;
        bool ok = r->list->pop(&data);
        if(!ok){
            continue;
        }
        ++i;
        fprintf(stderr, "[%s] consume msg:%s\n", r->name, data->c_str());
        delete data;
    }
    return nullptr;
}

int main(int argc, char *argv[]){
    List<std::string*> *list = new List<std::string*>;

    pthread_t rid[NC];
    pthread_t wid[NP];
    worker r[NC];
    worker w[NP];
    
    for(int i = 0; i < NP; ++i){
        sprintf(w[i].name,  "producer.%d", i);
        w[i].list = list;
        pthread_create(&wid[i], nullptr, produce, &w[i]);
    }
    for(int j = 0; j < NC; ++j){
        sprintf(r[j].name,  "consumer.%d", j);
        r[j].list = list;
        pthread_create(&rid[j], nullptr, consume, &r[j]);
    }

    for(int i = 0; i < NP; ++i){
        pthread_join(wid[i], nullptr);
    }
    for(int j = 0; j < NC; ++j){
        pthread_join(rid[j], nullptr);
    }

    delete list;
    return 0;
}
