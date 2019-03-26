/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_binary.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 12:15:50 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 19:25:02 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"
#include <fcntl.h>

void	write_param_byte(int type, int *length, int fmt[])
{
	char param;
	int	i;

	param = 0;
	if (type == FORK_M || type == LFORK_M || type == LIVE_M || type == ZJMP_M)
		return ;
	i = 6;
	while (*fmt && i)
	{
		if (*fmt == REG_O)
			param |= ((0x1 & 0x03) << i);
		else if (*fmt == IND_O)
			param |= ((0x3 & 0x03) << i);
		else if (*fmt == DIR_O)
			param |= ((0x2 & 0x03) << i);
		i -= 2;
		fmt++;
	}
	big_endian_string(param, 1, 0, length);
}

int		get_reg(const char *v)
{
	while (*v != 'r')
		v++;
	return (ft_atoi(v + 1));
}

int		get_ind(const char *v, t_data *d)
{
	int	addr;

	if (d->syntax == DFLT)
	{
		if ((addr = get_label_addr(v, d->label, d)) != -1)
			return (addr - d->cur_addr);
	}
	else
	{
		if (*v == '(' || *v == '[')
			v++;
		if (*v == '*')
			v++;
		if ((addr = get_label_addr(v, d->label, d)) != -1)
			return (addr - d->cur_addr);
	}
	while (!ft_isdigit(*v) && *v != '-')
		v++;
	if (*v == '0')
	{
		if (v[1] == 'x')
			return (ft_atoi_hexa(v));
		if (ft_isoctal(v[1]))
			return (ft_atoi_octal(v));
	}
	return (ft_atoi(v));
}

int		get_dir(const char *v, t_data *d)
{
	int	addr;

	if (d->syntax == DFLT)
	{
		if ((addr = get_label_addr(v + 1, d->label, d)) != -1)
			return (addr - d->cur_addr);
	}
	else
	{
		if (*v == '(' || *v == '[')
			v++;
		if ((addr = get_label_addr(v, d->label, d)) != -1)
			return (addr - d->cur_addr);
	}
	while (!ft_isdigit(*v) && *v != '-')
		v++;
	if (*v == '0')
	{
		if (v[1] == 'x')
			return (ft_atoi_hexa(v));
		if (ft_isoctal(v[1]))
			return (ft_atoi_octal(v));
	}
	return (ft_atoi(v));
}

int		write_operand(int size, int type, const char *value, t_data *d)
{
	int	v;

	if (type == DIR_O)
		v = get_dir(value, d);
	else if (type == IND_O)
		v = get_ind(value, d);
	else
		v = get_reg(value);
	big_endian_string(v, size, 0, NULL);
	return (size);
}

int		write_addr_operand(int *i, t_synt_tree *t, t_child *c, t_data *d)
{
	char	*s;
	int		type;
	int		size;
	int		off;
	
	s = c->s;
	size = g_binsize[t->type].opsize[*i][t->fmt[*i] - 1];
	type = t->fmt[*i];
	off = write_operand(size, type, c->s, d);
	s = ft_strchr(s, '+') + 1;
	(*i)++;
	size = g_binsize[t->type].opsize[*i][t->fmt[*i] - 1];
	type = t->fmt[*i];
	off += write_operand(size, type, c->s, d);
	return (off);
}

void	write_binary(t_data *d, t_synt_tree *t, char *f)
{
	const int		fd = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	t_header		header;
	t_child			*c;
	int				i;
	int				length;

	ft_memset(&header, '\0', sizeof(t_header));
	ft_assert(fd == -1, CREAT_ERROR);
	ft_strcpy(header.prog_name, d->name);
	ft_strcpy(header.prog_comment, d->comment);
	header.magic = big_endian_int(COREWAR_EXEC_MAGIC);
	header.prog_size = big_endian_int(d->cur_addr);
	write(fd, &header, sizeof(t_header));
	d->cur_addr = 0;
	while (t)
	{
		i = 0;
		length = 0;
		if (t->type > 0 && t->type < TOTAL_INST_NUMBER)
		{
			c = t->child;
			big_endian_string(t->type, 1, 1, &length);
			write_param_byte(t->type, &length, t->fmt);
			while (c)
			{
				if (d->syntax != DFLT && (t->type == STI_M || t->type == LDI_M || t->type == LLDI_M))
				{
					if (t->type == STI_M)
					{
						length += write_operand(g_binsize[t->type].opsize[i][t->fmt[i] - 1], t->fmt[i], c->s, d);
						c = c->next;
						i++;
						length += write_addr_operand(&i, t, c, d);
					}
					else
					{
						length += write_addr_operand(&i, t, c, d);
						c = c->next;
						i++;
						length += write_operand(g_binsize[t->type].opsize[i][t->fmt[i] - 1], t->fmt[i], c->s, d);
					}
				}
				else
					length += write_operand(g_binsize[t->type].opsize[i][t->fmt[i] - 1], t->fmt[i], c->s, d);
				c = c->next;
				i++;
			}
			write(fd, big_endian_string(0, 0, 0, NULL), length);
			d->cur_addr += length;
		}
		t = t->next;
	}
	close(fd);
}
