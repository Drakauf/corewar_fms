NAME = libft.a
CC = gcc -Wall -Werror -Wextra -O3
OBJ = ft_atoi.o\
ft_atol.o\
ft_bzero.o\
ft_crep.o\
ft_crepall.o\
ft_crrep.o\
ft_free_assign.o\
ft_free_options.o\
ft_get_opt_value.o\
ft_get_options.o\
ft_getline.o\
ft_getline_mfd.o\
ft_isalnum.o\
ft_isalpha.o\
ft_isascii.o\
ft_isdigit.o\
ft_isnumeric.o\
ft_isprint.o\
ft_isset_option.o\
ft_isspace.o\
ft_itoa.o\
ft_ltoa.o\
ft_ltrim.o\
ft_memalloc.o\
ft_memccpy.o\
ft_memchr.o\
ft_memcmp.o\
ft_memcpy.o\
ft_memcrep.o\
ft_memcrepall.o\
ft_memcrrep.o\
ft_memdel.o\
ft_memdup.o\
ft_memmove.o\
ft_mempcpy.o\
ft_memrchr.o\
ft_memrcpy.o\
ft_memset.o\
ft_print_options.o\
ft_putbin.o\
ft_putc.o\
ft_putchar_fd.o\
ft_putendl.o\
ft_putendl_fd.o\
ft_puts.o\
ft_putstr_fd.o\
ft_sort.o\
ft_strcat.o\
ft_strchr.o\
ft_strclr.o\
ft_strcmp.o\
ft_strcpy.o\
ft_strctrim.o\
ft_strdup.o\
ft_strfcat.o\
ft_strjoin.o\
ft_strjpath.o\
ft_strlcat.o\
ft_strlen.o\
ft_strncat.o\
ft_strncmp.o\
ft_strncpy.o\
ft_strndup.o\
ft_strnfcat.o\
ft_strnlen.o\
ft_strnstr.o\
ft_strrchr.o\
ft_strrep.o\
ft_strsplit.o\
ft_strstr.o\
ft_strsub.o\
ft_strtolower.o\
ft_strtoupper.o\
ft_strtrim.o\
ft_swap.o\
ft_tolower.o\
ft_toupper.o\
get_next_line.o\
printf/call_convertion_function.o \
printf/call_signed.o \
printf/call_signed2.o \
printf/call_signed3.o \
printf/call_signed4.o \
printf/call_unsigned.o \
printf/call_unsigned2.o \
printf/call_unsigned3.o \
printf/ft_printf.o \
printf/get_sign.o \
printf/integer_print.o \
printf/print_string_with_options.o \
printf/printf_options.o \
printf/bv_spe/b_specifier.o \
printf/bv_spe/lv_specifier.o \
printf/bv_spe/v_specifier.o \
printf/diouxXp_spe/diu_specifier.o \
printf/diouxXp_spe/o_specifier.o \
printf/diouxXp_spe/xp_specifier.o \
printf/f_spe/f_specifier.o \
printf/f_spe/is_nan.o \
printf/f_spe/lf_specifier.o \
printf/f_spe/lf_specifier_functions.o \
printf/f_spe/numeric_str_op.o \
printf/f_spe/ulong128.o \
printf/f_spe/ulong128_assign.o \
printf/n_spe/n_specifier.o \
printf/sScC_spe/c_specifier.o \
printf/sScC_spe/cmaj_specifier.o \
printf/sScC_spe/s_specifier.o \
printf/sScC_spe/smaj_specifier.o \
printf/sScC_spe/unicode_to_utf8.o \
printf/wW_spe/w_functions.o \
printf/wW_spe/w_print_member.o \
printf/wW_spe/w_print_member2.o \
printf/wW_spe/w_print_member3.o \
printf/wW_spe/w_specifier.o \
printf/wW_spe/w_specifier2.o \
printf/wW_spe/ft_space.o \
printf/wW_spe/wmaj_format_string.o \
printf/wW_spe/wmaj_free.o \
printf/wW_spe/wmaj_functions.o \
printf/wW_spe/wmaj_functions2.o \
printf/wW_spe/wmaj_functions3.o \
printf/wW_spe/wmaj_functions4.o \
printf/wW_spe/wmaj_functions5.o \
printf/wW_spe/wmaj_specifier.o \
printf/yYZ_spe/y_print.o \
printf/yYZ_spe/y_specifier.o \
printf/yYZ_spe/ymaj_specifier.o \
printf/yYZ_spe/zmaj_specifier.o 

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $^ 
	@ranlib $@

%.o: %.c
	@$(CC) -c $< -o $@

$(OBJ): libft.h

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

allc: all clean
