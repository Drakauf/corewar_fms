/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   graph_arena.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 11:52:07 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 11:42:37 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

void		generate_borders(struct s_vdata *data)
{
	const int	color = COLOR_BORDER;
	int			w;
	int			xy;

	ft_memset(data->px, '\0', data->sy * data->pitch);
	w = 0;
	while (w < 6)
	{
		xy = 0;
		while (xy < data->sy)
		{
			data->px[w + xy * data->sx] = color;
			data->px[(data->tbx - w - 7) + xy * data->sx] = color;
			data->px[(data->sx - w - 1) + xy * data->sx] = color;
			xy++;
		}
		xy = 0;
		while (xy < data->sx)
		{
			data->px[xy + w * data->sx] = color;
			data->px[xy + (data->sy - w - 1) * data->sx] = color;
			xy++;
		}
		w++;
	}
}

static void	draw_afont(struct s_vdata *data, struct s_vm *vm,
		struct s_pos p, struct s_pos i)
{
	unsigned char	left;
	unsigned char	byte;
	unsigned char	right;
	unsigned char	info;

	if ((info = ((char *)(vm->ainfo))[i.x + i.y * 64]) >= MAX_PLAYERS + 1)
	{
		((unsigned char *)(vm->ainfo))[i.x + i.y * 64] = info - MAX_PLAYERS - 1;
		info = (info % (MAX_PLAYERS + 1)) + MAX_PLAYERS + 1;
	}
	byte = ((unsigned char *)(vm->arena))[i.x + i.y * 64];
	left = (byte & 15);
	right = (left < 10) ? left + '0' : left + 'A' - 0xA;
	byte >>= 4;
	left = (byte < 10) ? byte + '0' : byte + 'A' - 0xA;
	p.x += draw_char(left, p, g_color[info], data);
	draw_char(right, p, g_color[info], data);
}

void		generate_arena(struct s_vdata *data, struct s_vm *vm)
{
	struct s_pos	i;
	struct s_pos	p;

	i.y = 0;
	p.y = 10;
	while (i.y < 64)
	{
		i.x = 0;
		p.x = 11;
		while (i.x < 64)
		{
			draw_afont(data, vm, p, i);
			i.x++;
			p.x += 28;
		}
		i.y++;
		p.y += 18;
	}
}

void		generate_processes(struct s_vdata *data, struct s_proc *proc,
		int x, int y)
{
	register int	w;
	register int	color;

	while (proc)
	{
		x = 6 + (proc->pcount % 64) * 28;
		y = 6 + (proc->pcount / 64) * 18;
		data->px[x + y * data->sx] ? proc = proc->next : 0;
		if (data->px[x + y * data->sx])
			continue;
		color = g_color[proc->number + MAX_PLAYERS + 1];
		w = y - 1;
		while (++w < y + 17)
		{
			data->px[x + w * data->sx] = color;
			data->px[x + 27 + w * data->sx] = color;
		}
		w = x - 1;
		while (++w < x + 28)
		{
			data->px[w + y * data->sx] = color;
			data->px[w + (y + 17) * data->sx] = color;
		}
		proc = proc->next;
	}
}
