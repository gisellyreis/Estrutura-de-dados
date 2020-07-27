#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

typedef struct cell cell_t;
typedef struct queue queuet;
typedef enum {false, true}bool;

struct cell {
    nodet *root;
    cell_t *next;
};

struct queue {
    cell_t *first, *last;
    unsigned int size;
};

cell_t *newCell(void);
queuet *newQueue(void);
bool isempty(queuet *q);
void enqueue(nodet *e, queuet *q);
nodet *dequeue(queuet *q);