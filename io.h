#ifndef NAGYHAZI_IO_H
#define NAGYHAZI_IO_H

#include <stdio.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "menu.h"

// forrás: https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a

#define ERROR   "\x1B[31m"
#define SUCCESS "\x1B[32m"
#define REQUEST "\x1B[33m"
#define INPUT   "\x1B[35m"
#define BOLD    "\x1B[1m"

#define RESET   "\x1B[0m"

bool welcomePrinted;

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
 */
MenuItem requestMenuItem();

#endif
