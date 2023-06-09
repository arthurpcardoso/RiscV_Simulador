//
// Created by Ricardo Jacobi on 18/11/22.
//

#define CODE_LIMIT 0x3f1

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "globals.h"
#include "memoria.h"
#include "registradores.h"
#include "riscv_func.h"
#include "RV_Header.h"
#include "instrucoes.h"

//
// Initial values for registers
//

void init() {
    pc = 0;
    ri = 0;
    stop_prg = 0;
    sp = 0x3ffc;
    gp = 0x1800;
}

void fetch() {
    ri = lw(pc, 0);                         
    pc = pc + 4;
    breg[0] = 0;                            // registrador zero sempre zero

    //printf("%x\n", ri);
}

void decode() {

    int32_t tmp;

    opcode = ri & 0x7F;
    rs2 = (ri >> 20) & 0x1F;
    rs1 = (ri >> 15) & 0x1F;
    rd = (ri >> 7) & 0x1F;
    shamt = (ri >> 20) & 0x1F;
    funct3 = (ri >> 12) & 0x7;
    funct7 = (ri >> 25);
    imm12_i = ((int32_t) ri) >> 20;
    tmp = get_field(ri, 7, 0x1f);
    imm12_s = set_field(imm12_i, 0, 0x1f, tmp);
    imm13 = imm12_s;
    imm13 = set_bit(imm13, 11, imm12_s & 1);
    imm13 = imm13 & ~1;
    imm20_u = ri & (~0xFFF);
// mais aborrecido...
    imm21 = (int32_t) ri >> 11;            // estende sinal
    tmp = get_field(ri, 12, 0xFF);        // le campo 19:12
    imm21 = set_field(imm21, 12, 0xFF, tmp);    // escreve campo em imm21
    tmp = get_bit(ri, 20);                // le o bit 11 em ri(20)
    imm21 = set_bit(imm21, 11, tmp);            // posiciona bit 11
    tmp = get_field(ri, 21, 0x3FF);
    imm21 = set_field(imm21, 1, 0x3FF, tmp);
    imm21 = imm21 & ~1;                    // zero bit 0
    ins_code = get_instr_code(opcode, funct3, funct7);
    imm32 = get_imm32(get_i_format(opcode, funct3, funct7));
}

int load_mem(const char *fn, int start) {
    FILE *fptr;
    int *m_ptr = mem + (start >> 2);
    int size = 0;

    fptr = fopen(fn, "rb");
    if (!fptr) {
        printf("Arquivo nao encontrado!");
        return -1;
    } else {
        while (!feof(fptr)) {
            fread(m_ptr, 4, 1, fptr);
            m_ptr++;
            size++;
        }
        fclose(fptr);
    }
    return size;
}

void step() {
    fetch();
    decode();
    execute();
}

void execute() {

    switch (ins_code)
    {
    case I_add:
        add(rs1,rs2,rd);
        break;
    case I_addi:
        addi(rs1,imm32,rd);
        break;
    case I_and:
        and(rs1,rs2,rd);
        break;
    case I_andi:
        andi(rs1,imm32,rd);
        break;
    case I_auipc:
        auipc(imm32,rd);
        break;
    case I_beq:
        beq(rs1,rs2,imm32);
        break;
    case I_bge:
        bge(rs1,rs2,imm32);
        break;
    case I_bgeu:
        bgeu(rs1,rs2,imm32);
        break;
    case I_blt:
        blt(rs1,rs2,imm32);
        break;
    case I_bltu:
        bltu(rs1,rs2,imm32);
        break;
    case I_bne:
        bne(rs1,rs2,imm32);
        break;
    case I_jal:
        jal(imm32);
        break;
    case I_jalr:
        jalr(rs1,imm32,rd);
        break;
    case I_lb:
        lb(rs1,imm32);
        break;
    case I_lw:
        lw(rs1,imm32);
        break;
    case I_lbu:
        lbu(rs1,imm32);
        break;
    case I_or:
        or(rs1,rs2,rd);
        break;
    case I_ori:
        ori(rs1,imm32,rd);
        break;
    case I_sb:
        sb(rs1,rs2,imm32);
        break;
    case I_sw:
        sw(rs1,rs2,imm32);
        break;
    case I_slli:
        slli(rs1,shamt,rd);
        break;
    case I_slt:
        slt(rs1,rs2,rd);
        break;
    case I_srai:
        srai(rs1,shamt,rd);
        break;
    case I_srli:    
        srli(rs1,shamt,rd);
        break;
    case I_sub:
        sub(rs1,rs2,rd);
        break;
    case I_xor:
        xor(rs1,rs2,rd);
        break;
    case I_lui:
        lui(imm32,rd);
        break;
    case I_ecall:
        ecall();
        break;
    
    default:
        break;
    }
}

