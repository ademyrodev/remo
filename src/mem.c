#include "mem.h"

void *reallocate(void *ptr, size_t size) {
  if (size == 0) {
    // We will free 'ptr'
    free(ptr);
    return NULL;
  } 

  void *reallocated = realloc(ptr, size);
  return reallocated;
}
