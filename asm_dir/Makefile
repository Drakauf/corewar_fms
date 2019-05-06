# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/02/25 16:43:57 by mhouppin     #+#   ##    ##    #+#        #
#    Updated: 2019/05/06 11:29:03 by mhouppin    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME      = ../asm
OBJ_DIR   = obj
SRC_DIR   = src
INC_DIR   = inc:../libft
LIB       = ../libft
ARCHIVE  := $(LIB)/libft.a
SOURCES   = src/atnt_alternative_addr_syntax.c\
			src/atnt_alternative_addr_syntax_arg1.c\
			src/atnt_alternative_addr_syntax_arg2.c\
			src/atnt_is_dir_ind_reg.c\
			src/atnt_is_register_error.c\
			src/atnt_syntax.c\
			src/base.c\
			src/character_info.c\
			src/check_operand_type.c\
			src/check_operands_syntax_and_type.c\
			src/default_is_dir_ind_reg.c\
			src/default_syntax.c\
			src/disassemble.c\
			src/disassemble_add_line.c\
			src/endian.c\
			src/escape_string.c\
			src/extension.c\
			src/free.c\
			src/ft_assert.c\
			src/ft_perror.c\
			src/general_parser.c\
			src/get_arguments.c\
			src/get_file_contents.c\
			src/get_instruction.c\
			src/get_opcode.c\
			src/get_operands.c\
			src/global.c\
			src/intel_is_dir_ind_reg.c\
			src/intel_syntax.c\
			src/is_label.c\
			src/label_struct.c\
			src/labels.c\
			src/main.c\
			src/mov_addr_check_arg1.c\
			src/mov_addr_check_arg2.c\
			src/mov_addr_register_contained.c\
			src/mov_addr_syntax.c\
			src/operand_error_check_and_print.c\
			src/print_help.c\
			src/push_new_label.c\
			src/push_new_operand.c\
			src/push_section.c\
			src/set_comment.c\
			src/set_name.c\
			src/skip.c\
			src/skip_operand_after_error.c\
			src/struct_tree_and_child.c\
			src/update_current_addr.c\
			src/write_binary.c\
			src/write_mov_operands.c\
			src/write_operand.c\
			src/write_operand_into_tree.c
OBJECTS  := $(patsubst ${SRC_DIR}/%.c,${OBJ_DIR}/%.o,${SOURCES})
DEPENDS  := $(patsubst ${SRC_DIR}/%.c,${OBJ_DIR}/%.d,${SOURCES})
CFLAGS    = -Wextra -Wall -O3
CINC     := -I $(subst :, -I ,${INC_DIR})
CC        = gcc
QTY      := $(shell echo ${SOURCES} | wc -w)
CNT      = 0
COLSET   = 0
COLWIN   = 0
SIZE     = 0
ASIZE    = 0
PERCENT  = 0


.PHONY: all clean fclean re allc
	# Chemins par defaut des .h


all: $(NAME)

# compilation des lib
#$(LIB):
#	$(MAKE) -C $@

# Creation du repertoire pour les .o
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Creation de l'executable
$(NAME): $(OBJ_DIR) $(OBJECTS)
	@$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(ARCHIVE)
	@echo

# Creation des .o et .d
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(eval CNT=$(shell echo "$(CNT) + 1" | bc))
	@$(eval COLSET=$(shell echo "$(CNT) * 255 / $(QTY)" | bc))
	@$(eval COLWIN=$(shell echo "$$(tput cols) - 15" | bc))
	@$(eval SIZE=$(shell echo "$(CNT) * $(COLWIN) / $(QTY)" | bc))
	@$(eval ASIZE=$(shell echo "$(COLWIN) - $(SIZE)" | bc))
	@$(eval PERCENT=$(shell echo "$(CNT) * 100 / $(QTY)" | bc))
	@printf "[48;2;255;$(COLSET);0m%$(SIZE)s[0m%$(ASIZE)s asm: %d%%[K[J\r" "" "" $(PERCENT)
	@$(CC) $(CFLAGS) $(CINC) -MMD -c $< -o $@

# inclusion des regles contenues dans les .d
-include $(DEPENDS)


clean:
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

allc: all clean
