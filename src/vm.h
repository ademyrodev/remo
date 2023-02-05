#ifndef VM_H
#define VM_H

// The mighty machine that executes our code!
#include "common.h"
#include "value.h"
#include "chunk.h"

#define STACK_MAX 256
typedef struct {
  // Instruction pointer - ptr to the current instruction
  uint8_t *ip;

  // Right now we will keep things simple.
  // When our compiler will be written, we will
  // allocate the stack to the needed size RIGHT AFTER 
  // compilation ends. Because our compiler will know
  // how many constants we will need.
  Value stack[STACK_MAX];
  Value *top;
} VM;
#undef STACK_MAX

// Stack functions
void resetStack(VM *);

void pushValue(VM *, Value);

Value popValue(VM *);

Value peekValue(VM *);

// Function that sets up our VM.
void interpret(VM *, Chunk *);

void allocVM(VM *);

void freeVM(VM *);

#endif
