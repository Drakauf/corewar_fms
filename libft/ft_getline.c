/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_getline.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 14:10:09 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/13 20:08:21 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

int				ft_getline(const int fd, char *line, size_t buffer_size)
{
	int		readl;
	int		tmp;
	char	*lfpos;

	if (fd < 0 || read(fd, NULL, 0) == -1 || !line)
		return (-1);
	if ((readl = read(fd, line, buffer_size - 1)) != 0)
	{
		line[readl] = '\0';
		if ((lfpos = ft_memchr(line, '\n', readl)) != NULL)
		{
			tmp = ft_strlen(++lfpos);
			lseek(fd, 0 - tmp, SEEK_CUR);
			ft_memset(lfpos, '\0', ft_strlen(lfpos));
		}
	}
	else
	{
		ft_memset(line, '\0', buffer_size);
		return (0);
	}
	return (1);
}
