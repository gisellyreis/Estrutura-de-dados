#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b)((a>b) ? a : b)
typedef struct node node_t;
typedef enum { false, true }bool;
typedef int element_t;

struct node {
    element_t ele;
    node_t *left, *right;
    int height;
};

node_t *newNode();
int avl_height(node_t *root);
node_t *get_max(node_t *root);
node_t *search(node_t *root, element_t e);
node_t *insert(node_t *root, element_t e);
node_t *delete(node_t *root, element_t e);
node_t *avl_rRight(node_t *root);
node_t *avl_rLeft(node_t *root);
node_t *rebalance(node_t *root);
void inorder(node_t *root);

node_t *newNode() {
    node_t *root = malloc(sizeof(node_t));
    if(!root) return NULL;
    root->ele = -1;
    root->left = NULL;
    root->right = NULL;
    root->height = 0;
    return root;
}

int avl_height(node_t *root) {
    if(root == NULL) return -1;
    else return root->height;
}

node_t *get_max(node_t *root) {
    while(root->right) root = root->right;
    return root;
}

node_t *search(node_t *root, element_t e) {
    if(root == NULL || e == root->ele) return root;
    else if(e < root->ele) return search(root->left, e);
    else if(e > root->ele) return search(root->right, e);
}

node_t *insert(node_t *root, element_t e) {
    if(root == NULL) {
        root = newNode();
        root->ele = e;
        return root;
    }
    else if(e < root->ele) root->left = insert(root->left, e);
    else if(e > root->ele) root->right = insert(root->right, e);
    return rebalance(root);
}

node_t *delete(node_t *root, element_t e) {
    node_t *p;
    if(root == NULL) return root;
    if(e < root->ele) root->left = delete(root->left, e);
    if(e > root->ele) root->right = delete(root->right, e);
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
            root->ele = p->ele;
            root->left = delete(root->left, p->ele);
        }
    }
    if(root) return rebalance(root);
    else return root;
}

node_t *avl_rRight(node_t *root) {
    node_t *y = root->left;
    root->left = y->right;
    y->right = root;
    root->height = MAX(avl_height(root->left), avl_height(root->right)) + 1;
    y->height = MAX(avl_height(root), avl_height(y->left)) + 1;
    return y;
}

node_t *avl_rLeft(node_t *root) {
    node_t *y = root->right;
    root->right = y->left;
    y->left = root;
    root->height = MAX(avl_height(root->right), avl_height(root->left)) + 1;
    y->height = MAX(avl_height(root), avl_height(root->right)) + 1;
    return y;
}

node_t *rebalance(node_t *root) {
    int lh = avl_height(root->left);
    int rh = avl_height(root->right);
    int f = lh - rh;
    root->height = MAX(lh, rh) + 1;

    if(f == 2) {
        if(avl_height(root->left->left) - avl_height(root->left->right) == -1)
            root->left = avl_rLeft(root->left);
        root = avl_rRight(root);
    }
    else if(f == -2) {
        if(avl_height(root->right->left) - avl_height(root->right->right) == 1)
            root->right = avl_rRight(root->right);
        root = avl_rLeft(root);
    }
    return root;
}

void inorder(node_t *root) {
    if(root == NULL) return;
    inorder(root->left);
    printf("%d\n", root->ele);
    inorder(root->right);
}


int main(void) {
    node_t *tree = NULL;
    tree = insert(tree, 10);
    tree = insert(tree, 50);
    tree = insert(tree, 5);
    tree = insert(tree, 25);

    inorder(tree);
    
}