/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   labels.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 18:54:30 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 18:55:38 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern int		duplicate_label(char **s, t_vector *label, int addr)
{
	t_label		**lab;
	int			count;
	int			i;

	i = 0;
	count = 0;
	lab = (t_label**)label->tab;
	while (i < label->len)
	{
		if (ft_strcmp(lab[i]->name, *s) == 0)
		{
			if (count == 1)
				return (lab[i]->len);
			free(*s);
			*s = lab[i]->name;
			lab[i]->addr = addr;
			count++;
		}
		i++;
	}
	return (0);
}

extern int		is_valid_label(char *label, t_data *d)
{
	int		i;
	t_pos	p;

	if (d->syntax != 0)
	{
		if (ft_isdigit(*label))
			ft_perror(NULL, "label must be begin with [a-zA-Z_]", &d->p, d);
		if (*label == 'r' && label[1]
			&& ((label[2] == '\0' && label[1] > '0' && label[1] <= '9')
			|| (label[2] && label[3] == '\0' && (i = atoi(label + 1)) < REG_NUMBER && i > 9)))
			ft_perror(NULL, "label can't be a register name", &d->p, d);
	}
	i = 0;
	while (label[i])
	{
		if (!ft_isalnum(label[i]) && label[i] != '_')
		{
			p = d->p;
			p.col += i;
			ft_perror(NULL, "label illegal char", &p, d);
			return (0);
		}
		i++;
	}
	return (1);
}
