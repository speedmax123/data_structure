#ifndef DATA_STRUCTURE_H_INCLUDED
#define DATA_STRUCTURE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "binarytree.h"
#include "utils.h"

#define FRZ system("echo -n")
#define BUF 4096
#define buf 12
//#define TEST 0
#define BT 0

/***
 ***
 *** double list
 */

 typedef struct d_node {
    struct d_node_t * prev;
    struct d_node_t * next;
    void * content;
 } d_node_t;
//node

typedef d_node_t * p_d_node_t;
typedef struct d_list {
    p_d_node_t head;
    p_d_node_t tail;
    unsigned int d_list_size;
}d_list_t;
typedef d_list_t * p_d_list_t;
//list

p_d_list_t d_list_create(void);
//create a d list
void d_list_destroy(p_d_list_t);
//destroy a d list
int d_list_insert_after(p_d_list_t, unsigned int, void *, size_t);
//insert a element into dlist after a certain position
int d_list_insert_before(p_d_list_t, unsigned int, void *, size_t);
//insert a element into dlist before a certain position
void d_list_watch(p_d_list_t, void(*)(const void*));
//watch the element of dlist
int d_list_delete(p_d_list_t, unsigned int);
extern int errno;

#endif // DATA_STRUCTURE_H_INCLUDED
