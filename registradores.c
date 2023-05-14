#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "registradores.h"

int32_t breg[32];

uint32_t	pc,				// contador de programa
            sp,				
            gp,				
            ri;			



uint32_t	opcode,		// codigo da operacao
            rs1,		// indice registrador rs
            rs2,		// indice registrador rt
            rd,			
            shamt,		
            funct3,		
            funct7;	

int32_t		imm12_i,	// constante 12 bits
            imm12_s,				// constante 12 bits
            imm13,					// constante 13 bits
            imm20_u,				// constante 20 bis mais significativos
            imm21,					// constante 21 bits
            imm32;                 // constante de 32 bits: o imediado da instrução