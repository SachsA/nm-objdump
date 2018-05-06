/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** nm get sections
*/

#include <string.h>
#include <stdio.h>
#include "nm.h"

static int get_sections32(elf_t *elf, char *file)
{
	int i = -1;
	int ret = 0;
	size_t size = 0;
	Elf32_Shdr start = elf->shdr32[elf->ehdr32->e_shstrndx];
	char *str = (char *)((void *)elf->ehdr32 + start.sh_offset);

	while (++i < elf->ehdr32->e_shnum) {
		if (elf->shdr32[i].sh_type == SHT_SYMTAB) {
			elf->sym32 = (Elf32_Sym *)((void *)elf->ehdr32 +
			elf->shdr32[i].sh_offset);
			size = elf->shdr32[i].sh_size / sizeof(Elf32_Sym);
		}
		else if (!strcmp(".strtab", str + elf->shdr32[i].sh_name))
			elf->str_tab = (char *)((void *)elf->ehdr32 +
			elf->shdr32[i].sh_offset);
	}
	if (size == 0)
		return (dprintf(2, "./my_nm: %s: no symbols\n", file), 0);
	ret = build_list32(elf, size);
	return (ret);
}

static int get_sections64(elf_t *elf, char *file)
{
	int i = -1;
	int ret = 0;
	size_t size = 0;
	Elf64_Shdr start = elf->shdr[elf->ehdr->e_shstrndx];
	char *str = (char *)((void *)elf->ehdr + start.sh_offset);

	while (++i < elf->ehdr->e_shnum) {
		if (elf->shdr[i].sh_type == SHT_SYMTAB) {
			elf->sym = (Elf64_Sym *)((void *)elf->ehdr +
			elf->shdr[i].sh_offset);
			size = elf->shdr[i].sh_size / sizeof(Elf64_Sym);
		}
		else if (!strcmp(".strtab", str + elf->shdr[i].sh_name))
			elf->str_tab = (char *)((void *)elf->ehdr +
			elf->shdr[i].sh_offset);
	}
	if (size == 0)
		return (dprintf(2, "./my_nm: %s: no symbols\n", file), 0);
	ret = build_list(elf, size);
	return (ret);
}

int get_sections(elf_t *elf, int version, file_info_t *file_info, char *str)
{
	int ret = 0;

	if (version == 32) {
		elf->shdr32 = file_info->data + elf->ehdr32->e_shoff;
		ret = get_sections32(elf, str);
	}
	else {
		elf->shdr = file_info->data + elf->ehdr->e_shoff;
		ret = get_sections64(elf, str);
	}
	return (ret);
}
