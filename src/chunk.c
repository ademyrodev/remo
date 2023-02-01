#include "chunk.h"
#include "common.h"
#include "mem.h"

// Static functions to make the code look less messy. 
static void reallocateChunk(Chunk *ch, int line) {
  if (ch->bytesSize <= ch->bytesUsed) {
    // Grow the array's size
    ch->bytesSize = DOUBLE_SIZE(ch->bytesSize);
    
    // Reallocate the array
    ch->instructions = ALLOCATE_ARRAY(uint8_t, ch->bytesSize, 
        ch->instructions);

    // Also grow ch->cols - it's a complete parralel array
    // to ch->instructions.
    ch->cols = ALLOCATE_ARRAY(int, ch->bytesSize, ch->cols);
  } 

  if (ch->linesSize <= ch->linesUsed) {
    // Grow the line array.
    ch->linesSize = DOUBLE_SIZE(ch->linesSize);
    ch->lines = ALLOCATE_ARRAY(LineInfo, ch->linesSize, 
        ch->lines);
  }

  if (line != ch->lines[ch->linesUsed - 1].line) {

    // Run length compression of the LineInfo array.
    // Basically, if [line] is not equal to the last one in
    // ch->lines.

    LineInfo newLine = {.offset = ch->bytesUsed, .line = line};

    ch->lines[ch->linesUsed++] = newLine;
  }
}

static int addConstant(Chunk *ch, Value constant) {
  // Adds a constant to 'ch' and returns
  // its index.
  addToValueArray(&ch->constantPool, constant);
  return ch->constantPool.used - 1;
}

void allocChunk(Chunk *ch) {
  // Fresh, zeroed state.
  ch->instructions = NULL;
  ch->bytesUsed = 0;
  ch->bytesSize = 0;

  ch->lines = NULL;
  ch->linesUsed = 0;
  ch->linesSize = 0;
  
  ch->cols = NULL;

  allocValueArray(&ch->constantPool);
}

void emitToChunk(Chunk *ch, uint8_t byte, int line, int col) {
  // Won't reallocate if it doesn't need to.
  reallocateChunk(ch, line); 

  ch->instructions[ch->bytesUsed] = byte;
  ch->cols[ch->bytesUsed] = col;
  ch->bytesUsed++;
}

void writeConstant(Chunk *ch, Value constant, int line, int col) {
  // This might look unecessarily complex, but because
  // our operands are uint8_ts, we can only store up to 
  // 256 different constants. So we are using a workaround
  // here - if the index is above 256, we push an uint32.
  int index = addConstant(ch, constant);
  
  if (index < 256) {
    // No problem, push a normal constant.
    emitToChunk(ch, OP_LOAD_CONSTANT, line, col);
    emitToChunk(ch, index, line, col);
  } else {
    // Not enough space, push an uint32.
    emitToChunk(ch, OP_LOAD_LONG_CONSTANT, line, col);
    emitToChunk(ch, (uint8_t) index, line, col);
    emitToChunk(ch, (uint8_t) ((index >> 8) & 0xff), line, col);
    emitToChunk(ch, (uint8_t) ((index >> 16) & 0xff), line, col);
  }
}

void freeChunk(Chunk *ch) {
  // Free anything that has been allocated
  FREE(ch->instructions);
  FREE(ch->lines);
  FREE(ch->cols);

  // Zero everything out
  freeValueArray(&ch->constantPool);
  allocChunk(ch);
}

// Binary search the line
int getLine(Chunk *ch, int instruction) {
  int start = 0;
  int end = ch->linesUsed - 1;

  while (1) {
    int mid = (start + end) / 2;
    LineInfo *line = &ch->lines[mid];

    if (instruction < line->offset) {
      end = mid - 1;
    } else if (mid == ch->linesUsed - 1 || instruction < ch->lines[mid + 1]
              .offset) {
      
      return line->line;
    } else {
      start = mid + 1;
    }
  }
}

