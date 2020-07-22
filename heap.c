#include <stdio.h>
#include <stdlib.h>

typedef struct heap heapt;
typedef enum { false, true }bool;
#define parent(i) (i-1) / 2
#define right(i) 2*i + 2
#define left(i) 2*i + 1

struct heap {
    int maxsize, h_size;
    int *heap;
};

heapt *newHeap(int n);
void insert(heapt *h, int k);
int delete(heapt *h);
void upHeap(heapt *h, int i);
void downHeap(heapt *h, int i);

heapt *newHeap(int n) {
    heapt *h = malloc(sizeof(heapt));
    if(!h) return NULL;
    h->heap= malloc(sizeof(int)*n);
    h->maxsize = n;
    h->h_size = 0;
    return h;
}

void insert(heapt *h, int k) {
    if(h->heap == NULL || h->h_size == h->maxsize) return;
    h->heap[h->h_size++] = k;
    int last = h->h_size -1;
    upHeap(h, last);
    return;
}

int delete(heapt *h) {
    if(h->h_size < 1) return -1;
    if(h->h_size == 1) {
        h->h_size--;
        return h->heap[0];
    }
    int top = h->heap[0];
    int last = h->heap[h->h_size-1];
    h->heap[0] = last;
    h->h_size--;
    downHeap(h, 0);
    return top;
}

void upHeap(heapt *h, int i) {
    int last = h->heap[i];
    int pai = h->heap[parent(i)];
    if(last > pai) {
        h->heap[i] = pai;
        h->heap[parent(i)] = last;
        upHeap(h, parent(i));
    }
}

void downHeap(heapt *h, int i) {
    if(left(i) >= h->h_size && right(i) >= h->h_size) return;
    int son1 = h->heap[left(i)];
    int son2 = -1;
    if(right(i) < h->h_size) {
        son2 = h->heap[right(i)];
        int imax = ((son1 > son2) ? left(i) : right(i));
        if(h->heap[i] < h->heap[imax]) {
            int aux = h->heap[i];
            h->heap[i] = h->heap[imax];
            h->heap[imax] = aux;
            downHeap(h, imax);
        }
    }
    return;
}

void showHeap(heapt *h) {
    int size = h->h_size;

    for(int i =0; i< size; i++) {
        printf("%d ", h->heap[i]);
    }
}

int main(void) {
    // Essa é a versão do Heap em que só o primeiro elemento é
    // obrigatóriamente o maior, mas o restante do vetor não está ordenado
    heapt *pq = newHeap(5);
    insert(pq, 10);
    insert(pq, 5);
    insert(pq, 50);
    insert(pq, 1);

    showHeap(pq);
}