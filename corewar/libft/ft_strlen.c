/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlen.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 11:03:43 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/21 13:52:33 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	const char			*ptr;
	const t_longword	*word_ptr;
	const t_longword	black_hole = 0x8080808080808080L;
	const t_longword	repeat_one = 0x0101010101010101L;

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
		if (((*word_ptr - repeat_one) & ~(*word_ptr) & black_hole) != 0)
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
