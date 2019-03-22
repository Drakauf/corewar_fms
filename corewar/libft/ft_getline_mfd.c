/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_getline.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 14:10:09 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/30 15:10:35 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static t_file	*new_file(const int fd, t_file **ptr)
{
	t_file	*new;
	t_file	*tmp;

	new = (t_file *)malloc(sizeof(t_file));
	new->fd = fd;
	new->next = NULL;
	*new->pline = '\0';
	if (!*ptr)
	{
		*ptr = new;
		return (new);
	}
	tmp = *ptr;
	while (tmp->next)
		tmp = new->next;
	tmp->next = new;
	return (new);
}

static t_file	*get_file(const int fd, t_file *files)
{
	while (files)
	{
		if (files->fd == fd)
			return (files);
		files = files->next;
	}
	return (NULL);
}

static int		free_file(const int fd, t_file **files)
{
	t_file	*prev;
	t_file	*cur;

	prev = NULL;
	if ((cur = *files) == NULL)
		return (0);
	while (cur->fd != fd)
	{
		prev = cur;
		if (!cur->next)
			return (0);
		cur = cur->next;
	}
	if (!prev)
	{
		prev = (*files)->next ? (*files)->next : NULL;
		free(*files);
		*files = prev;
	}
	else
	{
		prev->next = cur->next;
		free(cur);
	}
	return (0);
}

static int		set_line(t_file *file, char *buf, char **line)
{
	int		readl;
	char	*chrpos;

	while ((readl = read(file->fd, buf, FT_BUFSIZ)) > 0)
	{
		if (!*line)
			*line = ft_strdup("");
		buf[readl] = '\0';
		if ((chrpos = ft_memchr(buf, '\n', readl)) != NULL)
		{
			ft_memcpy(file->pline, chrpos + 1, ft_strlen(chrpos + 1) + 1);
			if (!(ft_strnfcat(line, buf, chrpos - buf)))
				return (0);
			ft_crep(*line, '\n', '\0');
			return (1);
		}
		if (!(ft_strnfcat(line, buf, readl + 1)))
			return (0);
	}
	*file->pline = '\0';
	return (*line ? 1 : 0);
}

int				ft_getline_mfd(const int fd, char **line)
{
	static t_file	*files = NULL;
	char			buf[FT_BUFSIZ + 1];
	char			*chrpos;
	t_file			*f;

	if (!line)
		return (free_file(fd, &files) - 1);
	*line = NULL;
	if (fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	if (!(f = get_file(fd, files))
			&& !(f = new_file(fd, &files)))
		return (-1);
	*buf = '\0';
	if (ft_strlen(f->pline) > 0)
	{
		if ((chrpos = ft_strchr(f->pline, '\n')) != NULL)
		{
			*line = ft_strndup(f->pline, chrpos - f->pline);
			ft_memmove(f->pline, chrpos + 1, ft_strlen(chrpos + 1) + 1);
			return (1);
		}
		*line = ft_strdup(f->pline);
	}
	return (set_line(f, buf, line) == 0 ? free_file(fd, &files) : 1);
}
