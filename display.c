#include <stdint.h>
#include "ccu.h"
#include "system.h"
#include "display.h"

void display_init() {
  PLL_VIDEO_CTRL_REG = (1<<31) | (1<<25) | (1<<24) | (98<<8) | (7<<0); // 287MHz
  BUS_CLK_GATING_REG1 |= (1<<12) | (1<<11) | (1<<3); // Enable DE, HDMI, TCON0
  BUS_SOFT_RST_REG1 |= (1<<12) | (3<<10) | (1<<3); // De-assert reset of DE, HDMI0/1, TCON0
  HDMI_CLK_REG = (1<<31); // Enable HDMI clk (use PLL3)
  HDMI_SLOW_CLK_REG = (1<<31); // Enable HDMI slow clk

  // HDMI PHY init, the following black magic is based on the procedure documented at:
  // http://linux-sunxi.org/images/3/38/AW_HDMI_TX_PHY_S40_Spec_V0.1.pdf
  HDMI_PHY_CFG1 = 0;
  udelay(5);
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
  HDMI_PHY_CFG1 |= (0xf<<8);
  HDMI_PHY_CFG1 |= (0xf<<4);
  HDMI_PHY_PLL1 = 0x3ddc5040;
  HDMI_PHY_PLL2 = 0x80084381;
  udelay(10000);
  HDMI_PHY_PLL3 = 1;
  HDMI_PHY_PLL1 |= (1<<25);
  udelay(100000);
  uint32_t tmp = (HDMI_PHY_STS & 0x1f800) >> 11;
  HDMI_PHY_PLL1 |= (1<<31) | (1<<30) | tmp;

  HDMI_PHY_CFG1 = 0x01FFFF7F;
  HDMI_PHY_CFG2 = 0x8063A800;
  HDMI_PHY_CFG3 = 0x0F81C485;

  /* enable read access to HDMI controller */
  HDMI_PHY_READ_EN = 0x54524545;
  /* descramble register offsets */
  HDMI_PHY_UNSCRAMBLE = 0x42494E47;

  // HDMI Config, based on the documentation at:
  // https://people.freebsd.org/~gonzo/arm/iMX6-HDMI.pdf
  HDMI_FC_INVIDCONF = (1<<6) | (1<<5) | (1<<4) | (1<<3); // Polarity etc
  HDMI_FC_INHACTIV0 = (1920 & 0xff);    // Horizontal pixels
  HDMI_FC_INHACTIV1 = (1920 >> 8);      // Horizontal pixels
  HDMI_FC_INHBLANK0 = (280 & 0xff);     // Horizontal blanking
  HDMI_FC_INHBLANK1 = (280 >> 8);       // Horizontal blanking

  HDMI_FC_INVACTIV0 = (1080 & 0xff);    // Vertical pixels
  HDMI_FC_INVACTIV1 = (1080 >> 8);      // Vertical pixels
  HDMI_FC_INVBLANK  = 45;               // Vertical blanking

  HDMI_FC_HSYNCINDELAY0 = (88 & 0xff);  // Horizontal Front porch
  HDMI_FC_HSYNCINDELAY1 = (88 >> 8);    // Horizontal Front porch
  HDMI_FC_VSYNCINDELAY  = 4;            // Vertical front porch
  HDMI_FC_HSYNCINWIDTH0 = (44 & 0xff);  // Horizontal sync pulse
  HDMI_FC_HSYNCINWIDTH1 = (0 >> 8);     // Horizontal sync pulse
  HDMI_FC_VSYNCINWIDTH  = 5;            // Vertical sync pulse
}
