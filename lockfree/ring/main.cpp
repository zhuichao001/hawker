#include <string>
#include <string.h>
#include <pthread.h>
#include "ring.h"

const int NP = 30;
const int NC = 20;
const int JOBS = 10000;


struct worker{
    char name[16];
    Ring<std::string> *ring;
};

void* produce(void *arg){
    worker * w = (worker*)arg;
    for(int i=0; i<JOBS; ){
        char data[64];
        sprintf(data, "[%s] job:%d", w->name, i);
        if( !w->ring->push(data) ){
            continue;
        }
        ++i;
    }
}

void* consume(void *arg){
    worker * r = (worker*)arg;
    for(int i=0; i<JOBS*NP/NC; ){
        std::string out;
        if(!r->ring->pop(&out)){
            continue;
        }
        ++i;
        fprintf(stderr, "[%s] consume msg:%s\n", r->name, out.c_str());
    }
}

int main(int argc, char *argv[]){
    Ring<std::string> *ring = new Ring<std::string>(100);

    pthread_t rid[NC];
    pthread_t wid[NP];
    worker r[NC];
    worker w[NP];
    
    for(int i = 0; i < NP; ++i){
        sprintf(w[i].name,  "producer.%d", i);
        w[i].ring = ring;
        pthread_create(&wid[i], nullptr, produce, &w[i]);
    }
    for(int j = 0; j < NC; ++j){
        sprintf(r[j].name,  "consumer.%d", j);
        r[j].ring = ring;
        pthread_create(&rid[j], nullptr, consume, &r[j]);
    }

    for(int i = 0; i < NP; ++i){
        pthread_join(wid[i], nullptr);
    }
    for(int j = 0; j < NC; ++j){
        pthread_join(rid[j], nullptr);
    }

    delete ring;
    return 0;
}
