/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   atnt_check_operand_type_syntax.c                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 07:00:08 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/18 12:17:28 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

/*
** Hexa bloque par les fonction is_direct_value() && is_indirect_value()
** (le x de 0x ne passera pas)
**
** Les labels ne passent pas non plus (embetant pour un jump)
*/

extern int		is_register(const char *s)
{
	int	n;

	if (*s == '%' || *s == 'r')
	{
		if (*s == '%')
			s++;
		if (*s != 'r' || (n = ft_atoi(++s)) == 0 || n > REG_NUMBER)
			return (0);
		while (ft_isdigit(*(++s)))
				;
		return (T_REG);
	}
	return (0);
}

extern int		is_direct_value(char *s, t_data *d)
{
	if (*s != '$' && !is_label(&s, d))
	{
		if (*s == '$')
			s++;
		if (*s == '-')
			s++;
		if (!ft_isdigit(*(s++)))
			return (0);
		while (ft_isdigit(*s))
			s++;
	}
	return (T_DIR);
}

extern int		is_indirect_value(char *s, t_data *d)
{
	if (*s != '(')
		return (0);
	s++;
	if (!is_label(&s, d))
	{
		if (!ft_isdigit(*(s++)))
			return (0);
		while (ft_isdigit(*s))
			s++;
	}
	if (*s != ')')
		return (0);
	return (T_IND);
}

extern int		atnt_check_operand_type_syntax(t_data *d, t_child *c,
											t_synt_tree *tree, int n)
{
	if (tree->type == LD_M)
		n = atnt_check_mov_syntax(d, c, tree, n);
	else if (is_direct_value(c->s, d))
		tree->fmt[n] = T_DIR;
	else if (is_indirect_value(c->s, d))
		tree->fmt[n] = T_IND;
	else if (is_register(c->s))
		tree->fmt[n] = T_REG;
	/*
	else if (tree->type == LLD_M) // lldi
*/
	return (n + 1);
}
