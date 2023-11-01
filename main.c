#include <stdio.h>
#include "menu.h"

int main(int argc, char *argv[]) {
    MenuItem *menu = (MenuItem*) malloc(sizeof(MenuItem));
    loadMenu(menu);
    printf("%s %d", menu->name, menu->price);

    // TODO: init program setup
    // request initial data:
    // - at least one table with its data
    // - at least one item on the menu
    // after that
    // - save given data (by default all tables are unoccupied)

    // TODO: switch/case for cmd arguments

    return 0;
}
