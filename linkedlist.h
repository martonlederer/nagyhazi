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

/**
 * Visszaad egy elemet a láncolt listából az
 * indexe alapján.
 * @param list Láncolst lista
 * @param index Elem indexe
 * @return Az elemre mutató pointer (vagy NULL
 * pointer, ha az elem nem található)
 */
ListItem *getItemByIndex(ListItem *list, int index);

/**
 * Megszámolja, hogy milyen hosszú az adott láncolt lista
 * @param list Láncolt lista, amit meg kell számolni
 * @return Lista hossza
 */
size_t getListLength(ListItem *list);

#endif
