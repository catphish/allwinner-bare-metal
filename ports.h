// The PORT registers base address.
#define PORT_BASE         0x01C20800

// Macros to access PORTG registers.
#define PG_CFG0           *(volatile uint32_t *)(PORT_BASE + 0xD8)
#define PG_DATA           *(volatile uint32_t *)(PORT_BASE + 0xE8)

// Macros to access PORTB registers.
#define PB_CFG2           *(volatile uint32_t *)(PORT_BASE + 0x2C)
#define PB_DATA           *(volatile uint32_t *)(PORT_BASE + 0x34)
