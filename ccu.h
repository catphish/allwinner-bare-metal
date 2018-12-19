// The CCU registers base address.
#define CCU_BASE 0x01C20000
// Macros to access CCU registers.
#define CCU_APB1_GATING *(volatile uint32_t *)(CCU_BASE + 0x6C)
#define PLL5_CFG_REG    *(volatile uint32_t *)(CCU_BASE + 0x20)
