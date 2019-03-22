/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/22 17:24:05 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/26 13:51:56 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static const char	*delete_left_spaces(const char *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}

static size_t		str_no_end_spaces_length(const char *s, char c)
{
	const char	*start = s;

	s += ft_strlen(s) - 1;
	while (*s == c)
		s--;
	return ((size_t)(s - start));
}

char				*ft_strctrim(const char *s, char c)
{
	size_t	length;

	if (!s)
		return (NULL);
	s = delete_left_spaces(s, c);
	if (!*s)
		return ((char *)ft_memalloc(1));
	length = str_no_end_spaces_length(s, c);
	return (ft_strndup(s, length + 1));
}
