/*
 * =====================================================================================
 *
 *       Filename:  scheduler.h
 *        Version:  1.0
 *        Created:  2013年11月25日 17时15分47秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "kthread.h"
typedef struct thread_list{
	thread_t *thread;
	struct thread_list *next;
}thread_list_t;
thread_list_t *ready_queue;
void init_scheduler(thread_t *initial_thread);
void thread_is_ready(thread_t * t);
void thread_not_ready(thread_t *t);
void scheduler();
#endif
