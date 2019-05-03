/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 15:34:15 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 15:52:16 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../../libft/libft.h"
# include "struct.h"

# undef lines
# undef ERR

# define HEADERSIZ				sizeof(t_header)

# define ERROR					-1
# define FATAL_ERROR			-1
# define IND_ERROR				NULL
# define DIR_ERROR				NULL
# define REG_ERROR				NULL
# define BREAK					0x1e101
# define ERROR_PTR				NULL
# define ERR					"\e[0;31mErreur: \e[0m"

# define DFLT					0
# define ATNT					1
# define INTL					2
# define CSTYLE					3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define HEXA_SYNTAX			HEXA_BOTH
# define LABEL_CHAR				':'

/*
** SYNTAX CHAR
*/

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"
# define KEYWORD_CHARS			LABEL_CHARS "-"
# define ALL_AUTHORIZED_CHAR	LABEL_CHARS "-, \t\n"

# define ATNT_IND				"*()"
# define ATNT_DIR				"$"
# define ATNT_REG				"%"
# define ATNT_COM				"#;"
# define ATNT_SPECIFIC			ATNT_DIR "" ATNT_IND "" ATNT_REG "" ATNT_COM

# define INTL_IND				"*[]"
# define INTL_DIR				""
# define INTL_REG				""
# define INTL_COM				"#;"
# define INTL_SPECIFIC			INTL_IND "" INTL_DIR "" INTL_COM "" INTL_REG

# define DFLT_IND				""
# define DFLT_COM				"#"
# define DFLT_DIR				"%"
# define DFLT_REG				""
# define DFLT_SPECIFIC			DFLT_DIR "" DFLT_COM
# define ATNT_AUTHORIZED_CHAR	KEYWORD_CHARS "+*" ATNT_SPECIFIC
# define INTL_AUTHORIZED_CHAR	KEYWORD_CHARS "+*" INTL_SPECIFIC
# define DFLT_AUTHORIZED_CHAR	KEYWORD_CHARS ":*" DFLT_SPECIFIC

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16
# define REG_N					REG_NUMBER

# define T_REG					0x1
# define T_DIR					0x4
# define T_IND					0x2
# define T_RDI					T_REG | T_DIR | T_IND
# define T_RD					T_REG | T_DIR
# define T_RI					T_REG | T_IND
# define T_DI					T_DIR | T_IND

# define REG_O					1
# define IND_O					2
# define DIR_O					3

# define REG_D					1
# define IND_D					3
# define DIR_D					2

# define NAME_LENGTH			PROG_NAME_LENGTH
# define COMMENT_LENGTH			PROG_COMMENT_LENGTH
# define COREWAR_EXEC_MAGIC		0xea83f3
# define MAGIC					COREWAR_EXEC_MAGIC

# define TOTAL_INST_NUMBER		17
# define N_INST					TOTAL_INST_NUMBER

const t_inst_info		g_inst_info[TOTAL_INST_NUMBER];
const char				*g_dflt_inst_set[TOTAL_INST_NUMBER];
const char				*g_altr_inst_set[TOTAL_INST_NUMBER];
const t_inst_size		g_binsize[TOTAL_INST_NUMBER];

/*
** get_arguments.c
*/

void		get_arguments(char *arg[], t_data *d);

/*
** file_extension.c
*/

int			valid_ext(const char *s, const char *ext);
char		*replace_ext(const char *s);

/*
** get_file_contents.c
*/

char		*get_contents(const char *const name, int *len,
							const char *const output);

/*
** print_help.c
*/

int			print_help(const char *prog);

/*
** character_info.c
*/

int			is_authorized_char(t_data *d, char c);
int			is_comment(char c);
int			is_not_space_or_label_end(char c);

/*
** skip.c
*/

char		*skip_spaces(char *s, t_pos *p);
char		*skip_new_lines(char *s, t_data *d);
char		*skip_all_but(char c, char *s);
char		*skip_chars(const char *ch, int len,
									char *s, t_data *d);

/*
** general_parser.c
*/

void		general_parser(t_data *d, t_synt_tree **tree);

/*
** labels.c
*/

int			duplicate_label(char *s, t_vector *label,
								int addr);
int			is_valid_label(char *label, t_data *d);

/*
** ft_assert.c
*/

void		ft_assert(int cond, enum e_err err);

/*
** struct_tree_and_child.c
*/

t_child		*new_child(char *keyword, t_data *d);
void		push_new_child(t_synt_tree *tree, t_child *new);
t_synt_tree	*new_node(char *s, t_data *d, int opcode);
t_synt_tree	*push_new_instruction(t_synt_tree **tree, t_synt_tree *new);

/*
** get_instruction.c
*/

char		*get_instruction(char *s, t_data *d, t_synt_tree **tree);

/*
** push_new_label.c
*/

char		*push_new_label(char *s, char *label, t_data *d, t_synt_tree **t);

/*
** push_section.c
*/

char		*push_section_name_with_argument(char *s, char *section, t_data *d,
												t_synt_tree **tree);
char		*push_section_comment_with_argument(char *s, char *section,
												t_data *d, t_synt_tree **tree);

/*
** set_comment.c
*/

