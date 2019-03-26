/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 10:47:07 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 10:47:44 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern int		valid_ext(const char *s, const char *ext)
{
	const char	*start = s;

	s += ft_strlen(s) - 1;
	while (1)
	{
		if (*s == '.')
			break ;
		if (s == start)
			return (0);
		s--;
	}
	return (ft_strcmp(s + 1, ext) == 0 ? 1 : 0);
}

extern char		*replace_ext(const char *s)
{
	char	*new;
	int		len;
	int		i;

	new = malloc((len = ft_strlen(s)) + 3);
	i = len + 2;
	new[i--] = '\0';
	new[i--] = 'r';
	new[i--] = 'o';
	new[i--] = 'c';
	while (i > -1)
	{
		new[i] = s[i];
		i--;
	}
	return (new);
}
