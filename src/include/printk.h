/*
 * =====================================================================================
 *
 *       Filename:  printk.h
 *        Version:  1.0
 *        Created:  2013年10月31日 16时43分07秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef PRINTK_H
#define PRINTK_H
#include "moe-string.h"

typedef __builtin_va_list va_list;
#define va_start(ap, last)         (__builtin_va_start(ap, last))
#define va_arg(ap, type)           (__builtin_va_arg(ap, type))
#define va_end(ap) 

void printk(const char *fmt,...);
#endif
