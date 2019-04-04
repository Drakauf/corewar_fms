/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   graphics.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 13:45:44 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 14:04:40 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"
#include <math.h>

const int	g_color[2 * MAX_PLAYERS + 2] = {
	COLOR_NONE, COLOR_ORANGE, COLOR_GREEN, COLOR_CYAN, COLOR_RED,
	COLOR_LNONE, COLOR_LORANGE, COLOR_LGREEN, COLOR_LCYAN, COLOR_LRED
};

extern int	*g_font[256];

static void	generate_borders(struct s_vdata *data)
{
	int		color;
	int		x;
	int		y;

	color = COLOR_BORDER;
	x = -1;
	while (++x < BORDER_SIZE)
	{
		y = -1;
		while (++y < data->sy)
		{
			data->px[x + y * data->sx] = color;
			data->px[(data->tbx - x - 1 - CHAR_SP / 2) + y * data->sx] = color;
			data->px[(data->sx - x - 1) + y * data->sx] = color;
		}
	}
	x = -1;
	while (++x < data->sx)
	{
		y = -1;
		while (++y < BORDER_SIZE)
		{
			data->px[x + y * data->sx] = color;
			data->px[x + (data->sy - y - 1) * data->sx] = color;
		}
	}
}

void		cw_init_window(struct s_vdata *data)
{
	int		t;

	data->tbx = (MEM_COLS * (CHAR_SX * 2 + CHAR_SP)) + BORDER_SIZE * 2 + CHAR_SP / 2;
	data->sx = data->tbx + (TB_MAX_CHARS * CHAR_SX) + BORDER_SIZE;
	data->sy = MEM_LINES * (CHAR_SY + CHAR_VSP) + BORDER_SIZE * 2;
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

unsigned char to_hex(unsigned char c)
{
	if (c < 10)
		return (c + '0');
	else
		return (c + 'A' - 0xA);
}

static void	draw_afont(struct s_vdata *data, void *arena, void *ainfo,
		struct s_pos p, struct s_pos i)
{
	struct s_pos	px;
	unsigned char	left;
	unsigned char	right;
	unsigned char	info;

	info = ((unsigned char *)ainfo)[i.x + i.y * MEM_COLS];
	if (info >= MAX_PLAYERS + 1)
	{
		((unsigned char *)ainfo)[i.x + i.y * MEM_COLS] -= (MAX_PLAYERS + 1);
		info = (info % (MAX_PLAYERS + 1)) + MAX_PLAYERS + 1;
	}
	left = ((unsigned char *)arena)[i.x + i.y * MEM_LINES];
	right = to_hex(left & 15);
	left = to_hex(left >> 4);
	px.y = 0;
	while (px.y < CHAR_SY)
	{
		px.x = 0;
		while (px.x < CHAR_SX)
		{
			data->px[p.x + px.x + (p.y + px.y) * data->sx] =
				data->font[left][px.x + px.y * CHAR_SX] * g_color[(int)(info & 15)];
			data->px[p.x + px.x + CHAR_SX + CHAR_HSP + (p.y + px.y) * data->sx] =
				data->font[right][px.x + px.y * CHAR_SX] * g_color[(int)(info & 15)];
			px.x++;
		}
		px.y++;
	}
}

static void	generate_arena(struct s_vdata *data, void *arena, void *ainfo)
{
	struct s_pos	i;
	struct s_pos	p;

	i.y = 0;
	while (i.y < MEM_LINES)
	{
		p.y = BORDER_SIZE + (CHAR_VSP / 2) + (CHAR_SY + CHAR_VSP) * i.y;
		i.x = 0;
		while (i.x < MEM_COLS)
		{
			p.x = BORDER_SIZE + (CHAR_BSP / 2) + (CHAR_SX * 2 + CHAR_SP) * i.x;
			draw_afont(data, arena, ainfo, p, i);
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
		start.x = proc->pcount % MEM_COLS;
		start.y = proc->pcount / MEM_COLS;
		start.x = BORDER_SIZE + (CHAR_SX * 2 + CHAR_SP) * start.x;
		start.y = BORDER_SIZE + (CHAR_SY + CHAR_VSP) * start.y;
		i.y = start.y;
		while (i.y < start.y + CHAR_SY + CHAR_VSP - 1)
		{
			data->px[start.x + i.y * data->sx] = color;
			data->px[start.x + CHAR_SX * 2 + CHAR_SP - 1 + i.y * data->sx] = color;
			i.y++;
		}
		i.x = start.x;
		while (i.x < start.x + CHAR_SX * 2 + CHAR_SP)
		{
			data->px[i.x + start.y * data->sx] = color;
			data->px[i.x + (start.y + CHAR_SY + CHAR_VSP - 1) * data->sx] = color;
			i.x++;
		}
		proc = proc->next;
	}
}

void		draw_line(struct s_pos start, struct s_pos end, int color, struct s_vdata *data)
{
	double	dx;
	double	dy;
	int		size;
	int		i;

	size = (int)hypot(end.x - start.x, end.y - start.y) + 1;
	dx = (end.x - start.x) / (double)size;
	dy = (end.y - start.y) / (double)size;
	i = 0;
	while (i <= size)
	{
		end.x = start.x + (dx * (double)i + 0.5);
		end.y = start.y + (dy * (double)i + 0.5);
		data->px[end.x + end.y * data->sx] = color;
		i++;
	}
}

int			draw_char(unsigned char c, struct s_pos p, int color, struct s_vdata *data)
{
	int		ix;
	int		iy;

	ix = 0;
	while (ix < CHAR_SX && ix + p.x < data->sx - BORDER_SIZE - 1)
	{
		iy = 0;
		while (iy < CHAR_SY)
		{
			data->px[p.x + ix + (p.y + iy) * data->sx] = data->font[c][ix + iy * CHAR_SX] * color;
			iy++;
		}
		ix++;
	}
	return (ix + CHAR_HSP);
}

void	draw_score(struct s_pos p, int lives, int color, struct s_vdata *data)
{
	int		i;
	char	*c;

	c = ft_itoa(lives);
	i = 0;
	while (c[i])
	{
		p.x += draw_char(c[i], p, color, data);
		i++;
	}
}

static int	draw_ply_scores(struct s_vdata *data, struct s_vm *vm)
{
	int		player;
	int		i;
	int		j;
	int		x;
	int		y;
	char	*name = "Corewar - version 2.6";

	player = 0;
	y = BORDER_SIZE + CHAR_VSP / 2;
	x = data->tbx;
	i = 0;
	while (name[i])
	{
		x += draw_char(name[i], (struct s_pos){x, y}, COLOR_WHITE, data);
		i++;
	}
	y += (CHAR_SY + CHAR_VSP) * 2;
	while (player < vm->players)
	{
		i = 0;
		x = data->tbx;
		while (vm->headers[player].prog_name[i])
		{
			x += draw_char(vm->headers[player].prog_name[i], (struct s_pos){x, y}, g_color[player + 1], data);
			i++;
		}
		x += CHAR_HSP * 2;
		x += draw_char('(', (struct s_pos){x, y}, g_color[player + 1], data);
		j = 0;
		while (vm->headers[player].comment[j] && i + j < TB_MAX_CHARS)
		{
			x += draw_char(vm->headers[player].comment[j], (struct s_pos){x, y}, g_color[player + 1], data);
			j++;
		}
		x += draw_char(')', (struct s_pos){x, y}, g_color[player + 1], data);
		y += CHAR_SY + CHAR_VSP;
		x = 0;
		j = 300;
		while (x < j)
		{
			draw_line((struct s_pos){x + data->tbx, y}, (struct s_pos){x + data->tbx, y + CHAR_SY - 1},
					(vm->llives[player] > vm->tcycles * x / j) ? g_color[player + 1] : COLOR_NONE, data);
			x++;
		}
		draw_score((struct s_pos){data->tbx + 300 + CHAR_SP, y}, vm->llives[player], g_color[player + 2 + MAX_PLAYERS], data);
		y += CHAR_SY + CHAR_VSP;
		player++;
	}
	return (y);
}

static int	draw_kill_time(struct s_vdata *data, struct s_vm *vm, int y)
{
	char	*info = "Next kill operation:";
	int		x;
	int		i;
	int		j;

	x = data->tbx;
	y += CHAR_SY * 2;
	i = 0;
	while (info[i])
	{
		x += draw_char(info[i], (struct s_pos){x, y}, COLOR_WHITE, data);
		i++;
	}
	y += CHAR_SY + CHAR_VSP;
	x = 0;
	j = 256;
	while (x < j)
	{
		draw_line((struct s_pos){x + data->tbx, y}, (struct s_pos){x + data->tbx, y + CHAR_SY - 1},
				(vm->cycles * 256 / vm->kcycles > x) ? ((255 - x) * 65536 + 65536 - 256) : COLOR_NONE, data);
		x++;
	}
	draw_score((struct s_pos){data->tbx + 256 + CHAR_SP, y}, vm->kcycles - vm->cycles, COLOR_WHITE, data);
	y += CHAR_SY + CHAR_VSP * 2;
	return (y);
}

static int	draw_process_count(struct s_vdata *data, struct s_vm *vm, int y)
{
	int				i;
	int				pl;
	int				c;
	int				x;
	struct s_proc	*p;
	char			*info = "Processes: ";

	pl = 0;
	while (pl < vm->players)
	{
		x = data->tbx;
		i = 0;
		while (info[i])
		{
			x += draw_char(info[i], (struct s_pos){x, y},
				g_color[pl + MAX_PLAYERS + 2], data);
			i++;
		}
		c = 0;
		p = vm->processes;
		while (p)
		{
			c += (p->number - 1 == pl);
			p = p->next;
		}
		draw_score((struct s_pos){x, y}, c, g_color[pl + MAX_PLAYERS + 2], data);
		y += CHAR_SY + CHAR_VSP;
		pl++;
	}
	y += CHAR_VSP;
	return (y);
}

static void	generate_toolbar(struct s_vdata *data, struct s_vm *vm, int last_frame)
{
	int		y;
	int		i;
	int		x;
	char	*info = "Winner: ";
	char	*disp = "Press any touch to continue";

	y = draw_ply_scores(data, vm);
	y = draw_kill_time(data, vm, y);
	y = draw_process_count(data, vm, y);
	if (last_frame)
	{
		x = data->tbx;
		i = 0;
		while (info[i])
		{
			x += draw_char(info[i], (struct s_pos){x, y}, COLOR_WHITE, data);
			i++;
		}
		i = 0;
		while (vm->headers[last_frame - 1].prog_name[i])
		{
			x += draw_char(vm->headers[last_frame - 1].prog_name[i],
				(struct s_pos){x, y}, g_color[last_frame], data);
			i++;
		}
		y += (CHAR_SY + CHAR_VSP) * 2;
		i = 0;
		x = data->tbx;
		while (disp[i])
		{
			x += draw_char(disp[i], (struct s_pos){x, y}, COLOR_LNONE, data);
			i++;
		}
	}
}

void		cw_update_window(struct s_vm *vm, int last_frame)
{
	struct s_vdata *data;

	data = vm->data;
	SDL_PollEvent(&(data->ev));
	if ((data->ev.type == SDL_KEYDOWN && data->ev.key.keysym.sym == SDLK_ESCAPE)
		|| data->ev.type == SDL_QUIT)
		exit(0);
	if (data->ev.type == SDL_KEYDOWN && data->ev.key.keysym.sym == SDLK_SPACE)
	{
		SDL_WaitEvent(&(data->ev));
		while (data->ev.type != SDL_KEYDOWN || data->ev.key.keysym.sym != SDLK_SPACE)
			SDL_WaitEvent(&(data->ev));
	}
	SDL_LockTexture(data->tx, NULL, (void **)&data->px, &data->pitch);
	ft_memset(data->px, '\0', data->sy * data->pitch);
	generate_borders(data);
	generate_arena(data, vm->arena, vm->ainfo);
	generate_processes(data, vm->processes);
	generate_toolbar(data, vm, last_frame);
	SDL_UnlockTexture(data->tx);
	SDL_RenderCopy(data->rd, data->tx, NULL, NULL);
	SDL_RenderPresent(data->rd);
}
