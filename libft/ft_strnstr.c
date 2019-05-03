/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 17:58:53 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/24 21:52:33 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static long			strnstr_start(const char *str, const char *sub, size_t size)
{
	long		equal;
	size_t		i;
	const char	*substart = sub;

	if (!*sub)
		return (0);
	i = 0;
	equal = FT_TRUE;
	while (i < size && *str && *sub)
	{
		equal &= (*(str++) == *(sub++));
		++i;
	}
	if (*sub)
		return (-1);
	if (equal)
		return (0);
	equal = sub - substart;
	return (equal);
}

char				*ft_strnstr(const char *str, const char *sub, size_t size)
{
	long		subsiz;
	long		strsiz;
	const char	*p;

	if ((subsiz = strnstr_start(str, sub, size)) == -1)
		return (NULL);
	if (subsiz == 0)
		return ((char *)str);
	str = str + 1;
	strsiz = (ft_strnlen(str, size - 1) - subsiz) + 1;
	while ((p = ft_memchr(str, *sub, strsiz)))
	{
		if ((ft_strncmp(p, sub, subsiz)) == 0)
			return ((char *)p);
		strsiz += (str - p) - 1;
		str = p + 1;
	}
	return (NULL);
}
