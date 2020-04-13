#include <stdio.h>
#include <stdlib.h>

typedef struct queue queue_t;
typedef int element_t;
typedef enum {false, true} bool;

struct queue {
    unsigned int first, last, maxsize;
    element_t *qvector;
};

// Functions: 

queue_t *newQueue(unsigned int n);
bool isfull(queue_t *q);
bool isempty(queue_t *q);
bool enqueue(element_t e, queue_t *q);
element_t dequeue(queue_t *q);

int main(void) {
    queue_t *fila = newQueue(5);
    bool teste;
    int x;
    for(int i=0; i< 5; i++) {
        printf("X = ");
        scanf("%i", &x);
        teste = enqueue(x, fila);
    }
    for(int i=0; i< 5; i++) {
        printf("%i ", dequeue(fila));
    }
    printf("\n");

    return 0;
}

queue_t *newQueue(unsigned int n) {
    queue_t *q = malloc(sizeof(queue_t));
    if(!q)
        return NULL;
    q->qvector = malloc(n*sizeof(element_t));
    if(!q->qvector)
        return NULL;
    q->first = 0;
    q->last = 0;
    q->maxsize = n;
    return q;
}

bool isfull(queue_t *q) {
    return ((q->last+1)%(q->maxsize) == q->first);
}

bool isempty(queue_t *q) {
    return (q->first == q->last);
}

bool enqueue(element_t e, queue_t *q){
    if(isfull(q))
        return false;
    q->qvector[q->last++] = e;
    if(q->last == q->maxsize)
        q->last = 0;
    return true;
}

element_t dequeue(queue_t *q) {
    if(isempty(q))
        return -1;
    unsigned int f = q->first++;
    if(q->first == q->maxsize)
        q->first = 0;
    return (q->qvector[f]);
}