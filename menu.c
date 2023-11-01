#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"

/**
 * A menün szereplő étel struktúrája
 */
typedef struct MenuItem {
    char *name;
    int price;
    struct MenuItem *next;
} MenuItem;

// Menü láncolt lista management

/**
 * A menü láncolt listához ad elemet
 * @param list Láncolt lista első elemére mutató pointer
 * @param item Új elem
 */
void addToMenu(MenuItem *list, MenuItem *item) {
    MenuItem *current = list;

    // megkeressük az utolsó elemet
    while (current->next != NULL)
        current = current->next;

    // linkelés
    current->next = item;
}

/**
 * A menü láncolt listából töröl egy elemet
 * @param list Láncolt lista első elemére mutató pointer
 * @param item Elem neve
 * @returns A sorozat új első eleme
 */
MenuItem *removeFromMenu(MenuItem *list, char *itemName) {
    MenuItem *current = list;

    // az első elemet külön kezeljük
    if (strcmp(current->name, itemName) == 0) {
        return current->next;
    }

    while (current->next != NULL) {
        // előző elem
        MenuItem *previous = current;
        current = current->next;

        // megnézzük, hogy az elem neve
        // egyezik a megadott névvel
        if (strcmp(current->name, itemName) == 0) {
            // az előzőt a következőhöz linkeljük
            previous->next = current->next;

            // felszabadítjuk az aktuális elemet
            free(current);

            // kilépünk a ciklusból
            break;
        }
    }

    return list;
}

/**
 * Egy menü lista felszabadítására szolgáló funkció
 * @param list Láncolt lista első elemére mutató pointer
 */
void freeMenu(MenuItem *list) {
    MenuItem *curr = list;

    while (list != NULL) {
        curr = list;
        list = list->next;
        free(curr);
    }
}

// Menü mentésére szolgáló funkciók

/**
 * A menü betöltését elvégző funkció
 * @param list A menü láncolt listájának első elemére mutató pointer
 */
void loadMenu(MenuItem *list) {
    FILE *f = fopen("./menu.txt", "r");

    // ha még nincs menü, a fájl nem létezik
    if (f == NULL) return;

    // aktuális elemek
    MenuItem *current = (MenuItem*) malloc(sizeof(MenuItem));
    MenuItem *previous = list;

    // elemek beolvasása a láncolt listába a fájlból
    fscanf(f, "%[^\\t] %d", previous->name, &previous->price);

    while (fscanf(f, "%[^\\t] %d", current->name, &current->price) == 2) {
        previous->next = current;
        previous = current;
    }

    // fájl bezárása
    fclose(f);
}

/**
 * A menü elmentését végző funkció
 * @param list A menü láncolt listájának első elemére mutató pointer
 */
void saveMenu(MenuItem *list) {
    FILE *f = fopen("./menu.txt", "w");
    MenuItem *current = list;

    if (f == NULL) {
        perror("Hiba volt a fájl megnyitása közben.");
        return;
    }

    // végigmegyünk a láncolt listán
    while (current != NULL) {
        // beírjuk a fájl egy új sorába a menü aktuális elemét
        fprintf(f, "%s\t%d\n", current->name, current->price);
        // következő elemre megyünk
        current = current->next;
    }

    fclose(f);
}
