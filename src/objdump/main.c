/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** main objdump
*/

#include "objdump.h"

int main(int argc, char **argv)
{
	int i = 0;
	int ret = 0;
	int check = 0;

	if (argc == 1)
		ret = my_objdump(argv, "a.out", i);
	while (++i < argc) {
		check = my_objdump(argv, NULL, i);
		if (check == 84) {
			ret = 84;
			continue;
		}
	}
	return (ret);
}
