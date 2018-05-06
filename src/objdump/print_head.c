/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** objdump print_head
*/

#include <stdio.h>
#include "objdump.h"

void print_head32(elf_t *elf, char **argv, int i)
{
	printf("\n%s:     file format elf32-i386\n", argv[i]);
	printf("architecture:");
	if (elf->ehdr->e_machine == EM_386)
		printf(" i386, ");
	flags(elf, 32);
	printf("start address 0x%08x\n\n", elf->ehdr32->e_entry);
}

void print_head(elf_t *elf, char **argv, int i)
{
	printf("\n%s:     file format elf64-x86-64\n", argv[i]);
	printf("architecture:");
	if (elf->ehdr->e_machine == EM_X86_64)
		printf(" i386:x86-64, ");
	flags(elf, 64);
	printf("start address 0x%016lx\n\n", elf->ehdr->e_entry);
}
