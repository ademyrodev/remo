#ifndef CHUNK_H
#define CHUNK_H

// Remo bytecode chunk definition.
#include "common.h"
#include "value.h"

typedef enum {
  OP_LOAD_CONSTANT,
  OP_LOAD_LONG_CONSTANT,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_RETURN
// We won't be using this name, but uint8_t to refer to an instruction.
} BytecodeInstruction;

typedef struct {
  // Line information struct compressed with run-length encoding.
  // We have an offset member that will be used to find which instruction
  // matches that offset.  
  int offset;

  int line;
} LineInfo;

typedef struct {
  // Like above, we're using uint8_t to refer to an instruction.
  uint8_t *instructions;
  int bytesUsed;
  int bytesSize; 
 
  // Every constant we will store will be here.
  ValueArray constantPool; 

  // Compressed list of lines.
  LineInfo *lines;
  int linesUsed;
  int linesSize;

  // This list won't be compressed - every instruction has a different column,
  // as long as they're in the same line.
  int *cols;
} Chunk;

void allocChunk(Chunk *);

void emitToChunk(Chunk *, uint8_t, int, int);

void writeConstant(Chunk *, Value, int, int);

void freeChunk(Chunk *);

int getLine(Chunk *, int);

#endif
