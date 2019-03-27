/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_chrep_all.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 21:30:59 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/15 13:38:01 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_crepall(char *s, int c, int replace)
{
	size_t	count;

	count = 0;
	while ((s = ft_strchr(s, c)) != NULL)
	{
		*(s++) = replace;
		count++;
	}
	return (count);
}
