/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_fd_contents.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/13 22:19:34 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 18:20:54 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*newalloc(char *s, char *buf, int len, int total_len)
{
	char	*new;

	new = malloc(total_len + len + 1);
	ft_memcpy(new, s, total_len);
	ft_memcpy(new + total_len, buf, len);
	free(s);
	return (new);
}

extern char	*get_fd_contents(int fd, int *ptrlen)
{
	char	buf[2048];
	char	*s;
	int		total_len;
	int		len;

	s = NULL;
	total_len = 0;
	while ((len = read(fd, buf, 2047)) > 0)
	{
		s = (!s) ? ft_memdup(buf, len) : newalloc(s, buf, len, total_len);
		total_len += len;
	}
	if (ptrlen)
		*ptrlen = total_len;
	s[total_len] = '\0';
	return (s);
}
