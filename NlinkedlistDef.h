#ifndef NLINKEDLISTDEF_H
#define NLINKEDLISTDEF_H
#include "linkedlist.h"

struct LL
{
    int count;
    NODE head;
};

typedef struct LL LL;
typedef LL* LIST;

#endif