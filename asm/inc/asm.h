/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 06:47:27 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/27 10:19:21 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include <stdint.h>

enum	e_inst
{
	LABEL_M, LIVE_M, LD_M, ST_M, ADD_M, SUB_M, AND_M, OR_M, XOR_M,
	ZJMP_M, LDI_M, STI_M, FORK_M, LLD_M, LLDI_M, LFORK_M, AFF_M, SECTION_M
};

# define ERROR					-1

# define DFLT					0
# define ATNT					1
# define INTL					2
# define CSTYLE					3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

enum	e_hexatype
{
	HEXA_MIN, HEXA_MAJ, HEXA_BOTH
};

# define HEXA_SYNTAX			HEXA_MIN
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

/*
** 
*/

# define REG_NUMBER				16

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

# define PROG_NAME_LENGTH		128
# define PROG_COMMENT_LENGTH	2048
# define COREWAR_EXEC_MAGIC		0xea83f3

# define TOTAL_INST_NUMBER		17
# define N_INST					TOTAL_INST_NUMBER

/*
** ERRORS
*/

enum	e_err
{
	COMMENT_MISSING,
	NAME_MISSING,
	OPEN_ERROR,
	TOO_FEW_ARGS,
	TOO_MANY_ARGS,
	EXT_ERROR,
	CREAT_ERROR,
	NO_INSTRUCTION,
	FILENAME_EXPECT,
	OUTPUT_EXPECT
};

typedef struct s_header	t_header;
typedef struct s_param	t_param;

struct		s_param
{
	int	count;
	int	type[3];
	int	size[3];
};

struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			prog_comment[PROG_COMMENT_LENGTH + 1];
};

typedef struct		s_inst_size
{
	int		param_byte;
	int		opsize[3][3];
}					t_inst_size;

typedef struct		s_inst_info
{
	int		n_operand;
	int		fmt[3];
}					t_inst_info;

typedef struct		s_label
{
	char	*name;
	int		len;
	int		addr;
}					t_label;

typedef struct		s_pos
{
	int		line;
	int		col;
}					t_pos;

typedef struct		s_data
{
	int					syntax_error;
	int					syntax;
	int					header_stat;
	int					file_len;
	t_pos				p;
	int					type;
	int					remaind;
	t_vector			*label;
	char				*file;
	char				*comment;
	char				*name;
	const char			**inst_set;
	int					n_inst;
	int					cur_addr;
	char				*output;
	char				*input;
	struct s_synt_tree	*current;
	struct s_synt_tree	*previous;
	struct s_inst_info	*inst_info;
}					t_data;

typedef struct		s_child
{
	char			*s;
	t_pos			p;
	int				len;
	int				fmt;
	struct s_child	*next;
}					t_child;

typedef struct		s_synt_tree
{
	char				*s;
	int					len;
	t_pos				p;
	int					total_operands;
	int					remainder;
	int					type;
	int					fmt[3];
	struct s_synt_tree	*next;
	struct s_child		*child;
}					t_synt_tree;

/*
** get_arguments.c
*/

extern void		get_arguments(char *arg[], t_data *d);

/*
** file_extension.c 
*/

extern int		valid_ext(const char *s, const char *ext);
extern char		*replace_ext(const char *s);

/*
** get_file_contents.c
*/

extern char		*get_contents(const char *name, int *len);

/*
** print_help.c
*/

extern int		print_help(const char *prog);

/*
** character_info.c
*/

extern int		is_authorized_char(t_data *d, char c);
extern int		is_comment(t_data *d, char c);
extern int		is_not_space_or_label_end(char c, t_data *d);

/*
** skip.c
*/

extern char		*skip_chars(const char *ch, int len, char *s, t_data *d);
extern char			*skip_spaces(char *s, t_pos *p);
extern char		*skip_new_lines(char *s, t_data *d);
extern char		*skip_all_but(char c, char *s);

/*
** general_parser.c
*/

extern void		general_parser(t_data *d, t_synt_tree **tree);


/*
** labels.c
*/

extern int		duplicate_label(char **s, t_vector *label, int addr);
extern int		is_valid_label(char *label, t_data *d);

/*
** ft_assert.c
*/

extern void		ft_assert(int cond, enum e_err err);

/*
** struct_tree_and_child.c
*/

extern t_child			*new_child(char *keyword, t_data *d);
extern void				push_new_child(t_synt_tree *tree, t_child *new);
extern t_synt_tree		*new_node(char *s, t_data *d, int opcode);
extern t_synt_tree		*push_new_instruction(t_synt_tree **tree, t_synt_tree *new);

/*
** get_instruction.c
*/

