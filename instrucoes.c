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

void bltu(int32_t rs1, int32_t rs2, int32_t imm13){
    if(reg[rs1] < reg[rs2]){
        pc = pc + imm13;
    }
};

void jal(int32_t imm21){
    reg[1] = pc + 4;
    pc = pc + imm21;
};

void jalr(int32_t rs1, int32_t imm12_i, int32_t rd){
    reg[rd] = pc + 4;
    pc = reg[rs1] + imm12_i;
};

void or (int32_t rs1, int32_t rs2, int32_t rd){
    reg[rd] = reg[rs1] | reg[rs2];
};

void lui(int32_t imm20_u, int32_t rd){
    reg[rd] = imm20_u;
};

void slt(int32_t rs1, int32_t rs2, int32_t rd){
    if(reg[rs1] < reg[rs2]){
        reg[rd] = 1;
    }else{
        reg[rd] = 0;
    }
};

void sltu(int32_t rs1, int32_t rs2, int32_t rd){
    if(reg[rs1] < reg[rs2]){
        reg[rd] = 1;
    }else{
        reg[rd] = 0;
    }
};

void ori(int32_t rs1, int32_t imm12_i, int32_t rd){
    reg[rd] = reg[rs1] | imm12_i;
};

void slli(int32_t rs1, int32_t shamt6, int32_t rd){
    reg[rd] = reg[rs1] << shamt6;
};

void srai(int32_t rs1, int32_t shamt6, int32_t rd){
    reg[rd] = reg[rs1] >> shamt6;
};

void slri(int32_t rs1, int32_t shamt6, int32_t rd){
    reg[rd] = reg[rs1] >> shamt6;
};

void sub(int32_t rs1, int32_t rs2, int32_t rd){
    reg[rd] = reg[rs1] - reg[rs2];
}; 

void xori(int32_t rs1, int32_t imm12_i, int32_t rd){
    reg[rd] = reg[rs1] ^ imm12_i;
};

void ecall(){
    if(reg[17] == 1){
        printf("%d", reg[10]);
    }else if(reg[17] == 4){
        printf("%s", &mem[reg[10]]);
    }else if(reg[17] == 10){
        exit(0);
    }
};