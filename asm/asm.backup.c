/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 06:46:23 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/16 00:25:53 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"
#include "../../libft/libft.h"
/*
t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
};
*/

/*
"AT&T" :
t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"mov", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},  //ld
	{"mov", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0}, //st
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"jz", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"mov", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1}, //ldi :: mov %r1(%r2), %reg
	{"mov", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1}, //sti :: mov %reg, %r1(%r1)
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lmov", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lmov", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, "long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{"nop"}
};
*/
/*
const int	g_operand_mask[17][4][3] = {
	{{0, 0, MASK_4}, {0}, {0}},
	{{0, MASK_2, MASK_4}, {MASK_1}, {0}, {0}},
	{{MASK_1}, {MASK_1, MASK_2}, {0}, {0}},
	{{MASK_1}, {MASK_1}, {MASK_1}, {0}},
	{{MASK_1}, {MASK_1}, {MASK_1}, {0}},
	{{MASK_1, MASK_2, MASK_4}, {MASK_1, MASK_2, MASK_4}, {MASK_1}, {0}},
	{{MASK_1, MASK_2, MASK_4}, {MASK_1, MASK_2, MASK_4}, {MASK_1}, {0}},
	{{MASK_1, MASK_2, MASK_4}, {MASK_1, MASK_2, MASK_4}, {MASK_1}, {0}},
	{{0, 0, MASK_2}, {0}, {0}, {0}},
	{{MASK_1, MASK_2, MASK_2}, {MASK_1, 0, MASK_2}, {}, {}}
};
*/
const int	g_altr_inst_fmt[17][4] = {
	{T_DIR, 0, 0, 0},				//live
	{T_DIR | T_IND, T_REG, 0, 0},	//ld (mov)
	{T_REG, T_REG | T_IND, 0},		//st (mov)
	{T_REG, T_REG, T_REG, 0},		//add
	{T_REG, T_REG, T_REG, 0},		//sub
	{T_RDI, T_RDI, T_REG, 0},		//and
	{T_RDI, T_RDI, T_REG, 0},		//or
	{T_RDI, T_RDI, T_REG, 0},		//xor
	{T_IND, 0, 0, 0},				//zjmp (jz)
	{T_IND, 0, 0, 0},				//fork
	{T_DIR | T_IND, T_REG, 0, 0},	//lld  (lmov)
	{T_RDI, T_DIR | T_REG, T_REG},	//lldi (lmov)
	{T_IND, 0, 0, 0},				//lfork
	{T_REG, 0, 0, 0},				//aff (nop)
};

const int	g_dflt_inst_fmt[17][4] = {
	{T_DIR, 0, 0, 0},				//live
	{T_DIR | T_IND, T_REG, 0, 0},	//ld (mov)
	{T_REG, T_REG | T_IND, 0},		//st (mov)
	{T_REG, T_REG, T_REG, 0},		//add
	{T_REG, T_REG, T_REG, 0},		//sub
	{T_RDI, T_RDI, T_REG, 0},		//and
	{T_RDI, T_RDI, T_REG, 0},		//or
	{T_RDI, T_RDI, T_REG, 0},		//xor
	{T_DIR, 0, 0, 0},				//zjmp (jz)
	{T_DIR, 0, 0, 0},				//fork
	{T_DIR | T_IND, T_REG, 0, 0},	//lld  (lmov)
	{T_RDI, T_DIR | T_REG, T_REG},	//lldi (lmov)
	{T_DIR, 0, 0, 0},				//lfork
	{T_REG, 0, 0, 0},				//aff (nop)
};

const char	*g_default_inst_set[DFLT_INST_NUMBER] = {
	"", "live", "ld", "st", "add", "sub", "and", "or", "xor",
	"zjmp", "fork", "lfork", "sti", "ldi", "lld", "lldi", "aff"
};

const char	*g_alternate_inst_set[ALTR_INST_NUMBER] = {
	"", "live", "mov", "add", "sub", "and", "or",
	"xor", "jz", "fork", "lfork", "lmov", "nop"
};

void	ft_assert(int cond, enum e_err err, int val)
{
	static char	*fmt[] = {
		"missing .name section\n",
		"missing .comment section\n",
		".name: bad character (line %d)\n",
		".comment: bad character (line %d)\n",
		".text: bad character (line %d)\n",
		"cannot open file\n",
		"Too few arguments\n",
		"Too many arguments\n",
		".name: too many characters (line %d)\n",
		".comment: too many characters (line %d)\n",
		"duplicate .name\n",
		"duplicate .comment\n"
	};

	if (cond)
	{
		ft_printf(fmt[err], val);
		exit(-1);
	}
}

int		is_label(const char *s, int *i, t_data *d)
{
	int		j;
	int		len;
	char	**label;

	j = 0;
	label = (char**)d->label->tab;
	while (j < d->label->len)
	{
		len = ft_strlen(label[j]);
		ft_printf("cmp('%.*s', '%.*s');\n", len, s, len, label[j]);
		if (s[len] == '\n' && ft_strncmp(s, label[j], len) == 0)
		{
			*i += len + 1;
			return (1);
		}
		j++;
	}
	return (0);
}

