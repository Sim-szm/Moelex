/*
 * =====================================================================================
 *
 *       Filename:  scheduler.c
 *        Version:  1.0
 *        Created:  2013年11月25日 17时19分38秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "moe_common.h"
#include "heap_manage.h"
#include "kthread.h"
#include "scheduler.h"

thread_list_t *current_thread;
void scheduler(){
	if(!ready_queue)
	      return ;
	thread_list_t *iterator=ready_queue;
	while(iterator->next){
		iterator=iterator->next;
	}
	iterator->next=current_thread;
	current_thread=ready_queue;
	ready_queue=ready_queue->next;
	switch_thread_work(current_thread->thread);
}
void init_scheduler(thread_t *initial_thread){
	current_thread=(thread_list_t*)kmalloc(sizeof(thread_list_t*));
	current_thread->thread=initial_thread;
	current_thread->next=0;
	ready_queue=0;
}
void thread_is_ready(thread_t *t){
	thread_list_t *item=(thread_list_t*)kmalloc(sizeof(thread_list_t*));
	item->next=0;
	item->thread=t;
	if(!ready_queue)
	      ready_queue=item;
	else{
		thread_list_t *iterator=ready_queue;
		while(iterator->next){
			iterator=iterator->next;
		}
		iterator->next=item;
	}
}
void thread_not_ready(thread_t *t){
	// Attempt to find the thread in the ready queue.
	thread_list_t *iterator=ready_queue;
	if(iterator->thread==t){
		ready_queue=iterator->next;
		kfree(iterator);
		return ;
	}
	while(iterator->next){
		if(iterator->next->thread==t){
			thread_list_t *loca=iterator->next;
			iterator->next=loca->next;
			kfree(loca);
		}
		iterator=iterator->next;
	}
}
