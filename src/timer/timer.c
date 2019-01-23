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
#include "moe_timer.h"
#include "moe_descriptor_tables.h"
#include "moe_monitor.h"
#include "kthread.h"
#include "scheduler.h"
static uint32_t tick = 0;

static void timer_callback(registers_t regs){
//   monitor_clear();
   scheduler();
}
void init_timer(uint32_t frequency){
   // Firstly, register our timer callback.
   register_interrupt_handler(IRQ0, (interrupt_handler_t)timer_callback);

   // The value we send to the PIT is the value to divide it's input clock
   // (1193180 Hz) by, to get our required frequency. Important to note is
   // that the divisor must be small enough to fit into 16-bits.
   uint32_t divisor = 1193180 / frequency;

   // Send the command byte.
   // D7 D6 D5 D4 D3 D2 D1 D0
   // 0  0  1  1  0  1  1  0
   // it is 36H
   // set 8254 runing in mode 3
   outb(0x43, 0x36);

   // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
   uint8_t l = (uint8_t)(divisor & 0xFF);
   uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );

   // Send the frequency divisor.
   outb(0x40, l);
   outb(0x40, h);
} 
