#ifndef NAGYHAZI_GUI_H
#define NAGYHAZI_GUI_H

#include <stdio.h>
#include "io.h"

/**
 * Megjeleníti a "grafikus" felhasználói menüt,
 * majd beolvassa a kiválasztott operációt
 * @return A kiválasztott operáció száma
 */
int showAndChooseMenu();

/**
 * Asztal, menü és rendelés láncolt listák
 * összetett struktúrája. Az ilyen típusú
 * változókban három pointer található, melyek
 * láncolt listák fejére mutatnak. Csak a grafikus
 * menü kezelő funkciójához szükséges.
 */
typedef struct GuiHandleResult {
    /**
     * A menü láncolt lista fejére mutató pointer
     */
    ListItem *menuList;
    /**
     * Az asztal láncolt lista fejére mutató pointer
     */
    ListItem *tableList;
    /**
     * A rendelés láncolt lista fejére mutató pointer
     */
    ListItem *orderList;
} GuiHandleResult;

/**
 * Kezeli a kiválasztott menüpontot, meghívja a
 * hozzá tartozó segédfunkciókat, kiírja és bekéri
 * a szükséges adatokat.
 * @param selected A kiválasztott menüpont száma
 * @param menuList Menü láncolt lista
 * @param tableList Asztal láncolt lista
 * @param orderList Rendelés láncolt lista
 * @returns Új menü, asztal és rendelés láncolt listák
 * fejei egy összetett struktúrában
 */
GuiHandleResult handleMenu(
        int selected,
        ListItem *menuList,
        ListItem *tableList,
        ListItem *orderList
);

#endif
