/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   skip.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 14:53:26 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 17:03:23 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern char		*skip_chars(const char *ch, int len, char *s, t_data *d)
{
	int	i;

	if (len == 0)
		return (0);
	while (*s)
	{
		i = 0;
		while (i < len)
		{
			if (*s == ch[i])
				break ;
			i++;
		}
		if (i == len)
			return (s);
		d->p.col++;
		s++;
	}
	return (s);
}

extern char		*skip_spaces(char *s, t_pos *p)
{
	while (*s == ' ' || *s == '\t')
	{
		p->col++;
		s++;
	}
	return (s);
}

extern char		*skip_new_lines(char *s, t_data *d)
{
	d->previous = d->current;
	d->current = NULL;
	d->p.col = 1;
	while (*s == '\n')
	{
		d->p.line++;
		s++;
	}
	return (s);
}

extern char		*skip_all_but(char c, char *s)
{
	while (*s && *s != c)
		s++;
	return (s);
}
