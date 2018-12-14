/*
 * =====================================================================================
 *
 *       Filename:  string.c
 *        Version:  1.0
 *        Created:  2013年10月28日 20时22分01秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "moe_string.h"
inline void *memcpy(uint8_t *s1, const uint8_t *s2, uint32_t n){
	for (; n != 0; n--) {
		*s1++ = *s2++;
	}  
   	 return s1;  
}

inline void *memset(uint8_t *s, uint8_t c, uint32_t n){
	for ( ; n != 0; n--) {
		*s++ = c;
	}
	return s; 
}
inline char *strcpy(char *s1,const char *s2){  
        char *s=s1;  
        while(*s2!='\0'&&*s!='\0')  
            *s++=*s2++;  
        *s='\0';  
        return s1;  
}  
inline  int strcmp(const char *s1,const char *s2){  
        for( ; *s1==*s2 ; *s1++,*s2++)  
            if(*s1=='\0')  
                return (0);  
            return((*s1>*s2) ? 1 : -1);         
}
inline char *strcat(char *s1,const char *s2) {  
        char *pt=s1;  
        while(*s1!='\0')  
            s1++;  
        s1--;  
        while(*s2!='\0')  
            *(s1++)=*(s2++);  
        *s1='\0';  
        return pt;  
}  
inline int strlen(const char *s){  
        int len=0;  
        const char *p;  
        for( p=s ; *p!='\0' ; *p++)  
            len++;  
        return len;  
}  
inline char *strchr(const char *s,int c){  
        for( ; *s!=((char)c) ; s++)  
            if(*s=='\0')  
                return NULL;  
        return ((char *)s);
}  
inline int strspn(const char *s1,const char * s2){  
        const char *p1,*p2;  
        for(p1=s1 ; *p1!='\0' ; p1++)  
            for(p2=s2 ; ; p2++)  
            {  
                if(*p2=='\0')  
                    return (p1-s1)+1;  
                else if(*p1==*p2)  
                    break;  
            }  
            return (p1-s1)+1;  
}  
