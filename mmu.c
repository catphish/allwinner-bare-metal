#include <stdint.h>

void mmu_init() {

  // Disable MMU
  asm("ldr r8, =0x0;    mcr p15, 0, r8, c1, c0, 0;" : : : "r8");

  // Populate the pagetable
  int n;
  for(n=0;n<4096;n++)
  {
    if(n==0)
    {
      // SRAM. Normal.
      *(volatile uint32_t *)(0x4000 + n*4) = (n<<20) | (1<<12) | (3<<10) | (0<<2) | 2;
    } else if(n>=0x400 && n<=0x401) {
      // First 2MB of DRAM, we will use this for the framebuffer, no cache
      *(volatile uint32_t *)(0x4000 + n*4) = (n<<20) | (1<<12) | (3<<10) | (0<<2) | 2;
    } else if(n>=0x402 && n<0xc00) {
      // Remaining DRAM. Write back.
      *(volatile uint32_t *)(0x4000 + n*4) = (n<<20) | (1<<12) | (3<<10) | (3<<2) | 2;
    } else {
      // Other stuff. Normal.
      *(volatile uint32_t *)(0x4000 + n*4) = (n<<20) | (1<<12) | (3<<10) | (0<<2) | 2;
    }
  }

  // Set up the pagetable
  asm("ldr r8, =0x4000; mcr p15, 0, r8, c2, c0, 0" : : : "r8");
  asm("ldr r8, =0x0;    mcr p15, 0, r8, c2, c0, 2" : : : "r8");
  asm("ldr r8, =0x3;    mcr p15, 0, r8, c3, c0, 0" : : : "r8");

  // Enable MMU
  asm(
    "ldr r8, =0x0;"
    "MCR p15, 0, r8, c8, C3, 0;"
    "MCR p15, 0, r8, c8, C5, 0;"
    "MCR p15, 0, r8, c8, C6, 0;"
    "MCR p15, 0, r8, c8, C7, 0;"
    "mcr p15, 0, r8, c12, c0, 0;"

    "ldr r8, =0x1005;"
    "mcr p15, 0, r8, c1, c0, 0;"
    : : : "r8");

}
