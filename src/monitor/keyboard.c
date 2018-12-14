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
#include "moe_descriptor_tables.h"
#include "moe_keyboard.h"
void keyboard_handler(){          
	uint8_t scancode = inb(0x60); //read code from buffer ,deal with one chacter from buffer .
	uint8_t ascii = 0;
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
    outb(0x43,0x36);
}   
void keyboard_init(){
	register_interrupt_handler(IRQ1,(interrupt_handler_t)keyboard_handler);
	enable_irq(IRQ1);
}
