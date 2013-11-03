/*
 * =====================================================================================
 *
 *       Filename:  moe-keyboard.h
 *        Version:  1.0
 *        Created:  2013年11月03日 17时01分24秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef _MOE_COMMON_H_
#define _MOE_COMMON_H_
#include "moe-common.h"
#include "moe-monitor.h"
#include "printk.h"
static uint8_t shift = 0;//here the variable shift is global; typedef unsigned char byte;
static uint8_t keymap[] = { /* SHIFT OFF */ 
             ' ',' ', '1', '2', '3', '4', '5', '6', '7', '8',  
             '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',  
                      't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',  ' ',  
                      'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',  
                      '\'', '~', ' ', '\"', 'z', 'x', 'c', 'v', 'b', 'n',  
                      'm', '<', '>', '/', ' ', ' ', ' ', ' ', ' ', //the last character this line is keymap[0x3B]  
             /* SHIFT ON */  
              ' ', ' ', '!', '@', '#', '$', '%', '^', '&', '*',  
                      '(', ')', '_', '+', ' ', ' ', 'Q', 'W', 'E', 'R',  
                      'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', ' ',  ' ',  
                      'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',  
                      '\"', '<', ' ', '"', 'Z', 'X', 'C', 'V', 'B', 'N',  
                      'M', '<', '>', '?', ' ', ' ', ' ', ' ', ' '};
void keyboard_handler();
void keyboard_init();
#endif
