#include <stdio.h>
#include <stdlib.h>

typedef struct stk stk_t;
typedef int element_t;
typedef enum {false, true} bool;

struct stk {
    unsigned int top, maxsize;
    element_t *svector;
};

// Functions: 

stk_t *newStk(unsigned int n);
bool isempty(stk_t *s);
bool isfull(stk_t *s);
void push(element_t e, stk_t *s);
element_t pop(stk_t *s);
void deleteStk(stk_t *s);

int main(void) {

    stk_t *pilha = newStk(5);
    push(2, pilha);
    push(4, pilha);
    push(6, pilha);
    push(8, pilha);
    push(1, pilha);

    for(int i=0, t = pilha->maxsize; i< t; i++) {
        printf("Top: %i\n", pop(pilha));
    }

    return 0;
}

stk_t *newStk(unsigned int n) {
    stk_t *s = malloc(sizeof(stk_t));
    if(!s) return NULL;
    s->svector = malloc(n*sizeof(element_t));
    if(!(s->svector)) return NULL;
    s->top = 0;
    s->maxsize = n;
    return s;
}

bool isempty(stk_t *s) {
    return (s->top == 0);
}

bool isfull(stk_t *s) {
    return (s->top == s->maxsize);
}

void push(element_t e, stk_t *s) {
    if(isfull(s)) return;
    s->svector[s->top++] = e;
}

element_t pop(stk_t *s) {
    if(isempty(s)) return -1;
    return (s->svector[--(s->top)]);
}

void deleteStk(stk_t *s) {
    free(s->svector);
    free(s);
}