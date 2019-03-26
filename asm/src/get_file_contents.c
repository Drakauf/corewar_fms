/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_file_contents.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 10:49:04 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 10:50:44 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

extern char		*get_contents(const char *name, int *len)
{
	const int	fd = open(name, O_RDONLY);
	char		*contents;

	ft_assert(fd == -1, OPEN_ERROR);
	contents = get_fd_contents(fd, len);
	close(fd);
	return (contents);
}
