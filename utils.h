#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <memory.h>

#define CHNWEEK(day) \
    (day == 0) ? "SUN" :\
    (day == 1) ? "MON" :\
    (day == 2) ? "TUE" :\
    (day == 3) ? "WED" :\
    (day == 4) ? "THU" :\
    (day == 5) ? "FRI" :\
    (day == 6) ? "SAT" : "wrong date"

#define LEAPYEAR(year) \
    (year == 1) ? "leapyear" : "not_leapyear"

#define LOG(x,y,z) \
    printf("[[%s][%s][%d][%s] is now [%s] and [%d]]\n", __FILE__, getDate(), __LINE__, x, y, z)

typedef struct life {
    void * yourself;
    void * partner;
    void * children;
    void * parents;
    void * money;
} life_t;

typedef life_t * p_life_t;

void life_destroy(p_life_t);
void watch(const void *);
char * getDate();
static int isLeapYear(const int);   /* 0 means not leap year 1 means leap year */

#endif // UTILS_H_INCLUDED
