/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** objdump check_ret
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include "objdump.h"

static int is_dir(const char *path, char *exec)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return (84);
	if (S_ISDIR(statbuf.st_mode)) {
		dprintf(2, "%s: Warning: '%s' is a directory\n", exec, path);
		return (84);
	}
	return (0);
}

int check_ret(char **argv, int i, file_info_t *file_info, elf_t *elf)
{
	int ret = 0;
	int check = 0;

	if (access(argv[i], F_OK) == -1) {
		dprintf(2, "%s: '%s': No such file\n", argv[0], argv[i]);
		return (84);
	}
	if (access(argv[i], R_OK) == -1) {
		dprintf(2, "%s: %s: Permission denied\n", argv[0], argv[i]);
		return (84);
	}
	if (is_dir(argv[i], argv[0]) == 84)
		return (84);
	check = init_elf(argv[i], file_info);
	if (check == 84)
		return (84);
	check = check_elf(elf, argv[0], argv[i], file_info);
	if (check != 0)
		ret = check;
	return (ret);
}

int check_ret_aout(char **argv, file_info_t *file_info, elf_t *elf)
{
	int ret = 0;
	int check = 0;

	if (access("a.out", F_OK) == -1) {
		dprintf(2, "%s: 'a.out': No such file\n", argv[0]);
		return (84);
	}
	if (access("a.out", R_OK) == -1) {
		dprintf(2, "%s: a.out: Permission denied\n", argv[0]);
		return (84);
	}
	if (is_dir("a.out", argv[0]) == 84)
		return (84);
	check = init_elf("a.out", file_info);
	if (check == 84)
		return (84);
	check = check_elf(elf, argv[0], "a.out", file_info);
	if (check != 0)
		ret = check;
	return (ret);
}
