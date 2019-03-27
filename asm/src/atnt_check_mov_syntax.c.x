/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   atnt_check_mov_syntax.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 07:04:41 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/18 15:17:21 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int			strlen_sp(char *s, t_data *d)
{
	char	*end;

	end = skip_chars(LABEL_CHARS, ft_strlen(LABEL_CHARS), s, d);
	return (end - s);
}

extern int			is_label(char **s, t_data *d)
{
	int		i;
	int		len1;
	int		len2;

	i = 0;
	len1 = strlen_sp(*s, d);
	if (len1 == 0)
		return (0);
	while (i < d->label->len)
	{
		len2 = ft_strlen((*((t_label**)(d->label->tab + (i * sizeof(void*)))))->name);
		ft_printf("cmp(\"%s\", \"%s\")\n\n", *s, (*((t_label**)(d->label->tab + (i * sizeof(void*)))))->name);
		if (len1 == len2 &&
				ft_strncmp(*s, (*((t_label**)(d->label->tab + (i * sizeof(void*)))))->name, len1) == 0)
		{
			*s += len1;
			return (1);
		}
		i++;
	}
	return (0);
}

char		*atnt_contained_register_syntax_variant(t_data *d, char *s, t_synt_tree *tree, int *n)
{
	int i;

	if (*s == '%')
		*(s++) = ' '; // simplification
	if (*s != 'r' || (i = ft_atoi(++s)) < 1 || i > REG_NUMBER)
	{
		ft_perror("mov", *n == 0 ? " operand 1" : " operand 2", &tree->p, d);
		return (NULL);
	}
	while (ft_isdigit(*(++s)))
		;
	tree->fmt[(*n)++] = T_REG;
	return (s);
}

char		*atnt_contained_register_syntax(t_data *d, char *s, t_synt_tree *tree, int n)
{
	int	i;

	if (*s == '%')
		*(s++) = ' '; // simplification...
	if (*s != 'r' || (i = ft_atoi(++s)) < 1 || i > REG_NUMBER)
	{
		ft_perror("mov", n == 0 ? " operand 1" : " operand 2", &tree->p, d);
		return (NULL);
	}
	while (ft_isdigit(*(++s)))
		;
	tree->fmt[n] = T_REG;
	return (s);
}

char		*atnt_contained_direct_value_syntax(t_data *d, char *s, t_synt_tree *tree, int n)
{
	if (!is_label(&s, d))
	{
		if (*s == '-')
		{
			if (*(++s) == '0' && s[1] == 'x')
				s += 2;
		}
		if (!ft_isdigit(*(s++)))
		{
			ft_perror("mov", n == 0 ? " operand 1" : " operand 2", &tree->p, d);
			return (NULL);
		}
		while (ft_isdigit(*s))
			s++;
	}
	tree->fmt[n] = T_DIR;
	return (s);
}

int			atnt_mov_reg_plus_reg_reg(t_data *d, t_child *c, t_synt_tree *tree, int n)
{
	char	*s;

	s = c->s + 2;
	if ((s = atnt_contained_register_syntax_variant(d, s, tree, &n)) == NULL)
		return (n);
	if (*s != ',' && *s != '+')
	{
		ft_perror("mov", n == 0 ? " operand 1" : " operand 2", &tree->p, d);
		return (n);
	}
	*(s++) = ' '; // simplification
	if ((s = atnt_contained_register_syntax(d, s, tree, n)) == NULL)
		return (n);
	if (n == 1)
	{
		c = c->next;
		if (!is_register(c->s))
		{
			ft_perror("mov", n == 0 ? " operand 1" : " operand 2", &tree->p, d);
			return (n + 1);
		}
		tree->fmt[++n] = T_REG;
	}
	return (n);
}

char		*atnt_first_operand_syntax_ok_variant(t_data *d, char *s, t_synt_tree *tree, int *n)
{
	if (*s == '*')
	{
		*(s++) = ' '; // simplification
		if (!is_label(&s, d))
		{
			if (*s == '0' && s[1] == 'x')
				s++;
			if (!ft_isdigit(s[1]))
			{
				ft_perror("mov", *n == 0 ? " operand 1" : " operand 2", &tree->p, d);
				return (NULL);
			}
		}
		tree->fmt[(*n)++] = T_IND;
		s++;
	}
	else if (ft_isdigit(*s) || (*s == '-' && ft_isdigit(*(++s))))
	{
		tree->fmt[(*n)++] = T_DIR;
		s++;
	}
	else
	{
		ft_perror("mov", *n == 0 ? " operand 1" : " operand 2", &tree->p, d);
		return (NULL);
	}
	while (ft_isdigit(*s))
		s++;
	return (s);
}

char		*atnt_second_operand_syntax_ok_variant(t_data *d, char *s, t_synt_tree *tree, int *n)
{
	int		i;

	if (*s == '%' || *s == 'r')
	{
		if (*s == '%')
			*(s++) = ' '; // simplification
		if (*s != 'r' || (i = ft_atoi(++s)) < 1 || i > REG_NUMBER)
		{
			ft_perror("mov", n == 0 ? " operand 1" : " operand 2", &tree->p, d);
			return (NULL);
		}
		while (ft_isdigit(*(++s)))
			;
		tree->fmt[(*n)++] = T_REG;
		return (s);
	}
	return (atnt_contained_direct_value_syntax(d, s, tree, *n));
}

