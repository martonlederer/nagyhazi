//
// Created by Marton Lederer on 01/11/2023.
//

#ifndef NAGYHAZI_MENU_H
#define NAGYHAZI_MENU_H

#include <stdio.h>
#include "debugmalloc.h"
#include "linkedlist.h"

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
ListItem *loadMenu();

/**
 * A menü elmentését végző funkció
 * @param list A menü láncolt listájának első elemére mutató pointer
 */
void saveMenu(ListItem *list);

/**
 * Felszabadítja a menü listát és az ételek neveit
 */
void freeMenu(ListItem *list);

/**
 * Kiírja a menü lista elemeit
 * @param list Menü láncolt lista
 */
void printMenu(ListItem *list);

/**
 * Hozzáad egy új elemet a menühöz
 * @param name Új étel neve
 * @param price Új étel ára
 * @param list Menü láncolt lista
 * @returns Új menü lista
 */
ListItem *newMenuItem(char *name, int price, ListItem *list);

#endif