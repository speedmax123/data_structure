#include "data_structure.h"

p_d_list_t d_list_create() {
    p_d_list_t list;
    if((list = (p_d_list_t)malloc(sizeof(d_list_t))) == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    list -> d_list_size = 0;
    list -> head = (p_d_node_t)malloc(sizeof(d_node_t));
    if(list -> head == NULL) {
        free(list);
        errno = ENOMEM;
        return NULL;
    }
    list -> head -> content = NULL;
    list -> head -> next = list -> head -> prev = NULL;
    list -> tail = list -> head;
    return list;
}

void d_list_destroy(p_d_list_t list) {
    unsigned int index;
    p_d_node_t current_node, ptr_node;

    if(list == NULL) {
        errno = EINVAL;
        return;
    }

    ptr_node = current_node = list -> head;
    if(list -> d_list_size != 0)
    {
        for(index = 1; index <= list -> d_list_size; index++)
        {
            current_node = current_node -> next;
            free(ptr_node -> content);
            free(ptr_node);
            ptr_node = current_node;
        }
        free(list);
    }
}

int d_list_insert_after(p_d_list_t list, unsigned int index, void * new_element, size_t n) {
    p_d_node_t current_node, temp_node;
    void * temp_data = NULL;
    unsigned int index_local = 0;

    if(list == NULL) {
        errno = EINVAL;
        return -1;
    }

    temp_data = malloc(n);
    if(!temp_data) {
        errno = EINVAL;
        return -1;
    }
    memset(temp_data, 0X00, buf);

    //when list is not null
    if(list -> d_list_size != 0) {
        temp_node = (p_d_node_t) malloc (sizeof(d_node_t));
        if (temp_node == NULL) {
            free(temp_data);
            errno = ENOMEM;
            return -1;
        }
        //printf("\n [FILENAME]:%s temp_data [LINE]: %d. is %s and sizeof is %d and strlen is %d  EOF\n\n",__FILE__, __LINE__, temp_data, sizeof temp_data, strlen(temp_data));
        memcpy(temp_data, new_element, n);
        #ifdef TEST
        printf("\n [FILENAME]:%s temp_data [LINE]: %d. is %s and sizeof is %d and strlen is %d  EOF\n\n",__FILE__, __LINE__, temp_data, sizeof temp_data, strlen(temp_data));
        #endif
        temp_node -> content = temp_data;               /* this must point to a new mem */
        //printf("\n [FILENAME]:%s temp_node -> content [LINE]: %d. is %s and sizeof is %d and strlen is %d  EOF\n\n",__FILE__, __LINE__, temp_node -> content, sizeof(temp_node -> content), strlen(temp_node -> content));
        temp_node -> next = temp_node -> prev = NULL;   /* initialize the prev and next pointer */
        if(index > 0 && index <= list -> d_list_size) { /* index is reasonable */
            current_node = list -> head;                /* point the current node to the head, then iterate it */
            while(index_local != index - 1) {           /* iterate the current node to the node indexed by index */
                index_local++;
                current_node = current_node -> next;
            }
            /* current node is now EOL */
            if(current_node -> next == NULL) {
                current_node -> next = temp_node;
                temp_node -> prev = current_node;
                list -> tail = list -> tail -> next;
                list -> d_list_size++;
                return 0;
            }
            /* current node is not EOL */
            //printf("##### content of current node is %s #####\n", current_node -> content);
            temp_node -> prev = current_node;
            temp_node -> next = current_node -> next;
            //current_node -> next -> prev = temp_node;
            p_d_node_t temp = current_node -> next;   /* the next node of current node's prev pointer should now point to temp_node and */
            //printf("##### content of temp is %s #####\n", temp -> content);
            temp -> prev = temp_node;
            current_node -> next = temp_node;
            //p_d_node_t temp2 = current_node -> next;
            //printf("##### content of temp2 is %s #####\n", temp2 -> content);
            //p_d_node_t temp3 = temp2 -> next;
            //printf("##### content of temp3 is %s #####\n", temp3 -> content);
            list -> d_list_size++;
        }
        else {
            free(temp_node);
            free(temp_data);
            errno = EINVAL;
            return -1;
        }
    }
    //when list is null
    else {
        //when index is out of list return -1
        if(index != 0) {
            free(temp_data);
            errno = EINVAL;
            return -1;
        }
        //make the head point to new_element
        memcpy(temp_data, new_element, n);
        list -> head -> content = temp_data;
        list -> d_list_size++;
    }
    return 0;
}

int d_list_insert_before(p_d_list_t list, unsigned int index, void * element, size_t n) {
    p_d_node_t temp_node, current_node;
    void * temp_data = NULL;
    unsigned int index_local = 0;

    if(list == NULL) {
        errno = EINVAL;
        return -1;
    }

    temp_data = malloc(n);
    if(temp_data == NULL) {
        errno = EINVAL;
        return -1;
    }

    memcpy(temp_data, element, n);
    temp_node = (p_d_node_t)malloc(sizeof(d_node_t));
    if(temp_node == NULL) {
        errno = EINVAL;
        return -1;
    }
    temp_node -> content = temp_data;
    temp_node -> prev = temp_node -> next = NULL;

    if(index > 0 && index < list -> d_list_size) {
        current_node = list -> head;
        while(index_local < index) {
            index_local++;
            current_node = current_node -> next;
        }

        if(index_local == 1) {
            p_d_node_t node_head = list -> head;
            node_head -> prev = temp_node;
            temp_node -> next = list -> head;
            list -> head = list -> head -> prev;
            list -> d_list_size++;
            return 0;
        }
        p_d_node_t temp = current_node -> prev;
        temp -> next = temp_node;
        temp_node -> prev = temp;
        temp_node -> next = current_node;
        list -> d_list_size++;
    }
    else {
        free(temp_data);
        free(temp_node);
        errno = EINVAL;
        return -1;
    }
    return 0;
}

int d_list_delete(p_d_list_t list, unsigned int index) {
    p_d_node_t current_node, temp_node;
    unsigned int index_local = 1;
    if(list == NULL) {
        errno = EINVAL;
        return -1;
    }
    current_node = list -> head;
    if(index > 0 && index <= list -> d_list_size) {
        while(index_local < index) {
            index_local++;
            current_node = current_node -> next;
        }
        if(index_local == 1) {
            temp_node = list -> head;
            list -> head = temp_node -> next;
            temp_node -> prev = NULL;
            free(temp_node -> content);
            free(temp_node);
            list -> d_list_size--;
            return 0;
        }
        if(index_local == list -> d_list_size) {
            temp_node = list -> tail;
            list -> tail = temp_node -> prev;
            temp_node -> next = NULL;
            free(temp_node -> content);
            free(temp_node);
            list -> d_list_size--;
        }
        temp_node = current_node;
        p_d_node_t temp_node_prev = temp_node -> prev;
        p_d_node_t temp_node_next = temp_node -> next;
        temp_node_prev -> next = temp_node -> next;
        temp_node_next -> prev = temp_node -> prev;
        free(temp_node -> content);
        free(temp_node);
        list -> d_list_size--;
    }
    else {
        errno = EINVAL;
        return -1;
    }
    return 0;
}

void d_list_watch(p_d_list_t list, void(*function)(const void*)) {
    unsigned int index;
    p_d_node_t current_node;

    /* when list is empty then return */
    if((list == NULL) || list -> d_list_size == 0) {
        errno = EINVAL;
        return;
    }

    current_node = list -> head;
    for(index = 1; index <= list -> d_list_size; current_node = current_node -> next, index++)   (*function)(current_node -> content);
    return;

}
