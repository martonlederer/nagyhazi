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
           " |_____|\\__|\\__\\___|_|  \\___|_| |_| |_|  |_(_)___/\n");
}

/**
 * Beolvas egy stringet, dinamikusan az "end" karakterig
 * @param end Karakter amit már nem szabad beolvasni
 * @return A beolvasott string
 */
char *readString(char end) {
    typedef struct DinString {
        char *data;
        int size;
    } DinString;

    DinString str = {
            malloc(sizeof(char)),
            1
    };
    str.data[0] = '\0';

    char curr_char;
    char *old_string = str.data;

    // leolvassuk az összes karaktert
    while (scanf("%c", &curr_char) == 1 && curr_char != end && str.size == 1) {
        // str növelés
        old_string = str.data;
        str.data = malloc((str.size + 1) * sizeof(char));

        // karaktermásolás
        for (int i = 0; i < str.size; i++)
            str.data[i] = old_string[i];

        // felszabadítás
        free(old_string);

        // új karakter hozzáadása
        str.data[str.size - 1] = curr_char;
        str.data[str.size] = '\0';
        str.size++;
    }

    return str.data;
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
    printf("Ár (Ft - forint): " REQUEST);
    int price;
    scanf("%d", &price);
    printf(RESET);

    return (MenuItem) {
        name,
        price
    };
}
