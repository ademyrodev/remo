#include <stdio.h>
#include "value.h"
#include "mem.h"
#include "common.h"

void allocValueArray(ValueArray *array) {
  // Fresh, zeroed state.
  array->values = NULL;
  array->size = 0;
  array->used = 0;
}

void addToValueArray(ValueArray *array, Value value) {
  if (array->size <= array->used) {
    // Grow our array.
    array->size = DOUBLE_SIZE(array->size);
    array->values = ALLOCATE_ARRAY(Value, 
        array->size, array->values);
  }

  // Append a value to the array
  array->values[array->used++] = value;
}

void freeValueArray(ValueArray *array) {
  // Free anything that has been allocated:
  FREE(array->values);

  // Zero everything out
  allocValueArray(array);
}

void logValue(Value value) {
  // For now, we will only output a double - we only have this
  // value type.
  printf("%g", value);
}
