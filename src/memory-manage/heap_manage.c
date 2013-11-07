/*
 * =====================================================================================
 *
 *       Filename:  heap_manage.c
 *        Version:  1.0
 *        Created:  2013年11月07日 18时04分14秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "memory_manage.h"
#include "heap_manage.h"
void split_chunk(header_t *chunk,uint32_t len);
void alloc_chunk(uint32_t start,uint32_t len);
void glue_chunk(header_t * chunk);
void heap_init(){

}
void *kmalloc(uint32_t l){
	l+=sizeof(header_t);
	header_t *cur=heap_first,*prev=0;
	while(cur){
		if(cur->allocated==0 && cur->length>=l){
			split_chunk(cur,l);
			cur->allocated=1;
			return (void*)((uint32_t)cur+sizeof(header_t));
		}
		prev=cur;
		cur=cur->next;
	}
	uint32_t chunk_start;
	if(pre)
	      chunk_start=(uint32_t)pre+pre->length;
	else{
		chunk_start=HEAD_START;
		heap_first=(header_t*)chunk_start;
	}
	alloc_chunk(chunk_start,l);
	cur=(header_t*)chunk_start;
	cur->pre=pre;
	cur->next=0;
	cur->allocated=1;
	cur->length=l;
	return (void*)(chunk_start+sizeof(header_t));
}
void kfree(void *p){
	header_t *head=(header_t*)((uint32_t)p-sizeof(header_t));
	head->allocated=0;
	glue_chunk(head);
}
