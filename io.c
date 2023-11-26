#include <stdio.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "menu.h"
#include "table.h"
#include "io.h"

/**
 * Kiírja a program nevét
 */
void printWelcome() {
    static bool welcomePrinted;

    if (welcomePrinted) return;
    welcomePrinted = true;

    printf("    __  _   _                            __   ___  \n"
           "  _/_/_| | | |                          /_ | / _ \\ \n"
           " | ____| |_| |_ ___ _ __ ___ _ __ ___    | || | | |\n"
           " |  _| | __| __/ _ \\ '__/ _ \\ '_ ` _ \\   | || | | |\n"
           " | |___| |_| ||  __/ | |  __/ | | | | |  | || |_| |\n"
           " |_____|\\__|\\__\\___|_|  \\___|_| |_| |_|  |_(_)___/\n\n");

    printf(REQUEST "Üdvözlöm! " RESET);
}

/**
 * Beolvas egy stringet, dinamikusan az "end" karakterig
 * @param end Karakter amit már nem szabad beolvasni
 * @return A beolvasott string
 */
char *readString(char end) {
    // string memória és méret
    char *data = (char*) malloc(sizeof(char));
    int size = 1;
    *data = '\0';

    // az éppen beolvasott char
    char curr_char;

    // leolvassuk az összes karaktert
    while (scanf("%c", &curr_char) == 1 && curr_char != end) {
        // str növelés
        data = (char*) realloc(data, (size + 1) * sizeof(char));

        // karaktermásolás
        char charstring[2] = { curr_char, '\0' };
        strcat(data, charstring);

        size++;
    }

    return data;
}

/**
 * Beolvas egy stringet, dinamikusan a következő sorig
 * @return A beolvasott string
 */
char *readStringLine() {
    return readString('\n');
}

/**
 * Elkér a felhasználótól egy új elemet a menüre
 * @returns A felhasználó által megadott új étel
 */
MenuItem *requestMenuItem() {
    // név
    printf("Étel neve: ");
    char *name = readStringLine();

    // ár
    printf("Ár (Ft - forint): " INPUT);
    int price;
    scanf("%d", &price);
    printf(RESET);

    // dinamikusan foglaljuk le, mert a
    // láncolt lista csak így tudja kezelni
    // a végén (felszabadítani)
    MenuItem *item = (MenuItem*) malloc(sizeof(MenuItem));
    *item = (MenuItem) {
        name,
        price
    };

    return item;
}

/**
 * Elkér a felhasználótól egy új asztalt
 * @returns A felhasználó által megadott asztal
 */
Table *requestTable() {
    // hely
    printf("Elhelyezkedés (x y): " INPUT);
    int x, y;
    scanf("%d %d", &x, &y);
    printf(RESET);

    // kapacitás
    printf("Kapacitás (hány fő fér el): " INPUT);
    int capacity;
    scanf("%d", &capacity);
    printf(RESET);

    // dinamikusan foglaljuk le, mert a
    // láncolt lista csak így tudja kezelni
    // a végén (felszabadítani)
    Table *table = (Table*) malloc(sizeof(Table));
    *table = (Table) {
        x, y, capacity, false
    };

    return table;
}

/**
 * Ellenőrzi a CLI argumentumokat
 *
 * @param argc Arg szám
 * @param requested Elvárt szám
 * @return Helyes vagy helytelen az argc
 */
bool verifyArgc(int argc, int requested) {
    if (argc - 2 == requested)
        return true;

    printf(ERROR "Ehhez a parancshoz %d argumentum szükséges", requested);
    return false;
}

/**
 * Készít egy szóközökből álló stringet, amivel
 * ugyan annyi helyet lehet kihagyni a konzolban
 * stringek között. A visszatért pointert később
 * fel kell szabadítani.
 * @param strlen A konzolban megjelenő többi string hossza együtt
 * @param linelen A sor teljes hossza, a szóköz karakterekkel együtt
 * @return Szóközökből álló string
 */
char *equalSpace(unsigned long strlen, unsigned long linelen) {
    // ennyiszer kell ismételni a szóköz karaktert
    unsigned long spaceCount = linelen - strlen;

    // létrehozzuk a stringet
    char *str = (char*) malloc(sizeof(char) * (spaceCount + 1));
    *str = '\0';

    while (spaceCount > 0) {
        strcat(str, " ");
        spaceCount--;
    }

    return str;
}

/**
 * Kiszámolja egy integer stringbe convertált hosszúságát
 * @param num Az integer
 * @return Hossz
 */
size_t istrlen(int num) {
    size_t len = 0;

    // nullát külön kell kezelni
    if (num == 0) len = 1;

    while (num > 0) {
        len++;
        num /= 10;
    }

    return len;
}
