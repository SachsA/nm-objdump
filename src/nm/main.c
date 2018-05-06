/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** nm main
*/

#include <stdio.h>
#include "nm.h"

int main(int argc, char **argv)
{
	int ret = 0;

	if (loop_nm(argc, argv) == 84)
		ret = 1;
	return (ret);
}
