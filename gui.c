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
    scanf("%d", &selected);
    printf(RESET);

    return selected;
}

/**
 * Elkéri a felhasználótól egy asztal számát
 * @return Asztal indexe
 */
int getTableIndex() {
    int tableIndex;

    printf("Az asztal száma: ");
    scanf("%d", &tableIndex);

    return tableIndex - 1;
}

/**
 * Elkéri a felhasználótól egy menün szereplő étel számát
 * @return Menü elem indexe
 */
int getMenuItemIndex() {
    int menuIndex;

    printf("Az étel menün szereplő száma: ");
    scanf("%d", &menuIndex);

    return menuIndex - 1;
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
    if (selected >= 1 && selected <= 8)
        printf(REQUEST "%s:\n" RESET, menus[selected - 1]);

    // a különböző esetekhez szükséges a kapcsos zárójelekkel
    // való blokkokra bontás, hogy újra lehessen deklarálni
    // az adott változókat ugyan azzal a névvel
    switch (selected) {
        case 1: {
            // beolvassuk az asztal számát
            int tableIndex = getTableIndex();

            // asztal megnyitása
            tableList = openTable(tableIndex, tableList);
        } break;

        case 2: {
            // menü elem és asztal számának beolvasása
            int menuIndex = getMenuItemIndex();
            int tableIndex = getTableIndex();

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
            int tableIndex = getTableIndex();

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
            // empty scanf
            char _;
            scanf("%c", &_);

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

            // felszabadítjuk a din nevet, hiszen azt már lemásoltuk
            free(name);
        } break;

        case 7: {
            // beolvassuk a menü elem indexét
            int menuIndex = getMenuItemIndex();

            // kiszedjük a menü listából
            menuList = removeMenuItem(menuIndex, menuList);
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
