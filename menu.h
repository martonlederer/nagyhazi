//
// Created by Marton Lederer on 01/11/2023.
//

#ifndef NAGYHAZI_MENU_H
#define NAGYHAZI_MENU_H

#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"

/**
 * A menün szereplő étel struktúrája
 */
typedef struct MenuItem {
    char *name;
    int price;
} MenuItem;

/**
 * A menü betöltését elvégző funkció
 * @param list A menü láncolt listájának első elemére mutató pointer
 */
void loadMenu(MenuItem *list);

/**
 * A menü elmentését végző funkció
 * @param list A menü láncolt listájának első elemére mutató pointer
 */
void saveMenu(MenuItem *list);

#endif