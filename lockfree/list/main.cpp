#include <string.h>
#include <pthread.h>
#include "lf_queue.h"

const int NP = 30;
const int NC = 20;
const int JOBS = 10000;


struct worker{
    char name[16];
    lf_queue *list;
};

void* produce(void *arg){
    worker * w = (worker*)arg;
    for(int i=0; i<JOBS; ){
        char data[64];
        sprintf(data, "[%s] job:%d", w->name, i);
        w->list->push(data);
        ++i;
    }
}

void* consume(void *arg){
    worker * r = (worker*)arg;
    for(int i=0; i<JOBS*NP/NC; ){
        char *data = r->list->pop();
        if(data==nullptr){
            continue;
        }
        ++i;
        fprintf(stderr, "[%s] consume msg:%s\n", r->name, data);
    }
}

int main(int argc, char *argv[]){
    lf_queue *queue = new lf_queue();

    pthread_t rid[NC];
    pthread_t wid[NP];
    worker r[NC];
    worker w[NP];
    
    for(int i = 0; i < NP; ++i){
        sprintf(w[i].name,  "producer.%d", i);
        w[i].list = queue;
        pthread_create(&wid[i], nullptr, produce, &w[i]);
    }
    for(int j = 0; j < NC; ++j){
        sprintf(r[j].name,  "consumer.%d", j);
        r[j].list = queue;
        pthread_create(&rid[j], nullptr, consume, &r[j]);
    }

    for(int i = 0; i < NP; ++i){
        pthread_join(wid[i], nullptr);
    }
    for(int j = 0; j < NC; ++j){
        pthread_join(rid[j], nullptr);
    }

    delete queue;
    return 0;
}
