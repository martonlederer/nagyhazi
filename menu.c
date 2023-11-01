#include <stdio.h>
#include <stdlib.h>

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

// Menü mentésére szolgáló funkciók

/**
 * A menü betöltését elvégző funkció
 * @param firstItem A menü láncolt listájának első elemére mutató pointer
 */
void loadMenu(MenuItem *firstItem) {
    FILE *f = fopen("./menu.txt", "r");

    // ha még nincs menü, a fájl nem létezik
    if (f == NULL) {
        firstItem = NULL;
        return;
    }

    // aktuális elemek
    MenuItem *current = (MenuItem*) malloc(sizeof(MenuItem));
    MenuItem *last = firstItem;

    // elemek beolvasása a láncolt listába a fájlból
    fscanf(f, "%[^\\t] %d", last->name, &last->price);

    while (fscanf(f, "%[^\\t] %d", current->name, &current->price) == 2) {
        last->next = current;
        last = current;
    }

    // fájl bezárása
    fclose(f);
}
