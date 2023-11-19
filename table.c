#include "linkedlist.h"
#include "table.h"

/**
 * Az asztalok betöltését elvégző funkció
 * @param list Az asztal láncolt listájának első elemére mutató pointer
 */
ListItem *loadTables() {
    FILE *f = fopen("./tables.txt", "r");

    // a fájl nem létezik
    if (f == NULL) return NULL;

    // aktuális elem
    ListItem *list = NULL;
    Table curr;
    int curr_occupied = 0;

    while(fscanf(f, "%d\t%d\t%d\t%d\n", &curr.x, &curr.y, &curr.capacity, &curr_occupied) == 4) {
        // int -> bool
        curr.occupied = (bool) curr_occupied;

        list = push(list, &curr);
    }

    // fájl bezárása
    fclose(f);

    return list;
}

/**
 * Az asztalok elmentését végző funkció
 * @param list Az asztal láncolt listájának első elemére mutató pointer
 */
void saveTables(ListItem *list) {
    FILE *f = fopen("./tables.txt", "w");
    ListItem *current = list;

    if (f == NULL) {
        perror("Hiba volt az asztalok fájl megnyitása közben.");
        return;
    }

    // végigmegyünk a láncolt listán
    while (current != NULL) {
        // beírjuk a fájl egy új sorába az asztalt
        Table *table = (Table*) current->data;
        fprintf(f, "%d\t%d\t%d\t%d\n", table->x, table->y, table->capacity, table->occupied);

        // következő elemre megyünk
        current = current->next;
    }

    fclose(f);
}
