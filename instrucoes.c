#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "memoria.h"
#include "registradores.h"
#include "instrucoes.h"

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
    breg[rd] = breg[rs1] + breg[rs2];
};

void addi(int32_t rs1, int32_t imm12_i, int32_t rd){
    breg[rd] = breg[rs1] + imm12_i;
};

void and(int32_t rs1, int32_t rs2, int32_t rd){
    breg[rd] = breg[rs1] & breg[rs2];
};

void andi(int32_t rs1, int32_t imm12_i, int32_t rd){
    breg[rd] = breg[rs1] & imm12_i;
};

void auipc(int32_t imm20_u, int32_t rd){
    breg[rd] = pc + imm20_u;
};

void beq(int32_t rs1, int32_t rs2, int32_t imm13){
    printf("beq\n");
    if(breg[rs1] == breg[rs2]){
        pc -= 4;
        pc = pc + imm13;
    }
};

void bne(int32_t rs1, int32_t rs2, int32_t imm13){
    if(breg[rs1] != breg[rs2]){
        pc -= 4;
        pc = pc + imm13;
    }
};

void bge(int32_t rs1, int32_t rs2, int32_t imm13){
    if(breg[rs1] >= breg[rs2]){
        pc -= 4;
        pc = pc + imm13;
    }
};

void bgeu(int32_t rs1, int32_t rs2, int32_t imm13){
    if(breg[rs1] >= breg[rs2]){
        pc -= 4;
        pc = pc + imm13;
    }
};

void blt(int32_t rs1, int32_t rs2, int32_t imm13){
    if(breg[rs1] < breg[rs2]){
        pc -= 4;
        pc = pc + imm13;
    }
};

void bltu(int32_t rs1, int32_t rs2, int32_t imm13){
    if(breg[rs1] < breg[rs2]){
        pc -= 4;
        pc = pc + imm13;
    }
};

void jal(int32_t imm21){
    pc -= 4;
    breg[1] = pc + 4;
    pc = pc + imm21;
};

void jalr(int32_t rs1, int32_t imm12_i, int32_t rd){
    breg[rd] = pc + 4;
    pc = breg[rs1] + imm12_i;
};

void or(int32_t rs1, int32_t rs2, int32_t rd){
    breg[rd] = breg[rs1] | breg[rs2];
};

void lui(int32_t imm20_u, int32_t rd){
    breg[rd] = imm20_u;
};

void slt(int32_t rs1, int32_t rs2, int32_t rd){
    if(breg[rs1] < breg[rs2]){
        breg[rd] = 1;
    }else{
        breg[rd] = 0;
    }
};

void sltu(int32_t rs1, int32_t rs2, int32_t rd){
    if(breg[rs1] < breg[rs2]){
        breg[rd] = 1;
    }else{
        breg[rd] = 0;
    }
};

void ori(int32_t rs1, int32_t imm12_i, int32_t rd){
    breg[rd] = breg[rs1] | imm12_i;
};

void slli(int32_t rs1, int32_t shamt6, int32_t rd){
    breg[rd] = breg[rs1] << shamt6;
};

void srai(int32_t rs1, int32_t shamt6, int32_t rd){
    breg[rd] = breg[rs1] >> shamt6;
};

void srli(int32_t rs1, int32_t shamt6, int32_t rd){
    breg[rd] = breg[rs1] >> shamt6;
};

void sub(int32_t rs1, int32_t rs2, int32_t rd){
    breg[rd] = breg[rs1] - breg[rs2];
}; 

void xor(int32_t rs1, int32_t rs2, int32_t rd){
    breg[rd] = breg[rs1] ^ breg[rs2];
};

void ecall(){
    if(breg[17] == 1){
        printf("%d", breg[10]);
    }else if(breg[17] == 4){
        printf("%s", &mem[breg[10]]);
    }else if(breg[17] == 10){
        exit(0);
    }
};