/*
 * =====================================================================================
 *
 *       Filename:  moe-pmm.h
 *        Version:  1.0
 *        Created:  2013年10月30日 21时24分15秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef _MOE_PMM_H
#define _MOE_PMM_H
#include "multiboot.h"
#include "moe-common.h"
#define PMM_STACK_ADDR 0xFF000000
#define PMM_MAX_SURPPORT 0x20000000
void init_pmm(multiboot *mboot_ptr);
void init_page_pmm(multiboot *mboot_ptr);
uint32_t pmm_alloc_page();
void pmm_free_page(uint32_t p);
extern char mm_paging_active ;

#endif
