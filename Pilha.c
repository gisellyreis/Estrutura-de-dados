#include <stdio.h>
#include <stdlib.h>

typedef struct cell cell_t;
typedef struct stk stk_t;
typedef int element_t;
typedef enum{false, true} bool;

struct cell {
    element_t element;
    cell_t *next;
};

struct stk {
    cell_t *top;
    unsigned int size;
};

// Functions: 

cell_t *newCell(void);
stk_t *newStk(void);
bool isempty(stk_t *s);
void push(element_t e, stk_t *s);
element_t pop(stk_t *s);
element_t seeTop(stk_t *s);

int main(void) {
    stk_t *pilha = newStk();

    push(2, pilha);
    push(5, pilha);
    push(7, pilha);

    for(int i=0, t=pilha->size; i< t; i++) {
        printf("Elemento no topo: %i\n", seeTop(pilha));
        printf("Pop: %i\n", pop(pilha));
    }

    return 0;
}

cell_t *newCell(void) {
    cell_t *p = malloc(sizeof(cell_t));
    if(!p) return NULL;
    p->element = -1;
    p->next = NULL;
    return p;
}

stk_t *newStk(void) {
    stk_t *s = malloc(sizeof(stk_t));
    if(!s) return NULL;
    s->top = NULL;
    s->size = 0;
    return s;
}

bool isempty(stk_t *s) {
    return (s->top == NULL);
}

void push(element_t e, stk_t *s) {
    cell_t *p = newCell();
    p->element = e;
    p->next = s->top;
    s->top = p;
    s->size++;
}

element_t pop(stk_t *s) {
    if(s == NULL || s->top == NULL)
        return -1;
    element_t e = s->top->element;
    s->top = s->top->next;
    s->size--;
    return e;
}

element_t seeTop(stk_t *s) {
    if(!s) return -1;
    return (s->top->element);
}