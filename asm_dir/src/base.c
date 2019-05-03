/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   base.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 14:59:37 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 15:31:42 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

#define ERR1	"hexadecimal character expected after 0x"
#define ERR2	"octal character expected after 0"
#define ERR3	"character is not octal"
#define ERR4	"character is not numeric"
#define ERR5	"character is not hexadecimal"

extern char		*skip_numbers_base(char *s, int base, t_child *c, t_data *d)
{
	const char	*err;
	t_pos		p;

	err = ERR4;
	if (base == 16)
	{
		err = ERR5;
		while (ft_ishexa(*s, HEXA_SYNTAX))
			s++;
	}
	else if (base == 8)
	{
		err = ERR3;
		while (ft_isoctal(*s))
			s++;
	}
	else
		while (ft_isdigit(*s))
			s++;
	if (base == 10 || !ft_isalnum(*s))
		return (s);
	p = (t_pos){c->p.line, c->p.col + (s - c->s)};
	ft_perror(NULL, err, &p, d);
	return (NULL);
}

static int		base_16(char **s, t_data *d, t_child *c, int *type)
{
	t_pos	p;

	p.line = c->p.line;
	(*s)++;
	if (!ft_ishexa(**s, HEXA_SYNTAX))
	{
		p.col = c->p.col + (*s - c->s - 1);
		ft_perror(NULL, ERR1, &p, d);
		*type = -1;
	}
	return (16);
}

static int		base_8(char **s, t_data *d, t_child *c, int *type)
{
	t_pos	p;

	p.line = c->p.line;
	if (**s > '7')
	{
		p.col = c->p.col + (*s - c->s);
		ft_perror(NULL, ERR2, &p, d);
		*type = -1;
	}
	return (8);
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
			base = base_16(&s, d, c, type);
		else if (ft_isdigit(*s))
			base = base_8(&s, d, c, type);
	}
	return (base);
}
