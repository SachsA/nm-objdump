/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** nm free list
*/

#include <stdlib.h>
#include "nm.h"

void free_list(list_t *list)
{
	list_t *tmp = NULL;

	while (list) {
		tmp = list;
		list = list->next;
		free(tmp);
	}
}
