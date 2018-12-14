/*
 * =====================================================================================
 *
 *       Filename:  moe_monitor.h
 *        Version:  1.0
 *        Created:  2013年10月22日 19时33分43秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef MOE_MONITOR_H
#define MOE_MONITOR_H
#include "moe_common.h"
void monitor_put(char c);
void monitor_clear();
void monitor_write(char *c);
void monitor_write_hex(uint32_t n);
void monitor_write_dec(uint32_t n);
#endif

