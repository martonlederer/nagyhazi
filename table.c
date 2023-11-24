#include "linkedlist.h"
#include "table.h"
#include "io.h"

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

/**
 * Új asztalt ad a meglévő asztalok listájához
 * @param x Elhelyezkedés X koordináta
 * @param y Elhelyezkedés Y koordináta
 * @param capacity Az asztalnál leültethető legtöbb ember száma
 * @param tableList Asztal láncolt lista
 * @return Új asztal lista
 */
ListItem *newTable(int x, int y, int capacity, ListItem *tableList) {
    // ellenőrizzük, hogy ezen a helyen nincs-e már egy asztal
    ListItem *curr = tableList;

    while (curr != NULL) {
        // hely összehasonlítása
        Table *table = (Table*) curr->data;

        // ha találunk a helyen asztalt, akkor kiírjuk a hibát
        // majd visszatérünk az eredeti listával
        if (table->x == x && table->y == y) {
            printf(ERROR "Ezen a helyen már van egy asztal.\n" RESET);
            return tableList;
        }

        // következő
        curr = curr->next;
    }

    // új asztal dinamikus memóriaallokációval
    Table *newTable = (Table*) malloc(sizeof(Table));
    *newTable = (Table) {
        x, y, capacity, false
    };

    // hozzáadjuk a listához
    tableList = push(tableList, newTable);

    printf(SUCCESS "Új asztal hozzáadva.\n" RESET);

    return tableList;
}

/**
 * Új asztalt nyit vendégek számára
 * @param index Az asztal indexe
 * @param tableList Asztal láncolt lista
 * @returns Új asztal lista
 */
ListItem *openTable(int index, ListItem *tableList) {
    ListItem *newList = setTableOccupied(index, tableList, true);

    // hiba a megnyitás során
    if (newList == NULL) {
        printf(ERROR "Az asztalt nem lehet megnyitni.\n" RESET);
        return tableList;
    }

    // asztal megnyitva
    printf(SUCCESS "A %d. asztal megnyitva. " RESET "Mostmár lehet hozzá felvenni a rendeléseket.\n", index);

    return newList;
}

/**
 * Egy asztalt jelöl meg foglaltnak (nyit meg) vagy szabadnak
 * @param index Az asztal indexe
 * @param tableList Asztal láncolt lista
 * @returns Új asztal lista vagy *NULL* hiba esetén
 */
ListItem *setTableOccupied(int index, ListItem *tableList, bool occupied) {
    // mínusz indexeket nem nézzük
    if (index < 0) return NULL;

    // végigmegyünk a listán amíg megtaláljuk az indexet
    int i = 0;
    ListItem *curr = tableList;

    while (i != index || curr != NULL) {
        curr = curr->next;
        i++;
    }

    // nem talátuk az asztalt
    if (curr == NULL) {
        printf(ERROR "Az asztal nem található.\n" RESET);

        return NULL;
    }

    // foglalttá tesszük az asztalt
    Table *table = (Table*) curr->data;
    table->occupied = occupied;

    return tableList;
}
