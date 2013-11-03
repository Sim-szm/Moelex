/*
 * =====================================================================================
 *
 *       Filename:  keyboard.c
 *        Version:  1.0
 *        Created:  2013年11月03日 17时09分30秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "moe-descriptor_tables.h"
#include "moe-keyboard.h"
void keyboard_handler(){           //过程：按下键盘->芯片收到中断信号->将中断号发给cpu->cpu加32得到中断向量->cpu去向量表中找到函数指针__irq1->__irq1跳到do_irq->do_irq通过中断号索引函数指针数组irq_handler[]，最终执行中断函数keyboard_handler()。  
  uint8_t scancode = inb(0x60); //read code from buffer ,only one byte when the interrupt occur，每次中断只处理缓冲区中的一个字节  
	uint8_t ascii = 0;
	#define LEFTSHIFT 0x2A
	#define RIGHTSHIFT 0x36
  switch (scancode) {//键盘按下和松开都会产生扫描码  
  case LEFTSHIFT:  
  case RIGHTSHIFT:  
    shift = 0x3B;         // Nothing special.只是按下shift键的话不做任何处理，注意shift是一个全局变量  
    break;  
  case LEFTSHIFT | 0x80:    //break code,relax the key  
  case RIGHTSHIFT | 0x80:   //松开键盘，shift标志清0  
    shift = 0;  
    break;  
  default://the other character  
      if (scancode < 0x3B){  
      ascii = keymap[scancode + shift];//由扫描码索引得到字符  
      printk("%c",ascii);  
    }  
  }  
}  
void enable_irq(int irq){  
  if (irq > 8)               //从芯片irq>8  
    outb(0x43,0x36);//set bit 0 means open,使用inb(SLAVE)读取从芯片的配置，并将irq号位清0，使能此中断。   
    //outb(inb(MASTER)&(~(1<<irq)),MASTER);    
}   
void keyboard_init(){
	register_interrupt_handler(IRQ1,(interrupt_handler_t)keyboard_handler);
	enable_irq(IRQ1);
}
