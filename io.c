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

bool welcomePrinted = false;

/**
 * Kiírja a program nevét
 */
void printWelcome() {
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
 */
MenuItem requestMenuItem() {
    // név
    printf("Étel neve: ");
    char *name = readStringLine();

    // ár
    printf("Ár (Ft - forint): " INPUT);
    int price;
    scanf("%d\n", &price);
    printf(RESET);

    return (MenuItem) {
        name,
        price
    };
}

/**
 * Elkér a felhasználótól egy új asztalt
 */
Table requestTable() {
    // hely
    printf("Elhelyezkedés (x y): " INPUT);
    int x, y;
    scanf("%d %d\n", &x, &y);
    printf(RESET);

    // kapacitás
    printf("Kapacitás (hány fő fér el): " INPUT);
    int capacity;
    scanf("%d\n", &capacity);
    printf(RESET);

    return (Table) {
            x, y, capacity, false
    };
}
