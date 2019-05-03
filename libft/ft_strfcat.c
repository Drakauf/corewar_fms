/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strfcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/15 16:24:55 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/15 16:27:15 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfcat(char **s1, const char *s2)
{
	char		*new;
	const int	s2len = ft_strlen(s2);

	if ((new = (char *)malloc(s2len + ft_strlen(*s1) + 1)) == NULL)
		return (NULL);
	ft_strcpy(new, *s1);
	free(*s1);
	ft_strncat(new, s2, s2len);
	*s1 = new;
	return (new);
}
