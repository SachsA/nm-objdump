/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** objdump print_sections
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "objdump.h"

static int verif_print(elf_t *elf, size_t i)
{
	int ret = 0;

	if ((elf->str_tab + elf->shdr[i].sh_name)[0] != '\0'
	&& strcmp(elf->str_tab + elf->shdr[i].sh_name, ".bss") != 0
	&& strcmp(elf->str_tab + elf->shdr[i].sh_name, ".shstrtab") != 0
	&& strcmp(elf->str_tab + elf->shdr[i].sh_name, ".symtab") != 0
	&& strcmp(elf->str_tab + elf->shdr[i].sh_name, ".rela") != 0
	&& ((strncmp(elf->str_tab + elf->shdr[i].sh_name, ".rela", 4) != 0 &&
	elf->ehdr->e_type == ET_REL) || elf->ehdr->e_type != ET_REL)
	&& strcmp(elf->str_tab + elf->shdr[i].sh_name, ".strtab") != 0) {
		ret = 1;
	}
	return (ret);
}

unsigned char *content_init(elf_t *elf, size_t i, size_t j)
{
	unsigned int ref = 0;
	unsigned char *content = calloc(17, sizeof(unsigned char));
	size_t hexa = elf->shdr[i].sh_addr + elf->shdr[i].sh_size;

	if (content == NULL)
		return (NULL);
	memset(content, ' ', 16);
	if (hexa > 16) {
		while (hexa != 0) {
			hexa = hexa / 16;
			ref += 1;
		}
	}
	if (ref <= 4)
		ref = 4;
	printf(" %0*lx ", ref, elf->shdr[i].sh_addr + j);
	return (content);
}

void print_sections(elf_t *elf)
{
	unsigned char *str;
	size_t i = 0;

	while (i < elf->ehdr->e_shnum) {
		if (elf->shdr[i].sh_size == 0) {
			i++;
			continue;
		}
		if (verif_print(elf, i) == 1) {
			str = (unsigned char *)
				(void *)elf->ehdr + elf->shdr[i].sh_offset;
			printf("Contents of section %s:\n",
			elf->str_tab + elf->shdr[i].sh_name);
			init_values(elf, i, str);
		}
		i++;
	}
}
