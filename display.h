// The HDMI registers base address.
#define HDMI_BASE 0x01EE0000
#define HDMI_PHY_BASE (HDMI_BASE + 0x10000)

// HDMI register helpers.
#define HDMI_PHY_POL        *(volatile uint32_t*)(HDMI_BASE + 0x10000)
#define HDMI_PHY_READ_EN    *(volatile uint32_t*)(HDMI_BASE + 0x10010)
#define HDMI_PHY_UNSCRAMBLE *(volatile uint32_t*)(HDMI_BASE + 0x10014)
#define HDMI_PHY_CFG1       *(volatile uint32_t*)(HDMI_BASE + 0x10020)
#define HDMI_PHY_CFG2       *(volatile uint32_t*)(HDMI_BASE + 0x10024)
#define HDMI_PHY_CFG3       *(volatile uint32_t*)(HDMI_BASE + 0x10028)
#define HDMI_PHY_PLL1       *(volatile uint32_t*)(HDMI_BASE + 0x1002C)
#define HDMI_PHY_PLL2       *(volatile uint32_t*)(HDMI_BASE + 0x10030)
#define HDMI_PHY_PLL3       *(volatile uint32_t*)(HDMI_BASE + 0x10034)
#define HDMI_PHY_STS        *(volatile uint32_t*)(HDMI_BASE + 0x10038)
#define HDMI_PHY_CEC        *(volatile uint32_t*)(HDMI_BASE + 0x1003C)

#define HDMI_FC_INVIDCONF   *(volatile uint8_t*)(HDMI_BASE + 0x1000)

#define HDMI_FC_INHACTIV0   *(volatile uint8_t*)(HDMI_BASE + 0x1001)
#define HDMI_FC_INHACTIV1   *(volatile uint8_t*)(HDMI_BASE + 0x1002)
#define HDMI_FC_INHBLANK0   *(volatile uint8_t*)(HDMI_BASE + 0x1003)
#define HDMI_FC_INHBLANK1   *(volatile uint8_t*)(HDMI_BASE + 0x1004)

#define HDMI_FC_INVACTIV0   *(volatile uint8_t*)(HDMI_BASE + 0x1005)
#define HDMI_FC_INVACTIV1   *(volatile uint8_t*)(HDMI_BASE + 0x1006)
#define HDMI_FC_INVBLANK    *(volatile uint8_t*)(HDMI_BASE + 0x1007)

#define HDMI_FC_HSYNCINDELAY0 *(volatile uint8_t*)(HDMI_BASE + 0x1008)
#define HDMI_FC_HSYNCINDELAY1 *(volatile uint8_t*)(HDMI_BASE + 0x1009)
#define HDMI_FC_HSYNCINWIDTH0 *(volatile uint8_t*)(HDMI_BASE + 0x100A)
#define HDMI_FC_HSYNCINWIDTH1 *(volatile uint8_t*)(HDMI_BASE + 0x100B)
#define HDMI_FC_VSYNCINDELAY  *(volatile uint8_t*)(HDMI_BASE + 0x100C)
#define HDMI_FC_VSYNCINWIDTH  *(volatile uint8_t*)(HDMI_BASE + 0x100D)

#define HDMI_FC_CTRLDUR       *(volatile uint8_t*)(HDMI_BASE + 0x1011)
#define HDMI_FC_EXCTRLDUR     *(volatile uint8_t*)(HDMI_BASE + 0x1012)
#define HDMI_FC_EXCTRLSPAC    *(volatile uint8_t*)(HDMI_BASE + 0x1013)
#define HDMI_FC_CH0PREAM      *(volatile uint8_t*)(HDMI_BASE + 0x1014)
#define HDMI_FC_CH1PREAM      *(volatile uint8_t*)(HDMI_BASE + 0x1015)
#define HDMI_FC_CH2PREAM      *(volatile uint8_t*)(HDMI_BASE + 0x1016)
#define HDMI_MC_FLOWCTRL      *(volatile uint8_t*)(HDMI_BASE + 0x4004)
#define HDMI_MC_CLKDIS        *(volatile uint8_t*)(HDMI_BASE + 0x4001)

#define HDMI_VP_STUFF        *(volatile uint8_t*)(HDMI_BASE + 0x0802)
#define HDMI_VP_CONF         *(volatile uint8_t*)(HDMI_BASE + 0x0804)

#define HDMI_TX_INVID0       *(volatile uint8_t*)(HDMI_BASE + 0x0200)
#define HDMI_TX_INSTUFFING   *(volatile uint8_t*)(HDMI_BASE + 0x0201)

// TCON
#define TCON0_BASE 0x01C0C000
#define TCON0_GCTL_REG    *(volatile uint32_t*)(TCON0_BASE + 0x000)
#define TCON0_CTL_REG    *(volatile uint32_t*)(TCON0_BASE + 0x090)
#define TCON0_BASIC0_REG *(volatile uint32_t*)(TCON0_BASE + 0x094)
#define TCON0_BASIC1_REG *(volatile uint32_t*)(TCON0_BASE + 0x098)
#define TCON0_BASIC2_REG *(volatile uint32_t*)(TCON0_BASE + 0x09C)
#define TCON0_BASIC3_REG *(volatile uint32_t*)(TCON0_BASE + 0x0A0)
#define TCON0_BASIC4_REG *(volatile uint32_t*)(TCON0_BASE + 0x0A4)
#define TCON0_BASIC5_REG *(volatile uint32_t*)(TCON0_BASE + 0x0A8)

void display_init();
