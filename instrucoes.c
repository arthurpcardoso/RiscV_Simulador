#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "instrucoes.h"
#include "memoria.h"

int32_t lb(uint32_t address, int32_t kte){
    int32_t tmp;
    tmp = mem[(address + kte)/4];
    tmp = tmp >> ((address + kte)%4)*8;
    tmp = tmp & 0x000000FF;
    return tmp;
};

int32_t lw(uint32_t address, int32_t kte){
    int32_t tmp;
    tmp = mem[(address + kte)/4];
    return tmp;
};

int32_t lbu(uint32_t address, int32_t kte){
    uint32_t tmp;
    tmp = mem[(address + kte)/4];
    tmp = tmp >> ((address + kte)%4)*8;
    tmp = tmp & 0x000000FF;
    return tmp;
};

void sb(uint32_t address, int32_t kte, int8_t dado){
    int32_t tmp;
    tmp = mem[(address + kte)/4];
    tmp = tmp & ~(0x000000FF << ((address + kte)%4)*8);
    tmp = tmp | (dado << ((address + kte)%4)*8);
    mem[(address + kte)/4] = tmp;
};

void sw(uint32_t address, int32_t kte, int32_t dado){
    mem[(address + kte)/4] = dado;
};

void add(int32_t rs1, int32_t rs2, int32_t rd){
    reg[rd] = reg[rs1] + reg[rs2];
};

void addi(int32_t rs1, int32_t imm12_i, int32_t rd){
    reg[rd] = reg[rs1] + imm12_i;
};

void and(int32_t rs1, int32_t rs2, int32_t rd){
    reg[rd] = reg[rs1] & reg[rs2];
};

void andi(int32_t rs1, int32_t imm12_i, int32_t rd){
    reg[rd] = reg[rs1] & imm12_i;
};

void auipc(int32_t imm20_u, int32_t rd){
    reg[rd] = pc + imm20_u;
};

void beq(int32_t rs1, int32_t rs2, int32_t imm13){
    if(reg[rs1] == reg[rs2]){
        pc = pc + imm13;
    }
};

void bne(int32_t rs1, int32_t rs2, int32_t imm13){
    if(reg[rs1] != reg[rs2]){
        pc = pc + imm13;
    }
};

void bge(int32_t rs1, int32_t rs2, int32_t imm13){
    if(reg[rs1] >= reg[rs2]){
        pc = pc + imm13;
    }
};

void bgeu(int32_t rs1, int32_t rs2, int32_t imm13){
    if(reg[rs1] >= reg[rs2]){
        pc = pc + imm13;
    }
};

void blt(int32_t rs1, int32_t rs2, int32_t imm13){
    if(reg[rs1] < reg[rs2]){
        pc = pc + imm13;
    }
};

