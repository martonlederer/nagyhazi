#include <stdio.h>
#include "debugmalloc.h"
#include "linkedlist.h"
#include "menu.h"

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
    int scanres = 0;

    // elemek beolvasása a láncolt listába a fájlból
    while (scanres != EOF) {
        char *line = (char*) malloc(sizeof(char));
        *line = '\0';

        // először beolvassuk a sort dinamikusan
        while ((scanres = fscanf(f, "%c", &c)) && scanres == 1 && c != '\n') {
            // + 2 kell, mert az strlen nem számolja a lezáró 0-t
            size_t new_len = strlen(line) + 2;
            line = (char*) realloc(line, new_len * sizeof(char));

            // az új karakter
            line[new_len - 2] = c;
            line[new_len - 1] = '\0';
        }

        if (strlen(line) == 0) {
            free(line);
            break;
        }

        MenuItem *newItem = (MenuItem*) malloc(sizeof(MenuItem));

        // most beolvassuk dinamikusan a nevet is
        newItem->name = (char*) malloc(sizeof(char));
        *newItem->name = '\0';

        char nc = '\0';
        char *linepos = line;

        while (sscanf(linepos, "%c", &nc) == 1 && nc != '\t') {
            size_t new_len = strlen(newItem->name) + 2;
            newItem->name = (char*) realloc(newItem->name, new_len * sizeof(char));

            // karakter hozzáadása
            newItem->name[new_len - 2] = nc;
            newItem->name[new_len - 1] = '\0';

            // következő elem
            linepos += sizeof(char);
        }

        // ár beolvasása (elcsúsztatjuk eggyel a pointert,
        // hogy számoljunk a tabulátor karakterrel)
        sscanf(linepos + sizeof(char), "%d\n", &newItem->price);
        free(line);

        list = push(list, newItem);
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
