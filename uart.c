#include <stddef.h>
#include <stdint.h>
#include "ccu.h"
#include "ports.h"

// The UART registers base address.
#define UART0_BASE 0x01C28000
// Macros to access UART registers.
#define UART0_RBR *(volatile uint32_t *)(UART0_BASE + 0x00)
#define UART0_DLL *(volatile uint32_t *)(UART0_BASE + 0x00)
#define UART0_THR *(volatile uint32_t *)(UART0_BASE + 0x00)
#define UART0_IER *(volatile uint32_t *)(UART0_BASE + 0x04)
#define UART0_FCR *(volatile uint32_t *)(UART0_BASE + 0x08)
#define UART0_LCR *(volatile uint32_t *)(UART0_BASE + 0x0C)
#define UART0_LSR *(volatile uint32_t *)(UART0_BASE + 0x14)
#define UART0_USR *(volatile uint32_t *)(UART0_BASE + 0x7C)

// The length of a null terminated string
size_t strlen(const char* str)
{
  size_t ret = 0;
  while ( str[ret] != 0 )
    ret++;
  return ret;
}

// Set up the UART (serial port)
void uart_init()
{
  PB_CFG2 |= (2<<24);

  // Enable UART0 clock
  CCU_APB1_GATING |= (1<<16);

  UART0_LCR = 0x83;
  UART0_DLL = 13;
  UART0_LCR = 0x3;

  // Disable UART0 interrupts.
  UART0_IER = 0x00000000;

  // Configure UART0 (enable FIFO)
  UART0_FCR = 0x00000001;
}

// UART is ready to receive data to transmit?
unsigned char uart_tx_ready()
{
  return (UART0_USR & 2);
}

// UART has received data?
unsigned char uart_rx_ready()
{
  return (UART0_LSR & 1);
}

// Push one byte to the UART port (blocking until ready to transmit)
void uart_putc(unsigned char byte)
{
  // Wait for UART transmit FIFO to be not full.
  while ( ! uart_tx_ready() );
  UART0_THR = byte;
}

// Write a zero terminated string to the UART
void uart_print(const char* str)
{
  while(*str) {
    uart_putc(*str);
    str++;
  }
}

// Print a char to the UART as ASCII HEX
void uart_print_uint8(unsigned char number)
{
  unsigned char chars[] = "0123456789ABCDEF";
  uart_putc(chars[(number >> 4) & 0xF]);
  uart_putc(chars[(number >> 0) & 0xF]);
}

// Print a uint32 to the UART as ASCII HEX
void uart_print_uint32(uint32_t number)
{
  unsigned char chars[] = "0123456789ABCDEF";
  uart_putc(chars[(number >> 28) & 0xF]);
  uart_putc(chars[(number >> 24) & 0xF]);
  uart_putc(chars[(number >> 20) & 0xF]);
  uart_putc(chars[(number >> 16) & 0xF]);
  uart_putc(chars[(number >> 12) & 0xF]);
  uart_putc(chars[(number >> 8) & 0xF]);
  uart_putc(chars[(number >> 4) & 0xF]);
  uart_putc(chars[(number >> 0) & 0xF]);
}