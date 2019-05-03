/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atol.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 15:35:54 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/15 11:48:17 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static inline const char	*left_trim(const char *s, int *negative)
{
	*negative = 0;
	while (ft_isspace(*s))
		s++;
	if (ft_isdigit(*s))
		return (s);
	if (*s == '+')
	{
		s++;
		if (!ft_isdigit(*s))
			return (NULL);
	}
	else if (*s == '-')
	{
		s++;
		if (!ft_isdigit(*s))
			return (NULL);
		*negative = 1;
	}
	return (s);
}

static inline long			ft_strtol(const char *s, int negative)
{
	unsigned long	n;

	n = 0;
	while (ft_isdigit(*s))
	{
		n *= 10;
		n += *(s++) - 48;
	}
	return ((negative) ? (long)(~n + 1) : (long)n);
}

extern inline long			ft_atol(const char *s)
{
	int	negative;

	if ((s = left_trim(s, &negative)) == NULL)
		return (0);
	return (ft_strtol(s, negative));
}
