/*
 * =====================================================================================
 *
 *       Filename:  panic.c
 *        Version:  1.0
 *        Created:  2013年10月31日 16时22分38秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "moe-common.h"
#include "panic.h"
#include "elf.h"
static void print_stack_trace();
extern elf_t kernel_elf;
void panic(const char *msg){
	printk("*** System panic : %s\n",msg);
	print_stack_trace();
	printk("*****\n");
	while(1);
}
void print_stack_trace(){
	uint32_t *ebp,*eip;
	asm volatile ("mov %%ebp,%0":"=r"(ebp));
	while(ebp){
		eip=ebp+1;
		printk("[0x%x] %s\n",*eip,elf_lookup_symbol(*eip,&kernel_elf));
		ebp=(uint32_t*)*ebp;
	}
}
