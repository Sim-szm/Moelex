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
void glue_chunk(header_t *chunk);
void free_chunk(header_t *chunk);
uint32_t heap_max=HEAP_START;
header_t *heap_first=0;
void heap_init(){

}
void *kmalloc(uint32_t l){
	l+=sizeof(header_t);
	header_t *cur=heap_first,*prev_header=0;
	while(cur){
		if(cur->allocated==0 && cur->length>=l){
			split_chunk(cur,l);
			cur->allocated=1;
			return (void*)((uint32_t)cur+sizeof(header_t));
		}
		prev_header=cur;
		cur=cur->next;
	}
	uint32_t chunk_start;
	if(prev_header)
	      chunk_start=(uint32_t)prev_header+prev_header->length;
	else{
		chunk_start=HEAP_START;
		heap_first=(header_t*)chunk_start;
	}
	alloc_chunk(chunk_start,l);
	cur=(header_t*)chunk_start;
	cur->prev=prev_header;
	cur->next=0;
	cur->allocated=1;
	cur->length=l;
	if (prev_header){
		prev_header->next = cur;
	}
	return (void*)(chunk_start+sizeof(header_t));
}
void kfree(void *p){
	header_t *head=(header_t*)((uint32_t)p-sizeof(header_t));
	head->allocated=0;
	glue_chunk(head);
}
void alloc_chunk(uint32_t start,uint32_t len){
	while(start+len>heap_max){
		uint32_t page=pmm_alloc_page();
		map(heap_max,page,PAGE_PRESENT|PAGE_WRITE);
		heap_max+=0x1000;
	}
}
void split_chunk(header_t *chunk,uint32_t len){
	if(chunk->length-len>sizeof(header_t)){
		header_t *newchunk=(header_t*)((uint32_t)chunk+chunk->length);
		newchunk->prev=chunk;
		newchunk->next=0;
		newchunk->allocated=0;
		newchunk->length=chunk->length-len;
		chunk->next=newchunk;
		chunk->length=len;
	}
}
void glue_chunk(header_t *chunk){
	if(chunk->next && chunk->next->allocated==0){
		chunk->length=chunk->length+chunk->next->length;
		chunk->next->next->prev=chunk;
		chunk->next=chunk->next->next;
	}
	if(chunk->prev && chunk->prev->allocated==0){
		chunk->prev->length=chunk->prev->length+chunk->length;
		chunk->prev->next=chunk->next;
		chunk->next->prev=chunk->prev;
		chunk=chunk->prev;
	}
	if(chunk->next==0){
		free_chunk(chunk);
	}
}
void free_chunk(header_t *chunk){
	if(chunk->prev==0)
	      heap_first=0;
	else
	      chunk->prev->next=0;

	while((heap_max-0x1000)>=(uint32_t)chunk){
		heap_max-=0x1000;
		uint32_t page;
		get_mapping(heap_max,&page);
		pmm_free_page(page);
		unmap(heap_max);
	}
}