char		*set_comment(char *s, t_data *d);

/*
** set_name.c
*/

char		*set_name(char *s, t_data *d);

/*
** get_operands.c
*/

char		*get_operands(char *s, t_data *d);

/*
** update_current_addr.c
*/

void		update_current_addr(t_data *d);

/*
** get_opcode.c
*/

int			get_opcode(char *s, t_data *d);

/*
** write_operand.c
*/

int			write_operand_into_tree(char **s, t_data *d);

/*
** free.c
*/

void		free_all(t_data *d, t_synt_tree *tree);
void		free_tree(t_synt_tree *t);

/*
** push_new_operand.c
*/

void		push_new_operand(char *s, t_data *d);

/*
** skip_operand_after_error.c
*/

int			skip_operand_after_error(char **s);

/*
** atnt_alternative_addr_syntax_arg1.c
*/

char		*get_arg_1(t_child *c, t_data *d, t_synt_tree *t, int i);

/*
** atnt_alternative_addr_syntax_arg2.c
*/

char		*get_arg_2(char *s, t_child *c, t_data *d, int i);

/*
** mov_addr_check_arg1.c
*/

char		*check_mov_arg1(char *s, t_child *c, t_data *d, int *fmt);

/*
** mov_addr_check_arg2.c
*/

void		check_mov_arg2(char *s, t_child *c, t_data *d, int *fmt);

/*
** atnt_alternative_addr_syntax.c
*/

int			set_atnt_alternative_mov_addr_syntax(t_child *c, t_data *d,
												t_synt_tree *t, int i);

/*
** operand_error_check_and_print.c
*/

char		*is_undefined_label_or_register(char *s, t_data *d, t_child *c,
											t_pos p);
int			print_error_base(char **s, t_child *c, t_data *d, int base);

/*
** mov_addr_register_contained
*/

int			register_contained(char **ps, t_data *d, t_child *c, t_pos p);

/*
** intel_is_dir_ind_reg.c
*/

int			intel_is_direct(char *s, t_data *d, t_child *c);
int			intel_is_indirect(char *s, t_data *d, t_child *c);
int			intel_is_register(char *s, t_data *d, t_child *c);

/*
** default_is_dir_ind_reg.c
*/

int			dflt_is_direct(char *s, t_data *d, t_child *c);
int			dflt_is_indirect(char *s, t_data *d, t_child *c);
int			dflt_is_register(char *s, t_data *d, t_child *c);

/*
** atnt_is_dir_reg.c
*/

int			atnt_is_direct(char *s, t_data *d, t_child *c);
int			atnt_is_indirect(char *s, t_data *d, t_child *c);
int			atnt_is_register(char *s, t_data *d, t_child *c);

/*
** is_label.c
*/

int			is_label(const char *s, t_vector *label, t_data *d);
int			get_label_addr(const char *s, t_vector *label, t_data *d);

/*
** base.c
*/

char		*skip_numbers_base(char *s, int base, t_child *c, t_data *d);
int			get_base(char *s, t_child *c, t_data *d, int *type);

/*
** endian.c
*/

int			little_endian(int int4);
char		*big_endian_string(int n, int size, int new, int *len);
int			big_endian_int(int int4);
short		big_endian_short(short int2);

/*
** disassemble.c
*/

int			disassemble(char *file, int len);

/*
** escape_string.c
*/

char		*escape_string(char *s, t_data *d);

/*
** atnt_is_register_error.c
*/

int			perror_undefined_label(t_data *d, t_child *c);
int			perror_inexistant_register(t_data *d, t_child *c);

/*
** disassemble_add_line.c
*/

char		*add_line(char *file, t_vector *lines, t_param *p, int opcode);
void		count_and_get_params(t_param *param, int byte, int opcode);

/*
** write_operand.c
*/

int			write_operand(int size, int type, const char *value, t_data *d);

/*
** write_mov_operands
*/

int			write_mov_operands(t_synt_tree *t, t_child *c, t_data *d);

/*
** write_binary.c
*/

void		write_binary(t_data *d, t_synt_tree *tree, char *f);

/*
** mov_addr_syntax.c
*/

int			set_mov_addr_syntax(t_child *c, t_data *d, t_synt_tree *t, int i);

/*
** check_operands_syntax_and_type.c
*/

void		check_operands_syntax_and_type(t_synt_tree *t, t_data *d);

/*
** atnt_syntax.c
*/

void		check_atnt_syntax(t_child *c, t_data *d, t_synt_tree *t);

/*
** default_syntax.c
*/

void		check_default_syntax(t_child *c, t_data *d, t_synt_tree *t);

/*
** intel_syntax.c
*/

void		check_intel_syntax(t_child *c, t_data *d, t_synt_tree *t);

/*
** check_operand_type.c
*/

void		check_operand_type(t_child *c, t_data *d, t_synt_tree *t, int i);

/*
** label_struct.c
*/

t_label		*new_label(char *s);

/*
** ft_perror.c
*/

void		ft_perror(const char *prefix, const char *error, t_pos *p,
																t_data *d);
void		*perror_and_set_fmt(const char *e, t_pos *p, t_data *d, int *fmt);

#endif
