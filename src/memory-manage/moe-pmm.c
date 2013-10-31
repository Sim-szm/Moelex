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
#include "moe-pmm.h"
uint32_t pmm_stack_loc=PMM_STACK_ADDR; //start location for alloc memory
uint32_t pmm_stack_max=PMM_STACK_ADDR; //max location for alloc mempry
uint32_t pmm_location; // no paging 
char mm_paging_active=0; //flag for paging manage
void init_pmm(multiboot_t *mboot_ptr){
	//wait , I need to learn ！
}
