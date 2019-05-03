/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_string.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/03 16:18:01 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 16:50:20 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

extern char		*escape_string(char *s, t_data *d)
{
	char	*tmp;
	int		n;

	tmp = s;
	n = 0;
	while (*tmp)
	{
		if (*tmp == '\\')
		{
			ft_memmove(tmp, tmp + 1, ft_strlen(tmp));
			if (*tmp == 'n')
				*tmp = '\n';
			else if (*tmp == 't')
				*tmp = '\t';
		}
		else if (*tmp == '\n')
		{
			n = -1;
			*tmp = ' ';
		}
		n++;
		tmp++;
	}
	d->p.col += n;
	return (s);
}
