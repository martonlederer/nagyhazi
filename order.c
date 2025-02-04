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

    while(fscanf(f, "%d\t%d\n", &curr.food, &curr.table) == 2) {
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
        printf(ERROR "Nem található étel ezzel az index-szel: %d.\n" RESET, menuItemIndex + 1);
        return orderList;
    }

    // megkeressük az asztalt
    ListItem *tableItem = getItemByIndex(tableList, tableIndex);

    // hasonlóan az előzőhöz, a NULL ptr azt jelenti,
    // hogy nem létezik az asztal
    if (tableItem == NULL) {
        printf(ERROR "Nem található asztal ezzel az index-szel: %d.\n" RESET, tableIndex + 1);
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
    orderList = push(orderList, order);

    // kiírjuk, hogy a rendelés sikeres volt
    MenuItem *food = (MenuItem*) menuItem->data;

    printf(SUCCESS "%s hozzáadva a rendeléshez.\n" RESET, food->name);

    // visszaadjuk a listát
    return orderList;
}

/**
 * Számla generálása, kiírása és asztal lezárása. A funkció
 * törli az összes rendelést az asztalhoz a számlázás után
 * @param tableIndex Az asztal indexe
 * @param menuList Menü láncolt lista
 * @param tableList Asztal láncolt lista
 * @param orderList Rendelés láncolt lista
 * @return Új rendelés- és asztal láncolt listák fejei egy
 * a összetett belőlük összetett struktúrában.
 */
BillResult issueBill(
    int tableIndex,
    ListItem *menuList,
    ListItem *tableList,
    ListItem *orderList
) {
    // eredmény változó, amit később frissítünk, ha
    // bármelyik láncolt listán változtatunk
    BillResult res;
    res.tableList = tableList;
    res.orderList = orderList;

    // megkeressük az asztalt
    ListItem *tableItem = getItemByIndex(tableList, tableIndex);

    // nem találtuk meg az asztalt
    if (tableItem == NULL) {
        printf(ERROR "Nem található asztal ezzel az index-szel: %d.\n" RESET, tableIndex + 1);
        return res;
    }

    // ha nem foglalt az asztal, akkor
    // nincsen megnyitva, így nem lehet felvenni
    // a rendelést
    Table *table = (Table*) tableItem->data;

    if (!table->occupied) {
        printf(ERROR "Ez az asztal még nincsen megnyitva. Nem lehet számlát generálni..\n" RESET);
        return res;
    }

    // számla kiírása
    printf("Számla:\n\n");

    // összesen mennyibe került
    int total = 0;
    ListItem *curr_order = orderList;

    while (curr_order != NULL) {
        Order *order = (Order*) curr_order->data;

        // ha nem ehhez az asztalhoz tartozik az elem, továbbmegyünk
        if (order->table != tableIndex) {
            curr_order = curr_order->next;

            continue;
        }

        // megkeressük az ételt a menün
        ListItem *menuItem = getItemByIndex(menuList, order->food);
        MenuItem *item = (MenuItem*) menuItem->data;

        // hozzáadjuk a teljes összeghez
        total += item->price;

        // hely kihagyása a név és az ár között
        char *space = equalSpace(strlen(item->name) + istrlen(item->price), 40);

        // kiírjuk
        printf("%s %s " REQUEST "%d" RESET " Ft\n", item->name, space, item->price);

        // hely string felszabadítása
        free(space);

        // következő
        curr_order = curr_order->next;
    }

    // kiírjuk a teljes árat
    char *space = equalSpace(istrlen(total) + 13, 40);
    printf("---\nÖsszesen: %s " REQUEST "%d" RESET " Ft\n", space, total);

    free(space);

    // külön töröljük a rendeléseket
    curr_order = orderList;
    ListItem *previous_order = NULL;

    while (curr_order != NULL) {
        ListItem *next = curr_order->next;
        Order *order = (Order*) curr_order->data;

        // itt nem használhatjuk a "removeItem" funkciót
        // mert az akár új indexet is oszthat a lista
        // összes elemének, így itt helyben kell kivenni
        // az elemet a listából
        if (order->table != tableIndex || previous_order == NULL)
            previous_order = curr_order;

        if (order->table == tableIndex) {
            previous_order->next = next;

            // ha az első elemet töröljük, akkor az orderList-et
            // is módosítani kell
            if (orderList == curr_order)
                orderList = next;

            // felszabadítás
            free(order);
            free(curr_order);
        }

        curr_order = next;
    }

    // lezárjuk az asztalt
    res.tableList = setTableOccupied(tableIndex, tableList, false);
    res.orderList = orderList;

    return res;
}
