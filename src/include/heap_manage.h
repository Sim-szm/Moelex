/*
 * =====================================================================================
 *
 *       Filename:  heap_manage.h
 *        Version:  1.0
 *        Created:  2013年11月07日 15时26分22秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef _HEAP_MANAGE_H
#define _HEAP_MANAGE_H
#define HEAP_START 0xD0000000
#define HEAP_END 0xFF000000
#include "moe_common.h"
typedef struct header{
	struct header *prev,*next;
	uint32_t allocated:1;
	uint32_t length:31;
}header_t;
/*I will refer to the size of a block being the number of bytes from the start of the
header to the end of the block - so within a block of size x, there will be x - sizeof(header_t) user-useable bytes.*/
void init_heap();
void *kmalloc(uint32_t l);
void kfree(void *p);
#endif
