# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/02/25 16:43:57 by mhouppin     #+#   ##    ##    #+#        #
#    Updated: 2019/04/04 10:57:39 by mhouppin    ###    #+. /#+    ###.fr      #
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
SOURCES  := $(wildcard ${SRC_DIR}/*.c)
OBJECTS  := $(patsubst ${SRC_DIR}/%.c,${OBJ_DIR}/%.o,${SOURCES})
DEPENDS  := $(patsubst ${SRC_DIR}/%.c,${SRC_DIR}/.%.d,${SOURCES})
CFLAGS   := -Wall -Wextra -O3
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
