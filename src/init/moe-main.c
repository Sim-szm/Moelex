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
elf_t kernel_elf;
int Moe_main(multiboot_t *mboot_ptr){
	init_descriptor_tables();
	monitor_clear();
	monitor_write("Hello my Moelex kernel !\n");
	monitor_write("I got your face !\n");
	//asm volatile("int $0x3");
	asm volatile("int $0x4");
//	asm volatile("sti");
	kernel_elf=elf_from_multiboot(mboot_ptr);
	panic("Testing trace stack !");
	init_pmm();
	init_vmm();
	init_page_pmm(mboot_ptr);
	monitor_write("malloc for data :\n");
	void *r1=kmalloc(50);
	printk("r1 :50 bytes in 0x%X\n",r1);
	void *r2=kmalloc(500);
	printk("r2 : 50000 bytes in 0x%X\n ",r2);
	kfree(r1);
	kfree(r2);
	//monitor_write("keyboard interrupt start :\n");
	monitor_write("print charater A and B with two thread :\n");
	keyboard_init();
	/*init_timer(50);*/
        asm volatile("sti");
	return 0;
}
