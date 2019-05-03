/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlen.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 11:03:43 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 17:19:32 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	const char			*ptr;
	const t_longword	*word_ptr;

	ptr = str;
	while (((t_longword)ptr % sizeof(t_longword)) != 0)
	{
		if (!*ptr)
			return (ptr - str);
		ptr++;
	}
	word_ptr = (t_longword *)ptr;
	while (1)
	{
		if (((*word_ptr - REPEAT_ONE) & ~(*word_ptr) & BLACK_HOLE) != 0)
		{
			ptr = (const char *)word_ptr;
			while (*ptr)
				ptr++;
			break ;
		}
		word_ptr++;
	}
	return (ptr - str);
}
