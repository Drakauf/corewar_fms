/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_join.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/17 17:28:52 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/17 18:33:44 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

extern char	*ft_strjpath(const char *s1, const char *s2)
{
	char		*new;
	const int	len = ft_strlen(s1);

	if (!(new = malloc(len + ft_strlen(s2) + 2)))
		return (NULL);
	ft_strncpy(new, s1, len);
	new[len] = '/';
	ft_strcpy(new + len + 1, s2);
	return (new);
}
