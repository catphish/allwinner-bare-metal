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

  USB1_O_HCCOMMANDSTATUS |= 1;
  while(USB1_O_HCCOMMANDSTATUS & 1);

  print_usb_status();

}
