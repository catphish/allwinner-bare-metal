#include "usb.h"
#include "uart.h"
#include "ccu.h"
#include "ports.h"
#include "system.h"

void print_usb_status() {
  uart_print_uint32(USB1_O_HCREVISION);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCCONTROL);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCCOMMANDSTATUS);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCINTERRUPTSTATUS);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCINTERRUPTENABLE);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCINTERRUPTDISABLE);
  uart_print("\r\n");

  uart_print_uint32(USB1_O_HCHCCA);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCPERIODCURRENTED);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCCONTROLHEADED);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCCONTROLCURRENTED);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCBULKHEADED);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCBULKCURRENTED);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCDONEHEAD);
  uart_print("\r\n");

  uart_print_uint32(USB1_O_HCFMINTERVAL);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCFMREMAINING);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCFMNUMBER);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCPERIODDICSTART);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCLSTHRESHOLD);
  uart_print("\r\n");

  uart_print_uint32(USB1_O_HCRHDESCRIPTORA);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCRHDESCRIPTORB);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCRHSTATUS);
  uart_print(" ");
  uart_print_uint32(USB1_O_HCRHPORTSTATUS);
  uart_print("\r\n");

  // uart_print_uint32(USB1_E_CAPLENGTH);
  // uart_print(" ");
  // uart_print_uint32(USB1_E_HCIVERSION);
  // uart_print(" ");
  // uart_print_uint32(USB1_E_HCSPARAMS);
  // uart_print(" ");
  // uart_print_uint32(USB1_E_HCCPARAMS);
  // uart_print(" ");
  // uart_print_uint32(USB1_E_HCSPPORTROUTE);

  // uart_print("\r\n");
  // uart_print_uint32(USB1_E_USBCMD);
  // uart_print(" ");
  // uart_print_uint32(USB1_E_USBSTS);
  // uart_print(" ");
  // uart_print_uint32(USB1_E_USBINTR);
  // uart_print(" ");
  // uart_print_uint32(USB1_E_FRINDEX);
  // uart_print(" ");
  // uart_print_uint32(USB1_E_CTRLDSSEGMENT);
  // uart_print(" ");
  // uart_print_uint32(USB1_E_PERIODICLISTBASE);
  // uart_print(" ");
  // uart_print_uint32(USB1_E_ASYNCLISTADDR);
  // uart_print(" ");
  // uart_print_uint32(USB1_E_CONFIGFLAG);
  // uart_print(" ");
  // uart_print_uint32(USB1_E_PORTSC);
  // uart_print("\r\n");

  uart_print("\r\n");
}

void memset(void* location, uint8_t chr, int length) {
  for(int n=0; n<length;n++)
    ((uint8_t*)location)[n] = chr;
}

void usb_init() {
  BUS_CLK_GATING0 |= (1<<29)|(1<<25);
  BUS_SOFT_RST0   |= (1<<29)|(1<<25);
  USBPHY_CFG      |= (1<<17) | (1<<9) | (1<<1);
  USB1_HCI_ICR    = 0x00000701;

  // USB1_E_CONFIGFLAG = 0;
  // USB1_E_USBCMD |= 1;

  udelay(100000);

  // memset(ed, 0, 16*5);
  // memset(&hcca, 0, 256);

  for(int n=0;n<32;n++)
    hcca.HccaInterrruptTable[n] = (uint32_t)ed;

  ed[0].info = 0x4000;
  //ed[1].info = 0x1800 | 0x402000;

  print_usb_status();

  //USB1_O_HCRHDESCRIPTORA = 0x10000204;
  //USB1_O_HCRHDESCRIPTORB = 0x00020002;

  // USB1_O_HCCONTROL |= 0x80;
  // USB1_O_HCFMINTERVAL = 0x27782EDF;

  USB1_O_HCCOMMANDSTATUS |= 1;
  while(USB1_O_HCCOMMANDSTATUS & 1);

  udelay(100000);

  USB1_O_HCFMINTERVAL = 0x27782EDF;
  USB1_O_HCPERIODDICSTART = 0x2A2F;
  USB1_O_HCHCCA = (uint32_t)&hcca;

  udelay(100000);

  // USB1_O_HCCONTROLHEADED    = (uint32_t)&ed;
  // USB1_O_HCCONTROLCURRENTED = 0;
  // USB1_O_HCBULKHEADED       = (uint32_t)&ed;
  // USB1_O_HCBULKCURRENTED    = 0;

  USB1_O_HCCONTROL = 0x6B0;
  USB1_O_HCRHSTATUS = 0x8000;
  USB1_O_HCINTERRUPTSTATUS = 4;
  USB1_O_HCINTERRUPTENABLE = 0xC000005B;
  // USB1_O_HCRHPORTSTATUS = 0x100;

  print_usb_status();
  udelay(100000);
  print_usb_status();

  // for(int n=0;n<0x01F8;n+=4) {
  //   uart_print("A: ");
  //   uart_print_uint32(n);
  //   uart_print(": ");
  //   uart_print_uint32(*(volatile uint32_t *)(R_PRCM_BASE + n));
  //   uart_print("\r\n");
  // }

  // uart_print("HCI_ICR: ");
  // uart_print_uint32(*(volatile uint32_t *)(USB1_BASE + 0x800));
  // uart_print(" HSIC_STATUS: ");
  // uart_print_uint32(*(volatile uint32_t *)(USB1_BASE + 0x804));
  // uart_print("\r\n");

  uart_print("\r\n");

}
