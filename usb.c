#include "usb.h"
#include "uart.h"
#include "ccu.h"
#include "ports.h"
#include "system.h"

// Allocate memory for a setup request and a setup response in DRAM
char setup_request[8] __attribute__ ((aligned (16))) = {0x80, 0x06, 0x00, 0x01, 0x00, 0x00, 0x08, 0x00};
char setup_response[8] __attribute__ ((aligned (16)));

// Allocate memory for hcca, ED and 3 x TD
struct hcca hcca;
struct ed controlED;
struct td setup_td[3];

void usb_init() {
  // Enable clocks
  BUS_CLK_GATING0 |= (1<<29)|(1<<25);
  BUS_SOFT_RST0   |= (1<<29)|(1<<25);
  USBPHY_CFG      |= (1<<17) | (1<<9) | (1<<1);
  // Enabe INCR16, INCR8, INCR4
  USB1_HCI_ICR    = 0x00000701;

  // Reset OHCI
  USB1_O_HCCOMMANDSTATUS |= 1;
  while(USB1_O_HCCOMMANDSTATUS & 1);

  // Basic OHCI setup
  USB1_O_HCFMINTERVAL = 0xA7782EDF; // Magic constant, sorry
  USB1_O_HCPERIODDICSTART = 0x2A2F; // Magic constant, sorry
  USB1_O_HCHCCA = (uint32_t)&hcca;
  USB1_O_HCCONTROLHEADED = (uint32_t)&controlED;
  USB1_O_HCCONTROLCURRENTED = 0;

  // Build the 3 transport descriptors for the setup process
  setup_td[0].info = 0xE2E00000;
  setup_td[0].cbp = (uint32_t)setup_request;
  setup_td[0].nexttd = (uint32_t)&setup_td[1];
  setup_td[0].bufferend = ((uint32_t)setup_request)+7;

  setup_td[1].info = 0xE3F00000;
  setup_td[1].cbp = (uint32_t)setup_response;
  setup_td[1].nexttd = (uint32_t)&setup_td[2];
  setup_td[1].bufferend = ((uint32_t)setup_response)+7;

  setup_td[2].info = 0xE3080000;
  setup_td[2].cbp = 0;
  setup_td[2].nexttd = (uint32_t)&setup_td[3];
  setup_td[2].bufferend = 0;

  // Build the endpoint descriptor for the setup process
  controlED.info = 0x00082000;
  controlED.headp = &setup_td[0];
  controlED.tailp = &setup_td[3];
  controlED.nexted = 0;

  // Reset the root hub port
  USB1_O_HCRHPORTSTATUS = (1<<4);
  udelay(10000);

  // Enable control packets
  USB1_O_HCCONTROL = 0x90;
  // Inform controller of new control data
  USB1_O_HCCOMMANDSTATUS |= 2;

  udelay(10000);

  // Everything that follows is to check the results.

  uart_print("Setup Request:  ");
  for(int n=0; n<8; n++) {
    uart_print_uint8(setup_request[n]);
    uart_print(" ");
  }
  uart_print("\r\n");

  uart_print("Setup Response: ");
  for(int n=0; n<8; n++) {
    uart_print_uint8(setup_response[n]);
    uart_print(" ");
  }
  uart_print("\r\n");

}
