#ifndef NAGYHAZI_ORDER_H
#define NAGYHAZI_ORDER_H

#include "linkedlist.h"

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
 */
ListItem *loadOrders();

/**
 * A rendelések elmentését végző funkció
 * @param list A rendelések láncolt listájának első elemére mutató pointer
 */
void saveOrders(ListItem *list);

#endif
