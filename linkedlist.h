#ifndef NAGYHAZI_LINKEDLIST_H
#define NAGYHAZI_LINKEDLIST_H

#include "debugmalloc.h"

/**
 * Generikus láncolt lista elemének struktúrája
 */
typedef struct ListItem {
    void *data;
    struct ListItem *next;
} ListItem;

/**
 * Generikus láncolt lista végéhez ad hozzá egy elemet
 * @param list Láncolt lista
 * @param data Új elem értéke
 * @return Új láncolt lista head
 */
ListItem *push(ListItem *list, void *data);

/**
 * Töröl egy elemet a láncolt listából
 * @param list Láncolt lista
 * @param index Eltávolítandó elem indexe
 * @return Új láncolt lista head
 */
ListItem *removeItem(ListItem *list, int index);

/**
 * Felszabadítja a lista memóriáját
 * @param list Felszabadítandó lista
 */
void freeList(ListItem *list);

#endif
