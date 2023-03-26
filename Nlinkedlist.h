#ifndef NLINKEDLIST_H
#define NLINKEDLIST_H
#include "NlinkedlistDef.h"

LIST createNewList();
NODE createNewNode(token t, NT nt, int tnt);
void insertNodeIntoList(NODE node, LIST list);
void removeFirst(LIST list);

#endif