extern char		*get_instruction(char *s, t_data *d, t_synt_tree **tree);

/*
** push_new_label.c
*/

extern char		*push_new_label(char *s, char *label, t_data *d, t_synt_tree **tree);

/*
** push_section.c
*/

extern char		*push_section_name_with_argument(char *s, char *section, t_data *d, t_synt_tree **tree);
extern char		*push_section_comment_with_argument(char *s, char *section, t_data *d, t_synt_tree **tree);

/*
** set_comment.c
*/

extern char		*set_comment(char *s, t_data *d);

/*
** set_name.c
*/

extern char		*set_name(char *s, t_data *d);

/*
** get_operands.c
*/

extern char		*get_operands(char *s, t_data *d);

/*
** update_current_addr.c
*/

extern void		update_current_addr(t_data *d);

/*
** get_opcode.c
*/

extern int		get_opcode(char *s, t_data *d);

/*
**
*/

/*
** free.c
*/

extern void		free_all(t_data *d, t_synt_tree *tree);
extern void		free_tree(t_synt_tree *t);

/*
**
*/

/*
**
*/

/*
**
*/

/*
**
*/

/*
**
*/

/*
**
*/

/*
**
*/

/*
**
*/

const t_inst_info		g_inst_info[TOTAL_INST_NUMBER];
const char				*g_dflt_inst_set[TOTAL_INST_NUMBER];
const char				*g_altr_inst_set[TOTAL_INST_NUMBER];
const t_inst_size		g_binsize[TOTAL_INST_NUMBER];

extern int	disassemble(char *file, int len);
extern char		*big_endian_string(int n, int size, int new, int *len);
extern int		big_endian_int(int int4);
extern short	big_endian_short(short int2);

extern int		get_label_addr(const char *s, t_vector *label, t_data *d);
void	write_binary(t_data *d, t_synt_tree *tree, char *f);
int		is_direct(char *s, t_data *d, t_child *c, t_pos p);
int		is_indirect(char *s, t_data *d, t_child *c, t_pos p);
int		is_register(char *s, t_data *d, t_child *c, t_pos p);

int		set_atnt_intel_addr_calc_syntax(t_child *c, t_data *d, t_synt_tree *t, int i);
void	check_operands_syntax_and_type(t_synt_tree *t, t_data *d);
void		check_atnt_syntax(t_child *c, t_data *d, t_synt_tree *t);
void		check_default_syntax(t_child *c, t_data *d, t_synt_tree *t);
void		check_intel_syntax(t_child *c, t_data *d, t_synt_tree *t);
extern void	check_operand_type(t_child *c, t_data *d, t_synt_tree *t, int i);
extern int		get_base(char *s, t_child *c, t_data *d, int *type);
void	ft_assert(int cond, enum e_err err);

extern char		*skip_numbers_base(char *s, int base);
extern int		is_label(const char *s, t_vector *label, t_data *d);

//extern int		is_label(char **s, t_data *d);
extern char		*skip_chars(const char *ch, int len, char *s, t_data *d);

int		intel_is_direct(char *s, t_data *d, t_child *c, t_pos p);
int		intel_is_indirect(char *s, t_data *d, t_child *c, t_pos p);
int		intel_is_register(char *s, t_data *d, t_child *c, t_pos p);
int		atnt_is_direct(char *s, t_data *d, t_child *c, t_pos p);
int		atnt_is_indirect(char *s, t_data *d, t_child *c, t_pos p);
int		atnt_is_register(char *s, t_data *d, t_child *c, t_pos p);
int		dflt_is_direct(char *s, t_data *d, t_child *c, t_pos p);
int		dflt_is_indirect(char *s, t_data *d, t_child *c, t_pos p);
int		dflt_is_register(char *s, t_data *d, t_child *c, t_pos p);
/*
** label_struct.c
*/

extern t_label		*new_label(char *s);

/*
** atnt_check_mov_syntax.c
*/
/*
extern int		atnt_check_mov_syntax(t_data *d, t_child *c,
									t_synt_tree *tree, int n);
*/

/*
** atnt_check_operand_type.c
*/
/*
extern int		is_register(const char *s);
extern int		is_direct_value(char *s, t_data *d);
extern int		is_indirect_value(char *s, t_data *d);
extern int		atnt_check_operand_type_syntax(t_data *d, t_child *c,
											t_synt_tree *tree, int n);
*/
/*
** atnt_check_operands.c
*/
/*
extern void		check_operands_atnt(t_data *d, t_synt_tree *tree);
extern int		altr_valid_label_syntax(const char *s);
*/
/*
** ft_perror.c
*/

void	ft_perror(const char *prefix, const char *error, t_pos *p, t_data *d);

#endif
