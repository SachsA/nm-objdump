##
## EPITECH PROJECT, 2018
## nm objdump
## File description:
## Makefile nm obj
##

CC		= gcc

RM		= rm -rf

SRC_NM		= src/nm/loop_nm.c			\
		  src/nm/init_elf.c			\
		  src/nm/init_type.c			\
		  src/nm/init_type32.c			\
		  src/nm/free_list.c			\
		  src/nm/build_list.c			\
		  src/nm/build_list32.c			\
		  src/nm/get_sections.c			\
		  src/nm/print_sections.c		\
		  src/nm/main.c

SRC_OBJ		= src/objdump/print_sections32.c	\
		  src/objdump/print_sections.c		\
		  src/objdump/fill_content.c		\
		  src/objdump/my_objdump.c		\
		  src/objdump/print_head.c		\
		  src/objdump/check_ret.c		\
		  src/objdump/init_elf.c		\
		  src/objdump/flags.c			\
		  src/objdump/main.c

OBJ_NM		= $(SRC_NM:.c=.o)

OBJ_OBJ		= $(SRC_OBJ:.c=.o)

CFLAGS		+= -I ./src/nm/include
CFLAGS		+= -I ./src/objdump/include
CFLAGS		+= -W -Wall -Wextra -g

LDFLAGS		+= -ldl

NAME_NM		= ./my_nm

NAME_OBJ	= ./my_objdump

all:		nm objdump

$(NAME_NM):	$(OBJ_NM)
		$(CC) -o $(NAME_NM) $(OBJ_NM) $(LDFLAGS)

$(NAME_OBJ):	$(OBJ_OBJ)
		$(CC) -o $(NAME_OBJ) $(OBJ_OBJ) $(LDFLAGS)

nm:		$(NAME_NM)

objdump:	$(NAME_OBJ)

clean:
		$(RM) $(OBJ_NM)
		$(RM) $(OBJ_OBJ)

fclean:		clean
		$(RM) $(NAME_NM)
		$(RM) $(NAME_OBJ)

re:		fclean all

.PHONY:		nm objdump all clean fclean re
