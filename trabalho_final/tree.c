#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

#define MAX(a,b) ((a > b) ? a : b)

typedef enum { false, true }bool;

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
            root->left = tree_rLeft(root->left);
        root = tree_rRight(root);
    }
    else if(f == -2) {
        if(tree_height(root->right->left) > tree_height(root->right->right))
            root->right = tree_rRight(root->right);
        root = tree_rLeft(root);
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
        return;
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
    if(root == NULL) return root;
    if(x->a < root->i->a) 
        root->left = node_delete(x, root->left);
    else if(x->a > root->i->a)
        root->right = node_delete(x, root->right);
    else {
        if(root->left == NULL) {
            p = root;
            root = root->right;
            free(p);
        }
        else if(root->right == NULL) {
            p = root;
            root = root->left;
            free(p);
        }
        else {
            p = get_max(root->left);
            root->i = p->i;
            root->left = node_delete(p->i, root->left);
        }
    }
    return rebalance(root);
}

intert *search(intert *x, nodet *root) {
    if(!root) return NULL;
    if(root->i->a == x->a && root->i->b == x->b) 
        return root->i;
    else if(x->a < root->i->a)
        return search(x, root->left);
    else return search(x, root->right);
}

bool do_overlap(intert *x, intert *y) {
    if(x->a <= y->b && y->b <= x->b) return true;
    else return false;
}

intert *overlap(intert *x, nodet *root) {
    if(!root) return NULL;
    if(do_overlap(x, root->i))
        printf("[%03d,%03d] ", root->i->a, root->i->b);
    if(root->left!=NULL && root->left->max >= x->a)
        return overlap(x, root->left);
    else 
        return overlap(x, root->right);
}

void inorder(nodet *root) {

}

void display(nodet *root) {

}