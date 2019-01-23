/*
 * =====================================================================================
 *
 *       Filename:  moelex_main.c
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
int flag = 0;
int moelex_main(multiboot_t *mboot_ptr){
	init_descriptor_tables();
	monitor_clear();
	monitor_write("Start Moelex kernel !\n");
	monitor_write("Welcome to Moelex !\n");
	//asm volatile("int $0x3");
	__asm__ __volatile__("int $0x4");
//	__asm__ __volatile__("sti");
	kernel_elf=elf_from_multiboot(mboot_ptr);
	panic("testing trace stack !");
	init_timer(200);
	init_pmm(mboot_ptr); 
	init_vmm();
	init_page_pmm(mboot_ptr);
	monitor_write("malloc data space :\n");
	void *address_1=kmalloc(50);
	printk("address_1 :50 bytes in 0x%X\n",address_1);
	void *address_2=kmalloc(500);
	printk("address_2 : 500 bytes in 0x%X\n ",address_2);
	//free mem
	printk("free mem in 0x%X\n",address_1);
	kfree(address_1);
	printk("free mem in 0x%X\n",address_2);
	kfree(address_2);
	monitor_write("keyboard interrupt start :\n");
	keyboard_init();
	//monitor_write(" timer trigger interrupts with kthread:\n");
	//init_scheduler(init_threading());
	//scheduler();
//	while(1){
        __asm__ __volatile__("sti");
//	}
	return 0;
}
