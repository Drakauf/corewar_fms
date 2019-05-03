/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fd_contents.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/11 15:19:50 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 10:49:29 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"
#include "fcntl.h"

extern char	*fd_contents(const int fd)
{
	char		*s;
	long		len;

	len = lseek(fd, 0, SEEK_END);
	ft_assert(len == -1, LSEEK_ERROR);
	ft_assert(len >= 0x7fff, TOO_LARGE_FILE);
	ft_assert(len == 0, EMPTY_FILE);
	lseek(fd, 0, SEEK_SET);
	s = malloc(len + 1);
	ft_assert(read(fd, s, len) != len, READ_ERROR);
	s[len] = '\0';
	return (s);
}
