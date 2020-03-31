#include <stdio.h>
#include <stdlib.h>

typedef struct cell cell_t;
typedef int element_t;

struct cell {
    element_t element;
    cell_t *next;
};

// Functions:

cell_t *newCell(void);
void insert(element_t e, cell_t *l);
cell_t *search(element_t e, cell_t *l);
element_t delete(element_t e, cell_t *l);

int main(void) {

    cell_t *list = newCell();
    cell_t *list2 = newCell();
    if(list) 
        printf("List successfully created\n");
    else
        printf("Error creating list\n");

    /*
         Tests:

    insert(5, list);
    insert(1, list);
    insert(8, list);

    cell_t *p = list;
  
    printf("%i %i %i", p->next->element, p->next->next->element, p->next->next->next->element);
    
    */

    return 0;
}


cell_t *newCell(void) {
    cell_t *p = (cell_t*)malloc(sizeof(cell_t));
    if(p) {
        p->element = -1;
        p->next = NULL;
        return p;
    }
    else {
        return NULL;
    }
}

void insert(element_t e, cell_t *l) {
    if(l) {
        cell_t *p = newCell();
        if(p) {
            p->next = l->next;
            l->next = p;
            p->element = e;
        }
    }
}

cell_t *search(element_t e, cell_t *l) {
    while(l &&  l->next->element != e) {
        l = l->next;
    }
    if(l->next)
        return (l);
    else 
        return NULL;
}

element_t delete(element_t e, cell_t *l) {
    cell_t *p = search(e, l);
    if(p) {
        cell_t *q = p->next;
        p->next = q->next;
        element_t x = q->element;
        free(q);
        return x;
    }
    else 
        return -1;
}