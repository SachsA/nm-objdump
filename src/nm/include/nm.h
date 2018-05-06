/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** nm nm h
*/

#ifndef NM_H_
	#define  NM_H_

	#include <elf.h>
	#include <stddef.h>

	typedef struct file_info_s {
		int size;
		void *data;
	}	       file_info_t;

	typedef struct elf_s {
		char *name;
		char *str_tab;
		char *shstr_tab;
		Elf64_Ehdr *ehdr;
		Elf64_Shdr *shdr;
		Elf64_Sym *sym;
		Elf32_Ehdr *ehdr32;
		Elf32_Shdr *shdr32;
		Elf32_Sym *sym32;
	}	       elf_t;

	typedef struct list_s {
		char type;
		char *name;
		size_t value;
		struct list_s *next;
	}	       list_t;

	void free_list(list_t *list);
	void print_sections(list_t *tmp);
	void print_sections32(list_t *tmp);
	int loop_nm(int argc, char **argv);
	int build_list(elf_t *elf, size_t size);
	int build_list32(elf_t *elf, size_t size);
	int init_elf(char *file, file_info_t *file_info);
	int get_sections(elf_t *elf, int version,
			file_info_t *file_info, char *str);
	int check_elf(elf_t *elf, char *path,
			char *file, file_info_t *file_info);
	void init_type(list_t *new, Elf64_Sym *sym,
			Elf64_Shdr *shdr, size_t value);
	void init_type32(list_t *new, Elf32_Sym *sym,
			Elf32_Shdr *shdr, size_t value);

#endif /* !NM_H_ */
