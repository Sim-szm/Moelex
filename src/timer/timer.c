/*
 * =====================================================================================
 *
 *       Filename:  timer.c
 *        Version:  1.0
 *        Created:  2013年10月28日 20时59分43秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "moe-timer.h"
#include "moe-descriptor_tables.h"
#include "moe-monitor.h"
static uint32_t tick = 0;

static void timer_callback(registers_t regs){
   tick++;
//   monitor_clear();
   monitor_write("Tick: ");
   monitor_write_dec(tick);
   monitor_write("\n");
}
void init_timer(uint32_t frequency){
   // Firstly, register our timer callback.
   register_interrupt_handler(IRQ0, (interrupt_handler_t)timer_callback);

   // The value we send to the PIT is the value to divide it's input clock
   // (1193180 Hz) by, to get our required frequency. Important to note is
   // that the divisor must be small enough to fit into 16-bits.
   uint32_t divisor = 1193180 / frequency;

   // Send the command byte.
   outb(0x43, 0x36);

   // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
   uint8_t l = (uint8_t)(divisor & 0xFF);
   uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );

   // Send the frequency divisor.
   outb(0x40, l);
   outb(0x40, h);
} 
