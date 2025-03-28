#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


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
    printf("INNIT\n");
    return;
}

void chip8_reset(void) {
    return;
}

void chip8_shutdown(void) {
    printf("Shutting down...\n");
    return;
}

void chip8_execute_instruction(void) {
    return;
}