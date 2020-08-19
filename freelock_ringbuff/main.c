#include <string.h>
#include <pthread.h>
#include "ringbuff.h"

const int NP = 30;
const int NC = 20;
const int JOBS = 10000;

struct worker{
    char name[16];
    int id;
    RingQueue * rb;
};


void* produce(void *arg){
    worker * w = (worker*)arg;
    
    for(int i=0; i<JOBS; ++i) {
        Entry * e= new Entry();
        sprintf(e->msg, "[%s.%d] => job:%d", w->name, w->id, i);
        w->rb->push(e);
    }
}

void* consume(void *arg){
    worker * w = (worker*)arg;

    for(int i=0; i<JOBS*NP/NC; ++i) {
        Entry *e = w->rb->pop();
        printf("msg:%s ||| %s:%d \n", e->msg, w->name, w->id);
        delete e;
    }
}

int main(int argc, char *argv[]) {
    RingQueue *rb = new RingQueue();

    pthread_t rid[NC];
    pthread_t wid[NP];
    worker r[NC];
    worker w[NP];
    
    for (int i = 0; i < NP; ++i) {
        sprintf(w[i].name,  "P_%d", i);
        w[i].id = i;
        w[i].rb = rb;
        pthread_create(&wid[i], NULL, produce, &w[i]);
    }

    for (int i = 0; i < NC; ++i) {
        sprintf(r[i].name,  "c_%d", i);
        r[i].id = i;
        r[i].rb = rb;
        pthread_create(&rid[i], NULL, consume, &r[i]);
    }

    for (int i = 0; i < NP; ++i) {
        pthread_join(wid[i], NULL);
    }

    for (int i = 0; i < NC; ++i) {
        pthread_join(rid[i], NULL);
    }

    return 0;
}
