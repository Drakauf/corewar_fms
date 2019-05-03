/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnfcat.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 11:30:56 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/15 16:24:16 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnfcat(char **s1, const char *s2, size_t size)
{
	char *new;

	if ((new = (char *)malloc(size + ft_strlen(*s1) + 1)) == NULL)
		return (NULL);
	ft_strcpy(new, *s1);
	free(*s1);
	ft_strncat(new, s2, size);
	*s1 = new;
	return (new);
}