int		get_inst_number(const char *s, const char **inst, int len, int *i)
{
	register int	inst_len;

	while (--len)
	{
		inst_len = ft_strlen(inst[len]);
		if (s[inst_len] == ' ' && ft_strncmp(s, inst[len], inst_len) == 0)
		{
			*i += inst_len + 1;
			return (len);
		}
	}
	return (-1);
}

int		get_instruction(t_data *d, int *i)
{
	int		inst;
	char	*sp;

	while (is_label(d->file + *i, i, d) == 1)
		;
	inst = get_inst_number(d->file + *i, d->inst_set, d->n_inst, i);
	if (inst == -1)
	{
		sp = ft_strchr(d->file + *i, ' ');
		if (!sp)
		{
			sp = ft_strchr(d->file + *i, '\n');
			if (!sp)
				sp = ft_strchr(d->file + *i, '\0');
		}
		ft_printf("unknown instruction %.*s\n", sp - (d->file + *i), d->file + *i);
		exit(-1);
	}
	return (inst);
}

int		check_operands(t_data *d, int i, int cur_inst)
{
	char	*lf;

	lf = ft_strchr(d->file + i, '\n');
	if (!lf)
		lf = ft_strchr(d->file + i, '\0');
	else
		lf++;
	return (lf - d->file);
}

void	semantic_check(t_data *d)
{
	int	i;
	int	cur_inst;

	i = 0;
	d->addr = 0;
	d->label_addr = malloc(sizeof(int) * d->label->len);
	ft_memset(d->label_addr, '\0', sizeof(int) * d->label->len);
	while (d->file[i])
	{
		cur_inst = get_instruction(d, &i);
		ft_printf("cur_inst = %#x\n", cur_inst);
		i = check_operands(d, i, cur_inst);
	}
}

int		skip_comment(t_data *d, int i)
{
	i++;
	while (d->file[i] != '\n' && d->file[i] != '\0')
		i++;
	return (i);
}

int		write_space_and_skip_tab(t_data *d, char *new, int i, int *j)
{
	if (*j != 0 && (new[*j - 1] != ' ' && new[*j - 1] != '\n'))
		new[(*j)++] = ' ';
	while (d->file[i] == ' ' || d->file[i] == '\t')
		i++;
	return (i);
}

int		set_name(t_data *d, int i)
{
	int	j;

	j = i - 1;
	while (j > -1 && d->file[j] != '\n')
	{
		ft_assert((d->file[j] != ' ' || d->file[j] != '\t'), SYNTAX_NAME, d->line);
		j--;
	}
	i += 5;
	if (d->file[i] != ' ' && d->file[i] != '\t' && d->file[i + 1] != '"')
	{
		write(2, "ERR_00\n", 7);
		exit(-1);
	}
	i += 2;
	j = i;
	while (d->file[i] != '"' || d->file[i - 1] == '\\')
		ft_assert(d->file[i++] == '\0', SYNTAX_NAME, d->line);
	ft_assert(i > PROG_NAME_LENGTH, NAME_LENGTH, d->line);
	ft_strncpy(d->header.prog_name, d->file + j, i);
	while (d->file[++i] != '\n' && d->file[i] != '\0')
		;
	return (d->file[i] == '\n' ? i + 1 : i);
}

int		set_comment(t_data *d, int i)
{
	int	j;

	j = i - 1;
	while (j > -1 && d->file[j] != '\n')
	{
		ft_assert((d->file[j] != ' ' && d->file[j] != '\t'), SYNTAX_COMMENT, d->line);
		j--;
	}
	i += 8;
	if (d->file[i] != ' ' && d->file[i] != '\t' && d->file[i + 1] != '"')
	{
		write(2, "ERR_01\n", 7);
		exit(-1);
	}
	i += 2;
	j = i;
	while (d->file[i] != '"' || d->file[i - 1] == '\\')
		ft_assert(d->file[i++] == '\0', SYNTAX_COMMENT, d->line);
	ft_assert(i > PROG_COMMENT_LENGTH, COMMENT_LENGTH, d->line);
	ft_strncpy(d->header.prog_comment, d->file + j, i);
	while (d->file[++i] != '\n' && d->file[i] != '\0')
		;
	return (d->file[i] == '\n' ? i + 1 : i);
}

int		set_header_info(t_data *d, int i)
{
	if (ft_strncmp(d->file + i, ".name", 5) == 0)
	{
		ft_assert(d->header_stat & 0x1, DUPLICATE_NAME, d->line);
		d->header_stat |= 0x1;
		return (set_name(d, i));
	}
	else if (ft_strncmp(d->file + i, ".comment", 8) == 0)
	{
		ft_assert(d->header_stat & 0x2, DUPLICATE_COMMENT, d->line);
		d->header_stat |= 0x2;
		return (set_comment(d, i));
	}
	ft_assert(1, ILLEGAL_CHAR, d->line);
	return (0x0);
}

