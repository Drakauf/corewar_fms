/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrep.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 20:08:03 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/24 17:39:17 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

static size_t	get_rep_count(const char *s, const char *search)
{
	size_t	count;

	count = 0;
	while ((s = ft_strstr(s, search)))
	{
		s++;
		count++;
	}
	return (count);
}

char			*ft_strrep(const char *s, const char *search,
							const char *replace)
{
	const size_t	replen = ft_strlen(replace);
	const size_t	sealen = ft_strlen(search);
	const char		*prev;
	char			*new;
	size_t			off;

	if ((off = get_rep_count(s, search)) == 0)
		return (ft_strdup(s));
	if (!(new = (char *)malloc(ft_strlen(s) + 1 + off * (replen - sealen))))
		return (NULL);
	prev = s;
	off = 0;
	while ((s = (const char *)ft_strstr(s, search)) != NULL)
	{
		ft_memcpy(new + off, prev, s - prev);
		off += (t_longword)(s - prev);
		ft_memcpy(new + off, replace, replen);
		off += replen;
		prev = s + sealen;
		s += sealen;
	}
	strcpy(new + off, prev);
	return (new);
}
