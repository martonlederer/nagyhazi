#include <stdio.h>
#include "io.h"
#include "gui.h"

/**
 * Választható menüpontok
 */
char menus[9][80] = {
        "Új asztal nyitása",
        "Rendelés hozzáadása",
        "Számlanyomtatás - asztal lezárása",
        "Foglalt/szabad asztalok térképének megjelenítése",
        "Menü megjelenítése",
        "Étel hozzáadása a menühöz",
        "Étel eltávolítása a menüből",
        "Asztal hozzáadása",
        "Kilépés"
};

/**
 * Megjeleníti a "grafikus" felhasználói menüt,
 * majd beolvassa a kiválasztott operációt
 * @return A kiválasztott operáció száma
 */
int showAndChooseMenu() {
    // menü megjelenítése
    printWelcome();
    printf(REQUEST "Kérem válasszon az alábbi menüpontok közül:\n" RESET);

    // menüpontok
    for (int i = 0; i < 9; i++) {
        printf("(%d) %s\n", i + 1, menus[i]);
    }

    // választott opció beolvasása
    printf(REQUEST "\n");
    int selected;

    // ellenőrzés
    if (scanf("%d", &selected) != 1 || selected > 9 || selected < 1) {
        printf(ERROR "Nem létező menüpont lett kiválasztva.\n" RESET);
        return showAndChooseMenu();
    }

    printf(RESET);

    // választott menü kiírása
    if (selected != 9)
        printf(REQUEST "%s:\n" RESET, menus[selected - 1]);

    return selected;
}
