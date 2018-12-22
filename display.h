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

void display_init();
