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
    RingQueue * rate; //限流
};


void* produce(void *arg){
    worker * w = (worker*)arg;
    
    for(int i=0; i<JOBS; ++i) {
       Entry * r = w->rate->pop();

       Entry * e= new Entry();
       sprintf(e->msg, "[%s.%d] => job:%d", w->name, w->id, i);
       w->rb->push(e);

       w->rate->push(r);

       //printf(">>>> %s\n", buff);
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
    RingQueue *rate = new RingQueue();
    Entry *es = new Entry[100];
    for (int i=0; i<100; ++i){
        rate->push(&es[i]);
    }

    pthread_t cpid[NC];
    pthread_t ppid[NP];
    worker cw[NC];
    worker pw[NP];
	
	for (int i = 0; i < NP; ++i) {
        sprintf(pw[i].name,  "P_%d", i);
        pw[i].id = i;
        pw[i].rb = rb;
        pw[i].rate = rate;
		pthread_create(&ppid[i], NULL, produce, &pw[i]);
    }

	for (int i = 0; i < NC; ++i) {
        sprintf(cw[i].name,  "c_%d", i);
        cw[i].id = i;
        cw[i].rb = rb;
		pthread_create(&cpid[i], NULL, consume, &cw[i]);
	}

	for (int i = 0; i < NP; ++i) {
		pthread_join(ppid[i], NULL);
	}
	for (int i = 0; i < NC; ++i) {
		pthread_join(cpid[i], NULL);
	}

    return 0;
}
