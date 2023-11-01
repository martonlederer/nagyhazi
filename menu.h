//
// Created by Marton Lederer on 01/11/2023.
//

#ifndef NAGYHAZI_MENU_H
#define NAGYHAZI_MENU_H

#include <stdio.h>
#include <stdlib.h>

/**
 * A menün szereplő étel struktúrája
 */
typedef struct MenuItem {
    char *name;
    int price;
    struct MenuItem *next;
} MenuItem;

/**
 * A menü láncolt listához ad elemet
 * @param list Láncolt lista első elemére mutató pointer
 * @param item Új elem
 */
void addToMenu(MenuItem *list, MenuItem *item);

/**
 * A menü betöltését elvégző funkció
 * @param firstItem A menü láncolt listájának első elemére mutató pointer
 */
void loadMenu(MenuItem *firstItem);

#endif NAGYHAZI_MENU_H
