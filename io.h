#ifndef NAGYHAZI_IO_H
#define NAGYHAZI_IO_H

#include <stdio.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "menu.h"
#include "table.h"

// forrás: https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a

#define ERROR   "\x1B[31m"
#define SUCCESS "\x1B[32m"
#define REQUEST "\x1B[33m"
#define INPUT   "\x1B[35m"
#define BOLD    "\x1B[1m"

#define RESET   "\x1B[0m"

/**
 * Kiírja a program nevét
 */
void printWelcome();

/**
 * Beolvas egy stringet, dinamikusan az "end" karakterig
 * @param end Karakter amit már nem szabad beolvasni
 * @return A beolvasott string
 */
char *readString(char end);

/**
 * Beolvas egy stringet, dinamikusan a következő sorig
 * @return A beolvasott string
 */
char *readStringLine();

/**
 * Elkér a felhasználótól egy új elemet a menüre
 * @returns A felhasználó által megadott új étel
 */
MenuItem *requestMenuItem();

/**
 * Elkér a felhasználótól egy új asztalt
 * @returns A felhasználó által megadott asztal
 */
Table *requestTable();

/**
 * Ellenőrzi a CLI argumentumokat
 *
 * @param argc Arg szám
 * @param requested Elvárt szám
 * @return Helyes vagy helytelen az argc
 */
bool verifyArgc(int argc, int requested);

/**
 * Készít egy szóközökből álló stringet, amivel
 * ugyan annyi helyet lehet kihagyni a konzolban
 * stringek között. A visszatért pointert később
 * fel kell szabadítani.
 * @param strlen A konzolban megjelenő többi string hossza együtt
 * @param linelen A sor teljes hossza, a szóköz karakterekkel együtt
 * @return Szóközökből álló string
 */
char *equalSpace(unsigned long strlen, unsigned long linelen);

/**
 * Kiszámolja egy integer stringbe convertált hosszúságát
 * @param num Az integer
 * @return Hossz
 */
size_t istrlen(int num);

#endif
