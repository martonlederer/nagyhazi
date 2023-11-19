#include "debugmalloc.h"
#include "linkedlist.h"

/**
 * Generikus láncolt lista végéhez ad hozzá egy elemet
 * @param list Láncolt lista
 * @param data Új elem értéke
 * @return Új láncolt lista head
 */
ListItem *push(ListItem *list, void *data) {
    ListItem *newItem = (ListItem*) malloc(sizeof (ListItem));
    newItem->data = data;
    newItem->next = NULL;

    // ha ez az első elem, akkor csak visszaadjuk az új pointert
    if (list == NULL)
        return newItem;

    ListItem *current = list;

    // megkeressük az utolsó elemet
    while (current->next != NULL)
        current = current->next;

    // hozzáfűzzük az utolsó elemhez az új elemet
    current->next = newItem;

    return list;
}

/**
 * Töröl egy elemet a láncolt listából
 * @param list Láncolt lista
 * @param index Eltávolítandó elem indexe
 * @return Új láncolt lista head
 */
ListItem *removeItem(ListItem *list, int index) {
    // head törlését külön kezeljük
    if (index == 0) {
        ListItem *next = list->next;
        free(list);
        return next;
    }

    // törlés index szerint
    // 1-es indextől kezdjük, hiszen a 0-ás indexet
    // már az elején kezeltük
    int j = 1;
    ListItem *current = list->next;
    ListItem *previous = list;

    while (current->next != NULL && j <= index) {
        // megtaláljuk az elemet
        if (index == j) {
            // előző linkelése a következőhöz
            previous->next = current->next;

            // felszabadítás
            free(current->data);
            free(current);

            // kilépés a ciklusból
            break;
        }

        previous = current;
        current = current->next;
        j++;
    }

    return list;
}

/**
 * Felszabadítja a lista memóriáját
 * @param list Felszabadítandó lista
 */
void freeList(ListItem *list) {
    ListItem *curr;

    while (list != NULL) {
        curr = list;
        list = list->next;

        free(curr->data);
        free(curr);
    }
}
