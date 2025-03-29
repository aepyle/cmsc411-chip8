#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <SDL/SDL.h>

uint16_t pc;
uint16_t ipntr;
uint8_t spntr;
uint8_t registers[16];
uint16_t stack[16];


uint8_t getNib(uint16_t hex, int index) {
    if (index > 3) { printf("Index too large: %i", index); return 0; }
    uint8_t val = (hex >> 4*(3-index)) % 16;
    return val;
}

uint16_t pop() {
    if (spntr < 0) { return 0; }
    uint8_t val = stack[spntr];
    stack[spntr] = 0;
    spntr -= 1;
}

void push(uint8_t val) {
    if (spntr >= 15) { return; }
    spntr += 1;
    stack[spntr] = val;
}

/* These functions are available to you to use in your code. */
uint8_t chip8_mem_read(uint16_t addr);
void chip8_mem_write(uint16_t addr, uint8_t val);
uint8_t chip8_register_read(uint8_t reg);
void chip8_register_write(uint8_t reg, uint8_t val);
void chip8_clear_frame(void);
void chip8_mem_clear(void);
int chip8_draw_sprite(uint16_t addr, uint8_t x, uint8_t y, uint8_t height);
void chip8_mem_reset(void);

/* Key statuses are defined as registers 0x00-0x0F */
#define CHIP8_REG_DT        0x10
#define CHIP8_REG_ST        0x11



void chip8_init(void) {
    pc = 0x200;
    ipntr = 0;
    spntr = 0;
    memset(registers, 0, 16);
    memset(stack, 0, 16);
}

void chip8_reset(void) {
    return;
}

void chip8_shutdown(void) {
    return;
}

void chip8_execute_instruction(void) {
    if (pc > 550) { return; }
    uint16_t instruction = chip8_mem_read(pc) << 8 | chip8_mem_read(pc + 1);

    uint8_t op_a = getNib(instruction, 0);
    uint8_t op_b = getNib(instruction, 1);
    uint8_t op_c = getNib(instruction, 2);
    uint8_t op_d = getNib(instruction, 3);

    printf("PC: %i, Instruction: 0x%X: %i, %i\n", pc, instruction, op_a, op_b);
    pc += 2;

    switch (op_a) {
        case 0:
            // Clear frame
            if (instruction == 0x00E0) { chip8_clear_frame(); printf("Clearing\n"); }
            // Return value
            else if (instruction == 0x00EE) { pc = pop(); printf("Popping\n"); }
            break;
        case 1:
            // Set pc to address (Jump)
            pc = instruction & 0x0FFF;
            printf("Jumping to 0x%X\n", pc);
            break;
        case 2:
            // Call subroutine at address NNN
            uint16_t address = instruction & 0x0FFF;
            printf("Calling function at 0x%X\n", address);
            push(pc);
            pc = address;
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            // Set register Vx to value NN
            registers[op_b] = instruction & 0x00FF;
            printf("Set register %i\n", op_b);
            break;
        case 7:
            // Add value NN to register Vx
            registers[op_b] += instruction & 0x00FF;
            printf("Add %i to register %i\n", instruction & 0x00FF, op_b);
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            // Set instruction pointer to value NNN
            ipntr = instruction & 0x0FFF;
            printf("Set i to %i\n", ipntr);
            break;
        case 11:
            break;
        case 12:
            break;
        case 13:
            // Draw sprite at (Vx, Vy) of N-bytes
            chip8_draw_sprite(ipntr, registers[op_b], registers[op_c], op_d);
            printf("Draw sprite: %i, %i, %i, %i\n", ipntr, registers[op_b], registers[op_c], op_d);
            break;
        case 14:
            break;
        case 15:
            break;
    }

    return;
}

