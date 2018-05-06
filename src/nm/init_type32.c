/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** nm init_type 32
*/

#include "nm.h"

static void weak_type(list_t *new, Elf32_Sym *sym, size_t value)
{
	if (!value) {
		if (ELF32_ST_TYPE(sym->st_info) == STT_OBJECT)
			new->type = 'v';
		else
			new->type = 'w';
	}
	else {
		if (ELF32_ST_TYPE(sym->st_info) == STT_OBJECT)
			new->type = 'V';
		else
			new->type = 'W';
	}
}

static void hard_types_bis(list_t *new, Elf32_Sym *sym, Elf32_Shdr *shdr)
{
	if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS)
		new->type = 'N';
	if ((shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
		shdr[sym->st_shndx].sh_flags == (SHF_WRITE | SHF_ALLOC)) ||
		shdr[sym->st_shndx].sh_type == (SHT_DYNAMIC))
		new->type = 'D';
	else if ((shdr[sym->st_shndx].sh_type == SHT_NOBITS &&
		shdr[sym->st_shndx].sh_flags == (SHF_WRITE | SHF_ALLOC)))
		new->type = 'B';
}

static void hard_types(list_t *new, Elf32_Sym *sym, Elf32_Shdr *shdr)
{
	if ((shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
		shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR)) ||
		shdr[sym->st_shndx].sh_type == SHT_INIT_ARRAY ||
		shdr[sym->st_shndx].sh_type == SHT_FINI_ARRAY)
		new->type = 'T';
	else if ((shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
		shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_MERGE)) ||
		shdr[sym->st_shndx].sh_flags == (SHF_ALLOC))
		new->type = 'R';
	else
		hard_types_bis(new, sym, shdr);
}

void init_type32(list_t *new, Elf32_Sym *sym, Elf32_Shdr *shdr, size_t value)
{
	if (ELF32_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
		new->type = 'u';
	else if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
		weak_type(new, sym, value);
	else {
		switch (sym->st_shndx) {
		case SHN_UNDEF:
			new->type = 'U';
			break;
		case SHN_ABS:
			new->type = 'A';
			break;
		case SHN_COMMON:
			new->type = 'C';
			break;
		default:
			hard_types(new, sym, shdr);
		}
	}
}
