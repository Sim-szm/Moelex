/*
 * =====================================================================================
 *
 *       Filename:  kthread.h
 *        Version:  1.0
 *        Created:  2013年11月25日 16时25分47秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef KTHREAD_H
#define KTHREAD_H
typedef struct{
	uint32_t id;
	uint32_t ebp;
	uint32_t esp;
	uint32_t ebx;
	uint32_t edi;
	uint32_t esi;
}thread_t;

thread_t *init_threading();
thread_t *create_thread(int (*fn)(void*),void*arg,uint32_t *stack);
void switch_thread_work(thread_t *next);

#endif
