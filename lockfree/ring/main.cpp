#include <string>
#include <string.h>
#include <pthread.h>
#include "ringbuff.h"

const int NP = 30;
const int NC = 20;
const int JOBS = 10000;


struct worker{
    char name[16];
    RingBuff<std::string> *ring;
};

void* produce(void *arg){
    worker * w = (worker*)arg;
    char data[64];
    for(int i=0; i<JOBS; ){
        sprintf(data, "[%s] job:%d", w->name, i);
        if( !w->ring->push(data) ){
            continue;
        }
        ++i;
    }
    return nullptr;
}

void* consume(void *arg){
    worker * r = (worker*)arg;
    std::string out;
    for(int i=0; i<JOBS*NP/NC; ){
        if(!r->ring->pop(&out)){
            continue;
        }
        ++i;
        fprintf(stderr, "[%s] consume msg:%s\n", r->name, out.c_str());
    }
    return nullptr;
}

int main(int argc, char *argv[]){
    RingBuff<std::string> *ring = new RingBuff<std::string>(1000);

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
