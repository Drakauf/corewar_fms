/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_perror.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 02:08:03 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 16:46:15 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

#define SPACES_40	"                                        "
#define SPACES_80	SPACES_40 "" SPACES_40

static char	*get_line_x(char *f, int line, int col, int *len)
{
	char			*s;
	char			*end;
	int				i;
	static char		buf[80];

	s = f;
	while (line--)
	{
		if ((s = ft_strchr(s, '\n')) == NULL || s[1] == '\0')
			return (NULL);
		s++;
	}
	if (col > 40)
		s += (col - 40);
	if ((end = ft_strchr(s, '\n')) == NULL)
		end = ft_strchr(s, '\0');
	if (end - s > 80)
		end -= end - s - 80;
	*len = end - s;
	i = -1;
	while (++i < *len)
		buf[i] = (s[i] == '\t') ? ' ' : s[i];
	return (buf);
}

void		ft_perror(const char *prefix, const char *error,
						t_pos *p, t_data *d)
{
	int					len;
	char				*ptr;
	static char	const	space[80] = SPACES_80;

	d->syntax_error++;
	write(2, "\e[0;31mError:\e[0m ", 18);
	if (prefix)
	{
		write(2, prefix, ft_strlen(prefix));
		write(2, ": ", 2);
	}
	write(2, error, ft_strlen(error));
	write(2, ": line ", 7);
	ptr = ft_itoa(p->line);
	write(2, ptr, ft_strlen(ptr));
	write(2, ":", 1);
	ptr = ft_itoa(p->col);
	write(2, ptr, ft_strlen(ptr));
	write(2, "\n", 1);
	if ((ptr = get_line_x(d->file, p->line - 1, p->col - 1, &len)) == NULL)
		return ;
	write(2, ptr, len);
	write(2, "\n", 1);
	write(2, space, p->col - 1 > 40 ? 40 : p->col - 1);
	write(2, "\e[1;32m^\e[0m\n", 14);
}

extern void	*perror_and_set_fmt(const char *e, t_pos *p,
									t_data *d, int *fmt)
{
	ft_perror(NULL, e, p, d);
	*fmt = -1;
	return (NULL);
}
