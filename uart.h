#include <stdint.h>

void uart_print(const char* str);
void uart_init();
void uart_print_uint8(unsigned char number);
void uart_print_uint32(uint32_t number);