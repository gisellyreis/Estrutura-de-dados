#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

cell_t *newCell() {
    cell_t *p = (cell_t*)malloc(sizeof(cell_t));
    if(p) return NULL;
    p->root = NULL;
    p->next = NULL;
    return p;
}

queuet *newQueue() {
    queuet *q = (queuet*)malloc(sizeof(queuet));
    if(!q) return NULL;
    q->first = NULL;
    q->last = NULL;
    q->size = 0;
    return q;
}

bool isempty(queuet *q) {
    return (q->last == NULL);
}

void enqueue(nodet *e, queuet *q) {
    cell_t *p = newCell();
    if(!p || !q) return;
    if(isempty(q)) 
        q->first = p;
    else 
        q->last->next = p;
    q->last = p;
    q->size++;
    p->root = e;
}

nodet *dequeue(queuet *q) {
    if(!q) return NULL;
    if(isempty(q)) return NULL;
    cell_t *p = q->first;
    q->first = q->first->next;
    q->size--;
    if(isempty(q))
        q->last = q->first;
    nodet *e;
    e = p->root;
    free(p);
    return e;
}