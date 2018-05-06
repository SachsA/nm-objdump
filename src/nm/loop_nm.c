/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** nm loop nm
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include "nm.h"

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

static int check_ret(char **argv, int i, file_info_t *file_info, elf_t *elf)
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

static int check_ret_aout(char **argv, file_info_t *file_info, elf_t *elf)
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

static int nm_aout(char **argv)
{
	elf_t elf;
	int check;
	int ret = 0;
	file_info_t file_info;

	check = check_ret_aout(argv, &file_info, &elf);
	if (check == 84)
		return (84);
	if (get_sections(&elf, check, &file_info, "a.out") == 84)
		return (84);
	return (ret);
}

int loop_nm(int argc, char **argv)
{
	elf_t elf;
	int check;
	int i = 0;
	int ret = 0;
	file_info_t file_info;

	if (argc == 1)
		ret = nm_aout(argv);
	while (++i < argc) {
		check = check_ret(argv, i, &file_info, &elf);
		if (check == 84) {
			ret = 84;
			continue;
		}
		if (argc > 2)
			printf("\n%s:\n", argv[i]);
		if (get_sections(&elf, check, &file_info, argv[i]) == 84)
			return (84);
	}
	return (ret);
}
