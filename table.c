#include "linkedlist.h"
#include "table.h"
#include "io.h"

/**
 * Az asztalok betöltését elvégző funkció
 * @param list Az asztal láncolt listájának első elemére mutató pointer
 * @returns A betöltött lista
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

        // dinamikusan foglaljuk le, mert a
        // láncolt lista csak így tudja kezelni
        // a végén (felszabadítani)
        Table *table = (Table*) malloc(sizeof(Table));
        *table = curr;

        list = push(list, table);
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
    printf(SUCCESS "A %d. asztal megnyitva. " RESET "Mostmár lehet hozzá felvenni a rendeléseket.\n", index + 1);

    return newList;
}

/**
 * Egy asztalt jelöl meg foglaltnak (nyit meg) vagy szabadnak
 * @param index Az asztal indexe
 * @param tableList Asztal láncolt lista
 * @returns Új asztal lista vagy *NULL* hiba esetén
 */
ListItem *setTableOccupied(int index, ListItem *tableList, bool occupied) {
    // megkeressük az asztalt
    ListItem *tableItem = getItemByIndex(tableList, index);

    // nem találtuk az asztalt
    if (tableItem == NULL) {
        printf(ERROR "Az asztal nem található.\n" RESET);

        return NULL;
    }

    Table *table = (Table*) tableItem->data;

    // megnézzük, hogy az asztal állapota már be van e állítva
    if (table->occupied == occupied)
        return NULL;

    // foglaltság beállítása
    table->occupied = occupied;

    return tableList;
}

/**
 * Kinyomtatja az étterem asztalainak térképét
 * @param tableList Asztal láncolt lista
 */
void printTableMap(ListItem *tableList) {
    // megszámoljuk az asztalokat és átmásoljuk őket egy
    // dinamikus tömbbe, sorrend szerint
    size_t tablecount = getListLength(tableList);
    size_t i = 0;
    ListItem *curr = tableList;
    int y = 0;

    while (i < tablecount) {
        // i előző értéke
        // ahhoz kell, hogy lássuk, hogy volt e asztal
        // ebben a sorban
        size_t previ = i;

        for (int j = 0; j < 4; j++) {
            curr = tableList;
            int localCount = 0;
            int lastX = 0;

            while (curr != NULL) {
                // aktuális asztal
                Table *currTable = (Table *) curr->data;

                // csak az aktuális sort írjuk ki
                if (currTable->y != y) {
                    curr = curr->next;
                    continue;
                }

                for (int k = lastX; k < currTable->x - 1; k++) {
                    printf("            ");
                }

                printf(currTable->occupied ? ERROR : SUCCESS);

                switch (j) {
                    case 3:
                    case 0:
                        printf("+---------+ ");
                        break;

                    case 1: {
                        size_t tableNum = localCount + 1 + i;
                        char *spaces = equalSpace(istrlen((int) tableNum) + 1, 9);

                        printf("|%d.%s| " RESET, (int) tableNum, spaces);
                        free(spaces);
                    } break;

                    case 2:
                        printf("|%s| " RESET, currTable->occupied ? "(foglalt)" : "(szabad) ");
                    break;

                    default:
                        break;
                }

                printf(RESET);

                // következő
                lastX = currTable->x;
                curr = curr->next;
                localCount++;
            }

            if (localCount > 0) printf("\n");
            else break;

            if (j == 3)
                i += localCount;
        }

        printf("\n");

        // ha nem volt asztal, akkor üres sor
        if (i == previ && i != 0)
            printf("\n\n\n\n");

        y++;
    }
}
