/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** objdump my_objdump
*/

#include "objdump.h"

static void obj32(elf_t *elf, file_info_t *file_info, char **argv, int i)
{
	elf->shdr32 = file_info->data + elf->ehdr32->e_shoff;
	elf->str_tab = (char *)((void *)elf->ehdr32 +
			elf->shdr32[elf->ehdr32->e_shstrndx].sh_offset);
	print_head32(elf, argv, i);
	print_sections32(elf);
}

static void obj(elf_t *elf, file_info_t *file_info, char **argv, int i)
{
	elf->shdr = file_info->data + elf->ehdr->e_shoff;
	elf->str_tab = (char *)((void *)elf->ehdr +
			elf->shdr[elf->ehdr->e_shstrndx].sh_offset);
	print_head(elf, argv, i);
	print_sections(elf);
}

int my_objdump(char **argv, char *file, int i)
{
	elf_t elf;
	int ret = 0;
	file_info_t file_info;

	if (file != NULL)
		ret = check_ret_aout(argv, &file_info, &elf);
	else
		ret = check_ret(argv, i, &file_info, &elf);
	if (ret == 32)
		obj32(&elf, &file_info, argv, i);
	else if (ret == 0)
		obj(&elf, &file_info, argv, i);
	return (ret);
}
