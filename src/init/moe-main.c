/*
 * =====================================================================================
 *
 *       Filename:  Moe-main.c
 *        Version:  1.0
 *        Created:  2013年10月22日 20时20分55秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "init_head.h"
int Moe_main(multiboot_t *mboot_ptr){
	init_descriptor_tables();
	monitor_clear();
	monitor_write("Hello my Moelex kernel !\n");
	monitor_write("I got your face !\n");
	//asm volatile("int $0x3");
	//asm volatile("int $0x4");
	asm volatile("sti");
	init_timer(50);
	return 0;
}
