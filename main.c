#include "debugmalloc.h"
#include "linkedlist.h"
#include "menu.h"
#include "io.h"
#include "table.h"
#include "order.h"

int main(int argc, char **argv) {
    // TODO: LABORON MEGKÉRDEZNI
    // - miért nincs meg a szorgalmi pontom (pontversenyben látszik, hogy csak egy van meg, kerítés feladat nincs ott)
    // - debugmallocnál szabad felszabadítani nem lefoglalt helyet?

    // TODO: init program setup
    // request initial data:
    // - at least one table with its data
    // - at least one item on the menu
    // after that
    // - save given data (by default all tables are unoccupied)

    // asztalok betöltése
    ListItem *tables = loadTables();

    if (tables == NULL) {
        printWelcome();

        // új asztal megadása
        printf(REQUEST "Kérem adja meg az étterem min. egy asztalát:\n" RESET);
        Table table = requestTable();

        tables = push(tables, &table);
        saveTables(tables);
    }

    // menü betöltése
    ListItem *menu = loadMenu();

    // a menü még nem lett létrehozva
    if (menu == NULL) {
        printWelcome();

        // új menü elem hozzáadása
        printf(REQUEST "Kérem adjon hozzá legalább egy elemet a menühöz:\n" RESET);
        MenuItem menuItem = requestMenuItem();

        menu = push(menu, &menuItem);
        saveMenu(menu);
    }

    // rendelések betöltése
    ListItem *orders = loadOrders();

    // TODO: switch/case for cmd arguments
    // TODO: save tables, menu, orders

    // cleanup
    freeMenu(menu);
    freeList(tables);
    freeList(orders);

    return 0;
}
