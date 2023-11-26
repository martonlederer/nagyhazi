#include <stdio.h>
#include "io.h"
#include "gui.h"
#include "order.h"
#include "table.h"

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

    // a különböző esetekhez szükséges a kapcsos zárójelekkel
    // való blokkokra bontás, hogy újra lehessen deklarálni
    // az adott változókat ugyan azzal a névvel
    switch (selected) {
        case 1: {
            // beolvassuk az asztal számát
            printf("Az asztal száma: ");
            int tableIndex;
            scanf("%d", &tableIndex);

            // asztal megnyitása
            tableList = openTable(tableIndex - 1, tableList);
        } break;

        case 2: {
            // menü elem és asztal számának beolvasása
            printf("Az étel menün szereplő száma: ");
            int menuIndex;
            scanf("%d", &menuIndex);

            printf("Az asztal száma: ");
            int tableIndex;
            scanf("%d", &tableIndex);

            // új rendelés
            orderList = orderNewItem(
                menuIndex,
                tableIndex,
                menuList,
                tableList,
                orderList
            );
        } break;

        case 3: {
            // asztal számának beolvasása
            printf("Az asztal száma: ");
            int tableIndex;
            scanf("%d", &tableIndex);

            // számlázás
            BillResult billRes = issueBill(
                tableIndex,
                menuList,
                tableList,
                orderList
            );

            // frissítjük a listákat
            tableList = billRes.tableList;
            orderList = billRes.orderList;
        } break;

        case 4:
            // asztal térkép nyomtatása
            printTableMap(tableList);
            break;

        case 5:
            // menü megjelenítése
            printMenu(menuList);
            break;

        case 6: {
            // beolvassuk a nevet és az árat
            printf("Új étel neve: ");
            char *name = readStringLine();

            printf("Új étel ára: ");
            int price;
            scanf("%d", &price);

            // hozzáadás a menü listához
            menuList = newMenuItem(
                name,
                price,
                menuList
            );
        } break;

        case 7: {
            // beolvassuk a menü elem indexét
            printf("Étel száma a menün: ");
            int index;
            scanf("%d", &index);

            // kiszedjük a menü listából
            menuList = removeMenuItem(index, menuList);
        } break;

        case 8: {
            // beolvassuk az új asztal adatait
            printf("Elhelyezkedés (x y): ");
            int x, y;
            scanf("%d %d", &x, &y);

            printf("Kapacitás (hány fő fér el): ");
            int capacity;
            scanf("%d", &capacity);

            // hozzáadjuk az asztal láncolt listához
            tableList = newTable(
                x,
                y,
                capacity,
                tableList
            );
        } break;

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
