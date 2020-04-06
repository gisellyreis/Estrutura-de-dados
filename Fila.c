#include <stdio.h>
#include <stdlib.h>

typedef struct cell cell_t;
typedef struct queue queue_t;
typedef int element_t;
typedef enum {false, true} bool;

struct cell {
    element_t element;
    cell_t *next;
};

struct queue {
    cell_t *first, *last;
    unsigned int size;
};

// Functions: 

cell_t *newCell(void);
queue_t *newQueue(void);
bool isempty(queue_t *q);
void enqueue(element_t e, queue_t *q);
element_t dequeue(queue_t *q);

int main(void) {
    queue_t *queue = newQueue();
    element_t x;

    printf("X = ");
    while(scanf("%d", &x) && x!= -1) {
        enqueue(x, queue);
        printf("X = ");
    }

    while(queue->size > 0) {
        printf("%d ", dequeue(queue));
    }

    return 0;
}

cell_t *newCell(void) {
    cell_t *p = (cell_t*)malloc(sizeof(cell_t));
    if(p) {
        p->element = -1;
        p->next = NULL;
        return p;
    } else 
        return NULL;
}

queue_t *newQueue(void) {
    queue_t *q = (queue_t*)malloc(sizeof(queue_t));
    if(q) {
        q->first = NULL;
        q->last = NULL;
        q->size = 0;
        return q;
    } else {
        return NULL;
    }
}

bool isempty(queue_t *q) {
    return (q->last == NULL);
}

void enqueue(element_t e, queue_t *q) {
    cell_t *p = newCell();
    if(!p) return;
    if(isempty(q)) 
        q->first = p;
    else 
        q->last->next = p;
    q->last = p;
    q->size++;
    p->element = e;
}

element_t dequeue(queue_t *q) {
    if(isempty(q)) return -1;
    cell_t *p = q->first;
    q->first = q->first->next;
    if(q->last == p)
        q->last = NULL;
    element_t e = p->element;
    q->size--;
    free(p);
    return e;
}