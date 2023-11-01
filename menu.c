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

/**
 * A menü betöltését elvégző funkció
 * @param firstItem A menü láncolt listájának első elemére mutató pointer
 */
void loadMenu(MenuItem *firstItem) {
    FILE *f = fopen("menu.txt", "r");

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
