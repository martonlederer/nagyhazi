#ifndef NAGYHAZI_TABLE_H
#define NAGYHAZI_TABLE_H

#include "linkedlist.h"

/**
 * Az asztalok struktúrája
 */
typedef struct Table {
    /** Asztal elhelyezhekdése **/
    int x, y;
    /** Hány ember fél el az asztalnál **/
    int capacity;
    /** Foglalt-e az asztal **/
    bool occupied;
} Table;

/**
 * Az asztalok betöltését elvégző funkció
 * @param list Az asztal láncolt listájának első elemére mutató pointer
 */
ListItem *loadTables();

/**
 * Az asztalok elmentését végző funkció
 * @param list Az asztal láncolt listájának első elemére mutató pointer
 */
void saveTables(ListItem *list);

/**
 * Új asztalt nyit vendégek számára
 * @param index Az asztal indexe
 * @param tableList Asztal láncolt lista
 * @returns Új asztal lista
 */
ListItem *openTable(int index, ListItem *tableList);

/**
 * Új asztalt nyit vendégek számára
 * @param index Az asztal indexe
 * @param tableList Asztal láncolt lista
 * @returns Új asztal lista
 */
ListItem *setTableOccupied(int index, ListItem *tableList, bool occupied);

#endif
