#include "linkedlist.h"
#include "order.h"

/**
 * A rendelések betöltését elvégző funkció
 * @param list A rendelések láncolt listájának első elemére mutató pointer
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
