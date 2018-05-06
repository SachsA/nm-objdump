/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** objdump init elf
*/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "nm.h"

int init_elf(char *file, file_info_t *file_info)
{
	int fd;
	int ret = 0;
	void *data;
	struct stat info;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ret = 84;
	if (fstat(fd, &info) == -1)
		ret = 84;
	data = mmap(NULL, info.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (data == ((void *) - 1))
		ret = 84;
	file_info->data = data;
	ret = close(fd);
	if (ret == -1)
		ret = 84;
	return (ret);
}

int check_elf(elf_t *elf, char *path, char *file, file_info_t *file_info)
{
	int ret = 0;

	elf->name = file;
	elf->ehdr = file_info->data;
	elf->ehdr32 = file_info->data;
	if (elf->ehdr->e_ident[EI_CLASS] != ELFCLASS64 &&
		elf->ehdr->e_ident[EI_CLASS] != ELFCLASS32)
		ret = 84;
	else if (elf->ehdr->e_ident[EI_CLASS] == ELFCLASS32)
		ret = 32;
	if (memcmp(elf->ehdr->e_ident, ELFMAG, SELFMAG)) {
		ret = 84;
		dprintf(2, "%s: %s: File format not recognized\n", path, file);
	}
	return (ret);
}
