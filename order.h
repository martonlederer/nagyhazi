#ifndef NAGYHAZI_ORDER_H
#define NAGYHAZI_ORDER_H

#include "linkedlist.h"
#include "io.h"

/**
 * A rendelések struktúrája
 */
typedef struct Order {
    /** Az asztal indexe **/
    int table;
    /** Az étel indexe **/
    int food;
} Order;

/**
 * A rendelések betöltését elvégző funkció
 * @param list A rendelések láncolt listájának első elemére mutató pointer
 * @returns A betöltött lista
 */
ListItem *loadOrders();

/**
 * A rendelések elmentését végző funkció
 * @param list A rendelések láncolt listájának első elemére mutató pointer
 */
void saveOrders(ListItem *list);

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
);

#endif
