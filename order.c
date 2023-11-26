#include "linkedlist.h"
#include "order.h"
#include "io.h"

/**
 * A rendelések betöltését elvégző funkció
 * @param list A rendelések láncolt listájának első elemére mutató pointer
 * @returns A betöltött lista
 */
ListItem *loadOrders() {
    FILE *f = fopen("./orders.txt", "r");

    // a fájl nem létezik
    if (f == NULL) return NULL;

    // aktuális elem
    ListItem *list = NULL;
    Order curr;

    while(fscanf(f, "%d\t%d\n", &curr.food, &curr.table) == 4) {
        // dinamikusan foglaljuk le, mert a
        // láncolt lista csak így tudja kezelni
        // a végén (felszabadítani)
        Order *order = (Order*) malloc(sizeof(Order));
        *order = curr;

        // hozzáadjuk a listához
        list = push(list, order);
    }

    // fájl bezárása
    fclose(f);

    return list;
}

/**
 * A rendelések elmentését végző funkció
 * @param list A rendelések láncolt listájának első elemére mutató pointer
 */
void saveOrders(ListItem *list) {
    FILE *f = fopen("./orders.txt", "w");
    ListItem *current = list;

    if (f == NULL) {
        perror("Hiba volt a rendelések fájl megnyitása közben.");
        return;
    }

    // végigmegyünk a láncolt listán
    while (current != NULL) {
        // beírjuk a fájl egy új sorába a rendelést
        Order *order = (Order*) current->data;
        fprintf(f, "%d\t%d\n", order->food, order->table);

        // következő elemre megyünk
        current = current->next;
    }

    fclose(f);
}

/**
 * Étel rendelésének felvételét elvégző funkció
 * @param menuItemIndex A rendelt étel menü elemének indexe
 * @param tableIndex A rendeléshez tartozó asztal indexe
 * @param menuList Menü láncolt lista
 * @param tableList Asztal láncolt lista
 * @param orderList Rendelés láncolt lista
 * @return Új rendelés láncolt lista feje
 */
ListItem *orderNewItem(
    int menuItemIndex,
    int tableIndex,
    ListItem *menuList,
    ListItem *tableList,
    ListItem *orderList
) {
    // megkeressüt az ételt
    ListItem *menuItem = getItemByIndex(menuList, menuItemIndex);

    // ha a menu_curr iterátor NULL pointer, akkor
    // az index alatt nem található étel
    if (menuItem == NULL) {
        printf(ERROR "Nem található étel ezzel az index-szel: %d.\n" RESET, menuItemIndex);
        return orderList;
    }

    // megkeressük az asztalt
    ListItem *tableItem = getItemByIndex(tableList, tableIndex);

    // hasonlóan az előzőhöz, a NULL ptr azt jelenti,
    // hogy nem létezik az asztal
    if (tableItem == NULL) {
        printf(ERROR "Nem található asztal ezzel az index-szel: %d.\n" RESET, tableIndex);
        return orderList;
    }

    // ha nem foglalt az asztal, akkor
    // nincsen megnyitva, így nem lehet felvenni
    // a rendelést
    Table *table = (Table*) tableItem->data;

    if (!table->occupied) {
        printf(ERROR "Ez az asztal még nincsen megnyitva. A rendelést nem lehet felvenni.\n" RESET);
        printf(REQUEST "Tipp: az asztal megnyitható az \"etterem nyitasztal <asztalindex>\" paranccsal.\n" RESET);
        return orderList;
    }

    // dinamikusan megadjuk a rendelést, hogy később
    // egységesen felszabadítható legyen a lista
    Order *order = (Order*) malloc(sizeof(Order));
    *order = (Order) {
        tableIndex,
        menuItemIndex
    };

    // berakjuk a rendelést a listába
    push(orderList, order);

    // kiírjuk, hogy a rendelés sikeres volt
    MenuItem *food = (MenuItem*) menuItem->data;

    printf(SUCCESS "%s hozzáadva a rendeléshez.\n" RESET, food->name);

    // visszaadjuk a listát
    return orderList;
}
