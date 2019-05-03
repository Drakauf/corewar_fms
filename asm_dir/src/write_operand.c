/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_operand.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 12:41:19 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 12:42:21 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int	get_reg(const char *v)
{
	while (*v != 'r')
		v++;
	return (ft_atoi(v + 1));
}

static int	get_ind(const char *v, t_data *d)
{
	int	addr;

	if (d->syntax == DFLT)
	{
		if ((addr = get_label_addr(v, d->label, d)) != -1)
			return (addr - d->cur_addr);
	}
	else
	{
		while (*v == '(' || *v == '[' || *v == '*')
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

static int	get_dir(const char *v, t_data *d)
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

extern int	write_operand(int size, int type, const char *value, t_data *d)
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
