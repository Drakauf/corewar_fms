/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/22 17:24:05 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/15 17:34:35 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static size_t		str_no_end_spaces_length(const char *s)
{
	const char	*start = s;

	s += ft_strlen(s) - 1;
	while (ft_isspace(*s))
		s--;
	return ((size_t)(s - start));
}

extern inline char	*ft_strtrim(const char *s)
{
	size_t	length;

	if (!s)
		return (NULL);
	s = (const char *)ft_ltrim(s);
	if (!*s)
		return ((char *)ft_memalloc(1));
	length = str_no_end_spaces_length(s);
	return (ft_strndup(s, length + 1));
}
