# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/04/08 15:21:23 by mhouppin     #+#   ##    ##    #+#        #
#    Updated: 2019/04/10 09:10:30 by mhouppin    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

CHMP_SRCS := $(wildcard champs/*.s)
CHMP_OBJS := $(patsubst champs/%.s,bin_cores/%.cor,$(CHMP_SRCS))
NAME      := libft asm corewar

all: libft/libft.a $(NAME)

libft/libft.a:	libft/*.c libft/printf/*.c libft/printf/*/*.c libft/vector/*.c \
				libft/libft.h libft/vector/*.h libft/printf/*.h

libft/libft.a:
	@make -C libft

corewar: corewar_dir/src/*.c corewar_dir/inc/*.h libft/libft.a
asm: asm_dir/src/*.c asm_dir/inc/*.h libft/libft.a

corewar asm:
	@make -C $@_dir

clean fclean re:
	@make $@ -C libft
	@make $@ -C asm_dir
	@make $@ -C corewar_dir

champs: asm bin_cores $(CHMP_OBJS)

bin_cores:
	@mkdir -p $@

bin_cores/%.cor: champs/%.s
	@./asm $< -o $@

rmchamps:
	@rm -rf bin_cores

.PHONY: all libft clean fclean re
