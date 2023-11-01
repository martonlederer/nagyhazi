#include <stdio.h>
#include "menu.h"

int main(int argc, char **argv) {
    MenuItem *menu = (MenuItem*) malloc(sizeof(MenuItem));

    *menu = (MenuItem) {
        "Teszt",
        15,
        NULL
    };
    MenuItem kett = {
            "Teszt2",
            15,
            NULL
    };

    addToMenu(menu, &kett);

    printf("%s %s", menu->name, menu->next->name);
    saveMenu(menu);
    freeMenu(menu);

    // TODO: init program setup
    // request initial data:
    // - at least one table with its data
    // - at least one item on the menu
    // after that
    // - save given data (by default all tables are unoccupied)

    // TODO: switch/case for cmd arguments

    return 0;
}
