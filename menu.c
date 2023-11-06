#include <stdio.h>
#include "debugmalloc.h"
#include "linkedlist.h"
#include "io.h"

/**
 * A menü betöltését elvégző funkció
 * @param list A menü láncolt listájának első elemére mutató pointer
 */
ListItem *loadMenu() {
    FILE *f = fopen("./menu.txt", "r");

    // ha még nincs menü, a fájl nem létezik
    if (f == NULL) return NULL;

    // aktuális elem
    ListItem *list = NULL;
    char c = '\0';

    // elemek beolvasása a láncolt listába a fájlból
    while (c != EOF) {
        MenuItem *newItem = (MenuItem*) malloc(sizeof(MenuItem));

        // init név
        newItem->name = (char*) malloc(sizeof(char));
        *newItem->name = '\0';

        while (scanf("%c", &c) == 1 && c != '\t') {
            // realloc
            unsigned long newNameLen = strlen(newItem->name) + 2;
            newItem->name = (char*) realloc(newItem->name, newNameLen * sizeof(char));

            // karakter hozzáadása
            newItem->name[newNameLen - 2] = c;
            newItem->name[newNameLen - 1] = '\0';
        }

        // ár beolvasása
        scanf("%d\n", &newItem->price);

        push(list, newItem);
    }

    // fájl bezárása
    fclose(f);

    return list;
}

/**
 * A menü elmentését végző funkció
 * @param list A menü láncolt listájának első elemére mutató pointer
 */
void saveMenu(ListItem *list) {
    FILE *f = fopen("./menu.txt", "w");
    ListItem *current = list;

    if (f == NULL) {
        perror("Hiba volt a fájl megnyitása közben.");
        return;
    }

    // végigmegyünk a láncolt listán
    while (current != NULL) {
        // beírjuk a fájl egy új sorába a menü aktuális elemét
        MenuItem *item = (MenuItem*) current->data;
        fprintf(f, "%s\t%d\n", item->name, item->price);

        // következő elemre megyünk
        current = current->next;
    }

    fclose(f);
}

/**
 * Felszabadítja a menü listát és az ételek neveit
 */
void freeMenu(ListItem *list) {
    ListItem *current = list;

    while (current != NULL) {
        // név felszabadítás
        MenuItem *item = (MenuItem*) current->data;
        free(item->name);

        // következő elem
        current = current->next;
    }

    // láncolt lista feszabadítás
    freeList(list);
}
