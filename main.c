#include <stdlib.h>
#include "debugmalloc.h"
#include "linkedlist.h"
#include "menu.h"
#include "io.h"
#include "table.h"
#include "order.h"

int main(int argc, char **argv) {
    // asztalok betöltése
    ListItem *tables = loadTables();

    if (tables == NULL) {
        printWelcome();

        // új asztal megadása
        printf(REQUEST "Kérem adja meg az étterem min. egy asztalát:\n" RESET);
        Table *table = requestTable();

        tables = push(tables, table);
    }

    // menü betöltése
    ListItem *menu = loadMenu();

    // a menü még nem lett létrehozva
    if (menu == NULL) {
        printWelcome();

        // új menü elem hozzáadása
        printf(REQUEST "Kérem adjon hozzá legalább egy elemet a menühöz:\n" RESET);
        MenuItem *menuItem = requestMenuItem();

        menu = push(menu, menuItem);
    }

    // rendelések betöltése
    ListItem *orders = loadOrders();

    // command mode
    if (argc > 1) {
        if (strcmp(argv[1], "nyitasztal") == 0 && verifyArgc(argc, 1))
            tables = openTable(atoi(argv[2]) - 1, tables);
        else if (strcmp(argv[1], "ujasztal") == 0 && verifyArgc(argc, 3))
            tables = newTable(
                    atoi(argv[3]),
                    atoi(argv[4]),
                    atoi(argv[2]),
                    tables
            );
        else if (strcmp(argv[1], "asztalterkep") == 0) {

        } else if (strcmp(argv[1], "menu") == 0)
            printMenu(menu);
        else if (strcmp(argv[1], "ujetel") == 0)
            menu = newMenuItem(
                argv[2],
                atoi(argv[3]),
                menu
            );
        else if (strcmp(argv[1], "toroletel") == 0) {

        } else if (strcmp(argv[1], "rendel") == 0) {

        } else if (strcmp(argv[1], "szamla") == 0) {

        } else
            printf(ERROR "Ez a parancs nem létezik (%s).\n" RESET, argv[1]);
    }
    // GUI mode
    else {

    }

    // mentés
    saveTables(tables);
    saveMenu(menu);
    saveOrders(orders);

    // cleanup
    freeMenu(menu);
    freeList(tables);
    freeList(orders);

    return 0;
}
