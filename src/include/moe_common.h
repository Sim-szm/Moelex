/*
 * =====================================================================================
 *
 *       Filename:  moe_common.h
 *        Version:  1.0
 *        Created:  2013年10月22日 19时23分21秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef MOE_COMMON_H
#define MOE_COMMON_H 
typedef unsigned int uint32_t ;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
typedef char int8_t;
void outb(uint16_t port,uint8_t value );
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
#endif 

