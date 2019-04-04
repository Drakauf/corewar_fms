/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   graphics.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 13:45:44 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 17:09:17 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"
#include <math.h>

const int	g_color[2 * MAX_PLAYERS + 2] = {
	COLOR_NONE, COLOR_ORANGE, COLOR_GREEN, COLOR_CYAN, COLOR_RED,
	COLOR_LNONE, COLOR_LORANGE, COLOR_LGREEN, COLOR_LCYAN, COLOR_LRED
};

static void	generate_borders(struct s_vdata *data)
{
	const int	color = COLOR_BORDER;
	int			x;
	int			y;

	x = -1;
	while (++x < 6)
	{
		y = -1;
		while (++y < data->sy)
		{
			data->px[x + y * data->sx] = color;
			data->px[(data->tbx - x - 7) + y * data->sx] = color;
			data->px[(data->sx - x - 1) + y * data->sx] = color;
		}
	}
	x = -1;
	while (++x < data->sx)
	{
		y = -1;
		while (++y < 6)
		{
			data->px[x + y * data->sx] = color;
			data->px[x + (data->sy - y - 1) * data->sx] = color;
		}
	}
}

void		cw_init_window(struct s_vdata *data)
{
	int		t;

	data->tbx = 1810;
	data->sx = 2456;
	data->sy = 1164;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	data->win = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, data->sx, data->sy, 0);
	data->rd = SDL_CreateRenderer(data->win, -1, 0);
	data->tx = SDL_CreateTexture(data->rd, SDL_PIXELFORMAT_ARGB32,
		SDL_TEXTUREACCESS_STREAMING, data->sx, data->sy);
	t = SDL_SetRenderTarget(data->rd, data->tx);
	t = SDL_LockTexture(data->tx, NULL, (void **)&data->px, &data->pitch);
	ft_memset(data->px, '\0', data->sy * data->pitch);
	generate_borders(data);
	data->font = load_font();
	SDL_UnlockTexture(data->tx);
	SDL_RenderCopy(data->rd, data->tx, NULL, NULL);
	SDL_RenderPresent(data->rd);
}

unsigned char	to_hex(unsigned char c)
{
	if (c < 10)
		return (c + '0');
	else
		return (c + 'A' - 0xA);
}

static void	draw_afont(struct s_vdata *data, struct s_vm *vm,
		struct s_pos p, struct s_pos i)
{
	struct s_pos	px;
	unsigned char	left;
	unsigned char	right;
	unsigned char	info;

	if ((info = ((char *)(vm->ainfo))[i.x + i.y * 64]) >= MAX_PLAYERS + 1)
	{
		((unsigned char *)(vm->ainfo))[i.x + i.y * 64] -= (MAX_PLAYERS + 1);
		info = (info % (MAX_PLAYERS + 1)) + MAX_PLAYERS + 1;
	}
	left = ((unsigned char *)(vm->arena))[i.x + i.y * 64];
	right = to_hex(left & 15);
	left = to_hex(left >> 4);
	px.y = -1;
	while (++(px.y) < 10)
	{
		px.x = -1;
		while (++(px.x) < 8)
		{
			data->px[p.x + px.x + (p.y + px.y) * data->sx] =
				data->font[left][px.x + px.y * 8] * g_color[(int)(info & 15)];
			data->px[p.x + px.x + 10 + (p.y + px.y) * data->sx] =
				data->font[right][px.x + px.y * 8] * g_color[(int)(info & 15)];
		}
	}
}

static void	generate_arena(struct s_vdata *data, struct s_vm *vm)
{
	struct s_pos	i;
	struct s_pos	p;

	i.y = 0;
	while (i.y < 64)
	{
		p.y = 10 + i.y * 18;
		i.x = 0;
		while (i.x < 64)
		{
			p.x = 11 + i.x * 28;
			draw_afont(data, vm, p, i);
			i.x++;
		}
		i.y++;
	}
}

static void	generate_processes(struct s_vdata *data, struct s_proc *proc)
{
	struct s_pos	start;
	struct s_pos	i;
	int				color;

	while (proc)
	{
		color = g_color[proc->number + MAX_PLAYERS + 1];
		start.x = 6 + (proc->pcount % 64) * 28;
		start.y = 6 + (proc->pcount / 64) * 18;
		i.y = start.y;
		while (i.y < start.y + 17)
		{
			data->px[start.x + i.y * data->sx] = color;
			data->px[start.x + 27 + i.y * data->sx] = color;
			i.y++;
		}
		i.x = start.x;
		while (i.x < start.x + 28)
		{
			data->px[i.x + start.y * data->sx] = color;
			data->px[i.x + (start.y + 17) * data->sx] = color;
			i.x++;
		}
		proc = proc->next;
	}
}

static void	draw_ply_name(struct s_vdata *data, struct s_vm *vm, int ply, int y)
{
	int		i;
	int		x;
	int		j;

	i = 0;
	x = data->tbx;
	while (vm->headers[ply].prog_name[i])
	{
		x += draw_char(vm->headers[ply].prog_name[i], (struct s_pos){x, y},
			g_color[ply + 1], data);
		i++;
	}
	x += 4;
	x += draw_char('(', (struct s_pos){x, y}, g_color[ply + 1], data);
	j = 0;
	while (vm->headers[ply].comment[j] && i + j < 80)
	{
		x += draw_char(vm->headers[ply].comment[j], (struct s_pos){x, y},
			g_color[ply + 1], data);
		j++;
	}
	x += draw_char(')', (struct s_pos){x, y}, g_color[ply + 1], data);
}

