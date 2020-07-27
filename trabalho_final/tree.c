#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "queue.c"

#define MAX(a,b) ((a > b) ? a : b)

intert *newInterval() {
    intert *i = (intert*) malloc(sizeof(intert));
    if(!i) return NULL;
    i->a = 0;
    i->b = 0;
    return i;
}

nodet *newNode(void) {
    nodet *root = (nodet*) malloc(sizeof(nodet));
    if(!root) return NULL;
    root->i = NULL;
    root->max = -2147483647;
    root->height = 0;
    root->left = NULL;
    root->right = NULL;
    return root;
}

int tree_height(nodet *root) {
    if(root == NULL) return -1;
    else return root->height;
}

nodet *get_max(nodet *root) {
    if(root)
        while(root->right) root = root->right;
    return root;
}

nodet *rotateR(nodet *root) {
    nodet *y = root->left;
    root->left = y->right;
    y->right = root;
    root->height = MAX(tree_height(root->left), tree_height(root->right)) + 1;
    y->height = MAX(tree_height(root), tree_height(y->left)) + 1;
    return y;
}

nodet *rotateL(nodet *root) {
    nodet *y = root->right;
    root->right = y->left;
    y->left = root;
    root->height = MAX(tree_height(root->right), tree_height(root->left)) + 1;
    y->height = MAX(tree_height(root), tree_height(root->right)) + 1;
    return y;
}

nodet *rebalance(nodet *root) {
    int lh = tree_height(root->left);
    int rh = tree_height(root->right);
    int f = lh - rh;
    root->height = MAX(lh, rh) + 1;

    if(f == 2) {
        if(tree_height(root->left->right) > tree_height(root->right->left))
            root->left = rotateL(root->left);
        root = rotateR(root);
    }
    else if(f == -2) {
        if(tree_height(root->right->left) > tree_height(root->right->right))
            root->right = rotateR(root->right);
        root = rotateL(root);
    }
    if(root->right != NULL && root->left != NULL)
		root->max = MAX(MAX(root->right->max,root->left->max), root->max);
	else if(root->left == NULL)
		root->max = MAX(root->right->max, root->max);
	else
		root->max = MAX(root->left->max, root->max);
    return root;
}

nodet *node_insert(intert *x, nodet *root) {
    if(root == NULL) {
        root = newNode();
        root->i = x;
        root->max = x->b;
        return root;
    }
    else if(x->a < root->i->a)
        root->left = node_insert(x, root->left);
    else if(x->a > root->i->a)
        root->right = node_insert(x, root->right);
    if(root->max < x->b) 
        root->max = x->b;
    
    return rebalance(root);
}

nodet *node_delete(intert *x, nodet *root) {
    nodet *p;
    if(!root) return root;
    if(x->a < root->i->a) 
        root->left = node_delete(x, root->left);
    else if(x->a > root->i->a)
        root->right = node_delete(x, root->right);
    else {
        if(root->i->b != x->b){
            root->left = node_delete(x, root->left);
            root->right = node_delete(x, root->right);
        }
        else {
            if(root->left == NULL) {
                p = root;
                root = root->right;
                free(p->i);
                free(p);
            }
            else if(root->right == NULL) {
                p = root;
                root = root->left;
                free(p->i);
                free(p);
            }
            else {
                p = get_max(root->left);
                root->i = p->i;
                root->left = node_delete(p->i, root->left);
            }
        }
    }
    if(root){
        root = rebalance(root);
    }
    return root;
}

intert *search(intert *x, nodet *root) {
    if(!root) return NULL;
    if(root->i->a == x->a && root->i->b == x->b) 
        return root->i;
    else if(x->a < root->i->a)
        return search(x, root->left);
    else return search(x, root->right);
}

intert *overlap(intert *x, nodet *root) {
    if(!root) return NULL;
    if(x->a <= root->i->b && root->i->b <= x->b)
        printf("[%03d,%03d] ", root->i->a, root->i->b);
    if(root->left!=NULL && root->left->max >= x->a)
        return overlap(x, root->left);
    else 
        return overlap(x, root->right);
}

void inorder(nodet *root) {
    if(root == NULL) return;
    inorder(root->left);
    printf("[%03d,%03d]\n", root->i->a, root->i->b);
    inorder(root->right);
}

void display(nodet *root) {
    if(!root) return;
    unsigned int i, j, e, k, line = 1, height = root->height; 
    nodet *flag = root;
    char space[9] = "        ";
    queuet *myQueue = newQueue();
    e = pow(2, root->height) -1;

    for(i =0; i< e; i++) printf("%s", space);

    printf("[%03d,%03d]\n", root->i->a, root->i->b);

    if(root->left) enqueue(root->left, myQueue);
    else enqueue(root, myQueue);

    if(root->right) enqueue(root->right, myQueue);
    else enqueue(flag, myQueue);

    while(line <= height) {
        k = pow(2, line);
        e = pow(2, height - line) -1;

        for(i=0; i< k; i++) {
            root = dequeue(myQueue);

            if(root != flag) {
                for(j = 0; j< e; j++) {printf("%s", space);}

                printf("[%03d,%03d]\n", root->i->a, root->i->b);

                for(j = 0; j<= e; j++) {printf("%s", space);}

                if(root->left) enqueue(root->left, myQueue);
                else enqueue(flag, myQueue);

                if(root->right) enqueue(root->right, myQueue);
                else enqueue(flag, myQueue);
            }
            else {
                for(j = 0; j< 2*e+2; j++) {printf("%s", space);}
                enqueue(flag, myQueue);
                enqueue(flag, myQueue);
            }
        }
        printf("\n");
        line++;
    }
}