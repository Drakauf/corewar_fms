/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi_octal.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 01:20:49 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 08:27:50 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static inline const char		*left_trim(const char *s)
{
	while (ft_isspace(*s))
		s++;
	if (*s == '0')
	{
		s++;
		while (*s == '0')
			s++;
		return (s);
	}
	return (NULL);
}

static inline unsigned int		ft_strtoi(const char *s)
{
	unsigned int	n;

	n = 0;
	while (1)
	{
		if (*s > '7' || *s < '0')
			break ;
		n *= 8;
		n += *(s++) - '0';
	}
	return (n);
}

extern inline unsigned int		ft_atoi_octal(const char *s)
{
	if ((s = left_trim(s)) == NULL)
		return (0);
	return (ft_strtoi(s));
}
