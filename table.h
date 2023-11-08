#ifndef NAGYHAZI_TABLE_H
#define NAGYHAZI_TABLE_H

#include "debugmalloc.h"
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

#endif
