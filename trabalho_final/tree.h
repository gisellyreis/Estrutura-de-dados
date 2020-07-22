#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a > b) ? a : b)

typedef struct node nodet;
typedef struct interval intert;

struct interval {
    int a;
    int b;
};

struct node {
    intert *i;
    int max;
    int height;
    nodet *left, *right;
};

intert *newInterval(void);
nodet *newNode(void);
int tree_height(nodet *root);
nodet *get_max(nodet *root);
nodet *rotateR(nodet *root);
nodet *rotateL(nodet *root);
nodet *rebalance(nodet *root);
nodet *node_insert(intert *x, nodet *root);
nodet *node_delete(intert *x, nodet *root);
intert *search(intert *x, nodet *root);
bool do_overlap(intert *x, intert *y);
intert *overlap(intert *x, nodet *root);
void inorder(nodet *root);
void display(nodet *root);