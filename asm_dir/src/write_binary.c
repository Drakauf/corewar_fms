/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_binary.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 12:15:50 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 12:48:30 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"
#include <fcntl.h>

static void	write_param_byte(int type, int *length, int fmt[])
{
	char	param;
	int		i;

	param = 0;
	if (type == FORK || type == LFORK || type == LIVE || type == ZJMP)
		return ;
	i = 6;
	while (*fmt && i)
	{
		if (*fmt == REG_O)
			param |= (0x1 << i);
		else if (*fmt == IND_O)
			param |= (0x3 << i);
		else if (*fmt == DIR_O)
			param |= (0x2 << i);
		i -= 2;
		fmt++;
	}
	big_endian_string(param, 1, 0, length);
}

static void	write_header(const int fd, t_data *d)
{
	t_header		header;

	ft_assert(fd == -1, CREAT_ERROR);
	ft_memset(&header, '\0', sizeof(t_header));
	ft_strcpy(header.prog_name, d->name);
	ft_strcpy(header.prog_comment, d->comment);
	header.magic = big_endian_int(MAGIC);
	header.prog_size = big_endian_int(d->cur_addr);
	write(fd, &header, sizeof(t_header));
}

static void	write_instruction(t_data *d, t_synt_tree *t, t_child *c,
								const int fd)
{
	int		length;
	int		i;

	length = 0;
	big_endian_string(t->type, 1, 1, &length);
	write_param_byte(t->type, &length, t->fmt);
	if (d->syntax != DFLT && (t->type == STI || t->type == LDI
				|| t->type == LLDI))
		length += write_mov_operands(t, c, d);
	else
	{
		i = 0;
		while (c)
		{
			length += write_operand(
						g_binsize[t->type].opsize[i][t->fmt[i] - 1],
						t->fmt[i], c->s, d);
			c = c->next;
			i++;
		}
	}
	write(fd, big_endian_string(0, 0, 0, NULL), length);
	d->cur_addr += length;
}

extern void	write_binary(t_data *d, t_synt_tree *t, char *filename)
{
	const int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);

	write_header(fd, d);
	d->cur_addr = 0;
	while (t)
	{
		if (t->type > 0 && t->type < TOTAL_INST_NUMBER)
			write_instruction(d, t, t->child, fd);
		t = t->next;
	}
	close(fd);
}
