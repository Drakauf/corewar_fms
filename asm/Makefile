# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/02/25 16:43:57 by mhouppin     #+#   ##    ##    #+#        #
#    Updated: 2019/03/20 11:02:55 by fcordon     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

SHELL     = bash
NAME      = asm
OBJ_DIR   = obj
SRC_DIR   = src
INC_DIR   = inc:../libft
LIB       = ../libft
ARCHIVE  := $(LIB)/libft.a
SOURCES  := $(wildcard ${SRC_DIR}/*.c)
OBJECTS  := $(patsubst ${SRC_DIR}/%.c,${OBJ_DIR}/%.o,${SOURCES})
DEPENDS  := $(patsubst ${SRC_DIR}/%.c,${SRC_DIR}/.%.d,${SOURCES})
CFLAGS    = -Wextra -Wall -g
CINC     := -I $(subst :, -I ,${INC_DIR})
CC        = gcc
INCLUDED := $(shell for deps in ${DEPENDS}; do if [[ -e $$deps ]]; then echo -n "$$deps "; fi; done)


.PHONY: all clean fclean re allc
# Chemins par defaut des .h


all: $(DEPENDS) $(OBJ_DIR) $(NAME)

# compilation des lib
#$(LIB):
#	$(MAKE) -C $@

# Creation du repertoire pour les .o
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Creation de l'executable
$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(ARCHIVE)

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

re: fclean all

allc: all clean
