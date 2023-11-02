#include <stdio.h>
#include "debugmalloc.h"
#include "linkedlist.h"

/**
 * A menün szereplő étel struktúrája
 */
typedef struct MenuItem {
    char *name;
    int price;
} MenuItem;

// Menü mentésére szolgáló funkciók

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
    MenuItem current;

    // elemek beolvasása a láncolt listába a fájlból
    while (fscanf(f, "%[^\\t] %d", current.name, &current.price) == 2) {
        // memóriát adunk az új elemnek és
        // megadjuk az értékét
        MenuItem *newItem = (MenuItem*) malloc(sizeof(MenuItem));
        *newItem = current;

        // TODO: string memória bővítés

        // hozzáfűzés a listához
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
