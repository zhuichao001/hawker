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

    pthread_t cpid[NC];
    pthread_t ppid[NP];
    worker cw[NC];
    worker pw[NP];
	
	for (int i = 0; i < NP; ++i) {
        sprintf(pw[i].name,  "P_%d", i);
        pw[i].id = i;
        pw[i].rb = rb;
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
