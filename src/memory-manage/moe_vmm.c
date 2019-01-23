/*
 * =====================================================================================
 *
 *       Filename:  moe_vmm.c
 *        Version:  1.0
 *        Created:  2013年11月04日 18时02分21秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "memory_manage.h"
uint32_t *current_directory;
uint32_t *page_directory=(uint32_t*)PAGE_DIR_VIRTUAL_ADDR;
uint32_t *page_tables=(uint32_t*)PAGE_TABLE_VIRTUAL_ADDR;
extern char pmm_paging_active;
void init_vmm(){
	int i;
	uint32_t cr0;
	register_interrupt_handler(14,&page_fault);
	uint32_t *pd=(uint32_t*)pmm_alloc_page();
	memset((uint8_t*)pd,0,0x1000);
	pd[0]=pmm_alloc_page()|PAGE_PRESENT|PAGE_WRITE;
	uint32_t *pt=(uint32_t*)(pd[0]&PAGE_MASK);
	for(i=0;i<1024;i++){
		pt[i]=i*0x1000|PAGE_PRESENT|PAGE_WRITE;
	}

//out kernel code currently resides in the first 4MB of our available memory,we,also need to sure the virtual address match the physical address of these .
	pd[1022]=pmm_alloc_page()|PAGE_PRESENT|PAGE_WRITE;
	pt=(uint32_t*)(pd[1022]&PAGE_MASK);
	memset((uint8_t*)pt,0,0x1000);
	pt[1023]=(uint32_t)pd|PAGE_PRESENT|PAGE_WRITE;
	pd[1023]=(uint32_t)pd|PAGE_PRESENT|PAGE_WRITE;
	//now ,set the current directory !
	switch_page_directory(pd);
	asm volatile("mov %%cr0, %0" : "r=" (cr0));
	cr0|=0x80000000;
	asm volatile("mov %0, %%cr0" : : "r" (cr0));

	uint32_t pt_idx=PAGE_DIR_IDX((PMM_STACK_ADDR>>12));
	page_directory[pt_idx]=pmm_alloc_page()|PAGE_PRESENT|PAGE_WRITE;
	memset((uint8_t*)page_tables[pt_idx*1024],0,0x1000);
	pmm_paging_active=1;
}
// and we have to enable the paging ! put value into the cr3 register
void switch_page_directory(uint32_t *pd){
	current_directory=pd;
	asm volatile("mov %0,%%cr3"::"r"(pd));
}
//we just tell enabled paging ,but if we want to access physical address ,we have map virtual to physical and access virtual .
void map(uint32_t va,uint32_t pa,uint32_t flags){
	uint32_t virtual_page=va/0x1000;
	uint32_t pt_idx=PAGE_DIR_IDX(virtual_page);
	if(page_directory[pt_idx]==0){
		page_directory[pt_idx]=pmm_alloc_page()|PAGE_PRESENT|PAGE_WRITE;
		memset((uint8_t*)page_tables[pt_idx*1024],0,0x1000);
	}
	page_tables[virtual_page]=(pa&PAGE_MASK)|flags;
}
void unmap (uint32_t va){
	uint32_t virtual_page=va/0x1000;
	page_tables[virtual_page]=0;
	asm volatile("invlpg (%0)": :"a"(va));
}
char get_mapping(uint32_t va,uint32_t *pa){
	uint32_t virtual_page=va/0x1000;
	uint32_t pt_idx=PAGE_DIR_IDX(virtual_page);
	if(page_directory[pt_idx]==0){
		return 0;
	}
	if(page_tables[virtual_page]!=0){
		if(pa)*pa=page_tables[virtual_page]&PAGE_MASK;
		return 1;
	}
}
void page_fault(registers_t *regs){
	uint32_t cr2;
	asm volatile("mov %%cr2,%0":"=r"(cr2));
	printk("page fault at 0x%x,faulting address 0x%x\n",regs->eip,cr2);
	printk("Error code:%x\n",regs->err_code);
	panic("");
	while(1);
}
