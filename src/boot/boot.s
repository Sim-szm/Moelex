; ----------------------------------------------------------------
; declaration:
;   boot.s ,as the boot_init file for Moelex
;   here is some rules based with GRUB Multiboot
; ----------------------------------------------------------------
MBOOT_HEADER_MAGIC 	equ 	0x1BADB002 	; Multiboot magic_num ,defined with the rules
MBOOT_PAGE_ALIGN 	equ 	1 << 0    	  ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO 		equ 	1 << 1    	  ; Provide your kernel with memory info
MBOOT_HEADER_FLAGS 	equ 	MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM 		equ 	- (MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]                       ; All instructions should be 32-bit.

[GLOBAL mboot]                  ; Make 'mboot' accessible from C.
[EXTERN _code]                   ; Start of the '.text' section.
[EXTERN _bss]                    ; Start of the .bss section.
[EXTERN _end]                    ; End of the last loadable section.


;Multiboot head code must be writed as the follow list,if you wanna to be support by GRUB:
; ----------------------------------------------------------
; offset type name 
;
; 0  u32  magic     
; 4  u32  flags     
; 8  u32  checksum   
; 12  u32  header_addr    
; 16  u32  load_addr      
; 20  u32  load_end_addr   
; 24  u32  bss_end_addr    
; 28  u32  entry_addr      
; 32  u32  mode_type      
; 36  u32  width     
; 40  u32  height    
; 44  u32  depth    
; Not include all , pleasr reference to the documnets:
;     <the multiboot specification version 0.6.96>
;-----------------------------------------------------------


mboot:
  dd  MBOOT_HEADER_MAGIC        ; GRUB will search for this value on each 4-byte boundary in your kernel file
  dd  MBOOT_HEADER_FLAGS        ; How GRUB should load your file / settings
  dd  MBOOT_CHECKSUM            ; To ensure that the above values are correct
  dd  mboot                     ; Location of this descriptor
  dd  _code                      ; Start of kernel '.text' (code) section.
  dd  _bss                       ; End of kernel '.data' section.
  dd  _end                       ; End of kernel.
  dd  start                     ; Kernel entry point (initial EIP).

[GLOBAL start]                  ; Kernel entry point.
[EXTERN moelex_main]               ; This is the entry point of our C code

start:
  push    ebx                   ; Load multiboot header location ,Execute For the Moelex kernel 
  cli                           ; Disable interrupts, and then start out kernel.
  call moelex_main                 ; call our moelex_main() function ,as the C language main().
  jmp $                         ; it should be shutdown , and now write as a big loop !
