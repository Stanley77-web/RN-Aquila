#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef int FileDes;
typedef struct node* Addr;
typedef struct node {
    FileDes info;
    Addr next;
} Node;
typedef Addr List;

#define FD(P) (P)->info
#define Next(P) (P)->next


Addr Allocation(FileDes info) {
    Addr New = (Addr) malloc (sizeof(Node));
    (New)->info = info;
    (New)->next = NULL;
    return New;
}

void LastNode(List L, Addr * Last) {
    *Last = L;
    while ((*Last)->next != NULL) *Last = (*Last)->next;
}

#endif