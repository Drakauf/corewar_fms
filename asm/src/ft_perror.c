/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_perror.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 02:08:03 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/20 17:26:32 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static char	*get_line_x(char *f, int line, int col, int *len)
{
	char	*s;
	char	*end;
	int		i;
	static char		buf[80];

	s = f;
	while (line)
	{
		s = ft_strchr(s, '\n') + 1;
		line--;
	}
	if (col > 40)
		s += (col - 40);
	end = ft_strchr(s, '\n');
	if (!end)
		end = ft_strchr(s, '\0');
	if (end - s > 80)
		end -= end - s - 80;
	*len = end - s;
	i = 0;
	while (i < *len)
	{
		buf[i] = (s[i] == '\t') ? ' ' : s[i];
		i++;
	}
	return (buf);
}

void	ft_perror(const char *prefix, const char *error, t_pos *p, t_data *d)
{
	int					len;
	char				*ptr;
	static char	const	space[80] = "                                        " 
		"                                        ";

	write(2, "\e[0;31mError:\e[0m ", 18);
	if (prefix)
		write(2, prefix, ft_strlen(prefix));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, ": line ", 7);
	ptr = ft_itoa(p->line);
	write(2, ptr, ft_strlen(ptr));
	write(2, ":", 1);
	ptr = ft_itoa(p->col);
	write(2, ptr, ft_strlen(ptr));
	write(2, "\n", 1);
	ptr = get_line_x(d->file, p->line - 1, p->col - 1, &len);
	write(2, ptr, len);
	write(2, "\n", 1);
	write(2, space, p->col - 1 > 40 ? 40 : p->col - 1);
	write(2, "\e[1;32m^\e[0m\n", 14);
	d->syntax_error++;
}

/*
void	ft_perror(const char *prefix, const char *error, t_pos *p, t_data *d)
{
	int		len;
	char	*ptr;
	static char	space[80] = "                                        " 
		"                                        ";
	static char	tab[80] = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t" 
		"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"
		"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";

	ft_printf("(perror) line = %d, col = %d, tab = %d\n", p->line, p->col, p->tab);
	write(2, "\e[0;31mError:\e[0m ", 18);
	if (prefix)
		write(2, prefix, ft_strlen(prefix));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, ": line ", 7);
	ptr = ft_itoa(p->line);
	write(2, ptr, ft_strlen(ptr));
	write(2, ": col ", 6);
	ptr = ft_itoa(p->col);
	write(2, ptr, ft_strlen(ptr));
	write(2, "\n", 1);
	ptr = get_line_x(d->file, p->line - 1, p->col - 1, &len);
	write(2, ptr, p->col);
	write(2, "\e[4;31;0;43m", 12);
	write(2, ptr + col, p->len);
	write(2, "\e[0m", 4);
	write(2, "\n", 1);
	if (p->col - p->tab > 0)
		write(2, space, p->col - p->tab < 80 ? p->col - p->tab : 80);
	if (tab > 0)
		write(2, tab, p->tab < 80 ? p->tab : 80);
	write(2, "\e[1;31m^\e[0m\n", 14);
	d->syntax_error++;
}
*/
/*
void	ft_perror(const char *prefix, const char *error, int line, t_data *d)
{
	char	*itoa_ptr;

	write(2, "\e[0;31mError:\e[0m ", 18);
	if (prefix)
	{
		write(2, prefix, ft_strlen(prefix));
		write(2, " ", 1);
	}
	write(2, error, ft_strlen(error));
	write(2, ": line ", 7);
	itoa_ptr = ft_itoa(line);
	write(2, itoa_ptr, ft_strlen(itoa_ptr));
	write(2, "\n", 1);
	d->syntax_error = 1;
}

*/
