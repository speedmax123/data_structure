#include "data_structure.h"
#include "utils.h"

extern p_bt_t bt_create() {

    p_bt_t bt;
    p_bt_node_t root;
    if((bt = (p_bt_t) malloc (sizeof(bt_t))) == NULL) {
        errno = ENOMEM;
        LOG("allocate memory for the tree", "failed", errno);
        return NULL;
    }
    LOG("allocate memory for the tree", "success", 0);

    bt ->binary_tree_size = 0;
    if((bt -> root = (p_bt_node_t) malloc (sizeof(bt_node_t))) == NULL) {
        free(bt);
        errno = ENOMEM;
        LOG("allocate memory for the root node", "failed", errno);
        return NULL;
    }
    LOG("allocate memory for the root node", "success", 0);

    root = bt -> root;
    root -> content = NULL;
    root -> lchild = root -> rchild = NULL;
    LOG("tree create", "success", 0);
    return bt;

}

extern int bt_insert(p_bt_t bt, void * element, size_t n, int(*function)(void *, void *)) {
    register p_bt_node_t temp_node;
    p_bt_node_t new_node;
    void * content_ptr;

    if(bt == NULL) {
        errno = EINVAL;
        return -1;
    }

    content_ptr = malloc(n);
    if(content_ptr == NULL) {
        errno = ENOMEM;
        return -1;
    }

    temp_node = bt -> root;
    int * val = (int*)(temp_node -> content);
    if(val != NULL)
        LOG("root", "root", * val);

    if(bt -> binary_tree_size == 0) {
        memcpy(content_ptr, element, n);
        temp_node -> content = content_ptr;
    }
    else {
        //make a dead loop which makes the compare function "cmp" lasts till the new element is arranged at a right position
        for(;;) {
            //at the very beginning, the binary tree has only one root, temp_node pointer is to root node, so compare the temp_node's element with the new element
            //when the element is larger than the temp_node's element
            if(cmp(temp_node -> content, element) > 0) {
                //when temp_node's left child is NULL, make its left node and put element in it
                if(temp_node -> lchild == NULL) {
                    LOG("this node's left child is null, so create its right left node", "", 0);
                    new_node = (p_bt_node_t) malloc (sizeof(bt_node_t));
                    if(new_node == NULL) {
                        errno = ENOMEM;
                        return -1;
                    }
                    memcpy(content_ptr, element, n);
                    new_node -> content = content_ptr;
                    new_node -> lchild = new_node -> rchild = NULL;
                    temp_node -> lchild = new_node;
                    break;
                }
                //when temp_node's left child node is not null
                else {
                    //now we can keep run function "cmp" comparing temp_node's content with element
                    LOG("this node's left child is not null, so trans itself to lchild", "", 0);
                    temp_node = temp_node -> lchild;
                }
            }
            //when the element is tinier than the temp_node's element
            else if(cmp(temp_node -> content, element) < 0) {
                //when temp_node's right child node is NULL, make its right now and put element in it
                if(temp_node -> rchild == NULL) {
                    LOG("this node's right child is null, so create its right child node", "", 0);
                    new_node = (p_bt_node_t)malloc(sizeof(p_bt_node_t));
                    if(new_node == NULL) {
                        errno = EINVAL;
                        return -1;
                    }
                    memcpy(content_ptr, element, n);
                    new_node -> content = content_ptr;
                    new_node -> lchild = new_node -> rchild = NULL;
                    temp_node -> rchild = new_node;
                    break;
                }
                //when temp_node's right child node is not null
                else {
                    //now we can keep run function "cmp" comparing temp_node's content with element
                    LOG("this node's right child is not null, so trans itself to lchild", "", 0);
                    temp_node = temp_node -> rchild;
                }
            }
            //when the element is total equal with temp_node's element, so where to put the new element is depended on requirement
            else if(cmp(temp_node -> content, element) == 0){
                #ifdef NEW

                #endif // NEW
                //default is to do nothing
                return 0;
            }
            //this condition happens maybe when function "cmp" dead
            else {
                free(content_ptr);
                errno = EINVAL;
                return -1;
            }
        }
    }
    bt -> binary_tree_size++;
    return 0;
}

static p_bt_node_t bt_free_node(p_bt_node_t node) {
    if(node == NULL) {
        LOG("current node is null", "", 0);
        return NULL;
    }
    else if(isleaf(node)) {
        int * tmp = (int *)(node -> content);
        LOG("current node is leaf node", "", *tmp);
        free(node -> content);
        free(node);
        tmp = NULL;
        return NULL;
    }
    else {
        node -> lchild = bt_free_node(node -> lchild);
        LOG("free node's left child node", "", 0);
        node -> rchild = bt_free_node(node -> rchild);
        LOG("free node's right child node", "", 0);
    }
}

extern void bt_destroy(p_bt_t tree) {
    p_bt_node_t root = tree -> root;
    int * val = root -> content;
    LOG("content of root is", "", *val);
    bt_free_node(tree -> root);
    LOG("free node", "okay", 0);
    free(tree);
    LOG("free tree", "okay", 0);
    root = NULL;
    val = NULL;
}

