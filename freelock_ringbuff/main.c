#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "ringbuff.h"


const int NP = 10;
const int NC = 10;
const int JOBS = 10000;

struct worker{
    char name[16];
    int id;
    RingQueue * rb;
};

void* produce(void *arg){
    worker * w = (worker*)arg;
    
    char buff[MSG_LEN];
    
    for(int i=0; i<JOBS; ++i) {
       sprintf(buff, "worker[name:%s, id:%d], job:%d\n", w->name, w->id, i);
       w->rb->push(buff, MSG_LEN);
    }
}

void* consume(void *arg){
    worker * w = (worker*)arg;

    char buff[MSG_LEN];
    int size;
    
    for(int i=0; i<JOBS; ++i) {
       w->rb->pop(buff, size);
       printf("%s:%d ||| msg:%s", w->name, w->id, buff);
    }
}

int main(int argc, char *argv[]) {
    RingQueue *rb = new RingQueue(8);

    pthread_t cpid[NC];
    pthread_t ppid[NP];
    worker cw[NC];
    worker pw[NP];
	
	for (int i = 0; i < NP; ++i) {
        sprintf(pw[i].name,  "P_%c", char('A'+i));
        pw[i].id = i;
        pw[i].rb = rb;
		pthread_create(&ppid[i], NULL, produce, &pw[i]);
    }

	for (int i = 0; i < NC; ++i) {
        sprintf(cw[i].name,  "c_%c", char('c'+i));
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
