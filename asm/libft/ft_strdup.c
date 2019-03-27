/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 21:38:35 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 21:38:41 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	const size_t	length = ft_strlen(s) + 1;
	void			*dest;

	if ((dest = malloc(length)) == NULL)
		return (NULL);
	return ((char *)ft_memcpy(dest, (void *)s, length));
}
