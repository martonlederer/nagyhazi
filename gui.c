#include <stdio.h>
#include "io.h"
#include "gui.h"

/**
 * Választható menüpontok
 */
char menus[9][80] = {
    "Új asztal nyitása",
    "Rendelés hozzáadása",
    "Számlanyomtatás - asztal lezárása",
    "Foglalt/szabad asztalok térképének megjelenítése",
    "Menü megjelenítése",
    "Étel hozzáadása a menühöz",
    "Étel eltávolítása a menüből",
    "Asztal hozzáadása",
    "Kilépés"
};

/**
 * Megjeleníti a "grafikus" felhasználói menüt,
 * majd beolvassa a kiválasztott operációt
 * @return A kiválasztott operáció száma
 */
int showAndChooseMenu() {
    // menü megjelenítése
    printWelcome();
    printf(REQUEST "Kérem válasszon az alábbi menüpontok közül:\n" RESET);

    // menüpontok
    for (int i = 0; i < 9; i++) {
        printf("(%d) %s\n", i + 1, menus[i]);
    }

    // választott opció beolvasása
    printf(REQUEST "\n");
    int selected;

    // ellenőrzés
    if (scanf("%d", &selected) != 1 || selected > 9 || selected < 1) {
        printf(ERROR "Nem létező menüpont lett kiválasztva.\n" RESET);
        return showAndChooseMenu();
    }

    printf(RESET);

    return selected;
}

/**
 * Kezeli a kiválasztott menüpontot, meghívja a
 * hozzá tartozó segédfunkciókat, kiírja és bekéri
 * a szükséges adatokat.
 * @param selected A kiválasztott menüpont száma
 * @param menuList Menü láncolt lista
 * @param tableList Asztal láncolt lista
 * @param orderList Rendelés láncolt lista
 * @returns Új menü, asztal és rendelés láncolt listák
 * fejei egy összetett struktúrában
 */
GuiHandleResult handleMenu(
    int selected,
    ListItem *menuList,
    ListItem *tableList,
    ListItem *orderList
) {
    // alap érték
    GuiHandleResult res = {
        menuList,
        tableList,
        orderList
    };

    // kilépés
    if (selected == 9)
        return res;

    // választott menü kiírása
    printf(REQUEST "%s:\n" RESET, menus[selected - 1]);

    switch (selected) {
        case 1:
            printf("Az asztal száma: ");
            int tableIndex;
            scanf("%d", &tableIndex);
            tableList = openTable(tableIndex - 1, tableList);

            break;

        default:
            printf(ERROR "A menüpont nem található.\n" RESET);
    }

    // frissítjük az eredmény változó pointereit
    res.menuList = menuList;
    res.tableList = tableList;
    res.orderList = orderList;

    // visszatérés
    return res;
}