int				atnt_check_mov_syntax_variant(t_data *d, t_child *c,
									t_synt_tree *tree, int n)
{
	char	*s;

	s = c->s + 1;
	if (*s == '%' || *s == 'r')
		return (atnt_mov_reg_plus_reg_reg(d, c, tree, n));
	if ((s = atnt_first_operand_syntax_ok_variant(d, s, tree, &n)) == NULL)
		return (n);
	if (*s != ',' && *s != '+')
	{
		ft_perror("mov", n == 0 ? " operand 1" : " operand 2", &tree->p, d);
		return (n);
	}
	*(s++) = ' '; // simplification
	if ((s = atnt_second_operand_syntax_ok_variant(d, s, tree, &n)) == NULL)
		return (n);
	if (*s != ')')
	{
		ft_perror("mov", n == 0 ? " operand 1" : " operand 2", &tree->p, d);
		return (n);
	}
	if (n == 1)
	{
		c = c->next;
		if (!is_register(c->s))
		{
			ft_perror("mov", n == 0 ? " operand 1" : " operand 2", &tree->p, d);
			d->syntax_error = 1;
			return (n);
		}
		tree->fmt[++n] = T_REG;
	}
	return (n);
}

static int		atnt_is_st_instruction(t_child **c,
								t_synt_tree *tree, int *n, t_data *d)
{
		tree->fmt[(*n)++] = T_REG;
		*c = (*c)->next;
		if (is_direct_value((*c)->s, d))
			tree->fmt[*n] = T_DIR;
		else if (is_indirect_value((*c)->s, d))
			tree->fmt[*n] = T_IND;
		else if (is_register((*c)->s))
			tree->fmt[*n] = T_REG;
		else
			tree->type = STI_M;
		if (tree->fmt[*n])
		{
			tree->type = ST_M;
			return (1);
		}
		return (0);
}

int		atnt_is_ld_instruction(t_child **c, t_synt_tree *tree,
								int *n, t_data *d)
{
	if (is_direct_value((*c)->s, d))
		tree->fmt[*n] = T_DIR;
	else if (is_indirect_value((*c)->s, d))
		tree->fmt[*n] = T_IND;
	else if (tree->type != STI_M)
		tree->type = LDI_M;
	if (tree->fmt[*n])
	{
		tree->type = LD_M;
		(*c) = (*c)->next;
		if (is_register((*c)->s))
			tree->fmt[++(*n)] = T_REG;
		else
			ft_perror(NULL, "mov operand 2", &tree->p, d);
		return (1);
	}
	return (0);
}

int			atnt_is_st_or_ld_instruction(t_child **c, t_synt_tree *tree, int *n, t_data *d)
{
	if (is_register((*c)->s))
	{
		/*
		 ** ST or STI syntax
		 */
		if (atnt_is_st_instruction(c, tree, n, d))
			return (1);
	}
	else
	{
		/*
		 ** LD, LDI or STI syntax
		 */
		if (atnt_is_ld_instruction(c, tree, n, d))
			return (1);
	}
	return (0);
}

char		*atnt_operand_1_syntax_ok(t_data *d, char *s, t_synt_tree *tree, int *n)
{
	if (*s == '*')
	{
		*(s++) = ' '; // simplification
		if (!is_label(&s, d))
		{
			if (*s == '0' && s[1] == 'x')
				s++;
			if (!ft_isdigit(s[1]))
			{
				ft_perror("mov", n == 0 ? " operand 1" : " operand 2", &tree->p, d);
				return (NULL);
			}
		}
		tree->fmt[(*n)++] = T_IND;
		s += 2;
	}
	else if (ft_isdigit(*s) || (*s == '-' && ft_isdigit(*(++s))))
	{
		tree->fmt[(*n)++] = T_DIR;
		s++;
	}
	else
	{
		ft_perror("mov", *n == 0 ? " operand 1" : " operand 2", &tree->p, d);
		return (NULL);
	}
	while (ft_isdigit(*s))
		s++;
	return (s);
}

char		*atnt_operand_2_syntax_ok(t_data *d, char *s, t_synt_tree *tree, int n)
{
	if (*s != '(')
	{
		ft_perror("mov", n == 0 ? " operand 1" : " operand 2", &tree->p, d);
		return (NULL);
	}
	*s = ' ';
	if (*(++s) == '%' || *s == 'r')
		s = atnt_contained_register_syntax(d, s, tree, n);
	else
		s = atnt_contained_direct_value_syntax(d, s, tree, n);
	return (s);
}

extern int		atnt_check_mov_syntax(t_data *d, t_child *c,
									t_synt_tree *tree, int n)
{
	char	*s;

	if (atnt_is_st_or_ld_instruction(&c, tree, &n, d))
		return (n);
	if (*c->s == '(')
		return (atnt_check_mov_syntax_variant(d, c, tree, n));
	if ((s = atnt_operand_1_syntax_ok(d, c->s, tree, &n)) == NULL
			|| (s = atnt_operand_2_syntax_ok(d, s, tree, n)) == NULL)
		return (n);
	if (*s != ')')
	{
		ft_perror("mov", n == 0 ? " operand 1" : " operand 2", &tree->p, d);
		return (n);
	}
	if (n == 1)
	{
		c = c->next;
		if (!is_register(c->s))
		{
			ft_perror("mov", n == 0 ? " operand 1" : " operand 2", &tree->p, d);
			return (n);
		}
		tree->fmt[++n] = T_REG;
	}
	return (n);
}