void run() {
    int i = 0;
    while (i < 455) {
        step();
        i += 1;
    }
}

int32_t get_imm32(enum FORMATS iformat) {
    switch (iformat) {
        case RType:     return 0;
        case IType:     return imm12_i;
        case SType:     return imm12_i;
        case SBType:    return imm13;
        case UType:     return imm20_u;
        case UJType:    return imm21;
        default:        return 0;
    }
}

enum FORMATS get_i_format(uint32_t opcode, uint32_t func3, uint32_t func7) {
    switch (opcode) {
        case 0x33 :
            return RType;
        case 0x03:
        case 0x13:
        case 0x67:
        case 0x73:
            return IType;
        case 0x23 :
            return SType;
        case 0x63 :
            return SBType;
        case 0x37 :
            return UType;
        case 0x6F:
        case 0x17 :
            return UJType;
        case 0x00:
            if (func3 == 0 && func7 == 0)
                return NOPType;
            else
                return NullFormat;
        default:
            printf("Undefined Format");
            return NullFormat;
    }
}

enum INSTRUCTIONS get_instr_code(uint32_t opcode, uint32_t funct3, uint32_t funct7) {
    switch (opcode) {
        case 0x33:
            switch (funct3)
            {
            case 0x0:
                switch (funct7)
                {
                    case 0x00:
                        return I_add;
                    case 0x20:
                        return I_sub;
                }
            case 0x2:
                return I_slt;
            case 0x3:
                return I_sltu;
            case 0x4:
                return I_xor;
            case 0x6:
                return I_or;
            case 0x7:
                return I_and;
            default:
                break;
                }
        case 0x03:
            switch (funct3)
            {
            case 0x0:
                return I_lb;
            case 0x2:
                return I_lw;
            case 0x4:
                return I_lbu;
            default:
                break;
            }
        case 0x13:
            switch (funct3)
            {
                case 0x0:
                    return I_addi;
                case 0x1:
                    return I_slli;
                case 0x5:
                    switch (funct7)
                    {
                        case 0x00:
                            return I_srli;
                        case 0x20:
                            return I_srai;
                    }
                case 0x6:
                    return I_ori;
                case 0x7:   
                    return I_andi;
            }
        case 0x23:
            switch (funct3)
            {
                case 0x0:
                    return I_sb;
                case 0x2:
                    return I_sw;
            }
        case 0x63:
            switch (funct3)
            {
                case 0x0:
                    return I_beq;
                case 0x1:
                    return I_bne;
                case 0x4:
                    return I_blt;
                case 0x5:
                    return I_bge;
                case 0x6:
                    return I_bltu;
                case 0x7:
                    return I_bgeu;
            }
        case 0x37:
            return I_lui;
        case 0x6F:
            return I_jal;
        case 0x17:
            return I_auipc;
        case 0x67:
            return I_jalr;
        case 0x73:
            return I_ecall;
        default:
            printf("Undefined Instruction");
            break;
            }
    }
