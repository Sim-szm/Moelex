/*
 * =====================================================================================
 *
 *       Filename:  memory_manage.h
 *        Version:  1.0
 *        Created:  2013年11月04日 17时41分48秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef _MEMORY_MANAGE_H
#define _MEMORY_MANAGE_H
#include "moe_pmm.h"
#include "moe_descriptor_tables.h"
/* To make our code more readable we also define some labels. As you remember, bit 1 stands for present, bit 2 for writeable and bit 3 for user     	accessible */
#define PAGE_PRESENT 0x1
#define PAGE_WRITE 0x2
#define PAGE_USER 0x4
#define PAGE_MASK 0xFFFFF000
/* define the desired virtual positions of our page directory and our page tables */
#define PAGE_DIR_VIRTUAL_ADDR 0xFFBFF000
#define PAGE_TABLE_VIRTUAL_ADDR 0xFFC00000
/* write two macros to ease getting indices of tables and directories from addresses */
#define PAGE_DIR_IDX(x) ((uint32_t)x/1024)
#define PAGE_TABLE_IDX(x) ((uint32_t)x%1024)

void init_vmm();
void switch_page_directory(uint32_t *pd);
void map(uint32_t va,uint32_t pa, uint32_t flags);
void unmap(uint32_t va);
char get_mapping(uint32_t va,uint32_t *pa);
void page_fault(registers_t *regs);//page_fault interruption !
#endif
