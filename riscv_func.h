#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void init();

void fetch();

enum FORMATS get_i_format(uint32_t opcode, uint32_t func3, uint32_t func7);

void decode();

void step();

void execute();

void run();

int load_mem(const char *fn, int start);

int32_t get_imm32(enum FORMATS iformat);

enum INSTRUCTIONS get_instr_code(uint32_t opcode, uint32_t funct3, uint32_t funct7);