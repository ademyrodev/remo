#include <stdio.h>
#include "common.h"
#include "disassembler.h"

// Simple instructions with no operands, such as OP_ADD (add)
static int simpleInstruction(int offset, char *name) {
  printf("    "); // Cool spacing
  printf("%s\n", name);

  return offset + 1; // 1 instruction forward
}

static int constantInstruction(Chunk *ch, int offset, char *name) {
  printf("    "); // Cool spacing; again
  printf("%s", name); 

  // Print the operand
  int operand = ch->instructions[offset + 1];
printf(" #%5d", operand); 
  printf(" (");
  logValue(ch->constantPool.values[operand]); 
  printf(")\n");

  // Jump 2 instructions forward because of the
  // operand

  return offset + 2; 
}

static int longConstantInstruction(Chunk* chunk, int offset, char* name) {
  // Bigger constants if we go over 256 constants (uint8_t limitations) 
  uint32_t constant = chunk->instructions[offset + 1] |
                     (chunk->instructions[offset + 2] << 8) |
                     (chunk->instructions[offset + 3] << 16);

  printf("    %s #%5d (", name, constant);
  logValue(chunk->constantPool.values[constant]);
  printf(")\n");
  return offset + 4;
}

static int disassembleInstruction(Chunk *ch, int offset) {
  // Pretty simple, yet so big.
  printf("    %d @ %d:%d", offset, getLine(ch, offset), ch->cols[offset]);
  switch (ch->instructions[offset]) {
    case OP_LOAD_CONSTANT:
      return constantInstruction(ch, offset, "loadi");

    case OP_LOAD_LONG_CONSTANT:
      return longConstantInstruction(ch, offset, "loadi");

    case OP_ADD:
      return simpleInstruction(offset, "add");

    case OP_SUB:
      return simpleInstruction(offset, "sub");

    case OP_MUL:
      return simpleInstruction(offset, "mul");

    case OP_DIV:
      return simpleInstruction(offset, "div");

    case OP_RETURN:
      return simpleInstruction(offset, "ret");
  }
}

void disassembleChunk(Chunk *ch, char *name) {
  // Print the chunks name and give the rest of the
  // work to disassembleInstruction().
  printf("%s:\n", name);

  for (int offset = 0; offset <= ch->bytesUsed - 1; 
      offset = disassembleInstruction(ch, offset)); // Nothing
}
