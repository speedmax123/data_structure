#include "data_structure.h"

int main(int argc, char * argv[])
{
    #ifdef TEST_MAIN
    unsigned char temp[BUF] = "";
    printf("size of temp is %d\n", sizeof(temp));
    FILE * fp = fopen("D:\js.js", "r");
    FILE * fp_copycat = fopen("D:\js1.js", "w+");
    if(NULL == fp || NULL == fp_copycat)
    {
        printf("open file error!\n");
        FRZ;
        exit(0);
    }
    else
    {
        int ret = fread(temp, 1, sizeof temp, fp);
        int ret_copycat = fwrite(temp, 1, strlen(temp), fp_copycat);
        if(!ret)
        {
            printf("read file error!\n");
            FRZ;
            exit(0);
        }
        else if(ret != ret_copycat)
        {
            printf("write is not equal with read\n");
            FRZ;
            exit(0);
        }
        strncat(temp, "\n", 2);
        fprintf(stdout, temp);
    }
    free(temp),fclose(fp),fclose(fp_copycat),FRZ;;
    #endif // TEST_MAIN

    //p_d_list_t list = d_list_create();

    p_bt_t tree = bt_create();
    int i = 5;

    #ifdef TEST_MAIN
    char * value = (char *)malloc(BUF);
    memcpy(value, "speedmax", sizeof("speedmax"));
    #endif // TEST

    #ifdef TEST
    //char value[BUF] = "speedmax";
    char * value = (char *)malloc(buf);
    memset(value, 0X00, buf);
    memcpy(value, "speedmax123", strlen("speedmax123"));
    #endif // TEST

    #ifdef TEST
    if(d_list_insert(list, 0, "speedmax", buf) != 0) {
        printf("list insert error!\n");
        FRZ;
        exit(0);
    }
    #endif // TEST

    do {
        #ifdef TEST
        if(d_list_insert(list, i, mylife, sizeof(mylife)) != 0) {
        #else
        //printf("current line is %d, value is %s, sizeof is %d, strlen is %d EOF\n",__LINE__, value, sizeof value, strlen(value));
        int value = i;
        int ret;
        //ret = ((i % 2 == 0) ? d_list_insert_after(list, i, value, buf) : d_list_insert_after(list, i, "speedmax", buf));
        ret = bt_insert(tree, &value, sizeof(value), cmp);
        if(ret != 0){
        #endif
            LOG(__FILE__, "insert error", 0);
            FRZ;
            exit(0);
        }
        i += 1;
    } while(i < 10);

    int val = 3;
    int ret = bt_insert(tree, &val, sizeof(val), cmp);
    if(ret != 0){
        LOG(__FILE__, "insert error", 0);
        FRZ;
        exit(0);
    }
    LOG("==============================LDR the tree", "", 0);
    bt_in_trav(tree, watch);
    LOG("==============================LRD the tree", "", 0);
    bt_backward_trav(tree, watch);
    LOG("==============================DLR the tree", "", 0);
    bt_forword_trav(tree, watch);
    p_bt_node_t result = bt_search(tree, &val, cmp);
    LOG("result node", "", *(int *)(result -> content));
    //LOG("删除一个二叉树结点", "", 0);
    //bt_delete(tree, &val, 4, cmp);
    //bt_in_trav(tree, watch);
    LOG("destroy the tree", "", 0);
    bt_destroy(tree);
    LOG("destroy tree successfully", "", 0);

    #ifdef TEST
    memset(value, 0X00, buf);
    memcpy(value, "xjttt", buf);
    if(d_list_insert_after(list, 1, value, buf) != 0) {
        printf("list insert error!\n");
        FRZ;
        exit(0);
    }
    if(d_list_insert_before(list, 1, "hello", buf) != 0) {
        printf("list insert error!\n");
        FRZ;
        exit(0);
    }
    if(d_list_delete(list, 10) != 0) {
        printf("list delete error!\n");
        FRZ;
        exit(0);
    }
    #endif // TEST
    //d_list_watch(list, watch);
    //d_list_destroy(list);
    #ifdef TEST
    life_destroy(mylife);
    #endif // TEST

    #ifdef TEST

    #define BUF1 9
        char * ptr = NULL;
        ptr = (char *) malloc (BUF1);
        if (ptr == NULL) {
            exit(1);
        }
        memset(ptr, 0X00, BUF1);
        printf("now pointer is %s and sizeof it is %lu and strlen of it is %lu\n", ptr, sizeof ptr, strlen(ptr));
        memcpy(ptr, "speedmax", strlen("speedmax"));
        printf("now pointer is %s and sizeof it is %lu and strlen of it is %lu\n", ptr, sizeof ptr, strlen(ptr));
        free(ptr);
        ptr = NULL;

    #endif // TEST
    FRZ;
    return 0;
}
