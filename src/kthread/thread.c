/*
 * =====================================================================================
 *
 *       Filename:  thread.c
 *        Version:  1.0
 *        Created:  2013年11月25日 16时31分04秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "heap_manage.h"
#include "kthread.h"
#include "string.h"

thread_t *init_threading(){
	thread_t *thread=kmalloc(sizeof(thread_t));
	thread->id=next_tid++;
	current_thread=thread;
	return thread;
}
thread_t *create_thread(int(*fn)(void*),void*arg,uint32_t *stack){
	thread_t *thread=kmalloc(sizeof(thread_t));
	memset(thread,0,sizeof(thread_t));
	thread_t->id=next_tid++;
	*--stack=(uint32_t)arg;
	*--stack=(uint32_t)&thread_exit;
	*--stack=(uint32_t)fn;
	*--stack=0;
	thread->ebp = (uint32_t)stack;
	thread->esp = (uint32_t)stack;
	return thread;
}
void switch_thread_work(thread_t *next){
	asm volatile("mov %%esp ,%0":"=r" (current_thread->esp));
	asm volatile("mov %%ebp ,%0":"=r" (current_thread->ebp));
	asm volatile("mov %%ebx ,%0":"=r" (current_thread->ebx));
	asm volatile("mov %%esi ,%0":"=r" (current_thread->esi));
	asm volatile("mov %%edi ,%0":"=r" (current_thread->edi));
	current_thread=next;
	asm volatile("mov %%edi ,%0":"=r" (current_thread->edi));
	asm volatile("mov %%esi ,%0":"=r" (current_thread->esi));
	asm volatile("mov %%ebx ,%0":"=r" (current_thread->ebx));
	asm volatile("mov %%esp ,%0":"=r" (current_thread->esp));
	asm volatile("mov %%ebp ,%0":"=r" (current_thread->ebp));
}
