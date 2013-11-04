/*
 * =====================================================================================
 *
 *       Filename:  moe-pmm.c
 *        Version:  1.0
 *        Created:  2013年10月31日 15时37分02秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "printk.h"
#include "memory_manage.h"
#define MM_MAP
uint32_t pmm_stack_loc=PMM_STACK_ADDR; //start location for alloc memory
uint32_t pmm_stack_max=PMM_STACK_ADDR; //max location for alloc mempry
uint32_t pmm_location; // no paging 
char pmm_paging_active=0; //flag for paging manage
void init_pmm(multiboot_t *mboot_ptr){
#ifdef MM_MAP  //get the RAM condition by bios's data
	printk("mem_lower :0x%X\n",mboot_ptr->mem_lower*1024);
	printk("mem_upper :0x%X\n\n",mboot_ptr->mem_upper*1024);
	mmap_t *mmap;
	printk("mmap_addr = 0x%X,mmap_length = 0x%X\n\n",(unsigned)mboot_ptr->mmap_addr,(unsigned)mboot_ptr->mmap_length);
	for(mmap=(mmap_t*)mboot_ptr->mmap_addr;
				(unsigned long)mmap < mboot_ptr->mmap_addr + mboot_ptr->mmap_length;
				mmap=(mmap_t*)((unsigned long)mmap+mmap->size+sizeof(mmap->size))){
		printk("size=0x%X,base_addr=0x%X%X,length=0x%X%X,type=0x%X\n",
					(unsigned)mmap->size,
					(unsigned)mmap->base_addr_high,
					(unsigned)mmap->base_addr_low,
					(unsigned)mmap->length_high,
					(unsigned)mmap->length_low);
	}
#endif
	pmm_location=0; //start in zero 
}
void init_page_pmm(multiboot_t *mboot_ptr){
	uint32_t i=mboot_ptr->mmap_addr;
	while(i<mboot_ptr->mmap_addr+mboot_ptr->mmap_length){
		mmap_t *mmap=(mmap_t*)i;
		if(mmap->type==1&&mmap->base_addr_low==0x100000){
			uint32_t j=mmap->base_addr_low;
			j+=0x100000;
			while(j<mmap->base_addr_low+mmap->length_low && j<=PMM_MAX_SURPPORT){
				pmm_free_page(j);
				j+=0x1000;
			}
		}
		i+=mmap->size+sizeof(uint32_t);
	}
}
uint32_t pmm_alloc_page(){
	if(pmm_paging_active){
		if(pmm_stack_loc==PMM_STACK_ADDR)
		      panic("Error:out of memory !");
		pmm_stack_loc-=sizeof(uint32_t);
		uint32_t *stack=(uint32_t*)pmm_stack_loc;
		return *stack;
	}	
	return pmm_location+=0x1000;//4KB
}
void pmm_free_page(uint32_t p){
	if(p<pmm_location)
	      return;
	if(pmm_stack_max<=pmm_stack_loc){
		map(pmm_stack_max,p,PAGE_PRESENT|PAGE_WRITE);
		pmm_stack_max+=4096;
	}else{
		uint32_t *stack=(uint32_t*)pmm_stack_loc;
		*stack=p;
		pmm_stack_loc+=sizeof(uint32_t);
	}
}
