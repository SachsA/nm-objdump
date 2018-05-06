/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** objdump fill contet
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "objdump.h"

static void fill_content(size_t k, int j,
			unsigned char *content, unsigned char *str)
{
	printf("%02x", str[j + k]);
	if (isprint(str[j + k]))
		content[k] = str[j + k];
	else
		content[k] = '.';
}

static void boucle_values(int j, size_t size,
			unsigned char *content, unsigned char *str)
{
	size_t k = 0;

	while (k < 16) {
		if (k + j < size)
			fill_content(k, j, content, str);
		else
			printf("  ");
		k++;
		if (k % 4 == 0)
			printf(" ");
	}
}

int init_values32(elf_t *elf, size_t i, unsigned char *str)
{
	size_t j = 0;
	unsigned char *content = NULL;

	while (j < elf->shdr32[i].sh_size) {
		content = content_init32(elf, i, j);
		if (content == NULL)
			return (84);
		boucle_values(j, elf->shdr32[i].sh_size, content, str);
		printf(" %s\n", content);
		free(content);
		j += 16;
	}
	return (0);
}

int init_values(elf_t *elf, size_t i, unsigned char *str)
{
	size_t j = 0;
	unsigned char *content = NULL;

	while (j < elf->shdr[i].sh_size) {
		content = content_init(elf, i, j);
		if (content == NULL)
			return (84);
		boucle_values(j, elf->shdr[i].sh_size, content, str);
		printf(" %s\n", content);
		free(content);
		j += 16;
	}
	return (0);
}
