# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/02/25 16:43:57 by mhouppin     #+#   ##    ##    #+#        #
#    Updated: 2019/05/06 11:29:13 by mhouppin    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME	:= ../corewar
OBJ_DIR	:= obj
SRC_DIR	:= src
INC_DIR	:= inc:../libft
ARCHIVE	:= ../libft/libft.a

SOURCES	:= \
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

OBJECTS	:= $(patsubst ${SRC_DIR}/%.c,${OBJ_DIR}/%.o,${SOURCES})
DEPENDS	:= $(patsubst ${SRC_DIR}/%.c,${OBJ_DIR}/%.d,${SOURCES})
CFLAGS	:= -Wall -Wextra -Werror -O3
CINC	:= -I $(subst :, -I ,${INC_DIR}) $(shell sdl2-config --cflags)
CSDL	:= $(shell sdl2-config --libs)
CC		:= gcc
QTY		:= $(shell echo ${SOURCES} | wc -w)
CNT		= 0
COLSET	= 0
COLWIN	= 0
SIZE	= 0
ASIZE	= 100
PERCENT	= 0

all: $(NAME)

# Creation du repertoire pour les .o
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Creation de l'executable
$(NAME): $(OBJ_DIR) $(OBJECTS)
	@$(CC) $(CFLAGS) $(CINC) -o $@ $(OBJECTS) $(CSDL) $(ARCHIVE)
	@echo

# Creation des .o et .d
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(eval CNT=$(shell echo "$(CNT) + 1" | bc))
	@$(eval COLSET=$(shell echo "$(CNT) * 255 / $(QTY)" | bc))
	@$(eval COLWIN=$(shell echo "$$(tput cols) - 15" | bc))
	@$(eval SIZE=$(shell echo "$(CNT) * $(COLWIN) / $(QTY)" | bc))
	@$(eval ASIZE=$(shell echo "$(COLWIN) - $(SIZE)" | bc))
	@$(eval PERCENT=$(shell echo "$(CNT) * 100 / $(QTY)" | bc))
	@printf "[48;2;255;$(COLSET);0m%$(SIZE)s[0m%$(ASIZE)s corewar: %d%%[K[J\r" "" "" $(PERCENT)
	@$(CC) $(CFLAGS) $(CINC) -MMD -c $< -o $@

# inclusion des regles contenues dans les .d
-include $(DEPENDS)

clean:
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

allc: all clean

.PHONY: all clean fclean re allc
