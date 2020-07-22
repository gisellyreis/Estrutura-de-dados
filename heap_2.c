#include <stdio.h>
#include <stdlib.h>

typedef int *heapt;
typedef struct pqueue pqueuet;

#define parent(i) (i-1)/2
#define left(i) 2*i + 1
#define right(i) 2*i + 2

struct pqueue {
    int size, maxsize;
    heapt priority;
};

void newHeap(pqueuet *h, int n);
void swap(heapt h, int i, int j);
void insert(heapt h, int x, int pn);
void delete(heapt h, int *pn);
int maxChild(heapt h, int i, int n);
void bubbleUp(heapt h, int i);
void bubbleDown(heapt h, int i, int n);
void heapfy(heapt h, int n);
void heapsort(int v[], int n);

void newHeap(pqueuet *h, int n) {
    h->priority = malloc(n*(sizeof(int)));
    h->maxsize = n;
    h->size = 0;
}

void swap(heapt h, int i, int j) {
    int k = h[i];
    h[i] = h[j];
    h[j] = k;
}

void insert(heapt h, int x, int pn) {
    h[pn] = x;
    bubbleUp(h, pn);
    (pn)++;
}

void delete(heapt h, int *pn) {
    if(*pn > 0) {
        swap(h, 0, (*pn)-1);
        (*pn)--;
        bubbleDown(h, 0, (*pn));
    }
}

int maxChild(heapt h, int i, int n) {
    int imax = left(i);
    if(imax < n-1 && h[right(i)] > h[imax]) imax = right(i);
    return imax;
}

void bubbleUp(heapt h, int i) {
    while(i > 0 && h[i] > h[parent(i)]) {
        swap(h, parent(i), i);
        i = parent(i);
    }
}

void bubbleDown(heapt h, int i, int n) {
    int imax = maxChild(h, i, n);
    while((imax < n) && (h[i] < h[imax])) {
        swap(h, i, imax);
        i = imax;
        imax = maxChild(h, i, n);
    }
}

void heapfy(heapt h, int n) {
    for(int i  = n/2; i>=0; i--) {
        bubbleDown(h, i, n);
    }
}

// Ordanação crescente
void heapsort(int v[], int n) {
    heapfy(v, n);
    while(n)
        delete(v, &n);
}

int main(void) {
    pqueuet *heap;

    newHeap(heap, 5);
    insert(heap->priority, 10, 0);
    insert(heap->priority, 5, 1);
    insert(heap->priority, 30, 2);
    insert(heap->priority, 2, 3);
    insert(heap->priority, 80, 4);

    //heapsort(heap->priority, 5);

    for(int i=0; i< 5; i++) {
        printf("%d ", heap->priority[i]);
    }

}