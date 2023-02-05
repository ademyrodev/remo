#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

// Disassembler file - will dissassemble chunks (no way!!)

#include "chunk.h"
#include "common.h"

int disassembleInstruction(Chunk *, int);

void disassembleChunk(Chunk *, char *);

#endif
