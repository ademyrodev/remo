// Types of values
#include "common.h"
#include "mem.h"

typedef double Value; 

typedef struct {
  Value *values;
  int size;
  int used;
} ValueArray;

// Initializes a ValueArray's state.
void allocValueArray(ValueArray *);

void addToValueArray(ValueArray *, Value);

void freeValueArray(ValueArray *);

// Displays a value.
void logValue(Value);
