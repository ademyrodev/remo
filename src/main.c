// Pretty much every inclusion we need is already there.
#include "common.h"
#include "disassembler.h"
#include "vm.h"

int main(int argc, char **argv) {
  // Handcrafted chunk. You can play around with it
  // by tweaking a few things here, or make your own
  // handcrafted chunk.
  Chunk myChunk;
  allocChunk(&myChunk);
  
  writeConstant(&myChunk, 3, 1, 123);
  writeConstant(&myChunk, 4, 2, 123);
  emitToChunk(&myChunk, OP_MUL, 3, 123);
  writeConstant(&myChunk, 5, 8, 23);
  emitToChunk(&myChunk, OP_DIV, 28, 3);
  writeConstant(&myChunk, 1, 4, 2);
  writeConstant(&myChunk, 2, 9, 3);
  emitToChunk(&myChunk, OP_ADD, 9, 4);
  emitToChunk(&myChunk, OP_SUB, 2, 9);
  emitToChunk(&myChunk, OP_RETURN, 4, 123);

  disassembleChunk(&myChunk, "my_chunk");

  // Now try to execute it
  VM ourVM;
  allocVM(&ourVM);
  interpret(&ourVM, &myChunk);
  freeVM(&ourVM);

  freeChunk(&myChunk);
  return 0;
}

void repl() {
  // I really like the "repl" idea, whoever invented it 
  // is an absolute genius. 
  // I think it comes from Lisp: Read, Evaluate, Print, Loop.
  // It's pretty easy to implement too. Take a look:
  // 
  // (print (eval (input)))
  // And because we are implementing Remo, here's how you would
  // do it in our beloved language:
  //
  // print(eval(input()));
}
