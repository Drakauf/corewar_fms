# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/02/25 16:43:57 by mhouppin     #+#   ##    ##    #+#        #
#    Updated: 2019/04/07 14:47:16 by mhouppin    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

SHELL     = bash
NAME     := corewar
OBJ_DIR  := obj
SRC_DIR  := src
INC_DIR  := inc:libft
ifeq (${USER},mhouppin)
	BIN_DIR = /Users/mhouppin/Documents/bin/lib/lib/
else
	BIN_DIR = /Users/shthevak/Documents/sdl/lib
endif
LIB      := libft
ARCHIVE  := $(LIB)/libft.a

SOURCES  := \
	src/champ_intro.c\
	src/corewar.c\
	src/exec_calcs.c\
	src/exec_checks.c\
	src/exec_cooldowns.c\
	src/exec_jumps.c\
	src/exec_loads.c\
	src/exec_misc.c\
	src/exec_tools.c\
	src/execute.c\
	src/font.c\
	src/graph_arena.c\
	src/graph_toolbar.c\
	src/graph_tools.c\
	src/graphics.c\
	src/launch_corewar.c\
	src/load_champs.c\
	src/load_tools.c\
	src/main.c\
	src/param_get.c\
	src/param_tools.c\
	src/parsing.c\
	src/process.c\
	src/struct.c\
	src/tools.c

OBJECTS  := $(patsubst ${SRC_DIR}/%.c,${OBJ_DIR}/%.o,${SOURCES})
DEPENDS  := $(patsubst ${SRC_DIR}/%.c,${SRC_DIR}/.%.d,${SOURCES})
CFLAGS   := -Wall -Wextra -Werror -O3
CINC     := -I $(subst :, -I ,${INC_DIR})
CC       := gcc
INCLUDED := $(shell for deps in ${DEPENDS}; do if [[ -e $$deps ]]; then echo -n "$$deps "; fi; done)


.PHONY: all $(LIB) clean fclean re allc


all: $(LIB) $(DEPENDS) $(OBJ_DIR) $(NAME)

# compilation des lib
$(LIB):
	$(MAKE) -C $@

# Creation du repertoire pour les .o
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Creation de l'executable
$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(CINC) -o $@ $^ -lSDL2 -L$(BIN_DIR) $(ARCHIVE)

# Creation des .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(CINC) -c $< -o $@

# creation des .d
$(SRC_DIR)/.%.d: $(SRC_DIR)/%.c
	@set -e; echo "$(OBJ_DIR)/`$(CC) $(CINC) -MM $<`" > $@

# inclusion des regles contenues dans les .d
include $(INCLUDED)


clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -f $(NAME)

uclean: fclean
	make fclean -C libft/

re: fclean all

allc: all clean
