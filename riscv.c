#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "riscv_func.h"

int main() {
    printf("Iniciando!\n");

    load_mem("code.bin", 0x0);
    load_mem("data.bin", 0x2000);

    init();
    
    step();
    step();
    step();
    step();
    step();
    step();
    step();
    step();
    step();
    step();
    step();
    

    
    return 0;
}