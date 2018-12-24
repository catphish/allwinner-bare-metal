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
#define TCON0_GCTL_REG   *(volatile uint32_t*)(TCON0_BASE + 0x000)
#define TCON0_CTL_REG    *(volatile uint32_t*)(TCON0_BASE + 0x090)
#define TCON0_BASIC0_REG *(volatile uint32_t*)(TCON0_BASE + 0x094)
#define TCON0_BASIC1_REG *(volatile uint32_t*)(TCON0_BASE + 0x098)
#define TCON0_BASIC2_REG *(volatile uint32_t*)(TCON0_BASE + 0x09C)
#define TCON0_BASIC3_REG *(volatile uint32_t*)(TCON0_BASE + 0x0A0)
#define TCON0_BASIC4_REG *(volatile uint32_t*)(TCON0_BASE + 0x0A4)
#define TCON0_BASIC5_REG *(volatile uint32_t*)(TCON0_BASE + 0x0A8)

// DE2
#define DE_BASE 0x01000000
#define DE_SCLK_GATE          *(volatile uint32_t*)(DE_BASE + 0x000)
#define DE_HCLK_GATE          *(volatile uint32_t*)(DE_BASE + 0x004)
#define DE_AHB_RESET          *(volatile uint32_t*)(DE_BASE + 0x008)
#define DE_SCLK_DIV           *(volatile uint32_t*)(DE_BASE + 0x00C)
#define DE_DE2TCON_MUX        *(volatile uint32_t*)(DE_BASE + 0x010)
#define DE_CMD_CTL            *(volatile uint32_t*)(DE_BASE + 0x014)
#define DE_DI_CTL             *(volatile uint32_t*)(DE_BASE + 0x01C)

#define DE_MIXER0             (DE_BASE + 0x100000)

#define DE_MIXER0_GLB         (DE_MIXER0 + 0x0)
#define DE_MIXER0_GLB_CTL     *(volatile uint32_t*)(DE_MIXER0_GLB + 0x000)
#define DE_MIXER0_GLB_STS     *(volatile uint32_t*)(DE_MIXER0_GLB + 0x004)
#define DE_MIXER0_GLB_DBUFFER *(volatile uint32_t*)(DE_MIXER0_GLB + 0x008)
#define DE_MIXER0_GLB_SIZE    *(volatile uint32_t*)(DE_MIXER0_GLB + 0x00C)

#define DE_MIXER0_BLD                (DE_MIXER0 + 0x1000)
#define DE_MIXER0_BLD_FILL_COLOR_CTL *(volatile uint32_t*)(DE_MIXER0_BLD + 0x000)
#define DE_MIXER0_BLD_CH_RTCTL       *(volatile uint32_t*)(DE_MIXER0_BLD + 0x080)
#define DE_MIXER0_BLD_BK_COLOR       *(volatile uint32_t*)(DE_MIXER0_BLD + 0x088)
#define DE_MIXER0_BLD_CTL            ((volatile uint32_t*)(DE_MIXER0_BLD + 0x090))
#define DE_MIXER0_BLD_OUT_COLOR      *(volatile uint32_t*)(DE_MIXER0_BLD + 0x0FC)
#define DE_MIXER0_BLD_SIZE           *(volatile uint32_t*)(DE_MIXER0_BLD + 0x08C)
#define DE_MIXER0_BLD_FILL_COLOR_0   *(volatile uint32_t*)(DE_MIXER0_BLD + 0x004)
#define DE_MIXER0_BLD_ISIZE_0        *(volatile uint32_t*)(DE_MIXER0_BLD + 0x008)
#define DE_MIXER0_BLD_KEY_CTL        *(volatile uint32_t*)(DE_MIXER0_BLD + 0x0B0)

#define DE_MIXER0_OVL_V              (DE_MIXER0 + 0x02000)
#define DE_MIXER0_OVL_V_ATTCTL       *(volatile uint32_t*)(DE_MIXER0_OVL_V + 0x000)

void display_init();