extern int bt_delete(p_bt_t tree, void * element, size_t n, int(*function)(void *, void *)) {
    register p_bt_node_t node;
    p_bt_node_t temp_node;
    void * temp;

    if(tree == NULL || function == NULL) {
        errno = EINVAL;
        return -1;
    }

    //initialize node to root node
    for(;;) {
        if(cmp(node -> content, element) < 0) {
            LOG("current node is tinier than element", "", 0);
            if(node -> rchild == NULL) {
                errno = EINVAL;
                return -1;
            }
            if(isleaf(node -> rchild) == 0) {
            //when current node's right child is leaf node, then make current node switched to its right child
                node = node -> rchild;
            }
            else if(isleaf(node -> rchild) == -1) {
            //when isleaf function return -1. it means error, and errno is EINVAL
                return -1;
            }
            else {
                p_bt_node_t N = node -> rchild;
                if(cmp(N -> content, element) == 0) {
                    //when node's right child equals with element
                    free(N -> content);
                    free(node -> rchild);
                    node -> rchild = NULL;
                    N = NULL;
                    break;
                }
                else {
                    //binary search no result now
                    errno = EINVAL;
                    return -1;
                }
            }

        }
        else if(cmp(node -> content, element) > 0) {
            LOG("current node is larger than element", "", 0);
            if(node -> lchild == NULL) {
                errno = EINVAL;
                return -1;
            }
            if(isleaf(node -> lchild) == 0) {
                node = node -> lchild;
            }
            else if(isleaf(node -> lchild) == -1) {
            //when isleaf function return -1. it means error, and errno is EINVAL
                errno = EINVAL;
                return -1;
            }
            else {
                p_bt_node_t N = node -> lchild;
                if(cmp(N -> content, element) == 0) {
                //when node's right child equals with element
                    free(N -> content);
                    free(node -> lchild);
                    N = NULL;
                    node -> lchild = NULL;
                    break;
                }
                else {
                    //binary search no result now
                    errno = EINVAL;
                    return -1;
                }
            }
        }
        else {
            temp = malloc(n);
            if(!temp) {
                errno = ENOMEM;
                return -1;
            }

            if(node -> rchild == NULL && node -> lchild != NULL) {
            //when node's content equals with element and only left child is not null
                if(tree -> binary_tree_size == 1) {
                    free(node -> content);
                    break;
                }
                //make another pointer to current node
                temp_node = node;
                //make node switched to itself
                node = node -> lchild;
                while(node -> rchild != NULL) {
                //till the max
                    node = node -> rchild;
                }
                memcpy(temp, node -> content, n);
                if(bt_delete(tree, temp, n, cmp) == -1) {
                //recursion
                    return -1;
                }
                temp_node -> content = temp;
            }
            else {
                if(tree -> binary_tree_size == 1) {
                    free(node -> content);
                    break;
                }
                temp_node = node;
                node = node -> rchild;
                while(node -> lchild != NULL) {
                    //till the min
                    node = node -> lchild;
                }
                memcpy(temp, node -> content, n);
                if(bt_delete(tree, temp, n, cmp) == -1) {
                    //recursion
                    break;
                }
                temp_node -> content = temp;
            }
            //here is no break
            return 0;
        }
    }
    tree -> binary_tree_size--;
    return 0;
}
static void backward_trav(p_bt_node_t node, int(*function)(void *)) {
    if(node == NULL) {
        return;
    }
    backward_trav(node -> lchild, function);
    backward_trav(node -> rchild, function);
    (*function)(node -> content);
    return;
}

extern int bt_backward_trav(p_bt_t tree, int(*function)(void *)) {
    if(tree == NULL || function == NULL) {
        errno = EINVAL;
        return -1;
    }
    backward_trav(tree -> root, watch);
    return 0;
}

static void forward_trav(p_bt_node_t node, int(*function)(void *)) {
    if(node == NULL) {
        return;
    }
    function(node -> content);
    forward_trav(node -> lchild, function);
    forward_trav(node -> rchild, function);
    return;
}

extern int bt_forword_trav(p_bt_t tree, int(*function)(void *)) {
    if(tree == NULL || function == NULL) {
        errno = EINVAL;
        return -1;
    }
    forward_trav(tree -> root, function);
    return 0;
}


static void in_trav(p_bt_node_t node, int(*function)(void *)) {
    if(node == NULL || function == NULL) {
        return;
    }
    in_trav(node -> lchild, function);
    (*function)(node -> content);
    in_trav(node -> rchild, function);
    return;
}

extern int bt_in_trav(p_bt_t tree, int(*function)(void *)) {
    if(tree == NULL || function == NULL) {
        errno = EINVAL;
        return -1;
    }
    in_trav(tree -> root, function);
    return 0;
}

static int isleaf(p_bt_node_t node) {
    if(node == NULL) {
        errno = EINVAL;
        return -1;
    }
    if(node -> lchild == NULL && node -> rchild == NULL) {
    //when a node's left child and right child are both null, then the node is a leaf node
        return 1;
    }
    else {
        return 0;
    }
}

extern p_bt_node_t bt_search(p_bt_t tree, void * element, int(*function)(void *, void *)) {
    if(tree == NULL || element == NULL) {
        errno == EINVAL;
        return NULL;
    }

    register p_bt_node_t node;
    node = tree -> root;
    for(;;) {
        if(function(node -> content, element) > 0) {
            LOG("current node' content is larger than element's", "true", 0);
            node = node -> lchild;
            if(node == NULL) {
                return NULL;
            }
            continue;
        }
        else if(function(node -> content, element) > 0) {
            LOG("current node's content is smaller than element's", "true", 0);
            node - node -> rchild;
            if(node == NULL) {
                return NULL;
            }
            continue;
        }
        else {
            LOG("current node's content is equal with element's", "true", *(int *)(node -> content));
            break;
        }
    }
    return node;
}

int cmp(void * local, void * out) {
    int * a = (int *)local;
    int * b = (int *)out;
    printf("[====local is %d and out is %d====]\n", *a, *b);
    if(*a > *b)
        return 1;
    if(*a < *b)
        return -1;
    if(*a == *b)
        return 0;
    return 0;
}