static int	draw_ply_scores(struct s_vdata *data, struct s_vm *vm, int y)
{
	int		player;
	int		x;

	player = 0;
	while (player < vm->players)
	{
		draw_ply_name(data, vm, player, y);
		y += 18;
		x = 0;
		while (x < 300)
		{
			draw_line((struct s_pos){x + data->tbx, y},
				(struct s_pos){x + data->tbx, y + 10 - 1},
				(vm->llives[player] > vm->tcycles * x / 300) ?
				g_color[player + 1] : COLOR_NONE, data);
			x++;
		}
		draw_score((struct s_pos){data->tbx + 312, y}, vm->llives[player],
			g_color[player + 2 + MAX_PLAYERS], data);
		y += 18;
		player++;
	}
	return (y + 20);
}

static int	draw_kill_time(struct s_vdata *data, struct s_vm *vm, int y)
{
	int			x;

	draw_str("Next kill operation:", (struct s_pos){data->tbx, y}, COLOR_WHITE,
		data);
	y += 18;
	x = 0;
	while (x < 256)
	{
		draw_line((struct s_pos){x + data->tbx, y},
			(struct s_pos){x + data->tbx, y + 9},
			(vm->cycles * 256 / vm->kcycles > x) ? (16776960 - x * 65536) :
			COLOR_NONE, data);
		x++;
	}
	x = data->tbx + 268 + draw_score((struct s_pos){data->tbx + 268, y},
		vm->kcycles - vm->cycles, COLOR_WHITE, data);
	draw_str(" cycles", (struct s_pos){x, y}, COLOR_WHITE, data);
	y += 26;
	return (y);
}

static int	living_count(struct s_proc *p, int pnum, struct s_vm *vm)
{
	int		i;

	i = 0;
	while (p)
	{
		i += (p->number == pnum && (vm->zcycles - p->lives < vm->kcycles));
		p = p->next;
	}
	return (i);
}

static int	process_count(struct s_proc *p, int pnum)
{
	int		i;

	i = 0;
	while (p)
	{
		i += (p->number == pnum);
		p = p->next;
	}
	return (i);
}

static int	draw_process_count(struct s_vdata *data, struct s_vm *vm, int y)
{
	int				pl;
	int				c;
	int				d;
	int				x;

	pl = 0;
	while (pl < vm->players)
	{
		x = data->tbx + draw_str("Processes: ", (struct s_pos){data->tbx, y},
			g_color[pl + MAX_PLAYERS + 2], data);
		c = process_count(vm->processes, pl + 1);
		d = living_count(vm->processes, pl + 1, vm);
		x += draw_score((struct s_pos){x, y}, c,
			g_color[pl + MAX_PLAYERS + 2], data);
		x += draw_str(" (", (struct s_pos){x, y},
			g_color[pl + MAX_PLAYERS + 2], data);
		x += draw_score((struct s_pos){x, y}, d,
			g_color[pl + MAX_PLAYERS + 2], data);
		draw_str(" alive)", (struct s_pos){x, y},
			g_color[pl + MAX_PLAYERS + 2], data);
		y += 18;
		pl++;
	}
	y += 8;
	return (y);
}

static void	display_winner(struct s_vdata *data, struct s_vm *vm, int y,
		int winner)
{
	int			x;

	x = draw_str("Winner: ", (struct s_pos){data->tbx, y}, COLOR_WHITE, data);
	draw_str(vm->headers[winner - 1].prog_name,
		(struct s_pos){x + data->tbx, y}, g_color[winner], data);
	y += 36;
	draw_str("Press any touch to continue...", (struct s_pos){data->tbx, y},
		COLOR_LNONE, data);
}

void	generate_toolbar(struct s_vdata *data, struct s_vm *vm,
		int last_frame)
{
	int		y;

	draw_str("Corewar - version 2.7", (struct s_pos){data->tbx, 10},
		COLOR_WHITE, data);
	y = draw_ply_scores(data, vm, 46);
	y = draw_kill_time(data, vm, y);
	y = draw_process_count(data, vm, y);
	if (last_frame)
		display_winner(data, vm, y, last_frame);
}

void		cw_update_window(struct s_vm *vm, struct s_vdata *data,
		int last_frame)
{
	SDL_PollEvent(&(data->ev));
	if ((data->ev.type == SDL_KEYDOWN && data->ev.key.keysym.sym == SDLK_ESCAPE)
		|| data->ev.type == SDL_QUIT)
		exit(0);
	if (data->ev.type == SDL_KEYDOWN && data->ev.key.keysym.sym == SDLK_SPACE)
	{
		SDL_WaitEvent(&(data->ev));
		while (data->ev.type != SDL_KEYDOWN ||
			data->ev.key.keysym.sym != SDLK_SPACE)
		{
			if ((data->ev.type == SDL_KEYDOWN && data->ev.key.keysym.sym
				== SDLK_ESCAPE) || data->ev.type == SDL_QUIT)
				exit(0);
			SDL_WaitEvent(&(data->ev));
		}
	}
	SDL_LockTexture(data->tx, NULL, (void **)&data->px, &data->pitch);
	ft_memset(data->px, '\0', data->sy * data->pitch);
	generate_borders(data);
	generate_arena(data, vm);
	generate_processes(data, vm->processes);
	generate_toolbar(data, vm, last_frame);
	SDL_UnlockTexture(data->tx);
	SDL_RenderCopy(data->rd, data->tx, NULL, NULL);
	SDL_RenderPresent(data->rd);
}
