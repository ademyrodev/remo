// Will take care of memory for us - allocations and all the good
// stuff.
#include "common.h"
#include <stdlib.h>

// Useful macros.
#define DOUBLE_SIZE(oldSize) \
  (((oldSize) == 0) ? 8 : ((oldSize) * 2))

#define ALLOCATE_ARRAY(type, size, array) \
  (type *) reallocate((array), (sizeof (type) * (size)))

// This doesn't need to be a macro, but it would feel out of place
// if it didn't.

#define FREE(array) \
  reallocate((array), (0))

// We have our own 'reallocate' function that will be used instead
// of stdlib functions. To free stuff, we'll use reallocate(array, 0).

void *reallocate(void *, size_t);


