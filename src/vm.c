#include "vm.h"
#include <stdio.h> 
#ifdef DEBUG_EXEC // For debugging
#include "disassembler.h"
#endif

void resetStack(VM *vm) { 
  vm->top = vm->stack;
}

void pushValue(VM *vm, Value value) {
  vm->top++;
  vm->top[-1] = value;
}

Value popValue(VM *vm) {
  vm->top--;
  
  Value result = *vm->top;  
  return result;
}

Value peekValue(VM *vm) {
  return vm->top[-1];
}

// Get the VM up and running:

void allocVM(VM *vm) {
  // Set up the VM's stack.
  resetStack(vm); 
} 
// LMAO it's actually just a function wrapper (sob)

void freeVM(VM *vm) {
  // Bruh these functions are unnecessary.
  allocVM(vm);
}

#ifdef DEBUG_EXEC
// Helper function for debugging while executing code.
void printStack(VM *vm) {
  printf("[ ");
  for (Value *ptr = vm->stack; ptr < vm->top; ptr++) {
    // Advance a value pointer accross the stack until it reaches
    // the top.
    logValue(*ptr);
    printf(" ");
  }

  printf("] ");
}
#endif

void interpret(VM *vm, Chunk *ch) {
  // Here's the fun stuff!
  // Define a few macros.
  #define RESULT_OF(vm, op) \
    double right = popValue(vm); \
    double left = popValue(vm); \
    pushValue((vm), right op left)

  #define GET_BYTE(vm) \
    (*vm->ip++)
  
  // Now before we get started - assign the vm's instruction
  // pointer.
  vm->ip = ch->instructions;

  // Iterate through every instruction in the chunk
  while (1) {
    #ifdef DEBUG_EXEC
    // Debug execution
    printStack(vm);
    disassembleInstruction(ch, (int) (vm->ip - ch->instructions));
    #endif
    uint8_t byte;
    switch (byte = GET_BYTE(vm)) {
      case OP_RETURN:
        // Right now, this function will print the top
        // of the stack and quit.
        logValue(popValue(vm));
        printf("\n");
        return;

      case OP_LOAD_CONSTANT: {
        // Push a constant into the stack.
        int operand = GET_BYTE(vm);
        pushValue(vm, ch->constantPool.values[operand]);
        break;
      }

      case OP_ADD: {
        RESULT_OF(vm, +);
        break;
      }

      case OP_SUB: {
        RESULT_OF(vm, -);
        break;
      }

      case OP_MUL: {
        RESULT_OF(vm, *);
        break;
      }
      
      case OP_DIV: {
        RESULT_OF(vm, /);
        break;
      }
    }
  }

  #undef RESULT_OF
  #undef GET_BYTE
}


