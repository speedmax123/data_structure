#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct binary_tree_node {
    void * content;
    //value of binary tree node
    struct binary_tree_node * lchild;
    //the left child node of this node
    struct binary_tree_node * rchild;
    //the right child node of this node
} bt_node_t;
/* binary tree node */

typedef bt_node_t * p_bt_node_t;
/* binary tree node pointer */

typedef struct binary_tree {
    //the root node of the binary tree
    p_bt_node_t * root;
    //size of the binary tree
    unsigned int binary_tree_size;
} bt_t;
/* binary tree */

typedef bt_t * p_bt_t;
/* binary tree pointer */

/* functions */

extern p_bt_t bt_create();
/* create a binary tree */

extern int bt_insert(p_bt_t, void *, size_t, int(*)(void *, void *));
/* insert a element to the binary tree */

extern int bt_delete(p_bt_t, void *, size_t, int(*)(void *, void *));
/* delete a element of the binary tree */

extern int bt_forword_trav(p_bt_t, int(*)(void *));
/* travel the tree DLR */

extern int bt_backward_trav(p_bt_t, int(*)(void *));
/* travel the tree LRD*/

extern int bt_in_trav(p_bt_t, int(*)(void *));
/* travel the tree LDR*/

static int isleaf(p_bt_node_t node);
/* check if this node is leaf node, 1 is leaf and 0 is not leaf other return value is err */

extern p_bt_node_t bt_search(p_bt_t, void *, int(*)(void *, void *));
/* binary search tree */

static p_bt_node_t bt_free_node(p_bt_node_t);
/* free some node */

extern void bt_destroy(p_bt_t);
/* destroy a binary tree */

extern int errno;

extern int cmp(void *, void*);
/* function "cmp" for compare element */

#endif // BINARYTREE_H_INCLUDED
