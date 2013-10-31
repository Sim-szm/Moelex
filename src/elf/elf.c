/*
 * =====================================================================================
 *
 *       Filename:  elf.c
 *        Version:  1.0
 *        Created:  2013年10月30日 21时43分27秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "moe-common.h"
#include "elf.h"
elf_t elf_from_multiboot (multiboot_t *mb){
	int i;
	elf_t elf;
	elf_section_header_t *sh = (elf_section_header_t*)mb->addr;
	uint32_t shstrtab = sh[mb->shndx].addr;
	for (i = 0; i < mb->num; i++){
		const char *name = (const char *) (shstrtab + sh[i].name);
		if (!strcmp (name, ".strtab")){
		elf.strtab = (const char *)sh[i].addr;
		elf.strtabsz = sh[i].size;
		}
		if (!strcmp (name, ".symtab")){
			elf.symtab = (elf_symbol_t*)sh[i].addr;
			elf.symtabsz = sh[i].size;
		}
	}
	return elf;
}

