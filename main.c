#include "debugmalloc.h"
#include "linkedlist.h"
#include "menu.h"
#include "io.h"
#include "table.h"

int main(int argc, char **argv) {
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
        saveMenu(menu);
    }

    // TODO: switch/case for cmd arguments

    // cleanup
    freeMenu(menu);

    return 0;
}
