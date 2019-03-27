/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   load_map.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 21:06:48 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 22:24:57 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

extern char	*get_file_contents(const char *file)
{
	char		*map;
	int			readl;
	const int	fd = open(file, O_RDONLY);
	struct stat	filestat;

	if (fd == -1)
		return (NULL);
	lstat(file, &filestat);
	if (filestat.st_size == 0)
		return (ft_strdup(""));
	if ((map = malloc(filestat.st_size + 1)) == NULL)
		return (NULL);
	readl = read(fd, map, filestat.st_size);
	map[readl] = '\0';
	return (map);
}
