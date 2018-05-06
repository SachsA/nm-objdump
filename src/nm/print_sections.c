/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** nm print_sections
*/

#include <stdio.h>
#include "nm.h"

void print_sections(list_t *tmp)
{
	if (tmp == NULL)
		return;
	while (tmp) {
		if (tmp->type == 'w' || tmp->type == 'U') {
			printf("                ");
			printf(" %c %s\n", tmp->type, tmp->name);
		}
		else {
			printf("%016lx %c %s\n",
			tmp->value, tmp->type, tmp->name);
		}
		tmp = tmp->next;
	}
}

void print_sections32(list_t *tmp)
{
	if (tmp == NULL)
		return;
	while (tmp) {
		if (tmp->type == 'w' || tmp->type == 'U') {
			printf("        ");
			printf(" %c %s\n", tmp->type, tmp->name);
		}
		else {
			printf("%08lx %c %s\n",
			tmp->value, tmp->type, tmp->name);
		}
		tmp = tmp->next;
	}
}
