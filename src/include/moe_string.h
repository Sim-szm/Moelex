/*
 * =====================================================================================
 *
 *       Filename:  moe_string.h
 *        Version:  1.0
 *        Created:  2013年10月28日 20时15分42秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef _STRING_H
#define _STRING_H
#include "moe_common.h"
#ifndef NULL  
#ifdef __cplusplus  
#define NULL    0  
#else  
#define NULL    ((void *)0)  
#endif  
#endif  
void *memcpy(uint8_t *s1, const uint8_t *s2, uint32_t n);
void *memset(uint8_t *s, uint8_t c, uint32_t n);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *s1,const char *s2);
char *strcat(char *s1,const char *s2);
int strlen(const char *s);
char *strchr(const char *s,int c); 
int strspn(const char *s1,const char * s2);
#endif
