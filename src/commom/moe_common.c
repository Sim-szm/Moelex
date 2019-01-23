/*
 * =====================================================================================
 *
 *       Filename:  moe_common.c
 *        Version:  1.0
 *        Created:  2013年10月22日 19时31分38秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "moe_common.h"
void outb(uint16_t port, uint8_t value)
{
    __asm__ __volatile__("outb %1, %0" : : "dN" (port), "a" (value));
}
uint8_t inb(uint16_t port)
{
   uint8_t ret;
   __asm__ __volatile__("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}
uint16_t inw(uint16_t port)
{
   uint16_t ret;
   __asm__ __volatile__("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
} 