int		authorized_char(t_data *d, char c)
{
	static char	*authorized = NULL;
	char		*i;

	if (authorized == NULL)
	{
		if (d->syntax == ATNT)
			authorized = ATNT_AUTHORIZED_CHAR;
		else if (d->syntax == INTL)
			authorized = INTL_AUTHORIZED_CHAR;
		else
			authorized = DFLT_AUTHORIZED_CHAR;
	}
	i = authorized;
	while (*i)
	{
		if (*i == c)
			return (1);
		++i;
	}
	return (0);
}

int		skip_endl(t_data *d, int i)
{
	d->line++;
	i++;
	while (d->file[i] == '\n')
		i++;
	return (i);
}

int		is_comment(t_data *d, char c)
{
	int	i;

	if (d->coml == 0)
		return (0);
	i = 0;
	while (i < d->coml)
	{
		if (c == d->com[i])
			return (1);
		i++;
	}
	return (0);
}

int		get_label(t_data *d, int i, char *new, int *j)
{
	int		k;
	t_all	label;

	k = i - 1;
	while (ft_isalnum(d->file[k]) || d->file[k] == '_')
		k--;
	label = (t_all)ft_strndup(d->file + k + 1, i - k);
	ft_printf("label.push_back(\"%s\");\n", label);
	d->label->push_back(d->label, label);
	while (d->file[++i] == ' ' || d->file[i] == '\t')
		;
	new[(*j)++] = ':';
	if (d->file[i] != '\n')
		new[(*j)++] = '\n';
	return (i);
}

void	delete_comments_trim_and_set_header(t_data *d)
{
	char		*new;
	int			i;
	int			j;

	i = 0;
	j = 0;
	new = malloc(ft_strlen(d->file) + 1);
	while (d->file[i])
	{
		if (is_comment(d, d->file[i]))
			i = skip_comment(d, i);
		else if (d->file[i] == '\t' || d->file[i] == ' ')
			i = write_space_and_skip_tab(d, new, i, &j);
		else if (d->file[i] == '.')
			i = set_header_info(d, i);
		else if (d->file[i] == LABEL_CHAR && i && ft_isalnum(d->file[i - 1]))
			i = get_label(d, i, new, &j);
		else if (d->file[i] == '\n')
		{
			i = skip_endl(d, i);
			if (j && new[j - 1] != '\n')
				new[j++] = '\n';
		}
		else
		{
			ft_assert(!authorized_char(d, d->file[i]), ILLEGAL_CHAR, d->line);
			new[j++] = d->file[i++];
		}
	}
	free(d->file);
	d->file = new;
	ft_assert((d->header_stat & 0x1) == 0x0, NAME_MISSING, 0);
	ft_assert((d->header_stat & 0x2) == 0x0, COMMENT_MISSING, 0);
}

void	set_specific_syntax(t_data *d)
{
	if (d->syntax == ATNT)
	{
		d->ind = ATNT_IND;
		d->dir = ATNT_DIR;
		d->reg = ATNT_REG;
		d->com = ATNT_COM;
	}
	if (d->syntax == INTL)
	{
		d->ind = ATNT_IND;
		d->dir = ATNT_DIR;
		d->reg = ATNT_REG;
		d->com = ATNT_COM;
	}
	else
	{
		d->ind = DFLT_IND;
		d->dir = DFLT_DIR;
		d->reg = DFLT_REG;
		d->com = DFLT_COM;
	}
	d->indl = ft_strlen(d->ind);
	d->dirl = ft_strlen(d->dir);
	d->regl = ft_strlen(d->reg);
	d->coml = ft_strlen(d->com);
}

void	delete_com_and_trim(t_data *d)
{
	d->line = 1;
	d->header_stat = 0;
	set_specific_syntax(d);
	d->label = new_vector(VECTOR_PTR, 8);
	delete_comments_trim_and_set_header(d);
	if (d->syntax == 0)
	{
		d->inst_set = g_default_inst_set;
		d->n_inst = DFLT_INST_NUMBER;
	}
	else
	{
		d->inst_set = g_alternate_inst_set;
		d->n_inst = ALTR_INST_NUMBER;
	}
	ft_printf("file =\n'%s'\n", d->file);
	semantic_check(d);
}

int		get_argument(const char *arg, t_data *d)
{
	if (ft_strcmp(arg, "--syntax-1") == 0) 
	{
		d->syntax = ATNT;
		return (1);
	}
	if (ft_strcmp(arg, "--syntax-2") == 0) 
	{
		d->syntax = INTL;
		return (1);
	}
	d->syntax = DFLT;
	return (0);
}

int		main(int ac, char *av[])
{
	t_data	data;

	ft_assert(ac < 2, TOO_FEW_ARGS, 0);
	ft_assert(ac > 3, TOO_MANY_ARGS, 0);
	av += get_argument(av[1], &data);
	ft_assert(!(data.file = get_file_contents(av[1])), OPEN_ERROR, 0);
	delete_com_and_trim(&data);
}
