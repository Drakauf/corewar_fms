/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_file_contents.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 10:49:04 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 11:39:59 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

static char	*fd_contents(const int fd, int *l)
{
	char		*s;
	long		len;

	len = lseek(fd, 0, SEEK_END);
	ft_assert(len == -1, LSEEK_ERROR);
	ft_assert(len >= 0x7fffffffL, TOO_LARGE_FILE);
	ft_assert(len == 0, EMPTY_FILE);
	lseek(fd, 0, SEEK_SET);
	s = malloc(len + 1);
	ft_assert((read(fd, s, len) != len), READ_ERROR);
	s[len] = '\0';
	*l = (int)len;
	return (s);
}

extern char	*get_contents(const char *const name, int *len,
								const char *const output)
{
	const int	fd = open(name, O_RDONLY);
	char		*contents;
	int			i;

	ft_assert(fd == -1, OPEN_ERROR);
	contents = fd_contents(fd, len);
	close(fd);
	if (!contents)
		return (NULL);
	if (output)
	{
		i = 0;
		while (contents[i] && (contents[i] < 33 || contents[i] == 127))
			i++;
		if (contents[i] == '\0')
		{
			free(contents);
			return (NULL);
		}
	}
	return (contents);
}
