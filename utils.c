#include "data_structure.h"

void life_destroy(p_life_t life) {
    if(life == NULL) {
        return;
    }

    if(life ->children != NULL) {
        free(life -> children);
        life -> children = NULL;
    }
    if(life ->money != NULL) {
        free(life -> money);
        life -> money = NULL;
    }
    if(life ->yourself != NULL) {
        free(life -> yourself);
        life -> yourself = NULL;
    }
    if(life ->parents != NULL) {
        free(life -> parents);
        life -> parents = NULL;
    }
    if(life ->partner != NULL) {
        free(life -> partner);
        life -> partner = NULL;
    }
    free(life);
    life = NULL;
}


void watch(const void * content) {
#define p(x)\
    printf("mylife contains %s EOF\n", x)
//    char * temp = (char *)malloc(buf);
//    memset(temp, 0X00, buf);
//    memcpy(temp, content, buf);
#ifdef TEST
    p_life_t life = content;
    printf("[==============[%s]==============]\n", getDate());
    p(sizeof(p_life_t));
    p(sizeof(life_t));
    p(sizeof(life));
    p(life -> parents);
    p(life -> partner);
    p(life -> yourself);
    p(life -> money);
    //p(life -> children);
    printf("[==============[%s]==============]\n", getDate());
#endif // TEST
    //printf("\n[==============[%s]==============]\n", getDate());
    //p(temp);
    //printf("\n[==============[%s]==============]\n", getDate());
    int * temp = (int *) content;
    LOG("this node's content is", "", * temp);
}

char * getDate() {
    static char time_str[15];
    time_t now;
    struct tm * tmNow;

    time(&now);
    tmNow = localtime(&now);

    //YYYY-MMDD-HH:MM:SS
    sprintf(time_str, "%4d%02d%02d-%02d:%02d:%02d %s %s",
            tmNow -> tm_year + 1900,
            tmNow -> tm_mon + 1,
            tmNow -> tm_mday,
            tmNow -> tm_hour,
            tmNow -> tm_min,
            tmNow -> tm_sec,
            CHNWEEK(tmNow -> tm_wday),
            LEAPYEAR(tmNow -> tm_year + 1900));

    return time_str;
}

static int isLeapYear(const int year) {
    if(((year % 100 == 0) && (year % 4 == 0)) || year % 400 == 0) {
        return 1;
    }
    return 0;
}

