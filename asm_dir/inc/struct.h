/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   struct.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 13:05:02 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 16:05:48 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum	e_inst
{
	LABEL, LIVE, LD, ST, ADD, SUB, AND, OR, XOR,
	ZJMP, LDI, STI, FORK, LLD, LLDI, LFORK, AFF, SECTION
};

enum	e_hexatype
{
	HEXA_MIN, HEXA_MAJ, HEXA_BOTH
};

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
	OUTPUT_EXPECT,
	EMPTY_FILE,
	TOO_LARGE_FILE,
	LSEEK_ERROR,
	MEMORY_ERROR,
	READ_ERROR
};

typedef struct s_header		t_header;
typedef struct s_param		t_param;
typedef struct s_inst_size	t_inst_size;
typedef struct s_inst_info	t_inst_info;
typedef struct s_label		t_label;
typedef struct s_pos		t_pos;
typedef struct s_data		t_data;
typedef struct s_child		t_child;
typedef struct s_synt_tree	t_synt_tree;

struct		s_param
{
	int	count;
	int	type[3];
	int	size[3];
};

# define PROG_NAME_LENGTH		128
# define PROG_COMMENT_LENGTH	2048

struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			prog_comment[PROG_COMMENT_LENGTH + 1];
};

struct		s_inst_size
{
	int		param_byte;
	int		opsize[3][3];
};

struct		s_inst_info
{
	int		n_operand;
	int		fmt[3];
};

struct		s_label
{
	char	*name;
	int		len;
	int		addr;
};

struct		s_pos
{
	int		line;
	int		col;
};

struct		s_data
{
	int					syntax_error;
	int					syntax;
	int					header_stat;
	int					file_len;
	t_pos				p;
	t_pos				tmp_p;
	int					cur_inst_error;
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
	char				*start;
	struct s_synt_tree	*current;
	struct s_synt_tree	*previous;
	struct s_synt_tree	*t;
	struct s_inst_info	*inst_info;
};

struct		s_child
{
	char			*s;
	t_pos			p;
	int				len;
	int				fmt;
	struct s_child	*next;
};

struct		s_synt_tree
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
};

#endif
