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
#include "printk.h"
#include "moe_string.h"

thread_t *current_thread;
uint32_t next_tid = 0;
uint32_t thread_exit=0;
thread_t *init_threading(){
	thread_t *thread=kmalloc(sizeof(thread_t));
	thread->id=next_tid++;
	current_thread=thread;
	return thread;
}
thread_t *create_thread(int(*fn)(void*),void*arg,uint32_t *stack){
	thread_t *thread=kmalloc(sizeof(thread_t));
	memset(thread,0,sizeof(thread_t));
	thread->id=next_tid++;
	*--stack=(uint32_t)arg;
	*--stack=(uint32_t)&thread_exit;
	*--stack=(uint32_t)fn;
	*--stack=0;
	thread->ebp = (uint32_t)stack;
	thread->esp = (uint32_t)stack;
	return thread;
}
void switch_thread_work(thread_t *next){
	monitor_write("A-");
	__asm__ __volatile__("mov %%esp ,%0":"=r" (current_thread->esp));
	__asm__ __volatile__("mov %%ebp ,%0":"=r" (current_thread->ebp));
	__asm__ __volatile__("mov %%ebx ,%0":"=r" (current_thread->ebx));
	__asm__ __volatile__("mov %%esi ,%0":"=r" (current_thread->esi));
	__asm__ __volatile__("mov %%edi ,%0":"=r" (current_thread->edi));
	current_thread=next;
	monitor_write("B-");
	__asm__ __volatile__("mov %%edi ,%0":"=r" (current_thread->edi));
	__asm__ __volatile__("mov %%esi ,%0":"=r" (current_thread->esi));
	__asm__ __volatile__("mov %%ebx ,%0":"=r" (current_thread->ebx));
	__asm__ __volatile__("mov %%esp ,%0":"=r" (current_thread->esp));
	__asm__ __volatile__("mov %%ebp ,%0":"=r" (current_thread->ebp));
}
