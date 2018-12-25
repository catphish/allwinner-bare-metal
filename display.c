#include <stdint.h>
#include "ccu.h"
#include "system.h"
#include "display.h"
#include "uart.h"

// This function initializes the HDMI port and TCON.
// Almost everything here is resolution specific and
// currently hardcoded to 1920x1080@60Hz.
void display_init() {
  // Clocks for HDMI, TCON and DE2
  PLL_VIDEO_CTRL_REG   = (1<<31) | (1<<25) | (1<<24) | (98<<8) | (7<<0); // 297MHz
  PLL_DE_CTRL_REG      = (1<<31) | (1<<24) | (17<<8) | (0<<0); // 432MHz
  BUS_CLK_GATING_REG1 |= (1<<11) | (1<<3); // Enable HDMI, TCON0
  BUS_SOFT_RST_REG1   |= (3<<10) | (1<<3); // De-assert reset of HDMI0/1, TCON0
  HDMI_CLK_REG         = (1<<31); // Enable HDMI clk (use PLL3)
  HDMI_SLOW_CLK_REG    = (1<<31); // Enable HDMI slow clk
  TCON0_CLK_REG        = (1<<31) | 1; // Enable TCON0 clk, divide by 2

  udelay(100000);

  // HDMI PHY init, the following black magic is based on the procedure documented at:
  // http://linux-sunxi.org/images/3/38/AW_HDMI_TX_PHY_S40_Spec_V0.1.pdf
  HDMI_PHY_CFG1 = 0;
  HDMI_PHY_CFG1 = 1;
  udelay(5);
  HDMI_PHY_CFG1 |= (1<<16);
  HDMI_PHY_CFG1 |= (1<<1);
  udelay(10);
  HDMI_PHY_CFG1 |= (1<<2);
  udelay(5);
  HDMI_PHY_CFG1 |= (1<<3);
  udelay(40);
  HDMI_PHY_CFG1 |= (1<<19);
  udelay(100);
  HDMI_PHY_CFG1 |= (1<<18);
  HDMI_PHY_CFG1 |= (7<<4);
  while((HDMI_PHY_STS & 0x80) == 0);
  HDMI_PHY_CFG1 |= (0xf<<4);
  HDMI_PHY_CFG1 |= (0xf<<8);
  HDMI_PHY_CFG3 |= (1<<0) | (1<<2);

  HDMI_PHY_PLL1 &= ~(1<<26);
  HDMI_PHY_CEC = 0;

  HDMI_PHY_PLL1 = 0x39dc5040;
  HDMI_PHY_PLL2 = 0x80084381;
  udelay(10000);
  HDMI_PHY_PLL3 = 1;
  HDMI_PHY_PLL1 |= (1<<25);
  udelay(10000);
  uint32_t tmp = (HDMI_PHY_STS & 0x1f800) >> 11;
  HDMI_PHY_PLL1 |= (1<<31) | (1<<30) | tmp;

  HDMI_PHY_CFG1 = 0x01FFFF7F;
  HDMI_PHY_CFG2 = 0x8063A800;
  HDMI_PHY_CFG3 = 0x0F81C485;

  /* enable read access to HDMI controller */
  HDMI_PHY_READ_EN = 0x54524545;
  /* descramble register offsets */
  HDMI_PHY_UNSCRAMBLE = 0x42494E47;

  udelay(100000);

//   // HDMI Config, based on the documentation at:
//   // https://people.freebsd.org/~gonzo/arm/iMX6-HDMI.pdf
  HDMI_FC_INVIDCONF = (1<<6) | (1<<5) | (1<<4) | (1<<3); // Polarity etc
  HDMI_FC_INHACTIV0 = (1920 & 0xff);    // Horizontal pixels
  HDMI_FC_INHACTIV1 = (1920 >> 8);      // Horizontal pixels
  HDMI_FC_INHBLANK0 = (280 & 0xff);     // Horizontal blanking
  HDMI_FC_INHBLANK1 = (280 >> 8);       // Horizontal blanking

  HDMI_FC_INVACTIV0 = (1079 & 0xff);    // Vertical pixels
  HDMI_FC_INVACTIV1 = (1079 >> 8);      // Vertical pixels
  HDMI_FC_INVBLANK  = 44;               // Vertical blanking

  HDMI_FC_HSYNCINDELAY0 = (87 & 0xff);  // Horizontal Front porch
  HDMI_FC_HSYNCINDELAY1 = (87 >> 8);    // Horizontal Front porch
  HDMI_FC_VSYNCINDELAY  = 3;            // Vertical front porch
  HDMI_FC_HSYNCINWIDTH0 = (43 & 0xff);  // Horizontal sync pulse
  HDMI_FC_HSYNCINWIDTH1 = (43 >> 8);    // Horizontal sync pulse
  HDMI_FC_VSYNCINWIDTH  = 4;            // Vertical sync pulse

  HDMI_FC_CTRLDUR    = 12;   // Frame Composer Control Period Duration
  HDMI_FC_EXCTRLDUR  = 32;   // Frame Composer Extended Control Period Duration
  HDMI_FC_EXCTRLSPAC = 1;    // Frame Composer Extended Control Period Maximum Spacing
  HDMI_FC_CH0PREAM   = 0x0b; // Frame Composer Channel 0 Non-Preamble Data
  HDMI_FC_CH1PREAM   = 0x16; // Frame Composer Channel 1 Non-Preamble Data
  HDMI_FC_CH2PREAM   = 0x21; // Frame Composer Channel 2 Non-Preamble Data
  HDMI_MC_FLOWCTRL   = 0;    // Main Controller Feed Through Control
  HDMI_MC_CLKDIS     = 0x7e; // Main Controller Synchronous Clock Domain Disable
  HDMI_MC_CLKDIS     = 0x7c; // Main Controller Synchronous Clock Domain Disable

  // TCON
  TCON0_GCTL_REG   = (1<<31);
  TCON_GINT0_REG = 0;
  //TCON0_CTL_REG = (1<<31) | (1<<1);
  TCON0_CTL_REG    = 0x800001E0;
  TCON0_BASIC0_REG = (1919<<16) | 1079;
  TCON0_BASIC1_REG = (1919<<16) | 1079;
  TCON0_BASIC2_REG = (1919<<16) | 1079;
  TCON0_BASIC3_REG = (2199<<16) | 147;
  TCON0_BASIC4_REG = (2250<<16) | 35;
  TCON0_BASIC5_REG = (43<<16) | 4;

  udelay(100000);

  // DE2
  BUS_CLK_GATING_REG1 |= (1<<12); // Enable DE
  BUS_SOFT_RST_REG1   |= (1<<12); // De-assert reset of DE
  DE_CLK_REG           = (1<<31) | (1<<24); // Enable DE clock, set source to PLL_DE

  udelay(100000);

  DE_AHB_RESET |= (1<<0);
  DE_SCLK_GATE |= (1<<0);
  DE_HCLK_GATE |= (1<<0);
  DE_DE2TCON_MUX &= ~(1<<0);

  udelay(100000);

  DE_MIXER0_GLB_CTL = 1;
  //DE_MIXER0_GLB_DBUFFER = 1;
  DE_MIXER0_GLB_SIZE = (1079<<16) | 1919;

  // I'm told this is a good idea
  for(uint32_t addr = DE_MIXER0 + 0x2000; addr < DE_MIXER0 + 0x6000; addr += 4)
   *(volatile uint32_t*)(addr) = 0;

   // Put some data in DRAM, if we see colours we're good
  for(int n=0x40000000; n<(0x40000000+1920*1080*2); n+=4)
    *(volatile uint32_t*)(n) = 0xff00ff00;
  for(int n=0x40000000+1920*1080*2; n<(0x40000000+1920*1080*4); n+=4)
    *(volatile uint32_t*)(n) = 0xffff00ff;

  DE_MIXER0_BLD_FILL_COLOR_CTL = 0x101;
  DE_MIXER0_BLD_CH_RTCTL = 1;
  DE_MIXER0_BLD_PREMUL_CTL = 0;
  DE_MIXER0_BLD_BK_COLOR = 0xff000000;
  DE_MIXER0_BLD_CH_RTCTL = 1;
  DE_MIXER0_BLD_CTL(0) = 0x03010301;
  DE_MIXER0_BLD_SIZE = (1079<<16) | 1919;
  DE_MIXER0_BLD_OUT_COLOR = 0;
  DE_MIXER0_BLD_KEY_CTL = 0;
  DE_MIXER0_BLD_FILL_COLOR(0) = 0xff000000;
  DE_MIXER0_BLD_CH_ISIZE(0) = (1079<<16) | 1919;

  DE_MIXER0_OVL_UI1_ATTCTL(0) = (1<<0) | (4<<8);
  DE_MIXER0_OVL_UI1_MBSIZE(0) = (1079<<16) | 1919;
  DE_MIXER0_OVL_UI1_COOR(0) = 0;
  DE_MIXER0_OVL_UI1_PITCH(0) = 7680;
  DE_MIXER0_OVL_UI1_TOP_LADD(0) = 0x40000000;
  DE_MIXER0_OVL_UI1_SIZE = (1079<<16) | 1919;

  DE_MIXER0_VSU_REGS  = 0;
  DE_MIXER0_GSU1_REGS = 0;
  DE_MIXER0_GSU2_REGS = 0;
  DE_MIXER0_GSU3_REGS = 0;
  DE_MIXER0_FCE_REGS  = 0;
  DE_MIXER0_BWS_REGS  = 0;
  DE_MIXER0_LTI_REGS  = 0;
  DE_MIXER0_PEAK_REGS = 0;
  DE_MIXER0_ASE_REGS  = 0;
  DE_MIXER0_FCC_REGS  = 0;

  DE_MIXER0_GLB_DBUFFER = 1;
  //DE_MIXER0_GLB_STS = 0;

  uart_print_uint32(DE_MIXER0_GLB_STS);
  uart_print("\r\n");

}
