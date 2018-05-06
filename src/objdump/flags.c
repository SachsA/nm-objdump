/*
** EPITECH PROJECT, 2018
** nm objdump
** File description:
** objdump flags
*/

#include <stdio.h>
#include "objdump.h"
#include "flags.h"

static void flags_size(elf_t *elf, unsigned int *flags, int version)
{
	switch ((version = 32) ? elf->ehdr32->e_type : elf->ehdr->e_type) {
	case ET_DYN:
		*flags += DYNAMIC + D_PAGED + HAS_SYMS;
		break;
	case ET_REL:
		*flags += HAS_RELOC + HAS_SYMS;
		break;
	case ET_EXEC:
		*flags += EXEC_P + D_PAGED + HAS_SYMS;
		break;
	default:
		*flags += BFD_NO_FLAGS;
	}
}

static void flags_name(elf_t *elf, int version)
{
	switch ((version = 32) ? elf->ehdr32->e_type : elf->ehdr->e_type) {
	case ET_DYN:
		printf("HAS_SYMS, DYNAMIC, D_PAGED\n");
		break;
	case ET_REL:
		printf("HAS_RELOC, HAS_SYMS\n");
		break;
	case ET_EXEC:
		printf("EXEC_P, HAS_SYMS, D_PAGED\n");
		break;
	default:
		printf("\n");
	}
}

void flags(elf_t *elf, int version)
{
	unsigned int flags = BFD_NO_FLAGS;

	flags_size(elf, &flags, version);
	printf("flags 0x%08x:\n", flags);
	flags_name(elf, version);
}
