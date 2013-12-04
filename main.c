#include <stdio.h>
#include <stdlib.h>

/*
 * data structure of AVL tree
 */
typedef struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
} node;

/*
 * return height of a node
 */
int height(node *n)
{
    if (n == NULL)
        return 0;
    return n->height;
}

/*
 * return the bigger value between a and b
 */
int max(int a, int b)
{
    return (a > b) ? a : b;
}

/*
 * create a new node and return its pointer
 */
node *new_node(int key)
{
    node *new_node = (node *)calloc(1, sizeof(node));

    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 0;

    return new_node;
}

/*
 * right rotate subtree rooted with y
 */
node *right_rotate(node *y)
{
    node *x = y->left;
    node *T2 = x->right;

    /* rotation */
    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    /* return new root */
    return x;
}

/*
 * left rotate subtree rooted with x
 */
node *left_rotate(node *x)
{
    node *y = x->right;
    node *T2 = y->left;

    /* rotation */
    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    /* return new root */
    return y;
}

/*
 * get the difference between height of left subtree and height of right subtree
 */
int get_balance(node *n)
{
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

/*
 * insert a node, caculate the balance of the node and rotate a tree to make it balanced
 */
node *node_insert(node *node, int key)
{
    int balance;

    if (node == NULL)
        return (new_node(key));

    if (key < node->key)
        node->left = node_insert(node->left, key);
    else
        node->right = node_insert(node->right, key);

    node->height = max(height(node->left), height(node->right)) + 1;
    balance = get_balance(node);

    /* Left Left */
    if (balance > 1 && key < (node->left)->key)
        return right_rotate(node);
    /* Left Right */
    if (balance > 1 && key > (node->left)->key) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    /* Right Right */
    if (balance < -1 && key > (node->right)->key)
        return left_rotate(node);
    /* Right Left */
    if (balance < -1 && key < (node->right)->key) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

/*
 * print items of a tree
 */
void print_tree(node *node)
{
    if (node) {
        print_tree(node->left);
        printf(" %d ", node->key);
        print_tree(node->right);
    }
}


int main()
{
    node *root = NULL;

    root = node_insert(root, 1);
    root = node_insert(root, 2);
    root = node_insert(root, 4);
    root = node_insert(root, 6);
    root = node_insert(root, 7);
    root = node_insert(root, 5);
    root = node_insert(root, 3);

    print_tree(root);

    return 0;
}
