// The HDMI registers base address.
#define HDMI_BASE 0x01C16000

// HDMI register helpers.
#define HDMI_VERSION           *(volatile uint32_t *)(HDMI_BASE + 0x0000)
#define HDMI_CTRL           *(volatile uint32_t *)(HDMI_BASE + 0x0000)
#define HDMI_INT_STATUS           *(volatile uint32_t *)(HDMI_BASE + 0x0000)
#define HDMI_HPD           *(volatile uint32_t *)(HDMI_BASE + 0x0000)
#define HDMI_VID_CTRL           *(volatile uint32_t *)(HDMI_BASE + 0x0000)
#define HDMI_VID_TIMING0           *(volatile uint32_t *)(HDMI_BASE + 0x0000)
#define HDMI_VID_TIMING1           *(volatile uint32_t *)(HDMI_BASE + 0x0000)
#define HDMI_VID_TIMING2           *(volatile uint32_t *)(HDMI_BASE + 0x0000)
#define HDMI_VID_TIMING3           *(volatile uint32_t *)(HDMI_BASE + 0x0000)
#define HDMI_VID_TIMING4           *(volatile uint32_t *)(HDMI_BASE + 0x0000)
#define HDMI_VERSION           *(volatile uint32_t *)(HDMI_BASE + 0x0000)
#define HDMI_VERSION           *(volatile uint32_t *)(HDMI_BASE + 0x0000)
#define HDMI_VERSION           *(volatile uint32_t *)(HDMI_BASE + 0x0000)
#define HDMI_VERSION           *(volatile uint32_t *)(HDMI_BASE + 0x0000)
#define HDMI_VERSION           *(volatile uint32_t *)(HDMI_BASE + 0x0000)

void display_init();
