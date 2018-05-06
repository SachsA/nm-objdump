/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** nm build list
*/

#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include "nm.h"

static void init_new(list_t *new, elf_t *elf, size_t i)
{
	size_t value = elf->sym[i].st_value;
	char *str = elf->str_tab + elf->sym[i].st_name;

	new->name = str;
	new->type = '?';
	new->value = value;
	new->next = NULL;
	init_type(new, &elf->sym[i], elf->shdr, value);
	if (ELF64_ST_BIND(elf->sym[i].st_info) == STB_LOCAL)
		new->type += 32;
}

static void put_before(list_t **list, list_t *tmp, list_t *new)
{
	list_t *tmp2 = *list;

	if (tmp == *list) {
		*list = new;
		new->next = tmp;
		return;
	}
	while (tmp2->next != tmp)
		tmp2 = tmp2->next;
	tmp2->next = new;
	new->next = tmp;
}

static void put_after(list_t *tmp, list_t *new)
{
	new->next = NULL;
	tmp->next = new;
}

static int add_list(list_t **list, elf_t *elf, size_t i)
{
	list_t *tmp = *list;
	list_t *new = malloc(sizeof(list_t));

	setlocale(LC_COLLATE, "");
	if (new == NULL)
		return (84);
	init_new(new, elf, i);
	if (*list == NULL) {
		new->next = NULL;
		*list = new;
		return (0);
	}
	while (tmp->next != NULL && strcoll(tmp->name, new->name) <= 0)
		tmp = tmp->next;
	if (strcoll(tmp->name, new->name) > 0)
		put_before(list, tmp, new);
	else
		put_after(tmp, new);
	return (0);
}

int build_list(elf_t *elf, size_t size)
{
	char *str;
	int ret = 0;
	size_t i = 0;
	list_t *tmp = NULL;
	list_t *list = NULL;

	while (i < size) {
		str = elf->str_tab + elf->sym[i].st_name;
		if (str[0] != '\0' &&
		ELF64_ST_TYPE(elf->sym[i].st_info) != STT_FILE)
			ret = add_list(&list, elf, i);
		i++;
	}
	tmp = list;
	print_sections(tmp);
	free_list(list);
	return (ret);
}
