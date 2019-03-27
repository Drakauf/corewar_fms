/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   all_syntax_is_label.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 14:59:37 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 17:37:18 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

static int		strlen_sp(const char *s)
{
	static char	*label_char = NULL;
	const char	*p;
	const char	*start = s;

	if (label_char == NULL)
		label_char = LABEL_CHARS;
	p = label_char;
	while (*p)
	{
		if (*s == *p)
		{
			s++;
			p = label_char;
		}
		else
			p++;
	}
	return (s - start);
}

extern int		is_label(const char *s, t_vector *label, t_data *d)
{
	int		i;
	int		splen;
	t_label	**lab;

	i = 0;
	lab = (t_label**)label->tab;
	if (d->syntax == DFLT)
		s++;
	splen = strlen_sp(s);
	while (i < label->len)
	{
		if (splen == lab[i]->len &&
			ft_strncmp(lab[i]->name, s, splen) == 0)
		{
			return (lab[i]->len + (d->syntax == DFLT));
		}
		i++;
	}
	return (0);
}

extern int		get_label_addr(const char *s, t_vector *label, t_data *d)
{
	int		i;
	int		splen;
	t_label	**lab;

	i = 0;
	lab = (t_label**)label->tab;
	if (d->syntax == DFLT)
		s++;
	splen = strlen_sp(s);
	while (i < label->len)
	{
		if (splen == lab[i]->len &&
			ft_strncmp(lab[i]->name, s, splen) == 0)
		{
			return (lab[i]->addr);
		}
		i++;
	}
	return (-1);
}

extern char		*skip_numbers_base(char *s, int base)
{
	if (base == 16)
		while (ft_ishexa(*s, 0))
			s++;
	else if (base == 8)
		while (ft_isoctal(*s))
			s++;
	else
		while (ft_isdigit(*s))
			s++;
	return (s);
}

extern int		get_base(char *s, t_child *c, t_data *d, int *type)
{
	int		base;
	t_pos	p;

	p = c->p;
	base = 10;
	if (*s == '0')
	{
		s++;
		if (*s == 'x')
		{
			s += 2;
			if (!ft_ishexa(*s, 0))
			{
				p.col = c->p.col + (s - c->s - 1);
				ft_perror(NULL, "hexadecimal character expected after 0x", &p, d);
				*type = -1;
			}
			base = 16;
		}
		else if (ft_isdigit(*s))
		{
			if (*s > '7')
			{
				p.col = c->p.col + (s - c->s);
				ft_perror(NULL, "octal character expected after 0", &p, d);
				*type = -1;
			}
			base = 8;
		}
	}
	return (base);
}
