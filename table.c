#include <stdbool.h>

/**
 * Az asztalok struktúrája
 **/
typedef struct Table {
    /** Asztal elhelyezhekdése **/
    int x, y;
    /** Hány ember fél el az asztalnál **/
    int capacity;
    /** Foglalt-e az asztal **/
    bool occupied;
} Table;

