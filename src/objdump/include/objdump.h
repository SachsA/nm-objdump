/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** objdump objdump h
*/

#ifndef OBJDUMP_H_
	#define  OBJDUMP_H_

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

	int check_elf(elf_t *elf, char *path, char *file,
	file_info_t *file_info);
	int check_ret(char **argv, int i, file_info_t *file_info, elf_t *elf);
	int check_ret_aout(char **argv, file_info_t *file_info, elf_t *elf);
	unsigned char *content_init32(elf_t *elf, size_t i, size_t j);
	unsigned char *content_init(elf_t *elf, size_t i, size_t j);
	int init_values32(elf_t *elf, size_t i, unsigned char *str);
	int init_values(elf_t *elf, size_t i, unsigned char *str);
	void print_head32(elf_t *elf, char **argv, int i);
	int init_elf(char *file, file_info_t *file_info);
	void print_head(elf_t *elf, char **argv, int i);
	int my_objdump(char **argv, char *file, int i);
	void flags(elf_t *elf, int version);
	void print_sections32(elf_t *elf);
	void print_sections(elf_t *elf);

#endif /* !OBJDUMP_H_ */
